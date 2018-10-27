#include <qlineedit.h>

#include "Editor/LevelEditor/PostProcessingOptions/EffectItemWidget.hpp"

namespace Editor
{
EffectItemWidget::EffectItemWidget(QString header, Elba::OpenGLComputeShader* shader, QWidget* parent)
  : QWidget(parent)
  , mLayout(new QVBoxLayout(this))
{
  //mLayout->addWidget(new QLabel(header));
}

Elba::OpenGLComputeShader* EffectItemWidget::GetShader()
{
  return mShader;
}


} // End of Editor namespace
