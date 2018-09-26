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

  std::vector<std::function<void(ResizeEvent)
};

} // End of Editor namespace
