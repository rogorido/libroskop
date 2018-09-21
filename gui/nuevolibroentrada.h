#ifndef NUEVOLIBROENTRADA_H
#define NUEVOLIBROENTRADA_H

#include <QWidget>

#include "objs/variados.h"

class QSqlQueryModel;
class QCompleter;

namespace Ui {
class NuevoLibroEntrada;
}

class NuevoLibroEntrada : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoLibroEntrada(int libro_id, QWidget *parent = 0);
    ~NuevoLibroEntrada();

public slots:

    void recibirAutor(elementopareado autor);
    void recibirCategoria(elementopareado categoria);

private slots:

    void cerrar();
    void aceptarLibro();
    void anadirAutor();
    void quitarAutor();
    void anadirCategoria();
    void quitarCategoria();

    // esto se activa en caso de que el libro se meta bien en la db
    void introducirAutores(int id);
    void introducirCategorias(int id);

    void borrarCampos();
    void cargarModelos();

signals:

    void seleccionarAutorSignal();
    void seleccionarCategoriaSignal();

private:
    Ui::NuevoLibroEntrada *ui;

    bool modificando = false;
    int libro_modificandi = 0;

    QList<elementopareado> autores;
    QList<elementopareado> categorias;

    QSqlQueryModel *m_editoriales;
    QSqlQueryModel *m_lugares;
    QSqlQueryModel *m_lenguas;
    QCompleter *c_editoriales;
    QCompleter *c_lugares;
    QCompleter *c_lenguas;

    /*
     * esto lo metemos en una QStringList pq en teoría son solo dos
     * que no cambian...
     */

    QStringList m_localizaciones;
    QCompleter *c_localizaciones;

    /*
     * Para el caso de que estemos modificando uno existente
     */
    void cargarLibro();
};

#endif // NUEVOLIBROENTRADA_H
