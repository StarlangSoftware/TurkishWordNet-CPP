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
    void addLiteral(const Literal& literal);
    Literal getLiteral(int index) const;
    Literal getLiteral(const string& name) const;
    int literalSize() const;
    bool contains(const Literal& literal) const;
    bool containsLiteral(const string& literalName) const;
    void removeLiteral(const Literal& toBeRemoved);
    void saveAsXml(ofstream& outfile);
    string to_string() const;
};


#endif //WORDNET_SYNONYM_H
