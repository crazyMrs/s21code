#include "mainwindow.h"

#include <QFileDialog>
#include <QLabel>

#include "QMessageBox"
#include "QPainter"
#include "QTimer"
#include "ui_mainwindow.h"

void MainWindow::return_to_original_settings() {
  ui->horizontalSlider_rotate_1->setValue(0);
  ui->horizontalSlider_rotate_2->setValue(0);
  ui->horizontalSlider_rotate_3->setValue(0);
  ui->openGLWidget->last_rotateX = 0;
  ui->openGLWidget->last_rotateY = 0;
  ui->openGLWidget->last_rotateZ = 0;

  ui->horizontalSlider_translate_1->setValue(0);
  ui->horizontalSlider_translate_2->setValue(0);
  ui->horizontalSlider_translate_3->setValue(0);

  ui->horizontalSlider_rotate_size->setValue(100);
  ui->openGLWidget->coef_size = 100;

  ui->openGLWidget->edgeColor = Qt::white;
  ui->openGLWidget->vertColor = Qt::white;
  ui->openGLWidget->backgroundColor = Qt::black;

  ui->comboBox->setCurrentIndex(0);
  ui->openGLWidget->projection_Type = 0;
  ui->comboBox_2->setCurrentIndex(0);
  ui->openGLWidget->points_Type = 0;
  ui->comboBox_3->setCurrentIndex(0);
  ui->openGLWidget->line_Type = 1;

  ui->horizontalSlider_LineSize_2->setValue(0);
  ui->horizontalSlider_PointSize->setValue(0);
  ui->openGLWidget->set_LineSize = 0;
  ui->openGLWidget->set_PointSize = 0;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  settings = new QSettings(QDir::homePath() + "/save_config/settings.conf",
                           QSettings::IniFormat);

  // background color
  connect(ui->pushButton_black, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::black); });
  connect(ui->pushButton_red, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::red); });
  connect(ui->pushButton_blue, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::blue); });
  connect(ui->pushButton_yellow, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::yellow); });
  connect(ui->pushButton_pink, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::magenta); });
  connect(ui->pushButton_white, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::white); });
  connect(ui->pushButton_green, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::green); });
  connect(ui->pushButton_lblue, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_background_color(Qt::cyan); });

  // vert color
  connect(ui->pushButton_black_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::black); });
  connect(ui->pushButton_red_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::red); });
  connect(ui->pushButton_blue_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::blue); });
  connect(ui->pushButton_yellow_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::yellow); });
  connect(ui->pushButton_pink_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::magenta); });
  connect(ui->pushButton_white_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::white); });
  connect(ui->pushButton_green_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::green); });
  connect(ui->pushButton_lblue_2, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_vert_color(Qt::cyan); });

  // edges color
  connect(ui->pushButton_black_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::black); });
  connect(ui->pushButton_red_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::red); });
  connect(ui->pushButton_blue_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::blue); });
  connect(ui->pushButton_yellow_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::yellow); });
  connect(ui->pushButton_pink_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::magenta); });
  connect(ui->pushButton_white_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::white); });
  connect(ui->pushButton_green_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::green); });
  connect(ui->pushButton_lblue_3, &QPushButton::clicked, this,
          [this]() { ui->openGLWidget->set_edge_color(Qt::cyan); });
}

MainWindow::~MainWindow() {
  saveSettings();
  free_mem();
  delete settings;
  delete ui;
}

void MainWindow::saveSettings() {
  settings->setValue("settings_on", 1);
  settings->setValue("projection_Type", ui->openGLWidget->projection_Type);

  points_TypeSettings = ui->openGLWidget->points_Type;
  settings->setValue("points_TypeSettings", points_TypeSettings);
  settings->setValue("set_PointSize", ui->openGLWidget->set_PointSize);

  lines_TypeSettings = ui->openGLWidget->line_Type;
  settings->setValue("lines_TypeSettings", lines_TypeSettings);
  settings->setValue("set_LineSize", ui->openGLWidget->set_LineSize);

  settings->setValue("edgeColor",
                     QColor(ui->openGLWidget->edgeColor)); //цвет линий
  settings->setValue("vertColor", QColor(ui->openGLWidget->vertColor)); //точек
  settings->setValue("backgroundColor",
                     QColor(ui->openGLWidget->backgroundColor)); //стены
}

