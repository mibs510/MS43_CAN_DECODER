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
    // TODO: Confirm each set of vid's and pid's, possibly add more?
    static const int SIZE_OF_IDS = 5;
    quint16 arduino_vendor_id[SIZE_OF_IDS] = {6790,9025,9025,10755,9025};
    quint16 arduino_product_id[SIZE_OF_IDS] = {29987,67,1,67,579};

    int odometer, last_rpm, rpm, speed, temp;
    double fuel_level ;
};

#endif // DIALOG_H
