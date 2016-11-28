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

//Takes string that surely contains malicious payload
//does a lookup for the key that was infected
void APIthet::analyzePayload(QString replyPayload)
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

void APIthet::analyzeApplicationFootprint(QNetworkReply *reply){
    if (reply->hasRawHeader("Server")) {
            ui->textBrowserResults->append(
                        "There was a server footprint");
            ui->textBrowserResults->append(
                    reply->rawHeader("Server"));
                    //    arg(reply->rawHeader("Server")));
                    //(reply->rawHeader("Server"));
            ui->textBrowserResults->append
                    ("-----------------------------------------------------------------------------");

    }
}

void APIthet::checkSecHeaders(QNetworkReply *reply)
{
    if (!reply->hasRawHeader(CONTENT_HEADER))
        contentHeaderMissed++;
        //ui->textBrowserResults->append("Content Type not set by the application");

    if (!reply->hasRawHeader(XFRAME_HEADER))
        xFrameHeaderMissed++;
        //ui->textBrowserResults->append("X Frame Options not set by the application");

    if (!reply->hasRawHeader(XCONTENT_HEADER))
        xContentHeaderMissed++;
        //ui->textBrowserResults->append("X Content Type not set by the application");

    if (!reply->hasRawHeader(HSTS_HEADER))
        hstsHeaderMissed++;
        //ui->textBrowserResults->append("Transport Layer Security not set by the application");

    if (!reply->hasRawHeader(XSS_HEADER))
        xssProtHeaderMissed++;
        //ui->textBrowserResults->append("XSS Protection header not set by the application");
    if (!reply->hasRawHeader(CSRF_TOKEN_1) || !reply->hasRawHeader(CSRF_TOKEN_2)
            || !reply->hasRawHeader(CSRF_TOKEN_3))
        csrfHeaderMissed++;

    //showHeaderResult();
}

void APIthet::showHeaderResult()
{
    //ui->textBrowserResults->clear();

    if (contentHeaderMissed)
        ui->textBrowserResults->append
                (QString("<font color=blue>Content Type not set by the application: %1 occurences</font>").
                    arg(contentHeaderMissed));
    if (hstsHeaderMissed)
        ui->textBrowserResults->append
                (QString("<font color=blue>Transport Layer Security not set by the application: %1 occurences</font>").
                 arg(hstsHeaderMissed));
    if (xFrameHeaderMissed)
        ui->textBrowserResults->append
                (QString("<font color=green>X Frame Options not set by the application: %1 occurences</font>").
                    arg(xFrameHeaderMissed));
    if (xContentHeaderMissed)
        ui->textBrowserResults->append
                (QString("<font color=orange>X Content Type not set by the application: %1 occurences</font>").
                 arg(xContentHeaderMissed));

    if (xssProtHeaderMissed)
        ui->textBrowserResults->append
                (QString("<font color=orange>XSS Protection header not set by the application: %1 occurences</font>").
                 arg(xssProtHeaderMissed));

    if (csrfHeaderMissed)
        ui->textBrowserResults->append
                (QString("<font color=orange>CSRF Token header not used by the application: %1 occurences</font>").
                 arg(csrfHeaderMissed));

    ui->textBrowserResults->append
            ("-----------------------------------------------------------------------------");

    if (csrfIssueLikely && csrfHeaderMissed) {
        ui->textBrowserResults->append
                ("<font color=orange>The application is likely vulnerable to CSRF issue</font>");
        ui->textBrowserResults->append("CSRF (OWASP), CWE 352");
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
    }

    if (passwdInGetQuery) {
        ui->textBrowserResults->append
                ("<font color=red>The application likely sends password as a parameter for a GET query</font>");
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
    }

    if (likelyUnauth) {
        ui->textBrowserResults->append
                ("<font color=red>The application has likely accessed a resource without authorization</font>");
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
    }
    //if (passwdInPostQuery)
}
