#include <iostream>

#include <qlabel.h>
#include <qlineedit.h>

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
  mUseHistogramCheckbox->setChecked(false);
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
  /////////////////////////////////


  // Assignment 4
  QWidget* noiseWidget = new QWidget();
  QGridLayout* noiseLayout = new QGridLayout(noiseWidget);
  noiseWidget->setLayout(noiseLayout);
  
  int row = 0;

  // Guassian Noise ////
  // checkbox for apply gaussian noise
  QLabel* gaussianNoise = new QLabel("Gaussian Noise");
  QPushButton* useGaussianNoise = new QPushButton("Apply");
  connect(useGaussianNoise,
    &QPushButton::pressed,
    this,
    &OptionsPanel::OnUseGaussianNoise);
  noiseLayout->addWidget(gaussianNoise, row, 0);
  noiseLayout->addWidget(useGaussianNoise, row++, 1);
  // mean
  QLabel* gaussianMeanX = new QLabel("Gaussian Mean X");
  QLineEdit* gaussianMeanXIn = new QLineEdit();
  connect(gaussianMeanXIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnGaussianMeanX);
  noiseLayout->addWidget(gaussianMeanX, row, 0);
  noiseLayout->addWidget(gaussianMeanXIn, row++, 1);
  QLabel* gaussianMeanY = new QLabel("Gaussian Mean Y");
  QLineEdit* gaussianMeanYIn = new QLineEdit();
  connect(gaussianMeanYIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnGaussianMeanY);
  noiseLayout->addWidget(gaussianMeanY, row, 0);
  noiseLayout->addWidget(gaussianMeanYIn, row++, 1);
  // variance
  QLabel* gaussianVarianceX = new QLabel("Gaussian Variance X");
  QLineEdit* gaussianVarianceXIn = new QLineEdit();
  connect(gaussianVarianceXIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnGaussianVarianceX);
  noiseLayout->addWidget(gaussianVarianceX, row, 0);
  noiseLayout->addWidget(gaussianVarianceXIn, row++, 1);
  QLabel* gaussianVarianceY = new QLabel("Gaussian Variance Y");
  QLineEdit* gaussianVarianceYIn = new QLineEdit();
  connect(gaussianVarianceYIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnGaussianVarianceX);
  noiseLayout->addWidget(gaussianVarianceY, row, 0);
  noiseLayout->addWidget(gaussianVarianceYIn, row++, 1);

  // S&P Noise ////
  // checkbox for apply S&P noise
  QLabel* saltPepperNoise = new QLabel("S&P Noise");
  QPushButton* useSaltPepperNoise = new QPushButton("Apply");
  useSaltPepperNoise->setChecked(false);
  connect(useSaltPepperNoise,
    &QPushButton::pressed,
    this,
    &OptionsPanel::OnUseSaltPepperNoise);
  noiseLayout->addWidget(saltPepperNoise, row, 0);
  noiseLayout->addWidget(useSaltPepperNoise, row++, 1);
  // P(a)
  QLabel* spPa = new QLabel("S&P: P(a)");
  QLineEdit* spPaIn = new QLineEdit();
  connect(spPaIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnPa);
  noiseLayout->addWidget(spPa, row, 0);
  noiseLayout->addWidget(spPaIn, row++, 1);
  // P(b)
  QLabel* spPb = new QLabel("S&P: P(b)");
  QLineEdit* spPbIn = new QLineEdit();
  connect(spPbIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnPb);
  noiseLayout->addWidget(spPb, row, 0);
  noiseLayout->addWidget(spPbIn, row++, 1);

  // Noise Reduction / Remove ////
  // Checkbox for apply noise reduction / removal (3x3 median filter)
  QLabel* noiseReduction = new QLabel("Noise Reduction");
  QPushButton* useNoiseReduction = new QPushButton("Apply");
  useNoiseReduction->setChecked(false);
  connect(useNoiseReduction,
    &QPushButton::pressed,
    this,
    &OptionsPanel::OnUseNoiseReduction);
  noiseLayout->addWidget(noiseReduction, row, 0);
  noiseLayout->addWidget(useNoiseReduction, row++, 1);

  // Local Noise Reduction ////
  // Checkbox for apply local noise reduction
  QLabel* localNoiseReduction = new QLabel("Local Noise Reduction");
  QPushButton* uselocalNoiseReduction = new QPushButton("Apply");
  uselocalNoiseReduction->setChecked(false);
  connect(uselocalNoiseReduction,
    &QPushButton::pressed,
    this,
    &OptionsPanel::OnUseLocalNoiseReduction);
  noiseLayout->addWidget(localNoiseReduction, row, 0);
  noiseLayout->addWidget(uselocalNoiseReduction, row++, 1);
  // guessed standard deviation
  QLabel* deviation = new QLabel("Standard Deviation");
  QLineEdit* deviationIn = new QLineEdit();
  connect(deviationIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnDeviation);
  noiseLayout->addWidget(deviation, row, 0);
  noiseLayout->addWidget(deviationIn, row++, 1);

  // Adaptive Median Noise Reduction
  // Checkbox for apply median noise reduction
  QLabel* adaptiveNoiseReduction = new QLabel("Adaptive Noise Reduction");
  QPushButton* useAdaptiveNoiseReduction = new QPushButton("Apply");
  useAdaptiveNoiseReduction->setChecked(false);
  connect(useAdaptiveNoiseReduction,
    &QPushButton::pressed,
    this,
    &OptionsPanel::OnUseAdaptiveNoiseReduction);
  noiseLayout->addWidget(adaptiveNoiseReduction, row, 0);
  noiseLayout->addWidget(useAdaptiveNoiseReduction, row++, 1);
  // value of S.max
  QLabel* sMax = new QLabel("S Max");
  QLineEdit* sMaxIn = new QLineEdit();
  connect(sMaxIn,
    &QLineEdit::textChanged,
    this,
    &OptionsPanel::OnSMax);
  noiseLayout->addWidget(sMax, row, 0);
  noiseLayout->addWidget(sMaxIn, row++, 1);

  // Add widgets to layout
  mLayout->addWidget(mInterpolationCombo);
  mLayout->addWidget(histWidg);
  mLayout->addWidget(fourierWidg);
  mLayout->addWidget(noiseWidget);
  
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

void OptionsPanel::OnUseGaussianNoise()
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->ApplyGaussianNoise();
  }
}

void OptionsPanel::OnGaussianMean(const QString& text)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetGaussianMean(text.toFloat());
  }
}

void OptionsPanel::OnGaussianVariance(const QString& text)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetGaussianVariance(text.toFloat());
  }
}

void OptionsPanel::OnUseSaltPepperNoise()
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->ApplySaltPepperNoise();
  }
}

void OptionsPanel::OnPa(const QString& text)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetPa(text.toFloat());
  }
}

void OptionsPanel::OnPb(const QString& text)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetPb(text.toFloat());
  }
}

void OptionsPanel::OnUseNoiseReduction()
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->ApplyNoiseReduction();
  }
}

void OptionsPanel::OnUseLocalNoiseReduction()
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->ApplyLocalNoiseReduction();
  }
}

void OptionsPanel::OnDeviation(const QString& text)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetDeviation(text.toFloat());
  }
}

void OptionsPanel::OnUseAdaptiveNoiseReduction()
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->ApplyAdaptiveNoiseReduction();
  }
}

void OptionsPanel::OnSMax(const QString& text)
{
  Elba::Object* obj = GetObject();

  if (obj)
  {
    Elba::ResizeHandler* resizer = obj->GetComponent<Elba::ResizeHandler>();
    resizer->SetSMax(text.toFloat());
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

