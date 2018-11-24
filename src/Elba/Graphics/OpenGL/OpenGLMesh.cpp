/**
* \file OpenGLMesh.cpp
* \author Nicholas Ammann
* \date 9/9/2018
* \brief Member function definitions for OpenGLMesh.
*/

#include <iostream>
#include <fstream>

#include <gl/glew.h>

#include <stbi/stb_image.h>

#include "Elba/Graphics/OpenGL/OpenGLMesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLVertexShader.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFragmentShader.hpp"

#include "Elba/Utilities/Utils.hpp"

namespace Elba
{

OpenGLMesh::OpenGLMesh()
{
}

void OpenGLMesh::Initialize()
{
  for (OpenGLSubmesh& submesh : mSubmeshes)
  {
    submesh.Initialize();
  }
}

void OpenGLMesh::Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model, const PointLight& light)
{
  for (OpenGLSubmesh& submesh : mSubmeshes)
  {
    submesh.Draw(proj, view, model, light);
  }
}

void OpenGLMesh::LoadShader(std::string name)
{
  std::string assetsDir = Utils::GetAssetsDirectory();

  std::string vertPath = assetsDir + "Shaders/" + name + ".vert";
  UniquePtr<OpenGLVertexShader> vertShader = NewUnique<OpenGLVertexShader>(vertPath);

  std::string fragPath = assetsDir + "Shaders/" + name + ".frag";
  UniquePtr<OpenGLFragmentShader> fragShader = NewUnique<OpenGLFragmentShader>(fragPath);

  mShaderProgram = std::make_shared<OpenGLProgram>(name.c_str());
  mShaderProgram->AttachShader(std::move(vertShader));
  mShaderProgram->AttachShader(std::move(fragShader));
  mShaderProgram->Link();

  for (OpenGLSubmesh& submesh : mSubmeshes)
  {
    submesh.SetShaders(mShaderProgram);
  }
}

std::vector<OpenGLSubmesh>& OpenGLMesh::GetSubmeshes()
{
  return mSubmeshes;
}

OpenGLProgram* OpenGLMesh::GetShaderProgram() const
{
  return mShaderProgram.get();
}

void OpenGLMesh::LoadMesh(std::string path)
{
  Assimp::Importer import;

  const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    std::cout << "Assimp Error: " << import.GetErrorString() << std::endl;
    return;
  }

  mDirectory = path.substr(0, path.find_last_of('/'));

  ProcessNode(scene->mRootNode, scene);
}

void OpenGLMesh::ProcessNode(aiNode* node, const aiScene* scene)
{
  for (unsigned int i = 0; i < node->mNumMeshes; ++i)
  {
    aiMesh *assimpSubmesh = scene->mMeshes[node->mMeshes[i]];
    UniquePtr<OpenGLSubmesh> submesh = ProcessSubmesh(assimpSubmesh, scene);
    mSubmeshes.emplace_back(*submesh);
  }

  for (unsigned int i = 0; i < node->mNumChildren; ++i)
  {
    ProcessNode(node->mChildren[i], scene);
  }
}

