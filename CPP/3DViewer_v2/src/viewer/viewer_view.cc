#include "viewer_view.h"

#include <QThread>

#include "../ui/ui_viewer_view.h"
#include "viewer_controller.h"

namespace s21 {

ViewerView::ViewerView(QWidget* parent)
    : model_(new ViewerModel()), QWidget(parent), ui_(new Ui::ViewerView) {
  model_->AttachObserver(static_cast<Observer*>(this));
  ui_->setupUi(this);

  ViewerController::Instance().SetModel(model_);
  widget_ = new OpenGLView(this);
  widget_->setGeometry(QRect(530, 20, 725, 710));

  ConnectButtons();
  ConnectSliders();
  ConnectBox();
}

ViewerView::~ViewerView() { delete ui_; }

void ViewerView::ResetSettings() {
  ui_->slider_ChangeSize->setSliderPosition(100);
  ui_->label_Scale->setText(QString::number(100));

  ui_->slider_RotateX->setSliderPosition(0);
  ui_->slider_RotateY->setSliderPosition(0);
  ui_->slider_RotateZ->setSliderPosition(0);

  ui_->label_RotateX->setText(QString::number(0));
  ui_->label_RotateY->setText(QString::number(0));
  ui_->label_RotateZ->setText(QString::number(0));

  ui_->slider_TranslateX->setSliderPosition(0);
  ui_->slider_TranslateY->setSliderPosition(0);
  ui_->slider_TranslateZ->setSliderPosition(0);

  ui_->label_TranslateX->setText(QString::number(0));
  ui_->label_TranslateY->setText(QString::number(0));
  ui_->label_TranslateZ->setText(QString::number(0));
}

void ViewerView::ConnectSliders() {
  connect(ui_->slider_ChangeSize, &QSlider::valueChanged, this,
          [this](int value) { ChangeSize(value); });

  connect(ui_->slider_TranslateX, &QSlider::valueChanged, this,
          [this](int value) { ChangeTranslation(value, xAxis); });
  connect(ui_->slider_TranslateY, &QSlider::valueChanged, this,
          [this](int value) { ChangeTranslation(value, yAxis); });
  connect(ui_->slider_TranslateZ, &QSlider::valueChanged, this,
          [this](int value) { ChangeTranslation(value, zAxis); });

  connect(ui_->slider_RotateX, &QSlider::valueChanged, this,
          [this](int value) { ChangeRotate(value, xAxis); });
  connect(ui_->slider_RotateY, &QSlider::valueChanged, this,
          [this](int value) { ChangeRotate(value, yAxis); });
  connect(ui_->slider_RotateZ, &QSlider::valueChanged, this,
          [this](int value) { ChangeRotate(value, zAxis); });

  connect(ui_->slider_PointSize, &QSlider::valueChanged, this,
          [this](int value) {
            widget_->GetOptions()->point_size_ = value;
            widget_->update();
          });
  connect(ui_->slider_LineSize, &QSlider::valueChanged, this,
          [this](int value) {
            widget_->GetOptions()->rib_size_ = value;
            widget_->update();
          });
}

void ViewerView::ConnectButtons() {
  connect(ui_->Button_File, SIGNAL(clicked()), this, SLOT(ClickedFile()));

  connect(ui_->button_ColorPhone, &QPushButton::clicked, this, [this]() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) widget_->GetOptions()->color_back_ = color;
    widget_->update();
  });
  connect(ui_->button_ColorRibs, &QPushButton::clicked, this, [this]() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) widget_->GetOptions()->color_ribs_ = color;
    widget_->update();
  });
  connect(ui_->button_ColorVerts, &QPushButton::clicked, this, [this]() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) widget_->GetOptions()->color_verts_ = color;
    widget_->update();
  });

  connect(ui_->button_Screenshot, &QPushButton::clicked, this,
          [this]() { SaveImage(); });
  connect(ui_->button_Gif, &QPushButton::clicked, this,
          [this]() { SaveGif(); });

  connect(ui_->button_save, &QPushButton::clicked, this,
          [this]() { widget_->SaveSettings(); });
}

void ViewerView::ConnectBox() {
  connect(ui_->comboBox_Points, &QComboBox::activated, this, [this](int index) {
    widget_->GetOptions()->point_shape_ = index;
    widget_->update();
  });
  connect(ui_->comboBox_Proj, &QComboBox::activated, this, [this](int index) {
    widget_->GetOptions()->projection_type_ = index;
    widget_->update();
  });
  connect(ui_->comboBox_Ribs, &QComboBox::activated, this, [this](int index) {
    widget_->GetOptions()->rib_shape_ = index;
    widget_->update();
  });
}

void ViewerView::SaveImage() {
  QString path =
      QFileDialog::getSaveFileName(this, "Выберите файл", "", "*.bmp *.jpeg");
  if (!path.isEmpty()) {
    widget_->grab().save(path);
  } else
    QMessageBox::information(this, "Не найден", "Файл не сохранен");
}

