#include "depozit.h"

#include "ui_depozit.h"

depozit::depozit(QWidget *parent) : QDialog(parent), ui(new Ui::depozit) {
  ui->setupUi(this);

  // Создаем градиентный фон
  QLinearGradient gradient(0, 0, 0, height());
  gradient.setColorAt(0, QColor(255, 127, 80)); // Начальный цвет
  gradient.setColorAt(1, QColor(186, 85, 211)); // Конечный цвет

  // Устанавливаем градиентный фон в качестве фона MainWindow
  QPalette palette;
  palette.setBrush(QPalette::Window, QBrush(gradient));
  setPalette(palette);
}

depozit::~depozit() { delete ui; }
