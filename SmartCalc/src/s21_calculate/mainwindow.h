#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qcustomplot.h>

#include <QLabel>
#include <QMainWindow>
#include <QVector>

#include "kredit.h"

extern "C" {
#include "../s21_calculate.h"
#include "../s21_stack.h"
int input_str(char *str, long double *result);
int checkstr(char *str);
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QLabel *actWindow;
  kredit *kreditcal;

private slots:
  void digits_numbers();
  void on_pushButton_dot_clicked();
  void operations();
  void math_operations();
  void trigonometric_operations();
  void on_pushButton_eq_clicked();
  void on_pushButton_ac_clicked();
  void on_pushButton_11_clicked();
  void auto_mul();
  void plot_graph();
  void on_pushButton_cred_clicked();
  void on_pushButton_ac_2_clicked();
};
#endif // MAINWINDOW_H
