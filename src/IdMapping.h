//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#ifndef WORDNET_IDMAPPING_H
#define WORDNET_IDMAPPING_H

#include <map>
using namespace std;

class IdMapping {
private:
    map<string, string> map;
public:
    IdMapping();
    explicit IdMapping(const string& fileName);
    [[nodiscard]] vector<string> keySet() const;
    [[nodiscard]] string mapTo(const string& id) const;
    [[nodiscard]] string singleMap(const string& id) const;
    void add(const string& key, const string& value);
    void remove(const string& key);
    void save(const string& fileName) const;
};


#endif //WORDNET_IDMAPPING_H
