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

//Slot to handle events after clear button is pressed
void APIthet::pushButtonClearSlot()
{
    ui->lineEditHeader->clear();
    ui->lineEditHeaderVal->clear();
    ui->lineEditURL->clear();
    ui->plainTextEditPayload->clear();
    ui->lineEditHeader->clear();
    ui->lineEditHeaderVal->setEnabled(false);
    ui->lineEditRandParam->clear();
    ui->lineEditRandParam->setEnabled(false);
    header->clearList();

    ui->comboBoxRandParam->setCurrentIndex(0);
    //ui->comboBoxRandParam->setEnabled(false);

    ui->textBrowserResults->clear();

    setDefault();
}
