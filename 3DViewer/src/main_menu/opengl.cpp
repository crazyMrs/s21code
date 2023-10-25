#include "opengl.h"

OpenGL::OpenGL(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGL::initializeGL() {
  glLoadIdentity();
  initializeOpenGLFunctions();
}
void OpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
void OpenGL::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), backgroundColor.alphaF());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  proj_Type();
  glEnableClientState(GL_VERTEX_ARRAY);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  if (file_open) {
    glVertexPointer(3, GL_DOUBLE, 0, verts.points);
    PointsSettings();
    LinesSettings();
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  update();
}

void OpenGL::LinesSettings() {
  if (!line_Type) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(set_LineSize);
  drawPolys();
  if (!line_Type) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void OpenGL::PointsSettings() {
  if (points_Type == 0) {
    glEnable(GL_POINT_SMOOTH);
    glPointSize((float)set_PointSize);
    glColor3f(vertColor.redF(), vertColor.greenF(), vertColor.blueF());
    glDrawArrays(GL_POINTS, 0, verts.amount_vert);
    glDisable(GL_POINT_SMOOTH);
  } else if (points_Type == 1) {
    glPointSize((float)set_PointSize);
    glColor3f(vertColor.redF(), vertColor.greenF(), vertColor.blueF());
    glDrawArrays(GL_POINTS, 0, verts.amount_vert);
  } else {
    glPointSize(0);
  }
}

void OpenGL::drawPolys() {
  if (poly.p != NULL) {
    glColor3f(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
    glDrawElements(GL_LINES, poly.verts_in_poly * 2, GL_UNSIGNED_INT, poly.p);
  } else {
    qDebug() << "Invalid polygon data!";
  }
}

void OpenGL::size_change(double coef_size) { axis_scale(&verts, coef_size); }

void OpenGL::translate(int axis, double value) {
  axis_moving(&verts, axis, prev_translate_value[axis], value);
  prev_translate_value[axis] = value;
}

void OpenGL::proj_Type() {
  MaxinMaximus();
  if (!projection_Type) {
    glOrtho(-max_in_minmax, max_in_minmax, -max_in_minmax, max_in_minmax,
            max_in_minmax, max_in_minmax);
  } else {
    float fov = 60.0 * M_PI / 180;
    float heapHeight = max_in_minmax / (2 * tan(fov / 2));
    glFrustum(-1, 1, -1, 1, heapHeight * 2, 6 * max_in_minmax);
    glTranslatef(0, 0, -max_in_minmax * 3);
  }
}

void OpenGL::MaxinMaximus() {
  float centerX = abs(verts.MinMax[0]) < abs(verts.MinMax[1])
                      ? abs(verts.MinMax[1])
                      : abs(verts.MinMax[0]);
  float centerY = abs(verts.MinMax[2]) < abs(verts.MinMax[3])
                      ? abs(verts.MinMax[3])
                      : abs(verts.MinMax[2]);
  float centerZ = abs(verts.MinMax[4]) < abs(verts.MinMax[5])
                      ? abs(verts.MinMax[5])
                      : abs(verts.MinMax[4]);
  max_in_minmax = centerX < centerY ? centerY : centerX;
  max_in_minmax = max_in_minmax < centerZ ? centerZ : max_in_minmax;
}

void OpenGL::mouseMoveEvent(QMouseEvent *mouse) {
  xRot += 1 / M_PI * (mouse->pos().y() - mPos.y());
  yRot += 1 / M_PI * (mouse->pos().x() - mPos.x());
  mPos = mouse->pos();
  update();
}

void OpenGL::mousePressEvent(QMouseEvent *mouse) { mPos = mouse->pos(); }

void OpenGL::set_background_color(const QColor &color) {
  QColor clearColor = color; // Создаем копию цвета
  clearColor.setAlpha(
      255); // Устанавливаем альфа-канал на полную непрозрачность
  glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(),
               clearColor.alphaF());
  backgroundColor = color; // Сохраняем цвет фона
  update(); // Запускаем перерисовку OpenGL виджета
}

void OpenGL::set_edge_color(const QColor &color) {
  edgeColor = color;
  update();
}

void OpenGL::set_vert_color(const QColor &color) {
  vertColor = color;
  update();
}
