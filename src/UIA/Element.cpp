#include "Element.h"
#include <QtCore/QDebug>


Element::Element(IUIAutomationElement* element)
{
  UIAElement = element;
  qDebug() << "Created element " + getName();
}

Element::~Element()
{
  UIAElement->Release();
  qDebug() << "Memory for object " + cachedName + " released.";
}

const ElementArea* Element::getArea() const
{
  RECT rect;
  HRESULT hr = UIAElement->get_CurrentBoundingRectangle(&rect);
  return SUCCEEDED(hr) ? new ElementArea(rect) : NULL;
}

QString Element::getName()
{
  if ( cachedName.isEmpty() ) {
    BSTR name;
    HRESULT hr = UIAElement->get_CurrentName(&name);
    if ( SUCCEEDED(hr) && name )
      cachedName = bstrToQString(name);
  }

  return cachedName;
}

IUIAutomationElement* Element::getUIAElement() const
{
  return UIAElement;
}

XUL::Item* Element::exportXUL() const
{
  XUL::Item* item = new XUL::Item("spacer");
  exportXULArea(item);
  return item;
}

void Element::exportXULArea(XUL::Item* item) const
{
  const ElementArea* a = getArea();
  item->setAttribute("top", QString::number( a->getTop() ));
  item->setAttribute("left", QString::number( a->getLeft() ));
  item->setAttribute("width", QString::number( a->getWidth() ));
  item->setAttribute("height", QString::number( a->getHeight() ));
}

QString Element::bstrToQString(BSTR& bstr)
{
  std::wstring str = (LPCWSTR) bstr;
  QString qstr = QString::fromStdWString(str);
  SysFreeString(bstr);
  return qstr;
}
