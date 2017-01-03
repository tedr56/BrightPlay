#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QDebug>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_udp = new QUdpSocket(this);
    //QShortcut *playShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(ui->PerfButton, SIGNAL(released()), this, SLOT(sendPerf()));
    connect(ui->PlayButton, SIGNAL(released()), this, SLOT(sendPlay()));
    connect(ui->PauseButton, SIGNAL(released()), this, SLOT(sendPause()));
    connect(ui->ResumeButton, SIGNAL(released()), this, SLOT(sendResume()));
    connect(ui->ForwardButton, SIGNAL(released()), this, SLOT(sendForward()));
    connect(ui->BackwardButton, SIGNAL(released()), this, SLOT(sendBackward()));
    connect(ui->LoopButton, SIGNAL(released()), this, SLOT(sendLoop()));
    ScannInterfaces();
}


void MainWindow::sendUdp(QByteArray datagram) {
    QNetworkInterface* IF = new QNetworkInterface();
    Q_UNUSED(IF);
    //qDebug() << IF->allAddresses();
    //qDebug() << IF->addressEntries();
    QHostAddress Ip = QHostAddress(ui->comboBox->currentText());
    m_udp->writeDatagram(datagram.data() , datagram.size(),  Ip, 5000);
    //m_udp->writeDatagram(datagram.data() , datagram.size(),  QHostAddress::Broadcast, 5000);
}

void MainWindow::ScannInterfaces()
{
    QNetworkInterface* IF = new QNetworkInterface();
    QList<QNetworkInterface> IFs = IF->allInterfaces();
    foreach (QNetworkInterface interface, IFs) {

        QList<QNetworkAddressEntry> entries = interface.addressEntries();

        foreach (QNetworkAddressEntry entry, entries) {
            QHostAddress ip = entry.ip();
            if (ip.protocol() == QAbstractSocket::IPv4Protocol) {
                if (!ip.isLoopback()) {
                    ui->comboBox->addItem(entry.broadcast().toString());
                }
            }
            qDebug() << entry.ip().toString();
        }
    }
    if (ui->comboBox->count() > 1) {
        ui->comboBox->removeItem(0);
    }
    ui->comboBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendPlay()
{
    sendUdp("playvideo");
}

void MainWindow::sendPause()
{
    sendUdp("pausevideo");
}

void MainWindow::sendResume()
{
    sendUdp("resumevideo");
}

void MainWindow::sendForward()
{
    sendUdp("seekforward");
}

void MainWindow::sendBackward()
{
    sendUdp("seekbackward");
}

void MainWindow::sendLoop()
{
    sendUdp("loopvideo");
}

void MainWindow::sendPerf()
{
    sendUdp("perfvideo")
}
