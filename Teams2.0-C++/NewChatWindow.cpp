#include "NewChatWindow.h"

NewChatWindow::NewChatWindow(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Select a Contact");
    setFixedSize(300, 400);

    contactList = new QListWidget(this);
    selectButton = new QPushButton("Start Chat", this);

    QStringList contacts = { "Alice", "Bob", "Charlie", "David", "Emma" };
    contactList->addItems(contacts);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(contactList);
    layout->addWidget(selectButton);

    connect(selectButton, &QPushButton::clicked, this, &NewChatWindow::selectContact);
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
