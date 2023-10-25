#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGifImage/src/gifimage/qgifimage.h>

#include <QColorDialog>
#include <QLabel>
#include <QMainWindow>
#include <QSettings>

extern "C" {
#include "../transformation.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

private:
  int points_TypeSettings;
  int lines_TypeSettings;
  void return_to_original_settings();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void on_horizontalSlider_translate_1_valueChanged(int value);

  void on_horizontalSlider_translate_2_valueChanged(int value);

  void on_horizontalSlider_translate_3_valueChanged(int value);

  void on_pushButton_clicked();

  void on_screenshot_clicked();

  void on_horizontalSlider_rotate_1_valueChanged(int value);

  void on_horizontalSlider_rotate_2_valueChanged(int value);

  void on_horizontalSlider_rotate_3_valueChanged(int value);

  void on_horizontalSlider_rotate_size_valueChanged(int value);

  void on_comboBox_2_activated(int index);

  void on_comboBox_activated(int index);

  void on_horizontalSlider_PointSize_valueChanged(int value);

  void on_horizontalSlider_LineSize_2_valueChanged(int value);

  void on_comboBox_3_activated(int index);

  void on_pushButton_gif_clicked();
  void createGif();
  void gif_button_text();

  void saveSettings();
  void loadSettings();
  void free_mem();

  void on_pushButton_save_clicked();

  void on_pushButton_update_clicked();

private:
  Ui::MainWindow *ui;
  QSettings *settings;
  QGifImage *gif_frame;
  QTimer *timer;
  QString filePat;
  int timecount = 0;
};
#endif // MAINWINDOW_H
