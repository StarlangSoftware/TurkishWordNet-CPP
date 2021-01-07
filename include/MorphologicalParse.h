//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_MORPHOLOGICALPARSE_H
#define MORPHOLOGICALANALYSIS_MORPHOLOGICALPARSE_H

#include <vector>
#include <Word.h>
#include "InflectionalGroup.h"

using namespace std;

class MorphologicalParse {
protected:
    vector<InflectionalGroup> inflectionalGroups;
    Word* root;
public:
    MorphologicalParse();
    Word* getWord();
    explicit MorphologicalParse(string parse);
    explicit MorphologicalParse(vector<string> inflectionalGroups);
    string getTransitionList();
    string getInflectionalGroupString(int index);
    InflectionalGroup getInflectionalGroup(int index);
    InflectionalGroup getLastInflectionalGroup();
    string getTag(int index);
    int tagSize();
    int size();
    InflectionalGroup firstInflectionalGroup();
    InflectionalGroup lastInflectionalGroup();
    Word* getWordWithPos();
    string getPos();
    string getRootPos();
    string lastIGContainsCase();
    bool lastIGContainsTag(MorphologicalTag tag);
    bool lastIGContainsPossessive();
    bool isCapitalWord();
    bool isNoun();
    bool isVerb();
    bool isRootVerb();
    bool isAdjective();
    bool isProperNoun();
    bool isPunctuation();
    bool isCardinal();
    bool isOrdinal();
    bool isReal();
    bool isNumber();
    bool isTime();
    bool isDate();
    bool isHashTag();
    bool isEmail();
    bool isPercent();
    bool isFraction();
    bool isRange();
    bool isPlural();
    bool isAuxiliary();
    bool containsTag(MorphologicalTag tag);
    string getTreePos();
    vector<string> getUniversalDependencyFeatures();
    string getUniversalDependencyPos();
    string to_string();
private:
    string getPronType();
    string getNumType();
    string getReflex();
    string getNumber();
    string getCase();
    string getDefinite();
    string getDegree();
    string getPolarity();
    string getPerson();
    string getVoice();
    string getAspect();
    string getTense();
    string getMood();
    string getVerbForm();
};


#endif //MORPHOLOGICALANALYSIS_MORPHOLOGICALPARSE_H
