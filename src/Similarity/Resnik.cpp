//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "Resnik.h"

Resnik::Resnik(WordNet &wordNet, map<string, double> informationContents) : ICSimilarity(wordNet, informationContents) {
}

double Resnik::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    string LCSid = wordNet.findLCSid(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return informationContents.find(LCSid)->second;
}
