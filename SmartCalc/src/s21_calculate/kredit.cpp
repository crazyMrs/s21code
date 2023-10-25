#include "kredit.h"

#include <QDoubleValidator>
#include <QLabel>
#include <QMessageBox>
#include <QString>

#include "ui_kredit.h"

kredit::kredit(QWidget *parent) : QDialog(parent), ui(new Ui::kredit) {
  ui->setupUi(this);

  ui->lineEdit_sum->setValidator(new QDoubleValidator(this));
  ui->lineEdit_pr->setValidator(new QDoubleValidator(this));
  ui->lineEdit_time->setValidator(new QIntValidator(this));

  // Создаем градиентный фон
  QLinearGradient gradient(0, 0, 0, height());
  gradient.setColorAt(0, QColor(255, 127, 80)); // Начальный цвет
  gradient.setColorAt(1, QColor(186, 85, 211)); // Конечный цвет

  // Устанавливаем градиентный фон в качестве фона MainWindow
  QPalette palette;
  palette.setBrush(QPalette::Window, QBrush(gradient));
  setPalette(palette);
}

kredit::~kredit() { delete ui; }

void kredit::on_pushButton_clicked() {
  if (ui->lineEdit_pr->text().isEmpty() || ui->lineEdit_sum->text().isEmpty() ||
      ui->lineEdit_time->text().isEmpty()) {
    return;
  } else if (ui->lineEdit_sum->text().contains('+') ||
             ui->lineEdit_sum->text().contains('-') ||
             ui->lineEdit_pr->text().contains('+') ||
             ui->lineEdit_pr->text().contains('-') ||
             ui->lineEdit_time->text().contains('+') ||
             ui->lineEdit_time->text().contains('-')) {
    return;
  } else {
    typedef struct {
      long double monthly_payment; // ежемесячно оплата
      long double overpayment;     // переплата
      long double total_payment;   // всего к оплате
    } CreditStruct;

    CreditStruct credit_struct = {0, 0, 0};

    QString summ = ui->lineEdit_sum->text();
    summ.replace(",", ".");
    long double cr_sum = summ.toDouble();

    QString proc = ui->lineEdit_pr->text();
    proc.replace(",", ".");
    long double cr_pr = proc.toDouble() / 100;

    QString year = ui->lineEdit_time->text();
    long double cr_year = year.toDouble();

    long double num_pay;

    if (ui->comboBox_3->currentText() == "лет") {
      num_pay = cr_year * 12.0;
    } else if (ui->comboBox_3->currentText() == "месяцев") {
      num_pay = cr_year;
    }

    if (ui->comboBox_4->currentText() == "Аннуитетные") {
      long double monthly_rate = cr_pr / 12.0;
      credit_struct.monthly_payment =
          (cr_sum * monthly_rate) / (1 - pow(1 + monthly_rate, -num_pay));
      credit_struct.total_payment = credit_struct.monthly_payment * num_pay;
      credit_struct.overpayment = credit_struct.total_payment - cr_sum;
      ui->label_mp->setText(
          QString("%L1 ₽").arg(credit_struct.monthly_payment, 0, 'f', 2));
      ui->label_kr->setText(
          QString("%L1 ₽").arg(credit_struct.overpayment, 0, 'f', 2));
      ui->label_vy->setText(
          QString("%L1 ₽").arg(credit_struct.total_payment, 0, 'f', 2));

    } else if (ui->comboBox_4->currentText() == "Дифференцированные") {
      long double monthly_interest_rate = cr_pr / 12.0;
      long double principal_payment = cr_sum / num_pay;

      long double remaining_balance = cr_sum;
      long double total_payment = 0.0;
      QString first_last_payments_text = "";

      for (int i = 1; i <= num_pay; ++i) {
        long double monthly_interest_payment =
            remaining_balance * monthly_interest_rate;

        if (i == num_pay) {
          principal_payment = remaining_balance;
          first_last_payments_text += QString("%L1 ₽").arg(
              principal_payment + monthly_interest_payment, 0, 'f', 2);

        } else if (i == 1) {
          first_last_payments_text +=
              QString("%L1 ₽").arg(
                  principal_payment + monthly_interest_payment, 0, 'f', 2) +
              " … ";
        }
        remaining_balance -= principal_payment;
        total_payment += principal_payment + monthly_interest_payment;
      }

      credit_struct.monthly_payment = principal_payment;
      credit_struct.total_payment = total_payment;
      long double overpayment = total_payment - cr_sum;

      ui->label_mp->setText(first_last_payments_text);
      ui->label_kr->setText(QString("%L1 ₽").arg(overpayment, 0, 'f', 2));
      ui->label_vy->setText(QString("%L1 ₽").arg(total_payment, 0, 'f', 2));
    }
  }
}