void ViewerView::ClickedFile() {
  QString path =
      QFileDialog::getOpenFileName(this, "Выберите файл", "", "*.obj");
  ViewerController& controller = ViewerController::Instance();
  if (!path.isEmpty()) try {
      controller.TranslateResult(path.toStdString());
      ui_->label_Filename->setText(QFileInfo(path).fileName());
      ui_->label_Verts->setText(
          QString::number(controller.GetData().amount_vertices_));
      ui_->label_Ribs->setText(
          QString::number(controller.GetData().amount_polygons_ / 2));
      ResetSettings();
    } catch (const S21ViewException& ex) {
      QMessageBox::critical(this, "Error", ex.what());
    }
}

// Rotates
void ViewerView::ChangeSize(int value) {
  // Если файл не открыт то не меняем ничего и ничего не вызываем
  try {
    ViewerController::Instance().ChangeScale(value);
  } catch (const S21ViewException& ex) {
    QMessageBox::critical(this, "Error", ex.what());
  }
  ui_->label_Scale->setText(QString::number(value));
}

void ViewerView::ChangeTranslation(int value, Axis axis) {
  // Если файл не открыт то не меняем ничего и ничего не вызываем
  try {
    ViewerController::Instance().MoveCoordinate(axis, value);
  } catch (const S21ViewException& ex) {
    QMessageBox::critical(this, "Error", ex.what());
  }

  switch (axis) {
    case xAxis:
      ui_->label_TranslateX->setText(QString::number(value));
      break;
    case yAxis:
      ui_->label_TranslateY->setText(QString::number(value));
      break;
    default:
      ui_->label_TranslateZ->setText(QString::number(value));
      break;
  }
}

void ViewerView::ChangeRotate(int value, Axis axis) {
  // Если файл не открыт то не меняем ничего и ничего не вызываем
  try {
    ViewerController::Instance().RotateCoordinate(axis, value);
  } catch (const S21ViewException& ex) {
    QMessageBox::critical(this, "Error", ex.what());
  }

  switch (axis) {
    case xAxis:
      ui_->label_RotateX->setText(QString::number(value));
      break;
    case yAxis:
      ui_->label_RotateY->setText(QString::number(value));
      break;
    default:
      ui_->label_RotateZ->setText(QString::number(value));
      break;
  }
}

void ViewerView::OnUpdate() { widget_->update(); }

void ViewerView::on_button_update_clicked() {
  const QSettings* settings = widget_->GetSettings();

  ui_->slider_PointSize->setValue(settings->value("verts_size", 0).toInt());
  widget_->GetOptions()->point_size_ = settings->value("verts_size", 0).toInt();
  ui_->slider_LineSize->setValue(settings->value("ribs_size", 0).toInt());
  widget_->GetOptions()->rib_size_ = settings->value("ribs_size", 0).toInt();

  ui_->comboBox_Proj->setCurrentIndex(
      settings->value("projection_type", 0).toInt());
  widget_->GetOptions()->projection_type_ =
      settings->value("projection_type", 0).toInt();

  ui_->comboBox_Points->setCurrentIndex(
      settings->value("verts_type", 0).toInt());
  widget_->GetOptions()->point_shape_ =
      settings->value("verts_type", 0).toInt();

  ui_->comboBox_Ribs->setCurrentIndex(settings->value("ribs_type", 0).toInt());
  widget_->GetOptions()->rib_shape_ = settings->value("ribs_type", 0).toInt();

  widget_->GetOptions()->color_back_ =
      settings->value("phone_color", 0).value<QColor>();
  widget_->GetOptions()->color_ribs_ =
      settings->value("ribs_color", 0).value<QColor>();
  widget_->GetOptions()->color_verts_ =
      settings->value("verts_color", 0).value<QColor>();

  widget_->update();
  update();
}

void ViewerView::SaveGif() {
  gif_path =
      QFileDialog::getSaveFileName(this, " Сохранение gif-файла", "", "*.gif");
  if (gif_path.isEmpty())
    QMessageBox::critical(this, "Error", "Не удалось сохранить файл.");
  else {
    ui_->button_Gif->setEnabled(false);
    timer_ = new QTimer(this);
    gif_image_ = new QGifImage();
    gif_image_->setDefaultDelay(10);

    connect(timer_, &QTimer::timeout, this, [=]() { CreateGif(); });
    timer_->start(100);
    qDebug() << frame_count_;
  }
}

void ViewerView::CreateGif() {
  QImage new_image = widget_->grabFramebuffer();
  QImage image_scaled = new_image.scaled({640, 480});
  gif_image_->addFrame(image_scaled);
  if (frame_count_ == 49) {
    timer_->stop();
    gif_image_->save(gif_path);
    QMessageBox::information(this, "/", "Gif успешно сохранен.");
    delete gif_image_;
    gif_image_ = nullptr;
    frame_count_ = -1;
    ui_->button_Gif->setEnabled(true);
  }
  ++frame_count_;
}

}  // namespace s21
