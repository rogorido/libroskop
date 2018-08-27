#include "nuevolibroentrada.h"
#include "ui_nuevolibroentrada.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

NuevoLibroEntrada::NuevoLibroEntrada(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoLibroEntrada)
{
    ui->setupUi(this);

    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarLibro()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btAnadirAutor, SIGNAL(clicked(bool)), this, SLOT(anadirAutor()));
    connect(ui->btQuitarAutor, SIGNAL(clicked(bool)), this, SLOT(quitarAutor()));
    connect(ui->btAnadirCategoria, SIGNAL(clicked(bool)), this, SLOT(anadirCategoria()));
    connect(ui->btQuitarCategoria, SIGNAL(clicked(bool)), this, SLOT(quitarCategoria()));
}

NuevoLibroEntrada::~NuevoLibroEntrada()
{
    delete ui;
}

void NuevoLibroEntrada::recibirAutor(elementopareado autor)
{
    autores.append(autor);

    QListWidgetItem *item = new QListWidgetItem(autor.elemento, ui->lwAutores);

}

void NuevoLibroEntrada::recibirCategoria(elementopareado categoria)
{
    categorias.append(categoria);

    QListWidgetItem *item = new QListWidgetItem(categoria.elemento, ui->lwCategorias);
}

void NuevoLibroEntrada::cerrar()
{
    parentWidget()->close();
}

void NuevoLibroEntrada::aceptarLibro()
{
    QSqlQuery query;

    QString titulo = ui->txtTitulo->text();
    QString subtitulo = ui->txtSubtitulo->text();
    QString editorial = ui->txtEditorial->text();
    QString year = ui->txtAno->text();
    QString lugar = ui->txtLugar->text();
    QString localizacion = ui->txtLocalizacion->text();

    query.prepare("INSERT INTO libro(titulo, subtitulo, editorial, lugar, fecha, localizacion) "
                  "VALUES(:titulo, :subtitulo, :editorial, :lugar, :fecha, :localizacion)");
    query.bindValue(":titulo", titulo);
    query.bindValue(":subtitulo", subtitulo);
    query.bindValue(":editorial", editorial);
    query.bindValue(":lugar", lugar);
    query.bindValue(":fecha", year);
    query.bindValue(":localizacion", localizacion);

    if (!query.exec()){
        qDebug() << query.lastError();
    }
    else {
        qDebug() << "geschafft";
        query.exec("SELECT seq FROM sqlite_sequence WHERE name='libro'");
        query.first();
        int ultimolibro_id = query.value(0).toInt();
        introducirAutores(ultimolibro_id);
        introducirCategorias(ultimolibro_id);
        borrarCampos();
    }
}

void NuevoLibroEntrada::anadirAutor()
{
    emit(seleccionarAutorSignal());
}

void NuevoLibroEntrada::quitarAutor()
{
    QModelIndex idx = ui->lwAutores->currentIndex();

    if (!idx.isValid())
        return;

    QString autorescogido = idx.data().toString();

    for (int var = 0; var < autores.size(); ++var) {
        if (autores.at(var).elemento == autorescogido) {
            autores.removeAt(var);
            break;
        }
    }

    ui->lwAutores->takeItem(ui->lwAutores->currentRow());

}

void NuevoLibroEntrada::anadirCategoria()
{
    emit(seleccionarCategoriaSignal());

}

void NuevoLibroEntrada::quitarCategoria()
{
    QModelIndex idx = ui->lwCategorias->currentIndex();

    if (!idx.isValid())
        return;

    QString cat_escogida = idx.data().toString();

    for (int var = 0; var < categorias.size(); ++var) {
        if (categorias.at(var).elemento == cat_escogida) {
            categorias.removeAt(var);
            break;
        }
    }

    ui->lwCategorias->takeItem(ui->lwCategorias->currentRow());
}

void NuevoLibroEntrada::introducirAutores(int id)
{
    QSqlQuery query;

    for (int var = 0; var < autores.size(); ++var) {
        query.prepare("INSERT INTO libros_autores(libro_id, autor_id) VALUES(:libro_id, :autor_id)");
        query.bindValue(":libro_id", id);
        query.bindValue(":autor_id", autores.at(var).id);
        if (!query.exec())
            qDebug() << query.lastError();
    }

}

void NuevoLibroEntrada::introducirCategorias(int id)
{
    QSqlQuery query;

    for (int var = 0; var < categorias.size(); ++var) {
        query.prepare("INSERT INTO libros_categorias(libro_id, categoria_id) VALUES(:libro_id, :categoria_id)");
        query.bindValue(":libro_id", id);
        query.bindValue(":categoria_id", categorias.at(var).id);
        if (!query.exec())
            qDebug() << query.lastError();
    }

}

void NuevoLibroEntrada::borrarCampos()
{
    ui->txtTitulo->setText("");
    ui->txtSubtitulo->setText("");
    ui->txtEditorial->setText("");
    ui->txtAno->setText("");
    ui->txtLugar->setText("");
    ui->txtLocalizacion->setText("");

    autores.clear();
    categorias.clear();

    ui->lwAutores->clear();
    ui->lwCategorias->clear();

    ui->txtTitulo->setFocus();

}

void NuevoLibroEntrada::cargarModelos()
{

}
