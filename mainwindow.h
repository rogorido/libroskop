#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QSqlDatabase>

class NuevoLibroEntrada;
class NuevoAutor;
class NuevaCategoria;
class dlgSeleccionarGeneral;
class dlgGestionLibros;

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

    /*
     * El asunto funciona así: en estas window se conectan todos las señales
     * y slots de los diferentes forms que se van abriendo. El form NuevoLibro
     * emite una señal que se conecta con el este slot de seleccionarAutor()
     * que a su vez abre el form dlgSeleccionar y este emite otras señales
     * que se conectar con el form NuevoLibro A TRAVÉS de este MainWindow!
     *
     * Por tanto:
     *
     * dlgnuevolibro emite-> seleccionarAutor
     *   --> esto abre dlgSeleccionar
     *   ---> que emite autorEscogidoSignal que se conecta con recibirAutor
     *        de dlgnuevolibro
     */

    void seleccionarAutor();
    void anadirAutor();

    void seleccionarCategoria();
    void anadirCategoria();

    void modificarLibro(int id);

private slots:
    void on_actionSalir_triggered();
    void crearNuevoLibro();

    void on_actionLibros_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    dlgSeleccionarGeneral *dlgseleccionar;
    NuevoLibroEntrada *dlgnuevolibro;
    NuevoAutor *dlgnuevoautor;
    NuevaCategoria *dlgnuevacategoria;
    dlgGestionLibros *dlggestionlibros;
};

#endif // MAINWINDOW_H
