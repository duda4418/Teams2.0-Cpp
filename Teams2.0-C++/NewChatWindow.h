#ifndef NEWCHATWINDOW_H
#define NEWCHATWINDOW_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

class NewChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewChatWindow(QWidget* parent = nullptr);

signals:
    void contactSelected(const QString& contactName);

private slots:
    void selectContact();

private:
    QListWidget* contactList;
    QPushButton* selectButton;
};

#endif // NEWCHATWINDOW_H
