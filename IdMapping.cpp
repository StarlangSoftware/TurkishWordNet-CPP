//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include <fstream>
#include <Word.h>
#include <vector>
#include <map>
#include "IdMapping.h"

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

vector<string> IdMapping::keySet() {
    vector<string> keySet;
    for (auto &it : map) {
        keySet.emplace_back(it.first);
    }
}

string IdMapping::mapTo(string id) {
    if (map.find(id) == map.end()){
        return "";
    }
    string mappedId = map.find(id)->second;
    while (map.find(mappedId) != map.end()){
        mappedId = map.find(id)->second;
    }
    return mappedId;
}

string IdMapping::singleMap(string id) {
    return map.find(id)->second;
}

void IdMapping::add(string key, string value) {
    map.emplace(key, value);
}

void IdMapping::remove(string key) {
    map.erase(key);
}

void IdMapping::save(string fileName) {
    ofstream outputFile;
    outputFile.open(fileName, ofstream :: out);
    for (auto &it : map) {
        outputFile << it.first << "->" << it.second;
    }
    outputFile.close();
}
