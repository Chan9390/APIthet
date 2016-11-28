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

httpHeaders::httpHeaders() {
    numHeaders = 0;
}

void httpHeaders::incrementHeaders() {
    ++numHeaders;
}

void httpHeaders::decrementHeaders() {
    if (numHeaders)
        --numHeaders;
}

void httpHeaders::insertHeader(QString hdrStr , QString hdrValStr) {
    header.append(hdrStr);
    headerVal.append(hdrValStr);
}

bool httpHeaders::hasElements() {
    if (numHeaders)
        return true;
    return false;
}

bool httpHeaders::isEmpty() {
    if (!numHeaders)
        return true;
    return false;
}

QString httpHeaders::getLastHeader() {
    if (numHeaders)
        return header.takeLast();
    return NULL;
}

QString httpHeaders::getLastHeaderVal()
{
    if (numHeaders)
        return headerVal.takeLast();
    return NULL;
}

void httpHeaders::clearList()
{
    header.clear();
    headerVal.clear();
    numHeaders = 0;
}

uint httpHeaders::getHeaderCount()
{
    return numHeaders;
}
