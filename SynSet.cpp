//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include <fstream>
#include <Word.h>
#include "SynSet.h"
#include "InterlingualRelation.h"
#include "SemanticRelation.h"

/**
 * Constructor initialize SynSet ID, synonym and relations list.
 *
 * @param id Synset ID
 */
SynSet::SynSet(string id) {
    this->id = move(id);
}

/**
 * Accessor for the SynSet ID.
 *
 * @return SynSet ID
 */
string SynSet::getId() {
    return id;
}

/**
 * Mutator method for the SynSet ID.
 *
 * @param id SynSet ID to be set
 */
void SynSet::setId(string id) {
    for (int i = 0; i < getSynonym().literalSize(); i++){
        synonym.getLiteral(i).setSynSetId(id);
    }
    this->id = move(id);
}

/**
 * Mutator method for the definition.
 *
 * @param definition String definition
 */
void SynSet::setDefinition(string definition) {
    this->definition = Word::split(move(definition), "|");
}

/**
 * Removes the specified definition from long definition.
 *
 * @param definition definition to be removed
 */
void SynSet::removeDefinition(string definition) {
    string longDefinition = getLongDefinition();
    if (Word::startsWith(longDefinition, definition + "|")){
        setDefinition(Word::replaceAll(longDefinition, definition + "|", ""));
    } else {
        if (Word::endsWith(longDefinition, "|" + definition)){
            setDefinition(Word::replaceAll(longDefinition, "|" + definition, ""));
        } else {
            if (longDefinition.find("|" + definition + "|") != string::npos){
                setDefinition(Word::replaceAll(longDefinition, "|" + definition, ""));
            }
        }
    }
}

/**
 * Removes the same definitions from long definition.
 *
 * @param locale Locale of the programme that will be used in converting upper/lower cases
 */
void SynSet::removeSameDefinitions() {
    string definition = getLongDefinition();
    bool removed = true;
    while (!definition.empty() && removed){
        removed = false;
        for (int j = 0; j < getSynonym().literalSize(); j++){
            Literal literal = getSynonym().getLiteral(j);
            string word = literal.getName();
            string uppercaseWord = Word::substring(literal.getName(), 0, 1) + Word::substring(literal.getName(), 1);
            if (definition.find("|" + word + "|") != string::npos){
                definition = Word::replaceAll(definition, "|" + word + "|", "|");
                removed = true;
            }
            if (definition.find("|" + word + "; ") != string::npos){
                definition = Word::replaceAll(definition, "|" + word + "; ", "|");
                removed = true;
            }
            if (definition.find("|" + uppercaseWord + "|") != string::npos){
                definition = Word::replaceAll(definition, "|" + uppercaseWord + "|", "|");
                removed = true;
            }
            if (definition.find("|" + uppercaseWord + "; ") != string::npos){
                definition = Word::replaceAll(definition, "|" + uppercaseWord + "; ", "|");
                removed = true;
            }
            if (definition.find("; " + word + "|") != string::npos){
                definition = Word::replaceAll(definition, "; " + word + "|", "|");
                removed = true;
            }
            if (definition.find("; " + uppercaseWord + "|") != string::npos){
                definition = Word::replaceAll(definition, "; " + uppercaseWord + "|", "|");
                removed = true;
            }
            if (Word::endsWith(definition, "; " + word)){
                definition = Word::replaceAll(definition, "; " + word, "");
                removed = true;
            }
            if (Word::endsWith(definition, "|" + word)){
                definition = Word::replaceAll(definition, "|" + word, "");
                removed = true;
            }
            if (Word::startsWith(definition, word + "|")){
                definition = Word::replaceAll(definition, word + "|", "");
                removed = true;
            }
            if (Word::startsWith(definition, uppercaseWord + "|")){
                definition = Word::replaceAll(definition, uppercaseWord + "|", "");
                removed = true;
            }
            if (Word::endsWith(definition, "; " + uppercaseWord)){
                definition = Word::replaceAll(definition, "; " + uppercaseWord, "");
                removed = true;
            }
            if (Word::endsWith(definition, "|" + uppercaseWord)){
                definition = Word::replaceAll(definition, "|" + uppercaseWord, "");
                removed = true;
            }
            if (definition == word){
                definition = "";
                removed = true;
            }
        }
    }
    if (!definition.empty() && definition.length() > 0){
        setDefinition(definition);
    } else {
        setDefinition("NO DEFINITION");
    }
}

