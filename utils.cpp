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

bool isConsistant(std::vector<Contrainte*> globalContraintes, long *nbTests){
    for(unsigned i = 0; i < globalContraintes.size(); ++i){
        ++*nbTests;
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

bool emptyDomain(std::vector<Variable*> vars){
    for(unsigned i = 0; i < vars.size(); ++i){
        if(vars[i]->getDomainSize() == 0) return true;
    }
    return false;
}

void checkAndRemove(Variable* v, std::vector<Contrainte*> globalContraintes, std::vector<Variable*> globalVariables, std::vector<Variable*> *variablesModifs, int *nbModif, long *nbTests){
    unsigned begin = 0;
    for(unsigned i = 0; i < globalVariables.size(); ++i){
        if(v->getIdentifier() == globalVariables[i]->getIdentifier()){
            begin = i + 1;
        }
    }

    for(; begin < globalVariables.size(); ++begin){
        //if(v->getIdentifier() != globalVariables[begin]->getIdentifier()){
            int removedSize = 0;
            for(unsigned j = 0; j < globalContraintes.size(); ++j){
                bool isInVars1 = globalContraintes[j]->isInVars(v);
                bool isInVars2 = globalContraintes[j]->isInVars(globalVariables[begin]);
                if(isInVars1 && isInVars2){
                    globalContraintes[j]->remove(v, globalVariables[begin], &removedSize);
                    ++*nbTests;
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

void reset(std::vector<Variable*> globalVars, long *nbNoeuds, long *nbTests, std::vector<int> domain){
    for(unsigned i = 0; i < globalVars.size(); ++i){
        globalVars[i]->setValue(0);
        globalVars[i]->setDomain(domain);
        globalVars[i]->setDomainSize(domain.size());
    }
    *nbNoeuds = 0;
    *nbTests = 0;
}

bool domOnDegHeuristic(Variable* v1, Variable* v2, std::vector<Contrainte*> globalContraintes){

    double degV1 = 0;
    double degV2 = 0;

    for(unsigned i = 0; i < globalContraintes.size(); ++i){
        for(unsigned j = 0; j < globalContraintes[i]->getVariables().size(); ++j){
            if(v1->getIdentifier() == globalContraintes[i]->getVariables()[j]->getIdentifier()) ++degV1;
            if(v2->getIdentifier() == globalContraintes[i]->getVariables()[j]->getIdentifier()) ++degV2;
        }
    }

    double heuristicV1 = (double)v1->getDomainSize() / degV1;
    double heuristicV2 = (double)v2->getDomainSize() / degV2;

    std::cout << v1->getIdentifier() << " --> " << v1->getDomainSize() << " / " << degV1 << " = " << heuristicV1 << " (" << v1->getValue() << ")" << std::endl;
    std::cout << v2->getIdentifier() << " --> " << v2->getDomainSize() << " / " << degV1 << " = " << heuristicV2 << " (" << v2->getValue() << ")" << std::endl;

    return heuristicV1 < heuristicV2;
}
