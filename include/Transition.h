//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_TRANSITION_H
#define MORPHOLOGICALANALYSIS_TRANSITION_H

#include "State.h"
#include "FsmParse.h"

class Transition {
private:
    State toState;
    string with;
    string withName;
    string formationToCheck;
    string toPos;
    string beforeLastVowel(string stem);
    string lastVowel(string stem);
    string lastPhoneme(string stem);
    string withFirstChar();
    bool startWithVowelorConsonantDrops();
    string resolveD(TxtWord* root, string formation);
    string resolveA(TxtWord* root, string formation, bool rootWord);
    string resolveH(TxtWord* root, string formation, bool beginningOfSuffix, bool specialCaseTenseSuffix, bool rootWord);
    string resolveC(string formation);
    string resolveS(string formation);
    string resolveSh(string formation);
public:
    Transition(State toState, string with, string withName);
    Transition(State toState, string with, string withName, string toPos);
    explicit Transition(string with);
    State getToState();
    string getToPos();
    bool transitionPossible(string currentSurfaceForm, string realSurfaceForm);
    bool transitionPossible(FsmParse currentFsmParse);
    bool transitionPossible(TxtWord* root, State fromState);
    bool softenDuringSuffixation(TxtWord* root);
    string makeTransition(TxtWord* root, string stem);
    string makeTransition(TxtWord* root, string stem, State startState);
    string to_String();
    string getWith();
};


#endif //MORPHOLOGICALANALYSIS_TRANSITION_H
