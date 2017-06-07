#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void readSerial();
private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    QString arduino_port_name;
    QByteArray serialData;
    static const quint16 arduino_vendor_id = 6790;
    static const quint16 arduino_product_id = 29987;

    int odometer, last_rpm, rpm, speed, temp;
    double fuel_level ;
};

#endif // DIALOG_H
