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

void MainWindow::setDefault()
{
    csrfPayload = false;
    csrfIssueLikely = false;
    headerHasAuth = false;
    hasQueryParams = false;
    likelyUnauth = false;
    passwdInGetQuery = false;
    passwdInPostQuery = false;
    postQueryHasBody = false;

    //initilize the count of absent headers to 0
    contentHeaderMissed = 0;
    xFrameHeaderMissed = 0;
    xContentHeaderMissed = 0;
    hstsHeaderMissed = 0;
    xssProtHeaderMissed = 0;

}
