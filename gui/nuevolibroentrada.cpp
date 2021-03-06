#include "nuevolibroentrada.h"
#include "ui_nuevolibroentrada.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QSqlQueryModel>
#include <QCompleter>

const QString sql_editoriales = "SELECT DISTINCT editorial FROM libro ORDER BY editorial";
const QString sql_lugares = "SELECT DISTINCT lugar FROM libro ORDER BY lugar";
const QString sql_lenguas = "SELECT DISTINCT lengua FROM libro ORDER BY lengua";

NuevoLibroEntrada::NuevoLibroEntrada(int libro_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoLibroEntrada)
{
    ui->setupUi(this);

    cargarModelos();

    connect(ui->btOK, SIGNAL(clicked(bool)), this, SLOT(aceptarLibro()));
    connect(ui->btCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->btAnadirAutor, SIGNAL(clicked(bool)), this, SLOT(anadirAutor()));
    connect(ui->btQuitarAutor, SIGNAL(clicked(bool)), this, SLOT(quitarAutor()));
    connect(ui->btAnadirEditor, SIGNAL(clicked(bool)), this, SLOT(anadirEditor()));
    connect(ui->btQuitarEditor, SIGNAL(clicked(bool)), this, SLOT(quitarEditor()));
    connect(ui->btAnadirCategoria, SIGNAL(clicked(bool)), this, SLOT(anadirCategoria()));
    connect(ui->btQuitarCategoria, SIGNAL(clicked(bool)), this, SLOT(quitarCategoria()));

    if (libro_id != 0) {
        libro_modificandi = libro_id;
        modificando = true;
        cargarLibro();
    }
}

NuevoLibroEntrada::~NuevoLibroEntrada()
{
    delete ui;
}

void NuevoLibroEntrada::recibirAutor(elementopareado autor)
{
    autores.append(autor);

    QListWidgetItem *item = new QListWidgetItem(autor.elemento, ui->lwAutores);
    Q_UNUSED(item)
}

void NuevoLibroEntrada::recibirEditor(elementopareado editor)
{
    editores.append(editor);

    QListWidgetItem *item = new QListWidgetItem(editor.elemento, ui->lwEditores);
    Q_UNUSED(item)

}

void NuevoLibroEntrada::recibirCategoria(elementopareado categoria)
{
    categorias.append(categoria);

    QListWidgetItem *item = new QListWidgetItem(categoria.elemento, ui->lwCategorias);
    Q_UNUSED(item)
}

void NuevoLibroEntrada::cerrar()
{
    parentWidget()->close();
}

