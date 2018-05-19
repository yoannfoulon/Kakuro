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

std::vector<Variable*> backTrack(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes, int *nbNoeuds, int *nbTests){

    std::stack<Variable*> process;

    int k = 0;
    Variable* currentVar;
    ++*nbNoeuds;

    process.push(globalVars[k]);

    while(!process.empty()){

        currentVar = process.top();
        bool consistant = false;

        for(int i = currentVar->getValue(); i < currentVar->getDomain().size() && !consistant; ++i){

            currentVar->setValue(currentVar->getDomain()[i]);
            consistant = isConsistant(globalContraintes, nbTests);

            if(consistant){
                if(isCompleted(globalVars)) return globalVars;
                process.push(globalVars[++k]);
                ++*nbNoeuds;
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

std::vector<Variable*> forwardChecking(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes, int *nbTests){

    std::stack<Variable*> process;
    std::stack<int> nbVarModif;
    std::vector<Variable*> variablesModif;

    int k = 0;

    process.push(globalVars[k]);

    while(!process.empty()){
        Variable *currentVar = process.top();

        int begin = 0;
        if(currentVar->getValue() > 0){
            for(int i = 0; i < currentVar->getDomainSize(); ++i){
                if(currentVar->getValue() == currentVar->getDomain()[i])
                    begin = i + 1;
            }

            int nbVarModifAtStep = nbVarModif.top();
            nbVarModif.pop();
            unsigned oldSize = variablesModif.size();
            for(int i = (oldSize - 1); i >= (oldSize - nbVarModifAtStep); --i){
                int removedSize = variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size() - 1];
                variablesModif[i]->getRemovedSizes().pop_back();

                variablesModif[i]->setDomainSize(
                    variablesModif[i]->getDomainSize() + removedSize
                );

                variablesModif.pop_back();
            }

            if(begin == currentVar->getDomainSize()){
                currentVar->setValue(0);
                --k;
                process.pop();
            }
            continue;
        }
        
        for(; begin < currentVar->getDomainSize(); ++begin){
            currentVar->setValue(currentVar->getDomain()[begin]);
            std::cout << "Valeur testée: " << currentVar->getValue ()  << " pour la variable " << currentVar->getIdentifier () << std::endl;
            int nbModif = 0;

            std::cout << "Début Check And Remove..." << std::endl;
            checkAndRemove(currentVar, globalContraintes, globalVars, &variablesModif, &nbModif);
            std::cout << "Fin Check And Remove. Tableau des variables modifiées: ";
            
            for(int i = 0; i < variablesModif.size(); ++i)
                std::cout << variablesModif[i]->getIdentifier() << " ";

            std::cout << std::endl;
            std::cout << "nbModif: " <<  nbModif << std::endl;

            nbVarModif.push(nbModif);

            for(int i = 0; i < globalVars.size(); ++i){
                std::cout << "Domaine de " << globalVars[i]->getIdentifier() << " (" << globalVars[i]->getDomainSize() << ") => ";

                for(int j = 0; j < globalVars[i]->getDomainSize(); ++j)
                    std::cout << globalVars[i]->getDomain()[j] << " ";

                std::cout << std::endl;
            }
            std::cout << std::endl;

            if(!emptyDomain(globalVars)){
                std::cout << "Valeur trouvée pour la variable " << currentVar->getIdentifier() << " : " << currentVar->getValue() << std::endl;
                if(isCompleted(globalVars)) return globalVars;
                process.push(globalVars[++k]);
                break;
            }

            else if(emptyDomain(globalVars) && begin == currentVar->getDomainSize() - 1){
                std::cout << "Aucune valeur consistante trouvée pour la variable " << currentVar->getIdentifier() << std::endl;
                std::cout << "Coucou";
                int nbVarModifAtStep = nbVarModif.top();
                std::cout << "1";
                nbVarModif.pop();
                std::cout << "2";
                unsigned oldSize = variablesModif.size();
                std::cout << "3";
                for(int i = (oldSize - 1); i >= (oldSize - nbVarModifAtStep); --i){
                    int removedSize = variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size() - 1];
                    variablesModif[i]->getRemovedSizes().pop_back();

                    variablesModif[i]->setDomainSize(
                        variablesModif[i]->getDomainSize() + removedSize
                    );

                    variablesModif.pop_back();
                }
                std::cout << "4";
                currentVar->setValue(0);
                std::cout << "5";
                --k;
                std::cout << "6";
                process.pop();
                std::cout << "7";
            }

            else{
                std::cout << "Domaine vide, passage à la valeur suivante" << std::endl;
                int nbVarModifAtStep = nbVarModif.top();
                nbVarModif.pop();
                unsigned oldSize = variablesModif.size();
                for(int i = (oldSize - 1); i >= (oldSize - nbVarModifAtStep); --i){
                    int removedSize = variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size() - 1];
                    variablesModif[i]->getRemovedSizes().pop_back();

                    variablesModif[i]->setDomainSize(
                        variablesModif[i]->getDomainSize() + removedSize
                    );

                    variablesModif.pop_back();
                }
            }
        }
    }

    /*int k = 0;

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

        if(emptyDomain(globalVars)){
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
    return globalVars;
}
