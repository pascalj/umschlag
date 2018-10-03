#ifndef MAIN_WINDOW__H
#define MAIN_WINDOW__H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>


namespace ui {
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

  void showMonth(int year, uint8_t month);
private:
  bool initializeDatabase();
  void loadOrInsertMonth(int year, int month);

private:
  QTableView *tableView;
  QSqlDatabase db;
};

} // namespace ui

#endif

