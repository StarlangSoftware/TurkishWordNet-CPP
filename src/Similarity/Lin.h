//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_LIN_H
#define WORDNET_LIN_H


#include "ICSimilarity.h"

class Lin : public ICSimilarity{
public:
    Lin(WordNet wordNet, map<string, double> informationContents);
    double computeSimilarity(SynSet synSet1, SynSet synSet2) override;
};


#endif //WORDNET_LIN_H
