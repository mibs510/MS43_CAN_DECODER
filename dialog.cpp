#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->fuel_lcdNumber->display("--");
    ui->rpm_lcdNumber->display("----");
    ui->odometer_lcdNumber->display("------");
    ui->speed_lcdNumber->display("--");
    ui->temperature_lcdNumber->display("--");

    arduino = new QSerialPort(this);
    QString arduino_port_name;
    bool arduino_available = false;

    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if (serialPortInfo.hasVendorIdentifier())
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        if (serialPortInfo.hasProductIdentifier())
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        if ((serialPortInfo.vendorIdentifier() == arduino_vendor_id) && (serialPortInfo.productIdentifier() == arduino_product_id)){
            arduino_available = true;
            qDebug() << "Opening " << serialPortInfo.portName();
            arduino->setPortName(serialPortInfo.portName());
            arduino->open(QSerialPort::ReadOnly);
            arduino->setBaudRate(QSerialPort::Baud115200);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            arduino->setFlowControl(QSerialPort::NoFlowControl);
            QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
        }
    }
    if (!arduino_available)
        QMessageBox::warning(this, "Hardware error!", "Couldn't find available arduino!");
}

Dialog::~Dialog()
{
    delete ui;
    if (arduino->isOpen())
        arduino->close();
}

void Dialog::readSerial(){
    serialData = arduino->readLine();
    //qDebug() << serialData;
    QString ourStringdata = QString::fromStdString(serialData.toStdString());
    ourStringdata.remove("\r\n");
    //qDebug() << ourStringdata;
    QStringList canbusByte = ourStringdata.split(",");
    if (canbusByte[0] == "1555"){
        fuel_level = (canbusByte[3].toDouble() / 50) * 100;
        ui->fuel_lcdNumber->display(fuel_level);
        qDebug() << "fuel_level = " << fuel_level;
        odometer = ((((canbusByte[2].toInt() * 256) + canbusByte[1].toInt()) * 10) / 1.609344);
        ui->odometer_lcdNumber->display(odometer);
        qDebug() << "odometer = " << odometer;
      }
    if (canbusByte[0] == "790"){
        rpm = (((canbusByte[4].toInt() * 256) + canbusByte[3].toInt()) / 6.42);

        ui->rpm_lcdNumber->display(rpm);
        qDebug() << "rpm = " << rpm;
    }
    if (canbusByte[0] == "339"){
        speed = (((canbusByte[3].toInt() * 256) + canbusByte[2].toInt()) / 128);
        ui->speed_lcdNumber->display(speed);
        qDebug() << "speed = " << speed;
    }
    if (canbusByte[0] == "809"){
        temp = ((.75 * canbusByte[2].toInt()) - 48.373);
        ui->temperature_lcdNumber->display(temp);
        qDebug() << "temp = " << temp;
    }
        qDebug() << canbusByte;
    canbusByte.clear();
}
