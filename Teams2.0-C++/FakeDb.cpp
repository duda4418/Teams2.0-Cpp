#include "FakeDB.h"
#include "json.hpp"


bool FakeDb::writeToJsonFile(const string& filename, const json& newData) {
    // Read existing data from the file
    string filenameJSON = filename + ".json";
    json existingData;
    ifstream inputFile(filenameJSON);
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
    ofstream outputFile(filenameJSON);
    if (!outputFile) {
        cerr << "Error opening file for writing: " << filenameJSON << endl;
        return false;
    }
    outputFile << existingData.dump(4); // Pretty print with 4 spaces
    outputFile.close();
    return true;
}

// Reads JSON data from a file
bool FakeDb::readFromJsonFile(const string& filename, json& data) {
    string filenameJSON = filename + ".json";
    ifstream file(filenameJSON);
    if (!file) {
        cerr << "Error opening file for reading: " << filenameJSON << endl;
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



