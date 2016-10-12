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

void MainWindow::pushButtonRunSlot()
{
    //process HTTP request
    processHttpReq();

    //Clear the results of previous API
    ui->textBrowserResults->clear();

    setDefault();
    //Disable the payload input box
    //ui->plainTextEditPayload->setEnabled(false);

    ui->textBrowser->append(ui->comboBoxHTTPMethods->currentText());
    ui->textBrowser->insertPlainText(" ");

    ui->textBrowser->insertPlainText(ui->lineEditURL->text());

    //Bad hardcode, define it as a string
    //ui->textBrowser->append("_________________________________________");
    if (ui->lineEditHeader->text().length()) {
        ui->textBrowser->append("");
        ui->textBrowser->append(ui->lineEditHeader->text());
        ui->textBrowser->insertPlainText(":");
        ui->textBrowser->insertPlainText(ui->lineEditHeaderVal->text());
    }
    if (ui->plainTextEditPayload->toPlainText().length())
    {
        ui->textBrowser->append("");
        ui->textBrowser->append(ui->plainTextEditPayload->toPlainText());
    }
    //show the activities of header list
}
