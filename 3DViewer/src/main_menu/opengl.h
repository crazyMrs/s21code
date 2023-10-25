#ifndef OPENGL_H
#define OPENGL_H

#include <QColor>
#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <algorithm>

#include "mainwindow.h"

class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT;

public:
  OpenGL(QWidget *parent = nullptr);
  vertex verts;
  polygon poly;
  double coef_size = 50.;

  int projection_Type = 0;
  double max_in_minmax = 0;
  void size_change(double coef_size);
  char *c_filename;
  int file_open = 0;
  QColor edgeColor = Qt::white;
  QColor vertColor = Qt::white;
  double prev_translate_value[3] = {0, 0, 0};
  void translate(int axis, double value);
  void proj_Type(); //тип проекции(центральная, параллельная)
  void MaxinMaximus(); //поиск самого максимального значения для проекций
  int last_rotateX;
  int last_rotateY;
  int last_rotateZ;
  int set_PointSize; //размер точек
  int points_Type;   // тип точек
  int set_LineSize;  //размер линии
  int line_Type;
  QColor backgroundColor = Qt::black;
  void set_background_color(const QColor &color);
  void set_edge_color(const QColor &color);
  void set_vert_color(const QColor &color);

private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void drawPolys();
  void LinesSettings();
  void PointsSettings();

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  QPoint mPos;
  double xRot = 0;
  double yRot = 0;
};

#endif // OPENGL_H
