//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "Resnik.h"

#include <utility>

/**
 * Class constructor that sets the wordnet and the information content hash map.
 * @param wordNet WordNet for which similarity metrics will be calculated.
 * @param informationContents Information content hash map.
 */
Resnik::Resnik(WordNet &wordNet, map<string, double> informationContents) : ICSimilarity(wordNet, std::move(informationContents)) {
}

/**
 * Computes Resnik wordnet similarity metric between two synsets.
 * @param synSet1 First synset
 * @param synSet2 Second synset
 * @return Resnik wordnet similarity metric between two synsets
 */
double Resnik::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    string LCSid = wordNet.findLCSid(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return informationContents.find(LCSid)->second;
}
