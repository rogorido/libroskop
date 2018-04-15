#include "proxynombres.h"

ProxyNombres::ProxyNombres(tiposeleccionar tipo, QObject *parent)
  : QSortFilterProxyModel(parent), tipoproxy(tipo)
{
}

bool ProxyNombres::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

  switch(tipoproxy) {
  case 0:

    return sourceModel()->data(index1).toString().contains(filterRegExp())
            || sourceModel()->data(index2).toString().contains(filterRegExp());
    break;

  case 1: // categorías

      return sourceModel()->data(index1).toString().contains(filterRegExp());
      break;

  default: // NOTE: esto no sé si es correcto así...
      return true;

  }

}
