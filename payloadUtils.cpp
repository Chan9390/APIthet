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

const QString charsetRandom("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
const QString numsetRandom("0123456789");

//function to generate map of url parameters
void APIthet::genKeyValueMap(QUrl *targetURL)
{
    //QString urlString = targetURL->toString(QUrl::PrettyDecoded);
    QUrlQuery targetUrlQuery = QUrlQuery(*targetURL);

    //Derive a map of key value pairs from the url
    urlParamMap = targetUrlQuery.queryItems(QUrl::PrettyDecoded);
}

//Generate a random string
void APIthet::genRandomStr(QString *randStr, int strLen)
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
void APIthet::genRandomNumericalStr(QString *randStr, int strLen)
{
    randStr->clear();

    for(int iterator = 0; iterator < strLen; ++iterator)
    {
        int index = qrand() % numsetRandom.length();
        QChar nextChar = numsetRandom.at(index);
        randStr->append(nextChar);
    }
}

void APIthet::genMaliciousStr(QString *maliciousStr, QString keyVal)
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


void APIthet::genJSonMaliciousParam(QString *maliciousJsonParam, QString keyValue)
{
    QStringList keyPair = keyValue.split(":");
    QString randomString;

    genMaliciousStr(&randomString, keyPair.first());

    maliciousJsonParam->append(keyPair.first());
    maliciousJsonParam->append(":");
    maliciousJsonParam->append(randomString);
}

void APIthet::insertInvertedCommas(QString *keyVal)
{
    keyVal->insert(keyVal->indexOf(':') + 1, '\"');
    keyVal->insert(keyVal->indexOf(':'), '\"');
}

void APIthet::genRandomPhone(QString *randParamString){
    QString tempString;

    randParamString->clear();

    genRandomNumericalStr(&tempString, RANDOM_PHONE_NUM_LEN);
    randParamString->append(tempString);
    tempString.clear();
}

void APIthet::genRandomIP(QString *randParamString){
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

void APIthet::genRandomWebsite(QString *randParamString){
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

void APIthet::genRandomEmail(QString *randParamString){
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

void APIthet::genRandNameSname(QString *randParamString){
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

void APIthet::genRandNames(QString *randParamString){
    QString tempString;

    randParamString->clear();

    genRandomStr(&tempString, RANDOM_NAME_LEN);
    randParamString->append(tempString);
    tempString.clear();
}

QString* APIthet::genRandSqliPayload(sqliTypes injType){
    QString *sqliPayload = new QString;
    QString tempStr;

    sqliPayload->clear();
    
    genRandomNumericalStr(&tempStr, 5);

    sqliPayload->append(tempStr);
    tempStr.clear();

    sqliPayload->append("' or ");

    genRandomNumericalStr(&tempStr, 4);

    sqliPayload->append(tempStr);
    sqliPayload->append("=");
    sqliPayload->append(tempStr);

    return sqliPayload;
}
