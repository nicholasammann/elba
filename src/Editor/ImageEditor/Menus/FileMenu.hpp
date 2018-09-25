#pragma once

#include "Editor/Framework/Menu.hpp"

namespace Editor
{

class FileMenu : public Framework::Menu
{
public:
  FileMenu(Framework::Workspace* workspace);

private:
  void LoadTexture();

};

} // End of Editor namespace

