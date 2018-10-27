#include <functional>

#include <qwidget.h>
#include <qvalidator.h>
#include <qlayout.h>
#include <qlabel.h>

#include "Elba/Graphics/OpenGL/Pipeline/OpenGLComputeShader.hpp"

namespace Editor
{
class EffectItemWidget : public QWidget
{
public:
  EffectItemWidget(QString header, Elba::OpenGLComputeShader* shader, QWidget* parent);

  template <typename T>
  QWidget* AddProperty(QString name, T value, std::function<void(const QString&)> fn);

private:
  Elba::OpenGLComputeShader* mShader;
  QVBoxLayout* mLayout;
};

template<typename T>
inline QWidget* EffectItemWidget::AddProperty(QString name, T value, std::function<void(const QString&)> fn)
{
  QWidget* result = new QWidget(this);
  QHBoxLayout* layout = new QHBoxLayout(result);
  result->setLayout(layout);

  QLineEdit* valueLine = new QLineEdit(this);
  valueLine->setText(value);

  connect(valueLine, &QLineEdit::textChanged, this, fn);

  QValidator* validator = nullptr;

  if (std::is_same<T, int>)
  {
    validator = new QIntValidator(this);
  }
  else if (std::is_same<T, float>() || std::is_same<T, double>())
  {
    validator = new QDoubleValidator(this);
  }
  else
  {
    throw "WE CAN'T HANDLE THAT TYPE OF VALUE - ONLY INTS, FLOATS, AND DOUBLES PLEASE";
  }

  valueLine->setValidator(validator);

  layout->addWidget(new QLabel(name));
  layout->addWidget(valueLine);

  mLayout->addWidget(result);

  return result;
}
} // End of Editor namespace
