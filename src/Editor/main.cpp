#include <qapplication.h>
#include <qstylefactory.h>

#include "Editor/Framework/MainWindow.hpp"
#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/ImageEditor/ImageEditor.hpp"

#define EDITOR_MODE

using namespace Editor;

// Change the app style
void SetDarkTheme(QApplication& app);

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  SetDarkTheme(app);

  Framework::MainWindow* mainWindow = new Editor::Framework::MainWindow();
  LevelEditor* editor = mainWindow->LoadWorkspace<LevelEditor>(mainWindow);
  //ImageEditor* editor = mainWindow->LoadWorkspace<ImageEditor>(mainWindow);

  if (!editor->Initialize())
  {
    return 1;
  }

  mainWindow->resize(1280, 800);
  mainWindow->show();

  app.setActiveWindow(mainWindow);

  return app.exec();
}

// Change the app style
void SetDarkTheme(QApplication& app)
{
  app.setStyle(QStyleFactory::create("Fusion"));

  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
  darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::BrightText, Qt::red);
  darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

  darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::HighlightedText, Qt::black);

  app.setPalette(darkPalette);
  app.setStyleSheet("QToolTip { color: #101010; background-color: #2a82da; border: 1px solid white; }");
}

