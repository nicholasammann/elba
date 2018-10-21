#pragma once

#include <qcolordialog.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qlineedit.h>

#include "Editor/Framework/Widget.hpp"

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/CS370/ImageOperationHandler.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Editor
{

class ImageEditor;

class ImageOperationsPanel : public Framework::Widget
{
public:
  ImageOperationsPanel(ImageEditor* workspace);

  virtual DockArea GetDefaultDockArea() const;

private:
  Elba::CoreModule* mCore;
  Elba::OpenGLModule* mGraphics;

  QVBoxLayout* mLayout;

  QComboBox* mNumImageCombo;
  void OnNumImageChange(int index);
  enum
  {
    SingleImage,
    DoubleImage
  };

  QComboBox* mOneImageOperationCombo;
  enum class OneImageOps
  {
    None,
    ImageNegative,
    LogTransform,
    GammaTransform
  };
  void OnOneImageOpChange(int index);

  QLineEdit* mInputC;
  QLineEdit* mInputGamma;

  QComboBox* mTwoImageOperationCombo;
  enum class TwoImageOps
  {
    None,
    Addition,
    Subtraction,
    Product
  };
  void OnTwoImageOpChange(int index);

  // helper
  Elba::ImageOperationHandler* GetImageOpComponent();
  Elba::ImageOperationHandler* mImageOpComponent;
};

} // End of Editor namespace

