#ifndef FAKE_DB_H
#define FAKE_DB_H

#include <fstream>
#include <iostream>
#include <string>
#include "json.hpp"
using namespace std;

using json = nlohmann::json;


class FakeDb {
public:
    // Writes JSON data to a file, appending the new data
    static bool writeToJsonFile(const string& filename, const json& newData);

    // Reads JSON data from a file
    static bool readFromJsonFile(const string& filename, json& data);
};

#endif // FAKE_DB_H
