#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDebug>

#include "gui/nuevolibroentrada.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString home = QDir::homePath();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(home + QString("/libros.db"));

    if (db.open())
        qDebug() << "DB abierta, paspanín!";

    connect(ui->actionNuevoLibro, SIGNAL(triggered(bool)), this, SLOT(crearNuevoLibro()));
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

QMdiSubWindow *MainWindow::crearSubWindow()
{
    QMdiSubWindow *child = new QMdiSubWindow;
    ui->mdiArea->addSubWindow(child);

    return child;
}

void MainWindow::on_actionSalir_triggered()
{
    qApp->quit();
}

void MainWindow::crearNuevoLibro()
{
    dlgnuevolibro = new NuevoLibroEntrada(this);
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(dlgnuevolibro);
    window->show();
}
