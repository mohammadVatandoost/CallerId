#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>
#include <QtCore>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/qserialport.h>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/qserialportglobal.h>
#include <QDebug>
#include <QTimer>
#include <iostream>

using namespace std;

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    QSerialPort *serial;
    QString come_port;
    QTimer *timer;
    QString temp;
    int counter = 0;
    int timerCounter = 0 ;
signals:

private slots:
    void recieve_SerialPort();
    void timerSlot();
};

#endif // BACKEND_H
