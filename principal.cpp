#include "principal.h"
#include "ui_principal.h"



Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    m_productos.append(new Producto(1, tr("Leche"), 0.80));
    m_productos.append(new Producto(2, tr("Pan"), 0.15));
    m_productos.append(new Producto(3, tr("Queso"), 2.50));
    foreach(Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }
    ui->inCedula->setFocus();
    QStringList cabecera = {tr("Cantidad"),tr("Producto"),tr("P. Unitario"),tr("Subtotal")};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    m_Subtotal = 0;
    ui->inCedula->setValidator(new QDoubleValidator(0,9999999999,0,this));
    ui->inTelefono->setValidator(new QDoubleValidator(0,9999999999,0,this));


}


Principal::~Principal()
{
    delete ui;
}

void Principal::calcular(float stProducto)
{
    m_Subtotal += stProducto;
    float iva = m_Subtotal * IVA / 100;
    float total = m_Subtotal + iva;

    ui->outSubtotal->setText(QString::number(m_Subtotal,'f',2));
    ui->outIva->setText(QString::number(iva,'f',2));
    ui->outTotal->setText(QString::number(total,'f',2));
}

void Principal::on_inProducto_currentIndexChanged(int index)
{
    float precio = m_productos.at(index)->precio();
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
    ui->inCantidad->setValue(0);
}

bool Principal::validarCedula(QString st)
{
    bool prov = true;
    int validarcedula[10];
    int validarPar[4];
    int validarImpar[5]={0};
    int sumaPar=0;
    int sumaImpar=0;
    int total;
    int numeroverificar;
    double num;

    if(st=="9999999999"){
        return true;
    }

    do
    {
        num=st.toInt();
        if(num<100000000 || num>9999999999)
        {
            prov=false;
            break;
        }

        QString p1=st.mid(0,1);
        QString p2=st.mid(1,1);
        QString p3=st.mid(2,1);
        QString p4=st.mid(3,1);
        QString p5=st.mid(4,1);
        QString p6=st.mid(5,1);
        QString p7=st.mid(6,1);
        QString p8=st.mid(7,1);
        QString p9=st.mid(8,1);
        QString p10=st.mid(9,1);

        validarcedula[0] = p1.toInt();
        validarcedula[1] = p2.toInt();
        validarcedula[2] = p3.toInt();
        validarcedula[3] = p4.toInt();
        validarcedula[4] = p5.toInt();
        validarcedula[5] = p6.toInt();
        validarcedula[6] = p7.toInt();
        validarcedula[7] = p8.toInt();
        validarcedula[8] = p9.toInt();
        validarcedula[9] = p10.toInt();

        if(validarcedula[0]>2)
        {
            prov = false;
            break;
        }

        validarPar[0] = validarcedula[1];
        validarPar[1] = validarcedula[3];
        validarPar[2] = validarcedula[5];
        validarPar[3] = validarcedula[7];
        validarImpar[0] = validarcedula[0];
        validarImpar[1] = validarcedula[2];
        validarImpar[2] = validarcedula[4];
        validarImpar[3] = validarcedula[6];
        validarImpar[4] = validarcedula[8];

        for(int i=0; i<5; i++)
        {
            validarImpar[i] = validarImpar[i] * 2;
            if(validarImpar[i] > 9)
            {
                validarImpar[i] = validarImpar[i] - 9;
            }
            sumaImpar =sumaImpar + validarImpar[i];
        }
        for(int i=0; i<4; i++)
        {
            sumaPar =sumaPar + validarPar[i];
        }

        total = sumaPar + sumaImpar;
        numeroverificar = total%10;
        if(numeroverificar==0)
        {
            if(numeroverificar == validarcedula[9])
            {
                prov=true;
                break;
            }else
            {
                prov=false;
                break;
            }
        }else if(numeroverificar != 0)
        {
            numeroverificar= 10 - numeroverificar;

            if(numeroverificar == validarcedula[9])
            {
                prov=true;
                break;
            }else
            {

                prov=false;
                break;
            }
        }

    }while(num < 100000000 || num > 9999999999 || validarcedula[0] > 2);
    return prov;

}

bool Principal::validarCarrito(Producto *p)
{
    foreach(Carrito *c, m_carrito){
        if(c->pro()->codigo() == p->codigo()){
            return true;
        }
    }
    return false;
}

