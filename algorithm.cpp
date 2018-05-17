#include "algorithm.hpp"
#include <stack>
#include <iostream>

std::vector<Variable*> backTrack(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes){

    std::stack<Variable*> process;
    int nbNoeuds = 1;

    int k = 0;

    /*
        Implémentation heurisitiques

    std::sort(globalVars.begin(), globalVars.end(), customLess);

    for(unsigned i = 0; i < globalVars.size(); ++i){
        std::cout << globalVars[i]->getHeuristic();
        if(i != globalVars.size()-2){
            std::cout << "."
        } else {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    */

    process.push(globalVars[k]);

    while(!process.empty()){
        Variable* currentVar = process.top();
        //std::cout << "Variable étudiée : " << currentVar->getIdentifier() << " -> " << currentVar->getValue() << std::endl;

        bool consistant = false;

        for(unsigned i = currentVar->getValue(); i < currentVar->getDomain().size() && !consistant; ++i){
            //std::cout << "Domaine en cours : " << currentVar->getDomain()[i] << std::endl;

            currentVar->setValue(currentVar->getDomain()[i]);
            consistant = isConsistant(globalContraintes);

            if(consistant){
                //std::cout << "Valeur " << currentVar->getValue() << " affectée pour la variable " << currentVar->getIdentifier() << std::endl;
                if(isCompleted(globalVars)){
                    return globalVars;
                }
                process.push(globalVars[++k]);
                ++nbNoeuds;
            }
        }
        if(!consistant){
            //std::cout << "Aucune valeur consistante trouvée pour la variable " << currentVar->getIdentifier() << std::endl;
            process.pop();
            --k;
            currentVar->setValue(0);
        }
    }
    return globalVars;
}


std::vector<Variable*> forwardChecking(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes){

    std::stack<Variable*> process;
    std::stack<int> nbVarModif;
    std::vector<Variable*> variablesModif;

    int nbNoeuds = 1;
    int k = 0;

    process.push(globalVars[k]);

    while(!process.empty()){

        Variable* currentVar = process.top();

        for(int i = 0; i < currentVar->getDomainSize(); ++i){
            int nbModif = 0;

            currentVar->setValue(currentVar->getDomain()[i]);
            checkAndRemove(currentVar, globalContraintes, globalVars, &variablesModif, &nbModif);
            nbVarModif.push(nbModif);

            for(unsigned j = 0; j < globalVars.size(); ++j){
                std::cout << "Domaine de " << globalVars[j]->getIdentifier() << " (" << globalVars[j]->getDomainSize() << ") => ";
                for(int k = 0; k < globalVars[j]->getDomainSize(); ++k){
                    std::cout << globalVars[j]->getDomain()[k] << " ";
                }
                std::cout << std::endl;
            }

            if(!emptyDomain(globalVars)){
                printf("\nValeur trouvée pour la variable %d => %d\n\n", currentVar->getIdentifier(), currentVar->getValue());
                if(isCompleted(globalVars)) return globalVars;
                process.push(globalVars[++k]);
                ++nbNoeuds;
                //TODO: Regarder pourquoi ce break change le résultat
                break;
            } else {
                int nbVarModifAtStep = nbVarModif.top();
                nbVarModif.pop();
                unsigned oldSize = variablesModif.size();
                for(unsigned i = (oldSize - 1); i >= (oldSize - nbVarModifAtStep); i--){
                    variablesModif[i]->setDomainSize(
                        variablesModif[i]->getDomainSize() +
                        variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size() - 1]
                    );
                    variablesModif[i]->getRemovedSizes().pop_back();
                    variablesModif.pop_back();
                }
                exit(0);
            }
        }

        if(emptyDomain(globalVars)){
            std::cout << "Aucune valeur consistante trouvée pour la variable " << currentVar->getIdentifier() << std::endl;
            process.pop();
            int nbVarModifAtStep = nbVarModif.top();
            nbVarModif.pop();
            unsigned oldSize = variablesModif.size();
            for(unsigned i = oldSize - 1; i >= oldSize - nbVarModifAtStep; i--){
                variablesModif[i]->setDomainSize(
                    variablesModif[i]->getDomainSize() +
                    variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size()]
                );
                variablesModif.pop_back();
            }
            --k;
            currentVar->setValue(0);
        }
    }
    return globalVars;
}
