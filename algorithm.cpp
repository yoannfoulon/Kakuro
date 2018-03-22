#include "algorithm.hpp"
#include <stack>
#include <iostream>

std::vector<Variable*> backTrack(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes){

    std::stack<Variable*> process;
    int nbNoeuds = 1;

    int k = 0;
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

    /*
        TODO: Récupérer les contraintes de différence liées à la variable étudiée actuellement et supprimer de leur domaine la valeur actuelle
        de la variable étudiée si celle ci s'avère être consistante.
    */
}
