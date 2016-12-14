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
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication apithetApp(argc, argv);

#if QT_NO_DEBUG
    QPixmap pixmap(":/icons/APIthet_banner.png");
    QSplashScreen splash(pixmap);
    splash.show();
    QThread::sleep(7);
#endif

    APIthet appWindow;
    apithetApp.setWindowIcon(QIcon(APPICON));
    appWindow.show();

#if QT_NO_DEBUG
    splash.finish(&appWindow);
#endif

    return apithetApp.exec();
}
