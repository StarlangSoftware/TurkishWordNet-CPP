//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "WuPalmer.h"

/**
 * Class constructor that sets the wordnet and the information content hash map.
 * @param wordNet WordNet for which similarity metrics will be calculated.
 */
WuPalmer::WuPalmer(WordNet &wordNet) : Similarity(wordNet) {
}

/**
 * Computes Wu-Palmer wordnet similarity metric between two synsets.
 * @param synSet1 First synset
 * @param synSet2 Second synset
 * @return Wu-Palmer wordnet similarity metric between two synsets
 */
double WuPalmer::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    double LCSdepth = wordNet.findLCSdepth(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return 2 * LCSdepth / (pathToRootOfSynSet1.size() + pathToRootOfSynSet2.size());
}
