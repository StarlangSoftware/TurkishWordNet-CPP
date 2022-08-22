//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "WuPalmer.h"

WuPalmer::WuPalmer(WordNet &wordNet) : Similarity(wordNet) {
}

double WuPalmer::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    double LCSdepth = wordNet.findLCSdepth(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return 2 * LCSdepth / (pathToRootOfSynSet1.size() + pathToRootOfSynSet2.size());
}
