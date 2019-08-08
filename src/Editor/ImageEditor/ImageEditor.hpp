#pragma once

#include "Elba/Engine.hpp"

#include "Editor/Framework/Workspace.hpp"

#include "Editor/ImageEditor/ImageWindow/ImageWindow.hpp"

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

  Elba::GlobalKey mResizeCallbackKey;
  void OnResize(const Elba::ResizeEvent& event);
};

} // End of Editor namespace
