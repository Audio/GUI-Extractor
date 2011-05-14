#include "EDocument.h"


EDocument::EDocument(IUIAutomationElement* element)
  : Element(element)
{
}

QString EDocument::getType() const
{
  return "document";
}

XUL::Item* EDocument::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("textbox");
  exportXULArea(item, diffLeft, diffTop);
  item->setAttribute("multiline", "true");
  return item;
}
