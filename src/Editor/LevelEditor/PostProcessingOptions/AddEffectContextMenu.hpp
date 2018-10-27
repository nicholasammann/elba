#pragma once

/* post processing effects
// Tier 1
blur
weighted blur
edge detection
glow/bloom
additive noise
rgb to hsv
post processed scratched film effect
tone change
hue change

// Tier 2
Realtime Hatching / Halftoning
image based anti-aliasing
video transitions
motion blur

// Tier 3
Watercolor effect
gpu-based implementation
Connected component labeling
*/

#include "Editor/Framework/Menu.hpp"

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLPostProcess.hpp"
#include "Elba/Graphics/OpenGL/OpenGLModule.hpp"

namespace Editor
{
class PostProcessingOptions;
class EffectItemWidget;

class AddEffectContextMenu : public Framework::Menu
{
public:
  AddEffectContextMenu(Framework::Workspace* workspace, PostProcessingOptions* options);
private:
  PostProcessingOptions* mOptionsPanel;
  Elba::OpenGLModule* mGraphics;
  Elba::OpenGLPostProcess* mPostProcess;

  void AddEffect(std::string shaderName, std::string itemName, EffectItemWidget** resultItem = nullptr, Elba::OpenGLProgram** resultPrg = nullptr);
  
  template <typename T>
  void AddUniform(EffectItemWidget* item, Elba::OpenGLProgram* prg, std::string uniformName, std::string label, T value);

  void AddBlur();
  void AddWeightedBlur();
  void AddMotionBlur();
  void AddEdgeDetection();
  void AddBloom();
  void AddAdditiveNoise();
  void AddRGBtoHSV();
  void AddScratchedFilm();
  void AddToneChangeSepia();
  void AddToneChangeGrayscale();
  void AddToneChangeBlackWhite();
  void AddHueChange();
  void ClearEffects();
};

template<typename T>
inline void AddEffectContextMenu::AddUniform(EffectItemWidget* item, Elba::OpenGLProgram* prg, std::string uniformName, std::string label, T value)
{
  if (std::is_same<int, T>())
  {
    Elba::OpenGLUniformInt uniform(uniformName, value);
    prg->SetUniform(uniform);

    item->AddProperty<int>(label.c_str(), value,
      [prg, uniformName](const QString& changedValue)
      {
        Elba::OpenGLUniformInt uniform(uniformName.c_str(), changedValue.toInt());
        prg->SetUniform(uniform);
      }
    );
  }
  else if (std::is_same<float, T>())
  {
    Elba::OpenGLUniformFloat uniform(uniformName, value);
    prg->SetUniform(uniform);

    item->AddProperty<int>(label.c_str(), value,
      [prg, uniformName](const QString& changedValue)
      {
        Elba::OpenGLUniformFloat uniform(uniformName.c_str(), changedValue.toFloat());
        prg->SetUniform(uniform);
      }
    );
  }
  else
  {
    // WE DON'T SUPPORT THAT TYPE YET
    assert(true);
  }
}
} // End of Editor namespace
