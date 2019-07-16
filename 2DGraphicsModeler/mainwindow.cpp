#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <iostream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        
    initialTime = QTime::currentTime ();
        
    startTimer (1000);
        
    renderArea = new RenderArea(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

QTime MainWindow::timeDifference (const QTime& begin, const QTime& end)
{
    int tempHour = 0;
    int tempMinute = 0;
    int tempSecond = 0;

    tempHour = end.hour() - begin.hour();
    if (tempHour < 0)
        tempHour = 24 + tempHour;

    tempMinute = end.minute() - begin.minute();
    if (tempMinute < 0)
    {
        tempMinute = 60 + tempMinute;
        tempHour--;
    }

    tempSecond = end.second() - begin.second();
    if (tempSecond < 0)
    {
        tempSecond = 60 + tempSecond;
        tempMinute--;
    }

    return QTime (tempHour, tempMinute, tempSecond);
}

void MainWindow::timerEvent (QTimerEvent* event)
{
    /*CONTINUOUS TIME COUNT IN WINDOW TITLE*/
    QString temp = "2D-SHAPE MODELER : [" + QTime::currentTime ().toString ("hh:mm:ss") + "]";
    setWindowTitle (temp);
}


void MainWindow::on_actionLogin_triggered()
{
    admin = new adminLogin(this);
    admin -> show();
}

void MainWindow::on_actionContact_Us_triggered()
{
    contact = new Contact(this);
    contact -> show();
}




void MainWindow::on_actionOpen_triggered()
{
    QString path=QFileDialog::getOpenFileName(this, "save.txt");
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream instream(&file);
       // pass qtextstream object;
    }

}

void MainWindow::on_actionSave_triggered()
{
    QString path = QFileDialog::getSaveFileName(nullptr, tr("Save"), ".txt");
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    custom::vector<Shape*> shapeVector = renderArea->shapeVector;
    std::stringstream ss;
    for(Shape* shape : shapeVector){
        shape->write(ss);
        ss << std::endl;
    }
    std::string str = ss.str();
    file.write(str.c_str());
}

void MainWindow::on_actionQuit_triggered()
{
    /*GET CURRENT LOGOUT TIME*/
    QTime endTime = QTime::currentTime ();
    
    /*PERTINENT TIME INFO TO TRANSLATE TO STRING*/
    QString temp = "LOGIN TIME     : [" + initialTime.toString ("hh:mm:ss") + "]\nLOGOUT TIME : [" + endTime.toString ("hh:mm:ss") + "]";
    QString temp2 = "\nElapsed time: " + timeDifference(initialTime,endTime).toString("hh:mm:ss");
    
    /*SETTING MESSAGE BOX INFO*/
    QMessageBox msgbox;
    msgbox.setText(temp + '\n' + temp2);
    msgbox.exec ();
    
    QApplication::quit();
}
