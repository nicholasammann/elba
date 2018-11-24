#include <qcheckbox.h>
#include <qlayout.h>

#include "Elba/Engine.hpp"
#include "Elba/Core/CoreModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLFramebuffer.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/AddEffectContextMenu.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/EffectItemWidget.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/PostProcessingOptions.hpp"

namespace Editor
{
PostProcessingOptions::PostProcessingOptions(Framework::Workspace* workspace)
  : Widget(workspace)
{
  QVBoxLayout* layout = new QVBoxLayout(this);

  QCheckBox* hatching = new QCheckBox("Use Hatching");
  hatching->setChecked(true);
  connect(hatching, &QCheckBox::stateChanged,
    this, &PostProcessingOptions::OnUseHatchingChanged);
  layout->addWidget(hatching);

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

EffectItemWidget* PostProcessingOptions::AddItem(QString header, Elba::OpenGLComputeShader* shader)
{
  QTreeWidgetItem* item = new QTreeWidgetItem(mTree);
  item->setText(0, header);
  mTree->addTopLevelItem(item);

  QTreeWidgetItem* child = new QTreeWidgetItem(item);
  item->addChild(child);

  EffectItemWidget* result = new EffectItemWidget(header, shader, this);
  mTree->setItemWidget(child, 0, result);

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

void PostProcessingOptions::OnUseHatchingChanged(int value)
{
  LevelEditor* editor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::Model* model = object->GetComponent<Elba::Model>();

  if (value)
  {
    model->LoadShader("hatching");
  }
  else
  {
    model->LoadShader("textured");
  }
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

