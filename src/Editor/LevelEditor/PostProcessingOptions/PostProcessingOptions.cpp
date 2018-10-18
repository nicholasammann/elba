#include <qcheckbox.h>
#include <qlayout.h>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFramebuffer.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/PostProcessingOptions.hpp"

namespace Editor
{
PostProcessingOptions::PostProcessingOptions(Framework::Workspace* workspace)
  : Widget(workspace)
{
  QVBoxLayout* layout = new QVBoxLayout();

  QCheckBox* postProcessing = new QCheckBox("Use Post Processing");
  connect(postProcessing, &QCheckBox::stateChanged,
    this, &PostProcessingOptions::OnUsePostProcessingChanged);
  layout->addWidget(postProcessing);

  QCheckBox* edgeDetection = new QCheckBox("Edge Detection");
  connect(edgeDetection, &QCheckBox::stateChanged,
          this, &PostProcessingOptions::OnEdgeDetectionChanged);
  layout->addWidget(edgeDetection);

  QCheckBox* blur= new QCheckBox("Blur");
  connect(blur, &QCheckBox::stateChanged,
          this, &PostProcessingOptions::OnBlurChanged);
  layout->addWidget(blur);

  layout->setAlignment(Qt::AlignTop);

  setLayout(layout);
}

Framework::Widget::DockArea PostProcessingOptions::GetDefaultDockArea() const
{
  return DockArea::Left;
}

Framework::Widget::DockArea PostProcessingOptions::GetAllowedDockAreas() const
{
  return DockArea::All;
}

void PostProcessingOptions::OnUsePostProcessingChanged(int value)
{
  LevelEditor* levelEditor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = levelEditor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  Elba::OpenGLModule* glModule = static_cast<Elba::OpenGLModule*>(graphics);

  glModule->SetUseFramebuffer(static_cast<bool>(value));
}

void PostProcessingOptions::OnEdgeDetectionChanged(int value)
{
  LevelEditor* levelEditor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = levelEditor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  Elba::OpenGLModule* glModule = static_cast<Elba::OpenGLModule*>(graphics);

  //std::vector<Elba::OpenGLPostProcessBuffer*>& buffers = glModule->GetPostProcessingBuffers();
  //Elba::OpenGLPostProcessBuffer* buffer = *buffers.begin();

  //buffer->SetEdgeDetection(value);
}

void PostProcessingOptions::OnBlurChanged(int value)
{
  LevelEditor* levelEditor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = levelEditor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  Elba::OpenGLModule* glModule = static_cast<Elba::OpenGLModule*>(graphics);

  //std::vector<Elba::OpenGLPostProcessBuffer*>& buffers = glModule->GetPostProcessingBuffers();
  //Elba::OpenGLPostProcessBuffer* buffer = *buffers.begin();

  //buffer->SetBlur(value);
}

} // End of Editor namespace

