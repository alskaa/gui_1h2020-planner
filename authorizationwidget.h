#ifndef AUTHORIZATIONFORM_H
#define AUTHORIZATIONFORM_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLineEdit>
#include <QSpacerItem>
#include <QMessageBox>
#include <QJsonObject>
#include <QApplication>
#include <QDesktopWidget>

class AuthorizationWidget : public QWidget
{
    Q_OBJECT
    QLineEdit       * usernameEdit;
    QLineEdit       * passwordEdit;

public:
    explicit AuthorizationWidget(QWidget *parent = 0);

signals:
    void onBackButtonClicked();
    void onSignInButtonClicked(QJsonObject object);

private slots:
    void returnToMenu();
    void signIn();

};

#endif // AUTHORIZATIONFORM_H
