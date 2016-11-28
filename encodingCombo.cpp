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

//Set the correct Encoding
void APIthet::setEncoding()
{
    //QComboBox *comboBoxEncode = ui->comboBoxEncode;
    QStringList encodeList;

    //Add HTTP Methods to the list
    encodeList << "Plain" << "URL" << "HTML" << "Base64" << "ASCII hex" << "Octal" << "Binary" << "Gzip";

    //Assign the string list to the combobox
    //comboBoxEncode->addItems(encodeList);
}
