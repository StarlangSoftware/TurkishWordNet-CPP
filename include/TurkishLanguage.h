//
// Created by Olcay Taner Yıldız on 23.12.2018.
//

#ifndef DICTIONARY_TURKISHLANGUAGE_H
#define DICTIONARY_TURKISHLANGUAGE_H

#include "Language.h"

class TurkishLanguage : public Language {
private:
    static const string VOWELS;
    static const string BACK_VOWELS;
    static const string FRONT_VOWELS;
    static const string BACK_ROUNDED_VOWELS;
    static const string BACK_UNROUNDED_VOWELS;
    static const string FRONT_ROUNDED_VOWELS;
    static const string FRONT_UNROUNDED_VOWELS;
    static const string CONSONANT_DROPS;
    static const string CONSONANTS;
    static const string SERT_SESSIZ;
public:
    static bool isVowel(const string &s);
    static bool isBackVowel(const string &s);
    static bool isFrontVowel(const string &s);
    static bool isBackRoundedVowel(const string &s);
    static bool isFrontRoundedVowel(const string &s);
    static bool isBackUnroundedVowel(const string &s);
    static bool isFrontUnroundedVowel(const string &s);
    static bool isConsonantDrop(const string &s);
    static bool isConsonant(const string &s);
    static bool isSertSessiz(const string &s);
    static bool isUppercase(const string &s);
    static const string LOWERCASE_LETTERS;
    static const string UPPERCASE_LETTERS;
    static const string LETTERS;
};

const inline string TurkishLanguage::VOWELS = "aeıioöuüâî";
const inline string TurkishLanguage::BACK_VOWELS = "aıouâ";
const inline string TurkishLanguage::FRONT_VOWELS = "eiöüî";
const inline string TurkishLanguage::BACK_ROUNDED_VOWELS = "ou";
const inline string TurkishLanguage::BACK_UNROUNDED_VOWELS = "aıâ";
const inline string TurkishLanguage::FRONT_ROUNDED_VOWELS = "öü";
const inline string TurkishLanguage::FRONT_UNROUNDED_VOWELS = "eiî";
const inline string TurkishLanguage::CONSONANT_DROPS = "nsy";
const inline string TurkishLanguage::CONSONANTS = "bcçdfgğhjklmnprsştvyzxqw";
const inline string TurkishLanguage::SERT_SESSIZ = "çfhkpsşt";
const inline string TurkishLanguage::LOWERCASE_LETTERS = "abcçdefgğhıijklmnoöprsştuüvyz";
const inline string TurkishLanguage::UPPERCASE_LETTERS = "ABCÇDEFGĞHIİJKLMNOÖPRSŞTUÜVYZ";
const inline string TurkishLanguage::LETTERS = "abcçdefgğhıijklmnoöprsştuüvyzABCÇDEFGĞHIİJKLMNOÖPRSŞTUÜVYZ";

/**
 * The isVowel method takes a character as an input and returns true if given character is a vowel.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a vowel.
 */
inline bool TurkishLanguage::isVowel(const string &s) {
    return (VOWELS.find(s) != -1);
}

/**
 * The isBackVowel method takes a character as an input and returns true if given character is a back vowel.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a back vowel.
 */
inline bool TurkishLanguage::isBackVowel(const string &s){
    return (BACK_VOWELS.find(s) != -1);
}

/**
 * The isFrontVowel method takes a character as an input and returns true if given character is a front vowel.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a front vowel.
 */
inline bool TurkishLanguage::isFrontVowel(const string &s) {
    return (FRONT_VOWELS.find(s) != -1);
}

/**
 * The isBackRoundedVowel method takes a character as an input and returns true if given character is a back rounded vowel.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a back rounded vowel.
 */
inline bool TurkishLanguage::isBackRoundedVowel(const string &s) {
    return (BACK_ROUNDED_VOWELS.find(s) != -1);
}

/**
 * The isFrontRoundedVowel method takes a character as an input and returns true if given character is a front rounded vowel.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a front rounded vowel.
 */
inline bool TurkishLanguage::isFrontRoundedVowel(const string &s) {
    return (FRONT_ROUNDED_VOWELS.find(s) != -1);
}

/**
 * The isBackUnroundedVowel method takes a character as an input and returns true if given character is a back unrounded vowel.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a back unrounded vowel.
 */
inline bool TurkishLanguage::isBackUnroundedVowel(const string &s) {
    return (BACK_UNROUNDED_VOWELS.find(s) != -1);
}

/**
 * The isFrontUnroundedVowel method takes a character as an input and returns true if given character is a front unrounded vowel.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a front unrounded vowel.
 */
inline bool TurkishLanguage::isFrontUnroundedVowel(const string &s) {
    return (FRONT_UNROUNDED_VOWELS.find(s) != -1);
}

/**
 * The isConsonantDrop method takes a character as an input and returns true if given character is a dropping consonant.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a dropping consonant.
 */
inline bool TurkishLanguage::isConsonantDrop(const string &s) {
    return (CONSONANT_DROPS.find(s) != -1);
}

/**
 * The isConsonant method takes a character as an input and returns true if given character is a consonant.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a consonant.
 */
inline bool TurkishLanguage::isConsonant(const string &s) {
    return (CONSONANTS.find(s) != -1);
}

/**
 * The isUppercase method takes a character as an input and returns true if given character is uppercase.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is uppercase.
 */
inline bool TurkishLanguage::isUppercase(const string &s) {
    return (UPPERCASE_LETTERS.find(s) != -1);
}

/**
 * The isSertSessiz method takes a character as an input and returns true if given character is a sert sessiz.
 *
 * @param ch {@link char} input to check.
 * @return true if given character is a sert sessiz.
 */
inline bool TurkishLanguage::isSertSessiz(const string &s) {
    return (SERT_SESSIZ.find(s) != -1);
}


#endif //DICTIONARY_TURKISHLANGUAGE_H
