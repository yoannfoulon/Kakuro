#include "utils.hpp"
#include <iostream>

/*
struct {
    bool operator()(Variable* a, Variable* b) const {
        return a->getHeuristic() < b->getHeuristic();
    }
} customLess;
*/

void displayCSP(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes){
    std::cout << "----------------- VARIABLES -------------------" << std::endl;

    for(int i = 0; i < globalVars.size(); ++i){
       std::cout << "Variable " << globalVars[i]->getIdentifier() << " -> " << globalVars[i]->getValue() << std::endl;
    }

    std::cout << "----------------- CONTRAINTES -------------------" << std::endl;

    for(int i = 0; i < globalContraintes.size(); ++i){
        std::cout << i << ") " << globalContraintes[i]->getType() << std::endl;
        for(int j = 0; j < globalContraintes[i]->getVariables().size(); ++j){
           std::cout << "Variable " << globalContraintes[i]->getVariables()[j]->getIdentifier() << " -> " << globalContraintes[i]->getVariables()[j]->getValue() << std::endl;
        }
       std::cout << "Arité " << globalContraintes[i]->getArite() << std::endl << std::endl;
    }
}

bool isConsistant(std::vector<Contrainte*> globalContraintes){
    for(int i = 0; i < globalContraintes.size(); ++i){
        bool verifiable = true;
        for (int j = 0; j < globalContraintes[i]->getArite() && verifiable; ++j) {
            if (globalContraintes[i]->getVariables()[j]->getValue() == 0) verifiable = false;
        }

        if (verifiable) {
            if(!globalContraintes[i]->evaluation()){
                return false;
            }
        }
    }
    return true;
}

bool isCompleted(std::vector<Variable*> solutions){
    for(int i = 0; i < solutions.size(); ++i){
        if(solutions[i]->getValue() == 0) return false;
    }
    return true;
}

bool emptyDomain(std::vector<Variable*> vars){
    for(int i = 0; i < vars.size(); ++i){
        if(vars[i]->getDomainSize() == 0) return true;
    }
    return false;
}

void checkAndRemove(Variable* v, std::vector<Contrainte*> globalContraintes, std::vector<Variable*> globalVariables, std::vector<Variable*> *variablesModifs, int *nbModif){
    int begin = 0;
    for(int i = 0; i < globalVariables.size(); ++i){
        if(v->getIdentifier() == globalVariables[i]->getIdentifier()){
            begin = i + 1;
        }
    }

    for(; begin < globalVariables.size(); ++begin){
        //if(v->getIdentifier() != globalVariables[begin]->getIdentifier()){
            printf ("Variable %d <=> Variable %d\n", v->getIdentifier(), globalVariables[begin]->getIdentifier());
            int removedSize = 0;
            for(int j = 0; j < globalContraintes.size(); ++j){
                bool isInVars1 = globalContraintes[j]->isInVars(v);
                bool isInVars2 = globalContraintes[j]->isInVars(globalVariables[begin]);
                if(isInVars1 && isInVars2){
                    globalContraintes[j]->remove(v, globalVariables[begin], &removedSize);
                }
            }
            

            if(removedSize != 0){
                globalVariables[begin]->getRemovedSizes().push_back(removedSize);
                variablesModifs->push_back(globalVariables[begin]);
                ++*nbModif;
            }
        //}
    }
}
