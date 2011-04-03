#include "ETable.h"


ETable::ETable(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETable::getType() const
{
  return "table";
}
