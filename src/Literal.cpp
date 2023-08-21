//
// Created by olcay on 21.03.2019.
//

#include "Literal.h"
#include "SemanticRelation.h"
#include <fstream>

/**
 * A constructor that initializes name, sense, SynSet ID and the relations.
 *
 * @param name     name of a literal
 * @param sense    index of sense
 * @param synSetId ID of the SynSet
 */
Literal::Literal(const string& name, int sense, const string& synSetId) {
    this->name = name;
    this->sense = sense;
    this->synSetId = synSetId;
}

/**
 * Accessor method to return SynSet ID.
 *
 * @return String of SynSet ID
 */
string Literal::getSynSetId() const{
    return synSetId;
}

/**
 * Accessor method to return name of the literal.
 *
 * @return name of the literal
 */
string Literal::getName() const{
    return name;
}

/**
 * Accessor method to return the index of sense of the literal.
 *
 * @return index of sense of the literal
 */
int Literal::getSense() const{
    return sense;
}

/**
 * Accessor method to return the origin of the literal.
 *
 * @return origin of the literal
 */
string Literal::getOrigin() const{
    return origin;
}

/**
 * Mutator method to set the origin with specified origin.
 *
 * @param _origin origin of the literal to set
 */
void Literal::setOrigin(const string& _origin) {
    this->origin = _origin;
}

/**
 * Mutator method to set the sense index of the literal.
 *
 * @param _sense sense index of the literal to set
 */
void Literal::setSense(int _sense) {
    this->sense = _sense;
}

/**
 * Appends the specified Relation to the end of relations list.
 *
 * @param relation element to be appended to the list
 */
void Literal::addRelation(Relation *relation) {
    relations.emplace_back(relation);
}

/**
 * Removes the first occurrence of the specified element from relations list,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param relation element to be removed from the list, if present
 */
void Literal::removeRelation(Relation *relation) {
    for (auto it = relations.begin() ; it != relations.end(); ++it){
        if (*(*it) == *relation){
            relations.erase(it);
            break;
        }
    }
}

/**
 * Returns <tt>true</tt> if relations list contains the specified relation.
 *
 * @param relation element whose presence in the list is to be tested
 * @return <tt>true</tt> if the list contains the specified element
 */
bool Literal::containsRelation(Relation *relation) const{
    for (Relation* r : relations){
        if (*r == *relation){
            return true;
        }
    }
    return false;
}

/**
 * Returns <tt>true</tt> if specified semantic relation type presents in the relations list.
 *
 * @param semanticRelationType element whose presence in the list is to be tested
 * @return <<tt>true</tt> if specified semantic relation type presents in the relations list
 */
bool Literal::containsRelationType(SemanticRelationType semanticRelationType) const{
    for (Relation* relation : relations){
        if (auto* semanticRelation = (SemanticRelation*)(relation)){
            if (semanticRelation->getRelationType() == semanticRelationType){
                return true;
            }
        }
    }
    return false;
}

/**
 * Returns the element at the specified position in relations list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in the list
 */
Relation* Literal::getRelation(int index) const{
    return relations.at(index);
}

/**
 * Returns size of relations list.
 *
 * @return the size of the list
 */
int Literal::relationSize() const{
    return relations.size();
}

/**
 * Mutator method to set name of a literal.
 *
 * @param _name name of the literal to set
 */
void Literal::setName(const string& _name){
    this->name = _name;
}

/**
 * Mutator method to set SynSet ID of a literal.
 *
 * @param _synSetId SynSet ID of the literal to set
 */
void Literal::setSynSetId(const string& _synSetId){
    this->synSetId = _synSetId;
}

/**
 * Overridden to_string method to print names and sense of literals.
 *
 * @return concatenated names and senses of literals
 */
string Literal::to_string() const{
    return name + " " + std::to_string(sense);
}

/**
 * Method to write Literals to the specified file in the XML format.
 *
 * @param outfile BufferedWriter to write XML files
 */
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

int Literal::getGroupNo() const {
    return groupNo;
}

void Literal::setGroupNo(int _groupNo) {
    this->groupNo = _groupNo;
}
