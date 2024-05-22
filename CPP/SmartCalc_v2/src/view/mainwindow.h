#ifndef CPP3_SMARTCALC_V2_SRC_VIEW_MAINWINDOW_H
#define CPP3_SMARTCALC_V2_SRC_VIEW_MAINWINDOW_H

#include <qcustomplot.h>

#include <QMainWindow>

#include "../controller/controller.h"
#include "kredit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr,
             s21::CalcController *Controller = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::CalcController *calc_controller_;
  QVector<double> x, y;
  bool isOperator(char ch);
  QString GetLastNumber(QString current_text);
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
  void plotFunction(QCustomPlot *customPlot, double xMin, double xMax,
                    double yMin, double yMax);
  void on_pushButton_cred_clicked();
  void on_pushButton_ac_2_clicked();
};
#endif  // CPP3_SMARTCALC_V2_SRC_VIEW_MAINWINDOW_H
