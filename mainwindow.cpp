#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_udp = new QUdpSocket(this);
    //QShortcut *playShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(ui->PlayButton, SIGNAL(released()), this, SLOT(sendPlay()));
    connect(ui->PauseButton, SIGNAL(released()), this, SLOT(sendPause()));
    connect(ui->ResumeButton, SIGNAL(released()), this, SLOT(sendResume()));
    connect(ui->ForwardButton, SIGNAL(released()), this, SLOT(sendForward()));
    connect(ui->BackwardButton, SIGNAL(released()), this, SLOT(sendBackward()));
    connect(ui->LoopButton, SIGNAL(released()), this, SLOT(sendLoop()));
}


void MainWindow::sendUdp(QByteArray datagram) {
    m_udp->writeDatagram(datagram.data() , datagram.size(),  QHostAddress::Broadcast, 5000);
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
