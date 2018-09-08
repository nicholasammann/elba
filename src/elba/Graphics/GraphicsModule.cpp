/**
* \file GraphicsModule.cpp
* \author Nicholas Ammann
* \date 2/24/2018
* \brief Class definition for GraphicsModule.
*/

#include <iostream>


#include "Elba/Engine.hpp"

#include "Elba/Graphics/GraphicsModule.hpp"

int g_width = 800;
int g_height = 600;

void window_resize_callback(GLFWwindow * aWindow, int aWidth, int aHeight)
{
  glViewport(0, 0, aWidth, aHeight);
  g_width = aWidth;
  g_height = aHeight;
}

namespace Elba
{
GraphicsModule::GraphicsModule(Engine* engine)
  : Module(engine)
  , mFactory(NewUnique<GraphicsFactory>(this))
  , mWindow(nullptr)
{
}

void GraphicsModule::Initialize()
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

void GraphicsModule::Update()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



  glfwSwapBuffers(mWindow);
  glfwPollEvents();
}

GraphicsFactory* GraphicsModule::GetFactory() const
{
  return mFactory.get();
}

} // End of Elba namespace
