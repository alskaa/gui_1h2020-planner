#ifndef MENUWIDGET_H
#define MENUWIDGET_H

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

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    QLabel  * label;
    explicit MenuWidget(QWidget *parent = 0);

signals:
    void onSignOutButtonClicked();
    void onCreateEventButtonClicked();
    void onCreateTemplateButtonClicked();
    void onCurrentEventsButtonClicked();
    void onEventsButtonClicked();
    void onTemplatesButtonClicked();

private slots:
    void returnToMenu();
    void createEvent();
    void createTemplate();
    void openEvents();
    void openTemplates();
    void openCurrentEvents();
};

#endif // MENUWIDGET_H
