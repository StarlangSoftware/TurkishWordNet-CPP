//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_WUPALMER_H
#define WORDNET_WUPALMER_H


#include "Similarity.h"

class WuPalmer : public Similarity {
public:
    explicit WuPalmer(WordNet& wordNet);
    double computeSimilarity(SynSet synSet1, SynSet synSet2) override;
};


#endif //WORDNET_WUPALMER_H
