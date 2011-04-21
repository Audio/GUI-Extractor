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

ElementArea Element::getArea(bool& valid) const
{
  RECT rect;
  HRESULT hr = UIAElement->get_CurrentBoundingRectangle(&rect);
  valid = SUCCEEDED(hr);
  return ElementArea(rect);
}

bool Element::isOffScreen() const
{
  BOOL offScreen;
  HRESULT hr = UIAElement->get_CurrentIsOffscreen(&offScreen);
  return SUCCEEDED(hr) && offScreen;
}

QString Element::getCachedName() const
{
  return cachedName;
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

QString Element::getLocalizedType()
{
  BSTR type;
  HRESULT hr = UIAElement->get_CurrentLocalizedControlType(&type);
  if ( SUCCEEDED(hr) && type )
    return bstrToQString(type);
  else
    return QObject::tr("Unknown");
}

QString Element::getOrientation() const
{
  OrientationType ori;
  HRESULT hr = UIAElement->get_CurrentOrientation(&ori);

  if ( SUCCEEDED(hr) && ori == OrientationType_Horizontal)
    return "horizontal";
  else if ( SUCCEEDED(hr) && ori == OrientationType_Vertical)
    return "vertical";
  else
    return "unknown";
}

IUIAutomationElement* Element::getUIAElement() const
{
  return UIAElement;
}

XUL::Item* Element::exportXUL(int diffLeft, int diffTop) const
{
  XUL::Item* item = new XUL::Item("stack");
  exportXULArea(item, diffLeft, diffTop, true);
  return item;
}

void Element::exportXULArea(XUL::Item* item, int diffLeft, int diffTop, bool noDiff) const
{
  bool valid;
  ElementArea a = getArea(valid);
  if (valid) {
    int top = (noDiff) ? 0 :  a.getTop() - diffTop;
    int left = (noDiff) ? 0 : a.getLeft() - diffLeft;
    item->setAttribute("top", QString::number(top) );
    item->setAttribute("left", QString::number(left) );
    item->setAttribute("width", QString::number( a.getWidth() ));
    item->setAttribute("height", QString::number( a.getHeight() ));
  }
}

QString Element::bstrToQString(BSTR& bstr)
{
  std::wstring str = (LPCWSTR) bstr;
  QString qstr = QString::fromStdWString(str);
  SysFreeString(bstr);
  return qstr;
}
