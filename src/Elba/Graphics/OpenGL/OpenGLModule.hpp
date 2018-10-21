#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "Elba/Graphics/GraphicsModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLFactory.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFramebuffer.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"

#include "Elba/Graphics/Camera.hpp"

#include "Elba/Utilities/StdTypedefs.hpp"

namespace Elba
{
/**
* \brief OpenGL implementation of graphics module.
*/
class OpenGLModule : public GraphicsModule
{
public:
  /**
  * \brief Constructor
  * \param engine The engine, which owns all modules.
  */
  OpenGLModule(Engine* engine);

  /**
  * \brief Initialize function called by Engine. Initializes GraphicsModule.
  */
  void Initialize() final;

  /**
  * \brief Initializes framebuffer for post processing.
  */
  void InitializePostProcessing();

  /**
  * \brief Update function called by Engine. Updates graphics.
  */
  void Update(double dt) final;

  /**
  * \brief Window/context agnostic rendering calls.
  */
  void Render(int screenWidth, int screenHeight) final;

  /**
  * \brief Constructs a Mesh and adds it to the graphics module.
  * \param name The name of the fbx file.
  * \return The Mesh that was just created.
  */
  UniquePtr<Mesh> RequestMesh(std::string name) final;

  std::pair<int, int> GetScreenDimensions() const;

  void SetClearColor(glm::vec4 color);

  Camera* GetCamera();

  OpenGLFramebuffer* GetFramebuffer();

  void SetUseFramebuffer(bool useFramebuffer);

  OpenGLPostProcess* GetPostProcess();

private:
  UniquePtr<OpenGLFactory> mFactory;
  GLFWwindow* mWindow;
  UniquePtr<Camera> mCamera;

  UniquePtr<OpenGLFramebuffer> mFramebuffer;
  bool mUseFramebuffer;

  UniquePtr<OpenGLPostProcess> mPostProcess;

  glm::vec4 mClearColor;
};

} // End of Elba namespace


