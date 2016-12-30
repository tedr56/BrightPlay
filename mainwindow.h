#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sendPlay(void);
    void sendPause(void);
    void sendResume(void);
    void sendForward(void);
    void sendBackward(void);
    void sendLoop(void);
    void sendUdp(QByteArray);

private:
    Ui::MainWindow *ui;
    QUdpSocket *m_udp;
};

#endif // MAINWINDOW_H
