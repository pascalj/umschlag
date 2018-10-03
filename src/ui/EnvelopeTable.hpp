#ifndef ENVELOPE_TABLE__H
#define ENVELOPE_TABLE__H
#include <QAbstractTableModel>
#include <QSqlQueryModel>


namespace ui {
class EnvelopeTable : public QAbstractTableModel {
  Q_OBJECT

public:
  EnvelopeTable(int year, uint8_t month, QObject *parent = nullptr);
  QVariant data(const QModelIndex &index,
                        int role) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  QSqlQueryModel base;
  int year;
  uint8_t month;
};
}

#endif
