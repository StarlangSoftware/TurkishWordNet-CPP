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
    explicit IdMapping(const string& fileName);
    vector<string> keySet() const;
    string mapTo(const string& id) const;
    string singleMap(const string& id) const;
    void add(const string& key, const string& value);
    void remove(const string& key);
    void save(const string& fileName);
};


#endif //WORDNET_IDMAPPING_H
