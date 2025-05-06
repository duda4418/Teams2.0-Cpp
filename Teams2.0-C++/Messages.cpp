#include "Messages.h"
#include "Authenticate.h"
#include <ctime>
#include <algorithm>

Messages::Messages() {}

Messages::~Messages() {}

string Messages::generateMessageId() {
    // Reuse the UUID generator from Authenticate class
    Authenticate auth;
    return auth.generateUUID();
}

bool Messages::addMessage(const string& discussionId, const string& senderId, const string& content) {
    // Create a new message object
    json newMessage = {
        {"id", generateMessageId()},
        {"discussion_id", discussionId},
        {"sender_id", senderId},
        {"content", content},
        {"timestamp", time(nullptr)},
        {"read", false}
    };

    // Add the message to messages.json
    return FakeDb::writeToJsonFile("messages", newMessage);
}

vector<json> Messages::getDiscussionMessages(const string& discussionId) {
    vector<json> allMessages = FakeDb::readFromJsonFile("messages");
    vector<json> discussionMessages;

    // Filter messages for the specified discussion
    for (const auto& message : allMessages) {
        if (message.contains("discussion_id") && message["discussion_id"] == discussionId) {
            discussionMessages.push_back(message);
        }
    }

    // Sort messages by timestamp (oldest first)
    sort(discussionMessages.begin(), discussionMessages.end(),
        [](const json& a, const json& b) {
            return a["timestamp"] < b["timestamp"];
        });

    return discussionMessages;
}

json Messages::getLastMessage(const string& discussionId) {
    vector<json> discussionMessages = getDiscussionMessages(discussionId);

    if (discussionMessages.empty()) {
        return json(nullptr);
    }

    // Return the most recent message (last in the sorted array)
    return discussionMessages.back();
}

bool Messages::deleteDiscussionMessages(const string& discussionId) {
    // This would require modifying the messages.json file to remove specific messages
    // Since our FakeDb doesn't support this directly, this is a placeholder for future implementation
    // In a real application, you would remove all messages with the given discussionId

    return true; // Placeholder
}