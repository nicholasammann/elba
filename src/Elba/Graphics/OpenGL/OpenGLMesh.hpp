#pragma once

/**
* \file OpenGLMesh.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Class definition for OpenGLMesh.
*/

#include <glm/mat4x4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Elba/Utilities/StdTypedefs.hpp"

#include "Elba/Graphics/GraphicsForwardDeclarations.hpp"

#include "Elba/Graphics/Mesh.hpp"
#include "Elba/Graphics/PointLight.hpp"
#include "Elba/Graphics/OpenGL/OpenGLSubmesh.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

namespace Elba
{
/**
* \brief Mesh that contains Submeshes.
*/
class OpenGLMesh : public Mesh
{
public:
  /**
  * \brief Constructor
  */
  OpenGLMesh();

  /**
  * \brief Initializes all contained submeshes.
  */
  void Initialize() final;

  /**
  * \brief Draws all submeshes contained by this Mesh.
  * \param proj The projection matrix.
  * \param view The view matrix.
  * \param model The model matrix.
  */
  void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model, const PointLight& light) final;

  /**
  * \brief Loads the mesh file at the given path.
  * \param path The path to the model file.
  */
  void LoadMesh(std::string path) final;

  void LoadShader(std::string name) final;

  std::vector<OpenGLSubmesh>& GetSubmeshes();

  OpenGLProgram* GetShaderProgram() const;

private:
  std::vector<OpenGLSubmesh> mSubmeshes;

  std::string mDirectory;

  std::shared_ptr<OpenGLProgram> mShaderProgram;

  /**
  * \brief Processes one node in the assimp tree.
  * \param node The node that will be processed.
  * \param scene The scene that the node is in? Honestly can't remember. It contains materials.
  */
  void ProcessNode(aiNode *node, const aiScene *scene);

  /**
  * \brief Processes a submesh contained in the mesh.
  * \param node The mesh that will be processed.
  * \param scene The scene that the node is in? Honestly can't remember. It contains materials.
  */
  UniquePtr<OpenGLSubmesh> ProcessSubmesh(aiMesh *mesh, const aiScene *scene);

  std::vector<OpenGLTexture> LoadMaterialTextures(aiMaterial *aMat, aiTextureType aType);
  unsigned int LoadBMP(const char *aFile, std::string aDir);
  unsigned int LoadTexture(const char *aFile, std::string aDir);
  std::vector<OpenGLTexture> mLoadedTextures;
};

} // End of Elba namespace
