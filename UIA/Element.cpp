#include "Element.h"
#include <QtCore/QDebug>


Element::Element(IUIAutomationElement* element)
  : area(NULL)
{
  UIAElement = element;
  qDebug() << "Created element " + getName();
}

Element::~Element()
{
  destroyActiveArea();
  UIAElement->Release();
  qDebug() << "Memory for object " + cachedName + " released.";
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

void Element::highlight()
{
  destroyActiveArea();

  RECT rect;
  HRESULT hr = UIAElement->get_CurrentBoundingRectangle(&rect);
  if ( SUCCEEDED(hr) ) {
    area = new ElementArea(rect);
    area->show();
  } else {
    qDebug() << "Cannot get bounding rectangle for " + getName();
  }
}

void Element::destroyActiveArea()
{
  if (area) {
    if ( area->isVisible() )
      area->close();

    delete area;
    area = NULL;
  }
}

QString Element::bstrToQString(BSTR& bstr)
{
  std::wstring str = (LPCWSTR) bstr;
  QString qstr = QString::fromStdWString(str);
  SysFreeString(bstr);
  return qstr;
}
