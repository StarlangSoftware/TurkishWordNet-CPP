#include <utility>

//
// Created by olcay on 19.03.2019.
//

#include "Relation.h"

/**
 * A constructor that sets the name of the relation.
 *
 * @param _name String relation name
 */
Relation::Relation(const string& _name) {
    this->name = _name;
}

/**
 * Accessor method for the relation name.
 *
 * @return String relation name
 */
string Relation::getName() const{
    return name;
}

/**
 * Mutator for the relation name.
 *
 * @param _name String relation name
 */
void Relation::setName(const string& _name) {
    this->name = _name;
}
