#include <iostream>

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

  // Add combo to layout
  mLayout->addWidget(mInterpolationCombo);
  mLayout->setAlignment(Qt::AlignTop);
}

Framework::Widget::DockArea OptionsPanel::GetDefaultDockArea() const
{
  return DockArea::Left;
}

void OptionsPanel::OnInterpolationChange(int index)
{
  Elba::Level* level = mCore->GetGameLevel();

  auto it = level->GetChildren().begin();

  if (it != level->GetChildren().end())
  {
    Elba::ResizeHandler* resizer = it->second->GetComponent<Elba::ResizeHandler>();

    resizer->SetInterpolationMode(static_cast<Elba::ResizeHandler::InterpolationMode>(index));
  }
}

} // End of Editor namespace

