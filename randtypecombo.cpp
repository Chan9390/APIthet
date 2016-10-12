/*
 *  Copyright [2016] [mail.gulpfriction@gmail.com]
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

//Set the correct Encoding
void MainWindow::setRandTypes()
{
    QComboBox *comboBoxRandParams = ui->comboBoxRandParam;
    QStringList randParamList;

    //Add HTTP Methods to the list
    randParamList << "NONE" << "Name" << "Name Surname" << "Email" << "Website" << "IP Address" << "Phone Number";

    //Assign the string list to the combobox
    comboBoxRandParams->addItems(randParamList);
}

void MainWindow::comboBoxRandParamSlot()
{
    ui->comboBoxRandParam->setEnabled(false);
    //ui->lineEditHeaderVal->setEnabled(false);

    if (ui->lineEditRandParam->text().length()) {
        ui->comboBoxRandParam->setEnabled(true);
        //ui->lineEditHeaderVal->setEnabled(true);
    }
}

void MainWindow::setRandParamString()
{
    randParamType = static_cast<randPayloadTypes> (ui->comboBoxRandParam->currentIndex());
}

void MainWindow::setRandString(QString *randParamString)
{
    setRandParamString();

    switch(randParamType) {
    case NAME:
        genRandNames(randParamString);
        break;
    case NAME_SNAME:
        genRandNameSname(randParamString);
        break;
    case EMAIL:
        genRandomEmail(randParamString);
        break;
    case WEBSITE:
        genRandomWebsite(randParamString);
        break;
    case IP_ADDR:
        genRandomIP(randParamString);
        break;
    case PHONE_NUMBER:
        genRandomPhone(randParamString);
        break;
    default:
        break;
    }
}
