#include "NewChatWindow.h"
#include "FakeDb.h"
#include "Globals.h"

NewChatWindow::NewChatWindow(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Select a Contact");
    setFixedSize(300, 400);

    contactList = new QListWidget(this);
    selectButton = new QPushButton("Start Chat", this);

    // Load users from users.json
    loadContactsFromDatabase();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(contactList);
    layout->addWidget(selectButton);

    connect(selectButton, &QPushButton::clicked, this, &NewChatWindow::selectContact);
}

void NewChatWindow::loadContactsFromDatabase()
{
    // Get users from database
    std::vector<json> users = FakeDb::readFromJsonFile("users");

    // Clear existing contacts
    contactList->clear();

    // Add each user except the current user to the list
    for (const auto& user : users) {
        if (user.contains("name") && user["name"] != USERNAME) {
            contactList->addItem(QString::fromStdString(user["name"]));
        }
    }
}

void NewChatWindow::selectContact()
{
    QListWidgetItem* selectedItem = contactList->currentItem();
    if (selectedItem)
    {
        emit contactSelected(selectedItem->text());
        accept();
    }
}