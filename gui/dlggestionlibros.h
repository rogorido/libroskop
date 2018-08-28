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

private:
    Ui::dlgGestionLibros *ui;

    QSqlQueryModel *m_libros;
};

#endif // DLGGESTIONLIBROS_H
