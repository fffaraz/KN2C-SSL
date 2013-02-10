
#include "serialport.h"

SerialPort::SerialPort(const QString & portName, QObject *parent) :
    QObject(parent)
{
    qDebug() << "Serialport Initialization...";
    this->port = new QextSerialPort(portName, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD19200);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);

    if (port->open(QIODevice::ReadWrite) == true) {
        connect(port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(port, SIGNAL(dsrChanged(bool)), this, SLOT(onDsrChanged(bool)));
        if (!(port->lineStatus() & LS_DSR))
            qDebug() << "warning: device is not turned on";
        qDebug() << "listening for data on" << port->portName();
    }
    else {
        qDebug() << "device failed to open:" << port->errorString();
    }
    qDebug() << "\n";
}

void SerialPort::onReadyRead()
{
    QByteArray bytes;
    int a = port->bytesAvailable();
    bytes.resize(a);
    port->read(bytes.data(), bytes.size());
    //qDebug() << "bytes read:" << bytes.size();
    qDebug() << "serial read data [" << bytes.size() << "]: " << bytes.toHex();
}

void SerialPort::onDsrChanged(bool status)
{
    if (status)
        qDebug() << "device was turned on";
    else
        qDebug() << "device was turned off";
}

QString SerialPort::ListPorts()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    QTextStream output(new QString("\n"));
    output << "List of ports:" << endl;
    for (int i = 0; i < ports.size(); i++)
    {
        output << "port name:" << ports.at(i).portName << endl;
        output << "friendly name:" << ports.at(i).friendName << endl;
        output << "physical name:" << ports.at(i).physName << endl;
        output << "enumerator name:" << ports.at(i).enumName << endl;
        output << "vendor ID:" << QString::number(ports.at(i).vendorID, 16) << endl;
        output << "product ID:" << QString::number(ports.at(i).productID, 16) << endl;
        output << "=====================================" << endl;
    }
    //qDebug() << *output.string();
    return *output.string();
}
