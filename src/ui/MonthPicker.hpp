#ifndef MONTHPICKER_HPP
#define MONTHPICKER_HPP

#include "../model/EnvelopeTableModel.hpp"
#include <QWidget>

namespace ui {
class MonthPicker : public QWidget {
Q_OBJECT

public:
  MonthPicker(QWidget *parent = nullptr);

signals:
  void monthChanged(model::Month month);

public slots:
  void yearChanged(const QString &);
  void monthChanged(const QString &);

private:

  model::Month month;
};
}

#endif /* MONTHPICKER_HPP */
