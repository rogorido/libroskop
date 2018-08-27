#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDebug>

#include "gui/nuevolibroentrada.h"
#include "gui/nuevoautor.h"
#include "gui/dlgseleccionargeneral.h"

#include "objs/variados.h"

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

void MainWindow::seleccionarAutor()
{
    dlgseleccionar = new dlgSeleccionarGeneral(0, this);
    connect(dlgseleccionar, SIGNAL(autorEscogidoSignal(elementopareado)), dlgnuevolibro, SLOT(recibirAutor(elementopareado)));
    connect(dlgseleccionar, SIGNAL(anadirNuevoAutorSignal()), this, SLOT(anadirAutor()));
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(dlgseleccionar);
    window->show();

}

void MainWindow::anadirAutor()
{
    dlgnuevoautor = new NuevoAutor(this);
    connect(dlgnuevoautor, SIGNAL(nuevoAutorAceptadoSignal()), dlgseleccionar, SLOT(actualizarAutores()));
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(dlgnuevoautor);
    window->show();

}

void MainWindow::seleccionarCategoria()
{
    dlgseleccionar = new dlgSeleccionarGeneral(1, this);
    connect(dlgseleccionar, SIGNAL(categoriaEscogidaSignal(elementopareado)), dlgnuevolibro, SLOT(recibirCategoria(elementopareado)));
    connect(dlgseleccionar, SIGNAL(anadirNuevaCategoriaSignal()), this, SLOT(anadirCategoria()));
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(dlgseleccionar);
    window->show();

}

void MainWindow::anadirCategoria()
{

}

void MainWindow::on_actionSalir_triggered()
{
    qApp->quit();
}

void MainWindow::crearNuevoLibro()
{
    dlgnuevolibro = new NuevoLibroEntrada(this);
    connect(dlgnuevolibro, SIGNAL(seleccionarAutorSignal()), this, SLOT(seleccionarAutor()));
    connect(dlgnuevolibro, SIGNAL(seleccionarCategoriaSignal()), this, SLOT(seleccionarCategoria()));
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(dlgnuevolibro);
    window->show();
}
