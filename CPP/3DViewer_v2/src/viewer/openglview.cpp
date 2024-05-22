#include "openglview.h"

namespace s21 {

Options::Options()
    : projection_type_(0),
      point_shape_(0),
      point_size_(0),
      rib_shape_(0),
      rib_size_(0),
      color_back_(Qt::black),
      color_ribs_(Qt::blue),
      color_verts_(Qt::blue) {}

OpenGLView::OpenGLView(QWidget* parent) : QOpenGLWidget(parent) {
  options_ = new Options();
  settings_ = new QSettings(this);
  controller_ = &ViewerController::Instance();
}

OpenGLView::~OpenGLView() {}

void OpenGLView::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_LINE_SMOOTH); // используется для сглаживания линий
  // glEnable(GL_BLEND); // смешивание цветов не обязательно, думаю

  InitializeParameters();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  ChangeProjection();
}

void OpenGLView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGLView::paintGL() {
  InitializeParameters();
  if (controller_->GetData().amount_vertices_) {
    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ChangeProjection();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glVertexPointer(3, GL_FLOAT, 0, controller_->GetData().vertices_.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    ChangePPoint();
    ChangePRib();
    glDrawElements(GL_LINES, controller_->GetData().amount_polygons_,
                   GL_UNSIGNED_INT, controller_->GetData().polygons_.data());

    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OpenGLView::InitializeParameters() {
  glClearColor(options_->color_back_.redF(), options_->color_back_.greenF(),
               options_->color_back_.blueF(), options_->color_back_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLView::ChangeProjection() {
  const float* highs = controller_->GetData().highs_;
  if (options_->projection_type_) {
    float fov = 45 * M_PI / 180;
    float heapHeight = 1 / (2 * tan(fov / 2));
    glFrustum(highs[0] * 1.5, highs[1] * 1.5, highs[2] * 1.5, highs[3] * 1.5,
              heapHeight, highs[5] * 110);
    glTranslatef(0, 0, -1 * 3);
  } else {
    glOrtho(-highs[0] * 2.5, highs[1] * 2.5, -highs[2] * 2.5, highs[3] * 2.5,
            highs[4] * 8, highs[5] * 8);
  }
}

void OpenGLView::ChangePPoint() {
  glColor3f(options_->color_verts_.redF(), options_->color_verts_.greenF(),
            options_->color_verts_.blueF());
  if (!options_->point_shape_) {
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, controller_->GetData().amount_vertices_);
    glDisable(GL_POINT_SMOOTH);

    glPointSize(options_->point_size_ / 10);
  } else if (options_->point_shape_ == 1) {
    glDrawArrays(GL_POINTS, 0, controller_->GetData().amount_vertices_);

    glPointSize(options_->point_size_ / 10);
  }
}

void OpenGLView::ChangePRib() {
  glColor3f(options_->color_ribs_.redF(), options_->color_ribs_.greenF(),
            options_->color_ribs_.blueF());
  glLineWidth(options_->rib_size_ / 10);
  if (options_->rib_shape_) {
    glLineStipple(1, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

Options* OpenGLView::GetOptions() noexcept { return options_; }

QSettings* OpenGLView::GetSettings() const noexcept { return settings_; }

void OpenGLView::SaveSettings() {
  settings_->setValue("phone_color", options_->color_back_);
  settings_->setValue("verts_color", options_->color_verts_);
  settings_->setValue("ribs_color", options_->color_ribs_);
  settings_->setValue("verts_size", options_->point_size_);
  settings_->setValue("ribs_size", options_->rib_size_);
  settings_->setValue("projection_type", options_->projection_type_);
  settings_->setValue("verts_type", options_->point_shape_);
  settings_->setValue("ribs_type", options_->projection_type_);
}

}  // namespace s21
