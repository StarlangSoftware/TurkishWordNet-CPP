//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include <fstream>
#include "StringUtils.h"
#include "SynSet.h"

#include <Dictionary/Word.h>

#include "InterlingualRelation.h"
#include "SemanticRelation.h"

/**
 * Constructor initialize SynSet ID, synonym and relations list.
 *
 * @param id Synset ID
 */
SynSet::SynSet(const string& id) {
    this->id = id;
}

/**
 * Accessor for the SynSet ID.
 *
 * @return SynSet ID
 */
string SynSet::getId() const{
    return id;
}

/**
 * Mutator method for the SynSet ID.
 *
 * @param _id SynSet ID to be set
 */
void SynSet::setId(const string& _id) {
    for (int i = 0; i < getSynonym().literalSize(); i++){
        synonym.getLiteral(i).setSynSetId(_id);
    }
    this->id = _id;
}

/**
 * Mutator method for the _definition.
 *
 * @param _definition String _definition
 */
void SynSet::setDefinition(const string& _definition) {
    this->definition = StringUtils::split(_definition, "|");
}

/**
 * Removes the specified _definition from long _definition.
 *
 * @param _definition _definition to be removed
 */
void SynSet::removeDefinition(const string& _definition) {
    string longDefinition = getLongDefinition();
    if (StringUtils::startsWith(longDefinition, _definition + "|")){
        setDefinition(StringUtils::replaceAll(longDefinition, _definition + "|", ""));
    } else {
        if (StringUtils::endsWith(longDefinition, "|" + _definition)){
            setDefinition(StringUtils::replaceAll(longDefinition, "|" + _definition, ""));
        } else {
            if (longDefinition.find("|" + _definition + "|") != string::npos){
                setDefinition(StringUtils::replaceAll(longDefinition, "|" + _definition, ""));
            }
        }
    }
}

/**
 * Removes the same definitions from long definition.
 */
void SynSet::removeSameDefinitions() {
    string _definition = getLongDefinition();
    bool removed = true;
    while (!_definition.empty() && removed){
        removed = false;
        for (int j = 0; j < getSynonym().literalSize(); j++){
            Literal literal = getSynonym().getLiteral(j);
            string word = literal.getName();
            string uppercaseWord = Word::substring(literal.getName(), 0, 1) + Word::substring(literal.getName(), 1);
            if (_definition.find("|" + word + "|") != string::npos){
                _definition = StringUtils::replaceAll(_definition, "|" + word + "|", "|");
                removed = true;
            }
            if (_definition.find("|" + word + "; ") != string::npos){
                _definition = StringUtils::replaceAll(_definition, "|" + word + "; ", "|");
                removed = true;
            }
            if (_definition.find("|" + uppercaseWord + "|") != string::npos){
                _definition = StringUtils::replaceAll(_definition, "|" + uppercaseWord + "|", "|");
                removed = true;
            }
            if (_definition.find("|" + uppercaseWord + "; ") != string::npos){
                _definition = StringUtils::replaceAll(_definition, "|" + uppercaseWord + "; ", "|");
                removed = true;
            }
            if (_definition.find("; " + word + "|") != string::npos){
                _definition = StringUtils::replaceAll(_definition, "; " + word + "|", "|");
                removed = true;
            }
            if (_definition.find("; " + uppercaseWord + "|") != string::npos){
                _definition = StringUtils::replaceAll(_definition, "; " + uppercaseWord + "|", "|");
                removed = true;
            }
            if (StringUtils::endsWith(_definition, "; " + word)){
                _definition = StringUtils::replaceAll(_definition, "; " + word, "");
                removed = true;
            }
            if (StringUtils::endsWith(_definition, "|" + word)){
                _definition = StringUtils::replaceAll(_definition, "|" + word, "");
                removed = true;
            }
            if (StringUtils::startsWith(_definition, word + "|")){
                _definition = StringUtils::replaceAll(_definition, word + "|", "");
                removed = true;
            }
            if (StringUtils::startsWith(_definition, uppercaseWord + "|")){
                _definition = StringUtils::replaceAll(_definition, uppercaseWord + "|", "");
                removed = true;
            }
            if (StringUtils::endsWith(_definition, "; " + uppercaseWord)){
                _definition = StringUtils::replaceAll(_definition, "; " + uppercaseWord, "");
                removed = true;
            }
            if (StringUtils::endsWith(_definition, "|" + uppercaseWord)){
                _definition = StringUtils::replaceAll(_definition, "|" + uppercaseWord, "");
                removed = true;
            }
            if (_definition == word){
                _definition = "";
                removed = true;
            }
        }
    }
    if (!_definition.empty() && _definition.length() > 0){
        setDefinition(_definition);
    } else {
        setDefinition("NO DEFINITION");
    }
}

