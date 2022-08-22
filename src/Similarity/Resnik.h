//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_RESNIK_H
#define WORDNET_RESNIK_H


#include "ICSimilarity.h"

class Resnik : public ICSimilarity {
public:
    Resnik(WordNet& wordNet, map<string, double> informationContents);
    double computeSimilarity(SynSet synSet1, SynSet synSet2) override;
};


#endif //WORDNET_RESNIK_H
