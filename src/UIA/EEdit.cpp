#include "EEdit.h"


EEdit::EEdit(IUIAutomationElement* element)
  : Element(element)
{
}

QString EEdit::getType()
{
  return "edit";
}
