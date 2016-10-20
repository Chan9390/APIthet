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

const QString charsetRandom("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
const QString numsetRandom("0123456789");

//function to generate map of url parameters
void MainWindow::genKeyValueMap(QUrl *targetURL)
{
    //QString urlString = targetURL->toString(QUrl::PrettyDecoded);
    QUrlQuery targetUrlQuery = QUrlQuery(*targetURL);

    //Derive a map of key value pairs from the url
    urlParamMap = targetUrlQuery.queryItems(QUrl::PrettyDecoded);
}

//Generate a random string
void MainWindow::genRandomStr(QString *randStr, int strLen)
{
    randStr->clear();

    for(int iterator = 0; iterator < strLen; ++iterator)
    {
        int index = qrand() % charsetRandom.length();
        QChar nextChar = charsetRandom.at(index);
        randStr->append(nextChar);
    }
}

//Generate a random string
void MainWindow::genRandomNumericalStr(QString *randStr, int strLen)
{
    randStr->clear();

    for(int iterator = 0; iterator < strLen; ++iterator)
    {
        int index = qrand() % numsetRandom.length();
        QChar nextChar = numsetRandom.at(index);
        randStr->append(nextChar);
    }
}

void MainWindow::genMaliciousStr(QString *maliciousStr, QString keyVal)
{
    QString randStr;

    genRandomStr(&randStr, RANDOM_CHAR_LEN);

    //Map the random payload for the key being used
    keyLookupTable[randStr] = keyVal;

    //Generate Malicious payload
    maliciousStr->clear();
    maliciousStr->append(maliciousPart1);
    maliciousStr->append(randStr);
    maliciousStr->append(maliciousPart2);
}

//Takes string that surely contains malicious payload
//does a lookup for the key that was infected
void MainWindow::analyzePayload(QString replyPayload)
{
    QStringList malPayload = replyPayload.split(maliciousPart1);
    QStringList relativeID = malPayload.at(1).split(maliciousPart2);

    QString lookupID = relativeID.at(0);
    QString malParam = keyLookupTable.value(lookupID);

    if (malParam.length()) {
        ui->textBrowserResults->append
                (QString("<font color=red> Reflected XSS detected for the param %1</font>").arg(malParam));
        ui->textBrowserResults->append("XSS (OWASP), CWE 79, CVE-2014-3737");
    }
    else {
        ui->textBrowserResults->append("<font color=red>Likely Blind XSS Scenario for unknown JSON parameter</font>");
        ui->textBrowserResults->append("<i>A payload was injected in the past, but appeared in a recent reply</i>");
        ui->textBrowserResults->append(malPayload.at(1));
        ui->textBrowserResults->append("XSS (OWASP), CWE 79, CVE-2014-3737");
    }
}

void MainWindow::genJSonMaliciousParam(QString *maliciousJsonParam, QString keyValue)
{
    QStringList keyPair = keyValue.split(":");
    QString randomString;

    genMaliciousStr(&randomString, keyPair.first());

    maliciousJsonParam->append(keyPair.first());
    maliciousJsonParam->append(":");
    maliciousJsonParam->append(randomString);
}

void MainWindow::insertInvertedCommas(QString *keyVal)
{
    keyVal->insert(keyVal->indexOf(':') + 1, '\"');
    keyVal->insert(keyVal->indexOf(':'), '\"');
}

void MainWindow::genRandomPhone(QString *randParamString){
    QString tempString;

    randParamString->clear();

    genRandomNumericalStr(&tempString, RANDOM_PHONE_NUM_LEN);
    randParamString->append(tempString);
    tempString.clear();
}

void MainWindow::genRandomIP(QString *randParamString){
    QString tempString;
    //QChar   singleChar;
    ushort  quartet;

    randParamString->clear();

    genRandomStr(&tempString, SINGLE_CHAR_LEN);
    quartet = tempString.at(0).unicode();
    randParamString->append(QString::number(quartet));
    randParamString->append(".");

    genRandomStr(&tempString, SINGLE_CHAR_LEN);
    quartet = tempString.at(0).unicode();
    randParamString->append(QString::number(quartet));
    randParamString->append(".");

    genRandomStr(&tempString, SINGLE_CHAR_LEN);
    quartet = tempString.at(0).unicode();
    randParamString->append(QString::number(quartet));
    randParamString->append(".");

    genRandomStr(&tempString, SINGLE_CHAR_LEN);
    quartet = tempString.at(0).unicode();
    randParamString->append(QString::number(quartet));
    tempString.clear();
}

void MainWindow::genRandomWebsite(QString *randParamString){
    QString tempString;

    randParamString->clear();
    randParamString->append("www.");

    genRandomStr(&tempString, RANDOM_DOMAIN_LEN);
    randParamString->append(tempString);
    randParamString->append(".");
    tempString.clear();

    genRandomStr(&tempString, RANDOM_SITE_TYPE_LEN);
    randParamString->append(tempString);
    tempString.clear();
}

void MainWindow::genRandomEmail(QString *randParamString){
    QString tempString;

    randParamString->clear();

    genRandomStr(&tempString, RANDOM_NAME_LEN);
    randParamString->append(tempString);
    randParamString->append("@");
    tempString.clear();

    genRandomStr(&tempString, RANDOM_DOMAIN_LEN);
    randParamString->append(tempString);
    randParamString->append(".");
    tempString.clear();

    genRandomStr(&tempString, RANDOM_SITE_TYPE_LEN);
    randParamString->append(tempString);
    tempString.clear();
}

void MainWindow::genRandNameSname(QString *randParamString){
    QString tempString;

    randParamString->clear();

    genRandomStr(&tempString, RANDOM_NAME_LEN);
    randParamString->append(tempString);
    randParamString->append(" ");
    tempString.clear();

    genRandomStr(&tempString, RANDOM_NAME_LEN);
    randParamString->append(tempString);
    tempString.clear();
}

void MainWindow::genRandNames(QString *randParamString){
    QString tempString;

    randParamString->clear();

    genRandomStr(&tempString, RANDOM_NAME_LEN);
    randParamString->append(tempString);
    tempString.clear();
}
