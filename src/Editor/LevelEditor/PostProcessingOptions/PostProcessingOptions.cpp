#include <qcheckbox.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qcombobox.h>

#include "Elba/Engine.hpp"
#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/CS370/VideoTransitions.hpp"
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

  // VIDEO CONTROLS
  QWidget* videoControls = new QWidget(this);
  QVBoxLayout* videoLayout = new QVBoxLayout(videoControls);
  videoControls->setLayout(videoLayout);

  QWidget* videoButtons = new QWidget(videoControls);
  QHBoxLayout* buttonsLayout = new QHBoxLayout(videoButtons);
  videoButtons->setLayout(buttonsLayout);
  QPushButton* toRealTime = new QPushButton("To Real Time");
  connect(toRealTime, &QPushButton::pressed, this, &PostProcessingOptions::OnTransitionToRealTime);
  QPushButton* toStaticImage = new QPushButton("To Static Image");
  connect(toStaticImage, &QPushButton::pressed, this, &PostProcessingOptions::OnTransitionToStaticImage);
  buttonsLayout->addWidget(toRealTime);
  buttonsLayout->addWidget(toStaticImage);

  QWidget* modeSelect = new QWidget(videoControls);
  QHBoxLayout* modeLayout = new QHBoxLayout(modeSelect);
  modeSelect->setLayout(modeLayout);
  QLabel* modeLabel = new QLabel("Transition Mode");
  QComboBox* modeCombo = new QComboBox(modeSelect);
  modeCombo->addItem("Transition A");
  modeCombo->addItem("Transition B");
  modeCombo->addItem("Transition C");
  connect(modeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PostProcessingOptions::OnTransitionModeChanged);
  modeLayout->addWidget(modeLabel);
  modeLayout->addWidget(modeCombo);

  videoLayout->addWidget(videoButtons);
  videoLayout->addWidget(modeSelect);
  layout->addWidget(videoControls);
  //////////////////


  QCheckBox* hatching = new QCheckBox("Use Hatching");
  hatching->setChecked(true);
  connect(hatching, &QCheckBox::stateChanged,
    this, &PostProcessingOptions::OnUseHatchingChanged);
  layout->addWidget(hatching);

  QLineEdit* lightIntensity = new QLineEdit();
  lightIntensity->setValidator(new QDoubleValidator());
  connect(lightIntensity, &QLineEdit::textEdited, this, &PostProcessingOptions::OnLightIntensityChanged);
  layout->addWidget(lightIntensity);

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
    // load hatching textures to mesh
  }
  else
  {
    model->LoadShader("textured");
    // load regular textures to mesh
  }
}

void PostProcessingOptions::OnLightIntensityChanged(const QString& value)
{
  LevelEditor* editor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  graphics->SetLightIntensity(value.toFloat());
}

void PostProcessingOptions::OnTransitionToRealTime()
{
  LevelEditor* editor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::VideoTransitions* comp = object->GetComponent<Elba::VideoTransitions>();

  if (comp)
  {
    comp->TriggerTransitionToRealTime();
  }
}

void PostProcessingOptions::OnTransitionToStaticImage()
{
  LevelEditor* editor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::VideoTransitions* comp = object->GetComponent<Elba::VideoTransitions>();

  if (comp)
  {
    comp->TriggerTransitionToStaticImage();
  }
}

void PostProcessingOptions::OnTransitionModeChanged(int value)
{
  LevelEditor* editor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::VideoTransitions* comp = object->GetComponent<Elba::VideoTransitions>();

  if (comp)
  {
    comp->SetMode(value);
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

