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

void MainWindow::processHttpReq()
{
    methods = static_cast<httpMethods> (ui->comboBoxHTTPMethods->currentIndex());

    switch (methods) {
    case GET:
        sendGEThttp();
        break;
    case POST:
        sendPOSThttp();
        break;
    case PUT:
        sendPUThttp();
        break;
    default:
        ui->textBrowser->append("----unhandled----");
        break;
    }
    //show the test result
    showHeaderResult();
    ui->pushButtonRun->setEnabled(true);
}
