#ifndef NUEVOLIBROENTRADA_H
#define NUEVOLIBROENTRADA_H

#include <QWidget>

namespace Ui {
class NuevoLibroEntrada;
}

class NuevoLibroEntrada : public QWidget
{
    Q_OBJECT

public:
    explicit NuevoLibroEntrada(QWidget *parent = 0);
    ~NuevoLibroEntrada();

private:
    Ui::NuevoLibroEntrada *ui;
};

#endif // NUEVOLIBROENTRADA_H
