#include <qlineedit.h>

#include "Editor/LevelEditor/PostProcessingOptions/EffectItemWidget.hpp"

namespace Editor
{
EffectItemWidget::EffectItemWidget(QString header, Elba::OpenGLComputeShader* shader, QWidget* parent)
  : QWidget(parent)
  , mLayout(new QVBoxLayout(this))
{
  mLayout->addWidget(new QLabel(header));
}


} // End of Editor namespace
