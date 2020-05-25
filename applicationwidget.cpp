#include "applicationwidget.h"

ApplicationWidget::ApplicationWidget(QWidget *parent) : QWidget(parent){
    networkClient = new NetworkClient();
    createEventWidget = new CreateEventWidget();
    createTemplateWidget = new CreateTemplateWidget();
    menuWidget = new MenuWidget();
    menuWidget->setGeometry(0,0,200,800);

    layout = new QHBoxLayout(this);
    this->setLayout(layout);

    QPalette pal = palette();

    model = new QStringListModel(this);
    view = new QListView(this);
    view->setModel(model);

    widgets = new QStackedWidget();
    widgets->addWidget(view);
    widgets->addWidget(createEventWidget);
    widgets->addWidget(createTemplateWidget);
    widgets->setCurrentWidget(view);
    widgets->setGeometry(200,0,800,800);


    layout->addWidget(menuWidget);

    listLayout = new QVBoxLayout(this);
    listTitle = new QLabel("Today to do list", this);
    listTitle->setAlignment(Qt::AlignCenter);
    listLayout->addWidget(listTitle);
    listLayout->addWidget(widgets);
    layout->addLayout(listLayout);

    connect(menuWidget, SIGNAL(onSignOutButtonClicked()), this, SLOT(returnToMenu()));
    connect(menuWidget, SIGNAL(onCreateEventButtonClicked()), this, SLOT(openCreateEventWidget()));
    connect(menuWidget, SIGNAL(onCreateTemplateButtonClicked()), this, SLOT(openCreateTemplateWidget()));
    connect(menuWidget, SIGNAL(onEventsButtonClicked()), this, SLOT(getEvents()));
    connect(menuWidget, SIGNAL(onTemplatesButtonClicked()), this, SLOT(getTemplates()));
    connect(menuWidget, SIGNAL(onCurrentEventsButtonClicked()), this, SLOT(openCurrentView()));

    connect(createEventWidget, SIGNAL(onCancelButtonClicked()), this, SLOT(openCurrentView()));
    connect(createEventWidget, SIGNAL(onCreateButtonClicked(QJsonObject)), this, SLOT(createEvent(QJsonObject)));
    connect(createTemplateWidget, SIGNAL(onCancelButtonClicked()), this, SLOT(openCurrentView()));
    connect(createTemplateWidget, SIGNAL(onCreateButtonClicked(QJsonObject)), this, SLOT(createTemplate(QJsonObject)));
    connect(networkClient, SIGNAL(responce(QJsonObject)), this, SLOT(getResponce(QJsonObject)));

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(deleteElement(QModelIndex)));
}

void ApplicationWidget::setUpUser(QString id, QString token){
    this->id = id;
    this->token = token;

}

void ApplicationWidget::returnToMenu(){
    emit (onSignOutButtonClicked());
}

void ApplicationWidget::deleteElement(QModelIndex index) {
    if(model->stringList() == eventsList) {
        status = "deleteevent";
        QJsonArray eventJsonArray = curUser.value("events").toArray();
        QString eventId = eventJsonArray.at(index.row()).toObject().value("id").toString();
        networkClient->deleteRequest("http://localhost:8080/api/v1/events/" + eventId,
                                  "Bearer " + token);
    } else if (model->stringList() == currentEventsList) {
        status = "deletecurevent";
        QString eventId = curEventsArray.at(index.row()).toObject().value("id").toString();
        networkClient->deleteRequest("http://localhost:8080/api/v1/events/" + eventId,
                                  "Bearer " + token);
    } else if (model->stringList() == templatesList) {
        status = "deletetemplate";
        QJsonArray templateJsonArray = curUser.value("templates").toArray();
        QString templateId = templateJsonArray.at(index.row()).toObject().value("id").toString();
        networkClient->deleteRequest("http://localhost:8080/api/v1/templates/" + templateId,
                                  "Bearer " + token);
    }
}

void ApplicationWidget::openCreateEventWidget(){
    listTitle->setText("");
    widgets->setCurrentWidget(createEventWidget);
}

void ApplicationWidget::openCreateTemplateWidget(){
    listTitle->setText("");
    widgets->setCurrentWidget(createTemplateWidget);
}


void ApplicationWidget::getCurrentUser(){
    status = "getcurrentuser";
    networkClient->getRequest("http://localhost:8080/api/v1/users/" + id,
                              "Bearer " + token);
}


void ApplicationWidget::createEvent(QJsonObject object){
    status = "createevent";
    object.insert("ownerId", id);
    networkClient->postRequest(object, "http://localhost:8080/api/v1/events/", "Bearer " + token);
}

void ApplicationWidget::createTemplate(QJsonObject object){
    status = "createtemplate";
    object.insert("ownerId", id);
    networkClient->postRequest(object, "http://localhost:8080/api/v1/templates/", "Bearer " + token);
}

void ApplicationWidget::getEvents(){
    listTitle->setText("My events list");
    eventsList.clear();
    QJsonArray eventJsonArray = curUser.value("events").toArray();
    if(!eventJsonArray.isEmpty()) {
        for(QJsonValueRef event: eventJsonArray) {
            QJsonObject object = event.toObject();
            QDateTime dateTime = QDateTime::fromString(object.value("time").toString(), "yyyy-MM-ddThh:mm:ss.zzz+0000");
            QString eventString = "time: " + dateTime.toString("dd.MM.yyyy hh:mm") +
                    "\ntitle: " + object.value("title").toString() +
                    "\ndescription: " + object.value("description").toString() + "\n";
            eventsList.append(eventString);
        }
    }
    model->setStringList(eventsList);
    widgets->setCurrentWidget(view);
}

void ApplicationWidget::getTemplates(){
    listTitle->setText("My templates list");
    templatesList.clear();
    QJsonArray templateJsonArray = curUser.value("templates").toArray();
    if(!templateJsonArray.isEmpty()) {
        for(QJsonValueRef templ: templateJsonArray) {
            QJsonObject object = templ.toObject();
            QString eventString = "title: " + object.value("title").toString() +
                    "\ndescription: " + object.value("description").toString() + "\n";
            templatesList.append(eventString);
        }
    }
    model->setStringList(templatesList);
    widgets->setCurrentWidget(view);
}

void ApplicationWidget::openCurrentView(){
    listTitle->setText("Today to do list");
    currentEventsList.clear();
    curEventsArray.empty();
    QJsonArray eventJsonArray = curUser.value("events").toArray();
    if(!eventJsonArray.isEmpty()) {
        for(QJsonValueRef event: eventJsonArray) {
            QJsonObject object = event.toObject();
            QDateTime dateTime = QDateTime::fromString(object.value("time").toString(), "yyyy-MM-ddThh:mm:ss.zzz+0000");
            if(dateTime.date() == QDate::currentDate()) {
                curEventsArray.append(object);
                QString eventString = "time: " + dateTime.toString("dd.MM.yyyy hh:mm") +
                        "\ntitle: " + object.value("title").toString() +
                        "\ndescription: " + object.value("description").toString() + "\n";
                currentEventsList.append(eventString);
            }
        }
    }
    model->setStringList(currentEventsList);
    widgets->setCurrentWidget(view);
}

void ApplicationWidget::getResponce(QJsonObject object) {
    if (status == "getcurrentuser") {
        curUser = object;
        menuWidget->label->setText(curUser.value("username").toString());
        if(model->stringList() == eventsList) {
            getEvents();
        }else if (model->stringList() == templatesList) {
            getTemplates();
        } else {
            openCurrentView();
        }
    } else {
        getCurrentUser();
    }
    return;
}
