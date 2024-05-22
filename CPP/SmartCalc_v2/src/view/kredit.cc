#include "kredit.h"

#include <QDoubleValidator>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <cmath>

#include "ui_kredit.h"

kredit::kredit(QWidget* parent) : QDialog(parent), ui(new Ui::kredit) {
  ui->setupUi(this);
  setFixedSize(width(), height());

  ui->creditAmount->setValidator(new QDoubleValidator(this));
  ui->rate->setValidator(new QDoubleValidator(this));
  ui->creditTerm->setValidator(new QIntValidator(this));

  // Создаем градиентный фон
  QLinearGradient gradient(0, 0, 0, height());
  gradient.setColorAt(0, QColor(255, 127, 80));  // Начальный цвет
  gradient.setColorAt(1, QColor(186, 85, 211));  // Конечный цвет

  // Устанавливаем градиентный фон в качестве фона MainWindow
  QPalette palette;
  palette.setBrush(QPalette::Window, QBrush(gradient));
  setPalette(palette);
}

kredit::~kredit() { delete ui; }

void kredit::on_pushButton_clicked() {
  if (inputFieldsEmpty() || inputFieldsContainInvalidChars()) {
    return;
  }

  bool have_error = true;
  QString rub = " \u20BD";
  double credit_amount = ui->creditAmount->text().toDouble();
  int credit_term = ui->creditTerm->text().toInt();
  int credit_term_type = ui->termPer->currentText() == "лет" ? 12 : 1;
  double credit_rate = ui->rate->text().toDouble();
  std::string credit_payment_type = ui->creditType->currentText().toStdString();

  if (!inputDataValid(credit_amount, credit_term, credit_rate)) {
    showErrorMessage("Enter credit information correctly");
  } else if (!creditDataValid(credit_amount, credit_term, credit_rate)) {
    showErrorMessage("Enter credit data more than 0");
  } else if (!creditTermValid(credit_term, credit_term_type)) {
    showErrorMessage("Enter a credit term less or equals than 20 years");
  } else {
    have_error = false;
    credit_input_.credit_amount = credit_amount;
    credit_input_.credit_term = credit_term;
    credit_input_.credit_term_type = credit_term_type;
    credit_input_.credit_rate = credit_rate;
    credit_input_.credit_payment_type = credit_payment_type;
    credit_controller_.SetInputData(credit_input_);
    credit_controller_.KreditCalculate();
    credit_output_ = credit_controller_.GetOutputData();

    updateMonthlyPaymentField(credit_payment_type);
    updateTotalPaymentFields();
    have_error = checkForErrors();
  }

  if (have_error) {
    showErrorFields();
  } else {
    updateResultFields(rub);
  }
}

bool kredit::inputFieldsEmpty() const {
  return ui->rate->text().isEmpty() || ui->creditAmount->text().isEmpty() ||
         ui->creditTerm->text().isEmpty();
}

bool kredit::inputFieldsContainInvalidChars() const {
  QString creditAmountText = ui->creditAmount->text();
  QString rateText = ui->rate->text();
  QString creditTermText = ui->creditTerm->text();

  QRegularExpression regex("[^0-9.]");
  return regex.match(creditAmountText).hasMatch() ||
         regex.match(rateText).hasMatch() ||
         regex.match(creditTermText).hasMatch();
}

bool kredit::inputDataValid(double amount, int term, double rate) const {
  return !(amount <= 0 || term <= 0 || rate < 0);
}

bool kredit::creditDataValid(double amount, int term, double rate) const {
  return inputDataValid(amount, term, rate);
}

bool kredit::creditTermValid(int term, int term_type) const {
  return term * term_type <= 240;
}

void kredit::showErrorMessage(const QString& message) const {
  QMessageBox::information(nullptr, "ERROR", message);
}

void kredit::updateMonthlyPaymentField(const std::string& payment_type) {
  QString rub = " \u20BD";
  if (payment_type == "Аннуитетные") {
    QString month_pay =
        QString::number(credit_output_.monthly_payment[0], 'f', 2);
    if (!month_pay.endsWith("nan") && !month_pay.endsWith("inf"))
      ui->monthPayment->setText(month_pay + rub);
    else
      showErrorFields();
  } else if (payment_type == "Дифференцированные") {
    ui->monthPayment->clear();
    size_t vector_size = credit_output_.monthly_payment.size();
    for (size_t i = 0; i < vector_size; i++) {
      QString m_number = QString::number(i + 1);
      double month_pay = credit_output_.monthly_payment[i];
      QString m_pay = QString::number(month_pay, 'f', 2);
      QString current_m_pay = ui->monthPayment->toPlainText();
      QString output_str = current_m_pay + m_number + " - " + m_pay + rub;
      if (i != vector_size - 1) output_str += "\n";
      ui->monthPayment->setText(output_str);
    }
  }
}

void kredit::updateTotalPaymentFields() {
  credit_output_.total_payment =
      std::round(credit_output_.total_payment * 100) / 100;
  credit_output_.over_payment =
      std::round(credit_output_.over_payment * 100) / 100;
}

bool kredit::checkForErrors() const {
  QString str1 = QString::number(credit_output_.monthly_payment[0], 'f', 2);
  QString str2 = QString::number(credit_output_.over_payment, 'f', 2);
  QString str3 = QString::number(credit_output_.total_payment, 'f', 2);

  return str1.startsWith("nan") || str2.startsWith("nan") ||
         str3.startsWith("nan") || str1.startsWith("inf") ||
         str2.startsWith("inf") || str3.startsWith("inf") ||
         str1.startsWith("-inf") || str2.startsWith("-inf") ||
         str3.startsWith("-inf") || credit_output_.monthly_payment[0] < 0 ||
         credit_output_.over_payment < 0 || credit_output_.total_payment < 0;
}

void kredit::showErrorFields() const {
  ui->monthPayment->setText("Error");
  ui->overPay->setText("Error");
  ui->totalPay->setText("Error");
}

void kredit::updateResultFields(const QString& rub) const {
  QString str1 =
      QString::number(credit_output_.monthly_payment[0], 'f', 2) + rub;
  QString str2 = QString::number(credit_output_.over_payment, 'f', 2) + rub;
  QString str3 = QString::number(credit_output_.total_payment, 'f', 2) + rub;

  ui->overPay->setText(str2);
  ui->totalPay->setText(str3);
}
