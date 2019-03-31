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

SemanticRelation::SemanticRelation(string name, string relationType, int toIndex) : Relation(move(name)){
    this->relationType = getSemanticTag(move(relationType));
    this->toIndex = toIndex;
}

SemanticRelation::SemanticRelation(string name, SemanticRelationType relationType, int toIndex) : Relation(move(name)){
    this->relationType = relationType;
    this->toIndex = toIndex;
}

SemanticRelationType SemanticRelation::getSemanticTag(string tag) {
    for (int j = 0; j < SEMANTIC_DEPENDENCY_SIZE; j++) {
        if (tag == SemanticRelation::semanticDependency[j]) {
            return SemanticRelation::semanticDependencyTags[j];
        }
    }
}

SemanticRelationType SemanticRelation::reverse(SemanticRelationType semanticRelationType) {
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
        default:
            break;
    }
}

int SemanticRelation::getToIndex() {
    return toIndex;
}

SemanticRelationType SemanticRelation::getRelationType(){
    return relationType;
}

void SemanticRelation::setRelationType(SemanticRelationType relationType){
    this->relationType = relationType;
}

string SemanticRelation::getTypeAsString(){
    return SemanticRelation::semanticDependency[static_cast<int>(relationType)];
}

string SemanticRelation::to_string() {
    return getTypeAsString() + "->" + name;
}

string SemanticRelation::to_xml() {
    if (toIndex == 0){
        return "<SR>" + name + "<TYPE>" + getTypeAsString() + "</TYPE></SR>";
    } else {
        return "<SR>" + name + "<TYPE>" + getTypeAsString() + "</TYPE>" + "<TO>" + std::to_string(toIndex) + "</TO></SR>";
    }
}
