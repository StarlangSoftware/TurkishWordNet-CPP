//
// Created by olcay on 21.03.2019.
//

#ifndef WORDNET_INTERLINGUALRELATION_H
#define WORDNET_INTERLINGUALRELATION_H

#include "Relation.h"
#include "InterlingualDependencyType.h"

class InterlingualRelation : public Relation {
private:
    InterlingualDependencyType dependencyType;
public:
    static const int INTERLINGUAL_DEPENDENCY_SIZE = 14;
    static const string ilrDependency[INTERLINGUAL_DEPENDENCY_SIZE];
    static const InterlingualDependencyType interlinguaDependencyTags[INTERLINGUAL_DEPENDENCY_SIZE];
    static InterlingualDependencyType getInterlinguaDependencyTag(string tag);
    InterlingualRelation(string name, string dependencyType);
    InterlingualDependencyType getType();
    string getTypeAsString() override;
    string to_string();
    string to_xml() override;
};


#endif //WORDNET_INTERLINGUALRELATION_H
