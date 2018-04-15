#ifndef NUEVOAUTOR_H
#define NUEVOAUTOR_H

#include <QWidget>

namespace Ui {
class NuevoAutor;
}

class NuevoAutor : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoAutor(QWidget *parent = 0);
    ~NuevoAutor();

private slots:

    void aceptarNuevoAutor();

signals:

    void nuevoAutorAceptadoSignal();

private:
    Ui::NuevoAutor *ui;
};

#endif // NUEVOAUTOR_H
