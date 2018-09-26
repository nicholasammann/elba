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
  , mFactory(NewUnique<OpenGLFactory>(this))
  , mCamera(NewUnique<Camera>())
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

    mWindow = glfwCreateWindow(g_width, g_height, "Elba", nullptr, nullptr);
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

    glEnable(GL_DEPTH_TEST);
  }
}

void OpenGLModule::Update()
{
  // Run update if engine is NOT running in editor
  // If running in editor, the Render function will be called explicitly
  if (!GetEngine()->InEditor())
  {
    Render(g_width, g_height);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
}

void OpenGLModule::Render(int screenWidth, int screenHeight)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawEvent event;

  event.proj = mCamera->ConstructProjMatrix(screenWidth, screenHeight);
  event.view = mCamera->ConstructViewMatrix();

  for (auto& pair : mDrawCallbacks)
  {
    pair.second(event);
  }
}

UniquePtr<Mesh> OpenGLModule::RequestMesh(std::string name)
{
  return mFactory->RequestMesh(name);
}

} // End of Elba namespace

