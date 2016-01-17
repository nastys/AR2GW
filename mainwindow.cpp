/*
 * Copyright © 2015 nastys
 *
 * This file is part of AR2GW.
 * AR2GW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AR2GW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AR2GW.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QTextStream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    offset_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toGW_clicked()
{
    QString tmp;
    tmp = ui->AR->document()->toPlainText();
    QStringList tmp2=tmp.trimmed().split("\n", QString::SkipEmptyParts);
    QString result="";
    bool ok;
    for (int i=0; i<tmp2.count(); i++)
    {
        QStringList tmp3=tmp2.at(i).split(" ", QString::SkipEmptyParts);
        int num = tmp3.at(0).toUInt(&ok, 16);
        if(num<=629145)
        {
            QMessageBox::warning(this, "Warning", "This code may not work.");
        }
        QString r1=QString::number(num+ui->cb_offset->currentData().toInt(&ok), 16);
        if(r1.count()<8)
        {
            for(int i=0; i<8-r1.count(); i++)
                r1="0"+r1;
        }
        result=result+QString(r1)+" "+QString(tmp3.at(1))+"\n";
    }

    ui->GW->document()->setPlainText(result.trimmed());
}

void MainWindow::offset_init()
{
    QFile file("offsets.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::critical(this, "Error", "Cannot open \"offsets.txt\".");

    QTextStream in(&file);

    QStringList tmp=in.readAll().trimmed().split("\n", QString::SkipEmptyParts);
    QString result="";
    for (int i=0; i<tmp.count(); i++)
    {
        QStringList tmp2=tmp.at(i).split(" ", QString::SkipEmptyParts);
        ui->cb_offset->addItem(QString(tmp2.at(0)).replace("+", " "), tmp2.at(1));
    }

    file.close();
}
