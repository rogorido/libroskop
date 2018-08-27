#ifndef DLGSELECCIONARGENERAL_H
#define DLGSELECCIONARGENERAL_H

#include <QWidget>

#include "objs/variados.h"

//class QSqlTableModel;
class QSqlQueryModel;
class ProxyNombres;

class QMenu;
class QAction;
class QModelIndex;

namespace Ui {
class dlgSeleccionarGeneral;
}

class dlgSeleccionarGeneral : public QWidget
{
    Q_OBJECT

public:
    /*
     *  tipo: 0 = autor, 1 = categoría
     */
    explicit dlgSeleccionarGeneral(int tipo, QWidget *parent = 0);
    ~dlgSeleccionarGeneral();

private slots:

    void anadirObjeto();
    void actualizarObjeto();
    void seleccionarObjeto(const QModelIndex &idx);

    void actualizarFiltro(const QString filtro);

    void aceptar();
    void cerrar();

public slots:

    void actualizarAutores();
    void actualizarCategorias();

signals:

    // estas dos se emiten para que las recoja la MainWindow
    void anadirNuevoAutorSignal();
    void anadirNuevaCategoriaSignal();

    void autorEscogidoSignal(elementopareado autor);
    void categoriaEscogidaSignal(elementopareado categoria);

private:
    Ui::dlgSeleccionarGeneral *ui;

    QSqlQueryModel *m_objeto;
    ProxyNombres *m_objeto_proxy;

    /*
     * aquí guardamos la query que usamos
     */
    QString sql_general;

    // si es para categorías o para autores
    // autores = 0, cats = 1
    int tipo_dialogo;

    void cargarModelo();
    void cargarTipo();
    void cargarTituloVentana();

    // esto es un sistema para que genere luego las señales...
    void autor();
    void categoria();

};

#endif // DLGSELECCIONARGENERAL_H
