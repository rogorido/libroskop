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

private slots:

    void aceptarLibro();
    void anadirAutor();
    void quitarAutor();
    void anadirCategoria();
    void quitarCategoria();

signals:

    void seleccionarAutorSignal();

private:
    Ui::NuevoLibroEntrada *ui;

    QList<elementopareado> autores;
    QList<elementopareado> categorias;
};

#endif // NUEVOLIBROENTRADA_H
