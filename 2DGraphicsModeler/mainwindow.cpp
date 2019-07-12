#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = new RenderArea(this);
}

void MainWindow::pushBufferToRenderArea()
{

}

bool MainWindow::loadShapes()
{
    bool loaded = false;
    bool corrupt = false;
    while(loaded==false)//This is just a placeholder
        //It simiulates the flag until it finishes reading
        //it the file/buffer
    {
        ShapeBuffer parentBuffer;
        /*
         Code to read input into the buffer
         should have a way to trip
         corrupt flag in event
         of txt corruption.
         */
        renderArea->passBuffer(parentBuffer);
        if(corrupt == true)
            return false;
        loaded=true;
    }
return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLogin_triggered()
{
    admin = new adminLogin(this);
    admin -> show();
}

void MainWindow::on_TestAddShape_released()
{
    renderArea->tripFlag();
    renderArea->update();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath=QFileDialog::getOpenFileName(this, "save.txt");
    QDir d = QFileInfo(filePath).absoluteDir();
    QString absolute=d.absolutePath();
    //todo implement load all shapes from QFileInfo
}

void MainWindow::on_actionSave_triggered()
{
    QString path = QFileDialog::getSaveFileName(nullptr, tr("Save"), ".txt");
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    //todo write entire shape vector to QFile
    file.write("testing");
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
