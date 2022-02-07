#include "carrito.h"

Carrito::Carrito(QObject *parent) : QObject(parent)
{
    m_cantidad = 0;
}

Carrito::Carrito(Producto *pro, int cantidad)
{
    m_pro = pro;
    m_cantidad = cantidad;
}

Producto *Carrito::pro() const
{
    return m_pro;
}

void Carrito::setPro(Producto *newPro)
{
    m_pro = newPro;
}

int Carrito::cantidad() const
{
    return m_cantidad;
}

void Carrito::setCantidad(int newCantidad)
{
    m_cantidad = newCantidad;
}
