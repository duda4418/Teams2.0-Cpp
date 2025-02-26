#ifndef CHATAPP_H
#define CHATAPP_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

class ChatApp : public QMainWindow
{
    Q_OBJECT

public:
    ChatApp(QWidget* parent = nullptr);
    ~ChatApp();

private slots:
    void sendMessage();
    void startNewChat();

private:
    QWidget* centralWidget;
    QPushButton* newChatButton;
    QListWidget* chatList;
    QTextEdit* chatDisplay;
    QLineEdit* messageInput;
    QPushButton* sendButton;
};

#endif // CHATAPP_H
