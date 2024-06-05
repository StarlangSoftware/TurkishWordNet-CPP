//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "JCN.h"

/**
 * Class constructor that sets the wordnet and the information content hash map.
 * @param wordNet WordNet for which similarity metrics will be calculated.
 * @param informationContents Information content hash map.
 */
JCN::JCN(WordNet &wordNet, map<string, double> informationContents) : ICSimilarity(wordNet, std::move(informationContents)) {
}

/**
 * Computes JCN wordnet similarity metric between two synsets.
 * @param synSet1 First synset
 * @param synSet2 Second synset
 * @return JCN wordnet similarity metric between two synsets
 */
double JCN::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    string LCSid = wordNet.findLCSid(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return 1 / (informationContents.find(synSet1.getId())->second + informationContents.find(synSet2.getId())->second - 2 * informationContents.find(LCSid)->second);
}
