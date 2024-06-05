//
// Created by olcay on 29.03.2019.
//

#include <iostream>
#include <utility>
#include "WordNet.h"
#include "XmlDocument.h"
#include "SemanticRelation.h"
#include "InterlingualRelation.h"

/**
 * Reads a wordnet from a Xml file. A wordnet consists of a list of synsets encapsulated inside SYNSET tag. A synset
 * has an id (represented with ID tag), a set of literals encapsulated inside SYNONYM tag, part of speech tag
 * (represented with POS tag), a set of semantic relations encapsulated inside SR tag, a definition (represented
 * with DEF tag), and a possible example (represented with EXAMPLE tag). Each literal has a name, possibly a group
 * number (represented with GROUP tag), a sense number (represented with SENSE tag) and a set of semantic relations
 * encapsulated inside SR tag. A semantic relation has a name and a type (represented with TYPE tag).
 * @param inputStream File stream that contains the wordnet.
 */
void WordNet::readWordNet(const string& fileName) {
    XmlElement *rootNode, *synSetNode, *partNode, *srNode, *typeNode, *toNode, *literalNode, *senseNode;
    map<string, SynSet>::iterator currentSynSet;
    Literal currentLiteral;
    XmlDocument doc = XmlDocument(fileName);
    doc.parse();
    rootNode = doc.getFirstChild();
    synSetNode = rootNode->getFirstChild();
    while (synSetNode != nullptr){
        partNode = synSetNode->getFirstChild();
        while (partNode != nullptr){
            if (partNode->getName() == "ID"){
                currentSynSet = addSynSet(SynSet(partNode->getPcData()));
            } else {
                if (partNode->getName() == "DEF"){
                    currentSynSet->second.setDefinition(partNode->getPcData());
                } else {
                    if (partNode->getName() == "EXAMPLE"){
                        currentSynSet->second.setExample(partNode->getPcData());
                    } else {
                        if (partNode->getName() == "BCS") {
                            currentSynSet->second.setBcs(std::stoi(partNode->getPcData()));
                        } else {
                            if (partNode->getName() == "POS") {
                                switch (partNode->getPcData()[0]) {
                                    case 'a':
                                        currentSynSet->second.setPos(Pos::ADJECTIVE);
                                        break;
                                    case 'v':
                                        currentSynSet->second.setPos(Pos::VERB);
                                        break;
                                    case 'b':
                                        currentSynSet->second.setPos(Pos::ADVERB);
                                        break;
                                    case 'n':
                                        currentSynSet->second.setPos(Pos::NOUN);
                                        break;
                                    case 'i':
                                        currentSynSet->second.setPos(Pos::INTERJECTION);
                                        break;
                                    case 'c':
                                        currentSynSet->second.setPos(Pos::CONJUNCTION);
                                        break;
                                    case 'p':
                                        currentSynSet->second.setPos(Pos::PREPOSITION);
                                        break;
                                    case 'r':
                                        currentSynSet->second.setPos(Pos::PRONOUN);
                                        break;
                                }
                            } else {
                                if (partNode->getName() == "SR") {
                                    typeNode = partNode->getFirstChild();
                                    if (typeNode != nullptr && typeNode->getName() == "TYPE") {
                                        toNode = typeNode->getNextSibling();
                                        if (toNode != nullptr && toNode->getName() == "TO") {
                                            currentSynSet->second.addRelation(new SemanticRelation(partNode->getPcData(), typeNode->getPcData(), stoi(toNode->getPcData())));
                                        } else {
                                            currentSynSet->second.addRelation(new SemanticRelation(partNode->getPcData(), typeNode->getPcData()));
                                        }
                                    }
                                } else {
                                    if (partNode->getName() == "ILR") {
                                        typeNode = partNode->getFirstChild();
                                        if (typeNode != nullptr && typeNode->getName() == "TYPE") {
                                            string interlingualId = partNode->getPcData();
                                            vector<SynSet> _synSetList;
                                            if (interlingualList.contains(interlingualId)){
                                                _synSetList = interlingualList.find(interlingualId)->second;
                                            }
                                            _synSetList.emplace_back(currentSynSet->second);
                                            interlingualList.insert_or_assign(interlingualId, _synSetList);
                                            currentSynSet->second.addRelation(new InterlingualRelation(interlingualId, typeNode->getPcData()));
                                        }
                                    } else {
                                        if (partNode->getName() == "SYNONYM") {
                                            literalNode = partNode->getFirstChild();
                                            while (literalNode != nullptr) {
                                                if (literalNode->getName() == "LITERAL") {
                                                    senseNode = literalNode->getFirstChild();
                                                    if (senseNode != nullptr) {
                                                        if (senseNode->getName() == "SENSE" && !senseNode->getPcData().empty()) {
                                                            currentLiteral = Literal(literalNode->getPcData(), stoi(senseNode->getPcData()), currentSynSet->second.getId());
                                                            srNode = senseNode->getNextSibling();
                                                            while (srNode != nullptr) {
                                                                if (srNode->getName() == "ORIGIN"){
                                                                    currentLiteral.setOrigin(srNode->getPcData());
                                                                } else {
                                                                    if (srNode->getName() == "GROUP"){
                                                                        currentLiteral.setGroupNo(stoi(srNode->getPcData()));
                                                                    } else {
                                                                        if (srNode->getName() == "SR") {
                                                                            typeNode = srNode->getFirstChild();
                                                                            if (typeNode != nullptr && typeNode->getName() == "TYPE") {
                                                                                toNode = typeNode->getNextSibling();
                                                                                if (toNode != nullptr && toNode->getName() == "TO") {
                                                                                    currentLiteral.addRelation(new SemanticRelation(srNode->getPcData(), typeNode->getPcData(), stoi(toNode->getPcData())));
                                                                                } else {
                                                                                    currentLiteral.addRelation(new SemanticRelation(srNode->getPcData(), typeNode->getPcData()));
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                srNode = srNode->getNextSibling();
                                                            }
                                                            currentSynSet->second.addLiteral(currentLiteral);
                                                            addLiteralToLiteralList(currentLiteral);
                                                        }
                                                    }
                                                }
                                                literalNode = literalNode->getNextSibling();
                                            }
                                        } else {
                                            if (partNode->getName() == "SNOTE") {
                                                currentSynSet->second.setNote(partNode->getPcData());
                                            } else {
                                                if (partNode->getName() == "WIKI"){
                                                    currentSynSet->second.setWikiPage(partNode->getPcData());
                                                }
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

/**
 * Method constructs a DOM parser using the dtd/xml schema parser configuration and using this parser it
 * reads exceptions from file and puts to exceptionList HashMap.
 *
 * @param exceptionFileName exception file to be read
 */
void WordNet::readExceptionFile(const string& exceptionFileName) {
    string wordName, rootForm;
    Pos pos;
    XmlElement* wordNode, *rootNode;
    XmlDocument doc = XmlDocument(exceptionFileName);
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

/**
 * A constructor that initializes the SynSet list, literal list and schedules the {@code SwingWorker} for execution
 * on a <i>worker</i> thread.
 */
WordNet::WordNet() {
    readWordNet("turkish_wordnet.xml");
}

/**
 * Another constructor that initializes the SynSet list, literal list, reads exception,
 * and schedules the {@code SwingWorker} according to file with a specified name for execution on a <i>worker</i> thread.
 *
 * @param fileName resource to be read for the WordNet task
 */
WordNet::WordNet(const string& fileName) {
    readExceptionFile("english_exception.xml");
    readWordNet(fileName);
}

/**
 * Another constructor that initializes the SynSet list, literal list, reads exception file with a specified name,
 * sets the Locale of the programme with the specified locale, and schedules the {@code SwingWorker} according
 * to file with a specified name for execution on a <i>worker</i> thread.
 *
 * @param fileName          resource to be read for the WordNet task
 * @param exceptionFileName exception file to be read
 */
WordNet::WordNet(const string& fileName, const string& exceptionFileName) {
    readWordNet(fileName);
    readExceptionFile(exceptionFileName);
}

/**
 * Adds a specified literal to the literal list.
 *
 * @param literal literal to be added
 */
void WordNet::addLiteralToLiteralList(const Literal& literal) {
    vector<Literal> literals;
    if (literalList.contains(literal.getName())){
        literals = literalList.find(literal.getName())->second;
    }
    literals.emplace_back(literal);
    literalList.insert_or_assign(literal.getName(), literals);
}

/**
 * Method reads the specified SynSet file, gets the SynSets according to IDs in the file, and merges SynSets.
 *
 * @param synSetFile SynSet file to be read and merged
 */
void WordNet::mergeSynSets(const string& synSetFile) {
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

/**
 * Returns the values of the SynSet list.
 *
 * @return values of the SynSet list
 */
vector<SynSet> WordNet::getSynSetList() const{
    vector<SynSet> result;
    for (auto& iterator : synSetList){
        result.emplace_back(iterator.second);
    }
    return result;
}

/**
 * Returns the keys of the literal list.
 *
 * @return keys of the literal list
 */
vector<string> WordNet::getLiteralList() const{
    vector<string> result;
    for (auto& iterator : literalList){
        result.emplace_back(iterator.first);
    }
    return result;
}

/**
 * Adds specified SynSet to the SynSet list.
 *
 * @param synSet SynSet to be added
 */
map<string, SynSet>::iterator WordNet::addSynSet(const SynSet& synSet) {
    return synSetList.emplace(synSet.getId(), synSet).first;
}

/**
 * Removes specified SynSet from the SynSet list.
 *
 * @param synSet SynSet to be added
 */
void WordNet::removeSynSet(const SynSet& s) {
    synSetList.erase(s.getId());
}

/**
 * Returns SynSet with the specified SynSet ID.
 *
 * @param synSetId ID of the SynSet to be returned
 * @return SynSet with the specified SynSet ID
 */
SynSet* WordNet::getSynSetWithId(const string& synSetId){
    if (synSetList.contains(synSetId)){
        return &(synSetList.find(synSetId)->second);
    } else {
        return nullptr;
    }
}

/**
 * Returns SynSet with the specified literal and sense index.
 *
 * @param literal SynSet literal
 * @param sense   SynSet's corresponding sense index
 * @return SynSet with the specified literal and sense index
 */
SynSet* WordNet::getSynSetWithLiteral(const string& literal, int sense){
    vector<Literal> literals;
    literals = literalList.find(literal)->second;
    for (const Literal& current : literals){
        if (current.getSense() == sense){
            return getSynSetWithId(current.getSynSetId());
        }
    }
    return nullptr;
}

/**
 * Returns the number of SynSets with a specified literal.
 *
 * @param literal literal to be searched in SynSets
 * @return the number of SynSets with a specified literal
 */
int WordNet::numberOfSynSetsWithLiteral(const string& literal) const{
    if (literalList.contains(literal)){
        return literalList.find(literal)->second.size();
    } else {
        return 0;
    }
}

/**
 * Returns a list of SynSets with a specified part of speech tag.
 *
 * @param pos part of speech tag to be searched in SynSets
 * @return a list of SynSets with a specified part of speech tag
 */
vector<SynSet> WordNet::getSynSetsWithPartOfSpeech(Pos pos) const{
    vector<SynSet> result;
    for (const SynSet& synSet : getSynSetList()){
        if (synSet.getPos() == pos){
            result.emplace_back(synSet);
        }
    }
    return result;
}

/**
 * Returns a list of literals with a specified literal String.
 *
 * @param literal literal String to be searched in literal list
 * @return a list of literals with a specified literal String
 */
vector<Literal> WordNet::getLiteralsWithName(const string& literal) const{
    if (literalList.contains(literal)){
        return literalList.find(literal)->second;
    } else {
        return vector<Literal>();
    }
}

/**
 * Finds the SynSet with specified literal String and part of speech tag and adds to the given SynSet list.
 *
 * @param result  SynSet list to add the specified SynSet
 * @param literal literal String to be searched in literal list
 * @param pos     part of speech tag to be searched in SynSets
 */
void WordNet::addSynSetsWithLiteralToList(vector<SynSet>& result, const string& literal, Pos pos) {
    SynSet* synSet;
    for (const Literal& current : literalList.find(literal)->second){
        synSet = getSynSetWithId(current.getSynSetId());
        if (synSet != nullptr && synSet->getPos() == pos){
            result.push_back(*synSet);
        }
    }
}

/**
 * Finds SynSets with specified literal String and adds to the newly created SynSet list.
 *
 * @param literal literal String to be searched in literal list
 * @return returns a list of SynSets with specified literal String
 */
vector<SynSet> WordNet::getSynSetsWithLiteral(const string& literal){
    SynSet* synSet;
    vector<SynSet> result;
    if (literalList.contains(literal)){
        for (const Literal& current : literalList.find(literal)->second){
            synSet = getSynSetWithId(current.getSynSetId());
            if (synSet != nullptr){
                result.emplace_back(*synSet);
            }
        }
    }
    return result;
}

/**
 * Finds literals with specified literal String and adds to the newly created literal String list. Ex: cleanest - clean
 *
 * @param literal literal String to be searched in literal list
 * @return returns a list of literals with specified literal String
 */
vector<string> WordNet::getLiteralsWithPossibleModifiedLiteral(const string& literal) const{
    vector<string> result;
    result.emplace_back(literal);
    if (exceptionList.contains(literal) && literalList.contains(exceptionList.find(literal)->second.getRoot())){
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

/**
 * Finds SynSets with specified literal String and part of speech tag, then adds to the newly created SynSet list. Ex: cleanest - clean
 *
 * @param literal literal String to be searched in literal list
 * @param pos     part of speech tag to be searched in SynSets
 * @return returns a list of SynSets with specified literal String and part of speech tag
 */
vector<SynSet> WordNet::getSynSetsWithPossiblyModifiedLiteral(const string& literal, Pos pos){
    vector<SynSet> result;
    vector<string> modifiedLiterals = getLiteralsWithPossibleModifiedLiteral(literal);
    for (const string &modifiedLiteral : modifiedLiterals){
        if (literalList.contains(modifiedLiteral)){
            addSynSetsWithLiteralToList(result, modifiedLiteral, pos);
        }
    }
    return result;
}

/**
 * Adds the reverse relations to the SynSet.
 *
 * @param synSet           SynSet to add the reverse relations
 * @param semanticRelation relation whose reverse will be added
 */
void WordNet::addReverseRelation(const SynSet& synSet, const SemanticRelation& semanticRelation) {
    SynSet* otherSynSet = getSynSetWithId(semanticRelation.getName());
    if (otherSynSet != nullptr){
        Relation* otherRelation = new SemanticRelation(synSet.getId(), SemanticRelation::reverse(semanticRelation.getRelationType()));
        if (!otherSynSet->containsRelation(otherRelation)){
            otherSynSet->addRelation(otherRelation);
        }
    }
}

/**
 * Removes the reverse relations from the SynSet.
 *
 * @param synSet           SynSet to remove the reverse relation
 * @param semanticRelation relation whose reverse will be removed
 */
void WordNet::removeReverseRelation(const SynSet& synSet, const SemanticRelation& semanticRelation) {
    SynSet* otherSynSet = getSynSetWithId(semanticRelation.getName());
    if (otherSynSet != nullptr){
        Relation* otherRelation = new SemanticRelation(synSet.getId(), SemanticRelation::reverse(semanticRelation.getRelationType()));
        if (otherSynSet->containsRelation(otherRelation)){
            otherSynSet->removeRelation(otherRelation);
        }
    }
}

/**
 * Loops through the SynSet list and adds the possible reverse relations.
 */
void WordNet::equalizeSemanticRelations() {
    for (const SynSet& synSet : getSynSetList()){
        for (int i = 0; i < synSet.relationSize(); i++){
            if (auto* relation = dynamic_cast<SemanticRelation*>(synSet.getRelation(i))){
                addReverseRelation(synSet, *relation);
            }
        }
    }
}

/**
 * Creates a list of literals with a specified word, or possible words corresponding to morphological parse.
 *
 * @param word      literal String
 * @param parse     morphological parse to get possible words
 * @param metaParse metamorphic parse to get possible words
 * @param fsm       finite state machine morphological analyzer to be used at getting possible words
 * @return a list of literal
 */
vector<Literal> WordNet::constructLiterals(const string& word, const MorphologicalParse& parse, const MetamorphicParse& metaParse,
                                           FsmMorphologicalAnalyzer fsm) const{
    vector<Literal> result;
    if (parse.size() > 0){
        if (!parse.isPunctuation() && !parse.isCardinal() && !parse.isReal()){
            unordered_set<string> possibleWords = fsm.getPossibleWords(parse, metaParse);
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

/**
 * Creates a list of SynSets with a specified word, or possible words corresponding to morphological parse.
 *
 * @param word      literal String  to get SynSets with
 * @param parse     morphological parse to get SynSets with proper literals
 * @param metaParse metamorphic parse to get possible words
 * @param fsm       finite state machine morphological analyzer to be used at getting possible words
 * @return a list of SynSets
 */
vector<SynSet> WordNet::constructSynSets(const string& word, const MorphologicalParse& parse, const MetamorphicParse& metaParse,
                                         FsmMorphologicalAnalyzer fsm){
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
                    for (const SynSet& synSet : synSets){
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

/**
 * Returns a list of literals using 3 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param morphologicalParse1 morphological parse to get possible words
 * @param morphologicalParse2 morphological parse to get possible words
 * @param morphologicalParse3 morphological parse to get possible words
 * @param metaParse1          metamorphic parse to get possible words
 * @param metaParse2          metamorphic parse to get possible words
 * @param metaParse3          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of literals
 */
vector<Literal>
WordNet::constructIdiomLiterals(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2,
                                const MorphologicalParse& morphologicalParse3, const MetamorphicParse& metaParse1,
                                const MetamorphicParse& metaParse2, const MetamorphicParse& metaParse3,
                                FsmMorphologicalAnalyzer fsm) const{
    vector<Literal> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
    unordered_set<string> possibleWords3 = fsm.getPossibleWords(morphologicalParse3, metaParse3);
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

/**
 * Returns a list of SynSets using 3 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param morphologicalParse1 morphological parse to get possible words
 * @param morphologicalParse2 morphological parse to get possible words
 * @param morphologicalParse3 morphological parse to get possible words
 * @param metaParse1          metamorphic parse to get possible words
 * @param metaParse2          metamorphic parse to get possible words
 * @param metaParse3          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of SynSets
 */
vector<SynSet>
WordNet::constructIdiomSynSets(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2,
                               const MorphologicalParse& morphologicalParse3, const MetamorphicParse& metaParse1,
                               const MetamorphicParse& metaParse2, const MetamorphicParse& metaParse3, FsmMorphologicalAnalyzer fsm){
    vector<SynSet> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
    unordered_set<string> possibleWords3 = fsm.getPossibleWords(morphologicalParse3, metaParse3);
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

/**
 * Returns a list of literals using 2 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param morphologicalParse1 morphological parse to get possible words
 * @param morphologicalParse2 morphological parse to get possible words
 * @param metaParse1          metamorphic parse to get possible words
 * @param metaParse2          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of literals
 */
vector<Literal>
WordNet::constructIdiomLiterals(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2,
                                const MetamorphicParse& metaParse1, const MetamorphicParse& metaParse2,
                                FsmMorphologicalAnalyzer fsm) const{
    vector<Literal> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
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

/**
 * Returns a list of SynSets using 2 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param morphologicalParse1 morphological parse to get possible words
 * @param morphologicalParse2 morphological parse to get possible words
 * @param metaParse1          metamorphic parse to get possible words
 * @param metaParse2          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of SynSets
 */
vector<SynSet>
WordNet::constructIdiomSynSets(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2,
                               const MetamorphicParse& metaParse1, const MetamorphicParse& metaParse2, FsmMorphologicalAnalyzer fsm){
    vector<SynSet> result;
    unordered_set<string> possibleWords1 = fsm.getPossibleWords(morphologicalParse1, metaParse1);
    unordered_set<string> possibleWords2 = fsm.getPossibleWords(morphologicalParse2, metaParse2);
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

/**
 * Sorts definitions of SynSets in SynSet list according to their lengths.
 */
void WordNet::sortDefinitions() {
    for (SynSet synSet: getSynSetList()){
        synSet.sortDefinitions();
    }
}

/**
 * Returns a list of SynSets with the interlingual relations of a specified SynSet ID.
 *
 * @param synSetId SynSet ID to be searched
 * @return a list of SynSets with the interlingual relations of a specified SynSet ID
 */
vector<SynSet> WordNet::getInterlingual(const string& synSetId) const{
    if (interlingualList.contains(synSetId)){
        return interlingualList.find(synSetId)->second;
    } else {
        return vector<SynSet>();
    }
}

/**
 * Finds the interlingual relations of each SynSet in the SynSet list with SynSets of a specified WordNet. Prints them on the screen.
 *
 * @param secondWordNet WordNet in other language to find relations
 */
void WordNet::multipleInterlingualRelationCheck1(WordNet secondWordNet) {
    for (const SynSet& synSet : getSynSetList()){
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

/**
 * Loops through the interlingual list and retrieves the SynSets from that list, then prints them.
 *
 * @param secondWordNet WordNet in other language to find relations
 */
void WordNet::multipleInterlingualRelationCheck2(WordNet secondWordNet) {
    for (auto& iterator : interlingualList){
        string s = iterator.first;
        if (interlingualList.find(s)->second.size() > 1){
            SynSet* second = secondWordNet.getSynSetWithId(s);
            if (second != nullptr){
                for (const SynSet& synSet : interlingualList.find(s)->second){
                    cout << synSet.getId() << "\t" << synSet.getSynonym().to_string() << "\t" << synSet.getDefinition() << "\t" << second->getId() << "\t" << second->getSynonym().to_string() << "\t" << second->getDefinition();
                }
            }
        }
    }
}

/**
 * Print the literals with same senses.
 */
void WordNet::sameLiteralSameSenseCheck() const{
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
    bool operator() (const SynSet& synSetA, const SynSet& synSetB){
        return synSetA.getSynonym().literalSize() < synSetB.getSynonym().literalSize();
    }
};

/**
 * Prints the literals with same SynSets.
 */
void WordNet::sameLiteralSameSynSetCheck() const{
    vector<SynSet> synsets;
    for (const SynSet& synSet : getSynSetList()){
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
    for (const SynSet& synSet : synsets){
        cout << synSet.getDefinition();
    }
}

/**
 * Prints the SynSets without definitions.
 */
void WordNet::noDefinitionCheck() const{
    for (const SynSet& synSet : getSynSetList()){
        if (synSet.getDefinition().empty()){
            cout << "SynSet " << synSet.getId() << " has no definition " << synSet.getSynonym().to_string();
        }
    }
}

/**
 * Prints SynSets without relation IDs.
 */
void WordNet::semanticRelationNoIDCheck(){
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

/**
 * Prints SynSets with same relations.
 */
void WordNet::sameSemanticRelationCheck() const{
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

/**
 * Performs check processes.
 *
 * @param secondWordNet WordNet to compare
 */
void WordNet::check(const WordNet& secondWordNet){
    //multipleInterlingualRelationCheck1(secondWordNet);
    sameLiteralSameSynSetCheck();
    sameLiteralSameSenseCheck();
    semanticRelationNoIDCheck();
    sameSemanticRelationCheck();
    noDefinitionCheck();
    //multipleInterlingualRelationCheck2(secondWordNet);
}

/**
 * Method to write SynSets to the specified file in the XML format.
 *
 * @param fileName file name to write XML files
 */
void WordNet::saveAsXml(const string& fileName) const {
    ofstream outFile;
    outFile.open(fileName, ofstream::out);
    outFile << "<SYNSETS>\n";
    for (SynSet synSet : getSynSetList()){
        synSet.saveAsXml(outFile);
    }
    outFile << "</SYNSETS>\n";
    outFile.close();
}

/**
 * Returns the size of the SynSet list.
 *
 * @return the size of the SynSet list
 */
int WordNet::size() const{
    return synSetList.size();
}

/**
 * Conduct common operations between similarity metrics.
 *
 * @param pathToRootOfSynSet1 first list of Strings
 * @param pathToRootOfSynSet2 second list of Strings
 * @return path length
 */
int WordNet::findPathLength(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const{
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

/**
 * Returns the depth of path.
 *
 * @param pathToRootOfSynSet1 first list of Strings
 * @param pathToRootOfSynSet2 second list of Strings
 * @return LCS depth
 */
int WordNet::findLCSdepth(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const{
    pair<string, int> temp = findLCS(pathToRootOfSynSet1, pathToRootOfSynSet2);
    if (!temp.first.empty()) {
        return temp.second;
    }
    return -1;
}

/**
 * Returns the ID of LCS of path.
 *
 * @param pathToRootOfSynSet1 first list of Strings
 * @param pathToRootOfSynSet2 second list of Strings
 * @return LCS ID
 */
string WordNet::findLCSid(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const{
    pair<string, int> temp = findLCS(pathToRootOfSynSet1, pathToRootOfSynSet2);
    return temp.first;
}

/**
 * Returns depth and ID of the LCS.
 *
 * @param pathToRootOfSynSet1 first list of Strings
 * @param pathToRootOfSynSet2 second list of Strings
 * @return depth and ID of the LCS
 */
pair<string, int> WordNet::findLCS(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const{
    for (int i = 0; i < pathToRootOfSynSet1.size(); i++) {
        string LCSid = pathToRootOfSynSet1.at(i);
        if (find(pathToRootOfSynSet2.begin(), pathToRootOfSynSet2.end(), LCSid) != pathToRootOfSynSet2.cend()) {
            return pair<string, int>(LCSid, pathToRootOfSynSet1.size() - i + 1);
        }
    }
    return pair<string, int>("", -1);
}

/**
 * Finds the path to the root node of a SynSets.
 *
 * @param synSet SynSet whose root path will be found
 * @return list of String corresponding to nodes in the path
 */
vector<string> WordNet::findPathToRoot(SynSet* synSet){
    vector<string> pathToRoot;
    while (synSet != nullptr) {
        pathToRoot.emplace_back(synSet->getId());
        synSet = percolateUp(synSet);
    }
    return pathToRoot;
}

/**
 * Finds the parent of a node. It does not move until the root, instead it goes one level up.
 *
 * @param root SynSet whose root will be find
 * @return root SynSet
 */
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

/**
 * Changes ID of a specified SynSet with the specified new ID.
 *
 * @param synSet SynSet whose ID will be updated
 * @param newId  new ID
 */
void WordNet::changeSynSetId(SynSet s, const string& newId) {
    synSetList.erase(s.getId());
    s.setId(newId);
    synSetList.emplace(newId, s);
}
