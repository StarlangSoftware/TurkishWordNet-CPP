//
// Created by olcay on 29.03.2019.
//

#include <iostream>
#include <utility>
#include "WordNet.h"
#include "XmlDocument.h"
#include "SemanticRelation.h"
#include "InterlingualRelation.h"

void WordNet::readWordNet(string fileName) {
    XmlElement *rootNode, *synSetNode, *partNode, *ilrNode, *srNode, *typeNode, *toNode, *literalNode, *textNode, *senseNode;
    SynSet currentSynSet;
    Literal currentLiteral;
    XmlDocument doc = XmlDocument(move(fileName));
    doc.parse();
    rootNode = doc.getFirstChild();
    synSetNode = rootNode->getFirstChild();
    while (synSetNode != nullptr){
        partNode = synSetNode->getFirstChild();
        while (partNode != nullptr){
            if (partNode->getName() == "ID"){
                currentSynSet = SynSet(partNode->getPcData());
                addSynSet(currentSynSet);
                cout << currentSynSet.getId() << "\n";
            } else {
                if (partNode->getName() == "DEF"){
                    currentSynSet.setDefinition(partNode->getPcData());
                } else {
                    if (partNode->getName() == "EXAMPLE"){
                        currentSynSet.setExample(partNode->getPcData());
                    } else {
                        if (partNode->getName() == "BCS") {
                            currentSynSet.setBcs(std::stoi(partNode->getPcData()));
                        } else {
                            if (partNode->getName() == "POS") {
                                switch (partNode->getPcData()[0]) {
                                    case 'a':
                                        currentSynSet.setPos(Pos::ADJECTIVE);
                                        break;
                                    case 'v':
                                        currentSynSet.setPos(Pos::VERB);
                                        break;
                                    case 'b':
                                        currentSynSet.setPos(Pos::ADVERB);
                                        break;
                                    case 'n':
                                        currentSynSet.setPos(Pos::NOUN);
                                        break;
                                    case 'i':
                                        currentSynSet.setPos(Pos::INTERJECTION);
                                        break;
                                    case 'c':
                                        currentSynSet.setPos(Pos::CONJUNCTION);
                                        break;
                                    case 'p':
                                        currentSynSet.setPos(Pos::PREPOSITION);
                                        break;
                                    case 'r':
                                        currentSynSet.setPos(Pos::PRONOUN);
                                        break;
                                }
                            } else {
                                if (partNode->getName() == "SR") {
                                    srNode = partNode->getFirstChild();
                                    if (srNode != nullptr) {
                                        typeNode = srNode->getNextSibling();
                                        if (typeNode != nullptr && typeNode->getName() == "TYPE") {
                                            toNode = typeNode->getNextSibling();
                                            if (toNode != nullptr && typeNode->getName() == "TO") {
                                                currentSynSet.addRelation(new SemanticRelation(srNode->getPcData(), typeNode->getPcData(), stoi(toNode->getPcData())));
                                            } else {
                                                currentSynSet.addRelation(new SemanticRelation(srNode->getPcData(), typeNode->getPcData()));
                                            }
                                        }
                                    }
                                } else {
                                    if (partNode->getName() == "ILR") {
                                        ilrNode = partNode->getFirstChild();
                                        if (ilrNode != nullptr) {
                                            typeNode = ilrNode->getNextSibling();
                                            if (typeNode != nullptr && typeNode->getName() == "TYPE") {
                                                string interlingualId = ilrNode->getPcData();
                                                vector<SynSet> synSetList;
                                                if (interlingualList.find(interlingualId) != interlingualList.end()){
                                                    synSetList = interlingualList.find(interlingualId)->second;
                                                }
                                                synSetList.emplace_back(currentSynSet);
                                                interlingualList.insert_or_assign(interlingualId, synSetList);
                                                currentSynSet.addRelation(new InterlingualRelation(interlingualId, typeNode->getPcData()));
                                            }
                                        }
                                    } else {
                                        if (partNode->getName() == "SYNONYM") {
                                            literalNode = partNode->getFirstChild();
                                            while (literalNode != nullptr) {
                                                textNode = literalNode->getFirstChild();
                                                if (textNode != nullptr) {
                                                    if (literalNode->getName() == "LITERAL") {
                                                        senseNode = textNode->getNextSibling();
                                                        if (senseNode != nullptr) {
                                                            if (senseNode->getName() == "SENSE" && senseNode->getFirstChild() != nullptr) {
                                                                currentLiteral = Literal(textNode->getPcData(), stoi(senseNode->getPcData()), currentSynSet.getId());
                                                                currentSynSet.addLiteral(currentLiteral);
                                                                addLiteralToLiteralList(currentLiteral);
                                                                srNode = senseNode->getNextSibling();
                                                                while (srNode != nullptr) {
                                                                    if (srNode->getName() == "SR") {
                                                                        typeNode = srNode->getNextSibling();
                                                                        if (typeNode != nullptr && typeNode->getName() == "TYPE") {
                                                                            currentLiteral.addRelation(new SemanticRelation(srNode->getPcData(), typeNode->getPcData()));
                                                                        }
                                                                    }
                                                                    srNode = srNode->getNextSibling();
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                literalNode = literalNode->getNextSibling();
                                            }
                                        } else {
                                            if (partNode->getName() == "SNOTE") {
                                                currentSynSet.setNote(partNode->getPcData());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            partNode = partNode->getNextSibling();
        }
        synSetNode = synSetNode->getNextSibling();
    }
}

void WordNet::readExceptionFile(string exceptionFileName) {
    string wordName, rootForm;
    Pos pos;
    XmlElement* wordNode, *rootNode;
    XmlDocument doc = XmlDocument(move(exceptionFileName));
    doc.parse();
    rootNode = doc.getFirstChild();
    wordNode = rootNode->getFirstChild();
    while (wordNode != nullptr){
        if (wordNode->hasAttributes()){
            wordName = wordNode->getAttributeValue("name");
            rootForm = wordNode->getAttributeValue("root");
            if (wordNode->getAttributeValue("pos") == "Adj") {
                pos = Pos::ADJECTIVE;
            } else {
                if (wordNode->getAttributeValue("pos") == "Adv") {
                    pos = Pos::ADVERB;
                } else {
                    if (wordNode->getAttributeValue("pos") == "Noun") {
                        pos = Pos::NOUN;
                    } else {
                        if (wordNode->getAttributeValue("pos") == "Verb") {
                            pos = Pos::VERB;
                        } else {
                            pos = Pos::NOUN;
                        }
                    }
                }
            }
            exceptionList.emplace(wordName, ExceptionalWord(wordName, rootForm, pos));
        }
        wordNode = wordNode->getNextSibling();
    }
}

WordNet::WordNet() {
    readWordNet("turkish_wordnet.xml");
}

WordNet::WordNet(string fileName) {
    readWordNet(move(fileName));
    readExceptionFile("englisg_exception.xml");
}

WordNet::WordNet(string fileName, string exceptionFileName) {
    readWordNet(move(fileName));
    readExceptionFile(move(exceptionFileName));
}

void WordNet::addLiteralToLiteralList(Literal literal) {
    vector<Literal> literals;
    if (literalList.find(literal.getName()) != literalList.end()){
        literals = literalList.find(literal.getName())->second;
    }
    literals.emplace_back(literal);
    literalList.insert_or_assign(literal.getName(), literals);
}

void WordNet::mergeSynSets(string synSetFile) {
    ifstream inputFile;
    string line;
    inputFile.open(synSetFile, ifstream :: in);
    while (inputFile.good()) {
        getline(inputFile, line);
        vector<string> synSetIds = Word::split(line);
        SynSet* mergedOne = getSynSetWithId(synSetIds[0]);
        if (mergedOne != nullptr){
            for (int i = 1; i < synSetIds.size(); i++){
                SynSet* toBeMerged = getSynSetWithId(synSetIds[i]);
                if (mergedOne->getPos() == toBeMerged->getPos()){
                    mergedOne->mergeSynSet(*toBeMerged);
                    removeSynSet(*toBeMerged);
                }
            }
        }
    }
    inputFile.close();
}

vector<SynSet> WordNet::getSynSetList() {
    vector<SynSet> result;
    for (auto& iterator : synSetList){
        result.emplace_back(iterator.second);
    }
    return result;
}

vector<string> WordNet::getLiteralList() {
    vector<string> result;
    for (auto& iterator : literalList){
        result.emplace_back(iterator.first);
    }
    return result;
}

void WordNet::addSynSet(SynSet synSet) {
    synSetList.emplace(synSet.getId(), synSet);
}

void WordNet::removeSynSet(SynSet s) {
    synSetList.erase(s.getId());
}

SynSet* WordNet::getSynSetWithId(string synSetId) {
    if (synSetList.find(synSetId) != synSetList.end()){
        return &(synSetList.find(synSetId)->second);
    } else {
        return nullptr;
    }
}

SynSet* WordNet::getSynSetWithLiteral(string literal, int sense) {
    vector<Literal> literals;
    literals = literalList.find(literal)->second;
    for (Literal current : literals){
        if (current.getSense() == sense){
            return getSynSetWithId(current.getSynSetId());
        }
    }
    return nullptr;
}

int WordNet::numberOfSynSetsWithLiteral(string literal) {
    if (literalList.find(literal) != literalList.end()){
        return literalList.find(literal)->second.size();
    } else {
        return 0;
    }
}

vector<SynSet> WordNet::getSynSetsWithPartOfSpeech(Pos pos) {
    vector<SynSet> result;
    for (SynSet synSet : getSynSetList()){
        if (synSet.getPos() == pos){
            result.emplace_back(synSet);
        }
    }
    return result;
}

vector<Literal> WordNet::getLiteralsWithName(string literal) {
    if (literalList.find(literal) != literalList.end()){
        return literalList.find(literal)->second;
    } else {
        return vector<Literal>();
    }
}

void WordNet::addSynSetsWithLiteralToList(vector<SynSet> result, string literal, Pos pos) {
    SynSet* synSet;
    for (Literal current : literalList.find(literal)->second){
        synSet = getSynSetWithId(current.getSynSetId());
        if (synSet != nullptr && synSet->getPos() == pos){
            result.emplace_back(*synSet);
        }
    }
}

vector<SynSet> WordNet::getSynSetsWithLiteral(string literal) {
    SynSet* synSet;
    vector<SynSet> result;
    if (literalList.find(literal) != literalList.end()){
        for (Literal current : literalList.find(literal)->second){
            synSet = getSynSetWithId(current.getSynSetId());
            if (synSet != nullptr){
                result.emplace_back(*synSet);
            }
        }
    }
    return result;
}

vector<string> WordNet::getLiteralsWithPossibleModifiedLiteral(string literal) {
    vector<string> result;
    result.emplace_back(literal);
    if (exceptionList.find(literal) != exceptionList.end() && literalList.find(exceptionList.find(literal)->second.getRoot()) != literalList.end()){
        result.emplace_back(exceptionList.find(literal)->second.getRoot());
    }
    if (Word::endsWith(literal, "s") && literalList.find(literal.substr(0, literal.length() - 1)) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 1));
    }
    if (Word::endsWith(literal, "es") && literalList.find(literal.substr(0, literal.length() - 2)) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 2));
    }
    if (Word::endsWith(literal, "ed") && literalList.find(literal.substr(0, literal.length() - 2)) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 2));
    }
    if (Word::endsWith(literal, "ed") && literalList.find(literal.substr(0, literal.length() - 2) + literal[literal.length() - 3]) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 2) + literal[literal.length() - 3]);
    }
    if (Word::endsWith(literal, "ed") && literalList.find(literal.substr(0, literal.length() - 2) + "e") != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 2) + "e");
    }
    if (Word::endsWith(literal, "er") && literalList.find(literal.substr(0, literal.length() - 2)) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 2));
    }
    if (Word::endsWith(literal, "er") && literalList.find(literal.substr(0, literal.length() - 2) + "e") != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 2) + "e");
    }
    if (Word::endsWith(literal, "ing") && literalList.find(literal.substr(0, literal.length() - 3)) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 3));
    }
    if (Word::endsWith(literal, "ing") && literalList.find(literal.substr(0, literal.length() - 3) + literal[literal.length() - 4]) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 3) + literal[literal.length() - 4]);
    }
    if (Word::endsWith(literal, "ing") && literalList.find(literal.substr(0, literal.length() - 3) + "e") != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 3) + "e");
    }
    if (Word::endsWith(literal, "ies") && literalList.find(literal.substr(0, literal.length() - 3) + "y") != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 3) + "y");
    }
    if (Word::endsWith(literal, "est") && literalList.find(literal.substr(0, literal.length() - 3)) != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 3));
    }
    if (Word::endsWith(literal, "est") && literalList.find(literal.substr(0, literal.length() - 3) + "e") != literalList.end()){
        result.emplace_back(literal.substr(0, literal.length() - 3) + "e");
    }
    return result;
}

