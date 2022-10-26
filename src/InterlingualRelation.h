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
    static InterlingualDependencyType getInterlinguaDependencyTag(const string& tag);
    InterlingualRelation(const string& name, const string& dependencyType);
    InterlingualDependencyType getType() const;
    string getTypeAsString() const override;
    string to_string() const;
    string to_xml() const override;
};


#endif //WORDNET_INTERLINGUALRELATION_H
