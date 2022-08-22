//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "JCN.h"

JCN::JCN(WordNet &wordNet, map<string, double> informationContents) : ICSimilarity(wordNet, move(informationContents)) {
}

double JCN::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    string LCSid = wordNet.findLCSid(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return 1 / (informationContents.find(synSet1.getId())->second + informationContents.find(synSet2.getId())->second - 2 * informationContents.find(LCSid)->second);
}
