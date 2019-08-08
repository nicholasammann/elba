#include "Elba/Core/Component.hpp"
#include "Elba/Graphics/OpenGL/Pipeline/OpenGLProgram.hpp"
#include "Elba/Graphics/OpenGL/OpenGLTexture.hpp"

namespace Elba
{
class VideoTransitions : public Component
{
public:
  VideoTransitions(Object* parent);
  void Initialize() final;
  void Update(double dt) final;
  void SetProgram(OpenGLProgram* program);

  void TriggerTransitionToRealTime();
  void TriggerTransitionToStaticImage();
  void SetMode(int mode);

private:
  OpenGLProgram* mProgram;
  float mTransitionAmount;
  float mTargetTransitionAmount;
  int mTransitionMode;
  OpenGLTexture* mStaticImage;
};
} // End of Elba namespace
