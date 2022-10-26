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
    SemanticRelation(const string& name, const string& relationType, int toIndex = 0);
    SemanticRelation(const string& name, SemanticRelationType relationType, int toIndex = 0);
    static const int SEMANTIC_DEPENDENCY_SIZE = 25;
    static const string semanticDependency[SEMANTIC_DEPENDENCY_SIZE];
    static const SemanticRelationType semanticDependencyTags[SEMANTIC_DEPENDENCY_SIZE];
    static SemanticRelationType getSemanticTag(const string& tag);
    static SemanticRelationType reverse(SemanticRelationType semanticRelationType);
    int getToIndex() const;
    SemanticRelationType getRelationType() const;
    void setRelationType(SemanticRelationType relationType);
    string getTypeAsString() const override;
    string to_string() const;
    string to_xml() const override;
};


#endif //WORDNET_SEMANTICRELATION_H