/**
 * Accessor for the definition.
 *
 * @return definition
 */
string SynSet::getDefinition() {
    if (!definition.empty()){
        return definition.at(0);
    }
}

/**
 * Returns the first literal's name.
 *
 * @return the first literal's name.
 */
string SynSet::representative() {
    return getSynonym().getLiteral(0).getName();
}

/**
 * Returns all the definitions in the list.
 *
 * @return all the definitions
 */
string SynSet::getLongDefinition() {
    if (!definition.empty()){
        string longDefinition = definition.at(0);
        for (int i = 1; i < definition.size(); i++){
            longDefinition += "|" + definition[i];
        }
        return longDefinition;
    } else {
        return "";
    }
}

/**
 * Sorts definitions list according to their lengths.
 */
void SynSet::sortDefinitions() {
    if (!definition.empty()){
        for (int i = 0; i < definition.size(); i++){
            for (int j = i + 1; j < definition.size(); j++){
                if (Word::size(definition[i]) < Word::size(definition[j])){
                    swap(definition[i], definition[j]);
                }
            }
        }
    }
}

/**
 * Accessor for the definition at specified index.
 *
 * @param index definition index to be accessed
 * @return definition at specified index
 */
string SynSet::getDefinition(int index) {
    if (index < definition.size() && index >= 0){
        return definition[index];
    } else {
        return "";
    }
}

/**
 * Returns number of definitions in the list.
 *
 * @return number of definitions in the list.
 */
int SynSet::numberOfDefinitions() {
    return definition.size();
}

/**
 * Mutator for the example.
 *
 * @param example String that will be used to set
 */
void SynSet::setExample(string example) {
    this->example = move(example);
}

/**
 * Accessor for the example.
 *
 * @return String example
 */
string SynSet::getExample() {
    return example;
}

/**
 * Mutator for the bcs value which enables the connection with the BalkaNet.
 *
 * @param bcs bcs value
 */
void SynSet::setBcs(int bcs) {
    if (bcs >= 1 && bcs <= 3){
        this->bcs = bcs;
    }
}

/**
 * Accessor for the bcs value
 *
 * @return bcs value
 */
int SynSet::getBcs() {
    return bcs;
}

/**
 * Mutator for the part of speech tags.
 *
 * @param pos part of speech tag
 */
void SynSet::setPos(Pos pos) {
    this->pos = pos;
}

/**
 * Accessor for the part of speech tag.
 *
 * @return part of speech tag
 */
Pos SynSet::getPos() {
    return pos;
}

/**
 * Mutator for the available notes.
 *
 * @param note String note to be set
 */
void SynSet::setNote(string note) {
    this->note = move(note);
}

/**
 * Accessor for the available notes.
 *
 * @return String note
 */
string SynSet::getNote() {
    return note;
}

/**
 * Appends the specified Relation to the end of relations list.
 *
 * @param relation element to be appended to the list
 */
void SynSet::addRelation(Relation *relation) {
    relations.emplace_back(relation);
}

/**
 * Removes the first occurrence of the specified element from relations list,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param relation element to be removed from the list, if present
 */
void SynSet::removeRelation(Relation *relation) {
    for (auto it = relations.begin() ; it != relations.end(); ++it){
        if (*(*it) == *relation){
            relations.erase(it);
            break;
        }
    }
}

/**
 * Removes the first occurrence of the specified element from relations list according to relation name,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param name element to be removed from the list, if present
 */
void SynSet::removeRelation(string name) {
    for (auto it = relations.begin() ; it != relations.end(); ++it){
        if ((*it)->getName() == name){
            relations.erase(it);
            break;
        }
    }
}

/**
 * Returns the element at the specified position in relations list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in the list
 */
Relation *SynSet::getRelation(int index) {
    return relations.at(index);
}

/**
 * Returns interlingual relations with the synonym interlingual dependencies.
 *
 * @return a list of SynSets that has interlingual relations in it
 */
vector<string> SynSet::getInterlingual() {
    vector<string> result;
    for (auto &i : relations) {
        if (auto * semanticRelation = dynamic_cast<InterlingualRelation*>(i)){
            auto * relation = (InterlingualRelation*) i;
            if (relation->getType() == InterlingualDependencyType::SYNONYM){
                result.emplace_back(relation->getName());
            }
        }
    }
    return result;
}

/**
 * Returns the size of the relations list.
 *
 * @return the size of the relations list
 */
int SynSet::relationSize() {
    return relations.size();
}