void MainWindow::loadSettings() {
  if (settings->value("settings_on").toInt()) {
    points_TypeSettings = settings->value("points_TypeSettings").toInt();
    if (points_TypeSettings == 0) {
      ui->openGLWidget->points_Type = 0;
      ui->comboBox_2->setCurrentIndex(ui->openGLWidget->points_Type);
    } else if (points_TypeSettings == 1) {
      ui->openGLWidget->points_Type = 1;
      ui->comboBox_2->setCurrentIndex(ui->openGLWidget->points_Type);
    } else {
      ui->openGLWidget->points_Type = 2;
      ui->comboBox_2->setCurrentIndex(ui->openGLWidget->points_Type);
    }
    ui->openGLWidget->set_PointSize = settings->value("set_PointSize").toInt();
    ui->horizontalSlider_PointSize->setValue(ui->openGLWidget->set_PointSize);

    lines_TypeSettings = settings->value("lines_TypeSettings").toInt();

    if (lines_TypeSettings == 0) {
      ui->openGLWidget->line_Type = 0;
    } else if (lines_TypeSettings) {
      ui->openGLWidget->line_Type = 1;
    }
    ui->comboBox_3->setCurrentIndex(ui->openGLWidget->line_Type);
    ui->openGLWidget->set_LineSize = settings->value("set_LineSize").toInt();
    ui->horizontalSlider_LineSize_2->setValue(ui->openGLWidget->set_LineSize);
    ui->openGLWidget->projection_Type =
        settings->value("projection_Type").toInt();
    ui->comboBox->setCurrentIndex(ui->openGLWidget->projection_Type);

    ui->openGLWidget->edgeColor = settings->value("edgeColor").toString();

    ui->openGLWidget->vertColor = settings->value("vertColor").toString();

    ui->openGLWidget->backgroundColor =
        settings->value("backgroundColor").toString();
  }
}

void MainWindow::free_mem() {
  if (ui->openGLWidget->poly.p != NULL &&
      ui->openGLWidget->verts.points != NULL) {
    free(ui->openGLWidget->verts.points);
    free(ui->openGLWidget->poly.p);
  }
}

void MainWindow::on_horizontalSlider_translate_1_valueChanged(int value) {
  ui->label_translate_1->setNum((double)value / 10.);
  ui->openGLWidget->translate(X_AXIS, (double)value / 10.);
}

void MainWindow::on_horizontalSlider_translate_2_valueChanged(int value) {
  ui->label_translate_2->setNum((double)value / 10.);
  ui->openGLWidget->translate(Y_AXIS, (double)value / 10.);
}

void MainWindow::on_horizontalSlider_translate_3_valueChanged(int value) {
  ui->label_translate_3->setNum((double)value / 10.);
  ui->openGLWidget->translate(Z_AXIS, (double)value / 10.);
}

void MainWindow::on_pushButton_clicked() {
  return_to_original_settings();
  QString rootPath = QDir::rootPath();
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Открыть файл"), rootPath, tr("Файлы OBJ (*.obj)"));
  ui->label_file_name->setText(fileName);

  if (!fileName.isEmpty()) {
    QByteArray ba = fileName.toLocal8Bit();
    ui->openGLWidget->c_filename = ba.data();

    int status =
        read_obj_file(ui->openGLWidget->c_filename, &ui->openGLWidget->verts,
                      &ui->openGLWidget->poly);

    if (status == OK) {
      QString output1, output2;
      output1 = QString("%1").arg(ui->openGLWidget->verts.amount_vert);
      output2 = QString("%1").arg(ui->openGLWidget->poly.amount_p);
      ui->label_vert->setText(output1);
      ui->label_pol->setText(output2);
      ui->openGLWidget->file_open = 1;
    } else {
      ui->label_vert->setText("Ошибка чтения файла.\n");
      ui->label_pol->setText("Ошибка чтения файла.\n");
    }
  }
  ui->openGLWidget->MaxinMaximus();
  ui->openGLWidget->file_open = 1;
}

