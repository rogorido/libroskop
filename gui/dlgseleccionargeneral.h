#ifndef DLGSELECCIONARGENERAL_H
#define DLGSELECCIONARGENERAL_H

#include <QWidget>

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
    explicit dlgSeleccionarGeneral(int tipo, QWidget *parent = 0);
    ~dlgSeleccionarGeneral();

private slots:

    void anadirObjeto();
    void actualizarObjeto();
    void seleccionarObjeto(const QModelIndex &idx);

    void actualizarFiltro(const QString filtro);

    void aceptar();
    void cerrar();

signals:
    void autorEscogidoSignal(elementopareado autor);
    void categoriaEscogidaSignal(elementopareado categoria);

private:
    Ui::dlgSeleccionarGeneral *ui;

    QSqlQueryModel *m_objeto;
    ProxyNombres *m_objeto_proxy;

    struct elementopareado{
      int id = 0;
      QString elemento = "";
    };

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
