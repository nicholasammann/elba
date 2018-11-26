#define GLM_ENABLE_EXPERIMENTAL

#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Elba/Engine.hpp"
#include "Elba/Core/CoreModule.hpp"
#include "Elba/Core/Components/CS370/VideoTransitions.hpp"

#include "Editor/LevelEditor/LevelEditor.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/AddEffectContextMenu.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/EffectItemWidget.hpp"
#include "Editor/LevelEditor/PostProcessingOptions/PostProcessingOptions.hpp"


namespace Editor
{
AddEffectContextMenu::AddEffectContextMenu(Framework::Workspace* workspace, PostProcessingOptions* options)
  : Framework::Menu("Add Effect", workspace)
  , mOptionsPanel(options)
  , mTimeElapsed(0.0f)
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
  AddAction<AddEffectContextMenu>("Video Transitions", &AddEffectContextMenu::AddVideoTransitions, this, "Adds video transitions shader.");
  addSeparator();
  AddAction<AddEffectContextMenu>("Watercolor", &AddEffectContextMenu::AddWatercolor, this, "Watercolor effect.");
  addSeparator();
  AddAction<AddEffectContextMenu>("Clear Effects", &AddEffectContextMenu::ClearEffects, this, "Removes all post processing effects");

  LevelEditor* editor = mOptionsPanel->GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::GraphicsModule* graphics = engine->GetGraphicsModule();
  mGraphics = static_cast<Elba::OpenGLModule*>(graphics);
  mPostProcess = mGraphics->GetPostProcess();

  setStyleSheet("QMenu::separator { background-color: gray; }");
}

void AddEffectContextMenu::AddEffect(std::string shaderName, std::string itemName, EffectItemWidget** resultItem, Elba::OpenGLProgram** resultPrg)
{
  Elba::GlobalKey key = mPostProcess->AddComputeShader(shaderName + ".comp");
  Elba::OpenGLComputeShader* shader = mPostProcess->GetComputeShader(key);
  EffectItemWidget* item = mOptionsPanel->AddItem(itemName.c_str(), shader);

  if (resultPrg)
  {
    *resultPrg = mPostProcess->GetComputeProgram(key);
  }

  if (resultItem)
  {
    *resultItem = item;
  }
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
  EffectItemWidget* item;
  Elba::OpenGLProgram* prg;
  AddEffect("motionBlur", "Motion Blur", &item, &prg);

  // find transform component and register for changed event
  LevelEditor* editor = mOptionsPanel->GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::Transform* transform = object->GetComponent<Elba::Transform>();
  transform->RegisterForTransformChanged(Elba::GlobalKey(), 
    [this, prg](const Elba::PhysicsTransform* tr)
    {
      this->OnTransformChanged(tr, prg);
    }
  );
}

void AddEffectContextMenu::AddAntiAliasing()
{
  AddEffect("antiAliasing", "Anti-Aliasing");
}

void AddEffectContextMenu::AddVideoTransitions()
{
  Elba::OpenGLProgram* prg;
  EffectItemWidget* item;
  AddEffect("videoTransitions", "Video Transitions", &item, &prg);

  LevelEditor* editor = mOptionsPanel->GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::VideoTransitions* video = object->GetComponent<Elba::VideoTransitions>();
  video->SetProgram(prg);
}

void AddEffectContextMenu::AddWatercolor()
{
  AddEffect("watercolor", "Watercolor");
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
  EffectItemWidget* item;
  Elba::OpenGLProgram* prg;
  AddEffect("scratchedFilm", "Scratched Film Effect", &item, &prg);
  AddUniform<int>(item, prg, "lineWidth", "Line Width", 3);
  AddUniform<int>(item, prg, "patternWidth", "Pattern Width", 431);
  AddUniform<int>(item, prg, "minPatternWidth", "Minimum Pattern Width", 233);
  AddUniform<float>(item, prg, "timeSince", "Time Since", 1.0f);
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
  EffectItemWidget* item;
  Elba::OpenGLProgram* prg;
  AddEffect("toneChangeBlackWhite", "Tone Change: Black & White", &item, &prg);
  AddUniform<float>(item, prg, "threshold", "Threshold", 0.2f);
}

void AddEffectContextMenu::AddHueChange()
{
  EffectItemWidget* item;
  Elba::OpenGLProgram* prg;
  AddEffect("hueChange", "Hue Change", &item, &prg);
  AddUniform<float>(item, prg, "hue", "Hue", 0.0f);
}

void AddEffectContextMenu::ClearEffects()
{
  LevelEditor* editor = mOptionsPanel->GetWorkspace<LevelEditor>();
  Elba::Engine* engine = editor->GetEngine();
  Elba::CoreModule* core = engine->GetCoreModule();
  Elba::Level* level = core->GetGameLevel();
  auto& childMap = level->GetChildren();
  auto firstObj = childMap.begin();
  Elba::Object* object = firstObj->second.get();
  Elba::VideoTransitions* video = object->GetComponent<Elba::VideoTransitions>();
  video->SetProgram(nullptr);

  mPostProcess->RemoveAllComputeShaders();
  mOptionsPanel->GetTree()->clear();
}

void AddEffectContextMenu::OnTransformChanged(const Elba::PhysicsTransform* transform, Elba::OpenGLProgram* prg)
{
  glm::mat4 scale = glm::scale(transform->GetWorldScale());
  glm::mat4 rotate = glm::toMat4(transform->GetWorldRotation());
  glm::mat4 translate = glm::translate(transform->GetWorldTranslation());

  glm::mat4 modelMat = translate * rotate * scale;

  Elba::OpenGLUniformMat4 uniform("transform", modelMat);
  prg->SetUniform(uniform);
}
} // End of Editor namespace
