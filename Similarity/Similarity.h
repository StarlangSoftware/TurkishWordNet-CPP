//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_SIMILARITY_H
#define WORDNET_SIMILARITY_H


#include "../WordNet.h"

class Similarity {
protected:
    WordNet wordNet;
public:
    virtual double computeSimilarity(SynSet synSet1, SynSet synSet2) = 0;
    explicit Similarity(WordNet& wordNet){
        this->wordNet = wordNet;
    }
};


#endif //WORDNET_SIMILARITY_H
