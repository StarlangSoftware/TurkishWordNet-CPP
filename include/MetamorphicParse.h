//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_METAMORPHICPARSE_H
#define MORPHOLOGICALANALYSIS_METAMORPHICPARSE_H

#include <string>
#include <vector>
#include "MorphologicalTag.h"
#include "Word.h"
#include "MorphologicalParse.h"

using namespace std;

class MetamorphicParse {
private:
    vector<string> metaMorphemeList;
    Word root;
public:
    static const int META_MORPHEME_SIZE = 109;
    static const string metaMorphemes[META_MORPHEME_SIZE];
    static const MorphologicalTag morphotacticTags[META_MORPHEME_SIZE];
    MetamorphicParse();
    static vector<MorphologicalTag> getMetaMorphemeTag(string tag);
    static vector<MorphologicalTag> getMetaMorphemeTag(MorphologicalParse parse, string tag);
    Word getWord();
    explicit MetamorphicParse(string parse);
    int size();
    void addMetaMorphemeList(string newTacticSet);
    void removeMetaMorphemeFromIndex(int index);
    string getMetaMorpheme(int index);
    string to_string();
};

#endif //MORPHOLOGICALANALYSIS_METAMORPHICPARSE_H
