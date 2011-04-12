#include "EEdit.h"


EEdit::EEdit(IUIAutomationElement* element)
  : Element(element)
{
}

QString EEdit::getType() const
{
  return "edit";
}

XUL::Item* EEdit::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("textbox");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("multiline", "true");
  return item;
}
