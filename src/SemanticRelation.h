//
// Created by olcay on 20.03.2019.
//

#ifndef WORDNET_SEMANTICRELATION_H
#define WORDNET_SEMANTICRELATION_H


#include "Relation.h"
#include "SemanticRelationType.h"

class SemanticRelation : public Relation {
private:
    SemanticRelationType relationType;
    int toIndex;
public:
    SemanticRelation(string name, string relationType, int toIndex = 0);
    SemanticRelation(string name, SemanticRelationType relationType, int toIndex = 0);
    static const int SEMANTIC_DEPENDENCY_SIZE = 25;
    static const string semanticDependency[SEMANTIC_DEPENDENCY_SIZE];
    static const SemanticRelationType semanticDependencyTags[SEMANTIC_DEPENDENCY_SIZE];
    static SemanticRelationType getSemanticTag(string tag);
    static SemanticRelationType reverse(SemanticRelationType semanticRelationType);
    int getToIndex();
    SemanticRelationType getRelationType();
    void setRelationType(SemanticRelationType relationType);
    string getTypeAsString() override;
    string to_string();
    string to_xml() override;
};


#endif //WORDNET_SEMANTICRELATION_H
