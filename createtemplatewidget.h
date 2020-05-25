#ifndef CREATETEMPLATEWIDGET_H
#define CREATETEMPLATEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDebug>
#include <QJsonObject>
#include <QMessageBox>

class CreateTemplateWidget : public QWidget
{
    Q_OBJECT
    QLineEdit   * titleEdit;
    QLineEdit   * descriptionEdit;
public:
    explicit CreateTemplateWidget(QWidget *parent = 0);

signals:
    void onCancelButtonClicked();
    void onCreateButtonClicked(QJsonObject object);
public slots:
    void cancelCreating();
    void createTemplate();
};

#endif // CREATETEMPLATEWIDGET_H
