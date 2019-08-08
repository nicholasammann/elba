#include <iostream>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/GameLogic/CS370/ResizeHandler.hpp"

#include "Editor/ImageEditor/ImageOperationsPanel/ImageOperationsPanel.hpp"
#include "Editor/ImageEditor/ImageEditor.hpp"

namespace Editor
{

ImageOperationsPanel::ImageOperationsPanel(ImageEditor* workspace)
  : Framework::Widget(workspace)
  , mLayout(new QVBoxLayout(this))
  , mImageOpComponent(nullptr)
{
  // cache core and graphics module ptrs
  Elba::Engine* engine = workspace->GetEngine();
  mCore = engine->GetCoreModule();
  mGraphics = static_cast<Elba::OpenGLModule*>(engine->GetGraphicsModule());

  setWindowTitle("Image Operations");

  // create menu widgets
  mNumImageCombo = new QComboBox(this);
  mNumImageCombo->addItem("Single Image Operations");
  mNumImageCombo->addItem("Double Image Operations");
  connect(mNumImageCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ImageOperationsPanel::OnNumImageChange);

  mOneImageOperationCombo = new QComboBox(this);
  mOneImageOperationCombo->addItem("None");
  mOneImageOperationCombo->addItem("Image Negative");
  mOneImageOperationCombo->addItem("Log Transform");
  mOneImageOperationCombo->addItem("Gamma Transform");
  connect(mOneImageOperationCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ImageOperationsPanel::OnOneImageOpChange);

  QDoubleValidator* validator = new QDoubleValidator(this);
  validator->setBottom(0.0);
  validator->setDecimals(4);

  mCWidg = new QWidget(this);
  QHBoxLayout* cLayout = new QHBoxLayout(this);
  QLabel* cLabel = new QLabel("C:");
  mInputC = new QLineEdit("C", this);
  mInputC->setValidator(validator);
  mInputC->setText("1.0");
  connect(mInputC, &QLineEdit::textChanged, this, &ImageOperationsPanel::OnCChanged);
  cLayout->addWidget(cLabel);
  cLayout->addWidget(mInputC);
  mCWidg->setLayout(cLayout);

  mGammaWidg = new QWidget(this);
  QLabel* gammaLabel = new QLabel("Gamma:");
  QHBoxLayout* gammaLayout = new QHBoxLayout(this);
  mInputGamma = new QLineEdit("Gamma", this);
  mInputGamma->setValidator(validator);
  mInputGamma->setText("0.5");
  connect(mInputGamma, &QLineEdit::textChanged, this, &ImageOperationsPanel::OnGammaChanged);
  gammaLayout->addWidget(gammaLabel);
  gammaLayout->addWidget(mInputGamma);
  mGammaWidg->setLayout(gammaLayout);

  mTwoImageOperationCombo = new QComboBox(this);
  mTwoImageOperationCombo->addItem("None");
  mTwoImageOperationCombo->addItem("Addition");
  mTwoImageOperationCombo->addItem("Subtraction");
  mTwoImageOperationCombo->addItem("Product");
  connect(mTwoImageOperationCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ImageOperationsPanel::OnTwoImageOpChange);

  mImageALabel = new QLabel("No Image A Selected");
  mImageBLabel = new QLabel("No Image B Selected");

  mLayout->setAlignment(Qt::AlignTop);
  mLayout->addWidget(mNumImageCombo);
  mLayout->addWidget(mOneImageOperationCombo);
  mLayout->addWidget(mCWidg);
  mLayout->addWidget(mGammaWidg);
  mLayout->addWidget(mTwoImageOperationCombo);
  mLayout->addWidget(mImageALabel);
  mLayout->addWidget(mImageBLabel);

  OnNumImageChange(0);
}

Framework::Widget::DockArea ImageOperationsPanel::GetDefaultDockArea() const
{
  return DockArea::Left;
}

void ImageOperationsPanel::SetImageALabel(std::string label)
{
  mImageALabel->setText(label.c_str());
}

void ImageOperationsPanel::SetImageBLabel(std::string label)
{
  mImageBLabel->setText(label.c_str());
}

void ImageOperationsPanel::OnNumImageChange(int index)
{
  switch (index)
  {
    case SingleImage:
    {
      mOneImageOperationCombo->show();
      mCWidg->show();
      mGammaWidg->show();
      mTwoImageOperationCombo->hide();
      mImageALabel->hide();
      mImageBLabel->hide();
      break;
    }

    case DoubleImage:
    {
      mTwoImageOperationCombo->show();
      mImageALabel->show();
      mImageBLabel->show();
      mOneImageOperationCombo->hide();
      mCWidg->hide();
      mGammaWidg->hide();
      break;
    }
  }
}

void ImageOperationsPanel::OnOneImageOpChange(int index)
{
  switch (static_cast<OneImageOps>(index))
  {
    case OneImageOps::None:
    {
      GetImageOpComponent()->SetImageNegative(0);
      GetImageOpComponent()->SetLogTransform(0);
      GetImageOpComponent()->SetGammaTransform(0);
      break;
    }

    case OneImageOps::ImageNegative:
    {
      GetImageOpComponent()->SetImageNegative(1);
      GetImageOpComponent()->SetLogTransform(0);
      GetImageOpComponent()->SetGammaTransform(0);
      break;
    }

    case OneImageOps::LogTransform:
    {
      GetImageOpComponent()->SetImageNegative(0);
      GetImageOpComponent()->SetLogTransform(1);
      GetImageOpComponent()->SetGammaTransform(0);
      break;
    }

    case OneImageOps::GammaTransform:
    {
      GetImageOpComponent()->SetImageNegative(0);
      GetImageOpComponent()->SetLogTransform(0);
      GetImageOpComponent()->SetGammaTransform(1);
      break;
    }
  }
}

void ImageOperationsPanel::OnCChanged(const QString& text)
{
  GetImageOpComponent()->SetCValue(text.toFloat());
}

void ImageOperationsPanel::OnGammaChanged(const QString& text)
{
  GetImageOpComponent()->SetGammaValue(text.toFloat());
}

void ImageOperationsPanel::OnTwoImageOpChange(int index)
{
  switch (static_cast<TwoImageOps>(index))
  {
    case TwoImageOps::None:
    {
      GetImageOpComponent()->DoNone();
      break;
    }

    case TwoImageOps::Addition:
    {
      GetImageOpComponent()->DoAddition();
      break;
    }

    case TwoImageOps::Subtraction:
    {
      GetImageOpComponent()->DoSubtraction();
      break;
    }

    case TwoImageOps::Product:
    {
      GetImageOpComponent()->DoProduct();
      break;
    }
  }
}

Elba::ImageOperationHandler* ImageOperationsPanel::GetImageOpComponent()
{
  if (!mImageOpComponent)
  {
    ImageEditor* workspace = GetWorkspace<ImageEditor>();
    Elba::Engine* engine = workspace->GetEngine();
    Elba::CoreModule* core = engine->GetCoreModule();
    Elba::Level* level = core->GetGameLevel();
    Elba::ObjectMap const& children = level->GetChildren();
    auto first = children.begin();
    mImageOpComponent = first->second->GetComponent<Elba::ImageOperationHandler>();
  }
  return mImageOpComponent;
}

} // End of Editor namespace

