//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#ifndef WORDNET_SYNONYM_H
#define WORDNET_SYNONYM_H

#include <vector>
#include "Literal.h"

class Synonym {
private:
    vector<Literal> literals;
public:
    Synonym() = default;
    void addLiteral(Literal literal);
    Literal getLiteral(int index);
    Literal getLiteral(string name);
    int literalSize();
    bool contains(Literal literal);
    bool containsLiteral(string literalName);
    void removeLiteral(Literal toBeRemoved);
    void saveAsXml(ofstream& outfile);
    string to_string();
};


#endif //WORDNET_SYNONYM_H
