#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setContentsMargins(400, 300, 400, 400);
    QLabel *helloLabel = new QLabel("Welcome to CurEvent!", this);
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(helloLabel);
    helloLabel->setAlignment(Qt::AlignCenter);

    QPushButton *authorizationButton = new QPushButton("sign in", this);
    QPushButton *registrationButton = new QPushButton("sign up", this);
    QSpacerItem *spacer = new QSpacerItem(30, 10);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(authorizationButton);
    buttonLayout->addItem(spacer);
    buttonLayout->addWidget(registrationButton);

    layout->addItem(labelLayout);
    layout->addItem(buttonLayout);

    connect(authorizationButton, SIGNAL(clicked()), this, SLOT(openAuthorizationWidget()));
    connect(registrationButton, SIGNAL(clicked()), this, SLOT(openRegistrationWidget()));
}

void MainWidget::openAuthorizationWidget(){
    emit(onAuthorizationButtonClicked());
}

void MainWidget::openRegistrationWidget(){
    emit(onRegistrationButtonClicked());
}

