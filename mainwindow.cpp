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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    header = new httpHeaders;

    //proxy = new QNetworkProxy;

    //this->setWindowIcon(QIcon(":/icons/APIthet_icon.png"));

    //Set all defaults
    ui->lineEditHeader->setStyleSheet("color: blue");
    ui->lineEditHeaderVal->setStyleSheet("color: blue");
    ui->plainTextEditPayload->setStyleSheet("color: brown");

    ui->lineEditURL->setPlaceholderText("Target URL");
    ui->lineEditRandParam->setPlaceholderText("Randomize JSON");
    //ui->lineEditHeader->setPlaceholderText("Header");
    //ui->lineEditHeader->setPlaceholderText("Header Value");

    ui->lineEditUsername->setPlaceholderText("Username");
    ui->lineEditPassword->setPlaceholderText("Password");

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(10);

    setMethods();
    setEncoding();
    setRandTypes();

    connect(ui->pushButtonRun, SIGNAL(clicked()), this, SLOT(lineURLSlot()));
    connect(ui->comboBoxHTTPMethods, SIGNAL(activated(QString)), this, SLOT(comboBoxHTTPSlot(QString)));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(pushButtonClearSlot()));
    connect(ui->pushButtonAddHeader, SIGNAL(clicked()), this, SLOT(textBrowserHeaderSlot()));
    //connect(ui->pushButtonAddPayload, SIGNAL(clicked()), this, SLOT(textBrowserPayloadSlot()));
    connect(ui->plainTextEditPayload, SIGNAL(textChanged()), this, SLOT(pushButtonEncodeSlot()));
    connect(ui->plainTextEditPayload, SIGNAL(textChanged()), this, SLOT(getRandJsonParam()));
    //connect(ui->pushButtonEncode, SIGNAL(clicked()), this, SLOT(textBrowserEncodeSlot()));
    connect(ui->lineEditHeader, SIGNAL(textChanged(QString)), this, SLOT(pushButtonHeaderSlot()));
    connect(ui->lineEditRandParam, SIGNAL(textChanged(QString)), this, SLOT(comboBoxRandParamSlot()));
    connect(ui->pushButtonRun, SIGNAL(clicked()), this, SLOT(pushButtonRunSlot()));
    connect(ui->checkBoxProxy, SIGNAL(stateChanged(int)), this, SLOT(enableProxySlot(int)));
    connect(ui->checkBoxAuth, SIGNAL(stateChanged(int)), this, SLOT(enableAuthSlot(int)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    //eventLoop.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
