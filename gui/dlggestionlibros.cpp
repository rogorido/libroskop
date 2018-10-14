#include "dlggestionlibros.h"
#include "ui_dlggestionlibros.h"

#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

const QString sql_general = "SELECT * FROM libro";
const QString sql_universidad = "SELECT * FROM libro WHERE localizacion='Biblioteca'";
const QString sql_embajada = "SELECT * FROM libro WHERE localizacion='Embajada'";
const QString sql_despacho = "SELECT * FROM libro WHERE localizacion='Despacho'";
const QString sql_digital = "SELECT * FROM libro WHERE localizacion='Digital'";


dlgGestionLibros::dlgGestionLibros(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionLibros)
{
    ui->setupUi(this);

    m_libros = new QSqlQueryModel(this);
    m_libros->setQuery(sql_general);
    m_libros->setHeaderData(1, Qt::Horizontal, trUtf8("Título"));
    m_libros->setHeaderData(2, Qt::Horizontal, trUtf8("Subtítulo"));
    m_libros->setHeaderData(3, Qt::Horizontal, trUtf8("Editorial"));
    m_libros->setHeaderData(4, Qt::Horizontal, trUtf8("Lugar"));
    m_libros->setHeaderData(5, Qt::Horizontal, trUtf8("Fecha"));
    m_libros->setHeaderData(6, Qt::Horizontal, trUtf8("Lengua"));
    m_libros->setHeaderData(7, Qt::Horizontal, trUtf8("Localización"));

    m_libros_proxy = new QSortFilterProxyModel(this);
    m_libros_proxy->setSourceModel(m_libros);

    ui->tvLibros->setModel(m_libros_proxy);
    ui->tvLibros->hideColumn(0); // la id

    ui->tvLibros->setAlternatingRowColors(true);
    //ui->twResoluciones->setColumnWidth(1, 80);
    ui->tvLibros->resizeColumnsToContents();
    //ui->tvLibros->resizeRowsToContents();
    //ui->tvLibros->horizontalHeader()->setStretchLastSection(true);
    ui->tvLibros->setSortingEnabled(true);
    ui->tvLibros->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tvLibros->setSelectionMode(QAbstractItemView::SingleSelection);

    // escogemos la primera línea del modelo...
    QModelIndex index = m_libros->index(0,0);
    if (index.isValid()) {
        ui->tvLibros->setCurrentIndex(index);
    }

    sql_activa = sql_general;
    ui->lblTotal->setText(QString("Total: %1").arg(m_libros->rowCount()));

    /*
      Inicializamos también los otros modelos, aunque
      todavía no los cargamos.
    */

    m_autores = new QSqlQueryModel(this);
    m_editores = new QSqlQueryModel(this);
    m_categorias = new QSqlQueryModel(this);

    connect(ui->tvLibros->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(seleccionarLibro(QModelIndex)));

}

dlgGestionLibros::~dlgGestionLibros()
{
    delete ui;
}

void dlgGestionLibros::on_rbUniversidad_clicked()
{
    m_libros->setQuery(sql_universidad);
    sql_activa = sql_universidad;
}

void dlgGestionLibros::on_rbTodos_clicked()
{

    m_libros->setQuery(sql_general);
    sql_activa = sql_general;
}

void dlgGestionLibros::on_rbEmbajada_clicked()
{
    m_libros->setQuery(sql_embajada);
    sql_activa = sql_embajada;
}

void dlgGestionLibros::on_pbBorrar_clicked()
{
    /*
     * Joder esto es un puot lío... necesito tanto puto idx?
     */

    // esto entiendo que coge el índice del tableview...
    QModelIndex idx = ui->tvLibros->currentIndex();
    if (!idx.isValid())
        return;

    // de ahí coge el índice del model que subyace (que es un qsortfilteretc)...
    QModelIndex idx2 = idx.model()->index(idx.row(), 0);
    if (!idx2.isValid())
        return;

    // y eso lo mapea al original.
    QModelIndex idx3 = m_libros_proxy->mapToSource(idx2);
    if (!idx3.isValid())
        return;

    int libro_id = m_libros->data(idx3, Qt::DisplayRole).toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Borrar libro", "Davidiano, ¿seguro que quieres borrar este libro?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "el id del libro es: " << libro_id;
        borrarLibro(libro_id);
    }

}

