# Qt嵌入外部exe程序窗口 Demo

## 项目概述

这是一个Qt项目演示，展示了如何将外部的Resium 3D Map Demo.exe程序窗口嵌入到Qt主窗口中。该项目使用Windows API来实现窗口查找和嵌入功能。

## 主要功能

- **自动启动外部程序**: 程序启动时自动运行Resium 3D Map Demo.exe
- **智能窗口查找**: 使用多种方法查找目标窗口（Chrome_WidgetWin_1类名）
- **窗口嵌入**: 将找到的外部窗口嵌入到Qt主窗口中
- **调试信息**: 提供详细的调试输出，帮助定位问题

## 技术特点

- 使用Qt框架进行GUI开发
- 使用Windows API进行窗口操作
- 支持窗口枚举和查找
- 跨进程窗口嵌入

## 文件结构

```
qtexe_test/
├── main.cpp              # 主程序入口，负责启动外部exe程序
├── mainwindow.h          # 主窗口类头文件
├── mainwindow.cpp        # 主窗口类实现，包含窗口嵌入逻辑
├── mainwindow.ui         # Qt Designer界面文件
├── qtexe_test.pro        # Qt项目配置文件
├── qtexe_test.pro.user   # Qt Creator用户配置文件
├── .gitignore           # Git忽略文件配置
└── README.md            # 项目说明文档
```

## 环境要求

- **操作系统**: Windows 10/11
- **Qt版本**: Qt 5.x 或 Qt 6.x
- **编译器**: MSVC 或 MinGW
- **外部程序**: Resium 3D Map Demo.exe

## 编译和运行

### 1. 环境准备
确保已安装Qt开发环境，并配置好编译工具链。

### 2. 编译项目
```cmd
qmake qtexe_test.pro
nmake  # 或者 mingw32-make
```

### 3. 运行程序
```cmd
qtexe_test.exe
```

## 程序流程

1. 启动Qt应用程序
2. 自动启动Resium 3D Map Demo.exe
3. 等待2秒让外部程序完全启动
4. 查找目标窗口（Chrome_WidgetWin_1类名，包含"Resium"和"Demo"关键词）
5. 将找到的窗口嵌入到Qt主窗口中

## 窗口查找策略

程序使用以下策略查找目标窗口：
1. 查找类名为"Chrome_WidgetWin_1"的窗口
2. 窗口标题必须包含"Resium"关键词（不区分大小写）
3. 窗口标题必须包含"Demo"关键词（不区分大小写）
4. 如果找不到符合条件的窗口，会输出调试信息

## 调试信息

程序会输出详细的调试信息到控制台：
- 外部程序启动状态
- 窗口查找过程
- 嵌入操作结果
- 找到的窗口详细信息

## 配置说明

### 外部程序路径
在 `main.cpp` 中修改外部程序的路径：
```cpp
QString exePath = "D:/Program Files/Resium 3D Map Demo/Resium 3D Map Demo.exe";
```

### 等待时间
可以调整程序等待外部程序启动的时间：
```cpp
QThread::msleep(2000);  // 等待2秒
```

## 注意事项

1. **路径配置**: 确保Resium 3D Map Demo.exe的路径正确
2. **启动顺序**: 外部程序需要完全启动后才能被嵌入
3. **窗口类名**: 如果目标程序的窗口类名不是"Chrome_WidgetWin_1"，需要修改查找逻辑
4. **权限要求**: 程序可能需要管理员权限来操作其他进程的窗口

## 故障排除

### 问题1: 找不到目标窗口
**解决方案**:
1. 查看调试输出中的窗口信息
2. 确认外部程序已完全启动
3. 检查窗口类名和标题是否正确
4. 调整等待时间

### 问题2: 外部程序启动失败
**解决方案**:
1. 检查exe文件路径是否正确
2. 确认exe文件存在且可执行
3. 检查是否有权限问题

### 问题3: 窗口嵌入失败
**解决方案**:
1. 确认目标窗口句柄有效
2. 检查Qt窗口容器是否正确设置
3. 确认Windows API调用成功

## 扩展功能

可以考虑添加以下功能：
- 支持多个外部程序窗口嵌入
- 添加窗口大小调整功能
- 实现窗口拖拽功能
- 添加窗口状态监控

## 许可证

本项目仅供学习和演示使用。

## 贡献

欢迎提交Issue和Pull Request来改进这个项目。

## 联系方式

如有问题或建议，请通过GitHub Issues联系。