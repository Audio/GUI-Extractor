#include "ESlider.h"


ESlider::ESlider(IUIAutomationElement* element)
  : Element(element)
{
}

QString ESlider::getType()
{
  return "slider";
}
