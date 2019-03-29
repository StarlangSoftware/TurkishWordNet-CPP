//
// Created by Olcay Taner Yıldız on 4.01.2019.
//

#ifndef DICTIONARY_TXTDICTIONARY_H
#define DICTIONARY_TXTDICTIONARY_H
#include "Dictionary.h"
#include "Trie.h"
#include "TxtWord.h"

class TxtDictionary : public Dictionary {
private:
    void loadFromText(string filename);
    void addWordWhenRootSoften(Trie* trie, string last, string root, TxtWord* word);
public:
    explicit TxtDictionary(string filename = "turkish_dictionary.txt", Comparator comparator = Comparator::TURKISH);
    TxtDictionary clone();
    bool addWithFlag(string name, string flag);
    void addNumber(string name);
    void addRealNumber(string name);
    void addFraction(string name);
    void addTime(string name);
    bool addProperNoun(string name);
    bool addNoun(string name);
    bool addVerb(string name);
    bool addAdjective(string name);
    bool addAdverb(string name);
    bool addPronoun(string name);
    void mergeDictionary(string secondFilename, string mergedFilename);
    void saveAsTxt(string filename);
    Trie* prepareTrie();
};


#endif //DICTIONARY_TXTDICTIONARY_H
