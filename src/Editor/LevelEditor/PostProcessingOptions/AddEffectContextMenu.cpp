#include "Elba/Engine.hpp"

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
  addSeparator();
  AddAction<AddEffectContextMenu>("Random Tier 2", &AddEffectContextMenu::AddHueChange, this, "");
  addSeparator();
  AddAction<AddEffectContextMenu>("Clear Effects", &AddEffectContextMenu::ClearEffects, this, "Removes all post processing effects");

  LevelEditor* editor = mOptionsPanel->GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  mGraphics = static_cast<Elba::OpenGLModule*>(graphics);
  mPostProcess = mGraphics->GetPostProcess();

  setStyleSheet("QMenu::separator { background-color: gray; }");
}

void AddEffectContextMenu::AddBlur()
{
  Elba::GlobalKey key = mPostProcess->AddComputeShader("blur.comp");
  mOptionsPanel->AddItem("Blur");
}

void AddEffectContextMenu::AddWeightedBlur()
{
  mPostProcess->AddComputeShader("weightedBlur.comp");
  mOptionsPanel->AddItem("Weighted Blur");
}

void AddEffectContextMenu::AddEdgeDetection()
{
  mPostProcess->AddComputeShader("edgeDetection.comp");
  mOptionsPanel->AddItem("Edge Detection");
}

void AddEffectContextMenu::AddBloom()
{
  mPostProcess->AddComputeShader("bloom.comp");
  mOptionsPanel->AddItem("Bloom");
}

void AddEffectContextMenu::AddAdditiveNoise()
{
  mPostProcess->AddComputeShader("additiveNoise.comp");
  mOptionsPanel->AddItem("Additive Noise");
}

void AddEffectContextMenu::AddRGBtoHSV()
{
  mPostProcess->AddComputeShader("rgbToHsv.comp");
  mOptionsPanel->AddItem("RGB To HSV");
}

void AddEffectContextMenu::AddScratchedFilm()
{
  mPostProcess->AddComputeShader("scratchedFilm.comp");
  mOptionsPanel->AddItem("Scratched Film Effect");
}

void AddEffectContextMenu::AddToneChange()
{
  mPostProcess->AddComputeShader("toneChange.comp");
  mOptionsPanel->AddItem("Tone Change");
}

void AddEffectContextMenu::AddHueChange()
{
  mPostProcess->AddComputeShader("hueChange.comp");
  mOptionsPanel->AddItem("Hue Change");
}

void AddEffectContextMenu::ClearEffects()
{
  mPostProcess->RemoveAllComputeShaders();
  mOptionsPanel->GetTree()->clear();
}
} // End of Editor namespace
