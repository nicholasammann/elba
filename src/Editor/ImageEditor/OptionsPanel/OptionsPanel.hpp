#pragma once

#include <qcolordialog.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qcheckbox.h>

#include "Editor/Framework/Widget.hpp"

#include "Elba/Core/CoreModule.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Editor
{

class ImageEditor;

class OptionsPanel : public Framework::Widget
{
public:
  OptionsPanel(ImageEditor* workspace);

  virtual DockArea GetDefaultDockArea() const;

private:
  QVBoxLayout* mLayout;
  QComboBox* mInterpolationCombo;
  QCheckBox* mUseHistogramCheckbox;
  QComboBox* mFourierMethodCombo;
  QComboBox* mFourierImageSelectionCombo;

  Elba::CoreModule* mCore;
  Elba::OpenGLModule* mGraphics;

  void OnInterpolationChange(int index);
  void OnUseHistogramChange(int value);
  void OnFourierMethodChange(int index);
  void OnFourierImageChange(int index);

  Elba::Object* GetObject();
};

} // End of Editor namespace

