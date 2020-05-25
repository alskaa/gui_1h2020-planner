#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authorizationwidget.h"
#include "mainwidget.h"
#include "registrationwidget.h"
#include "applicationwidget.h"
#include "networkclient.h"

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QStackedWidget>
#include <QJsonObject>
#include <QMessageBox>
#include <QString>

class MainWindow : public QMainWindow {
    Q_OBJECT
    NetworkClient       * networkClient;
    QStackedWidget      * widgets;
    AuthorizationWidget * authorizationWidget;
    MainWidget          * mainWidget;
    RegistrationWidget  * registrationWidget;
    ApplicationWidget   * applicationWidget;

    QString         status;
    QJsonValue      token;

    void getWhoAmI(QJsonObject object);
    void openApplicationWidget(QJsonObject object);

public:
    explicit MainWindow(QWidget *parent = 0);

signals:
    void onSignOutButtonClicked();

public slots:
    void signIn(QJsonObject object);
    void signUp(QJsonObject object);
    void openAuthorizationWidget();
    void openRegistrationWidget();
    void openMainWidget();
    void getResponce(QJsonObject object);
};



#endif // MAINWINDOW_H
