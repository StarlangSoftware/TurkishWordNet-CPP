//
// Created by olcay on 19.03.2019.
//

#include "Relation.h"

Relation::Relation(string name) {
    this->name = move(name);
}

string Relation::getName() {
    return name;
}

void Relation::setName(string name) {
    this->name = name;
}
