#-----------------------------------------------------------------------------
#
#    Copyright [2016] [mail.gulpfriction@gmail.com]
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#-----------------------------------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = APIthet
TEMPLATE = app


SOURCES += main.cpp\
    pushButtonEncode.cpp \
    pushButtonHeader.cpp \
    pushButtonRun.cpp \
    httpSendOperations.cpp \
    processHttpReq.cpp \
    httpRecvOperations.cpp \
    setProxySetting.cpp \
    linkedListMethods.cpp \
    webUtils.cpp \
    jsonUtils.cpp \
    payloadUtils.cpp \
    lineEditUrl.cpp \
    encodingCombo.cpp \
    httpCombo.cpp \
    randTypeCombo.cpp \
    randParamText.cpp \
    setDefaults.cpp \
    pushButtonClear.cpp \
    resultTab.cpp \
    postAttacks.cpp \
    getAttacks.cpp \
    apithet.cpp \
    textBrowser.cpp

HEADERS  += \
    apithet.h

FORMS    += \
    APIthet.ui

RESOURCES += \
    APIthetResource.qrc
win32:RC_ICONS += icons/APIthet.ico

QMAKE_LFLAGS += -static -static-libgcc
CONFIG-=console
DISTFILES +=

