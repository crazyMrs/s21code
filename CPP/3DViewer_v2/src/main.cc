#include <locale.h>

#include <QApplication>

#include "viewer/viewer_view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_ALL, "C");
  s21::ViewerView w;
  w.setWindowTitle("Viewer v2.0");
  w.show();
  return a.exec();
}
