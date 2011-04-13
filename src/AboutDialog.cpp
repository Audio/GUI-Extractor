#include "AboutDialog.h"
#include "ui_aboutdialog.h"


AboutDialog::AboutDialog(QWidget* parent)
  : QDialog(parent), ui(new Ui::AboutDialog)
{
  ui->setupUi(this);
  connect(ui->buttonClose, SIGNAL( clicked() ), SLOT( closeButtonClicked() ));
  ui->labelLink->setOpenExternalLinks(true);
}

AboutDialog::~AboutDialog()
{
  delete ui;
}

void AboutDialog::closeButtonClicked()
{
  close();
}
