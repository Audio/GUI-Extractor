#include "Client.h"


Client::~Client()
{
  UIA->Release();
  CoUninitialize();
  emit error("UIA instance has been deallocated");
}

void Client::initialize()
{
  CoInitialize(NULL);
  HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**) &UIA);

  if ( FAILED(hr) )
    emit error("Initialization of UIA Failed");
  else
    emit error("UIA instance has been successfuly created");
}

Element* Client::getRootElement()
{
  IUIAutomationElement* root = NULL;
  HRESULT hr = UIA->GetRootElement(&root);
  if ( FAILED(hr) || !root ) {
    emit error("Cannot obtain root element");
    if (root)
      root->Release();

    return NULL;
  }

  return new Element(root);
}

QList<Element*> Client::getImmediateChildren(Element* parent)
{
  QList<Element*> children;

  IUIAutomationTreeWalker* walker = NULL;
  UIA->get_RawViewWalker(&walker);
  if (!walker) {
    emit error("Cannot obtaion viewWallker in getImmediateChildren()");
    return children;
  }

  IUIAutomationElement* element;
  walker->GetFirstChildElement( parent->getUIAElement(), &element );
  if (!element) {
    emit error("Cannot obtaion first child in getImmediateChildren()");
    return children;
  }

  while (element) {
    children.append( new Element(element) );
    IUIAutomationElement* next = NULL;
    walker->GetNextSiblingElement(element, &next);
    element = next;
  }

  walker->Release();

  return children;
}

QList<Element*> Client::topLevelWindows()
{
  QList<Element*> windows;
  Element* root = getRootElement();
  if (root) {
    windows = getImmediateChildren(root);
    delete root;
  }

  return windows;
}
