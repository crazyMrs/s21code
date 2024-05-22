#include <QApplication>

#include "../controller/controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::ModelCalculator Model;
  s21::CalcController Controller(&Model);
  MainWindow w(nullptr, &Controller);
  w.show();
  return a.exec();
}
