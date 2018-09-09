#include "Elba/Engine.hpp"
#include "OpenGLModule.hpp"

namespace Elba
{

int g_width = 800;
int g_height = 600;

void window_resize_callback(GLFWwindow* aWindow, int aWidth, int aHeight)
{
  glViewport(0, 0, aWidth, aHeight);
  g_width = aWidth;
  g_height = aHeight;
}

OpenGLModule::OpenGLModule(Engine* engine)
: GraphicsModule(engine)
{
}

void OpenGLModule::Initialize()
{
  Engine* engine = GetEngine();

  // Create window with GLFW if engine is NOT running in editor
  if (!engine->InEditor())
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(800, 600, "Elba", nullptr, nullptr);
    glfwMakeContextCurrent(mWindow);

    if (!mWindow)
    {
      glfwTerminate();

      throw std::exception("Failed to create GLFW Window");
    }

    GLenum err = glewInit();

    if (GLEW_OK != err)
    {
      throw std::exception("glewInit failed");
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(mWindow, window_resize_callback);
  }
}

void OpenGLModule::Update()
{
  // Run update if engine is NOT running in editor
  // If running in editor, the Render function will be called explicitly
  if (!GetEngine()->InEditor())
  {
    Render();
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
}

void OpenGLModule::Render()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

UniquePtr<Mesh> OpenGLModule::RequestMesh(std::string name)
{
  return std::move(mFactory->RequestMesh(name));
}

} // End of Elba namespace

