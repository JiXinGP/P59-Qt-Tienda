#ifndef CARRITO_H
#define CARRITO_H

#include <QObject>

#include "producto.h"

class Carrito : public QObject
{
    Q_OBJECT
public:
    explicit Carrito(QObject *parent = nullptr);
    Carrito(Producto *pro, int cantidad);

    Producto *pro() const;

    void setPro(Producto *newPro);
    int cantidad() const;
    void setCantidad(int newCantidad);

signals:

private:
    Producto *m_pro;
    int m_cantidad;
};

#endif // CARRITO_H
