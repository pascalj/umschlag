#ifndef MAIN_WINDOW__H
#define MAIN_WINDOW__H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>
#include "../model/EnvelopeTableModel.hpp"


namespace ui {
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

public slots:
  void showMonth(model::Month);

private:
  bool initializeDatabase();
  void loadOrInsertMonth(model::Month);

private:
  QTableView *tableView;
  QSqlDatabase db;
};

} // namespace ui

#endif

