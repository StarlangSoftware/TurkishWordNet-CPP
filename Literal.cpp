//
// Created by olcay on 21.03.2019.
//

#include "Literal.h"
#include "SemanticRelation.h"
#include <fstream>

Literal::Literal(string name, int sense, string synSetId) {
    this->name = move(name);
    this->sense = sense;
    this->synSetId = move(synSetId);
}

string Literal::getSynSetId() {
    return synSetId;
}

string Literal::getName() {
    return name;
}

int Literal::getSense() {
    return sense;
}

string Literal::getOrigin() {
    return origin;
}

void Literal::setOrigin(string origin) {
    this->origin = move(origin);
}

void Literal::setSense(int sense) {
    this->sense = sense;
}

void Literal::addRelation(Relation *relation) {
    relations.emplace_back(relation);
}

void Literal::removeRelation(Relation *relation) {
    for (auto it = relations.begin() ; it != relations.end(); ++it){
        if (*(*it) == *relation){
            relations.erase(it);
            break;
        }
    }
}

bool Literal::containsRelation(Relation *relation) {
    for (Relation* r : relations){
        if (*r == *relation){
            return true;
        }
    }
    return false;
}

bool Literal::containsRelationType(SemanticRelationType semanticRelationType) {
    for (Relation* relation : relations){
        if (SemanticRelation* semanticRelation = dynamic_cast<SemanticRelation*>(relation)){
            if (semanticRelation->getRelationType() == semanticRelationType){
                return true;
            }
        }
    }
    return false;
}

Relation* Literal::getRelation(int index){
    return relations.at(index);
}

int Literal::relationSize(){
    return relations.size();
}

void Literal::setName(string name){
    this->name = move(name);
}

void Literal::setSynSetId(string synSetId){
    this->synSetId = move(synSetId);
}

string Literal::to_string(){
    return name + " " + std::to_string(sense);
}

void Literal::saveAsXml(ofstream& outfile){
    if (name == "&"){
        outfile << "<LITERAL>&amp;<SENSE>" + std::to_string(sense) + "</SENSE>";
    } else {
        outfile << "<LITERAL>" + name + "<SENSE>" + std::to_string(sense) + "</SENSE>";
    }
    if (!origin.empty()){
        outfile << "<ORIGIN>" + origin + "</ORIGIN>";
    }
    for (Relation* r:relations){
        outfile << r->to_xml();
    }
    outfile << "</LITERAL>";
}