#ifndef DLGGESTIONLIBROS_H
#define DLGGESTIONLIBROS_H

#include <QWidget>

class QSqlQueryModel;

namespace Ui {
class dlgGestionLibros;
}

class dlgGestionLibros : public QWidget
{
    Q_OBJECT

public:
    explicit dlgGestionLibros(QWidget *parent = nullptr);
    ~dlgGestionLibros();

private slots:
    void on_rbUniversidad_clicked();
    void on_rbTodos_clicked();
    void on_rbEmbajada_clicked();
    void on_pbBorrar_clicked();

    void borrarLibro(int id);

private:
    Ui::dlgGestionLibros *ui;

    QSqlQueryModel *m_libros;
};

#endif // DLGGESTIONLIBROS_H