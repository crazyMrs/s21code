#ifndef CPP3_SMARTCALC_V2_SRC_VIEW_KREDIT_H
#define CPP3_SMARTCALC_V2_SRC_VIEW_KREDIT_H

#include <QDialog>

#include "../controller/kredit_controller.h"

namespace Ui {
class kredit;
}

class kredit : public QDialog {
  Q_OBJECT

 public:
  explicit kredit(QWidget* parent = nullptr);
  ~kredit();

 private slots:
  void on_pushButton_clicked();
  bool inputFieldsEmpty() const;
  bool inputFieldsContainInvalidChars() const;
  bool inputDataValid(double amount, int term, double rate) const;
  bool creditDataValid(double amount, int term, double rate) const;
  bool creditTermValid(int term, int term_type) const;
  void showErrorMessage(const QString& message) const;
  void updateMonthlyPaymentField(const std::string& payment_type);
  void updateTotalPaymentFields();
  bool checkForErrors() const;
  void showErrorFields() const;
  void updateResultFields(const QString& rub) const;

 private:
  Ui::kredit* ui;
  s21::KreditController credit_controller_;
  s21::CreditInput credit_input_;
  s21::CreditOutput credit_output_;
};

#endif  // CPP3_SMARTCALC_V2_SRC_VIEW_KREDIT_H
