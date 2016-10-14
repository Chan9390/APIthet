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

void MainWindow::checkSecHeaders(QNetworkReply *reply)
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

    //showHeaderResult();
}

void MainWindow::showHeaderResult()
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

    ui->textBrowserResults->append("------------------------------------");

    if (csrfIssueLikely) {
        ui->textBrowserResults->append
                ("<font color=orange>The application is likely vulnerable to CSRF issue</font>");
        ui->textBrowserResults->append("------------------------------------");
    }

    if (passwdInGetQuery) {
        ui->textBrowserResults->append
                ("<font color=red>The application likely sends password as a parameter for a GET query</font>");
        ui->textBrowserResults->append("------------------------------------");
    }

    if (likelyUnauth) {
        ui->textBrowserResults->append
                ("<font color=red>The application has likely accessed a resource without authorization</font>");
        ui->textBrowserResults->append("------------------------------------");
    }
    //if (passwdInPostQuery)
}