bool Principal::validarUsuario()
{
    bool bandera = false;
    QString ced = ui->inCedula->text();
    if(ced == "9999999999"){
        m_cliente = new Cliente(ced,".",".",".",".");
        return true;
    }

    if(ui->inCedula->text().isEmpty()){
        bandera = true;
        ui->inCedula->setStyleSheet("background-color: rgb(217, 72, 72);");
    }
    if(ui->inNombre->text().isEmpty()){
        bandera = true;
        ui->inNombre->setStyleSheet("background-color: rgb(217, 72, 72);");
    }
    if(ui->inEmail->text().isEmpty()){
        bandera = true;
        ui->inEmail->setStyleSheet("background-color: rgb(217, 72, 72);");
    }
    if(ui->inTelefono->text().isEmpty()){
        bandera = true;
        ui->inTelefono->setStyleSheet("background-color: rgb(217, 72, 72);");
    }
    if(ui->inDireccion->text().isEmpty()){
        bandera = true;
        ui->inDireccion->setStyleSheet("background-color: rgb(217, 72, 72);");
    }
    if(bandera){
        ui->statusbar->showMessage(tr("Campos vacios"),4000);
        return false;
    }
    if(validarCedula(ced)){
        QString nombre = ui->inNombre->text();
        QString email = ui->inEmail->text();
        QString telefono = ui->inTelefono->text();
        QString direccion = ui->inDireccion->text();
        m_cliente = new Cliente(ced,nombre,telefono,email,direccion);
        return true;

    }else{
        ui->inCedula->setStyleSheet("background-color: rgb(255, 112, 119);");
        ui->statusbar->showMessage(tr("Cedula incorrecta"),4000);
        return false;
    }

    return true;
}

void Principal::limpiar()
{
    ui->inCedula->clear();
    ui->inNombre->clear();
    ui->inEmail->clear();
    ui->inTelefono->clear();
    ui->inDireccion->clear();
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    int fila = ui->outDetalle->rowCount();
    for(int i=0; i <= fila;){
        ui->outDetalle->removeRow(fila);
        fila--;
    }
    ui->inCedula->setStyleSheet("background-color: rgb(0, 80, 117);");
    ui->inNombre->setStyleSheet("background-color: rgb(0, 80, 117);");
    ui->inEmail->setStyleSheet("background-color: rgb(0, 80, 117);");
    ui->inTelefono->setStyleSheet("background-color: rgb(0, 80, 117);");
    ui->inDireccion->setStyleSheet("background-color: rgb(0, 80, 117);");
    m_Subtotal = 0;
    totalCompras = 0;
    ui->outSubtotal->setText("$ 0.0");
    ui->outIva->setText("$ 0.0");
    ui->outTotal->setText("$ 0.0");
    m_carrito.clear();
}

void Principal::on_btnAgregar_clicked()
{
    int cantidad = ui->inCantidad->value();
    if( cantidad == 0){
        return;
    }
    int i = ui->inProducto->currentIndex();
    totalCompras++;
    Producto *p = m_productos.at(i);
    if(!validarCarrito(p)){
        m_carrito.append(new Carrito(p,cantidad));

        float subTotal = p->precio() * cantidad;
        int fila = ui->outDetalle->rowCount();
        ui->outDetalle->insertRow(fila);
        ui->outDetalle->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
        ui->outDetalle->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
        ui->outDetalle->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(),'f',2)));
        ui->outDetalle->setItem(fila, 3, new QTableWidgetItem(QString::number(subTotal,'f',2)));
        ui->inCantidad->setValue(0);
        ui->inProducto->setFocus();
        calcular(subTotal);
        return;
    }else{
        int i=0;
        foreach(Carrito *c, m_carrito){
            if(c->pro()->codigo() == p->codigo()){

                float precioAntiguo = m_carrito.at(i)->cantidad() * p->precio();
                int canAnti = m_carrito.at(i)->cantidad();
                c->setCantidad(cantidad + canAnti);
                ui->outDetalle->setItem(i,0,new QTableWidgetItem(QString::number(c->cantidad())));
                float subTotal = p->precio() * cantidad;
                float subTotalUnitario = precioAntiguo + subTotal;
                ui->outDetalle->setItem(i,3,new QTableWidgetItem(QString::number(subTotalUnitario)));

                ui->inCantidad->setValue(0);
                ui->inProducto->setFocus();

                calcular(subTotal);
                break;
            }
            i++;
        }

    }

}

void Principal::on_btnImprimir_clicked()
{
    if(validarUsuario() && totalCompras != 0){
        ui->inCedula->setStyleSheet("background-color: rgb(119, 200, 112);");
        ui->inNombre->setStyleSheet("background-color: rgb(119, 200, 112);");
        ui->inEmail->setStyleSheet("background-color: rgb(119, 200, 112);");
        ui->inTelefono->setStyleSheet("background-color: rgb(119, 200, 112);");
        ui->inDireccion->setStyleSheet("background-color: rgb(119, 200, 112);");
        Factura p;
        p.setCliente(m_cliente);
        p.setLista(m_carrito);
        p.Facturacion();
        p.exec();
        limpiar();
        delete m_cliente;
    }else{
        if(totalCompras == 0)
            ui->statusbar->showMessage(tr("No hay compras"),5000);
        return;
    }
}

void Principal::on_btnLimpiar_clicked()
{
    limpiar();
}
