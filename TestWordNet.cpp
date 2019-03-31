//
// Created by Olcay Taner YILDIZ on 2019-03-30.
//

#include <iostream>
#include "WordNet.h"

int main(){
    WordNet wordNet = WordNet("english_wordnet_version_31.xml");
    wordNet.saveAsXml("deneme.xml");
}