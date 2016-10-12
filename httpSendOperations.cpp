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
    QString randomString;
    QUrl targetURL = QUrl(urlString);
    QString strQuery = targetURL.query(QUrl::PrettyDecoded);

    setApplicationProxy();
    //Add headers to the request
    setHttpHeaders(&httpRequest);

    //Check if the URL contains any key value pairs
    if (strQuery.length() && !(strQuery.isEmpty())) {
        genKeyValueMap(&targetURL);

        QPair<QString, QString> keyValue;
        hasQueryParams = true;

        //likely contains password
        if (strQuery.contains("pass") || strQuery.contains("password") ||
                strQuery.contains("paswd") || strQuery.contains("passwd"))
            passwdInGetQuery = true;

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
            httpRequest.setUrl(malUrlString);

            //Invoke get method
            manager->get(httpRequest);

            ui->textBrowser->append(maliciousParams);
            ui->textBrowser->append(queryParams);
            ui->textBrowser->append(malUrlString);
        }
        //clear the map of its records
        urlParamMap.clear();
    }

    else {
        //Set URL
        httpRequest.setUrl(targetURL);

        //Invoke get method
        manager->get(httpRequest);
    }
    //CSRF Request
    prepareCsrfRequest(&httpRequest);
    httpRequest.setUrl(targetURL);
    manager->get(httpRequest);

    ui->pushButtonAdd->setEnabled(false);
}

void MainWindow::sendPOSThttp()
{
    QNetworkRequest httpRequest;
    //;

    QString strQuery = ui->lineEditURL->text();
    QUrl targetURL = QUrl(ui->lineEditURL->text());
    QString postPayload = ui->plainTextEditPayload->toPlainText();
    QByteArray reqPayloadBinary = postPayload.toUtf8();
    QString modPayload = postPayload.simplified();
            //QJsonDocument::fromJson(reqPayloadBinary).toJson(QJsonDocument::Compact);


    QMap<QString, quint16>::iterator jsonParamsEntry;

    //form a json map from the payload
    bool validJsonPayload = genJSONpayload(reqPayloadBinary);

    //check if there is a random JSON payload
    bool hasRandomJsonParam = false;

    setApplicationProxy();

    if (ui->lineEditRandParam->isEnabled() && ui->comboBoxRandParam->currentIndex())
        hasRandomJsonParam = true;

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

    //Algorithm:
    //Get a copy of the original payload
    //Get a copy of the Key Value pair from Json Payload Map
    //Modify the key value pair to contain malicious param
    //replace the original key value with malicious one in the payload
    //send the payload through post
    for (int iterCount = 0; iterCount < jsonParamsMap.count(),
         jsonParamsEntry != jsonParamsMap.end(); iterCount++, jsonParamsEntry++) {

        QString keyValue = jsonParamsEntry.key();
        quint16 jsonParamRepeat = jsonParamsEntry.value();
        int indexOfKeyValue = 0;
        int newIndex = 0;

        insertInvertedCommas(&keyValue);

        while (jsonParamRepeat >= 1)
        {
            QString maliciousJsonParam;
            QString localPayload = modPayload;

            //inner loop
            //Modify the key value pair to contain malicious param
            genJSonMaliciousParam(&maliciousJsonParam, keyValue);

            indexOfKeyValue = modPayload.indexOf(keyValue, newIndex,
                                                 Qt::CaseInsensitive);

            //the next search will be done from here
            newIndex = indexOfKeyValue + keyValue.length();

            //replace the real key value at the fresh index with malicious one
            localPayload.replace(indexOfKeyValue, keyValue.length(), maliciousJsonParam);

            //if (!localPayload.contains(maliciousPart1))
            //    ui->textBrowser->append("A miss");

            //insert unique random json param
            if (hasRandomJsonParam) {
                QString randParamString;
                setRandString(&randParamString);
                localPayload.replace(ui->lineEditRandParam->text(), randParamString);
            }

            manager->post(httpRequest, localPayload.toUtf8());
            //decrement the count by one
            --jsonParamRepeat;
            //The final count should be 0
            jsonParamsMap[keyValue] = jsonParamRepeat;
        }
    }

    //try csrf payload
    prepareCsrfRequest(&httpRequest);
    manager->post(httpRequest, ui->plainTextEditPayload->toPlainText().toUtf8());

    //Invoke post method
    if (!validJsonPayload)
        manager->post(httpRequest, ui->plainTextEditPayload->toPlainText().toUtf8());
    else {
        //Clear the relevant data structures
        jsonMap.clear();
        jsonParamsMap.clear();
        jsonList.clear();
    }
    ui->pushButtonAdd->setEnabled(false);
}

void MainWindow::sendPUThttp()
{
    QNetworkRequest httpRequest;
    QUrl targetURL = QUrl(ui->lineEditURL->text());
    QString strQuery = targetURL.query(QUrl::PrettyDecoded);

    if (strQuery.length())
        ui->textBrowser->append(strQuery);

    //Set URL
    httpRequest.setUrl(targetURL);

    //Add headers to the request
    setHttpHeaders(&httpRequest);

    //Invoke post method
    manager->put(httpRequest, ui->plainTextEditPayload->toPlainText().toUtf8());
    ui->pushButtonAdd->setEnabled(false);
}
