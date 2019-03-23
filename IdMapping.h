//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#ifndef WORDNET_IDMAPPING_H
#define WORDNET_IDMAPPING_H

#include <map>
#include <unordered_set>
using namespace std;

class IdMapping {
private:
    map<string, string> map;
public:
    IdMapping();
    explicit IdMapping(string fileName);
    vector<string> keySet();
    string mapTo(string id);
    string singleMap(string id);
    void add(string key, string value);
    void remove(string key);
    void save(string fileName);
};


#endif //WORDNET_IDMAPPING_H
