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

//Set the correct HTTP Method
void MainWindow::setMethods()
{
    QComboBox *comboBoxHTTPMethods = ui->comboBoxHTTPMethods;
    QStringList methodList;

    //Add HTTP Methods to the list
    methodList << "GET" << "POST" << "PUT" << "HEAD"
               << "DELETE" << "TRACE" << "CONNECT" << "OPTIONS";

    //Assign the string list to the combobox
    comboBoxHTTPMethods->addItems(methodList);
}

void MainWindow::comboBoxHTTPSlot(QString selectedMethod)
{
    if (selectedMethod == "PUT" || selectedMethod == "POST"
            || selectedMethod == "DELETE") {
        ui->plainTextEditPayload->setEnabled(true);
        //ui->comboBoxEncode->setEnabled(true);
    }
    else {
        ui->plainTextEditPayload->setEnabled(false);
        //ui->comboBoxEncode->setEnabled(false);
    }
}

