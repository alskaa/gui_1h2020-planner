#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setGeometry((QApplication::desktop()->availableGeometry().width() - 1200)/2,
                      (QApplication::desktop()->availableGeometry().height() - 800)/2,
                      1200,800);
    this->setFixedSize(1200,800);
    widgets = new QStackedWidget(this);
    mainWidget = new MainWidget(this);
    authorizationWidget = new AuthorizationWidget(this);
    registrationWidget = new RegistrationWidget(this);
    applicationWidget = new ApplicationWidget(this);
    networkClient = new NetworkClient(this);

    widgets->addWidget(mainWidget);
    widgets->addWidget(authorizationWidget);
    widgets->addWidget(registrationWidget);
    widgets->addWidget(applicationWidget);

    connect(mainWidget, SIGNAL(onAuthorizationButtonClicked()), this, SLOT(openAuthorizationWidget()));
    connect(mainWidget, SIGNAL(onRegistrationButtonClicked()), this, SLOT(openRegistrationWidget()));
    connect(registrationWidget, SIGNAL(onBackButtonClicked()), this, SLOT(openMainWidget()));
    connect(authorizationWidget, SIGNAL(onBackButtonClicked()), this, SLOT(openMainWidget()));
    connect(authorizationWidget, SIGNAL(onSignInButtonClicked(QJsonObject)), this, SLOT(signIn(QJsonObject)));
    connect(registrationWidget, SIGNAL(onSignUpButtonClicked(QJsonObject)), this, SLOT(signUp(QJsonObject)));
    connect(applicationWidget, SIGNAL(onSignOutButtonClicked()), this, SLOT(openMainWidget()));
    connect(networkClient, SIGNAL(responce(QJsonObject)), this, SLOT(getResponce(QJsonObject)));

    this->setCentralWidget(widgets);

    openMainWidget();
}


void MainWindow::openAuthorizationWidget(){
   widgets->setCurrentWidget(authorizationWidget);
}

void MainWindow::openRegistrationWidget(){
   widgets->setCurrentWidget(registrationWidget);
}

void MainWindow::openMainWidget() {
    widgets->setCurrentWidget(mainWidget);
}

void MainWindow::openApplicationWidget(QJsonObject object) {
    applicationWidget->setUpUser(object.value("id").toString(), object.value("token").toString());
    applicationWidget->getCurrentUser();
    widgets->setCurrentWidget(applicationWidget);
}

void MainWindow::signIn(QJsonObject object) {
    networkClient->postRequest(object, "http://localhost:8080/api/v1/login","");
    status = "signin";
}

void MainWindow::signUp(QJsonObject object) {
    networkClient->postRequest(object, "http://localhost:8080/api/v1/register","");
    status = "signup";
}

void MainWindow::getWhoAmI(QJsonObject object) {
    networkClient->getRequest("http://localhost:8080/api/v1/whoami","Bearer " + object.value("access_token").toString());
    status = "whoami";
}


void MainWindow::getResponce(QJsonObject object) {
    if (object.contains("message")) {
        QMessageBox::information(this, trUtf8("error"), object.value("message").toString(), QMessageBox::Ok);
        return;
    }
    if (status == "signin" || status == "signup") {
        token = object.value("access_token");
        getWhoAmI(object);
    } else if (status == "whoami") {
        object.insert("token", token.toString());
        openApplicationWidget(object);
    }
    return;
}

