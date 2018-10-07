#include "MonthPicker.hpp"
#include "../model/EnvelopeTableModel.hpp"
#include <QComboBox>
#include <QLayout>

namespace ui {
MonthPicker::MonthPicker(QWidget *) {
  auto layout = new QHBoxLayout;
  auto years = new QComboBox;
  for (int i = 2000; i < 2019; i++) {
    years->addItem(QString::number(i));
  }
  auto months = new QComboBox;
  for (int i = 1; i < 13; i++) {
    months->addItem(QString::number(i));
  }
  layout->addWidget(years);
  layout->addWidget(months);
  setLayout(layout);

  QObject::connect(years, SIGNAL(currentIndexChanged(const QString &)), this,
                   SLOT(yearChanged(const QString &)));
  QObject::connect(months, SIGNAL(currentIndexChanged(const QString &)), this,
                   SLOT(monthChanged(const QString &)));

}

void MonthPicker::yearChanged(const QString &text) {
  month = model::Month{text.toUInt(), month.month};
  emit monthChanged(month);
}
void MonthPicker::monthChanged(const QString &text) {
  month = model::Month{month.year, text.toUInt()};
  emit monthChanged(month);
}
}
