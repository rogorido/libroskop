#include "dlgseleccionargeneral.h"
#include "ui_dlgseleccionargeneral.h"

#include "objs/proxynombres.h"

#include <QInputDialog>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QModelIndex>
#include <QDebug>

dlgSeleccionarGeneral::dlgSeleccionarGeneral(int tipo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlgSeleccionarGeneral), tipo_dialogo(tipo)
{
    ui->setupUi(this);

    cargarTipo();
    cargarModelo();
    cargarTituloVentana();

    connect(ui->btAnadir, SIGNAL(clicked(bool)), this, SLOT(anadirObjeto()));
    connect(ui->txtFiltro, SIGNAL(textEdited(QString)), this, SLOT(actualizarFiltro(QString)));
    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptar()));
    connect(ui->twSeleccionar, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(aceptar()));
    connect(ui->twSeleccionar, SIGNAL(clicked(const QModelIndex &)), this, SLOT(seleccionarObjeto(QModelIndex)));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(close()));

    ui->txtFiltro->setFocus();
}

dlgSeleccionarGeneral::~dlgSeleccionarGeneral()
{
    delete ui;
}

void dlgSeleccionarGeneral::cargarTipo(){
    m_objeto = new QSqlQueryModel(this);

    switch (tipo_dialogo) {
    case 0:{
        sql_general = "SELECT * FROM autores ORDER BY apellido";
        ui->btAnadir->setText("Aña&dir autor");
        break;}
    case 1:{
        sql_general = "SELECT * FROM categorias ORDER BY categoria";
        ui->btAnadir->setText("Aña&dir categoría");
        break;}
    default:
        break;
    }

    m_objeto->setQuery(sql_general);
}

void dlgSeleccionarGeneral::cargarTituloVentana()
{
    switch (tipo_dialogo) {
    case 0:
        setWindowTitle("Seleccionar autor");
        break;
    case 1:
        setWindowTitle("Seleccionar categoría");
        break;
    default:
        break;
    }
}

void dlgSeleccionarGeneral::cargarModelo(){

    m_objeto_proxy = new ProxyNombres(tipo_dialogo, this);
    m_objeto_proxy->setSourceModel(m_objeto);

    ui->twSeleccionar->setModel(m_objeto_proxy);
    ui->twSeleccionar->hideColumn(0);
    ui->twSeleccionar->setAlternatingRowColors(true);
    ui->twSeleccionar->resizeColumnsToContents();
    ui->twSeleccionar->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twSeleccionar->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twSeleccionar->resizeRowsToContents();

    // escogemos la primera línea...
    QModelIndex index = m_objeto_proxy->index(0,0);
    ui->twSeleccionar->setCurrentIndex(index);

}


void dlgSeleccionarGeneral::actualizarFiltro(const QString filtro){

    if (filtro.length() > 2) {
        m_objeto_proxy->setFilterRegExp(QRegExp(filtro, Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twSeleccionar->resizeRowsToContents();
    }
    else
    {
        m_objeto_proxy->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
        ui->twSeleccionar->resizeRowsToContents();
    }
}

void dlgSeleccionarGeneral::seleccionarObjeto(const QModelIndex &idx)
{
    /*
     * sacamos el índice de la columna 0 que es donde está
     * la id de la resolución, para luego convertirla en int
     * y usarla en el filtro del otro modelo.
     */
    QModelIndex indice = idx.model()->index(idx.row(), 0);
    if (!indice.isValid())
        return;

    QModelIndex indice_verdadero = m_objeto_proxy->mapToSource(indice);

    //persona_id = m_objeto->data(indice_verdadero, Qt::DisplayRole).toInt();
}

void dlgSeleccionarGeneral::aceptar(){

    // esto es un poco absurdo, tiene que haber otra manera...
    switch (tipo_dialogo) {
    case 0:
        autor();
        break;
    case 1:
        categoria();
        break;
    default:
        break;
    }

    close();
}

void dlgSeleccionarGeneral::autor(){

    elementopareado autorescogido;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);
    QModelIndex idx2 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 2);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombre = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();
    QString apellido = m_objeto->data(m_objeto_proxy->mapToSource(idx2), Qt::DisplayRole).toString();

    QString nombrecompleto = apellido + QString(', ') + nombre;

    autorescogido.id = id;
    autorescogido.elemento = nombrecompleto;

    emit(autorEscogidoSignal(autorescogido));
}

void dlgSeleccionarGeneral::categoria(){

    elementopareado categoriaescogida;

    // tiene que haber otra manera de hacer esto...
    QModelIndex idx0 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 0);
    QModelIndex idx1 = m_objeto_proxy->index(ui->twSeleccionar->currentIndex().row(), 1);

    if (!idx0.isValid())
        return;

    int id = m_objeto->data(m_objeto_proxy->mapToSource(idx0), Qt::DisplayRole).toInt();
    QString nombrecategoria = m_objeto->data(m_objeto_proxy->mapToSource(idx1), Qt::DisplayRole).toString();

    categoriaescogida.id = id;
    categoriaescogida.elemento = nombrecategoria;

    emit(categoriaEscogidaSignal(categoriaescogida));
}

void dlgSeleccionarGeneral::anadirObjeto(){

    switch (tipo_dialogo) {
    case 0:{
        emit(anadirNuevoAutorSignal());
        break;}
    case 1:{
        emit(anadirNuevaCategoriaSignal());
        break;}
    default:
        break;
    }

}

void dlgSeleccionarGeneral::actualizarObjeto(){

    m_objeto->setQuery(sql_general);
    ui->twSeleccionar->resizeRowsToContents();
}

void dlgSeleccionarGeneral::actualizarAutores(){

}

void dlgSeleccionarGeneral::actualizarCategorias(){

}

/*

void dlgSeleccionarGeneral::comprobarVacio()
{
    if (m_objeto->rowCount() == 0){
        qDebug() << "cerrando...";
        close();
    }
}

*/
