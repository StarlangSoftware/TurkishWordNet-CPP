//
// Created by Olcay Taner Yıldız on 2.01.2019.
//

#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

#include<vector>
#include<map>
#include <locale>
#include "Word.h"
#include <iostream>

using namespace std;

enum class Comparator{
    ENGLISH, TURKISH, TURKISH_NO_CASE
};

class Dictionary {
private:
    map<string, int> comparatorMap;
protected:
    vector<Word*> words;
    string filename;
    Comparator comparator = Comparator::ENGLISH;
    void sort();
public:
    static const map<string, int> turkishComparatorMap;
    static const map<string, int> turkishIgnoreCaseComparatorMap;
    Dictionary();
    explicit Dictionary(Comparator comparator);
    Word* getWord(string name);
    void removeWord(string name);
    int getWordIndex(string name);
    bool wordExists(string name);
    unsigned long size();
    Word* getWord(unsigned long index);
    unsigned long longestWordSize();
    unsigned long getWordStartingWith(string hash);
};

const inline map<string, int> Dictionary::turkishComparatorMap =
{{"a", 0}, {"â", 1}, {"á", 2}, {"å", 3}, {"ã", 4}, {"ä", 5},
{"b", 6}, {"c", 7}, {"ç", 8}, {"d", 9}, {"e", 10}, {"é", 11},
{"æ", 12}, {"f", 13}, {"g", 14}, {"ğ", 15}, {"h", 16}, {"ı", 17},
{"í", 18}, {"i", 19}, {"î", 20}, {"ï", 21}, {"j", 22}, {"k", 23},
{"l", 24}, {"m", 25}, {"n", 26}, {"o", 27}, {"ó", 28}, {"ö", 29},
{"p", 30}, {"q", 31}, {"r", 32}, {"s", 33}, {"ş", 34}, {"t", 35},
{"u", 36}, {"ú", 37}, {"ü", 38}, {"û", 39}, {"v", 40}, {"w", 41},
{"x", 42}, {"y", 43}, {"z", 44}, {"A", 45}, {"B", 46}, {"C", 47},
{"Ç", 48}, {"D", 49}, {"E", 50}, {"F", 51}, {"G", 52}, {"Ğ", 53},
{"H", 54}, {"I", 55}, {"İ", 56}, {"J", 57}, {"K", 58}, {"L", 59},
{"M", 60}, {"N", 61}, {"O", 62}, {"Ö", 63}, {"P", 64}, {"Q", 65},
{"R", 66}, {"S", 67}, {"Ş", 68}, {"T", 69}, {"U", 70}, {"Ü", 71},
{"V", 72}, {"W", 73}, {"X", 74}, {"Y", 75}, {"Z", 76}, {"-", 77},
{"&", 78}, {"'", 79}, {"’", 80}, {".", 81}, {"(", 82}, {")", 83},
{"0", 84}, {"1", 85}, {"2", 86}, {"3", 87}, {"4", 88}, {"5", 89},
{"6", 90}, {"7", 91}, {"8", 92}, {"9", 93}, {"<", 94}, {">", 95},
{"/", 96}, {":", 97}, {";", 98}, {"$", 99}, {" ", 100}};

const inline map<string, int> Dictionary::turkishIgnoreCaseComparatorMap =
        {{"a", 0}, {"â", 1}, {"á", 2}, {"å", 3}, {"ã", 4}, {"ä", 5},
         {"A", 6}, {"Â", 7}, {"b", 8}, {"B", 9}, {"c", 10}, {"C", 11},
         {"ç", 12}, {"Ç", 13}, {"d", 14}, {"D", 15}, {"e", 16}, {"é", 17},
         {"æ", 18}, {"E", 19}, {"f", 20}, {"F", 21}, {"g", 22}, {"G", 23},
         {"ğ", 24}, {"Ğ", 25}, {"h", 26}, {"H", 27}, {"ı", 28}, {"í", 29},
         {"I", 30}, {"i", 31}, {"î", 32}, {"ï", 33}, {"İ", 34}, {"Î", 35},
         {"j", 36}, {"J", 37}, {"k", 38}, {"K", 39}, {"l", 40}, {"L", 41},
         {"m", 42}, {"M", 43}, {"n", 44}, {"N", 45}, {"o", 46}, {"O", 47},
         {"ó", 48}, {"ö", 49}, {"Ö", 50}, {"p", 51}, {"P", 52}, {"q", 53},
         {"Q", 54}, {"r", 55}, {"R", 56}, {"s", 57}, {"S", 58}, {"ş", 59},
         {"Ş", 60}, {"t", 61}, {"T", 62}, {"u", 63}, {"ú", 64}, {"U", 65},
         {"ü", 66}, {"û", 67}, {"Ü", 68}, {"Û", 69}, {"v", 70}, {"V", 71},
         {"w", 72}, {"W", 73}, {"x", 74}, {"X", 75}, {"y", 76}, {"Y", 77},
         {"z", 78}, {"Z", 79}, {"-", 80}, {"&", 81}, {"'", 82}, {"’", 83},
         {".", 84}, {"(", 85}, {")", 86}, {"0", 87}, {"1", 88}, {"2", 89},
         {"3", 90}, {"4", 91}, {"5", 92}, {"6", 93}, {"7", 94}, {"8", 95},
         {"9", 96}, {"<", 97}, {">", 98}, {"/", 99}, {":", 100}, {";", 101},
         {"$", 102}, {" ", 103}};

struct turkishWordComparator{
    map<string, int> comparatorMap;
/**
 * The wordComparator takes two {@link Word}s as inputs; wordA and wordB and compares their names. Returns the result of this comparison.
 *
 * @param wordA Word type input.
 * @param wordB Word type input.
 * @return the value {@code 0} if the wordA is equal to the wordB; a value less than {@code 0} if this wordA is
 * lexicographically less than wordB; and a value greater than {@code 0} if this wordA is lexicographically greater
 * than wordB.
 */
    turkishWordComparator(map<string, int> comparatorMap){
        this->comparatorMap = comparatorMap;
    }

    bool operator() (Word* wordA, Word* wordB){
        string nameA = wordA->getName();
        const char* charPtr1 = nameA.c_str();
        string nameB = wordB->getName();
        const char* charPtr2 = nameB.c_str();
        if (wordA->getName() == wordB->getName()){
            return false;
        }
        if (wordB->getName().starts_with(wordA->getName())){
            return true;
        }
        if (wordA->getName().starts_with(wordB->getName())){
            return false;
        }
        while (*charPtr1 && *charPtr2){
            string char1;
            if ((*charPtr1 & 0xC0) != 0x80){
                do{
                    char1 += *charPtr1;
                    charPtr1++;
                } while ((*charPtr1 & 0xC0) == 0x80);
            }
            string char2;
            if ((*charPtr2 & 0xC0) != 0x80){
                do{
                    char2 += *charPtr2;
                    charPtr2++;
                } while ((*charPtr2 & 0xC0) == 0x80);
            }
            if (comparatorMap.contains(char1) && comparatorMap.contains(char2)){
                int index1 = comparatorMap.at(char1), index2 = comparatorMap.at(char2);
                if (index1 < index2){
                    return true;
                } else {
                    if (index1 > index2){
                        return false;
                    }
                }
            } else {
                cout << char1 << char2 << endl;
                return true;
            }
        }
        return true;
    }
};

#endif //DICTIONARY_DICTIONARY_H
