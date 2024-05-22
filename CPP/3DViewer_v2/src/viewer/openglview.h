#ifndef CPP4_S21_VIEWER_V20_SRC_VIEWER_OPENGLVIEW_H_
#define CPP4_S21_VIEWER_V20_SRC_VIEWER_OPENGLVIEW_H_

#define GL_SILENCE_DEPRECATION

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QSlider>
#include <QTimer>
#include <QWidget>

#include "../third_party/QtGifImage/include/gifimage/qgifimage.h"
#include "viewer_controller.h"

namespace s21 {

typedef struct Options {
  Options();
  ~Options() = default;

  int projection_type_, point_shape_, point_size_, rib_shape_, rib_size_;
  QColor color_ribs_;
  QColor color_verts_;
  QColor color_back_;
} Options;

class OpenGLView : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

 public:
  OpenGLView(QWidget* parent = nullptr);
  ~OpenGLView();

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void ClearCharacters();
  void SaveSettings();

  // Getters
  Options* GetOptions() noexcept;
  QSettings* GetSettings() const noexcept;
  // Setters
  void SetColor(const int& type, const QColor& color);

  void ChangePRib();
  void ChangePPoint();
  void ChangeProjection();

 private:
  void InitializeParameters();
  Options* options_;
  QSettings* settings_;
  ViewerController* controller_;
};

}  // namespace s21

#endif  // CPP4_S21_VIEWER_V20_SRC_VIEWER_OPENGLVIEW_H_
