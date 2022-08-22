#include <utility>

//
// Created by olcay on 19.03.2019.
//

#include "Relation.h"

/**
 * A constructor that sets the name of the relation.
 *
 * @param name String relation name
 */
Relation::Relation(string name) {
    this->name = move(name);
}

/**
 * Accessor method for the relation name.
 *
 * @return String relation name
 */
string Relation::getName() {
    return name;
}

/**
 * Mutator for the relation name.
 *
 * @param name String relation name
 */
void Relation::setName(string name) {
    this->name = move(name);
}