void MainWindow::on_screenshot_clicked() {
  QPixmap screenshot = ui->openGLWidget->grab();
  QString filePath = QFileDialog::getSaveFileName(
      this, "Save Screenshot", "", "ui->openGLWidget->objs (*.bmp *.jpeg)");
  if (!filePath.isEmpty()) {
    screenshot.save(filePath);
  }
}

void MainWindow::on_horizontalSlider_rotate_1_valueChanged(int value) {
  ui->label_rotate_1->setNum((double)value);
  int change = value;
  axis_turn_oX(&ui->openGLWidget->verts,
               value - ui->openGLWidget->last_rotateX);
  ui->openGLWidget->last_rotateX = change;
  update();
}

void MainWindow::on_horizontalSlider_rotate_2_valueChanged(int value) {
  ui->label_rotate_2->setNum((double)value);
  double change = value;
  axis_turn_oY(&ui->openGLWidget->verts,
               value - ui->openGLWidget->last_rotateY);
  ui->openGLWidget->last_rotateY = change;
  update();
}

void MainWindow::on_horizontalSlider_rotate_3_valueChanged(int value) {
  ui->label_rotate_3->setNum((double)value);
  int change = value;
  axis_turn_oZ(&ui->openGLWidget->verts,
               value - ui->openGLWidget->last_rotateZ);
  ui->openGLWidget->last_rotateZ = change;
  update();
}

void MainWindow::on_horizontalSlider_rotate_size_valueChanged(int value) {
  double val = (double)value / ui->openGLWidget->coef_size;
  ui->openGLWidget->size_change(val);
  ui->openGLWidget->coef_size = (double)value;
}

void MainWindow::on_comboBox_2_activated(int index) {
  if (index == 0) {
    ui->openGLWidget->points_Type = 0;
  } else if (index == 1) {
    ui->openGLWidget->points_Type = 1;
  } else {
    ui->openGLWidget->points_Type = 2;
  }
}

void MainWindow::on_comboBox_activated(int index) {
  if (index == 0) {
    ui->openGLWidget->projection_Type = 0;
  } else if (index == 1) {
    ui->openGLWidget->projection_Type = 1;
  }
}

void MainWindow::on_horizontalSlider_PointSize_valueChanged(int value) {
  ui->openGLWidget->set_PointSize = value;
}

void MainWindow::on_horizontalSlider_LineSize_2_valueChanged(int value) {
  ui->openGLWidget->set_LineSize = value;
}

void MainWindow::on_comboBox_3_activated(int index) {
  if (index == 1) {
    ui->openGLWidget->line_Type = 0;
  } else if (index == 0) {
    ui->openGLWidget->line_Type = 1;
  }
}

void MainWindow::on_pushButton_gif_clicked() {
  timer = new QTimer(this);
  filePat = QFileDialog::getSaveFileName(this, tr("Сохрнить Gif"), "/",
                                         tr("Файлы (*.gif)"));
  if (filePat.isEmpty()) {
    QMessageBox::warning(this, tr("Ошибка"), tr("Файл не был сохранен."));
  } else {
    ui->pushButton_gif->setEnabled(false);
    gif_frame = new QGifImage;
    gif_frame->setDefaultDelay(10);
    timer->setInterval(100);
    timecount = 1;
    timer->start();
    connect(timer, &QTimer::timeout, this, &MainWindow::gif_button_text);
    connect(timer, SIGNAL(timeout()), this, SLOT(createGif()));
  }
}

void MainWindow::createGif() {
  if (gif_frame && timer) {
    QImage img = ui->openGLWidget->grabFramebuffer();
    QSize img_size(640, 480);
    QImage scaled_img = img.scaled(img_size);
    gif_frame->addFrame(scaled_img);
    int MaxFrames = 50;
    if (timecount == MaxFrames) {
      timer->stop();
      ui->pushButton_gif->setText("GIF");
      gif_frame->save(filePat);
      QMessageBox::information(0, "/", "Gif успешно сохранен.");
      delete gif_frame;
      gif_frame = nullptr;
      ui->pushButton_gif->setEnabled(true);
    }
    timecount++;
  }
}

void MainWindow::gif_button_text() {
  ui->pushButton_gif->setText(QString::number(timecount / 10) + " сек");
}

void MainWindow::on_pushButton_save_clicked() { saveSettings(); }

void MainWindow::on_pushButton_update_clicked() {
  loadSettings();
  update();
}
