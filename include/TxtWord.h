//
// Created by Olcay Taner Yıldız on 2.01.2019.
//

#ifndef DICTIONARY_TXTWORD_H
#define DICTIONARY_TXTWORD_H

#include<vector>
#include <string>
#include <unordered_set>
#include "Word.h"

using namespace std;

class TxtWord : public Word {
private:
    unordered_set<string> flags;
public:
    TxtWord(string name);
    TxtWord(string name, string flag);
    void addFlag(string flag);
    TxtWord* clone();
    void removeFlag(string flag);
    string verbType();
    bool containsFlag(string flag);
    bool samePos(TxtWord word);
    bool isNominal();
    bool isPassive();
    bool isAbbreviation();
    bool isInterjection();
    bool isDuplicate();
    bool isHeader();
    bool isAdjective();
    bool isPureAdjective();
    bool isPronoun();
    bool isQuestion();
    bool isVerb();
    bool isPortmanteau();
    bool isDeterminer();
    bool isConjunction();
    bool isAdverb();
    bool isPostP();
    bool isPortmanteauEndingWithSI();
    bool isPortmanteauFacedVowelEllipsis();
    bool isPortmanteauFacedSoftening();
    bool isSuffix();
    bool isProperNoun();
    bool isPlural();
    bool isNumeral();
    bool isReal();
    bool isFraction();
    bool isTime();
    bool isDate();
    bool isPercent();
    bool isRange();
    bool isOrdinal();
    bool notObeysVowelHarmonyDuringAgglutination();
    bool obeysAndNotObeysVowelHarmonyDuringAgglutination();
    bool rootSoftenDuringSuffixation();
    bool rootSoftenAndNotSoftenDuringSuffixation();
    bool verbSoftenDuringSuffixation();
    bool nounSoftenDuringSuffixation();
    bool endingKChangesIntoG();
    bool isExceptional();
    bool duplicatesDuringSuffixation();
    bool duplicatesAndNotDuplicatesDuringSuffixation();
    bool lastIdropsDuringSuffixation();
    bool lastIDropsAndNotDropDuringSuffixation();
    bool takesRelativeSuffixKi();
    bool takesRelativeSuffixKu();
    bool consonantSMayInsertedDuringPossesiveSuffixation();
    bool lastIdropsDuringPassiveSuffixation();
    bool vowelAChangesToIDuringYSuffixation();
    bool vowelEChangesToIDuringYSuffixation();
    bool takesSuffixIRAsAorist();
    bool takesSuffixDIRAsFactitive();
    bool showsSuRegularities();
    string to_string();
};


#endif //DICTIONARY_TXTWORD_H
