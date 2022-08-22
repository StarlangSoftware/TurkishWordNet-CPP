//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#ifndef WORDNET_SIMILARITYPATH_H
#define WORDNET_SIMILARITYPATH_H


#include "Similarity.h"

class SimilarityPath : public Similarity {
public:
    explicit SimilarityPath(WordNet& wordNet);
    double computeSimilarity(SynSet synSet1, SynSet synSet2) override;
};


#endif //WORDNET_SIMILARITYPATH_H