vector<SynSet> WordNet::getSynSetsWithPossiblyModifiedLiteral(string literal, Pos pos) {
    vector<SynSet> result;
    vector<string> modifiedLiterals = getLiteralsWithPossibleModifiedLiteral(move(literal));
    for (const string &modifiedLiteral : modifiedLiterals){
        if (literalList.find(modifiedLiteral) != literalList.end()){
            addSynSetsWithLiteralToList(result, modifiedLiteral, pos);
        }
    }
    return result;
}

void WordNet::addReverseRelation(SynSet synSet, SemanticRelation semanticRelation) {
    SynSet* otherSynSet = getSynSetWithId(semanticRelation.getName());
    if (otherSynSet != nullptr){
        Relation* otherRelation = new SemanticRelation(synSet.getId(), SemanticRelation::reverse(semanticRelation.getRelationType()));
        if (!otherSynSet->containsRelation(otherRelation)){
            otherSynSet->addRelation(otherRelation);
        }
    }
}

void WordNet::removeReverseRelation(SynSet synSet, SemanticRelation semanticRelation) {
    SynSet* otherSynSet = getSynSetWithId(semanticRelation.getName());
    if (otherSynSet != nullptr){
        Relation* otherRelation = new SemanticRelation(synSet.getId(), SemanticRelation::reverse(semanticRelation.getRelationType()));
        if (otherSynSet->containsRelation(otherRelation)){
            otherSynSet->removeRelation(otherRelation);
        }
    }
}

