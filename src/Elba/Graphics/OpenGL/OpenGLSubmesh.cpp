#include <algorithm>

#include <gl/glew.h>

#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

namespace Elba
{

static std::string uniformNames[4] = { "diffuseTex", "specularTex", "normalTex", "heightTex" };

OpenGLSubmesh::OpenGLSubmesh()
  : Submesh()
  , mProgram(nullptr)
  , mTextures{ nullptr }
{
}

OpenGLSubmesh::OpenGLSubmesh(const std::vector<Vertex>& verts, const std::vector<Face>& faces)
  : Submesh()
  , mProgram(nullptr)
  , mTextures{ nullptr }
{
  mVertices = verts;
  mFaces = faces;
}

void OpenGLSubmesh::Initialize()
{
  //// Vertex Array Object ////
  // create and bind vertex array object
  glGenVertexArrays(1, &mVAO);
  glBindVertexArray(mVAO);
  //////////////////////////////

  //// Vertex Buffer Object ////
  // create and bind empty vertex buffer object
  glGenBuffers(1, &mVBO);
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
  //////////////////////////////

  unsigned int *indices = new unsigned int[mFaces.size() * 3];

  for (unsigned int i = 0; i < mFaces.size(); ++i)
  {
    for (unsigned int j = 0; j < 3; ++j)
    {
      indices[3 * i + j] = mFaces[i].mIndices[j];
    }
  }

  //// Element Buffer Object ////
  // create and bind empty element buffer object
  glGenBuffers(1, &mEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mFaces.size() * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
  ///////////////////////////////

  // tell OpenGL how it should interpret all vertex data
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mColor));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mTexCoords));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));

  glBindVertexArray(0);
}

void OpenGLSubmesh::Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model, const PointLight& light)
{
  // Can't draw anything without a shader
  if (!mProgram)
  {
    return;
  }

  mProgram->Use();
  GLuint prg = mProgram->Get();

  unsigned int usedTextures = 0;

  for (int i = 0; i < TextureType::TypeCount; ++i)
  {
    if (mTextures[i])
    {
      mTextures[i]->SetUniform(prg, uniformNames[i], usedTextures);
      mTextures[i]->Bind(usedTextures++);
    }
  }

  for (OpenGLTexture* texture : mExtraTextures)
  {
    texture->SetUniform(prg, texture->GetUniformName(), usedTextures);
    texture->Bind(usedTextures++);
  }

  /*
  unsigned int shdrPrg = mShader->GetShaderProgram();

  unsigned int matLoc = glGetUniformLocation(shdrPrg, "Material.ambient");
  glUniform4fv(matLoc, 1, mMaterial.ambient);

  matLoc = glGetUniformLocation(shdrPrg, "Material.diffuse");
  glUniform4fv(matLoc, 1, mMaterial.diffuse);

  matLoc = glGetUniformLocation(shdrPrg, "Material.specular");
  glUniform4fv(matLoc, 1, mMaterial.specular);

  matLoc = glGetUniformLocation(shdrPrg, "Material.emissive");
  glUniform4fv(matLoc, 1, mMaterial.emissive);

  matLoc = glGetUniformLocation(shdrPrg, "Material.shininess");
  glUniform1f(matLoc, mMaterial.shininess);
  */

  mProgram->SetUniform("view", view);
  mProgram->SetUniform("projection", proj);
  mProgram->SetUniform("model", model);
  mProgram->SetUniform("pointLight.position", light.GetPosition());
  mProgram->SetUniform("pointLight.intensity", light.GetIntensity());

  glBindVertexArray(mVAO);
  glDrawElements(GL_TRIANGLES, static_cast<int>(mFaces.size()) * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  for (int i = 0; i < TextureType::TypeCount; ++i)
  {
    if (mTextures[i])
    {
      mTextures[i]->Unbind();
    }
  }

  for (OpenGLTexture* texture : mExtraTextures)
  {
    texture->Unbind();
  }
}

void OpenGLSubmesh::SetShaders(std::shared_ptr<OpenGLProgram> program)
{
  mProgram = program;
}

void OpenGLSubmesh::LoadTexture(const std::string& path, TextureType type)
{
  if (mTextures[type])
  {
    delete mTextures[type];
  }

  // should validate path at some point
  mTextures[type] = new OpenGLTexture(path);

  // dispatch event to all listeners
  TextureChangeEvent event;
  event.newTexture = mTextures[type];
  event.type = type;

  for (auto cb : mTextureChangeCallbacks)
  {
    cb.second(event);
  }
}

void OpenGLSubmesh::LoadTexture(OpenGLTexture* texture, TextureType type)
{
  // make sure the new texture exists before we...
  if (!texture)
  {
    return;
  }

  // DELETE OUR CURRENT GOOD BOI
  if (mTextures[type])
  {
    delete mTextures[type];
  }

  // fine, we'll take the new doggo
  mTextures[type] = texture;

  // dispatch event to all listeners
  TextureChangeEvent event;
  event.newTexture = mTextures[type];
  event.type = type;

  for (auto cb : mTextureChangeCallbacks)
  {
    cb.second(event);
  }
}

OpenGLTexture* OpenGLSubmesh::GetTexture(TextureType type) const
{
  return mTextures[type];
}

void OpenGLSubmesh::RegisterForTextureChange(Elba::GlobalKey key, TextureChangeCallback callback)
{
  mTextureChangeCallbacks.emplace_back(std::make_pair(key, callback));
}

bool OpenGLSubmesh::DeregisterForTextureChange(Elba::GlobalKey key)
{
  auto result = std::find_if(mTextureChangeCallbacks.begin(), mTextureChangeCallbacks.end(),
    [key](const std::pair<Elba::GlobalKey, TextureChangeCallback>& pair)
  {
    if (key.ToStdString() == pair.first.ToStdString())
    {
      return true;
    }
    return false;
  });

  if (result != mTextureChangeCallbacks.end())
  {
    mTextureChangeCallbacks.erase(result);
    return true;
  }

  return false;
}

void OpenGLSubmesh::AddTexture(OpenGLTexture* texture)
{
  mExtraTextures.push_back(texture);
}

} // End of Elba namespace
