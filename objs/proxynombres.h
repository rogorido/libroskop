#ifndef PROXYNOMBRES_H
#define PROXYNOMBRES_H

#include <QSortFilterProxyModel>

class ProxyNombres : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyNombres(int tipo, QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:

    /*
       una int que nos permite usar el modelo con diversos modelos base:
       1. 0 es para los nombres de autores
       2. 1 es para los nombres de lugares
    */
    
    int tipoproxy;
};

#endif // PROXYNOMBRES_H
