#include "nuevacategoria.h"
#include "ui_nuevacategoria.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

NuevaCategoria::NuevaCategoria(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevaCategoria)
{
    ui->setupUi(this);

    connect(ui->btOK, SIGNAL(clicked(bool)), SLOT(aceptarNuevaCategoria()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), SLOT(cerrar()));

    ui->txtCategoria->setFocus();
}

NuevaCategoria::~NuevaCategoria()
{
    delete ui;
}

void NuevaCategoria::aceptarNuevaCategoria()
{
    QString categoria = ui->txtCategoria->text();
    QSqlQuery query;

    if (categoria.isEmpty() )
        return;

    query.prepare("INSERT INTO categorias(categoria) VALUES(:categoria)");
    query.bindValue(":categoria", categoria);

    if (!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "esta es la query: " << query.executedQuery().toUtf8();
    }
    else{
        emit(nuevaCategoriaAceptadaSignal());
        // por qué carajos no funciona un simple close()?
        parentWidget()->close();
    }
}

void NuevaCategoria::cerrar()
{
    parentWidget()->close();

}
