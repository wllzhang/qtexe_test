#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QWindow>
#include <Windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("Qt嵌入exe Demo");

    // 等待外部程序启动并查找窗口
    QTimer::singleShot(5000, this, &MainWindow::embedExternalWindow);
}

// 窗口枚举回调函数
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    if (IsWindowVisible(hwnd)) {
        wchar_t className[256];
        wchar_t windowTitle[256];

        GetClassName(hwnd, className, 256);
        GetWindowText(hwnd, windowTitle, 256);

        QString classNameStr = QString::fromWCharArray(className);
        QString titleStr = QString::fromWCharArray(windowTitle);

        if (!classNameStr.isEmpty() || !titleStr.isEmpty()) {
//            qDebug() << "找到窗口 - 类名:" << classNameStr << "标题:" << titleStr;
        }
    }
    return TRUE;
}

void MainWindow::embedExternalWindow()
{
//    qDebug() << "开始查找外部窗口";

//    // 首先打印所有可见窗口，帮助调试
//    qDebug() << "=== 所有可见窗口列表===";
//    EnumWindows(EnumWindowsProc, 0);
//    qDebug() << "=== 窗口列表结束===";

    // 首先尝试通过标题查找Resium窗口
    HWND hwnd = nullptr;

    qDebug() << "开始查找Resium窗口...";

    // 尝试查找包含"Resium"的窗口
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        if (IsWindowVisible(hwnd)) {
            wchar_t className[256];
            wchar_t windowTitle[256];

            GetClassName(hwnd, className, 256);
            GetWindowText(hwnd, windowTitle, 256);

            QString classNameStr = QString::fromWCharArray(className);
            QString titleStr = QString::fromWCharArray(windowTitle);

            // 打印每个窗口信息用于调试
            if (classNameStr == "Chrome_WidgetWin_1") {
//                qDebug() << "检查Chrome窗口:" << classNameStr << "标题:" << titleStr;
            }

            // 更宽松的匹配条件
            if (classNameStr == "Chrome_WidgetWin_1" &&  (titleStr.contains("Resium", Qt::CaseInsensitive)) &&  (titleStr.contains("Demo", Qt::CaseInsensitive)) ) {
//                qDebug() << "找到Resium相关窗口:" << classNameStr << titleStr;
                *(HWND*)lParam = hwnd;
                return FALSE; // 停止枚举
            }
        }
        return TRUE;
    }, (LPARAM)&hwnd);

    if (hwnd == nullptr) {
        qDebug() << "未找到Resium窗口";
        return;
    }

    // 打印找到的窗口信息
    wchar_t className[256];
    wchar_t windowTitle[256];
    GetClassName(hwnd, className, 256);
    GetWindowText(hwnd, windowTitle, 256);
    QString classNameStr = QString::fromWCharArray(className);
    QString titleStr = QString::fromWCharArray(windowTitle);
    qDebug() << "找到的窗口-句柄:" << (void*)hwnd << "类名:" << classNameStr << "标题:" << titleStr;

    // 将外部窗口嵌入到Qt窗口中
    QWindow *externalWindow = QWindow::fromWinId((WId)hwnd);
    if (externalWindow) {
        QWidget *widget = QWidget::createWindowContainer(externalWindow, this);
        widget->setGeometry(10, 10, 800, 600);
        widget->show();
        qDebug() << "窗口嵌入成功！";
    } else {
        qDebug() << "窗口嵌入失败！";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}