//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_STATE_H
#define MORPHOLOGICALANALYSIS_STATE_H

#include <string>
using namespace std;

class State {
private:
    bool startState;
    bool endState;
    string name;
    string pos;
public:
    State();
    State(string name, bool startState, bool endState);
    State(string name, bool startState, bool endState, string pos);
    string getName();
    string getPos();
    bool isEndState();
    string to_String();
    bool operator==(const State &anotherState) const{
        return (name == anotherState.name);
    }
    bool operator<(const State &anotherState) const{
        return (name < anotherState.name);
    }
};


#endif //MORPHOLOGICALANALYSIS_STATE_H
