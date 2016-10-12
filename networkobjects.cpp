#include "mainwindow.h"
#include "ui_mainwindow.h"

//Slot to perform HTTP Request
void MainWindow::doHTTPReq()
{
    int httpMethod = ui->comboBoxHTTPMethods->currentIndex();

    //ui->pushButtonAdd->setEnabled(false);

    switch (httpMethod) {
        case 0:
            manager->get(QNetworkRequest(QUrl(ui->lineEdit->text())));
            break;
        case 1:
        {
            QByteArray postData;
            postData.append(ui->textEdit->toPlainText());
            manager->post(QNetworkRequest(QUrl(ui->lineEdit->text())), postData);
        }
            break;
        default:
            manager->get(QNetworkRequest(QUrl(ui->lineEdit->text())));
            break;
    }
}

