//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMPARSE_H
#define MORPHOLOGICALANALYSIS_FSMPARSE_H

#include <TxtWord.h>
#include "MorphologicalParse.h"
#include "State.h"

class FsmParse : public MorphologicalParse {
private:
    vector<State> suffixList;
    vector<string> formList;
    vector<string> transitionList;
    vector<string> withList;
    string initialPos;
    string pos;
    string form;
    string verbAgreement = "";
    string possesiveAgreement = "";
public:
    explicit FsmParse(Word* root);
    FsmParse() = default;
    FsmParse(int number, State startState);
    FsmParse(double number, string stringValue, State startState);
    FsmParse(string punctuation, State startState);
    FsmParse(TxtWord* root, State startState);
    void constructInflectionalGroups();
    string getVerbAgreement();
    string getPossesiveAgreement();
    void setAgreement(string transitionName);
    string getLastLemmaWithTag(string pos);
    string getLastLemma();
    void addSuffix(State suffix, string form, string transition, string with, string toPos);
    string getSurfaceForm();
    State getStartState();
    string getFinalPos();
    string getInitialPos();
    void setForm(string name);
    State getFinalSuffix();
    FsmParse clone();
    string headerTransition();
    string pronounTransition();
    string transitionlist();
    string getSuffixList();
    string getWithList();
    string to_String();
/**
 * The overridden compareTo metgod takes an {@link Object} as an input and if it is an instance of the {@link FsmParse}
 * class it returns the result of comparison of the items of transitionList with input {@link Object}.
 *
 * @param o {@link Object} input to compare.
 * @return comparison of the items of transitionList with input {@link Object}, and returns 0 if input is not an
 * instance of {@link FsmParse} class.
 */
    bool operator==(FsmParse &fsmParse){
        return (to_String() == fsmParse.to_String());
    }
    bool operator<(FsmParse &fsmParse){
        return (to_String() < fsmParse.to_String());
    }
};


#endif //MORPHOLOGICALANALYSIS_FSMPARSE_H
