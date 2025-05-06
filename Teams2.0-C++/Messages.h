#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include <vector>
#include "json.hpp"
#include "FakeDb.h"

using namespace std;
using json = nlohmann::json;

class Messages
{
public:
    Messages();
    ~Messages();

    // Add a new message to a specific discussion
    bool addMessage(const string& discussionId, const string& senderId, const string& content);

    // Get all messages for a specific discussion
    vector<json> getDiscussionMessages(const string& discussionId);

    // Get the last message for a discussion (for previews)
    json getLastMessage(const string& discussionId);

    // Delete messages for a specific discussion
    bool deleteDiscussionMessages(const string& discussionId);

private:
    string generateMessageId();
};

#endif // MESSAGES_H