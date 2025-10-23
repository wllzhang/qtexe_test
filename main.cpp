#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QWidget>
#include <QProcess>
#include <QWindow>
#include <QThread>
#include <Windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 启动Resium 3D Map Demo.exe
    QProcess *m_process = new QProcess;
    QString exePath = "D:/Program Files/Resium 3D Map Demo/Resium 3D Map Demo.exe";
    m_process->setProgram(exePath);
    m_process->start();
    
    if (!m_process->waitForStarted(5000)) {
        qDebug() << "Failed to start Resium 3D Map Demo.exe";
        qDebug() << "Error:" << m_process->errorString();
        qDebug() << "Exit code:" << m_process->exitCode();
        return -1;
    }
    
    // 等待程序完全启动
    QThread::msleep(2000);
    
    MainWindow w;
    w.show();
    return a.exec();
}