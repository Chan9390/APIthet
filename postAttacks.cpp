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

#include "apithet.h"
#include "ui_apithet.h"

void APIthet::performPostCSRF(QNetworkRequest *httpRequest)
{
    attackType = CSRF;

    //try csrf payload
    prepareCsrfRequest(httpRequest);
    //httpRequest->setUrl(targetURL);
    manager->post(*httpRequest, ui->plainTextEditPayload->toPlainText().toUtf8());

    attackType = NO_ATTACK;
    eventLoop.exec();
}

void APIthet::performJsonXSS(QNetworkRequest *httpRequest)
{
    QString postPayload = ui->plainTextEditPayload->toPlainText();
    QString modPayload = postPayload.simplified();
    QByteArray reqPayloadBinary = postPayload.toUtf8();

    //check if there is a random JSON payload
    bool hasRandomJsonParam = false;

    QMap<QString, quint16>::iterator jsonParamsEntry;

    attackType = XSS;

    //initialize the iterator to beginning of the map element
    jsonParamsEntry = jsonParamsMap.begin();

    if (ui->lineEditRandParam->isEnabled() && ui->comboBoxRandParam->currentIndex())
        hasRandomJsonParam = true;

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

        //identify the current parameter that has
        //been injected with malicious parameter
        currentParam.clear();
        currentParam = keyValue;

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

            manager->post(*httpRequest, localPayload.toUtf8());

            //decrement the count by one
            --jsonParamRepeat;
            //The final count should be 0
            jsonParamsMap[keyValue] = jsonParamRepeat;
            eventLoop.exec();
        }
    }

    attackType = NO_ATTACK;

    //Clear the relevant data structures
    jsonMap.clear();
    jsonParamsMap.clear();
    jsonList.clear();
}
