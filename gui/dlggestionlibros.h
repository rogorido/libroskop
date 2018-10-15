#ifndef DLGGESTIONLIBROS_H
#define DLGGESTIONLIBROS_H

#include <QWidget>

class QSqlQueryModel;
class QSortFilterProxyModel;
class QModelIndex;

namespace Ui {
class dlgGestionLibros;
}

class dlgGestionLibros : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionLibros(QWidget *parent = 0);
    ~dlgGestionLibros();

private slots:
    // GUI
    void on_rbUniversidad_clicked();
    void on_rbTodos_clicked();
    void on_rbEmbajada_clicked();
    void on_pbBorrar_clicked();
    void on_rbDespacho_clicked();
    void on_rbDigital_clicked();
    void on_pbEditar_clicked();

    void borrarLibro(int id);
    void actualizarLabelTotales();
    void cargarDatosDerivados(int libro_id);
    void seleccionarLibro(const QModelIndex &idx);

signals:

    void modificarLibro(int id);

private:
    Ui::dlgGestionLibros *ui;

    QSqlQueryModel *m_libros;
    QSortFilterProxyModel *m_libros_proxy;
    QSqlQueryModel *m_autores;
    QSqlQueryModel *m_editores;
    QSqlQueryModel *m_categorias;

    QString sql_activa;
};

#endif // DLGGESTIONLIBROS_H
