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


vector<json> FakeDb::readFromJsonFile(const string& filename) {
    std::string filenameJSON = filename + ".json";
    std::ifstream file(filenameJSON);
    std::vector<json> objs;

    if (!file) {
        cerr << "Error opening file for reading: " << filenameJSON << endl;
        return objs;
    }

    json data;
    try {
        file >> data;
    }
    catch (json::parse_error& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
        return objs;
    }
    file.close();

    if (data[filename].is_array()) {
        for (const auto& obj : data[filename]) {
            objs.push_back(obj);
        }
    }

    return objs;
}
// Reads JSON data from a file
/*bool FakeDb::readFromJsonFile(const string& filename, json& data, vector<string>& ids) {
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

    if (filename == "users")
    {
        if (data.find(filename) != data.end()) {
            for (const auto& user : data[filename]) {
                if (user.contains("name")) {
                    ids.push_back(user["name"]);
                }
            }
        }
    }
    return true;
}*/



