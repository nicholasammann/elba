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

  EffectItemWidget* AddEffect(std::string shaderName, std::string itemName);

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
} // End of Editor namespace