UniquePtr<OpenGLSubmesh> OpenGLMesh::ProcessSubmesh(aiMesh* mesh, const aiScene* scene)
{
  std::vector<Vertex> verts;
  std::vector<Face> faces;
  std::vector<OpenGLTexture> texs;

  for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
  {
    Vertex vertex;

    // position
    vertex.mPos.x = mesh->mVertices[i].x;
    vertex.mPos.y = mesh->mVertices[i].y;
    vertex.mPos.z = mesh->mVertices[i].z;

    // normal
    vertex.mNormal.x = mesh->mNormals[i].x;
    vertex.mNormal.y = mesh->mNormals[i].y;
    vertex.mNormal.z = mesh->mNormals[i].z;

    // texture coordinates
    if (mesh->mTextureCoords[0])
    {
      vertex.mTexCoords.x = mesh->mTextureCoords[0][i].x;
      vertex.mTexCoords.y = mesh->mTextureCoords[0][i].y;
    }
    else
    {
      vertex.mTexCoords = glm::vec2(0.0f, 0.0f);
    }

    verts.push_back(vertex);
  }

  // indices
  for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
  {
    aiFace assimpFace = mesh->mFaces[i];
    faces.emplace_back(assimpFace.mIndices[0], assimpFace.mIndices[1], assimpFace.mIndices[2]);
  }

  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

  UniquePtr<OpenGLSubmesh> submesh = NewUnique<OpenGLSubmesh>(verts, faces);

  // store diffuse maps
  std::vector<OpenGLTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
  if (!diffuseMaps.empty())
  {
    OpenGLTexture* diffuse = new OpenGLTexture(*diffuseMaps.begin());
    submesh->LoadTexture(diffuse, TextureType::Diffuse);
  }

  // store specular maps
  std::vector<OpenGLTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
  if (!specularMaps.empty())
  {
    OpenGLTexture* specular = new OpenGLTexture(*specularMaps.begin());
    submesh->LoadTexture(specular, TextureType::Specular);
  }

  std::vector<OpenGLTexture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT);
  if (!normalMaps.empty())
  {
    OpenGLTexture* normal = new OpenGLTexture(*normalMaps.begin());
    submesh->LoadTexture(normal, TextureType::Normal);
  }

  // store height maps
  std::vector<OpenGLTexture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT);
  if (!heightMaps.empty())
  {
    OpenGLTexture* height = new OpenGLTexture(*heightMaps.begin());
    submesh->LoadTexture(height, TextureType::Height);
  }

  return std::move(submesh);
}

std::vector<OpenGLTexture> OpenGLMesh::LoadMaterialTextures(aiMaterial* aMat, aiTextureType aType)
{
  std::vector<OpenGLTexture> texs;

  for (unsigned int i = 0; i < aMat->GetTextureCount(aType); ++i)
  {
    aiString str;
    aMat->GetTexture(aType, i, &str);

    bool alreadyLoaded = false;

    for (unsigned int j = 0; j < mLoadedTextures.size(); ++j)
    {
      if (std::strcmp(mLoadedTextures[j].GetPath().c_str(), str.C_Str()) == 0)
      {
        texs.push_back(mLoadedTextures[j]);
        alreadyLoaded = true;
        break;
      }
    }

    if (!alreadyLoaded)
    {
      std::string textureDir = Utils::GetAssetsDirectory() + "Textures/";
      OpenGLTexture texture((textureDir + std::string(str.C_Str())).c_str());
      texs.push_back(texture);
      mLoadedTextures.push_back(texture);
    }
  }
  return texs;
}

unsigned int OpenGLMesh::LoadBMP(const char* aFile, std::string aDir)
{
  std::string fullPath = aDir + "/" + aFile;

  char header[54] = { '\0' };
  unsigned int dataPos = 0;
  unsigned int width, height = 0;
  unsigned int imageSize = 0;
  char *data = nullptr;

  std::ifstream file(fullPath);

  if (file.is_open())
  {
    file.read(header, 54);

    if (header[0] != 'B' || header[1] != 'M')
    {
      std::cout << "Not a BMP File" << std::endl;
      return 0;
    }

    dataPos = *(int*)&(header[0x0A]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    imageSize = *(int*)&(header[0x22]);

    if (imageSize == 0)
    {
      imageSize = width * height * 3;
    }

    if (dataPos == 0)
    {
      dataPos = 54;
    }

    data = new char[imageSize];

    file.read(data, imageSize - 54);
    file.close();

    unsigned int texID;
    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return texID;
  }
  else
  {
    std::cout << "BMP Texture could not be loaded." << std::endl;
  }

  return 0;
}

unsigned int OpenGLMesh::LoadTexture(const char* aFile, std::string aDir)
{
  std::string fullPath = aDir + "/" + aFile;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(fullPath.c_str(), &width, &height, &nrComponents, 0);

  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << fullPath << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

} // End of Elba namespace
