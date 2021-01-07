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
    map<string, string> misspelledWords;
    void loadFromText(string filename);
    void loadMisspelledWords(const string& filename);
    void addWordWhenRootSoften(Trie* trie, string last, string root, TxtWord* word);
public:
    explicit TxtDictionary(string filename, Comparator comparator);
    explicit TxtDictionary(string filename = "turkish_dictionary.txt", Comparator comparator = Comparator::TURKISH, string misspelledFileName = "turkish_misspellings.txt");
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
    string getCorrectForm(const string& misspelledWord);
    Trie* prepareTrie();
};


#endif //DICTIONARY_TXTDICTIONARY_H
