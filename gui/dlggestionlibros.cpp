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
    m_libros->setHeaderData(6, Qt::Horizontal, trUtf8("Localización"));

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
    QModelIndex idx = ui->tvLibros->currentIndex();

    if (!idx.isValid())
        return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Borrar libro", "Davidiano, ¿seguro que quieres borrar este libro?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        int row = ui->tvLibros->currentIndex().row();
        QModelIndex idx2 = m_libros->index(row, 0);
        int libro_id = m_libros->data(idx2, Qt::DisplayRole).toInt();
        qDebug() << "el id del libro es: " << libro_id;
        borrarLibro(libro_id);
    }

}

void dlgGestionLibros::borrarLibro(int id)
{
    QSqlQuery query;

    if (!query.exec(QString("DELETE FROM libros_autores WHERE libro_id=%1").arg(id)))
        qDebug() << "fallido borrado de libros_autores";

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
