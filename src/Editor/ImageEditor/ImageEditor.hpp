#pragma once

#include "Elba/Engine.hpp"

#include "Editor/Framework/Workspace.hpp"

namespace Editor
{
class ImageWindow;

class ImageEditor : public Framework::Workspace
{
public:
  ImageEditor(Framework::MainWindow* mainWindow);

  bool Initialize() final;
  void Shutdown() final;

  void Update();

  Elba::Engine* GetEngine();

private:
  Elba::Engine* mEngine;

  ImageWindow* mImageWindow;
};

} // End of Editor namespace
