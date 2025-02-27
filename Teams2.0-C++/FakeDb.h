#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include "json.hpp" // Include the JSON library

using namespace std;
using json = nlohmann::json;

class FakeDB {
private:
    unordered_map<string, string> users; // Key: UserID, Value: UserData

public:
    // Constructor - Loads data from file
    FakeDB() {
        loadFromFile("users.json");
    }

    // Load user data from a JSON file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        json jsonData;
        file >> jsonData; // Read JSON data from file
        file.close();

        // Convert JSON data to unordered_map
        for (auto& [key, value] : jsonData.items()) {
            users[key] = value;
        }
    }

    // Save user data to file
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        json jsonData(users);
        file << jsonData.dump(4); // Pretty print JSON with indentation
        file.close();
    }

    // Add a user to the database
    void addUser(const string& userID, const string& userData) {
        users[userID] = userData;
        saveToFile("users.json"); // Save changes to file
    }

    // Get user data
    string getUser(const string& userID) const {
        auto it = users.find(userID);
        return (it != users.end()) ? it->second : "User not found";
    }

    // Check if a user exists
    bool userExists(const string& userID) const {
        return users.find(userID) != users.end();
    }

    // Print all users (for debugging)
    void printUsers() const {
        for (const auto& pair : users) {
            cout << "UserID: " << pair.first << ", Data: " << pair.second << endl;
        }
    }
};
