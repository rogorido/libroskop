#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QSqlDatabase>

class NuevoLibroEntrada;
class NuevoAutor;
class dlgSeleccionarGeneral;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMdiSubWindow *crearSubWindow();

public slots:

    void seleccionarAutor();
    void anadirAutor();

    void seleccionarCategoria();
    void anadirCategoria();

private slots:
    void on_actionSalir_triggered();
    void crearNuevoLibro();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    dlgSeleccionarGeneral *dlgseleccionar;
    NuevoLibroEntrada *dlgnuevolibro;
    NuevoAutor *dlgnuevoautor;
};

#endif // MAINWINDOW_H
