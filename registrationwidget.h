#ifndef REGISTRATIONWIDGET_H
#define REGISTRATIONWIDGET_H

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
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <regex>

class RegistrationWidget : public QWidget
{
    Q_OBJECT
    QLineEdit       * usernameEdit;
    QLineEdit       * passwordEdit;
    QLineEdit       * emailEdit;

public:
    explicit RegistrationWidget(QWidget *parent = 0);

signals:
    void onBackButtonClicked();
    void onSignUpButtonClicked(QJsonObject object);

private slots:
    void returnToMenu();
    void signUp();
};

#endif // REGISTRATIONWIDGET_H
