#include "AppUI.h"
#include "Authenticate.h"
#include <QApplication>
#include <fstream>
#include <iostream>

// Function to initialize JSON files if they don't exist
void initializeJsonFiles() {
    // Check if discussions.json exists, if not create it
    std::ifstream discussionsFile("discussions.json");
    if (!discussionsFile.good()) {
        std::ofstream createDiscussionsFile("discussions.json");
        createDiscussionsFile << "{\"discussions\": []}" << std::endl;
        createDiscussionsFile.close();
        std::cout << "Created discussions.json" << std::endl;
    }
    discussionsFile.close();

    // Check if messages.json exists, if not create it
    std::ifstream messagesFile("messages.json");
    if (!messagesFile.good()) {
        std::ofstream createMessagesFile("messages.json");
        createMessagesFile << "{\"messages\": []}" << std::endl;
        createMessagesFile.close();
        std::cout << "Created messages.json" << std::endl;
    }
    messagesFile.close();
}

int main(int argc, char* argv[])
{
    // Initialize JSON files if needed
    initializeJsonFiles();

    QApplication a(argc, argv);

    // Get current user ID
    Authenticate client;
    string userID = client.get_userID();

    // Initialize ChatApp with the user ID
    ChatApp w;
    w.setCurrentUserId(userID);
    w.show();

    return a.exec();
}