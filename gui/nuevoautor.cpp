#include "nuevoautor.h"
#include "ui_nuevoautor.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

NuevoAutor::NuevoAutor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoAutor)
{
    ui->setupUi(this);

    connect(ui->btOK, SIGNAL(clicked(bool)), SLOT(aceptarNuevoAutor()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), SLOT(cerrar()));
}

NuevoAutor::~NuevoAutor()
{
    delete ui;
}

void NuevoAutor::aceptarNuevoAutor()
{
    QString nombre = ui->txtNombre->text();
    QString apellidos = ui->txtApellidos->text();
    QSqlQuery query;

    if (nombre.isEmpty() && apellidos.isEmpty() )
        return;

    query.prepare("INSERT INTO autores(nombre, apellido) VALUES(:nombre, :apellido)");
    query.bindValue(":nombre", nombre);
    query.bindValue(":apellido", apellidos);

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
    }
    else{
        emit(nuevoAutorAceptadoSignal());
        // por qué carajos no funciona un simple close()?
        parentWidget()->close();
    }
}

void NuevoAutor::cerrar()
{
    parentWidget()->close();
}
