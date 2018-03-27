#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("libros.db");

    if (db.open())
        qDebug() << "DB abierta, paspanín!";
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

void MainWindow::on_actionSalir_triggered()
{
    qApp->quit();
}
