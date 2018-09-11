#pragma once

#include "Elba/Engine.hpp"

#include "Editor/Framework/Workspace.hpp"

namespace Editor
{
class LevelWindow;

class LevelEditor : public Framework::Workspace
{
public:
  LevelEditor(Framework::MainWindow* mainWindow);

  bool Initialize() final;
  void Shutdown() final;

  void Update();

  Elba::Engine* GetEngine();

private:
  Elba::Engine* mEngine;

  LevelWindow* mLevelWindow;
};

} // End of Editor namespace
