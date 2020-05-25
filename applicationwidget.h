#ifndef APPLICATIONWIDGET_H
#define APPLICATIONWIDGET_H

#include "menuwidget.h"
#include "createeventwidget.h"
#include "createtemplatewidget.h"
#include "networkclient.h"

#include <QWidget>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLineEdit>
#include <QSpacerItem>
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QListView>
#include <QStackedWidget>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStringList>
#include <QDateTime>
#include <QModelIndex>

class ApplicationWidget : public QWidget
{
    Q_OBJECT
    NetworkClient         * networkClient;
    MenuWidget            * menuWidget;
    CreateEventWidget     * createEventWidget;
    CreateTemplateWidget  * createTemplateWidget;
    QStringListModel      * model;
    QListView             * view;
    QLabel                * title;
    QLabel                * listTitle;
    QStackedWidget        * widgets;

    QHBoxLayout           * layout;
    QVBoxLayout           * listLayout;    

    QStringList           currentEventsList;
    QStringList           eventsList;
    QStringList           templatesList;

    QString               status;
    QString               token;
    QString               id;
    QJsonObject           curUser;
    QJsonArray            curEventsArray;


public:
    explicit ApplicationWidget(QWidget *parent = 0);
    void setUpUser(QString id, QString token);
    void getCurrentUser();

signals:
     void onSignOutButtonClicked();

public slots:
     void returnToMenu();
     void deleteElement(QModelIndex index);
     void openCreateEventWidget();
     void openCreateTemplateWidget();
     void getEvents();
     void getTemplates();
     void openCurrentView();
     void getResponce(QJsonObject object);
     void createEvent(QJsonObject object);
     void createTemplate(QJsonObject object);
};

#endif // APPLICATIONWIDGET_H
