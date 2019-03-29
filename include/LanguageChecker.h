//
// Created by LMF319018 on 09/01/2019.
//

#ifndef CORPUS_LANGUAGECHECKER_H
#define CORPUS_LANGUAGECHECKER_H
#include <string>
using namespace std;

class LanguageChecker {
public:
    virtual bool isValidWord(string word) = 0;
};


#endif //CORPUS_LANGUAGECHECKER_H
