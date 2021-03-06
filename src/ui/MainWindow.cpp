#include "MainWindow.hpp"
#include "../model/EnvelopeTableModel.hpp"
#include <QDebug>
#include <QHeaderView>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QLayout>
#include "MonthPicker.hpp"

namespace ui {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), db(QSqlDatabase::addDatabase("QSQLITE")) {
  initializeDatabase();

  QWidget *mainWidget = new QWidget;
  tableView = new QTableView(this);
  auto monthPicker = new ui::MonthPicker(this);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(monthPicker);
  layout->addWidget(tableView);
  mainWidget->setLayout(layout);
  setCentralWidget(mainWidget);
  model::Month month{2018, 10};
  QObject::connect(monthPicker, SIGNAL(monthChanged(model::Month)), this, SLOT(showMonth(model::Month)));
  showMonth(month);
}

void MainWindow::showMonth(model::Month month) {
  loadOrInsertMonth(month);
  model::EnvelopeTableModel *model = new model::EnvelopeTableModel(month);
  tableView->setModel(model);
  tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::loadOrInsertMonth(model::Month month) {
  QSqlQuery query;
  query.prepare("INSERT INTO envelopes (category_id, year, month)"
                "SELECT categories.id, :year, :month FROM "
                "categories");
  query.bindValue(":year", month.year);
  query.bindValue(":month", month.month);
  query.exec();
}

bool MainWindow::initializeDatabase() {
  if (!db.open()) {
    qDebug() << "Unable to open database";
    qDebug() << db.lastError();
    return false;
  }
  QSqlError error = db.exec("CREATE TABLE IF NOT EXISTS categories ("
                            "id integer primary key, "
                            "name VARCHAR(255), "
                            "deleted integer);")
                        .lastError();

  db.exec("CREATE TABLE IF NOT EXISTS accounts ("
          "id integer primary key, "
          "name varchar(255), "
          "number varchar(255))");

  db.exec("CREATE TABLE IF NOT EXISTS transactions ("
          "id integer primary key, "
          "date varchar(255), "
          "purpose text, "
          "account_id integer, "
          "cents integer, "
          "category_id integer, "
          "FOREIGN KEY(account_id) REFERENCES accounts(id), "
          "FOREIGN KEY(category_id) REFERENCES categories(id))");

  db.exec("CREATE TABLE IF NOT EXISTS months ("
          "id integer primary key, "
          "year integer, "
          "month integer)");

  db.exec("CREATE TABLE IF NOT EXISTS envelopes ("
          "id integer primary key, "
          "category_id integer, "
          "year integer, "
          "month integer, "
          "budget integer DEFAULT 0, "
          "FOREIGN KEY(category_id) REFERENCES categories(id))");

  if (error.isValid()) {
    qDebug() << error;
  }
  db.exec("INSERT INTO categories (name) VALUES (\"example\")");
  db.exec("INSERT INTO transactions (category_id, date, purpose, cents) VALUES (1, date(\"2018-10-15\"), \"inflow\", 3411)");
  db.exec("INSERT INTO transactions (category_id, date, purpose, cents) VALUES (2, date(\"2018-10-15\"), \"outflow\", -433)");
  return !error.isValid();
}

} // namespace ui

