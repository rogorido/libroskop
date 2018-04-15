#ifndef NUEVOLIBROENTRADA_H
#define NUEVOLIBROENTRADA_H

#include <QWidget>

namespace Ui {
class NuevoLibroEntrada;
}

class NuevoLibroEntrada : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoLibroEntrada(QWidget *parent = 0);
    ~NuevoLibroEntrada();

private slots:

    void aceptarLibro();
    void anadirAutor();
    void quitarAutor();
    void anadirCategoria();
    void quitarCategoria();

signals:

    void anadirAutorSignal();

private:
    Ui::NuevoLibroEntrada *ui;

    struct elementopareado{
      int id = 0;
      QString elemento = "";
    };

    QList<elementopareado> autores;
    QList<elementopareado> categorias;
};

#endif // NUEVOLIBROENTRADA_H
