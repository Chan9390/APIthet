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


void MainWindow::performUrlXSS(QNetworkRequest *httpRequest)
{
    QString urlString = ui->lineEditURL->text();
    QString randomString;
    QPair<QString, QString> keyValue;

    attackType = XSS;

    for (mapEntry = urlParamMap.begin();
        mapEntry != urlParamMap.end(); mapEntry++) {
        QString malUrlString = urlString;
        keyValue = *mapEntry;

        //generate a malicious payload
        genMaliciousStr(&randomString, keyValue.first);

        //form valid and malicious keyvalue pairs
        QString queryParams = QString("%1=%2").arg(keyValue.first, keyValue.second);
        QString maliciousParams = QString("%1=%2").arg(keyValue.first, randomString);

        malUrlString.replace(queryParams, maliciousParams);

        //Set URL
        httpRequest->setUrl(malUrlString);

        //identify the current parameter that has
        //been injected with malicious parameter
        currentParam.clear();
        currentParam = keyValue.first;

        //Invoke get method
        manager->get(*httpRequest);
        eventLoop.exec();
    }
    //clear the map of its records
    urlParamMap.clear();
    attackType = NO_ATTACK;
}

void MainWindow::performGetCSRF(QNetworkRequest *httpRequest)
{
    QString urlString = ui->lineEditURL->text();
    QUrl targetURL = QUrl(urlString);

    attackType = CSRF;

    prepareCsrfRequest(httpRequest);
    httpRequest->setUrl(targetURL);
    manager->get(*httpRequest);

    attackType = NO_ATTACK;
    eventLoop.exec();
}
