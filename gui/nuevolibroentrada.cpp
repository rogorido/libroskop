#include "nuevolibroentrada.h"
#include "ui_nuevolibroentrada.h"

NuevoLibroEntrada::NuevoLibroEntrada(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoLibroEntrada)
{
    ui->setupUi(this);

    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarLibro()));
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

void NuevoLibroEntrada::aceptarLibro()
{

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
