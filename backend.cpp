#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    serial->close();
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    // timer for connection check
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    timer->start(1000);
}

void Backend::recieve_SerialPort()
{
    QByteArray data;
    data = serial->readAll();
     temp.append(data);
//    qDebug() << "qDebug" << temp;
    if(temp.contains("CallerID")) {
     if(counter == 1) {
      QStringList list = temp.split("CallerID:");
//      qDebug() << "qDebug list[1]: " << list[1];
      QStringList list2 = list[1].split(" ");
//      qDebug() << "qDebug list2[0]: " << list2[0];
      cout << list2[0].toStdString();
      temp.clear();
      counter = 0;
     } else {
         counter++;
     }
    }
}

void Backend::timerSlot()
{

    if(QSerialPortInfo::availablePorts().size()>0) {
       if(!serial->isOpen()) {
           Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
                      serial->setPortName(port.portName());
//                      qDebug() << " portName : " << port.portName();
                      //           serial->setPortName("COM11");
                                 if(serial->open(QIODevice::ReadWrite)) {
//                                   qDebug() << " conndected : ";
                                   cout << "conndected";
                                   connect(serial, SIGNAL(readyRead()), SLOT(recieve_SerialPort()));
                                   break;
                                 } else {
//                                     qDebug() << "Notconndected";
                                    if(timerCounter == 1) {
                                     cout << "Notconndected";
                                    }
                                     serial->close();
                                 }
                                 timerCounter = 1;
           }

       }
      } else {
          serial->close();
          qDebug() << "Disconndected : ";
      }

}
