#include <qcheckbox.h>
#include <qlayout.h>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFramebuffer.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/PostProcessingOptions.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/AddEffectContextMenu.hpp"

namespace Editor
{
PostProcessingOptions::PostProcessingOptions(Framework::Workspace* workspace)
  : Widget(workspace)
{
  QVBoxLayout* layout = new QVBoxLayout(this);

  //QCheckBox* postProcessing = new QCheckBox("Use Post Processing");
  //postProcessing->setChecked(true);
  //connect(postProcessing, &QCheckBox::stateChanged,
  //  this, &PostProcessingOptions::OnUsePostProcessingChanged);
  //layout->addWidget(postProcessing);

  mTree = new QTreeWidget(this);
  mTree->setHeaderLabel("Post Processing Pipeline");
  mTree->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(mTree, &QWidget::customContextMenuRequested, this, &PostProcessingOptions::OnContextMenu);

  layout->addWidget(mTree);

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

QTreeWidgetItem* PostProcessingOptions::AddItem(QString header)
{
  QTreeWidgetItem* result = new QTreeWidgetItem(mTree);
  result->setText(0, header);
  mTree->addTopLevelItem(result);
  return result;
}

QTreeWidget* PostProcessingOptions::GetTree()
{
  return mTree;
}

void PostProcessingOptions::OnContextMenu(const QPoint& point)
{
  AddEffectContextMenu* menu = new AddEffectContextMenu(GetWorkspace<LevelEditor>(), this);
  QPoint globalPos = mTree->mapToGlobal(point);
  menu->exec(globalPos);
}

/*
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
*/

} // End of Editor namespace

