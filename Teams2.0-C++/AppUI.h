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
#include <QMap>
#include <memory>  // For std::unique_ptr
#include "Discussions.h"
#include "Messages.h"
#include "Message.h"  // Include the new Message header

class ChatApp : public QMainWindow
{
    Q_OBJECT

public:
    ChatApp(QWidget* parent = nullptr);
    ~ChatApp();

    // Set the current user ID
    void setCurrentUserId(const std::string& userId);

private slots:
    void sendMessage();
    void openNewChatWindow();
    void startNewChat(const QString& contactName);
    void onChatSelected(QListWidgetItem* item);
    void loadUserChats();

private:
    QWidget* centralWidget;
    QPushButton* newChatButton;
    QListWidget* chatList;
    QTextEdit* chatDisplay;
    QLineEdit* messageInput;
    QPushButton* sendButton;

    std::string currentUserId;
    QString currentContactName;
    std::string currentDiscussionId;
    Discussions discussionsManager;
    Messages messagesManager;

    // Map to keep track of contact names and their discussion IDs
    QMap<QString, QString> contactDiscussionMap;

    void displayChatHistory(const std::string& discussionId);
};

#endif // CHATAPP_H