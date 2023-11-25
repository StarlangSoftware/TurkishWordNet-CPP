//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_ICSIMILARITY_H
#define WORDNET_ICSIMILARITY_H


#include "Similarity.h"

class ICSimilarity : public Similarity{
protected:
    map<string, double> informationContents;
public:
    ICSimilarity(WordNet& wordNet, map<string, double> informationContents) : Similarity(wordNet){
        this->informationContents = std::move(informationContents);
    }
};


#endif //WORDNET_ICSIMILARITY_H
