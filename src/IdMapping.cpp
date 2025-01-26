//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include <fstream>
#include "Dictionary/Word.h"
#include <vector>
#include "IdMapping.h"

#include <StringUtils.h>

/**
 * Constructor to load ID mappings from specific file "mapping.txt" to a HashMap.
 */
IdMapping::IdMapping() {
    ifstream inputFile;
    string s;
    inputFile.open("mapping.txt", ifstream :: in);
    while (inputFile.good()) {
        getline(inputFile, s);
        vector<string> tokens = StringUtils::split(s, "->");
        if (!tokens.empty()) {
            map.emplace(tokens.at(0), tokens.at(1));
        }
    }
    inputFile.close();
}

/**
 * Constructor to load ID mappings from given file to a HashMap.
 *
 * @param fileName String file name input that will be read
 */
IdMapping::IdMapping(const string& fileName) {
    ifstream inputFile;
    string s;
    inputFile.open(fileName, ifstream :: in);
    while (inputFile.good()) {
        getline(inputFile, s);
        vector<string> tokens = StringUtils::split(s, "->");
        if (!tokens.empty()) {
            map.emplace(tokens.at(0), tokens.at(1));
        }
    }
    inputFile.close();
}

/**
 * Returns a Set view of the keys contained in this map.
 *
 * @return a set view of the keys contained in this map
 */
vector<string> IdMapping::keySet() const{
    vector<string> keySet;
    keySet.reserve(map.size());
    for (auto &it : map) {
        keySet.emplace_back(it.first);
    }
    return keySet;
}

/**
 * Returns the value to which the specified key is mapped,
 * or {@code null} if this map contains no mapping for the key.
 *
 * @param id String id of a key
 * @return value of the specified key
 */
string IdMapping::mapTo(const string& id) const{
    if (!map.contains(id)){
        return "";
    }
    string mappedId = map.find(id)->second;
    while (map.contains(mappedId)){
        mappedId = map.find(id)->second;
    }
    return mappedId;
}

/**
 * Returns the value to which the specified key is mapped.
 *
 * @param id String id of a key
 * @return value of the specified key
 */
string IdMapping::singleMap(const string& id) const{
    return map.find(id)->second;
}

/**
 * Associates the specified value with the specified key in this map.
 *
 * @param key   key with which the specified value is to be associated
 * @param value value to be associated with the specified key
 */
void IdMapping::add(const string& key, const string& value) {
    map.emplace(key, value);
}

/**
 * Removes the mapping for the specified key from this map if present.
 *
 * @param key key whose mapping is to be removed from the map
 */
void IdMapping::remove(const string& key) {
    map.erase(key);
}

/**
 * Saves map to the specified file.
 *
 * @param fileName String file to write map
 */
void IdMapping::save(const string& fileName) const {
    ofstream outputFile;
    outputFile.open(fileName, ofstream :: out);
    for (auto &it : map) {
        outputFile << it.first << "->" << it.second;
    }
    outputFile.close();
}
