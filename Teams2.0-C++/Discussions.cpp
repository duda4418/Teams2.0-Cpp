#include "Discussions.h"
#include "Authenticate.h"
#include <ctime>

Discussions::Discussions() {}

Discussions::~Discussions() {}

string Discussions::generateDiscussionId() {
    // Reuse the UUID generator from Authenticate class
    Authenticate auth;
    return auth.generateUUID();
}

bool Discussions::createDiscussion(const string& userId, const string& contactName) {
    // Find the contact's user ID
    string contactId;
    vector<json> users = FakeDb::readFromJsonFile("users");

    for (const auto& user : users) {
        if (user.contains("name") && user["name"] == contactName) {
            contactId = user["id"];
            break;
        }
    }

    if (contactId.empty()) {
        return false; // Contact not found
    }

    // Check if discussion already exists
    string existingDiscussionId = getDiscussionId(userId, contactName);
    if (!existingDiscussionId.empty()) {
        return true; // Discussion already exists
    }

    // Create new discussion
    string discussionId = generateDiscussionId();

    json newDiscussion = {
        {"id", discussionId},
        {"participants", {userId, contactId}},
        {"created_at", time(nullptr)},
        {"updated_at", time(nullptr)}
    };

    return FakeDb::writeToJsonFile("discussions", newDiscussion);
}

vector<json> Discussions::getUserDiscussions(const string& userId) {
    vector<json> allDiscussions = FakeDb::readFromJsonFile("discussions");
    vector<json> userDiscussions;

    for (const auto& discussion : allDiscussions) {
        if (discussion.contains("participants")) {
            for (const auto& participant : discussion["participants"]) {
                if (participant == userId) {
                    userDiscussions.push_back(discussion);
                    break;
                }
            }
        }
    }

    return userDiscussions;
}

string Discussions::getDiscussionId(const string& userId, const string& contactName) {
    // Find the contact's user ID
    string contactId;
    vector<json> users = FakeDb::readFromJsonFile("users");

    for (const auto& user : users) {
        if (user.contains("name") && user["name"] == contactName) {
            contactId = user["id"];
            break;
        }
    }

    if (contactId.empty()) {
        return ""; // Contact not found
    }

    // Look for a discussion with both users as participants
    vector<json> discussions = FakeDb::readFromJsonFile("discussions");

    for (const auto& discussion : discussions) {
        if (discussion.contains("participants") && discussion.contains("id")) {
            const auto& participants = discussion["participants"];
            bool hasUser = false;
            bool hasContact = false;

            for (const auto& participant : participants) {
                if (participant == userId) {
                    hasUser = true;
                }
                else if (participant == contactId) {
                    hasContact = true;
                }
            }

            if (hasUser && hasContact) {
                return discussion["id"];
            }
        }
    }

    return ""; // No existing discussion found
}

json Discussions::getDiscussionDetails(const string& discussionId) {
    vector<json> discussions = FakeDb::readFromJsonFile("discussions");

    for (const auto& discussion : discussions) {
        if (discussion.contains("id") && discussion["id"] == discussionId) {
            return discussion;
        }
    }

    return json(nullptr); // Discussion not found
}

bool Discussions::deleteDiscussion(const string& discussionId) {
    // This would require modifying the discussions.json file to remove a specific discussion
    // Since our FakeDb doesn't support this directly, this is a placeholder for future implementation

    return true; // Placeholder
}