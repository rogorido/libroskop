#include "dlggestionlibros.h"
#include "ui_dlggestionlibros.h"

#include <QSqlQueryModel>

const QString sql_general = "SELECT * FROM libro";

dlgGestionLibros::dlgGestionLibros(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgGestionLibros)
{
    ui->setupUi(this);

    m_libros = new QSqlQueryModel(this);
    m_libros->setQuery(sql_general);
    ui->tvLibros->setModel(m_libros);
}

dlgGestionLibros::~dlgGestionLibros()
{
    delete ui;
}

void dlgGestionLibros::on_rbUniversidad_clicked()
{

}
