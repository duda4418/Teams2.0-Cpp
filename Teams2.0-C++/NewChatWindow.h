#ifndef NEWCHATWINDOW_H
#define NEWCHATWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "json.hpp"

using json = nlohmann::json;

class NewChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewChatWindow(QWidget* parent = nullptr);

signals:
    void contactSelected(const QString& contactName);

private slots:
    void selectContact();
    void loadContactsFromDatabase();

private:
    QListWidget* contactList;
    QPushButton* selectButton;
};

#endif // NEWCHATWINDOW_H