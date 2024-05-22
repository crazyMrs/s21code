#include "mainwindow.h"

#include <QDebug>
#include <QDoubleValidator>
#include <QLabel>
#include <QString>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  // Создаем градиентный фон
  QLinearGradient gradient(0, 0, 0, height());
  gradient.setColorAt(0, QColor(255, 127, 80)); // Начальный цвет
  gradient.setColorAt(1, QColor(186, 85, 211)); // Конечный цвет

  // Устанавливаем градиентный фон в качестве фона MainWindow
  QPalette palette;
  palette.setBrush(QPalette::Window, QBrush(gradient));
  setPalette(palette);

  ui->setupUi(this);

  this->actWindow = ui->result_show;
  ui->result_show_x->setValidator(new QDoubleValidator(this));

  ui->lineEdit_xMin->setValidator(new QDoubleValidator(this));
  ui->lineEdit_xMax->setValidator(new QDoubleValidator(this));
  ui->lineEdit_yMin->setValidator(new QDoubleValidator(this));
  ui->lineEdit_yMax->setValidator(new QDoubleValidator(this));

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_pm, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(math_operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(trigonometric_operations()));

  connect(ui->pushButton_ac, SIGNAL(clicked()), this,
          SLOT(on_pushButton_eq_clicked()));

  connect(ui->plotButton, SIGNAL(clicked()), this, SLOT(plot_graph()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  if (this->actWindow->text() == "0") {
    this->actWindow->setText(button->text());
  } else {
    actWindow->setText(actWindow->text().append(button->text()));
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  // if(!(this->actWindow->text().contains('.')))
  //        this->actWindow->setText(this->actWindow->text() + ".");
  //    if(this->actWindow->text()=='.') {
  //            this->actWindow->setText("0.");
  //        }
  QString text = this->actWindow->text();
  QChar lastChar = text.isEmpty() ? ' ' : text[text.length() - 1];

  if (!text.contains('.') && (lastChar.isDigit() || lastChar == 'x')) {
    this->actWindow->setText(this->actWindow->text() + ".");
  }
  if (this->actWindow->text() == '.') {
    this->actWindow->setText("0.");
  }
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();

  double all_numbers;

  QString new_label;

  if (button->text() == "+/-") {
    all_numbers = (ui->result_show->text()).toDouble();
    all_numbers = all_numbers * -1;

    new_label = QString::number(all_numbers, 'g', 15);

    ui->result_show->setText(new_label);
  }
}

void MainWindow::math_operations() {
  auto_mul();

  this->actWindow = ui->result_show;

  QPushButton *button = (QPushButton *)sender();

  QString current_expression = this->actWindow->text();

  if (!(this->actWindow->text().endsWith("/") ||
        this->actWindow->text().endsWith("*") ||
        this->actWindow->text().endsWith("+") ||
        this->actWindow->text().endsWith("-") ||
        this->actWindow->text().endsWith("^") ||
        this->actWindow->text().endsWith("mod"))) {
    current_expression += button->text();
  } else {
    current_expression += "(";
  }

  ui->result_show->setText(current_expression);
}

void MainWindow::trigonometric_operations() {
  auto_mul();
  this->actWindow = ui->result_show;

  QPushButton *button = (QPushButton *)sender();
  QString new_label;

  if (this->actWindow->text() == "0") {
    this->actWindow->setText(button->text());
  } else {
    new_label = (this->actWindow->text() + button->text()) + "(";
  }

  this->actWindow->setText(new_label);
}

void MainWindow::on_pushButton_ac_clicked() {
  ui->result_show->setText("");
  ui->result_show_x->setText("");
}

void MainWindow::on_pushButton_ac_2_clicked() {
  QString current_text = ui->result_show->text();

  if (current_text.isEmpty()) {
    return;
  }

  // убираем последний символ
  current_text.chop(1);

  ui->result_show->setText(current_text);
}

void MainWindow::on_pushButton_11_clicked() {
  QString new_label;

  if (!(ui->result_show->text().endsWith("x")))
    new_label = ui->result_show->text() + "x";

  ui->result_show->setText(new_label);
}

void MainWindow::auto_mul() {
  QString current_expression = ui->result_show->text();

  int len = current_expression.length();

  for (int i = 0; i < len - 1; ++i) {
    QChar current_char = current_expression[i];
    QChar next_char = current_expression[i + 1];

    if ((current_char.isDigit() || current_char == 'x') &&
        (next_char == '(' || next_char == 'x')) {
      current_expression.insert(i + 1, '*');
      len++;
    } else if ((current_char == ')') &&
               (next_char.isDigit() || next_char == 'x' || next_char == '(' ||
                next_char.isLetter())) {
      current_expression.insert(i + 1, '*');
      len++;
    }
  }

  ui->result_show->setText(current_expression);
}

void MainWindow::on_pushButton_eq_clicked() {
  if (ui->result_show->text().isEmpty()) {
    return;
  }
  auto_mul();

  QString temp = ui->result_show->text();
  QString temp_x = ui->result_show_x->text();

  if (!temp_x.isEmpty()) {
    if (temp_x.startsWith("-")) {
      temp_x = "(" + temp_x + ")";
    } else if (temp_x.startsWith("+")) {
      temp_x = temp_x.mid(1);
    }
    temp = temp.replace("x", temp_x);
  }

  if (!temp.isEmpty() && !temp.startsWith(")") &&
      !(temp.endsWith("/") || temp.endsWith("*") || temp.endsWith("+") ||
        temp.endsWith("-") || temp.endsWith("^") || temp.endsWith("mod"))) {
    QByteArray ba = temp.toLatin1();
    char *str = ba.data();

//    if (temp.contains("(") && temp.indexOf("(") < temp.lastIndexOf("+")) {
//      temp.remove(temp.indexOf("+", temp.indexOf("(")), 1);
//      str = temp.toLatin1().data(); // Обновляем указатель
//    }

    ba.replace(",", ".");
    long double result;
    qDebug() << str;
    int error = input_str(str, &result);
    qDebug() << input_str(str, &result);
    qDebug() << error;
    if (!error)
      ui->result_show->setText(QString::number(result, 'g', 15));
    if (error == -1)
      ui->result_show->setText("ERROR");
    if (error == -2)
      ui->result_show->setText("INF");
  } else {
    return;
  }
}

//ГРАФИКИ!!!!!
// Функция для вставки знаков умножения
QString insertMultiplicationSigns(const QString &expr) {
  QString result;
  for (int i = 0; i < expr.length(); ++i) {
    QChar current_char = expr[i];
    QChar next_char = (i + 1 < expr.length()) ? expr[i + 1] : QChar();

    if (current_char == 'x') {
      result += "(x)";
    } else {
      result += current_char;
    }

    if ((current_char.isDigit() || current_char == 'x') &&
        (next_char == '(' || next_char == 'x' || next_char.isDigit())) {
      result += '*';
    }
  }
  return result;
}

// Функция отрисовки графика
void plotFunction(QCustomPlot *customPlot, QString &function, double xMin,
                  double xMax, double yMin, double yMax) {
  customPlot->clearGraphs();

  QVector<double> x, y;
  x.clear();
  y.clear();

  customPlot->xAxis->setRange(xMin, xMax);
  customPlot->yAxis->setRange(yMin, yMax);

  if (xMin >= -1000000 && xMax <= 1000000 && yMin >= -1000000 &&
      yMax <= 1000000) {
    double X, Y = 0;
    for (X = xMin; X <= xMax; X += 0.1) {
      QString current_expr = insertMultiplicationSigns(function);
      // qDebug() << current_expr;
      QString xValue = QString::number(X);
      current_expr.replace("x", xValue);
      QByteArray str_buffer = current_expr.toUtf8();
      char *str = str_buffer.data();
      long double result;

      if (input_str(str, &result) == 0) {
        x.push_back(X);
        Y = result;
        y.push_back(Y);
      }
    }
  }

  customPlot->addGraph();
  customPlot->graph(0)->addData(x, y);
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                              QCP::iSelectPlottables);
  customPlot->replot();
}

void MainWindow::plot_graph() {
  QString expression = ui->result_show->text();
  bool is_x_min, is_y_min, is_x_max, is_y_max = false;
  double xMin = (ui->lineEdit_xMin->text().isEmpty())
                    ? -20.0
                    : ui->lineEdit_xMin->text().toDouble(&is_x_min);
  double xMax = (ui->lineEdit_xMax->text().isEmpty())
                    ? 20.0
                    : ui->lineEdit_xMax->text().toDouble(&is_x_max);
  double yMin = (ui->lineEdit_yMin->text().isEmpty())
                    ? -20.0
                    : ui->lineEdit_yMin->text().toDouble(&is_y_min);
  double yMax = (ui->lineEdit_yMax->text().isEmpty())
                    ? 20.0
                    : ui->lineEdit_yMax->text().toDouble(&is_y_max);
  plotFunction(ui->plotwidget, expression, xMin, xMax, yMin, yMax);
}

//КРЕДИТНЫЙ
void MainWindow::on_pushButton_cred_clicked() {
  kreditcal = new kredit(this);
  kreditcal->show();
}
