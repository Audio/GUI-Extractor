#include "EDataGrid.h"


EDataGrid::EDataGrid(IUIAutomationElement* element)
  : Element(element)
{
}

QString EDataGrid::getType() const
{
  return "data grid";
}
