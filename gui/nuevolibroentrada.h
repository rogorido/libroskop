#ifndef NUEVOLIBROENTRADA_H
#define NUEVOLIBROENTRADA_H

#include <QWidget>

#include "objs/variados.h"

namespace Ui {
class NuevoLibroEntrada;
}

class NuevoLibroEntrada : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoLibroEntrada(QWidget *parent = 0);
    ~NuevoLibroEntrada();

public slots:

    void recibirAutor(elementopareado autor);
    void recibirCategoria(elementopareado categoria);

private slots:

    void aceptarLibro();
    void anadirAutor();
    void quitarAutor();
    void anadirCategoria();
    void quitarCategoria();

    void borrarCampos();
    void cargarModelos();

signals:

    void seleccionarAutorSignal();
    void seleccionarCategoriaSignal();

private:
    Ui::NuevoLibroEntrada *ui;

    QList<elementopareado> autores;
    QList<elementopareado> categorias;
};

#endif // NUEVOLIBROENTRADA_H
