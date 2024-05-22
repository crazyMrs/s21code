#ifndef KREDIT_H
#define KREDIT_H

#include <QDialog>

namespace Ui {
class kredit;
}

class kredit : public QDialog {
  Q_OBJECT

public:
  explicit kredit(QWidget *parent = nullptr);
  ~kredit();

private slots:
  void on_pushButton_clicked();

private:
  Ui::kredit *ui;
};

#endif // KREDIT_H
