#include <iostream>

#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"
#include "Elba/Core/Components/CS370/ResizeHandler.hpp"

#include "Editor/ImageEditor/ImageOperationsPanel/ImageOperationsPanel.hpp"
#include "Editor/ImageEditor/ImageEditor.hpp"

namespace Editor
{

ImageOperationsPanel::ImageOperationsPanel(ImageEditor* workspace)
  : Framework::Widget(workspace)
  , mLayout(new QVBoxLayout(this))
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

  QDoubleValidator* validator = new QDoubleValidator(this);
  validator->setBottom(0.0);
  validator->setDecimals(4);

  mInputC = new QLineEdit("C", this);
  mInputC->setValidator(validator);
  mInputC->setText("0.5");

  mInputGamma = new QLineEdit("Gamma", this);
  mInputGamma->setValidator(validator);
  mInputGamma->setText("0.5");

  mTwoImageOperationCombo = new QComboBox(this);
  mTwoImageOperationCombo->addItem("None");
  mTwoImageOperationCombo->addItem("Addition");
  mTwoImageOperationCombo->addItem("Subtraction");
  mTwoImageOperationCombo->addItem("Product");

  mLayout->setAlignment(Qt::AlignTop);
  mLayout->addWidget(mNumImageCombo);
  mLayout->addWidget(mOneImageOperationCombo);
  mLayout->addWidget(mTwoImageOperationCombo);
  mLayout->addWidget(mInputC);
  mLayout->addWidget(mInputGamma);

  mOneImageOperationCombo->hide();
  mTwoImageOperationCombo->hide();
  mInputC->hide();
  mInputGamma->hide();
}

Framework::Widget::DockArea ImageOperationsPanel::GetDefaultDockArea() const
{
  return DockArea::Left;
}

void ImageOperationsPanel::OnNumImageChange(int index)
{
  switch (index)
  {
    case SingleImage:
    {
      mOneImageOperationCombo->show();
      mInputC->show();
      mInputGamma->show();
      mTwoImageOperationCombo->hide();
      break;
    }

    case DoubleImage:
    {
      mTwoImageOperationCombo->show();
      mOneImageOperationCombo->hide();
      mInputC->hide();
      mInputGamma->hide();
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
      break;
    }

    case OneImageOps::ImageNegative:
    {
      break;
    }

    case OneImageOps::LogTransform:
    {
      break;
    }

    case OneImageOps::GammaTransform:
    {
      break;
    }
  }
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
  if (mImageOpComponent)
  {
    return mImageOpComponent;
  }

  ImageEditor* workspace = GetWorkspace<ImageEditor>();
  Elba::Engine* engine = workspace->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  Elba::ObjectMap const& children = level->GetChildren();
  auto first = children.begin();
  return first->second->GetComponent<Elba::ImageOperationHandler>();
}

} // End of Editor namespace

