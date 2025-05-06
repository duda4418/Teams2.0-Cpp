#ifndef DISCUSSIONS_H
#define DISCUSSIONS_H

#include <string>
#include <vector>
#include "json.hpp"
#include "FakeDb.h"

using namespace std;
using json = nlohmann::json;

class Discussions
{
public:
    Discussions();
    ~Discussions();

    // Create a new discussion between two users
    bool createDiscussion(const string& userId, const string& contactName);

    // Get all discussions for a user
    vector<json> getUserDiscussions(const string& userId);

    // Get discussion ID between two users (if exists)
    string getDiscussionId(const string& userId, const string& contactName);

    // Get detailed information about a specific discussion
    json getDiscussionDetails(const string& discussionId);

    // Delete a discussion
    bool deleteDiscussion(const string& discussionId);

private:
    string generateDiscussionId();
};

#endif // DISCUSSIONS_H