void dlgGestionLibros::borrarLibro(int id)
{
    QSqlQuery query;

    if (!query.exec(QString("DELETE FROM libros_autores WHERE libro_id=%1").arg(id)))
        qDebug() << "fallido borrado de libros_autores";

    if (!query.exec(QString("DELETE FROM libros_editores WHERE libro_id=%1").arg(id)))
        qDebug() << "fallido borrado de libros_editores";

    if (!query.exec(QString("DELETE FROM libros_categorias WHERE libro_id=%1").arg(id)))
        qDebug() << "fallido borrado de libros_categorias";

    if (!query.exec(QString("DELETE FROM libro WHERE libro_id=%1").arg(id)))
        qDebug() << "fallido borrado de libros";

    m_libros->setQuery(sql_activa);
    actualizarLabelTotales();

}

void dlgGestionLibros::actualizarLabelTotales()
{
    ui->lblTotal->setText(QString("Total: %1").arg(m_libros->rowCount()));

}

void dlgGestionLibros::on_rbDespacho_clicked()
{
    m_libros->setQuery(sql_despacho);
    sql_activa = sql_embajada;

}

void dlgGestionLibros::on_rbDigital_clicked()
{
    m_libros->setQuery(sql_digital);
    sql_activa = sql_embajada;

}

void dlgGestionLibros::on_pbEditar_clicked()
{
    /*
     * Joder esto es un puot lío... necesito tanto puto idx?
     */

    // esto entiendo que coge el índice del tableview...
    QModelIndex idx = ui->tvLibros->currentIndex();
    if (!idx.isValid())
        return;

    // de ahí coge el índice del model que subyace (que es un qsortfilteretc)...
    QModelIndex idx2 = idx.model()->index(idx.row(), 0);
    if (!idx2.isValid())
        return;

    // y eso lo mapea al original.
    QModelIndex idx3 = m_libros_proxy->mapToSource(idx2);
    if (!idx3.isValid())
        return;

    int libro_id = m_libros->data(idx3, Qt::DisplayRole).toInt();

    emit(modificarLibro(libro_id));
}

void dlgGestionLibros::cargarDatosDerivados(int libro_id){

    QSqlQuery query;
    // qDebug() << "escogido: " << libro_id;

    m_autores->setQuery(QString("SELECT nombre || ' ' || apellido FROM autores a JOIN libros_autores la ON a.autor_id = la.autor_id WHERE la.libro_id = %1").arg(libro_id));
    m_autores->setHeaderData(0, Qt::Horizontal, trUtf8("Autor(es)"));
    ui->tvAutores->setModel(m_autores);
    ui->tvAutores->setAlternatingRowColors(true);
    ui->tvAutores->resizeColumnsToContents();
    // ui->tvAutores->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ui->tvAutores->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvAutores->horizontalHeader()->setStretchLastSection(true);

    m_editores->setQuery(QString("SELECT nombre || ' ' || apellido FROM autores a JOIN libros_editores la ON a.autor_id = la.editor_id WHERE la.libro_id = %1").arg(libro_id));
    m_editores->setHeaderData(0, Qt::Horizontal, trUtf8("Editor(es)"));
    ui->tvEditores->setModel(m_editores);
    ui->tvEditores->setAlternatingRowColors(true);
    ui->tvEditores->resizeColumnsToContents();
    // ui->tvEditores->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ui->tvEditores->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvEditores->horizontalHeader()->setStretchLastSection(true);

    m_categorias->setQuery(QString("SELECT categoria FROM categorias c JOIN libros_categorias lc ON c.categoria_id = lc.categoria_id WHERE lc.libro_id = %1").arg(libro_id));
    m_categorias->setHeaderData(0, Qt::Horizontal, trUtf8("Categoría(s)"));
    ui->tvCategorias->setModel(m_categorias);
    ui->tvCategorias->setAlternatingRowColors(true);
    ui->tvCategorias->resizeColumnsToContents();
    // ui->tvCategorias->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ui->tvCategorias->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tvCategorias->horizontalHeader()->setStretchLastSection(true);

}

void dlgGestionLibros::seleccionarLibro(const QModelIndex &idx){

    int libro_seleccionado;

    Q_UNUSED(idx)
    // NOTE: aquí no estoy usando lo de idx... he cogido este código de lo de modificar persona...
    QModelIndex indice= m_libros_proxy->index(ui->tvLibros->currentIndex().row(), 0);
    if (!indice.isValid())
        return;

    libro_seleccionado = m_libros->data(m_libros_proxy->mapToSource(indice), Qt::DisplayRole).toInt();

    cargarDatosDerivados(libro_seleccionado);
}
