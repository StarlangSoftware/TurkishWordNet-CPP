//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H
#define MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H

#include <vector>
#include <string>
#include "MorphologicalTag.h"

using namespace std;

class InflectionalGroup {
public:
    static MorphologicalTag getMorphologicalTag(string tag);
    static string getTag(MorphologicalTag tag);
    explicit InflectionalGroup(string IG);
    MorphologicalTag getTag(int index);
    int size();
    string to_String();
    MorphologicalTag containsCase();
    bool containsPlural();
    bool containsTag(MorphologicalTag tag);
    bool containsPossessive();
    static const int TAG_SIZE = 129;
    static const MorphologicalTag morphoTags[TAG_SIZE];
private:
    vector<MorphologicalTag> IG;
    static const string tags[TAG_SIZE];
};

#endif //MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H
