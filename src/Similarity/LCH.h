//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_LCH_H
#define WORDNET_LCH_H


#include "Similarity.h"

class LCH : public Similarity{
public:
    explicit LCH(WordNet wordNet);
    double computeSimilarity(SynSet synSet1, SynSet synSet2) override;
};


#endif //WORDNET_LCH_H
