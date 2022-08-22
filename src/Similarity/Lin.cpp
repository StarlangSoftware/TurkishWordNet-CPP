//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include "Lin.h"

Lin::Lin(WordNet wordNet, map<string, double> informationContents) : ICSimilarity(wordNet, move(informationContents)) {

}

double Lin::computeSimilarity(SynSet synSet1, SynSet synSet2) {
    vector<string> pathToRootOfSynSet1 = wordNet.findPathToRoot(&synSet1);
    vector<string> pathToRootOfSynSet2 = wordNet.findPathToRoot(&synSet2);
    string LCSid = wordNet.findLCSid(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return (2 * informationContents.find(LCSid)->second)
           / (informationContents.find(synSet1.getId())->second + informationContents.find(synSet2.getId())->second);
}
