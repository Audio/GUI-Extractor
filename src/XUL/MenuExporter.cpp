#include "MenuExporter.h"
#include "UIA/EMenu.h"


MenuExporter::MenuExporter(EMenuBar* menubar, Element* window, Client* client, QObject* parent)
  : QObject(parent), window(window), client(client), currentItem(NULL)
{
  QList<Element*> tempItems = client->getImmediateChildren(menubar);
  foreach (Element* item, tempItems) {
    EMenuItem* menuItem = (EMenuItem*) item;
    if ( menuItem->supportExpandCollapse() )
      items.append(menuItem);
  }

  timer = new QTimer(this);
  connect(timer, SIGNAL( timeout() ), SLOT( tryAnalyzeMenu() ));

  prepareToLoadNextMenu();
}

void MenuExporter::prepareToLoadNextMenu()
{
  if ( items.isEmpty() ) {
    emit allMenusLoaded();
  } else {
    currentItem = items.takeFirst();
    currentItem->expandMenu();
    failAttempts = 0;
    timer->start(100);
  }
}

void MenuExporter::tryAnalyzeMenu()
{
  EMenu* menu = (EMenu*) client->getTopMenuElement(window);
  if (menu) {
    timer->stop();
    QList<Element*> menuItems = client->getImmediateChildren(menu);
    emit menuLoaded(currentItem, menuItems);
    currentItem->collapseMenu();
    delete currentItem;
    delete menu;
    prepareToLoadNextMenu();
  } else {
    ++failAttempts;

    if (failAttempts >= 10) {
      emit menuNotLoaded(currentItem);
      currentItem->collapseMenu();
      delete currentItem;
      prepareToLoadNextMenu();
    }
  }
}
