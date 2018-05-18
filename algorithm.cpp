#include "algorithm.hpp"
#include <stack>
#include <iostream>

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

std::vector<Variable*> backTrack(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes){

    std::stack<Variable*> process;

    int nbNoeuds = 1;
    int k = 0;
    Variable* currentVar;

    process.push(globalVars[k]);

    while(!process.empty()){

        currentVar = process.top();
        bool consistant = false;

        for(int i = currentVar->getValue(); i < currentVar->getDomain().size() && !consistant; ++i){

            currentVar->setValue(currentVar->getDomain()[i]);
            consistant = isConsistant(globalContraintes);

            if(consistant){
                if(isCompleted(globalVars)) return globalVars;
                process.push(globalVars[++k]);
                ++nbNoeuds;
            }
        }
        if(!consistant){
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

    int k = 0;

    process.push(globalVars[k]);

    while(!process.empty()){
        Variable* currentVar = process.top();
        
        bool domainCheck = false; 
        if(emptyDomain(globalVars) || (currentVar->getDomainSize() == 1 && currentVar->getValue() == currentVar->getDomain()[0])){
            process.pop();
            globalVars[k]->setDomainSize(globalVars[k]->getDomainSize() + 1);
            int nbVarModifAtStep = nbVarModif.top();
            nbVarModif.pop();
            unsigned oldSize = variablesModif.size();
            for(int j = (oldSize - 1); j >= (oldSize - nbVarModifAtStep); j--){
                variablesModif[j]->setDomainSize(
                    variablesModif[j]->getDomainSize() +
                    variablesModif[j]->getRemovedSizes()[variablesModif[j]->getRemovedSizes().size() - 1]
                );
                variablesModif[j]->getRemovedSizes().pop_back();
                variablesModif.pop_back();
            }
            --k;
            currentVar->setValue(0);
            domainCheck = true;
        }
        if(domainCheck) continue;

        std::cout << currentVar->getValue() << std::endl;
        int begin = 0;
        if(currentVar->getValue() > 0){
            for (int i = 0; i < currentVar->getDomainSize(); i++)
				if (currentVar->getValue() == currentVar->getDomain()[i])
					begin = i + 1;
        }

        for(int i = begin; i < currentVar->getDomainSize(); ++i){
            int nbModif = 0;

            currentVar->setValue(currentVar->getDomain()[i]);
            std::cout << "Valeur testée: " << currentVar->getValue ()  << " pour la variable " << currentVar->getIdentifier () << std::endl;
            checkAndRemove(currentVar, globalContraintes, globalVars, &variablesModif, &nbModif);
            nbVarModif.push(nbModif);

            for(int j = 0; j < globalVars.size(); ++j){
                std::cout << "Domaine de " << globalVars[j]->getIdentifier() << " (" << globalVars[j]->getDomainSize() << ") => ";
                for(int k = 0; k < globalVars[j]->getDomainSize(); ++k){
                    std::cout << globalVars[j]->getDomain()[k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            if(!emptyDomain(globalVars)){
                printf("\nValeur trouvée pour la variable %d => %d\n\n", currentVar->getIdentifier(), currentVar->getValue());
                if(isCompleted(globalVars)) return globalVars;
                process.push(globalVars[++k]);
                //TODO: Regarder pourquoi ce break change le résultat
                break;
            }
            else if(emptyDomain(globalVars) && i == currentVar->getDomainSize() - 1){
                std::cout << "Aucune valeur consistante trouvée pour la variable " << currentVar->getIdentifier() << std::endl;
                process.pop();
                int nbVarModifAtStep = nbVarModif.top();
                std::cout << variablesModif[variablesModif.size() - 1]->getRemovedSizes()[ variablesModif[variablesModif.size() - 1]->getRemovedSizes().size() - 1] << std::endl;
                nbVarModif.pop();
                unsigned oldSize = variablesModif.size();
                for(int j = (oldSize - 1); j >= (oldSize - nbVarModifAtStep); j--){
                    variablesModif[j]->setDomainSize(
                        variablesModif[j]->getDomainSize() +
                        variablesModif[j]->getRemovedSizes()[variablesModif[j]->getRemovedSizes().size() - 1]
                    );
                    variablesModif[j]->getRemovedSizes().pop_back();
                    variablesModif.pop_back();
                }
                --k;
                currentVar->setValue(0);
            }
            else {
                for(int z = 0; z < variablesModif.size(); ++z){
                    std::cout << variablesModif[z]->getIdentifier() << " -> ";
                    for(int y = 0; y <  variablesModif[z]->getRemovedSizes().size(); ++y){
                        std::cout << variablesModif[z]->getRemovedSizes()[y] << " ";
                    }
                    std::cout << std::endl;
                }
                std::cout << "EMPTY DOMAIN" << std::endl;
                int nbVarModifAtStep = nbVarModif.top();
                std::cout << nbVarModifAtStep << std::endl;
                nbVarModif.pop();
                unsigned oldSize = variablesModif.size();
                //std::cout << oldSize << std::endl;
                for(int j = (oldSize - 1); j >= (oldSize - nbVarModifAtStep); j--){
                    variablesModif[j]->setDomainSize(
                        variablesModif[j]->getDomainSize() +
                        variablesModif[j]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size() - 1]
                    );
                    variablesModif[j]->getRemovedSizes().pop_back();
                    variablesModif[j]->setValue(0);
                    variablesModif.pop_back();

                    for(int z = 0; z < variablesModif.size(); ++z){
                    std::cout << variablesModif[z]->getIdentifier() << " -> ";
                    for(int y = 0; y <  variablesModif[z]->getRemovedSizes().size(); ++y){
                        std::cout << variablesModif[z]->getRemovedSizes()[y] << " ";
                    }
                    std::cout << std::endl;
                    }

                    std::cout << globalVars[8]->getDomain()[globalVars[8]->getDomainSize() - 1] << std::endl;
                }
            }
        }

        /*if(emptyDomain(globalVars)){
            std::cout << "Aucune valeur consistante trouvée pour la variable " << currentVar->getIdentifier() << std::endl;
            process.pop();
            int nbVarModifAtStep = nbVarModif.top();
            nbVarModif.pop();
            unsigned oldSize = variablesModif.size();
            for(int i = oldSize - 1; i >= oldSize - nbVarModifAtStep; i--){
                variablesModif[i]->setDomainSize(
                    variablesModif[i]->getDomainSize() +
                    variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size()]
                );
                variablesModif.pop_back();
            }
            --k;
            currentVar->setValue(0);
        }*/
    }
    return globalVars;
}