/**
 * Adds a specified literal to the synonym.
 *
 * @param literal literal to be added
 */
void SynSet::addLiteral(Literal literal) {
    synonym.addLiteral(move(literal));
}

/**
 * Accessor for the synonym.
 *
 * @return synonym
 */
Synonym SynSet::getSynonym() {
    return synonym;
}

/**
 * Compares literals of synonym and the specified SynSet, returns true if their have same literals.
 *
 * @param synSet SynSet to compare
 * @return true if SynSets have same literals, false otherwise
 */
bool SynSet::containsSameLiteral(SynSet synSet) {
    for (int i = 0; i < synonym.literalSize(); i++){
        string literal1 = synonym.getLiteral(i).getName();
        for (int j = 0; j < synSet.getSynonym().literalSize(); j++){
            string literal2 = synSet.getSynonym().getLiteral(j).getName();
            if (literal1 == literal2){
                return true;
            }
        }
    }
    return false;
}

/**
 * Returns <tt>true</tt> if relations list contains the specified relation.
 *
 * @param relation element whose presence in the list is to be tested
 * @return <tt>true</tt> if the list contains the specified element
 */
bool SynSet::containsRelation(Relation *relation) {
    for (Relation* r : relations) {
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
bool SynSet::containsRelationType(SemanticRelationType semanticRelationType) {
    for (Relation* relation : relations) {
        if (auto * semanticRelation = dynamic_cast<SemanticRelation*>(relation)){
            if (semanticRelation->getRelationType() == semanticRelationType){
                return true;
            }
        }
    }
    return false;
}

/**
 * Merges synonym and a specified SynSet with their definitions, relations, part of speech tags and examples.
 *
 * @param synSet SynSet to be merged
 */
void SynSet::mergeSynSet(SynSet synSet) {
    for (int i = 0; i < synSet.getSynonym().literalSize(); i++){
        if (!synonym.contains(synSet.getSynonym().getLiteral(i))){
            synonym.addLiteral(synSet.getSynonym().getLiteral(i));
        }
    }
    if (definition.empty() && !synSet.getDefinition().empty()){
        setDefinition(synSet.getDefinition());
    } else {
        if (!definition.empty() && !synSet.getDefinition().empty() && getLongDefinition() != synSet.getLongDefinition()){
            setDefinition(getLongDefinition() + "|" + synSet.getLongDefinition());
        }
    }
    if (synSet.relationSize() != 0){
        for (int i = 0; i < synSet.relationSize(); i++){
            if (!containsRelation(synSet.getRelation(i))){
                addRelation(synSet.getRelation(i));
            }
        }
    }
    if (example.empty() && !synSet.example.empty()){
        example = synSet.example;
    }
}

/**
 * Overridden toString method to print the first definition or representative.
 *
 * @return print the first definition or representative.
 */
string SynSet::to_string() {
    if (!definition.empty()){
        return definition[0];
    } else {
        return representative();
    }
}

/**
 * Method to write SynSets to the specified file in the XML format.
 *
 * @param outfile BufferedWriter to write XML files
 */
void SynSet::saveAsXml(ofstream& outfile) {
    string polarity;
    outfile << "<SYNSET>";
    outfile << "<ID>" + id + "</ID>";
    synonym.saveAsXml(outfile);
    if (pos == Pos::NOUN){
        outfile << "<POS>n</POS>";
    } else {
        if (pos == Pos::ADJECTIVE){
            outfile << "<POS>a</POS>";
        } else {
            if (pos == Pos::VERB){
                outfile << "<POS>v</POS>";
            } else {
                if (pos == Pos::ADVERB){
                    outfile << "<POS>b</POS>";
                } else {
                    if (pos == Pos::CONJUNCTION){
                        outfile << "<POS>c</POS>";
                    } else {
                        if (pos == Pos::PRONOUN){
                            outfile << "<POS>r</POS>";
                        } else {
                            if (pos == Pos::INTERJECTION){
                                outfile << "<POS>i</POS>";
                            } else {
                                if (pos == Pos::PREPOSITION){
                                    outfile << "<POS>p</POS>";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (Relation* r:relations){
        outfile << r->to_xml();
    }
    if (!definition.empty()){
        outfile << "<DEF>" + getLongDefinition() + "</DEF>";
    }
    if (!example.empty()){
        outfile << "<EXAMPLE>" + example + "</EXAMPLE>";
    }
    outfile << "</SYNSET>\n";
}