void NuevoLibroEntrada::aceptarLibro()
{
    QSqlQuery query;
    int ultimolibro_id;

    QString titulo = ui->txtTitulo->text();
    QString subtitulo = ui->txtSubtitulo->text();
    QString editorial = ui->txtEditorial->text();
    QString year = ui->txtAno->text();
    QString lugar = ui->txtLugar->text();
    QString lengua = ui->txtLengua->text();
    QString localizacion = ui->txtLocalizacion->text();

    // Primero hacemos el caso de que sea libro nuevo...

    if (!modificando) {
        query.prepare("INSERT INTO libro(titulo, subtitulo, editorial, lugar, fecha, lengua, localizacion) "
                      "VALUES(:titulo, :subtitulo, :editorial, :lugar, :fecha, :lengua, :localizacion)");
         }
    else {
        query.prepare("UPDATE libro SET titulo = :titulo, subtitulo = :subtitulo, editorial = :editorial, "
                      "lugar = :lugar, fecha = :fecha, lengua = :lengua, localizacion = :localizacion "
                      "WHERE libro_id = :id");
         }

    query.bindValue(":titulo", titulo);
    query.bindValue(":subtitulo", subtitulo);
    query.bindValue(":editorial", editorial);
    query.bindValue(":lugar", lugar);
    query.bindValue(":fecha", year);
    query.bindValue(":lengua", lengua);
    query.bindValue(":localizacion", localizacion);

    if (modificando)
        query.bindValue(":id", libro_modificandi);

    if (!query.exec()){
        qDebug() << query.lastError();
    }
    else {
        if (modificando)
            qDebug() << trUtf8("libro modificado con éxito!");
        else
            qDebug() << trUtf8("libro introducido con éxito!");

        if (!modificando) {
            query.exec("SELECT seq FROM sqlite_sequence WHERE name='libro'");
            query.first();
            ultimolibro_id = query.value(0).toInt();
        }
        else
            ultimolibro_id = libro_modificandi;

        introducirAutores(ultimolibro_id);
        introducirEditores(ultimolibro_id);
        introducirCategorias(ultimolibro_id);

        if (!modificando)
            borrarCampos();
        else
            parentWidget()->close();
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

void NuevoLibroEntrada::anadirEditor()
{
    emit(seleccionarEditorSignal());
}

void NuevoLibroEntrada::quitarEditor()
{
    QModelIndex idx = ui->lwEditores->currentIndex();

    if (!idx.isValid())
        return;

    QString editorescogido = idx.data().toString();

    for (int var = 0; var < editores.size(); ++var) {
        if (editores.at(var).elemento == editorescogido) {
            editores.removeAt(var);
            break;
        }
    }

    ui->lwEditores->takeItem(ui->lwEditores->currentRow());

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
    QString sql;

    sql = QString("DELETE FROM libros_autores WHERE libro_id = %1").arg(id);

    if (modificando)
        query.exec(sql);

    for (int var = 0; var < autores.size(); ++var) {
        query.prepare("INSERT INTO libros_autores(libro_id, autor_id) VALUES(:libro_id, :autor_id)");
        query.bindValue(":libro_id", id);
        query.bindValue(":autor_id", autores.at(var).id);
        if (!query.exec())
            qDebug() << query.lastError();
    }

}

void NuevoLibroEntrada::introducirEditores(int id)
{
    QSqlQuery query;
    QString sql;

    sql = QString("DELETE FROM libros_editores WHERE libro_id = %1").arg(id);

    if (modificando)
        query.exec(sql);

    for (int var = 0; var < editores.size(); ++var) {
        query.prepare("INSERT INTO libros_editores(libro_id, editor_id) VALUES(:libro_id, :editor_id)");
        query.bindValue(":libro_id", id);
        query.bindValue(":editor_id", editores.at(var).id);
        if (!query.exec())
            qDebug() << query.lastError();
    }

}

void NuevoLibroEntrada::introducirCategorias(int id)
{
    QSqlQuery query;
    QString sql;

    sql = QString("DELETE FROM libros_categorias WHERE libro_id = %1").arg(id);

    if (modificando)
        query.exec(sql);

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
    ui->txtLengua->setText("");
    ui->txtLocalizacion->setText("");

    autores.clear();
    editores.clear();
    categorias.clear();

    ui->lwAutores->clear();
    ui->lwEditores->clear();
    ui->lwCategorias->clear();

    ui->txtTitulo->setFocus();

}

void NuevoLibroEntrada::cargarModelos()
{
    m_editoriales = new QSqlQueryModel(this);
    m_editoriales->setQuery(sql_editoriales);

    c_editoriales = new QCompleter(m_editoriales, this);
    c_editoriales->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtEditorial->setCompleter(c_editoriales);

    m_lugares = new QSqlQueryModel(this);
    m_lugares->setQuery(sql_lugares);

    c_lugares = new QCompleter(m_lugares, this);
    c_lugares->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLugar->setCompleter(c_lugares);

    m_lenguas = new QSqlQueryModel(this);
    m_lenguas->setQuery(sql_lenguas);

    c_lenguas = new QCompleter(m_lenguas, this);
    c_lenguas->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLengua->setCompleter(c_lenguas);

    m_localizaciones << "Biblioteca" << "Embajada" << "Despacho" << "Digital";
    c_localizaciones = new QCompleter(m_localizaciones, this);
    c_localizaciones->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtLocalizacion->setCompleter(c_localizaciones);

}

void NuevoLibroEntrada::cargarLibro()
{
    QSqlQuery query, query2;
    QString sql, sql2;
    elementopareado autor;
    elementopareado editor;
    elementopareado categoria;

    sql = QString("SELECT * FROM libro WHERE libro_id = %1").arg(libro_modificandi);
    if (!query.exec(sql))
        qDebug() << query.lastError();

    query.first();

    ui->txtTitulo->setText(query.value(1).toString());
    ui->txtSubtitulo->setText(query.value(2).toString());
    ui->txtEditorial->setText(query.value(3).toString());
    ui->txtLugar->setText(query.value(4).toString());
    ui->txtAno->setText(query.value(5).toString());
    ui->txtLengua->setText(query.value(6).toString());
    ui->txtLocalizacion->setText(query.value(7).toString());

    sql = QString("SELECT * FROM libros_autores WHERE libro_id = %1").arg(libro_modificandi);
    if (!query.exec(sql))
        qDebug() << query.lastError();

    while (query.next()) {
        autor.id = query.value(2).toInt();

        // Extraemos nombre y apellidos...
        sql2 = QString("SELECT autor_id, nombre || ' ' || apellido FROM autores WHERE autor_id = %1").arg(autor.id);
        if (!query2.exec(sql2)){
            qDebug() << query2.lastError();
            return;
        }

        query2.first();
        autor.elemento = query2.value(1).toString();
        autores.append(autor);
        QListWidgetItem *item = new QListWidgetItem(autor.elemento, ui->lwAutores);
        Q_UNUSED(item)
    }

    /*
      Ahora los editores.
    */

    sql = QString("SELECT * FROM libros_editores WHERE libro_id = %1").arg(libro_modificandi);
    if (!query.exec(sql))
        qDebug() << query.lastError();

    while (query.next()) {
        autor.id = query.value(2).toInt();

        // Extraemos nombre y apellidos...
        sql2 = QString("SELECT autor_id, nombre || ' ' || apellido FROM autores WHERE autor_id = %1").arg(autor.id);
        if (!query2.exec(sql2)){
            qDebug() << query2.lastError();
            return;
        }

        query2.first();
        editor.elemento = query2.value(1).toString();
        editores.append(editor);
        QListWidgetItem *item = new QListWidgetItem(editor.elemento, ui->lwEditores);
        Q_UNUSED(item)
    }

    /*
      Ahora las categorías.
    */

    sql = QString("SELECT * FROM libros_categorias WHERE libro_id = %1").arg(libro_modificandi);
    if (!query.exec(sql))
        qDebug() << query.lastError();

    while (query.next()) {
        categoria.id = query.value(2).toInt();

        // Extraemos nombre y apellidos...
        sql2 = QString("SELECT * FROM categorias WHERE categoria_id = %1").arg(categoria.id);
        if (!query2.exec(sql2)){
            qDebug() << query2.lastError();
            return;
        }

        query2.first();
        categoria.elemento = query2.value(1).toString();
        categorias.append(categoria);
        QListWidgetItem *item = new QListWidgetItem(categoria.elemento, ui->lwCategorias);
        Q_UNUSED(item)

    }



}
