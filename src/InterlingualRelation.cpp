//
// Created by olcay on 21.03.2019.
//

#include "InterlingualRelation.h"

const string InterlingualRelation::ilrDependency[INTERLINGUAL_DEPENDENCY_SIZE] = {"Hypernym", "Near_antonym", "Holo_member", "Holo_part", "Holo_portion",
                                                                   "Usage_domain", "Category_domain", "Be_in_state", "Subevent", "Verb_group",
                                                                   "Similar_to", "Also_see", "Causes", "SYNONYM"};

const InterlingualDependencyType InterlingualRelation::interlinguaDependencyTags[INTERLINGUAL_DEPENDENCY_SIZE] = {InterlingualDependencyType::HYPERNYM, InterlingualDependencyType::NEAR_ANTONYM, InterlingualDependencyType::HOLO_MEMBER, InterlingualDependencyType::HOLO_PART, InterlingualDependencyType::HOLO_PORTION,
                                                                                                                  InterlingualDependencyType::USAGE_DOMAIN, InterlingualDependencyType::CATEGORY_DOMAIN, InterlingualDependencyType::BE_IN_STATE, InterlingualDependencyType::SUBEVENT, InterlingualDependencyType::VERB_GROUP,
                                                                                                                  InterlingualDependencyType::SIMILAR_TO, InterlingualDependencyType::ALSO_SEE, InterlingualDependencyType::CAUSES, InterlingualDependencyType::SYNONYM};

/**
 * Compares specified {@code String} tag with the tags in InterlingualDependencyType {@code Array}, ignoring case
 * considerations.
 *
 * @param tag String to compare
 * @return interlingual dependency type according to specified tag
 */
InterlingualDependencyType InterlingualRelation::getInterlinguaDependencyTag(string tag) {
    for (int j = 0; j < INTERLINGUAL_DEPENDENCY_SIZE; j++) {
        if (tag == InterlingualRelation::ilrDependency[j]) {
            return InterlingualRelation::interlinguaDependencyTags[j];
        }
    }
}

/**
 * InterlingualRelation method sets its relation with the specified String name, then gets the InterlingualDependencyType
 * according to specified String dependencyType.
 *
 * @param name           relation name
 * @param dependencyType interlingual dependency type
 */
InterlingualRelation::InterlingualRelation(string name, string dependencyType) : Relation(move(name)){
    this->dependencyType = getInterlinguaDependencyTag(move(dependencyType));
}

/**
 * Accessor method to get the private InterlingualDependencyType.
 *
 * @return interlingual dependency type
 */
InterlingualDependencyType InterlingualRelation::getType(){
    return dependencyType;
}

/**
 * Method to retrieve interlingual dependency type as {@code String}.
 *
 * @return String interlingual dependency type
 */
string InterlingualRelation::getTypeAsString(){
    return InterlingualRelation::ilrDependency[static_cast<int>(dependencyType)];
}

/**
 * toString method to print interlingual dependency type.
 *
 * @return String of relation name
 */
string InterlingualRelation::to_string(){
    return getTypeAsString() + "->" + name;
}

string InterlingualRelation::to_xml(){
    return "<ILR>" + name + "<TYPE>" + getTypeAsString() + "</TYPE></ILR>";
}