/**
 * Accessor for the definition.
 *
 * @return definition
 */
string SynSet::getDefinition() const{
    if (!definition.empty()){
        return definition.at(0);
    }
}

/**
 * Returns the first literal's name.
 *
 * @return the first literal's name.
 */
string SynSet::representative() const{
    return getSynonym().getLiteral(0).getName();
}

/**
 * Returns all the definitions in the list.
 *
 * @return all the definitions
 */
string SynSet::getLongDefinition() const{
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
string SynSet::getDefinition(int index) const{
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
int SynSet::numberOfDefinitions() const{
    return definition.size();
}

/**
 * Mutator for the _example.
 *
 * @param _example String that will be used to set
 */
void SynSet::setExample(const string& _example) {
    this->example = _example;
}

/**
 * Accessor for the example.
 *
 * @return String example
 */
string SynSet::getExample() const{
    return example;
}

/**
 * Mutator for the _bcs value which enables the connection with the BalkaNet.
 *
 * @param _bcs _bcs value
 */
void SynSet::setBcs(int _bcs) {
    if (_bcs >= 1 && _bcs <= 3){
        this->bcs = _bcs;
    }
}

/**
 * Accessor for the bcs value
 *
 * @return bcs value
 */
int SynSet::getBcs() const{
    return bcs;
}

/**
 * Mutator for the part of speech tags.
 *
 * @param _pos part of speech tag
 */
void SynSet::setPos(Pos _pos) {
    this->pos = _pos;
}

/**
 * Accessor for the part of speech tag.
 *
 * @return part of speech tag
 */
Pos SynSet::getPos() const{
    return pos;
}

/**
 * Mutator for the available notes.
 *
 * @param _note String _note to be set
 */
void SynSet::setNote(const string& _note) {
    this->note = _note;
}

/**
 * Accessor for the available notes.
 *
 * @return String note
 */
string SynSet::getNote() const{
    return note;
}

/**
 * Mutator for the wiki pages.
 *
 * @param _wikiPage String Wiki page to be set
 */
void SynSet::setWikiPage(const string& _wikiPage) {
    this->wikiPage = _wikiPage;
}

/**
 * Accessor for the wiki page.
 *
 * @return String wiki page
 */
string SynSet::getWikiPage() const{
    return wikiPage;
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
void SynSet::removeRelation(const string& name) {
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
Relation *SynSet::getRelation(int index) const{
    return relations.at(index);
}

/**
 * Returns interlingual relations with the synonym interlingual dependencies.
 *
 * @return a list of SynSets that has interlingual relations in it
 */
vector<string> SynSet::getInterlingual() const{
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
int SynSet::relationSize() const{
    return relations.size();
}

/**
 * Adds a specified literal to the synonym.
 *
 * @param literal literal to be added
 */
void SynSet::addLiteral(const Literal& literal) {
    synonym.addLiteral(literal);
}

/**
 * Accessor for the synonym.
 *
 * @return synonym
 */
Synonym SynSet::getSynonym() const{
    return synonym;
}

/**
 * Compares literals of synonym and the specified SynSet, returns true if their have same literals.
 *
 * @param synSet SynSet to compare
 * @return true if SynSets have same literals, false otherwise
 */
bool SynSet::containsSameLiteral(const SynSet& synSet) const{
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
bool SynSet::containsRelation(Relation *relation) const{
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
 * @return true if specified semantic relation type presents in the relations list
 */
bool SynSet::containsRelationType(SemanticRelationType semanticRelationType) const{
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
void SynSet::mergeSynSet(const SynSet& synSet) {
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
string SynSet::to_string() const{
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
    if (!wikiPage.empty()){
        outfile << "<WIKI>" + getWikiPage() + "</WIKI>";
    }
    if (!definition.empty()){
        outfile << "<DEF>" + getLongDefinition() + "</DEF>";
    }
    if (!example.empty()){
        outfile << "<EXAMPLE>" + example + "</EXAMPLE>";
    }
    outfile << "</SYNSET>\n";
}
