#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QSqlDatabase>

class NuevoLibroEntrada;

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

private slots:
    void on_actionSalir_triggered();
    void crearNuevoLibro();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    NuevoLibroEntrada *dlgnuevolibro;
};

#endif // MAINWINDOW_H
