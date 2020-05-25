#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent){
    QVBoxLayout * layout = new QVBoxLayout();
    this->setLayout(layout);

    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    QPushButton * signOutButton = new QPushButton("sign out", this);
    QPushButton * createEventButton = new QPushButton("create event", this);
    QPushButton * createTemplateButton = new QPushButton("create template", this);
    QPushButton * eventsButton = new QPushButton("my events", this);
    eventsButton->setStyleSheet("QPushButton { border-image:url(:resource/folder.png);} QPushButton:hover:!pressed{border: 3px solid black;}");
    QPushButton * currentEventsButton = new QPushButton("current events", this);
    currentEventsButton->setStyleSheet("QPushButton { border-image:url(:resource/folder.png);} QPushButton:hover:!pressed{border: 3px solid black;}");
    currentEventsButton->setFixedSize(100,80);
    QPushButton * templatesButton = new QPushButton("my templates", this);
    eventsButton->setFixedSize(100,80);
    templatesButton->setStyleSheet("QPushButton { border-image:url(:resource/folder.png);} QPushButton:hover:!pressed{border: 3px solid black;}");
    QSpacerItem* spacer = new QSpacerItem(100, 100);
    QSpacerItem* eventSpacer = new QSpacerItem(50, 100);
    templatesButton->setFixedSize(100,80);

    QHBoxLayout * eventLayout = new QHBoxLayout();
    eventLayout->addItem(eventSpacer);
    eventLayout->addWidget(eventsButton);
    eventLayout->addItem(eventSpacer);
    eventLayout->addWidget(currentEventsButton);
    eventLayout->addItem(eventSpacer);

    QHBoxLayout * templateLayout = new QHBoxLayout();
    templateLayout->addItem(spacer);
    templateLayout->addWidget(templatesButton);
    templateLayout->addItem(spacer);

    layout->addWidget(label);
    layout->addWidget(signOutButton);
    layout->addItem(new QSpacerItem(100, 20));
    layout->addWidget(createEventButton);
    layout->addWidget(createTemplateButton);
    layout->addItem(new QSpacerItem(100, 200));
    layout->addItem(eventLayout);
    layout->addItem(new QSpacerItem(100, 50));
    layout->addItem(templateLayout);
    layout->addItem(new QSpacerItem(100, 200));

    connect(signOutButton, SIGNAL(clicked()), this, SLOT(returnToMenu()));
    connect(createEventButton, SIGNAL(clicked()), this, SLOT(createEvent()));
    connect(createTemplateButton, SIGNAL(clicked()), this, SLOT(createTemplate()));
    connect(eventsButton, SIGNAL(clicked()), this, SLOT(openEvents()));
    connect(currentEventsButton, SIGNAL(clicked()), this, SLOT(openCurrentEvents()));
    connect(templatesButton, SIGNAL(clicked()), this, SLOT(openTemplates()));
}

void MenuWidget::returnToMenu(){
    emit (onSignOutButtonClicked());
}

void MenuWidget::createEvent(){
    emit (onCreateEventButtonClicked());
}

void MenuWidget::createTemplate(){
    emit (onCreateTemplateButtonClicked());
}

void MenuWidget::openEvents(){
    emit (onEventsButtonClicked());
}

void MenuWidget::openCurrentEvents(){
    emit (onCurrentEventsButtonClicked());
}

void MenuWidget::openTemplates(){
    emit (onTemplatesButtonClicked());
}
