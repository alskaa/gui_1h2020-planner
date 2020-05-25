#include "registrationwidget.h"

RegistrationWidget::RegistrationWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setContentsMargins(300, 200, 300, 200);

    QLabel *regLabel = new QLabel("registration", this);
    regLabel->setAlignment(Qt::AlignCenter);

    QLabel *usernameLabel = new QLabel("username:", this);
    usernameLabel->setAlignment(Qt::AlignCenter);
    QLabel *passwordLabel = new QLabel("password:", this);
    passwordLabel->setAlignment(Qt::AlignCenter);
    QLabel *emailLabel = new QLabel("email:", this);
    emailLabel->setAlignment(Qt::AlignCenter);

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    emailEdit = new QLineEdit(this);
    QPushButton *registrationButton = new QPushButton("sign up", this);
    QPushButton *backButton = new QPushButton("back to main menu", this);

    layout->addWidget(regLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(emailLabel);
    layout->addWidget(emailEdit);
    layout->addWidget(registrationButton);
    layout->addWidget(backButton);

    connect(backButton, SIGNAL(clicked()), this, SLOT(returnToMenu()));
    connect(registrationButton, SIGNAL(clicked()), this, SLOT(signUp()));
}

void RegistrationWidget::returnToMenu(){
    emit(onBackButtonClicked());
}

void RegistrationWidget::signUp(){
    if ((emailEdit->text() == "") || (passwordEdit->text() == "") || (usernameEdit -> text() == "")) {
        QMessageBox::information(this, trUtf8("error"), "Please, input all data", QMessageBox::Ok);
        return;
    }
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if (!std::regex_match(emailEdit->text().toStdString(),pattern)) {
        QMessageBox::information(this, trUtf8("error"), "Email is not corect", QMessageBox::Ok);
        return;
    }
    QJsonObject json;
    json.insert("email", emailEdit->text());
    json.insert("password", passwordEdit->text());
    json.insert("username", usernameEdit -> text());
    emit (onSignUpButtonClicked(json));
}
