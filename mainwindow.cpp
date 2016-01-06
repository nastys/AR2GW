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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toGW_clicked()
{
    //bool ok;
    //ui->GW1->setText(QString::number(ui->AR1->text().toUInt(&ok, 16)+335544320, 16));
    //ui->GW2->setText(ui->AR2->text());
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
        result=result+QString(QString::number(num+335544320, 16))+" "+QString(tmp3.at(1))+"\n";
    }

    ui->GW->document()->setPlainText(result.trimmed());
}
