#include "nuevolibroentrada.h"
#include "ui_nuevolibroentrada.h"

NuevoLibroEntrada::NuevoLibroEntrada(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoLibroEntrada)
{
    ui->setupUi(this);
}

NuevoLibroEntrada::~NuevoLibroEntrada()
{
    delete ui;
}
