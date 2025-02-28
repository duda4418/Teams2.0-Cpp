#include "Authenticate.h"
#include "FakeDb.h"
#include "Globals.h"
#include <random>
#include <sstream>
#include <iomanip>

using namespace std;

Authenticate::Authenticate() {};

Authenticate::~Authenticate() {};

string Authenticate::generateUUID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);

    stringstream ss;
    ss << hex << setfill('0') << setw(8) << dis(gen) << "-"
        << setw(4) << (dis(gen) & 0xFFFF) << "-"
        << setw(4) << ((dis(gen) & 0x0FFF) | 0x4000) << "-"  // Version 4 UUID
        << setw(4) << ((dis(gen) & 0x3FFF) | 0x8000) << "-"  // Variant 1
        << setw(12) << dis(gen);

    return ss.str();
}

string Authenticate::get_userID() {

    vector<json> data = FakeDb::readFromJsonFile("users");
    if (data.empty()) {
        return "Error reading from file or no users found";
    }


    // Check if the USERNAME exists in the "users" list
    for (const auto& user : data) {
        if (user["name"] == USERNAME) {
            // Return the user ID if found
            return user["id"];
        }
    }


    // If USERNAME doesn't exist, add it
    json newUser = {
        {"name", USERNAME},
        {"password", PASSWORD},
        {"id", generateUUID()} // Generate or assign an ID as needed
    };

    // Write the new user to the file
    bool success = FakeDb::writeToJsonFile("users", newUser);
    if (!success) {
        return "Error writing to file";
    }

    return "new user created";
}