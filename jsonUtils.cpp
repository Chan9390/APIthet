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

bool APIthet::genJSONpayload(QString replyPayload)
{
    QJsonDocument replyJsonDoc = QJsonDocument::fromJson(replyPayload.toUtf8());

    QVariant jsonVariant = replyJsonDoc.toVariant();

    if (jsonVariant.canConvert<QMap<QString, QVariant> >()) {
        jsonMap = jsonVariant.toMap();
        analyzeJsonMap();
        //ui->textBrowser->append("Map");
    }
    else if (jsonVariant.canConvert<QList<QVariant> >()) {
        jsonList = jsonVariant.toList();
        analyzeJsonList();
        //ui->textBrowser->append("List");
    }

    else {
        ui->textBrowser->append("can't parse payload as JSON");
        return false;
    }
    return true;
}

void APIthet::analyzeJsonList()
{
    int numNodes = jsonList.count();
    for(int iter = 0; iter < numNodes; ++iter)
    {
        QVariant jsonNode = jsonList.at(iter);

        //check if Node can be coverted into a string or int
        /*
         if (!jsonNode.canConvert<QMap<QString, QVariant> >()
               && !jsonNode.canConvert<QList<QVariant> >()) {
            ui->textBrowser->append(".................");
            //ui->textBrowser->append(jsonMapEntry.key());
            ui->textBrowser->append(jsonNode.toString());
        }
        */
        analyzeJsonNode(&jsonNode);
    }
}

void APIthet::analyzeJsonList(QList<QVariant> *localList)
{
    int numNodes = localList->count();
    for(int iter = 0; iter < numNodes; iter++)
    {
        QVariant jsonNode = localList->at(iter);
        //check if Node can be coverted into a string or int
        /*
        if (!jsonNode.canConvert<QMap<QString, QVariant> >()
                && !jsonNode.canConvert<QList<QVariant> >()) {
            ui->textBrowser->append(".................");
            //ui->textBrowser->append(jsonMapEntry.key());
            ui->textBrowser->append(jsonNode.toString());
        }
        else
        */
            analyzeJsonNode(&jsonNode);
    }
}

void APIthet::analyzeJsonMap()
{
    for(QMap<QString, QVariant>::iterator jsonMapEntry = jsonMap.begin();
        jsonMapEntry != jsonMap.end(); ++jsonMapEntry)
    {
        QVariant jsonNode = *jsonMapEntry;
        if (!jsonNode.canConvert<QMap<QString, QVariant> >()
                && !jsonNode.canConvert<QList<QVariant> >()) {
            //ui->textBrowser->append(".................");
            populateJsonParamMap(jsonMapEntry.key(), jsonMapEntry.value().toString());
            //ui->textBrowser->append(jsonMapEntry.key());
            //ui->textBrowser->append(jsonMapEntry.value().toString());
        }
        else
            analyzeJsonNode(&jsonNode);
    }
}

void APIthet::analyzeJsonMap(QMap<QString, QVariant> *localMap)
{
    QMap<QString, QVariant>::iterator jsonMapEntry = localMap->begin();
    for (int iter = 0; iter < localMap->count(); ++iter, jsonMapEntry++)
    {
        QVariant jsonNode = *jsonMapEntry;
        //check if Node can be coverted into a string or int
        if (!jsonNode.canConvert<QMap<QString, QVariant> >()
                && !jsonNode.canConvert<QList<QVariant> >()) {
            //ui->textBrowser->append(".................");
            populateJsonParamMap(jsonMapEntry.key(), jsonMapEntry.value().toString());
        }
        else
            analyzeJsonNode(&jsonNode);
    }
}

void APIthet::analyzeJsonNode(QVariant *jsonNode)
{
    if (jsonNode->canConvert<QMap<QString, QVariant> >()) {
        QMap<QString, QVariant> localMap = jsonNode->toMap();
        analyzeJsonMap(&localMap);
    }
    else if (jsonNode->canConvert<QList<QVariant> >()) {
        QList<QVariant> localList = jsonNode->toList();
        analyzeJsonList(&localList);
    }
    else {
        ui->textBrowser->append("Nothing to do");
    }
}

void APIthet::populateJsonParamMap(QString key, QString value)
{
    QString keyValPair = key + ":" + value;
    writeJsonParamMap(keyValPair);
}

void APIthet::writeJsonParamMap(QString jsonStrings)
{
    int keyValueCount = 1;
    if (jsonParamsMap.contains(jsonStrings)) {
        keyValueCount = (jsonParamsMap.value(jsonStrings)) + 1;
        jsonParamsMap[jsonStrings] = keyValueCount;
    }
    else
        jsonParamsMap[jsonStrings] = keyValueCount;
}

