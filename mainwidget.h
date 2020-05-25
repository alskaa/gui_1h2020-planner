#ifndef MAINWIDGET_H
#define MAINWIDGET_H

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

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:
    void onAuthorizationButtonClicked();
    void onRegistrationButtonClicked();

private slots:
    void openAuthorizationWidget();
    void openRegistrationWidget();
};

#endif // MAINWIDGET_H
