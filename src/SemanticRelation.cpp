//
// Created by olcay on 20.03.2019.
//

#include "SemanticRelation.h"

const string SemanticRelation::semanticDependency[SEMANTIC_DEPENDENCY_SIZE] = {"ANTONYM", "HYPERNYM",
                                                                               "INSTANCE_HYPERNYM", "HYPONYM", "INSTANCE_HYPONYM", "MEMBER_HOLONYM", "SUBSTANCE_HOLONYM",
                                                                               "PART_HOLONYM", "MEMBER_MERONYM", "SUBSTANCE_MERONYM", "PART_MERONYM", "ATTRIBUTE",
                                                                               "DERIVATION_RELATED", "DOMAIN_TOPIC", "MEMBER_TOPIC", "DOMAIN_REGION", "MEMBER_REGION",
                                                                               "DOMAIN_USAGE", "MEMBER_USAGE", "ENTAILMENT", "CAUSE", "ALSO_SEE",
                                                                               "VERB_GROUP", "SIMILAR_TO", "PARTICIPLE_OF_VERB"};

const SemanticRelationType SemanticRelation::semanticDependencyTags[SEMANTIC_DEPENDENCY_SIZE] = {SemanticRelationType::ANTONYM, SemanticRelationType::HYPERNYM,
                                                                                                 SemanticRelationType::INSTANCE_HYPERNYM, SemanticRelationType::HYPONYM, SemanticRelationType::INSTANCE_HYPONYM, SemanticRelationType::MEMBER_HOLONYM, SemanticRelationType::SUBSTANCE_HOLONYM,
                                                                                                 SemanticRelationType::PART_HOLONYM, SemanticRelationType::MEMBER_MERONYM, SemanticRelationType::SUBSTANCE_MERONYM, SemanticRelationType::PART_MERONYM, SemanticRelationType::ATTRIBUTE,
                                                                                                 SemanticRelationType::DERIVATION_RELATED, SemanticRelationType::DOMAIN_TOPIC, SemanticRelationType::MEMBER_TOPIC, SemanticRelationType::DOMAIN_REGION, SemanticRelationType::MEMBER_REGION,
                                                                                                 SemanticRelationType::DOMAIN_USAGE, SemanticRelationType::MEMBER_USAGE, SemanticRelationType::ENTAILMENT, SemanticRelationType::CAUSE, SemanticRelationType::ALSO_SEE,
                                                                                                 SemanticRelationType::VERB_GROUP, SemanticRelationType::SIMILAR_TO, SemanticRelationType::PARTICIPLE_OF_VERB};

/**
 * A constructor to initialize relation type and the relation name.
 *
 * @param name         name of the relation
 * @param relationType String semantic dependency tag
 */
SemanticRelation::SemanticRelation(const string& name, const string& relationType, int toIndex) : Relation(name){
    this->relationType = getSemanticTag(relationType);
    this->toIndex = toIndex;
}

/**
 * Another constructor that initializes relation type, relation name, and the index.
 *
 * @param name         name of the relation
 * @param relationType String semantic dependency tag
 * @param toIndex      index of the relation
 */
SemanticRelation::SemanticRelation(const string& name, SemanticRelationType relationType, int toIndex) : Relation(name){
    this->relationType = relationType;
    this->toIndex = toIndex;
}

/**
 * Accessor to retrieve semantic relation type given a specific semantic dependency tag.
 *
 * @param tag String semantic dependency tag
 * @return semantic relation type
 */
SemanticRelationType SemanticRelation::getSemanticTag(const string& tag){
    for (int j = 0; j < SEMANTIC_DEPENDENCY_SIZE; j++) {
        if (tag == SemanticRelation::semanticDependency[j]) {
            return SemanticRelation::semanticDependencyTags[j];
        }
    }
}

/**
 * Returns the reverse of a specific semantic relation type.
 *
 * @param semanticRelationType semantic relation type to be reversed
 * @return reversed version of the semantic relation type
 */
SemanticRelationType SemanticRelation::reverse(SemanticRelationType semanticRelationType){
    switch (semanticRelationType){
        case SemanticRelationType::HYPERNYM:
            return SemanticRelationType::HYPONYM;
        case SemanticRelationType::HYPONYM:
            return SemanticRelationType::HYPERNYM;
        case SemanticRelationType::ANTONYM:
            return SemanticRelationType::ANTONYM;
        case SemanticRelationType::INSTANCE_HYPERNYM:
            return SemanticRelationType::INSTANCE_HYPONYM;
        case SemanticRelationType::INSTANCE_HYPONYM:
            return SemanticRelationType::INSTANCE_HYPERNYM;
        case SemanticRelationType::MEMBER_HOLONYM:
            return SemanticRelationType::MEMBER_MERONYM;
        case SemanticRelationType::MEMBER_MERONYM:
            return SemanticRelationType::MEMBER_HOLONYM;
        case SemanticRelationType::PART_MERONYM:
            return SemanticRelationType::PART_HOLONYM;
        case SemanticRelationType::PART_HOLONYM:
            return SemanticRelationType::PART_MERONYM;
        case SemanticRelationType::SUBSTANCE_MERONYM:
            return SemanticRelationType::SUBSTANCE_HOLONYM;
        case SemanticRelationType::SUBSTANCE_HOLONYM:
            return SemanticRelationType::SUBSTANCE_MERONYM;
        case SemanticRelationType::DOMAIN_TOPIC:
            return SemanticRelationType::MEMBER_TOPIC;
        case SemanticRelationType::MEMBER_TOPIC:
            return SemanticRelationType::DOMAIN_TOPIC;
        case SemanticRelationType::DOMAIN_REGION:
            return SemanticRelationType::MEMBER_REGION;
        case SemanticRelationType::MEMBER_REGION:
            return SemanticRelationType::DOMAIN_REGION;
        case SemanticRelationType::DOMAIN_USAGE:
            return SemanticRelationType::MEMBER_USAGE;
        case SemanticRelationType::MEMBER_USAGE:
            return SemanticRelationType::DOMAIN_USAGE;
        case SemanticRelationType::DERIVATION_RELATED:
            return SemanticRelationType::DERIVATION_RELATED;
        default:
            break;
    }
}

/**
 * Returns the index value.
 *
 * @return index value.
 */
int SemanticRelation::getToIndex() const{
    return toIndex;
}

/**
 * Accessor for the semantic relation type.
 *
 * @return semantic relation type
 */
SemanticRelationType SemanticRelation::getRelationType() const{
    return relationType;
}

/**
 * Mutator for the semantic relation type.
 *
 * @param _relationType semantic relation type.
 */
void SemanticRelation::setRelationType(SemanticRelationType _relationType){
    this->relationType = _relationType;
}

/**
 * Accessor method to retrieve the semantic relation type as a String.
 *
 * @return String semantic relation type
 */
string SemanticRelation::getTypeAsString() const{
    return SemanticRelation::semanticDependency[static_cast<int>(relationType)];
}

/**
 * Overridden toString method to print semantic relation types and names.
 *
 * @return semantic relation types and names
 */
string SemanticRelation::to_string() const{
    return getTypeAsString() + "->" + name;
}

string SemanticRelation::to_xml() const{
    if (toIndex == 0){
        return "<SR>" + name + "<TYPE>" + getTypeAsString() + "</TYPE></SR>";
    } else {
        return "<SR>" + name + "<TYPE>" + getTypeAsString() + "</TYPE>" + "<TO>" + std::to_string(toIndex) + "</TO></SR>";
    }
}
