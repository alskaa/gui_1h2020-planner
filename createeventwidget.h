#ifndef CREATEEVENTWIDGET_H
#define CREATEEVENTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QTimeEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>

class CreateEventWidget : public QWidget
{
    Q_OBJECT

    QLineEdit   * titleEdit;
    QLineEdit   * descriptionEdit;
    QDateEdit   * dateEdit;
    QTimeEdit   * timeEdit;
public:
    explicit CreateEventWidget(QWidget *parent = 0);

signals:
    void onCancelButtonClicked();
    void onCreateButtonClicked(QJsonObject object);
public slots:
    void cancelCreating();
    void createEvent();
};

#endif // CREATEEVENTWIDGET_H
