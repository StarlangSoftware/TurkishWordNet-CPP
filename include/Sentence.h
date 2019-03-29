//
// Created by LMF319018 on 09/01/2019.
//

#ifndef CORPUS_SENTENCE_H
#define CORPUS_SENTENCE_H
#include <vector>
#include <Word.h>
#include "LanguageChecker.h"

using namespace std;

class Sentence {
protected:
    vector<Word*> words;
public:
    Sentence();
    ~Sentence();
    Sentence clone();
    Sentence(ifstream file);
    Sentence(string sentence);
    Sentence(string sentence, LanguageChecker* languageChecker);
    Word* getWord(int index);
    vector<Word*> getWords();
    vector<Word> getWordList();
    vector<string> getStrings();
    int getIndex(Word* word);
    unsigned long wordCount();
    void addWord(Word* word);
    int charCount();
    void replaceWord(int i, Word* newWord);
    bool safeIndex(int index);
    string to_string();
    string toWords();
    void writeToFile(ofstream file);

    /**
     * The == method takes a Sentence as an input. First compares the sizes of both {@link vector} words and words
     * of the Sentence input. If they are not equal then it returns false. Than it compares each word in the {@link vector}.
     * If they are equal, it returns true.
     *
     * @param s Sentence to compare.
     * @return true if words of two sentences are equal.
     */
    bool operator==(const Sentence &anotherSentence) const{
        if (words.size() != anotherSentence.words.size())
            return false;
        for (unsigned long i = 0; i < words.size(); i++){
            if (words.at(i)->getName() != anotherSentence.words.at(i)->getName()){
                return false;
            }
        }
        return true;
    }
};


#endif //CORPUS_SENTENCE_H
