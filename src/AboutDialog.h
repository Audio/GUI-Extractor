#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtGui/QDialog>


namespace Ui {
  class AboutDialog;
}

class AboutDialog : public QDialog
{
  Q_OBJECT

public:
  AboutDialog(QWidget* parent = 0);
  ~AboutDialog();

private slots:
  void closeButtonClicked();

private:
  Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
