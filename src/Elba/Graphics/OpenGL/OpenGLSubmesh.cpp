#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLSubmesh.hpp"

namespace Elba
{

OpenGLSubmesh::OpenGLSubmesh()
  : Submesh()
{
}

OpenGLSubmesh::OpenGLSubmesh(const std::vector<Vertex>& verts, const std::vector<Face>& faces)
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
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));

  glBindVertexArray(0);
}

void OpenGLSubmesh::Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model)
{
  if (mShader)
  {
    mShader->UseShaderProgram();
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
  GLuint shdrPrg = mShader->GetShaderProgram();

  unsigned int viewLoc = glGetUniformLocation(shdrPrg, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  unsigned int projLoc = glGetUniformLocation(shdrPrg, "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

  unsigned int modelLoc = glGetUniformLocation(shdrPrg, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  glBindVertexArray(mVAO);
  glDrawElements(GL_TRIANGLES, mFaces.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void OpenGLSubmesh::SetShader(OpenGLShader* shader)
{
  mShader = shader;
}

} // End of Elba namespace
