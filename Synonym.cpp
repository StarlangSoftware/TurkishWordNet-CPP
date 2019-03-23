//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include "Synonym.h"
#include <fstream>

void Synonym::addLiteral(Literal literal) {
    literals.emplace_back(literal);
}

Literal Synonym::getLiteral(int index) {
    return literals.at(index);
}

Literal Synonym::getLiteral(string name) {
    for (Literal literal:literals){
        if (literal.getName() == name){
            return literal;
        }
    }
}

int Synonym::literalSize() {
    return literals.size();
}

bool Synonym::contains(Literal literal) {
    for (const Literal &current : literals){
        if (current == literal){
            return true;
        }
    }
    return false;
}

bool Synonym::containsLiteral(string literalName) {
    for (Literal current : literals){
        if (current.getName() == literalName){
            return true;
        }
    }
    return false;
}

void Synonym::removeLiteral(Literal toBeRemoved) {
    for (auto it = literals.begin() ; it != literals.end(); ++it){
        if (*it == toBeRemoved){
            literals.erase(it);
            break;
        }
    }
}

void Synonym::saveAsXml(ofstream& outfile) {
    outfile << "<SYNONYM>";
    for (Literal literal:literals){
        literal.saveAsXml(outfile);
    }
    outfile << "</SYNONYM>";
}

string Synonym::to_string() {
    string result;
    for (Literal literal : literals){
        result += literal.getName() + " ";
    }
    return result;
}
