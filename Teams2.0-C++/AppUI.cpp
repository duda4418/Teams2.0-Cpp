#include "AppUI.h"

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
    connect(newChatButton, &QPushButton::clicked, this, &ChatApp::startNewChat);
}

void ChatApp::sendMessage()
{
    QString message = messageInput->text().trimmed();
    if (!message.isEmpty())
    {
        chatDisplay->append("You: " + message);
        messageInput->clear();
    }
}

void ChatApp::startNewChat()
{
    chatDisplay->clear();
    chatList->addItem("New Chat");
}

ChatApp::~ChatApp() {}
