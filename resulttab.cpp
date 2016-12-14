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
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                (QString("<font color=red> Reflected XSS detected for the param %1</font>").arg(malParam));
        ui->textBrowserResults->append("XSS (OWASP), CWE 79, CVE-2014-3737");
    }
    else {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append("<font color=red>Likely Blind XSS Scenario for unknown JSON parameter</font>");
        ui->textBrowserResults->append("<i>A payload was injected in the past, but appeared in a recent reply</i>");
        ui->textBrowserResults->append(malPayload.at(1));
        ui->textBrowserResults->append("XSS (OWASP), CWE 79, CVE-2014-3737");
    }
}

void APIthet::analyzeApplicationFootprint(QNetworkReply *reply){
    if (reply->hasRawHeader("Server")) {
        header->addServerFootPrint(reply->rawHeader("Server"));
    }
    if (reply->hasRawHeader("X-Powered-By")) {
        header->addServerFootPrint(reply->rawHeader("X-Powered-By"));
    }
}

void APIthet::checkSecHeaders(QNetworkReply *reply)
{
    if (!reply->hasRawHeader(CONTENT_SEC_POL_HEADER))
        contentHeaderMissed++;
        //ui->textBrowserResults->append("Content Type not set by the application");

    if (!reply->hasRawHeader(XFRAME_OPTIONS_HEADER))
        xFrameHeaderMissed++;
        //ui->textBrowserResults->append("X Frame Options not set by the application");

    if (!reply->hasRawHeader(X_CONTENT_TYPE_OPT_HEADER))
        xContentHeaderMissed++;
        //ui->textBrowserResults->append("X Content Type not set by the application");

    if (!reply->hasRawHeader(HSTS_HEADER))
        hstsHeaderMissed++;
        //ui->textBrowserResults->append("Transport Layer Security not set by the application");

    if (!reply->hasRawHeader(ALLOW_ORIGIN))
        corsLikely++;

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

    if (contentHeaderMissed) {
        ui->textBrowserResults->append
            ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                (QString("<font color=blue>Content Type not set by the application: %1 occurences</font>").
                    arg(contentHeaderMissed));
        ui->textBrowserResults->append
                ("<i>This header safeguards against content injection attacks.</i>");
        ui->textBrowserResults->append
                ("<i>This header informs the user agent what are valid sources to load from.</i>");
    }

    if (xContentHeaderMissed) {
        ui->textBrowserResults->append
            ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                (QString("<font color=blue>X Content Type </color> not set by the application: %1 occurences</font>").
                 arg(xContentHeaderMissed));
        ui->textBrowserResults->append
                ("<i>This header prevents user agent interpreting the contents differently than specified.</i>");
    }
    if (hstsHeaderMissed) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                (QString("<font color=blue>Transport Layer Security not set by the application: %1 occurences</font>").
                 arg(hstsHeaderMissed));
        ui->textBrowserResults->append
                ("<i>HSTS header automatically redirects HTTP requests to HTTPS for the target domain</i>");
        ui->textBrowserResults->append
                ("<i>HSTS header does not allow a user to override the invalid certificate message</i>");
    }
    if (xFrameHeaderMissed) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                (QString("<font color=green>X Frame Options not set by the application: %1 occurences</font>").
                    arg(xFrameHeaderMissed));
        ui->textBrowserResults->append
                ("<i>This header improves the protection of user agent against Clickjacking </i>");
    }
    if (xssProtHeaderMissed) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                (QString("<font color=orange>XSS Protection header not set by the application: %1 occurences</font>").
                 arg(xssProtHeaderMissed));
        ui->textBrowserResults->append
                ("<i>This header helps specify browsers to use in-built capabilities against reflected XSS</i>");
    }

    if (csrfHeaderMissed) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                (QString("<font color=orange>CSRF Token header not used by the application: %1 occurences</font>").
                 arg(csrfHeaderMissed));
    }

    if (csrfIssueLikely && csrfHeaderMissed) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                ("<font color=orange>The application is likely vulnerable to CSRF issue</font>");
        ui->textBrowserResults->append("CSRF (OWASP), CWE 352");
    }

    if (passwdInGetQuery) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                ("<font color=red>The application likely sends password as a parameter for a GET query</font>");
    }

    if (likelyUnauth) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                ("<font color=red>The application has likely accessed a resource without authorization</font>");

    }

    if (corsLikely) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                ("<font color=green>Acess Control - Allow Origin header not set by the application</font>");
        ui->textBrowserResults->append
                ("<i>This header helps protect the application against CORS vulnerablities</i>");
        ui->textBrowserResults->append
                ("<i>Set the parameters to whitelisted URLs to restrict access to the applciation</i>");
    }

    while (header->footPrintPresent())
    {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        ui->textBrowserResults->append
                ("Application has left the following footprint:");
        ui->textBrowserResults->append(QString("<b>%1</b>").arg(header->getServerFootPrint()));
        ui->textBrowserResults->append("Security Misconfiguration (OWASP), CWE 200");
        ui->textBrowserResults->append("<i>This vulnerability helps attacker know about the technology \
stack/network topology being used by the application</i>");

    }
    //if (passwdInPostQuery)
}
