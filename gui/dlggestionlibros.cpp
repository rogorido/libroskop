#include "dlggestionlibros.h"
#include "ui_dlggestionlibros.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

const QString sql_general = "SELECT * FROM libro";
const QString sql_universidad = "SELECT * FROM libro WHERE localizacion='Universidad'";
const QString sql_embajada = "SELECT * FROM libro WHERE localizacion='Embajada'";

dlgGestionLibros::dlgGestionLibros(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionLibros)
{
    ui->setupUi(this);

    m_libros = new QSqlQueryModel(this);
    m_libros->setQuery(sql_general);
    ui->tvLibros->setModel(m_libros);
    ui->tvLibros->hideColumn(0); // la id
}

dlgGestionLibros::~dlgGestionLibros()
{
    delete ui;
}

void dlgGestionLibros::on_rbUniversidad_clicked()
{
    m_libros->setQuery(sql_universidad);
}

void dlgGestionLibros::on_rbTodos_clicked()
{
    m_libros->setQuery(sql_general);
}

void dlgGestionLibros::on_rbEmbajada_clicked()
{
    m_libros->setQuery(sql_embajada);
}

void dlgGestionLibros::on_pbBorrar_clicked()
{
    QSqlQuery query;
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
        if (!query.exec(QString("DELETE FROM libro WHERE libro_id=%1").arg(libro_id)))
            qDebug() << "fallido";

    }

}
