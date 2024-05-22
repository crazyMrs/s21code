#ifndef CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_VIEW_H
#define CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_VIEW_H

#include <QWidget>

#include "openglview.h"
#include "viewer_model.h"

namespace Ui {
class ViewerView;
}

namespace s21 {

class ViewerView : public QWidget, public Observer {
  Q_OBJECT

 public:
  explicit ViewerView(QWidget* parent = nullptr);
  ~ViewerView();

  void OnUpdate() override;

 private slots:
  void ClickedFile();
  void SaveImage();
  void ChangeSize(int value);
  void ChangeTranslation(int value, Axis axis);
  void ChangeRotate(int value, Axis axis);
  void SaveGif();
  void CreateGif();

  void on_button_update_clicked();

 private:
  void ConnectButtons();
  void ConnectSliders();
  void ConnectBox();
  void ResetSettings();

  QTimer* timer_ = nullptr;
  QString gif_path = "";
  QGifImage* gif_image_ = nullptr;
  int frame_count_ = 0;

  ViewerModel* model_;
  OpenGLView* widget_;
  Ui::ViewerView* ui_;
};

}  // namespace s21

#endif  // CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_VIEW_H
