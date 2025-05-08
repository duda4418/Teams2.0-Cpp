#ifndef MESSAGE_FACTORY_H
#define MESSAGE_FACTORY_H

#include "Message.h"
#include <memory>
#include <map>
#include <string>

class MessageFactory {
public:
    // Create a message based on sender and current user
    static std::unique_ptr<Message> createMessage(
        const std::string& senderId,
        const std::string& content,
        long timestamp,
        const std::string& currentUserId,
        const std::map<std::string, std::string>& userIdToName) {

        if (senderId == currentUserId) {
            return std::make_unique<SentMessage>(senderId, content, timestamp);
        }
        else {
            std::string senderName = "Unknown";
            auto it = userIdToName.find(senderId);
            if (it != userIdToName.end()) {
                senderName = it->second;
            }
            return std::make_unique<ReceivedMessage>(senderId, content, timestamp, senderName);
        }
    }
};

#endif // MESSAGE_FACTORY_H