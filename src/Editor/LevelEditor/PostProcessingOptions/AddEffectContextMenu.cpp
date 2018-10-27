#include "Elba/Engine.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/AddEffectContextMenu.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/EffectItemWidget.hpp"
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
  AddAction<AddEffectContextMenu>("Tone Change: Sepia", &AddEffectContextMenu::AddToneChangeSepia, this, "Changes tone of the color space to Sepia");
  AddAction<AddEffectContextMenu>("Tone Change: Grayscale", &AddEffectContextMenu::AddToneChangeGrayscale, this, "Changes tone of the color space to Grayscale");
  AddAction<AddEffectContextMenu>("Tone Change: Black & White", &AddEffectContextMenu::AddToneChangeBlackWhite, this, "Changes tone of the color space to Black and White");
  AddAction<AddEffectContextMenu>("Hue Change", &AddEffectContextMenu::AddHueChange, this, "Changes dominant hue of the color space using RGB to HSV");
  addSeparator();
  AddAction<AddEffectContextMenu>("Motion Blur", &AddEffectContextMenu::AddMotionBlur, this, "Implements motion blur");
  addSeparator();
  AddAction<AddEffectContextMenu>("Clear Effects", &AddEffectContextMenu::ClearEffects, this, "Removes all post processing effects");

  LevelEditor* editor = mOptionsPanel->GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  mGraphics = static_cast<Elba::OpenGLModule*>(graphics);
  mPostProcess = mGraphics->GetPostProcess();

  setStyleSheet("QMenu::separator { background-color: gray; }");
}

EffectItemWidget* AddEffectContextMenu::AddEffect(std::string shaderName, std::string itemName)
{
  Elba::GlobalKey key = mPostProcess->AddComputeShader(shaderName + ".comp");
  Elba::OpenGLComputeShader* shader = mPostProcess->GetComputeShader(key);
  return mOptionsPanel->AddItem(itemName.c_str(), shader);
}

void AddEffectContextMenu::AddBlur()
{
  AddEffect("blur", "Uniform Blur");
}

void AddEffectContextMenu::AddWeightedBlur()
{
  AddEffect("weightedBlur", "Weighted Blur");
}

void AddEffectContextMenu::AddMotionBlur()
{
  AddEffect("motionBlur", "Motion Blur");
}

void AddEffectContextMenu::AddEdgeDetection()
{
  AddEffect("edgeDetection", "Edge Detection");
}

void AddEffectContextMenu::AddBloom()
{
  AddEffect("bloom", "Bloom");
}

void AddEffectContextMenu::AddAdditiveNoise()
{
  AddEffect("additiveNoise", "Additive Noise");
}

void AddEffectContextMenu::AddRGBtoHSV()
{
  AddEffect("rgbToHsv", "RGB To HSV");
}

void AddEffectContextMenu::AddScratchedFilm()
{
  AddEffect("scratchedFilm", "Scratched Film Effect");
}

void AddEffectContextMenu::AddToneChangeSepia()
{
  AddEffect("toneChangeSepia", "Tone Change: Sepia");
}

void AddEffectContextMenu::AddToneChangeGrayscale()
{
  AddEffect("toneChangeGrayscale", "Tone Change: Grayscale");
}

void AddEffectContextMenu::AddToneChangeBlackWhite()
{
  Elba::GlobalKey key = mPostProcess->AddComputeShader("toneChangeBlackWhite.comp");
  Elba::OpenGLComputeShader* shader = mPostProcess->GetComputeShader(key);
  EffectItemWidget* item = mOptionsPanel->AddItem("Tone Change: Black & White", shader);
  
  Elba::OpenGLProgram* prg = mPostProcess->GetComputeProgram(key);
  Elba::OpenGLUniformFloat uniform("threshold", 0.2f);
  prg->SetUniform(uniform);

  item->AddProperty<float>("Threshold", 0.2f, 
    [prg](const QString& value)
    { 
      Elba::OpenGLUniformFloat uniform("threshold", value.toFloat());
      prg->SetUniform(uniform);
    }
  );
}

void AddEffectContextMenu::AddHueChange()
{
  Elba::GlobalKey key = mPostProcess->AddComputeShader("hueChange.comp");
  Elba::OpenGLComputeShader* shader = mPostProcess->GetComputeShader(key);
  EffectItemWidget* item = mOptionsPanel->AddItem("Hue Change", shader);

  Elba::OpenGLProgram* prg = mPostProcess->GetComputeProgram(key);
  Elba::OpenGLUniformFloat uniform("Hue", 0.0f);
  prg->SetUniform(uniform);

  item->AddProperty<float>("Hue", 0.0f,
    [prg](const QString& value)
  {
    Elba::OpenGLUniformFloat uniform("hue", value.toFloat());
    prg->SetUniform(uniform);
  }
  );
}

void AddEffectContextMenu::ClearEffects()
{
  mPostProcess->RemoveAllComputeShaders();
  mOptionsPanel->GetTree()->clear();
}
} // End of Editor namespace
