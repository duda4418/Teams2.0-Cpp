#include "AppUI.h"
#include "NewChatWindow.h"
#include "Globals.h"
#include "FakeDb.h"
#include "Message.h"
#include "MessageFactory.h"

ChatApp::ChatApp(QWidget* parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Chat App");
    resize(900, 600);

    newChatButton = new QPushButton("New Chat");
    newChatButton->setStyleSheet("background-color: #F7B500; font-size: 16px; padding: 10px; border-radius: 10px;");

    chatList = new QListWidget();

    QVBoxLayout* sidebarLayout = new QVBoxLayout();
    sidebarLayout->addWidget(newChatButton);
    sidebarLayout->addWidget(chatList);
    sidebarLayout->setSpacing(10);

    QWidget* sidebarWidget = new QWidget();
    sidebarWidget->setLayout(sidebarLayout);
    sidebarWidget->setFixedWidth(250);
    sidebarWidget->setStyleSheet("background-color: #2F4F5F; padding: 10px; border-radius: 10px;");

    chatDisplay = new QTextEdit();
    chatDisplay->setReadOnly(true);
    chatDisplay->setStyleSheet("background-color: white; border: 1px solid gray; font-size: 14px;");

    messageInput = new QLineEdit();
    messageInput->setPlaceholderText("Type a message...");
    messageInput->setStyleSheet("padding: 8px; border: 1px solid gray; font-size: 14px;");

    sendButton = new QPushButton("Send");
    sendButton->setStyleSheet("background-color: #F7B500; font-size: 16px; padding: 10px; border-radius: 10px;");

    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);

    QVBoxLayout* chatLayout = new QVBoxLayout();
    chatLayout->addWidget(chatDisplay);
    chatLayout->addLayout(inputLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(sidebarWidget);
    mainLayout->addLayout(chatLayout);

    connect(sendButton, &QPushButton::clicked, this, &ChatApp::sendMessage);
    connect(newChatButton, &QPushButton::clicked, this, &ChatApp::openNewChatWindow);
    connect(chatList, &QListWidget::itemClicked, this, &ChatApp::onChatSelected);
}

void ChatApp::setCurrentUserId(const std::string& userId) {
    currentUserId = userId;
    loadUserChats();
}

void ChatApp::loadUserChats() {
    // Clear the current list
    chatList->clear();
    contactDiscussionMap.clear();

    // Get all discussions for the current user
    vector<json> userDiscussions = discussionsManager.getUserDiscussions(currentUserId);

    // Get all users to map IDs to names
    vector<json> users = FakeDb::readFromJsonFile("users");

    // Create a map of user IDs to names for quick lookup
    std::map<std::string, std::string> userIdToName;
    for (const auto& user : users) {
        if (user.contains("id") && user.contains("name")) {
            userIdToName[user["id"]] = user["name"];
        }
    }

    // Add each discussion to the list with the other participant's name
    for (const auto& discussion : userDiscussions) {
        if (discussion.contains("participants") && discussion.contains("id")) {
            for (const auto& participantId : discussion["participants"]) {
                // Skip the current user
                if (participantId != currentUserId) {
                    // Get the name of the other participant
                    std::string contactName = userIdToName[participantId];
                    if (!contactName.empty()) {
                        // Add to the UI list
                        QString qContactName = QString::fromStdString(contactName);
                        chatList->addItem(qContactName);

                        // Store in our map
                        contactDiscussionMap[qContactName] = QString::fromStdString(discussion["id"]);
                    }
                    break;
                }
            }
        }
    }
}

void ChatApp::openNewChatWindow()
{
    NewChatWindow* newChatWindow = new NewChatWindow(this);
    connect(newChatWindow, &NewChatWindow::contactSelected, this, &ChatApp::startNewChat);
    newChatWindow->exec();
}

void ChatApp::startNewChat(const QString& contactName)
{
    // Save the current contact name
    currentContactName = contactName;

    // Check if we already have a discussion with this contact
    if (contactDiscussionMap.contains(contactName)) {
        currentDiscussionId = contactDiscussionMap[contactName].toStdString();
        displayChatHistory(currentDiscussionId);
        return;
    }

    // Create a new discussion
    bool success = discussionsManager.createDiscussion(currentUserId, contactName.toStdString());

    if (success) {
        // Get the new discussion ID
        currentDiscussionId = discussionsManager.getDiscussionId(currentUserId, contactName.toStdString());

        // Update our map and UI
        contactDiscussionMap[contactName] = QString::fromStdString(currentDiscussionId);
        if (chatList->findItems(contactName, Qt::MatchExactly).isEmpty()) {
            chatList->addItem(contactName);
        }

        // Clear chat display
        chatDisplay->clear();
    }
}

void ChatApp::onChatSelected(QListWidgetItem* item)
{
    if (item) {
        currentContactName = item->text();
        currentDiscussionId = contactDiscussionMap[currentContactName].toStdString();
        displayChatHistory(currentDiscussionId);
    }
}

void ChatApp::displayChatHistory(const std::string& discussionId)
{
    chatDisplay->clear();

    // Get messages for this discussion
    vector<json> messages = messagesManager.getDiscussionMessages(discussionId);

    // Get users for name lookup
    vector<json> users = FakeDb::readFromJsonFile("users");
    std::map<std::string, std::string> userIdToName;
    for (const auto& user : users) {
        if (user.contains("id") && user.contains("name")) {
            userIdToName[user["id"]] = user["name"];
        }
    }

    // Create and display each message using polymorphism with the factory pattern
    std::vector<std::unique_ptr<Message>> messageObjects;

    for (const auto& message : messages) {
        if (message.contains("sender_id") && message.contains("content") && message.contains("timestamp")) {
            std::string senderId = message["sender_id"];
            std::string content = message["content"];
            long timestamp = message["timestamp"];

            // Use the factory to create the appropriate message type
            messageObjects.push_back(
                MessageFactory::createMessage(senderId, content, timestamp, currentUserId, userIdToName)
            );
        }
    }

    // Display all messages using polymorphism
    for (const auto& msg : messageObjects) {
        msg->display(chatDisplay);
    }
}

// The sendMessage() method should also be updated to use the MessageFactory:
void ChatApp::sendMessage()
{
    QString messageText = messageInput->text().trimmed();
    if (!messageText.isEmpty() && !currentDiscussionId.empty())
    {
        // Add message to messages.json
        bool success = messagesManager.addMessage(currentDiscussionId, currentUserId, messageText.toStdString());

        if (success) {
            // Create empty map since we're sending a message (don't need the name mapping)
            std::map<std::string, std::string> emptyMap;

            // Create and display the sent message using polymorphism through the factory
            auto sentMsg = MessageFactory::createMessage(
                currentUserId, messageText.toStdString(), time(nullptr), currentUserId, emptyMap
            );
            sentMsg->display(chatDisplay);
            messageInput->clear();
        }
    }
}

ChatApp::~ChatApp() {}