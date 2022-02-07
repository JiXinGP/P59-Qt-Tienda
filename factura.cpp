#include "factura.h"
#include "ui_factura.h"

Factura::Factura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Factura)
{
    ui->setupUi(this);
    m_datos = "";
}

Factura::~Factura()
{
    delete ui;
}

void Factura::on_btnGuardar_released()
{
    QDateTime c = QDateTime::currentDateTime();
    QString nameFormat = c.toString("ddMMyyyy_hhmmss");
    QFile archivo("../" + nameFormat + ".txt");

    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear un stream de texto
        QTextStream salida(&archivo);
        salida << m_datos;

        QMessageBox::information(this,tr("Informacion"),tr("El archivo fue guardado con exito"));
    }else{
        QMessageBox::warning(this,
                             tr("Guardar datos"),
                             tr("No se pudo guardar el archivo"));
    }
    archivo.close();
}

void Factura::on_btnSalir_released()
{

    Factura::close();
}

void Factura::setLista(const QList<Carrito *> &newLista)
{
    m_lista = newLista;
}

void Factura::setCliente(Cliente *newCliente)
{
    m_cliente = newCliente;
}

void Factura::Facturacion()
{
    m_datos += tr("\n************************ FACTURA ***********************\n");
    m_datos += tr("\n******************** DATOS DEL CLIENTE *******************\n\n");
    m_datos += tr("Cedula: ") + m_cliente->cedula() + "\n";
    m_datos += tr("Nombre: ") + m_cliente->nombre() + "\n";
    m_datos += tr("Telefono: ") + m_cliente->telefono() + "\n";
    m_datos += tr("Email: ") + m_cliente->email() + "\n";
    m_datos += tr("Direccion: ") + m_cliente->direccion() + "\n";
    m_datos += tr("\n******************** DATOS DE LA COMPRA ******************\n");
    m_datos += tr("\n   Cant.\t  Descripcion\t       P.Unitario\t  Subtotal\n");

    foreach(Carrito *c, m_lista){
        float subto = c->pro()-> precio() * c->cantidad();
        m_Subtotal += subto;
        m_datos += "    " + QString::number(c->cantidad());
        m_datos += "\t  " + c->pro()->nombre();
        m_datos += "\t                       " + QString::number(c->pro()->precio());
        m_datos += "\t                   " + QString::number(subto, 'f', 2);
        m_datos += "\n";
    }
    m_datos += "\n\n\n\n\n\n\n\n\n\n";
    m_Iva = m_Subtotal * 0.12;
    m_Total = m_Iva + m_Subtotal;
    m_datos += tr("\t\t\t\tSubtotal:\t$ ") + QString::number(m_Subtotal, 'f', 2) + "\n";
    m_datos += tr("\t\t\t\tIVA:\t$ ") + QString::number(m_Iva, 'f', 2) + "\n";
    m_datos += tr("\t\t\t\tTotal:\t$ ") + QString::number(m_Total, 'f', 2) + "\n";
    ui->outFactura->setPlainText(m_datos);
}

