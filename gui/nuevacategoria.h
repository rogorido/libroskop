#ifndef NUEVACATEGORIA_H
#define NUEVACATEGORIA_H

#include <QWidget>

namespace Ui {
class NuevaCategoria;
}

class NuevaCategoria : public QWidget
{
    Q_OBJECT

public:
    explicit NuevaCategoria(QWidget *parent = nullptr);
    ~NuevaCategoria();

private slots:

    void aceptarNuevaCategoria();
    void cerrar();

signals:

    void nuevaCategoriaAceptadaSignal();

private:
    Ui::NuevaCategoria *ui;
};

#endif // NUEVACATEGORIA_H
