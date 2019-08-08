#include <qcheckbox.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qcombobox.h>

#include "Elba/Engine.hpp"
#include "Elba/Core/CoreModule.hpp"
#include "Elba/GameLogic/Rotate.hpp"
#include "Elba/GameLogic/CS370/VideoTransitions.hpp"
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

  // Object Movement
  QWidget* moveSpeedWidg = new QWidget();
  QHBoxLayout* moveSpeedLayout = new QHBoxLayout(moveSpeedWidg);
  moveSpeedWidg->setLayout(moveSpeedLayout);
  QLabel* moveSpeedLabel = new QLabel("Move Speed");
  QLineEdit* moveSpeed = new QLineEdit(moveSpeedWidg);
  moveSpeed->setText("0.0");
  moveSpeed->setValidator(new QDoubleValidator());
  connect(moveSpeed, &QLineEdit::textEdited, this, &PostProcessingOptions::OnMoveSpeedChanged);
  moveSpeedLayout->addWidget(moveSpeedLabel);
  moveSpeedLayout->addWidget(moveSpeed);
  layout->addWidget(moveSpeedWidg);

  QWidget* rotateSpeedWidg = new QWidget();
  QHBoxLayout* rotateSpeedLayout = new QHBoxLayout(rotateSpeedWidg);
  rotateSpeedWidg->setLayout(rotateSpeedLayout);
  QLabel* rotateSpeedLabel = new QLabel("Rotate Speed");
  QLineEdit* rotateSpeed = new QLineEdit(rotateSpeedWidg);
  rotateSpeed->setText("0.0");
  rotateSpeed->setValidator(new QDoubleValidator());
  connect(rotateSpeed, &QLineEdit::textEdited, this, &PostProcessingOptions::OnRotateSpeedChanged);
  rotateSpeedLayout->addWidget(rotateSpeedLabel);
  rotateSpeedLayout->addWidget(rotateSpeed);
  layout->addWidget(rotateSpeedWidg);


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
  hatching->setChecked(false);
  connect(hatching, &QCheckBox::stateChanged,
    this, &PostProcessingOptions::OnUseHatchingChanged);
  layout->addWidget(hatching);

  QWidget* lightWidget = new QWidget();
  QHBoxLayout* lightLayout = new QHBoxLayout(lightWidget);
  lightWidget->setLayout(lightLayout);
  QLabel* lightLabel = new QLabel("Light Intensity");
  QLineEdit* lightIntensity = new QLineEdit(lightWidget);
  lightIntensity->setText("1.0");
  lightIntensity->setValidator(new QDoubleValidator());
  connect(lightIntensity, &QLineEdit::textEdited, this, &PostProcessingOptions::OnLightIntensityChanged);
  lightLayout->addWidget(lightLabel);
  lightLayout->addWidget(lightIntensity);
  layout->addWidget(lightWidget);

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

void PostProcessingOptions::OnMoveSpeedChanged(const QString& value)
{
  LevelEditor* editor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::Rotate* comp = object->GetComponent<Elba::Rotate>();

  if (comp)
  {
    comp->SetMoveSpeed(value.toFloat());
  }
}

void PostProcessingOptions::OnRotateSpeedChanged(const QString& value)
{
  LevelEditor* editor = GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::Rotate* comp = object->GetComponent<Elba::Rotate>();

  if (comp)
  {
    comp->SetRotateSpeed(value.toFloat());
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

