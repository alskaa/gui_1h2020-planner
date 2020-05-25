#include "createtemplatewidget.h"

CreateTemplateWidget::CreateTemplateWidget(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setContentsMargins(200, 200, 200, 200);

    QLabel *mainLabel = new QLabel("create template", this);
    mainLabel->setAlignment(Qt::AlignCenter);

    QLabel * titleLabel = new QLabel("title:", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QLabel *descriptionLabel = new QLabel("description:", this);
    descriptionLabel->setAlignment(Qt::AlignCenter);

    titleEdit = new QLineEdit(this);
    descriptionEdit = new QLineEdit(this);
    QPushButton *createButton = new QPushButton("create", this);
    QPushButton *backButton = new QPushButton("cancel", this);

    layout->addWidget(mainLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);

    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(backButton);

    layout->addItem(buttonLayout);
    connect(backButton, SIGNAL(clicked()), this, SLOT(cancelCreating()));
    connect(createButton, SIGNAL(clicked()), this, SLOT(createTemplate()));
}

void CreateTemplateWidget::cancelCreating(){
    emit (onCancelButtonClicked());
}

void CreateTemplateWidget::createTemplate(){
    if ((descriptionEdit->text() == "") || (titleEdit->text() == "")) {
        QMessageBox::information(this, trUtf8("error"), "Please, input all data", QMessageBox::Ok);
        return;
    }
    QJsonObject json;
    json.insert("title", titleEdit->text());
    json.insert("description", descriptionEdit->text());
    emit (onCreateButtonClicked(json));
}
