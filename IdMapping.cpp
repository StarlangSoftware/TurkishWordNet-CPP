//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include <fstream>
#include <Word.h>
#include <vector>
#include <map>
#include "IdMapping.h"

/**
 * Constructor to load ID mappings from specific file "mapping.txt" to a {@link HashMap}.
 */
IdMapping::IdMapping() {
    ifstream inputFile;
    string s;
    inputFile.open("mapping.txt", ifstream :: in);
    while (inputFile.good()) {
        getline(inputFile, s);
        vector<string> tokens = Word::split(s, "->");
        if (!tokens.empty()) {
            map.emplace(tokens.at(0), tokens.at(1));
        }
    }
    inputFile.close();
}

/**
 * Constructor to load ID mappings from given file to a {@link HashMap}.
 *
 * @param fileName String file name input that will be read
 */
IdMapping::IdMapping(string fileName) {
    ifstream inputFile;
    string s;
    inputFile.open(fileName, ifstream :: in);
    while (inputFile.good()) {
        getline(inputFile, s);
        vector<string> tokens = Word::split(s, "->");
        if (!tokens.empty()) {
            map.emplace(tokens.at(0), tokens.at(1));
        }
    }
    inputFile.close();
}

/**
 * Returns a {@link Set} view of the keys contained in this map.
 *
 * @return a set view of the keys contained in this map
 */
vector<string> IdMapping::keySet() {
    vector<string> keySet;
    for (auto &it : map) {
        keySet.emplace_back(it.first);
    }
}

/**
 * Returns the value to which the specified key is mapped,
 * or {@code null} if this map contains no mapping for the key.
 *
 * @param id String id of a key
 * @return value of the specified key
 */
string IdMapping::mapTo(string id) {
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
string IdMapping::singleMap(string id) {
    return map.find(id)->second;
}

/**
 * Associates the specified value with the specified key in this map.
 *
 * @param key   key with which the specified value is to be associated
 * @param value value to be associated with the specified key
 */
void IdMapping::add(string key, string value) {
    map.emplace(key, value);
}

/**
 * Removes the mapping for the specified key from this map if present.
 *
 * @param key key whose mapping is to be removed from the map
 */
void IdMapping::remove(string key) {
    map.erase(key);
}

/**
 * Saves map to the specified file.
 *
 * @param fileName String file to write map
 */
void IdMapping::save(string fileName) {
    ofstream outputFile;
    outputFile.open(fileName, ofstream :: out);
    for (auto &it : map) {
        outputFile << it.first << "->" << it.second;
    }
    outputFile.close();
}
