//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "LCH.h"

LCH::LCH(WordNet wordNet) : Similarity(wordNet){
}

double LCH::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    int pathLength = wordNet.findPathLength(pathToRootOfSynSet1, pathToRootOfSynSet2);
    float maxDepth = fmax(pathToRootOfSynSet1.size(), pathToRootOfSynSet2.size());
    return -log(pathLength / (2 * maxDepth));
}
