#include <iostream>

#include <qlabel.h>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Core/Components/CS370/ResizeHandler.hpp"

#include "Editor/ImageEditor/OptionsPanel/OptionsPanel.hpp"
#include "Editor/ImageEditor/ImageEditor.hpp"

namespace Editor
{

OptionsPanel::OptionsPanel(ImageEditor* workspace)
  : Framework::Widget(workspace)
  , mLayout(new QVBoxLayout(this))
{
  Elba::Engine* engine = workspace->GetEngine();
  mCore = engine->GetCoreModule();
  mGraphics = static_cast<Elba::OpenGLModule*>(engine->GetGraphicsModule());

  setWindowTitle("Options");

  mInterpolationCombo = new QComboBox(this);
  mInterpolationCombo->addItem("None");
  mInterpolationCombo->addItem("Nearest Neighbor");
  mInterpolationCombo->addItem("Bilinear");

  // listen for selected item changes
  connect(mInterpolationCombo, 
          QOverload<int>::of(&QComboBox::currentIndexChanged), 
          this,
          &OptionsPanel::OnInterpolationChange);

  // Set current to None
  mInterpolationCombo->setCurrentIndex(0);

  // checkbox for turning on and off histogram equalization
  QWidget* histWidg = new QWidget(this);
  QHBoxLayout* histLayout = new QHBoxLayout(this);
  histWidg->setLayout(histLayout);
  mUseHistogramCheckbox = new QCheckBox(this);
  mUseHistogramCheckbox->setChecked(true);
  QLabel* histLabel = new QLabel("Use Histogram Equalization");
  histLayout->addWidget(histLabel);
  histLayout->addWidget(mUseHistogramCheckbox);
  connect(mUseHistogramCheckbox, &QCheckBox::stateChanged, this, &OptionsPanel::OnUseHistogramChange);

  // Fourier widgets
  QWidget* fourierWidg = new QWidget(this);
  QGridLayout* fourierLayout = new QGridLayout(this);
  fourierWidg->setLayout(fourierLayout);

  QLabel* methodLabel = new QLabel("Fourier Method");
  mFourierMethodCombo = new QComboBox(this);
  mFourierMethodCombo->addItem("None");
  mFourierMethodCombo->addItem("Direct");
  mFourierMethodCombo->addItem("Separable");
  mFourierMethodCombo->addItem("Fast");
  connect(mFourierMethodCombo,
    QOverload<int>::of(&QComboBox::currentIndexChanged),
    this,
    &OptionsPanel::OnFourierMethodChange);
  mFourierMethodCombo->setCurrentIndex(0);

  QLabel* imageLabel = new QLabel("Fourier Image");
  mFourierImageSelectionCombo = new QComboBox(this);
  mFourierImageSelectionCombo->addItem("Original");
  mFourierImageSelectionCombo->addItem("Frequency");
  mFourierImageSelectionCombo->addItem("Transformed");
  connect(mFourierImageSelectionCombo,
    QOverload<int>::of(&QComboBox::currentIndexChanged),
    this,
    &OptionsPanel::OnFourierImageChange);
  mFourierImageSelectionCombo->setCurrentIndex(0);

  fourierLayout->addWidget(methodLabel, 0, 0);
  fourierLayout->addWidget(mFourierMethodCombo, 0, 1);
  fourierLayout->addWidget(imageLabel, 1, 0);
  fourierLayout->addWidget(mFourierImageSelectionCombo, 1, 1);

  // Add widgets to layout
  mLayout->addWidget(mInterpolationCombo);
  mLayout->addWidget(histWidg);
  mLayout->addWidget(fourierWidg);
  
  // Set alignment of our widgets in the layout
  mLayout->setAlignment(Qt::AlignTop);
}

Framework::Widget::DockArea OptionsPanel::GetDefaultDockArea() const
{
  return DockArea::Left;
}

void OptionsPanel::OnInterpolationChange(int index)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetInterpolationMode(static_cast<Elba::ResizeHandler::InterpolationMode>(index));
  }
}

void OptionsPanel::OnUseHistogramChange(int value)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetUseHistogramEqualization(static_cast<bool>(value));
  }
}

void OptionsPanel::OnFourierMethodChange(int index)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetFourierMethod(static_cast<Elba::ResizeHandler::FourierMethod>(index));
  }
}

void OptionsPanel::OnFourierImageChange(int index)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetCurrentImage(static_cast<Elba::ResizeHandler::CurrentImage>(index));
  }
}

Elba::Object* OptionsPanel::GetObject()
{
  Elba::Level* level = mCore->GetGameLevel();

  auto it = level->GetChildren().begin();

  if (it != level->GetChildren().end())
  {
    return it->second.get();
  }
  return nullptr;
}

} // End of Editor namespace

