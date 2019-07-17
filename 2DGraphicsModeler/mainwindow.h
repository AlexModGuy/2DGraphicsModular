#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QMessageBox>
#include "renderarea.h"
#include "adminlogin.h"
#include "contact.h"
#include "palette.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ShapeBuffer buffer;
    RenderArea *renderArea;
    QTime timeDifference (const QTime&, const QTime&);

private slots:
    void on_actionLogin_triggered();
    void on_actionContact_Us_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    
protected:
    void timerEvent (QTimerEvent* event);

private:
    Ui::MainWindow *ui;
    adminLogin *admin;
    Contact    *contact;
    Palette    *palette;
    QTime initialTime;
};

#endif // MAINWINDOW_H
