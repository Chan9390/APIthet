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

void MainWindow::enableProxySlot(int state)
{
    ui->lineEditProxyHost->setEnabled(state);
    ui->spinBoxPort->setEnabled(state);
    ui->checkBoxAuth->setEnabled(state);
}

void MainWindow::enableAuthSlot(int state){
    ui->lineEditUsername->setEnabled(state);
    ui->lineEditPassword->setEnabled(state);
}

void MainWindow::setApplicationProxy()
{
    bool proxyState = false;

    proxyState = ui->checkBoxProxy->isChecked();

    if (proxyState && ui->lineEditProxyHost->text().length()) {
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName(ui->lineEditProxyHost->text());
        proxy.setPort(ui->spinBoxPort->value());
        //proxy.setPort(ui->lineEditProxyPort->text().toUShort());

        //only read proxy parameters if proxy button is set
        //and proxy line edit for IP/name has some length
        if (ui->checkBoxAuth->isEnabled() &&
                ui->lineEditUsername->text().length() &&
                ui->lineEditPassword->text().length())
        {
            proxy.setUser(ui->lineEditUsername->text());
            proxy.setPassword(ui->lineEditPassword->text());

        }
        QNetworkProxy::setApplicationProxy(proxy);
    }
    else {
        //use the system proxy
        QNetworkProxyFactory::setUseSystemConfiguration(true);
    }
}
