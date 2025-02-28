#include "AppUI.h"
#include "Authenticate.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Authenticate client;
    string userID = client.get_userID();
    ChatApp w;  
    w.show();  
    return a.exec();
}
