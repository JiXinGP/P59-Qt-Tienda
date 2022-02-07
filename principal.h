#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QMessageBox>

#include "producto.h"
#include "carrito.h"
#include "cliente.h"
#include "factura.h"
#include "producto.h"

#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:
    void on_inProducto_currentIndexChanged(int index);

    void on_btnAgregar_clicked();

    void on_btnImprimir_clicked();

    void on_btnLimpiar_clicked();

private:
    Ui::Principal *ui;
    QList<Producto*> m_productos;
    QList<Carrito*> m_carrito;
    Cliente *m_cliente;

    float m_Subtotal;
    float totalCompras=0;
    void calcular(float stProducto);
    bool validarCedula(QString st);
    bool validarCarrito(Producto *p);
    bool validarUsuario();
    void limpiar();

};
#endif // PRINCIPAL_H
