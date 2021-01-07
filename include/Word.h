//
// Created by Olcay Taner Yıldız on 23.12.2018.
//

#ifndef DICTIONARY_WORD_H
#define DICTIONARY_WORD_H

#include <string>
using namespace std;

class Word {
protected:
    string name;
public:
    Word();
    virtual ~Word() = default;
    explicit Word(string name);
    string to_string();
    int charCount();
    Word clone();
    string getName() const;
    void setName(string name);
    static bool isCapital(string surfaceForm);
    static bool isPunctuation(string surfaceForm);
    static bool isHonorific(string surfaceForm);
    static bool isOrganization(string surfaceForm);
    static bool isMoney(string surfaceForm);
    static bool startsWith(string largeString, string smallString);
    static bool endsWith(string largeString, string smallString);
    static vector<string> split(string line, string separator);
    static vector<string> split(string line);
    static string replaceAll(string str, string from, string to);
    static string trim(string str);
    static int size(string surfaceForm);
    static string toLowerCase(string surfaceForm);
    static string toUpperCase(string surfaceForm);
    static string lastChar(string surfaceForm);
    static string charAt(string surfaceForm, int index);
    static string* allCharacters(string surfaceForm);
    static string substring(string surfaceForm, int index, int length);
    static string substring(string surfaceForm, int index);
    static string substringExceptLastChar(string surfaceForm);
    static string substringExceptLastTwoChars(string surfaceForm);
    bool isPunctuation();
    static bool isTime(string surfaceForm);
    static Word* toWordArray(string* sourceArray, int size);
    vector<Word> toCharacters();
    friend istream& operator>> (istream& is, Word& word){
        is >> word.name;
        return is;
    }
    friend ostream& operator<<(ostream& os, const Word& word){
        os << word.getName();
        return os;
    }
    bool operator==(const Word &anotherWord) const{
        return (name == anotherWord.name);
    }
    bool operator<(const Word &anotherWord) const{
        return (name < anotherWord.name);
    }
};


#endif //DICTIONARY_WORD_H
