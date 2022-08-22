//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "SimilarityPath.h"

SimilarityPath::SimilarityPath(WordNet &wordNet) : Similarity(wordNet) {
}

double SimilarityPath::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    // Find path to root of both elements. Percolating up until root is necessary since depth is necessary to compute the score.
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    // Find path length
    int pathLength = wordNet.findPathLength(pathToRootOfSynSet1, pathToRootOfSynSet2);
    int maxDepth = (int)(fmax(pathToRootOfSynSet1.size(), pathToRootOfSynSet2.size()));
    return 2 * maxDepth - pathLength;
}
