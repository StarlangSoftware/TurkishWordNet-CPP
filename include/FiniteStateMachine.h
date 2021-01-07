//
// Created by Olcay Taner Yıldız on 1.03.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FINITESTATEMACHINE_H
#define MORPHOLOGICALANALYSIS_FINITESTATEMACHINE_H

#include <vector>
#include <map>
#include "State.h"
#include "Transition.h"

using namespace std;

class FiniteStateMachine {
private:
    vector<State> states;
    map<State, vector<Transition>> transitions;
public:
    FiniteStateMachine() = default;
    explicit FiniteStateMachine(string fileName);
    bool isValidTransition(string transition);
    State getState(string name);
    vector<State> getStates();
    void addTransition(State fromState, State toState, string with, string withName);
    void addTransition(State fromState, State toState, string with, string withName, string toPos);
    vector<Transition> getTransitions(State state);
};


#endif //MORPHOLOGICALANALYSIS_FINITESTATEMACHINE_H
