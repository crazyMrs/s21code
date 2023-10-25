#ifndef DEPOZIT_H
#define DEPOZIT_H

#include <QDialog>

namespace Ui {
class depozit;
}

class depozit : public QDialog {
  Q_OBJECT

public:
  explicit depozit(QWidget *parent = nullptr);
  ~depozit();

private:
  Ui::depozit *ui;
};

#endif // DEPOZIT_H
