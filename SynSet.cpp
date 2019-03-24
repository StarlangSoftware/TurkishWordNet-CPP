//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#include <fstream>
#include <Word.h>
#include "SynSet.h"
#include "InterlingualRelation.h"
#include "SemanticRelation.h"

SynSet::SynSet(string id) {
    this->id = move(id);
}

string SynSet::getId() {
    return id;
}

void SynSet::setId(string id) {
    this->id = move(id);
}

void SynSet::setDefinition(string definition) {
    this->definition = Word::split(move(definition), "|");
}

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

string SynSet::getDefinition() {
    if (!definition.empty()){
        return definition.at(0);
    }
}

string SynSet::representative() {
    return getSynonym().getLiteral(0).getName();
}

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

string SynSet::getDefinition(int index) {
    if (index < definition.size() && index >= 0){
        return definition[index];
    } else {
        return "";
    }
}

int SynSet::numberOfDefinitions() {
    return definition.size();
}

void SynSet::setExample(string example) {
    this->example = move(example);
}

string SynSet::getExample() {
    return example;
}

void SynSet::setBcs(int bcs) {
    if (bcs >= 1 && bcs <= 3){
        this->bcs = bcs;
    }
}

int SynSet::getBcs() {
    return bcs;
}

void SynSet::setPos(Pos pos) {
    this->pos = pos;
}

Pos SynSet::getPos() {
    return pos;
}

void SynSet::setNote(string note) {
    this->note = move(note);
}

string SynSet::getNote() {
    return note;
}

void SynSet::addRelation(Relation *relation) {
    relations.emplace_back(relation);
}

void SynSet::removeRelation(Relation *relation) {
    for (auto it = relations.begin() ; it != relations.end(); ++it){
        if (*(*it) == *relation){
            relations.erase(it);
            break;
        }
    }
}

void SynSet::removeRelation(string name) {
    for (auto it = relations.begin() ; it != relations.end(); ++it){
        if ((*it)->getName() == name){
            relations.erase(it);
            break;
        }
    }
}

Relation *SynSet::getRelation(int index) {
    return relations.at(index);
}

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

int SynSet::relationSize() {
    return relations.size();
}

void SynSet::addLiteral(Literal literal) {
    synonym.addLiteral(move(literal));
}

Synonym SynSet::getSynonym() {
    return synonym;
}

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

bool SynSet::containsRelation(Relation *relation) {
    for (Relation* r : relations) {
        if (*r == *relation){
            return true;
        }
    }
    return false;
}

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

string SynSet::to_string() {
    if (!definition.empty()){
        return definition[0];
    } else {
        return representative();
    }
}

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
    if (!definition.empty()){
        outfile << "<DEF>" + getLongDefinition() + "</DEF>";
    }
    if (!example.empty()){
        outfile << "<EXAMPLE>" + example + "</EXAMPLE>";
    }
    outfile << "</SYNSET>\n";
}

void SynSet::saveAsLmf(ofstream& outfile, string ili) {
    string posChar;
    switch (pos){
        case Pos::NOUN:
            posChar = "n";
            break;
        case Pos::ADJECTIVE:
            posChar = "a";
            break;
        case Pos::ADVERB:
            posChar = "r";
            break;
        case Pos::VERB:
            posChar = "v";
            break;
        default:
            posChar = "x";
            break;
    }
    outfile << "\t<Synset id=\"" + id + "\" ili=\"" + ili + "\" partOfSpeech=\"" + posChar + "\">\n";
    if (!getLongDefinition().empty()){
        string longDefinition = getLongDefinition();
        if (longDefinition.find("\"") != string::npos){
            longDefinition = Word::replaceAll(longDefinition, "\"", "&quot;");
        }
        outfile << "\t\t<Definition>" + longDefinition + "</Definition>\n";
    }
    for (Relation* r:relations){
        if (SemanticRelation* semanticRelation = dynamic_cast<SemanticRelation*>(r)){
            switch (((SemanticRelation*) r)->getRelationType()){
                case SemanticRelationType::MEMBER_TOPIC:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"has_domain_topic\"/>\n";
                    break;
                case SemanticRelationType::MEMBER_REGION:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"has_domain_region\"/>\n";
                    break;
                case SemanticRelationType::PART_HOLONYM:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"holo_part\"/>\n";
                    break;
                case SemanticRelationType::PART_MERONYM:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"mero_part\"/>\n";
                    break;
                case SemanticRelationType::MEMBER_HOLONYM:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"holo_member\"/>\n";
                    break;
                case SemanticRelationType::MEMBER_MERONYM:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"mero_member\"/>\n";
                    break;
                case SemanticRelationType::SUBSTANCE_HOLONYM:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"holo_substance\"/>\n";
                    break;
                case SemanticRelationType::SUBSTANCE_MERONYM:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"mero_substance\"/>\n";
                    break;
                case SemanticRelationType::ALSO_SEE:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"also\"/>\n";
                    break;
                case SemanticRelationType::DERIVATION_RELATED:
                    break;
                default:
                    outfile << "\t\t<SynsetRelation target=\"" + r->getName() + "\" relType=\"" + ((SemanticRelation*) r)->getTypeAsString() + "\"/>\n";
                    break;
            }
        }
    }
    if (!example.empty()){
        outfile << "\t\t<Example>" + getExample() + "</Example>\n";
    }
    outfile << "\t</Synset>\n";
}
