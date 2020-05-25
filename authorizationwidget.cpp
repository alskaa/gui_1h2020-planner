#include "authorizationwidget.h"

AuthorizationWidget::AuthorizationWidget(QWidget *parent) : QWidget(parent){
    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setContentsMargins(300, 200, 300, 200);

    QLabel *authLabel = new QLabel("authorization", this);
    authLabel->setAlignment(Qt::AlignCenter);

    QLabel *usernameLabel = new QLabel("username:", this);
    usernameLabel->setAlignment(Qt::AlignCenter);

    QLabel *passwordLabel = new QLabel("password:", this);
    passwordLabel->setAlignment(Qt::AlignCenter);

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    QPushButton *authorizationButton = new QPushButton("sign in", this);
    QPushButton *backButton = new QPushButton("back to main menu", this);

    layout->addWidget(authLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(authorizationButton);
    layout->addWidget(backButton);

    connect(backButton, SIGNAL(clicked()), this, SLOT(returnToMenu()));
    connect(authorizationButton, SIGNAL(clicked()), this, SLOT(signIn()));
}

void AuthorizationWidget::returnToMenu(){
    emit(onBackButtonClicked());
}


void AuthorizationWidget::signIn(){
    if ((passwordEdit->text() == "") || (usernameEdit -> text() == "")) {
        QMessageBox::information(this, trUtf8("error"), "Please, input all data", QMessageBox::Ok);
        return;
    }
    QJsonObject json;
    json.insert("password", passwordEdit->text());
    json.insert("username", usernameEdit -> text());

    emit (onSignInButtonClicked(json));
}

