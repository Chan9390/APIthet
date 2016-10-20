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
void MainWindow::sendGEThttp()
{
    QNetworkRequest httpRequest;
    QString urlString = ui->lineEditURL->text();
    //QString randomString;
    QUrl targetURL = QUrl(urlString);
    QString strQuery = targetURL.query(QUrl::PrettyDecoded);

    setApplicationProxy();
    //Add headers to the request
    setHttpHeaders(&httpRequest);

    //Check if the URL contains any key value pairs
    if (strQuery.length() && !(strQuery.isEmpty())) {
        genKeyValueMap(&targetURL);

        hasQueryParams = true;

        //likely contains password
        if (strQuery.contains("pass") || strQuery.contains("password") ||
                strQuery.contains("paswd") || strQuery.contains("passwd"))
            passwdInGetQuery = true;
        performUrlXSS(&httpRequest);
    }

    else {
        //Set URL
        httpRequest.setUrl(targetURL);
        //Invoke get method
        manager->get(httpRequest);
        eventLoop.exec();
    }
    //CSRF Request
    performGetCSRF(&httpRequest);
}

void MainWindow::sendPOSThttp()
{
    QNetworkRequest httpRequest;
    //;

    QString strQuery = ui->lineEditURL->text();
    QUrl targetURL = QUrl(ui->lineEditURL->text());
    QString postPayload = ui->plainTextEditPayload->toPlainText();
    QByteArray reqPayloadBinary = postPayload.toUtf8();


    QMap<QString, quint16>::iterator jsonParamsEntry;

    //form a json map from the payload
    bool validJsonPayload = genJSONpayload(reqPayloadBinary);

    setApplicationProxy();

    //initialize the iterator to beginning of the map element
    jsonParamsEntry = jsonParamsMap.begin();

    //Set URL
    httpRequest.setUrl(targetURL);

    //Add headers to the request
    setHttpHeaders(&httpRequest);

    if (postPayload.length())
        postQueryHasBody = true;

    //likely contains password
    if (strQuery.contains("pass") || strQuery.contains("password") ||
        strQuery.contains("paswd") || strQuery.contains("passwd"))
            passwdInPostQuery = true;

    if (validJsonPayload)
        performJsonXSS(&httpRequest);


    performPostCSRF(&httpRequest);

    //Invoke post method
    if (!validJsonPayload)
        manager->post(httpRequest, ui->plainTextEditPayload->toPlainText().toUtf8());
}

void MainWindow::sendPUThttp()
{
    QNetworkRequest httpRequest;
    QUrl targetURL = QUrl(ui->lineEditURL->text());
    QString strQuery = targetURL.query(QUrl::PrettyDecoded);

    //if (strQuery.length())
    //    ui->textBrowser->append(strQuery);

    //Set URL
    httpRequest.setUrl(targetURL);

    //Add headers to the request
    setHttpHeaders(&httpRequest);

    //Invoke post method
    manager->put(httpRequest, ui->plainTextEditPayload->toPlainText().toUtf8());
    //ui->pushButtonAdd->setEnabled(false);
}
