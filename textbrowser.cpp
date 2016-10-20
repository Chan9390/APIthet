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

void MainWindow::textBrowserHeaderSlot()
{
    headerHasAuth = false;
    ui->textBrowser->clear();
    if (ui->lineEditHeader->text().length()) {
        header->incrementHeaders();
        header->insertHeader(ui->lineEditHeader->text(),
                            ui->lineEditHeaderVal->text());

        ui->textBrowser->append(ui->lineEditHeader->text());
        ui->textBrowser->insertPlainText(" : ");
        ui->textBrowser->insertPlainText(ui->lineEditHeaderVal->text());
        ui->textBrowser->append
                ("<font color=orange>was added to the request header</font>");

        //check if the header is an auth header
        if ((ui->lineEditHeaderVal->text().length()) &&
                ((ui->lineEditHeader->text().contains("key")) ||
                (ui->lineEditHeader->text().contains("auth")) ||
                (ui->lineEditHeader->text().contains("token")) ||
                (ui->lineEditHeader->text().contains("authentication"))
                ))
            headerHasAuth = true;
    }

    ui->lineEditHeader->clear();
    ui->lineEditHeaderVal->clear();
}

void MainWindow::textBrowserPayloadSlot()
{
    ui->textBrowser->clear();
    if (ui->plainTextEditPayload->toPlainText().length()) {
        ui->textBrowser->append(ui->plainTextEditPayload->toPlainText());
    }
    else
        ui->textBrowser->append("<font color=orange>empty payload, not added</font>");
}

void MainWindow::textBrowserEncodeSlot()
{
    ui->textBrowser->clear();

    QTextCursor cursor = ui->plainTextEditPayload->textCursor();

    cursor.beginEditBlock();
    cursor.setPosition(QTextCursor::PreviousCharacter, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    cursor.endEditBlock();

    //cursor.insertText("Hello World");

    //ui->textBrowser->append("<font color=orange>select text to encode...</font>");
}
