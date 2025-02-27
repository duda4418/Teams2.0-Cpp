#include "FakeDB.h"
#include "json.hpp"


bool FakeDb::writeToJsonFile(const string& filename, const json& newData) {
    // Read existing data from the file
    json existingData;
    ifstream inputFile(filename);
    if (inputFile) {
        try {
            inputFile >> existingData;
        }
        catch (json::parse_error& e) {
            cerr << "Error reading existing file: " << e.what() << endl;
            return false;
        }
    }
    inputFile.close();

    // If the existing data doesn't have a "users" key, create it
    if (existingData.find(filename) == existingData.end()) {
        existingData[filename] = json::array();
    }

    // Add the new data (user) to the "users" array
    existingData[filename].push_back(newData);

    // Write the updated data back to the file
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "Error opening file for writing: " << filename << endl;
        return false;
    }
    outputFile << existingData.dump(4); // Pretty print with 4 spaces
    outputFile.close();
    return true;
}

// Reads JSON data from a file
bool FakeDb::readFromJsonFile(const string& filename, json& data) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file for reading: " << filename << endl;
        return false;
    }
    try {
        file >> data;
    }
    catch (json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return false;
    }
    file.close();
    return true;
}



