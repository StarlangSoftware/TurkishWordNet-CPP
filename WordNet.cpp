//
// Created by olcay on 29.03.2019.
//

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
                currentSynSet = SynSet(partNode->getFirstChild()->getPcData());
                addSynSet(currentSynSet);
            } else {
                if (partNode->getName() == "DEF"){
                    currentSynSet.setDefinition(partNode->getFirstChild()->getPcData());
                } else {
                    if (partNode->getName() == "EXAMPLE"){
                        currentSynSet.setExample(partNode->getFirstChild()->getPcData());
                    } else {
                        if (partNode->getName() == "BCS") {
                            currentSynSet.setBcs(std::stoi(partNode->getFirstChild()->getPcData()));
                        } else {
                            if (partNode->getName() == "POS") {
                                switch (partNode->getFirstChild()->getPcData()[0]) {
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
                                                currentSynSet.addRelation(new SemanticRelation(srNode->getPcData(), typeNode->getFirstChild()->getPcData(), stoi(toNode->getFirstChild()->getPcData())));
                                            } else {
                                                currentSynSet.addRelation(new SemanticRelation(srNode->getPcData(), typeNode->getFirstChild()->getPcData()));
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
                                                currentSynSet.addRelation(new InterlingualRelation(interlingualId, typeNode->getFirstChild()->getPcData()));
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
                                                                currentLiteral = Literal(textNode->getPcData(), stoi(senseNode->getFirstChild()->getPcData()), currentSynSet.getId());
                                                                currentSynSet.addLiteral(currentLiteral);
                                                                addLiteralToLiteralList(currentLiteral);
                                                                srNode = senseNode->getNextSibling();
                                                                while (srNode != nullptr) {
                                                                    if (srNode->getName() == "SR") {
                                                                        typeNode = srNode->getFirstChild()->getNextSibling();
                                                                        if (typeNode != nullptr && typeNode->getName() == "TYPE") {
                                                                            currentLiteral.addRelation(new SemanticRelation(srNode->getFirstChild()->getPcData(), typeNode->getFirstChild()->getPcData()));
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
                                                currentSynSet.setNote(partNode->getFirstChild()->getPcData());
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
        SynSet mergedOne = getSynSetWithId(synSetIds[0]);
        for (int i = 1; i < synSetIds.size(); i++){
            SynSet toBeMerged = getSynSetWithId(synSetIds[i]);
            if (mergedOne.getPos() == toBeMerged.getPos()){
                mergedOne.mergeSynSet(toBeMerged);
                removeSynSet(toBeMerged);
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

SynSet WordNet::getSynSetWithId(string synSetId) {
    return synSetList.find(synSetId)->second;
}

SynSet WordNet::getSynSetWithLiteral(string literal, int sense) {
    vector<Literal> literals;
    literals = literalList.find(literal)->second;
    for (Literal current : literals){
        if (current.getSense() == sense){
            return getSynSetWithId(current.getSynSetId());
        }
    }
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
    SynSet synSet;
    for (Literal current : literalList.find(literal)->second){
        synSet = getSynSetWithId(current.getSynSetId());
        if (synSet.getPos() == pos){
            result.emplace_back(synSet);
        }
    }
}

vector<SynSet> WordNet::getSynSetsWithLiteral(string literal) {
    SynSet synSet;
    vector<SynSet> result;
    if (literalList.find(literal) != literalList.end()){
        for (Literal current : literalList.find(literal)->second){
            synSet = getSynSetWithId(current.getSynSetId());
            result.emplace_back(synSet);
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
    SynSet otherSynSet = getSynSetWithId(semanticRelation.getName());
    Relation* otherRelation = new SemanticRelation(synSet.getId(), SemanticRelation::reverse(semanticRelation.getRelationType()));
    if (!otherSynSet.containsRelation(otherRelation)){
        otherSynSet.addRelation(otherRelation);
    }
}

void WordNet::removeReverseRelation(SynSet synSet, SemanticRelation semanticRelation) {
    SynSet otherSynSet = getSynSetWithId(semanticRelation.getName());
    Relation* otherRelation = new SemanticRelation(synSet.getId(), SemanticRelation::reverse(semanticRelation.getRelationType()));
    if (otherSynSet.containsRelation(otherRelation)){
        otherSynSet.removeRelation(otherRelation);
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
            result.emplace_back(getSynSetWithLiteral("(özel isim)", 1));
        }
        if (parse.isTime()){
            result.emplace_back(getSynSetWithLiteral("(zaman)", 1));
        }
        if (parse.isDate()){
            result.emplace_back(getSynSetWithLiteral("(tarih)", 1));
        }
        if (parse.isHashTag()){
            result.emplace_back(getSynSetWithLiteral("(hashtag)", 1));
        }
        if (parse.isEmail()){
            result.emplace_back(getSynSetWithLiteral("(eposta)", 1));
        }
        if (parse.isOrdinal()){
            result.emplace_back(getSynSetWithLiteral("(sayı sıra sıfatı)", 1));
        }
        if (parse.isPercent()){
            result.emplace_back(getSynSetWithLiteral("(yüzde)", 1));
        }
        if (parse.isFraction()){
            result.emplace_back(getSynSetWithLiteral("(kesir sayı)", 1));
        }
        if (parse.isRange()){
            result.emplace_back(getSynSetWithLiteral("(sayı aralığı)", 1));
        }
        if (parse.isReal()){
            result.emplace_back(getSynSetWithLiteral("(reel sayı)", 1));
        }
        if (!parse.isPunctuation() && !parse.isCardinal() && !parse.isReal()){
            unordered_set<string> possibleWords = fsm.getPossibleWords(parse, metaParse);
            for (string possibleWord : possibleWords){
                vector<SynSet> synSets = getSynSetsWithLiteral(possibleWord);
                if (synSets.size() > 0){
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
            if (result.size() == 0){
                for (string possibleWord : possibleWords){
                    vector<SynSet> synSets = getSynSetsWithLiteral(possibleWord);
                    result.insert(result.end(), synSets.begin(), synSets.end());
                }
            }
        } else {
            vector<SynSet> synSets = getSynSetsWithLiteral(word);
            result.insert(result.end(), synSets.begin(), synSets.end());
        }
        if (parse.isCardinal() && result.size() == 0){
            result.emplace_back(getSynSetWithLiteral("(tam sayı)", 1));
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
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
    unordered_set<string> possibleWords3 = fsm.getPossibleWords(morphologicalParse3, metaParse3);
    for (string possibleWord1 : possibleWords1){
        for (string possibleWord2 : possibleWords2){
            for (string possibleWord3 : possibleWords3) {
                vector<Literal> literals = getLiteralsWithName(possibleWord1 + " " + possibleWord2 + " " + possibleWord3);
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
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
    unordered_set<string> possibleWords3 = fsm.getPossibleWords(morphologicalParse3, metaParse3);
    for (string possibleWord1 : possibleWords1){
        for (string possibleWord2 : possibleWords2){
            for (string possibleWord3 : possibleWords3) {
                if (numberOfSynSetsWithLiteral(possibleWord1 + " " + possibleWord2 + " " + possibleWord3) > 0) {
                    vector<SynSet> synSets = getSynSetsWithLiteral(possibleWord1 + " " + possibleWord2 + " " + possibleWord3);
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
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
    for (string possibleWord1 : possibleWords1){
        for (string possibleWord2 : possibleWords2){
            vector<Literal> literals = getLiteralsWithName(possibleWord1 + " " + possibleWord2);
            result.insert(result.end(), literals.begin(), literals.end());
        }
    }
    return result;
}

vector<SynSet>
WordNet::constructIdiomSynSets(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2,
                               MetamorphicParse metaParse1, MetamorphicParse metaParse2, FsmMorphologicalAnalyzer fsm) {
    vector<SynSet> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
    for (string possibleWord1 : possibleWords1){
        for (string possibleWord2 : possibleWords2){
            if (numberOfSynSetsWithLiteral(possibleWord1 + " " + possibleWord2) > 0) {
                vector<SynSet> synSets = getSynSetsWithLiteral(possibleWord1 + " " + possibleWord2);
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
