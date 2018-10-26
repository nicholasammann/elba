#include "Elba/Engine.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/AddEffectContextMenu.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/PostProcessingOptions.hpp"

namespace Editor
{
AddEffectContextMenu::AddEffectContextMenu(Framework::Workspace* workspace, PostProcessingOptions* options)
  : Framework::Menu("Add Effect", workspace)
  , mOptionsPanel(options)
{
  AddAction<AddEffectContextMenu>("Blur", &AddEffectContextMenu::AddBlur, this, "Uniform blurring / averaging operation");
  AddAction<AddEffectContextMenu>("Weighted Blur", &AddEffectContextMenu::AddWeightedBlur, this, "Blur based on anisotropic kernel");
  AddAction<AddEffectContextMenu>("Edge Detection", &AddEffectContextMenu::AddEdgeDetection, this, "Sobel operator to highlight edges");
  AddAction<AddEffectContextMenu>("Bloom", &AddEffectContextMenu::AddBloom, this, "Applies glow based on edge information");
  AddAction<AddEffectContextMenu>("Additive Noise", &AddEffectContextMenu::AddAdditiveNoise, this, "Additive Gaussian noise to simulate aging or malfunction");
  AddAction<AddEffectContextMenu>("RGB to HSV", &AddEffectContextMenu::AddRGBtoHSV, this, "Changes rendered scene from RGB to HSV, then back to RGB");
  AddAction<AddEffectContextMenu>("Scratched Film Effect", &AddEffectContextMenu::AddScratchedFilm, this, "Adds a pattern of scratches on film");
  AddAction<AddEffectContextMenu>("Tone Change", &AddEffectContextMenu::AddToneChange, this, "Changes tone of the color space");
  AddAction<AddEffectContextMenu>("Hue Change", &AddEffectContextMenu::AddHueChange, this, "Changes dominant hue of the color space using RGB to HSV");

  LevelEditor* editor = mOptionsPanel->GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  Elba::OpenGLModule* glModule = static_cast<Elba::OpenGLModule*>(graphics);
  mPostProcess = glModule->GetPostProcess();
}

void AddEffectContextMenu::AddBlur()
{
  Elba::GlobalKey key = mPostProcess->AddComputeShader("blur.comp");
  //Elba::OpenGLProgram* prg = mPostProcess->GetComputeProgram(key);
}

void AddEffectContextMenu::AddWeightedBlur()
{
  mPostProcess->AddComputeShader("weightedBlur.comp");
}

void AddEffectContextMenu::AddEdgeDetection()
{
  mPostProcess->AddComputeShader("edgeDetection.comp");
}

void AddEffectContextMenu::AddBloom()
{
  mPostProcess->AddComputeShader("bloom.comp");
}

void AddEffectContextMenu::AddAdditiveNoise()
{
  mPostProcess->AddComputeShader("additiveNoise.comp");
}

void AddEffectContextMenu::AddRGBtoHSV()
{
  mPostProcess->AddComputeShader("rgbToHsv.comp");
}

void AddEffectContextMenu::AddScratchedFilm()
{
  mPostProcess->AddComputeShader("scratchedFilm.comp");
}

void AddEffectContextMenu::AddToneChange()
{
  mPostProcess->AddComputeShader("toneChange.comp");
}

void AddEffectContextMenu::AddHueChange()
{
  mPostProcess->AddComputeShader("hueChange.comp");
}
} // End of Editor namespace
