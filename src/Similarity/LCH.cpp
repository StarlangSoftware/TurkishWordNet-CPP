//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "LCH.h"

/**
 * Class constructor that sets the wordnet.
 * @param wordNet WordNet for which similarity metrics will be calculated.
 */
LCH::LCH(WordNet wordNet) : Similarity(wordNet){
}

/**
 * Computes LCH wordnet similarity metric between two synsets.
 * @param synSet1 First synset
 * @param synSet2 Second synset
 * @return LCH wordnet similarity metric between two synsets
 */
double LCH::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    int pathLength = wordNet.findPathLength(pathToRootOfSynSet1, pathToRootOfSynSet2);
    float maxDepth = fmax(pathToRootOfSynSet1.size(), pathToRootOfSynSet2.size());
    return -log(pathLength / (2 * maxDepth));
}
