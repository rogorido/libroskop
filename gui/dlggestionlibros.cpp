#include "dlggestionlibros.h"
#include "ui_dlggestionlibros.h"

#include <QSqlQueryModel>

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
