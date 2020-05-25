#include "createeventwidget.h"

CreateEventWidget::CreateEventWidget(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setContentsMargins(200, 200, 200, 200);

    QLabel *mainLabel = new QLabel("create event", this);
    mainLabel->setAlignment(Qt::AlignCenter);

    QLabel * titleLabel = new QLabel("title:", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QLabel *descriptionLabel = new QLabel("description:", this);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    QLabel *dateLabel = new QLabel("date:", this);
    dateLabel->setAlignment(Qt::AlignCenter);
    QLabel *timeLabel = new QLabel("time:", this);
    timeLabel->setAlignment(Qt::AlignCenter);

    titleEdit = new QLineEdit(this);
    descriptionEdit = new QLineEdit(this);
    dateEdit = new QDateEdit(this);
    dateEdit->setDate(QDate::currentDate());
    timeEdit = new QTimeEdit(this);
    timeEdit->setTime(QTime::currentTime());
    QPushButton *createButton = new QPushButton("create", this);
    QPushButton *backButton = new QPushButton("cancel", this);

    layout->addWidget(mainLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);
    layout->addWidget(descriptionLabel);
    layout->addWidget(descriptionEdit);
    layout->addWidget(dateLabel);
    layout->addWidget(dateEdit);
    layout->addWidget(timeLabel);
    layout->addWidget(timeEdit);

    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(backButton);

    layout->addItem(buttonLayout);
    this->connect(backButton, SIGNAL(clicked()), this, SLOT(cancelCreating()));
    this->connect(createButton, SIGNAL(clicked()), this, SLOT(createEvent()));
}

void CreateEventWidget::cancelCreating(){
    emit (onCancelButtonClicked());
}

void CreateEventWidget::createEvent(){
    if ((descriptionEdit->text() == "") || (titleEdit->text() == "")) {
        QMessageBox::information(this, trUtf8("error"), "Please, input all data", QMessageBox::Ok);
        return;
    }
    QJsonObject json;
    QDate date = dateEdit->date();
    QTime time = timeEdit->time();
    QDateTime dateTime;
    dateTime.setDate(date);
    dateTime.setTime(time);
    json.insert("time", dateTime.toString("yyyy-MM-ddThh:mm:ss.zzz"));
    json.insert("title", titleEdit->text());
    json.insert("description", descriptionEdit->text());
    emit (onCreateButtonClicked(json));
}
