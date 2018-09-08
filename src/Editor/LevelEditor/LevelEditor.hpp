#pragma once

#include "Elba/Engine.hpp"

#include "Editor/Framework/Workspace.hpp"

namespace Editor
{

class LevelEditor : public Framework::Workspace
{
public:
  LevelEditor(Framework::MainWindow* mainWindow);

  bool Initialize() final;
  void Shutdown() final;

  void Update();

private:
  Elba::Engine* mEngine;

};

} // End of Editor namespace
