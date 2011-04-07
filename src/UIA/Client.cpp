#include "Client.h"
#include "ElementFactory.h"


Client::Client()
  : UIA(NULL)
{
}

Client::~Client()
{
  UIA->Release();
  CoUninitialize();
  emit eventHappened( tr("UI Automation has been disabled.") );
}

void Client::init()
{
  CoInitialize(NULL);
  HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**) &UIA);

  if ( FAILED(hr) )
    emit eventHappened( tr("Initialization of UI Automation has failed."), Log::WARNING );
  else
    emit eventHappened( tr("UI Automation has been initialized.") );
}

Element* Client::getRootElement()
{
  IUIAutomationElement* root = NULL;
  HRESULT hr = UIA->GetRootElement(&root);
  if ( FAILED(hr) || !root ) {
    emit eventHappened( tr("Cannot obtain the Desktop element."), Log::WARNING );
    if (root)
      root->Release();

    return NULL;
  }

  return ElementFactory::getElement(root);
}

QList<Element*> Client::getImmediateChildren(Element* parent)
{
  QList<Element*> children;

  IUIAutomationTreeWalker* walker = NULL;
  UIA->get_RawViewWalker(&walker);
  if (!walker)
    return children;

  IUIAutomationElement* element;
  walker->GetFirstChildElement( parent->getUIAElement(), &element );

  while (element) {
    children.append( ElementFactory::getElement(element) );
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
