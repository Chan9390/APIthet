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

//Handle Replies
void APIthet::replyFinished (QNetworkReply *reply)
{
    ui->textBrowser->clear();

    //ui->textBrowser->append(reply->readAll().constData());
    switch(attackType) {
    case XSS:
        processXssReply(reply);
        break;
    case CSRF:
        processCsrfReply(reply);
        break;
    case SQL_INJ:
        processSqliReply(reply);
    case HTML_INJ:
        processHtmlInjectionReply(reply);
    case OPEN_REDIRECT:
        processOpenRedirectReply(reply);
    case HTTP_SPLITTING:
    case CRLF:
    case CORS:
    case HEADER_FUZZ:
    default:
        break;
    }

    //check if an operation was performed without an Auth header
    if (!reply->error()) {
        if (headerHasAuth && (hasQueryParams || postQueryHasBody))
            likelyUnauth = true;

        checkSecHeaders(reply);
    }

    analyzeApplicationFootprint(reply);

    reply->deleteLater();

    //end of the event loop
    eventLoop.quit();
}

void APIthet::processCsrfReply(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode < 200 || statusCode > 208)
    {
        ui->textBrowser->append("An error occured while performing the operation...");
        ui->textBrowser->append(reply->errorString());
    }

    else
        csrfIssueLikely = true;
}

void APIthet::processSqliReply(QNetworkReply *reply)
{
    QByteArray hostResponse = reply->readAll();
    QString replyStr = QString(hostResponse);

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (replyStr.contains("error"))
        processErrorMessage(replyStr);
    else if (statusCode >= 200 && statusCode <= 208)
    {
        ui->textBrowserResults->append(
                QString("<font color=red>Blind SQLI likely for JSON param -- %1</font>").arg(currentParam));
        ui->textBrowserResults->append
                ("<i>Malicious payload was injected, but was treated as a valid parameter</i>");
        ui->textBrowserResults->append
                ("SQL Injection (OWASP type - Injection), CWE 89");
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
    }
}

void APIthet::processXssReply(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode < 200 || statusCode > 208)
    {
        ui->textBrowser->append("An error occured while performing the operation...");
        ui->textBrowser->append(reply->errorString());
    }

    else {
        QByteArray hostResponse = reply->readAll();
        QString replyStr = QString(hostResponse);

        //Analyze the reply, check if it contains any malicious payload
        if (replyStr.contains(maliciousPart1) && replyStr.contains(maliciousPart2))
            analyzePayload(replyStr);

        else if (currentParam.length()) {
            ui->textBrowserResults->append
                    (QString("<font color=red>Stored XSS likely for JSON param -- %1</font>").arg(currentParam));
            ui->textBrowserResults->append
                    ("<i>Malicious payload was injected, but application replied with HTTP status OK</i>");
            ui->textBrowserResults->append
                    ("Cross Site Scripting (OWASP type - XSS), CWE 79");
            ui->textBrowserResults->append
                    ("-----------------------------------------------------------------------------");
        }
    }
}

void APIthet::processHtmlInjectionReply(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode < 200 || statusCode > 208)
    {
        ui->textBrowser->append("An error occured while performing the operation...");
        ui->textBrowser->append(reply->errorString());
    }

    else {
        QByteArray hostResponse = reply->readAll();
        QString replyStr = QString(hostResponse);

        if (replyStr.contains(htmlInjContent)) {
            ui->textBrowserResults->append
                    (QString("<font color=red>HTML injection found for param %1 </font>").arg(currentParam));
            ui->textBrowserResults->append("<i>HTML Injection (OWASP type - Injection)</i>");
        }
    }
}

void APIthet::processOpenRedirectReply(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode < 200 || statusCode > 308)
    {
        ui->textBrowser->append("An error occured while performing the operation...");
        ui->textBrowser->append(reply->errorString());
    }
    else {
        QByteArray hostResponse = reply->readAll();
        QString replyStr = QString(hostResponse);
        QString desiredReply =
                "This domain is established to be used for illustrative examples in documents";

        if (replyStr.contains(desiredReply)) {
            ui->textBrowserResults->append
                    ("<font color=red>Open Redirect vulnerability found</font>");
        }
    }
}

void APIthet::processErrorMessage(QString reply)
{
    if (reply.contains("sql") || reply.contains("syntax") ||
            reply.contains("table") || reply.contains("database")) {
        ui->textBrowserResults->append
                ("-----------------------------------------------------------------------------");
        if (reply.contains("MySQL") || reply.contains("MSSQL") ||
                reply.contains("Oracle") || reply.contains("MariaDB") ||
                reply.contains("Postgre") || reply.contains("Mongo")) {
            ui->textBrowserResults->append
                    ("<font color=red><b>The application is very likely vulnerable to SQLI!!!</b></font>");
        }
        else {
            ui->textBrowserResults->append
                            ("<font color=red>The application is likely vulnerable to SQLI!!!</font>");
        }
        ui->textBrowserResults->append
                ("SQL Injection (OWASP type - Injection), CWE 89");
    }
}
