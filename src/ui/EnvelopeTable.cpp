#include "EnvelopeTable.hpp"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLocale>

namespace ui {

EnvelopeTable::EnvelopeTable(int year, uint8_t month, QObject *parent)
    : QAbstractTableModel(parent), year(year), month(month) {
  QSqlQuery query;
  query.prepare(
      "SELECT categories.name, envelopes.budget, SUM(transactions.cents) "
      "as outflow, categories.id FROM envelopes "
      "LEFT JOIN categories ON categories.id = envelopes.category_id "
      "LEFT JOIN transactions ON envelopes.category_id = transactions.category_id "
      "WHERE strftime(\"%Y-%m\", transactions.date) = (:year || '-' || :month) "
      "GROUP BY transactions.category_id ");
  query.bindValue(":year", year);
  query.bindValue(":month", month);
  query.exec();
  base.setQuery(query);
}

QVariant EnvelopeTable::data(const QModelIndex &index,
                             int role = Qt::DisplayRole) const {
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (index.column() == 0) {
    return base.data(index);
  } else if (index.column() < 3) {
    return QLocale().toCurrencyString(base.data(index).toInt() / 100.0);
  } else {
    return QVariant("outflow");
  }
}

int EnvelopeTable::columnCount(const QModelIndex &) const {
  return 3;
}

int EnvelopeTable::rowCount(const QModelIndex &parent) const {
  return base.rowCount(parent);
}

bool EnvelopeTable::hasChildren(const QModelIndex &) const { return false; }

QVariant EnvelopeTable::headerData(int section, Qt::Orientation orientation,


                                   int role) const {
  if (role != Qt::DisplayRole)
    return QVariant();
  QVariant ret;
  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      ret = tr("Category");
      break;
    case 1:
      ret = tr("Budget");
      break;
    case 2:
      ret = tr("Outflow");
    }
  }
  return ret;
}

Qt::ItemFlags EnvelopeTable::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractTableModel::flags(index); // | Qt::ItemIsEditable;
 }
} // namespace ui
