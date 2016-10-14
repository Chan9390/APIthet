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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSplashScreen>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>

#include <QThread>
#include <QEventLoop>

#include <QLinkedList>
#include <QList>
#include <QPair>
#include <QHash>
#include <iterator>

#include <QUrl>
#include <QUrlQuery>

#include <QStringList>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include <QRegExp>


#define APPICON ":/icons/APIthet_icon.png"

#define CONTENT_HEADER  "Content-Security-Policy"
#define XFRAME_HEADER   "X-Frame-Options"
#define XCONTENT_HEADER "X-Content-Type-Options"
#define HSTS_HEADER     "Strict-Transport-Security"
#define XSS_HEADER      "X-XSS-Protection"

#define maliciousPart1  "\"><ScRiPt SRC="
#define maliciousPart2  "></ScRiPt>"

#define RANDOM_CHAR_LEN 5
#define RANDOM_NAME_LEN 6
#define SINGLE_CHAR_LEN 1
#define RANDOM_DOMAIN_LEN   6
#define RANDOM_PHONE_NUM_LEN    10
#define RANDOM_SITE_TYPE_LEN    3

namespace Ui {
class MainWindow;
}

enum httpMethods {
    GET=0,
    POST,
    PUT,
    HEAD,
    DELETE,
    TRACE,
    CONNECT,
    OPTIONS,
};

enum randPayloadTypes {
    NONE = 0,
    NAME,
    NAME_SNAME,
    EMAIL,
    WEBSITE,
    IP_ADDR,
    PHONE_NUMBER,
};

class apiList {
private:
    //Target Url
    QUrl targetUrl;
    //HTTP Request
    QNetworkRequest reqHandle;
    //HTTP Reply
    QNetworkReply *replyHandle;
    //Network Access Manager
    QNetworkAccessManager networkAccessManager;

    ~apiList();
};

class httpHeaders {
public:
    httpHeaders();
    void incrementHeaders();
    void decrementHeaders();
    void insertHeader(QString hdrStr , QString hdrValStr);
    bool hasElements();
    bool isEmpty();
    QString getLastHeader();
    QString getLastHeaderVal();
    void clearList();
    uint getHeaderCount();

private:
    uint numHeaders;
    QLinkedList<QString> header;
    QLinkedList<QString> headerVal;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setMethods();
    void setEncoding();
    void setRandTypes();
    //void setProxy();

    apiList *apiEntry;
    QNetworkProxy proxy;

    ~MainWindow();

public slots:

    //slot to handle cleaar button
    void pushButtonClearSlot();

    //slot for adding header
    void textBrowserHeaderSlot();

    //slot for adding payload
    void textBrowserPayloadSlot();

    //slot for encoding payload
    void textBrowserEncodeSlot();

    //slot to enable/disable Encode button
    void pushButtonEncodeSlot();

    // Slot to enable/disable Header button
    void pushButtonHeaderSlot();

    //Slot to handle Run button
    void pushButtonRunSlot();

    //slot to handle http request
    void replyFinished (QNetworkReply *reply);

    //slot to handle enable proxy button
    void enableProxySlot(int state);

    //slot to handle enable auth button
    void enableAuthSlot(int state);

    //Slot to handle payload text with selected HTTP method
    void comboBoxHTTPSlot(QString selectedMethod);

    //slot for the payload line edit
    void getRandJsonParam();

    //slot for random payload combobox
    void comboBoxRandParamSlot();

private:
    Ui::MainWindow *ui;

    //Handle error conditions
    //to check url text
    bool lineUrlValid();
    void processHttpReq();
    void sendGEThttp();
    void sendPOSThttp();
    void sendPUThttp();
    void setHttpHeaders(QNetworkRequest *httpRequest);
    void checkSecHeaders(QNetworkReply *reply);

    void genKeyValueMap(QUrl *targetURL);
    void genRandomStr(QString *randStr, int strLen);
    void genRandomNumericalStr(QString *randStr, int strLen);

    void genMaliciousStr(QString *maliciousStr, QString keyVal);
    void reportMalPayload(QString Payload);
    void analyzePayload(QString replyPayload);
    bool genJSONpayload(QString replyPayload);
    void analyzeJsonList();
    void analyzeJsonList(QList<QVariant> *localList);
    void analyzeJsonMap();
    void analyzeJsonNode(QVariant *jsonNode);

    void setApplicationProxy();

    void populateJsonParamMap(QString key, QString value);
    void writeJsonParamMap(QString jsonStrings);
    void analyzeJsonMap(QMap<QString, QVariant> *localMap);

    void insertInvertedCommas(QString *keyVal);
    void genJSonMaliciousParam(QString *maliciousJsonParam, QString keyValue);
    
    void genRandomPhone(QString *);
    void genRandomIP(QString *);
    void genRandomWebsite(QString *);
    void genRandomEmail(QString *);
    void genRandNameSname(QString *);
    void genRandNames(QString *);

    void setRandParamString();
    void setRandString(QString *randParamString);

    void prepareCsrfRequest(QNetworkRequest *httpRequest);
    void showHeaderResult();

    void setDefault();

    QNetworkAccessManager *manager;

    QList<QPair<QString, QString> > urlParamMap;
    QList<QPair<QString, QString> >::iterator mapEntry;

    QHash<QString, QString> keyLookupTable;

    QMap<QString, QVariant> jsonMap;

    QMap<QString, quint16> jsonParamsMap;

    QList<QVariant> jsonList;

    httpMethods methods;
    randPayloadTypes randParamType;

    QEventLoop eventLoop;

    httpHeaders *header;

    //flag to specify a payload crafted CSRF
    bool csrfPayload;
    bool csrfIssueLikely;
    //there was and authentication header in the request
    bool headerHasAuth;
    //the request has queries in URL or body
    bool hasQueryParams;

    bool postQueryHasBody;

    bool likelyUnauth;
    //password likely present in query
    bool passwdInGetQuery;

    bool passwdInPostQuery;

    int contentHeaderMissed;
    int xFrameHeaderMissed;
    int xContentHeaderMissed;
    int hstsHeaderMissed;
    int xssProtHeaderMissed;

    QString currentParam;
};


#endif // MAINWINDOW_H