void WordNet::equalizeSemanticRelations() {
    for (SynSet synSet : getSynSetList()){
        for (int i = 0; i < synSet.relationSize(); i++){
            if (auto* relation = dynamic_cast<SemanticRelation*>(synSet.getRelation(i))){
                addReverseRelation(synSet, *relation);
            }
        }
    }
}

vector<Literal> WordNet::constructLiterals(string word, MorphologicalParse parse, MetamorphicParse metaParse,
                                           FsmMorphologicalAnalyzer fsm) {
    vector<Literal> result;
    if (parse.size() > 0){
        if (!parse.isPunctuation() && !parse.isCardinal() && !parse.isReal()){
            unordered_set<string> possibleWords = fsm.getPossibleWords(parse, move(metaParse));
            for (const string &possibleWord : possibleWords){
                vector<Literal> added = getLiteralsWithName(possibleWord);
                result.insert(result.end(), added.begin(), added.end());
            }
        } else {
            vector<Literal> added = getLiteralsWithName(word);
            result.insert(result.end(), added.begin(), added.end());
        }
    } else {
        vector<Literal> added = getLiteralsWithName(word);
        result.insert(result.end(), added.begin(), added.end());
    }
    return result;
}

vector<SynSet> WordNet::constructSynSets(string word, MorphologicalParse parse, MetamorphicParse metaParse,
                                         FsmMorphologicalAnalyzer fsm) {
    vector<SynSet> result;
    if (parse.size() > 0){
        if (parse.isProperNoun()){
            result.emplace_back(*getSynSetWithLiteral("(özel isim)", 1));
        }
        if (parse.isTime()){
            result.emplace_back(*getSynSetWithLiteral("(zaman)", 1));
        }
        if (parse.isDate()){
            result.emplace_back(*getSynSetWithLiteral("(tarih)", 1));
        }
        if (parse.isHashTag()){
            result.emplace_back(*getSynSetWithLiteral("(hashtag)", 1));
        }
        if (parse.isEmail()){
            result.emplace_back(*getSynSetWithLiteral("(eposta)", 1));
        }
        if (parse.isOrdinal()){
            result.emplace_back(*getSynSetWithLiteral("(sayı sıra sıfatı)", 1));
        }
        if (parse.isPercent()){
            result.emplace_back(*getSynSetWithLiteral("(yüzde)", 1));
        }
        if (parse.isFraction()){
            result.emplace_back(*getSynSetWithLiteral("(kesir sayı)", 1));
        }
        if (parse.isRange()){
            result.emplace_back(*getSynSetWithLiteral("(sayı aralığı)", 1));
        }
        if (parse.isReal()){
            result.emplace_back(*getSynSetWithLiteral("(reel sayı)", 1));
        }
        if (!parse.isPunctuation() && !parse.isCardinal() && !parse.isReal()){
            unordered_set<string> possibleWords = fsm.getPossibleWords(parse, metaParse);
            for (const string &possibleWord : possibleWords){
                vector<SynSet> synSets = getSynSetsWithLiteral(possibleWord);
                if (!synSets.empty()){
                    for (SynSet synSet : synSets){
                        if (parse.getPos() == "NOUN" || parse.getPos() == "ADVERB" || parse.getPos() == "VERB" || parse.getPos() == "ADJ" || parse.getPos() == "CONJ"){
                            if (synSet.getPos() == Pos::NOUN){
                                if (parse.getPos() == "NOUN" || parse.getRootPos() == "NOUN"){
                                    result.emplace_back(synSet);
                                }
                            } else {
                                if (synSet.getPos() == Pos::ADVERB){
                                    if (parse.getPos() == "ADVERB" || parse.getRootPos() == "ADVERB"){
                                        result.emplace_back(synSet);
                                    }
                                } else {
                                    if (synSet.getPos() == Pos::VERB){
                                        if (parse.getPos() == "VERB" || parse.getRootPos() == "VERB"){
                                            result.emplace_back(synSet);
                                        }
                                    } else {
                                        if (synSet.getPos() == Pos::ADJECTIVE){
                                            if (parse.getPos() == "ADJ" || parse.getRootPos() == "ADJ"){
                                                result.emplace_back(synSet);
                                            }
                                        } else {
                                            if (synSet.getPos() == Pos::CONJUNCTION){
                                                if (parse.getPos() == "CONJ" || parse.getRootPos() == "CONJ"){
                                                    result.emplace_back(synSet);
                                                }
                                            } else {
                                                result.emplace_back(synSet);
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            result.emplace_back(synSet);
                        }
                    }
                }
            }
            if (result.empty()){
                for (const string &possibleWord : possibleWords){
                    vector<SynSet> synSets = getSynSetsWithLiteral(possibleWord);
                    result.insert(result.end(), synSets.begin(), synSets.end());
                }
            }
        } else {
            vector<SynSet> synSets = getSynSetsWithLiteral(word);
            result.insert(result.end(), synSets.begin(), synSets.end());
        }
        if (parse.isCardinal() && result.empty()){
            result.emplace_back(*getSynSetWithLiteral("(tam sayı)", 1));
        }
    } else {
        vector<SynSet> synSets = getSynSetsWithLiteral(word);
        result.insert(result.end(), synSets.begin(), synSets.end());
    }
    return result;
}

vector<Literal>
WordNet::constructIdiomLiterals(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2,
                                MorphologicalParse morphologicalParse3, MetamorphicParse metaParse1,
                                MetamorphicParse metaParse2, MetamorphicParse metaParse3,
                                FsmMorphologicalAnalyzer fsm) {
    vector<Literal> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(move(morphologicalParse1), move(metaParse1));
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(move(morphologicalParse2), move(metaParse2));
    unordered_set<string> possibleWords3 = fsm.getPossibleWords(move(morphologicalParse3), move(metaParse3));
    for (const string &possibleWord1 : possibleWords1){
        for (const string &possibleWord2 : possibleWords2){
            for (const string &possibleWord3 : possibleWords3) {
                string idiom;
                idiom.append(possibleWord1).append(" ").append(possibleWord2).append(" ").append(possibleWord3);
                vector<Literal> literals = getLiteralsWithName(idiom);
                result.insert(result.end(), literals.begin(), literals.end());
            }
        }
    }
    return result;
}

vector<SynSet>
WordNet::constructIdiomSynSets(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2,
                               MorphologicalParse morphologicalParse3, MetamorphicParse metaParse1,
                               MetamorphicParse metaParse2, MetamorphicParse metaParse3, FsmMorphologicalAnalyzer fsm) {
    vector<SynSet> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(move(morphologicalParse1), move(metaParse1));
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(move(morphologicalParse2), move(metaParse2));
    unordered_set<string> possibleWords3 = fsm.getPossibleWords(move(morphologicalParse3), move(metaParse3));
    for (const string &possibleWord1 : possibleWords1){
        for (const string &possibleWord2 : possibleWords2){
            for (const string &possibleWord3 : possibleWords3) {
                string idiom;
                idiom.append(possibleWord1).append(" ").append(possibleWord2).append(" ").append(possibleWord3);
                if (numberOfSynSetsWithLiteral(idiom) > 0) {
                    vector<SynSet> synSets = getSynSetsWithLiteral(idiom);
                    result.insert(result.end(), synSets.begin(), synSets.end());
                }
            }
        }
    }
    return result;
}

vector<Literal>
WordNet::constructIdiomLiterals(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2,
                                MetamorphicParse metaParse1, MetamorphicParse metaParse2,
                                FsmMorphologicalAnalyzer fsm) {
    vector<Literal> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(move(morphologicalParse1), move(metaParse1));
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(move(morphologicalParse2), move(metaParse2));
    for (const string &possibleWord1 : possibleWords1){
        for (const string &possibleWord2 : possibleWords2){
            string idiom;
            idiom.append(possibleWord1).append(" ").append(possibleWord2);
            vector<Literal> literals = getLiteralsWithName(idiom);
            result.insert(result.end(), literals.begin(), literals.end());
        }
    }
    return result;
}

vector<SynSet>
WordNet::constructIdiomSynSets(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2,
                               MetamorphicParse metaParse1, MetamorphicParse metaParse2, FsmMorphologicalAnalyzer fsm) {
    vector<SynSet> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(move(morphologicalParse1), move(metaParse1));
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(move(morphologicalParse2), move(metaParse2));
    for (const string &possibleWord1 : possibleWords1){
        for (const string &possibleWord2 : possibleWords2){
            string idiom;
            idiom.append(possibleWord1).append(" ").append(possibleWord2);
            if (numberOfSynSetsWithLiteral(idiom) > 0) {
                vector<SynSet> synSets = getSynSetsWithLiteral(idiom);
                result.insert(result.end(), synSets.begin(), synSets.end());
            }
        }
    }
    return result;
}

void WordNet::sortDefinitions() {
    for (SynSet synSet: getSynSetList()){
        synSet.sortDefinitions();
    }
}

vector<SynSet> WordNet::getInterlingual(string synSetId) {
    if (interlingualList.find(synSetId) != interlingualList.end()){
        return interlingualList.find(synSetId)->second;
    } else {
        return vector<SynSet>();
    }
}

void WordNet::multipleInterlingualRelationCheck1(WordNet secondWordNet) {
    for (SynSet synSet : getSynSetList()){
        vector<string> interlingual = synSet.getInterlingual();
        if (interlingual.size() > 1){
            for (const string &s : interlingual){
                SynSet* second = secondWordNet.getSynSetWithId(s);
                if (second != nullptr){
                    cout << synSet.getId() << "\t" << synSet.getSynonym().to_string() << "\t" << synSet.getDefinition() << "\t" << second->getId() << "\t" << second->getSynonym().to_string() << "\t" << second->getDefinition();
                }
            }
        }
    }
}

void WordNet::multipleInterlingualRelationCheck2(WordNet secondWordNet) {
    for (auto& iterator : interlingualList){
        string s = iterator.first;
        if (interlingualList.find(s)->second.size() > 1){
            SynSet* second = secondWordNet.getSynSetWithId(s);
            if (second != nullptr){
                for (SynSet synSet : interlingualList.find(s)->second){
                    cout << synSet.getId() << "\t" << synSet.getSynonym().to_string() << "\t" << synSet.getDefinition() << "\t" << second->getId() << "\t" << second->getSynonym().to_string() << "\t" << second->getDefinition();
                }
            }
        }
    }
}

void WordNet::sameLiteralSameSenseCheck() {
    for (auto& iterator : literalList){
        string name = iterator.first;
        vector<Literal> literals = literalList.find(name)->second;
        for (int i = 0; i < literals.size(); i++){
            for (int j = i + 1; j < literals.size(); j++){
                if (literals.at(i).getSense() == literals.at(j).getSense() && literals.at(i).getName() == literals.at(j).getName()){
                    cout << "Literal " << name << " has same senses.";
                }
            }
        }
    }
}

struct synSetSizeComparator{
    bool operator() (SynSet synSetA, SynSet synSetB){
        return synSetA.getSynonym().literalSize() < synSetB.getSynonym().literalSize();
    }
};

void WordNet::sameLiteralSameSynSetCheck() {
    vector<SynSet> synsets;
    for (SynSet synSet : getSynSetList()){
        bool found = false;
        for (int i = 0; i < synSet.getSynonym().literalSize(); i++){
            Literal literal1 = synSet.getSynonym().getLiteral(i);
            for (int j = i + 1; j < synSet.getSynonym().literalSize(); j++){
                Literal literal2 = synSet.getSynonym().getLiteral(j);
                if (literal1.getName() == literal2.getName()){
                    synsets.emplace_back(synSet);
                    found = true;
                    break;
                }
            }
            if (found){
                break;
            }
        }
    }
    stable_sort(synsets.begin(), synsets.end(), synSetSizeComparator());
    for (SynSet synSet : synsets){
        cout << synSet.getDefinition();
    }
}

void WordNet::noDefinitionCheck() {
    for (SynSet synSet : getSynSetList()){
        if (synSet.getDefinition().empty()){
            cout << "SynSet " << synSet.getId() << " has no definition " << synSet.getSynonym().to_string();
        }
    }
}

void WordNet::semanticRelationNoIDCheck() {
    for (SynSet synSet : getSynSetList()){
        for (int i = 0; i < synSet.getSynonym().literalSize(); i++){
            Literal literal = synSet.getSynonym().getLiteral(i);
            for (int j = 0; j < literal.relationSize(); j++){
                Relation* relation = literal.getRelation(j);
                if (getSynSetWithId(relation->getName()) == nullptr){
                    literal.removeRelation(relation);
                    j--;
                    cout << "Relation " << relation->getName() << " of Synset " << synSet.getId() << " does not exists " << synSet.getSynonym().to_string();
                }
            }
        }
        for (int j = 0; j < synSet.relationSize(); j++){
            Relation* relation = synSet.getRelation(j);
            if (auto* semanticRelation = dynamic_cast<SemanticRelation*>(relation)){
                if (getSynSetWithId(relation->getName()) == nullptr){
                    synSet.removeRelation(relation);
                    j--;
                    cout << "Relation " << relation->getName() << " of Synset " << synSet.getId() << " does not exists " << synSet.getSynonym().to_string();
                }
            }
        }
    }
}

void WordNet::sameSemanticRelationCheck() {
    for (SynSet synSet : getSynSetList()){
        for (int i = 0; i < synSet.getSynonym().literalSize(); i++){
            Literal literal = synSet.getSynonym().getLiteral(i);
            for (int j = 0; j < literal.relationSize(); j++){
                Relation* relation = literal.getRelation(j);
                Relation* same = nullptr;
                for (int k = j + 1; k < literal.relationSize(); k++){
                    if (relation->getName() == literal.getRelation(k)->getName()){
                        cout << relation->getName() << "--" << literal.getRelation(k)->getName() << " are same relation for synset " << synSet.getId();
                        same = literal.getRelation(k);
                    }
                }
                if (same != nullptr){
                    literal.removeRelation(same);
                }
            }
        }
        for (int j = 0; j < synSet.relationSize(); j++){
            Relation* relation = synSet.getRelation(j);
            Relation* same = nullptr;
            for (int k = j + 1; k < synSet.relationSize(); k++){
                if (relation->getName() == synSet.getRelation(k)->getName()){
                    cout << relation->getName() << "--" << synSet.getRelation(k)->getName() << " are same relation for synset " << synSet.getId();
                    same = synSet.getRelation(k);
                }
            }
            if (same != nullptr){
                synSet.removeRelation(same);
            }
        }
    }
}

void WordNet::check(WordNet secondWordNet) {
    //multipleInterlingualRelationCheck1(secondWordNet);
    sameLiteralSameSynSetCheck();
    sameLiteralSameSenseCheck();
    semanticRelationNoIDCheck();
    sameSemanticRelationCheck();
    noDefinitionCheck();
    //multipleInterlingualRelationCheck2(secondWordNet);
}

void WordNet::saveAsXml(string fileName) {
    ofstream outFile;
    outFile.open(fileName, ofstream::out);
    outFile << "<SYNSETS>\n";
    for (SynSet synSet : getSynSetList()){
        synSet.saveAsXml(outFile);
    }
    outFile << "</SYNSETS>\n";
    outFile.close();
}

int WordNet::size() {
    return synSetList.size();
}

int WordNet::findPathLength(vector<string> pathToRootOfSynSet1, vector<string> pathToRootOfSynSet2) {
    // There might not be a path between nodes, due to missing nodes. Keep track of that as well. Break when the LCS if found.
    for (int i = 0; i < pathToRootOfSynSet1.size(); i++) {
        auto foundIndex = find(pathToRootOfSynSet2.begin(), pathToRootOfSynSet2.end(), pathToRootOfSynSet1.at(i));
        if (foundIndex != pathToRootOfSynSet2.cend()) {
            // Index of two lists - 1 is equal to path length. If there is not path, return -1
            return i + foundIndex - pathToRootOfSynSet2.begin() - 1;
        }
    }
    return -1;
}

int WordNet::findLCSdepth(vector<string> pathToRootOfSynSet1, vector<string> pathToRootOfSynSet2){
    pair<string, int> temp = findLCS(move(pathToRootOfSynSet1), move(pathToRootOfSynSet2));
    if (!temp.first.empty()) {
        return temp.second;
    }
    return -1;
}

string WordNet::findLCSid(vector<string> pathToRootOfSynSet1, vector<string> pathToRootOfSynSet2){
    pair<string, int> temp = findLCS(move(pathToRootOfSynSet1), move(pathToRootOfSynSet2));
    return temp.first;
}

pair<string, int> WordNet::findLCS(vector<string> pathToRootOfSynSet1, vector<string> pathToRootOfSynSet2){
    for (int i = 0; i < pathToRootOfSynSet1.size(); i++) {
        string LCSid = pathToRootOfSynSet1.at(i);
        if (find(pathToRootOfSynSet2.begin(), pathToRootOfSynSet2.end(), LCSid) != pathToRootOfSynSet2.cend()) {
            return pair(LCSid, pathToRootOfSynSet1.size() - i + 1);
        }
    }
    return pair("", -1);
}

vector<string> WordNet::findPathToRoot(SynSet* synSet){
    vector<string> pathToRoot;
    while (synSet != nullptr) {
        pathToRoot.emplace_back(synSet->getId());
        synSet = percolateUp(synSet);
    }
    return pathToRoot;
}

SynSet* WordNet::percolateUp(SynSet* root){
    for (int i = 0; i < root->relationSize(); i++) {
        Relation* r = root->getRelation(i);
        if (auto* relation = dynamic_cast<SemanticRelation*>(r)) {
            if (relation->getRelationType() == SemanticRelationType::HYPERNYM) {
                root = getSynSetWithId(r->getName());
                // return even if one hypernym is found.
                return root;
            }
        }
    }
    return nullptr;
}