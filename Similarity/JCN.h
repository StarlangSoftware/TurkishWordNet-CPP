//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_JCN_H
#define WORDNET_JCN_H


#include "ICSimilarity.h"

class JCN : public ICSimilarity{
public:
    JCN(WordNet& wordNet, map<string, double> informationContents);
    double computeSimilarity(SynSet synSet1, SynSet synSet2) override;
};


#endif //WORDNET_JCN_H
