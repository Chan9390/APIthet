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

//Set Http headers to the request
void MainWindow::setHttpHeaders(QNetworkRequest *httpRequest)
{
    while (header->getHeaderCount()) {
        httpRequest->setRawHeader(header->getLastHeader().toUtf8(),
                                header->getLastHeaderVal().toUtf8());
        header->decrementHeaders();
    }
}

void MainWindow::prepareCsrfRequest(QNetworkRequest *httpRequest)
{
    //Set header for arbitrary content type
    httpRequest->setRawHeader(QString("Content-Type").toUtf8(),
                            QString("*").toUtf8());
    //Set header for arbitrary origin
    httpRequest->setRawHeader(QString("Origin").toUtf8(),
                            QString("*").toUtf8());
    csrfPayload = true;
}
