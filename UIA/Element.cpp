#include "Element.h"
#include <QtCore/QDebug>


Element::Element(IUIAutomationElement* element)
{
  UIAElement = element;
  qDebug() << "Created element " + getName();
}

Element::~Element()
{
  qDebug() << "Memory for object " + getName() + " released.";
  UIAElement->Release();
}

QString Element::getName()
{
  // TODO cache
  BSTR name;
  HRESULT hr = UIAElement->get_CurrentName(&name);
  return ( SUCCEEDED(hr) ? bstrToQString(name) : "FAILLLL" );
}

QString Element::bstrToQString(const BSTR& bstr)
{
  if (!bstr)             // TODO it can falls on assert
    return "?? WTF ??";

  std::wstring str = (LPCWSTR) bstr;
  QString qstr = QString::fromStdWString(str);
  SysFreeString(bstr);
  return qstr;
}
