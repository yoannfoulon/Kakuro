#include "utils.hpp"
#include <iostream>

struct {
    bool operator()(Variable* a, Variable* b) const {
        return a->getHeuristic() < b->getHeuristic();
    }
} customLess;

void displayCSP(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes){
    std::cout << "----------------- VARIABLES -------------------" << std::endl;

    for(unsigned i = 0; i < globalVars.size(); ++i){
       std::cout << "Variable " << globalVars[i]->getIdentifier() << " -> " << globalVars[i]->getValue() << std::endl;
    }

    std::cout << "----------------- CONTRAINTES -------------------" << std::endl;

    for(unsigned i = 0; i < globalContraintes.size(); ++i){
        std::cout << i << ") " << globalContraintes[i]->getType() << std::endl;
        for(unsigned j = 0; j < globalContraintes[i]->getVariables().size(); ++j){
           std::cout << "Variable " << globalContraintes[i]->getVariables()[j]->getIdentifier() << " -> " << globalContraintes[i]->getVariables()[j]->getValue() << std::endl;
        }
       std::cout << "Arité " << globalContraintes[i]->getArite() << std::endl << std::endl;
    }
}

bool isConsistant(std::vector<Contrainte*> globalContraintes){
    for(unsigned i = 0; i < globalContraintes.size(); ++i){
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
    for(unsigned i = 0; i < solutions.size(); ++i){
        if(solutions[i]->getValue() == 0) return false;
    }
    return true;
}

bool noEmptyDomain(std::vector<Variable*> vars){
    for(unsigned i = 0; i < vars.size(); ++i){
        if(vars[i]->getDomainSize() == 0)
            return true;
    }
    return false;
}

void checkAndRemove(Variable* v, std::vector<Contrainte*> globalContraintes){
    for(unsigned i = 0; i < globalContraintes.size(); ++i){
        globalContraintes[i]->remove(v);
    }
}
