#ifndef FACTURA_H
#define FACTURA_H

#include <QDialog>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

#include "carrito.h"
#include "cliente.h"

namespace Ui {
class Factura;
}

class Factura : public QDialog
{
    Q_OBJECT

public:
    explicit Factura(QWidget *parent = nullptr);

    ~Factura();

    void Facturacion();
    void setLista(const QList<Carrito *> &newLista);
    void setCliente(Cliente *newCliente);

private slots:

    void on_btnGuardar_released();

    void on_btnSalir_released();

private:
    Ui::Factura *ui;
    QList<Carrito*> m_lista;
    Cliente *m_cliente;
    QString m_datos;
    float m_Subtotal = 0;
    float m_Iva = 0;
    float m_Total = 0;
};

#endif // FACTURA_H
