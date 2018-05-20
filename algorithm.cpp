#include "algorithm.hpp"
#include <stack>
#include <iostream>


std::vector<Variable*> backTrack(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes, long *nbNoeuds, long *nbTests){

    std::stack<Variable*> process;

    unsigned k = 0;
    Variable* currentVar;

    process.push(globalVars[k]);

    while(!process.empty()){

        currentVar = process.top();
        bool consistant = false;

        for(unsigned i = currentVar->getValue(); i < currentVar->getDomain().size() && !consistant; ++i){
            ++*nbNoeuds;
            currentVar->setValue(currentVar->getDomain()[i]);
            consistant = isConsistant(globalContraintes, nbTests);

            if(consistant){
                if(isCompleted(globalVars)) return globalVars;
                process.push(globalVars[++k]);
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

std::vector<Variable*> forwardChecking(std::vector<Variable*> globalVars, std::vector<Contrainte*> globalContraintes, long *nbNoeuds, long *nbTests, bool heuristic){

    //Pile des variables auxquelles des valeurs ont été attribuées ou devant passer dans l'algorithme
    std::stack<Variable*> process;
    //Pile stockant le nombre de variables dont le domaine a été modifié à chaque étape de l'algorithme
    std::stack<int> nbVarModif;
    //Tableau des variables
    std::vector<Variable*> variablesModif;

    //Compteur permettant de savoir quelle variable de globalVars il est nécéssaire d'empiler
    unsigned k = 0;

    if(heuristic) std::sort(globalVars.begin(), globalVars.end(), Sorter(globalContraintes));

    //Empilage de la première variable
    process.push(globalVars[k]);

    while(!process.empty()){
        //On dépile la variable à laquelle on veut attribuer une valeur à cette étape de l'algorithme

        Variable *currentVar = process.top();

        int begin = 0;
        if(currentVar->getValue() > 0){
            //Si la variable a déja une valeur différente de 0, cela signifie que l'algorithme est déja passé sur celle-ci et est revenu en arrière
            //On cherche donc à recommencer à la valeur d'après
            for(int i = 0; i < currentVar->getDomainSize(); ++i){
                if(currentVar->getValue() == currentVar->getDomain()[i])
                    begin = i + 1;
            }

            //On efface les modifications de domaine du à la valuation précédente de cette variable
            int nbVarModifAtStep = nbVarModif.top();
            nbVarModif.pop();
            int oldSize = variablesModif.size();
            for(int i = (oldSize - 1); i >= (oldSize - nbVarModifAtStep); i--){
                //Le tableau removedSizes faisant partie des objets de classe Variable contiennent le nombre d'éléments
                //enlevés du domaine à chaque étape ou la variable a été modifié
                int removedSize = variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size() - 1];
                variablesModif[i]->getRemovedSizes().pop_back();

                variablesModif[i]->setDomainSize(
                    variablesModif[i]->getDomainSize() + removedSize
                );

                variablesModif.pop_back();
            }

            //Si la valeur de begin est égal a la taille du domaine de la variable a valuer, ca veut dire qu'on a épuisé
            //toutes les valeurs de son domaine. L'erreur se situe donc à un niveau précédent: On dépile la variable pour revenir à celle
            //d'avant et on passe à l'itération suivante de la boucle
            if(begin == currentVar->getDomainSize()){
                currentVar->setValue(0);
                --k;
                process.pop();
                continue;
            }
        }

        //Sinon on parcourt les valeurs restantes du domaine pour trouver une valuation ne produisant pas de domaine vide
        for(; begin < currentVar->getDomainSize(); ++begin){
            ++*nbNoeuds;
            //On attribue une valuation a la variable courante
            currentVar->setValue(currentVar->getDomain()[begin]);
            //std::cout << "Valeur testée: " << currentVar->getValue ()  << " pour la variable " << currentVar->getIdentifier () << std::endl;

            //On initialise le nombre de variables modifiées par cette valuation
            int nbModif = 0;

            //Cette fonction vérifie les contraintes, modifie les domaines correctement, répertorie
            //les variables modifiées, les compte, et compte les modifications sur chacune de ces dernières
            checkAndRemove(currentVar, globalContraintes, globalVars, &variablesModif, &nbModif, nbTests);

            //On push le nombre de variables modifiées à cette étape sur la pile du nombre de modification à chaque étape
            nbVarModif.push(nbModif);
            //Si on a pas de domaine vide, la valuation est correcte: On vérifie si la grille est terminée, puis on empile la
            //variable suivant avant de sortir de la boucle for parcourant le domaine de la variable courante
            if(!emptyDomain(globalVars)){
                //std::cout << "Valeur trouvée pour la variable " << currentVar->getIdentifier() << " : " << currentVar->getValue() << std::endl;
                if(isCompleted(globalVars)) return globalVars;
                if(heuristic){
                    std::sort(globalVars.begin(), globalVars.end(), Sorter(globalContraintes));
                    ++k;
                    while(globalVars[k]->getValue() > 0 && k < globalVars.size())
                        ++k;

                    process.push(globalVars[k]);
                } else {
                    process.push(globalVars[++k]);
                }
                break;
            }


            //Sinon, si on a un domaine vide et que begin est égal à l'indice du dernier élément du domaine de la
            //variable courante, cela signifie qu'on a trouvé aucune valeur consistante pour cette variable
            else if(emptyDomain(globalVars) && begin == currentVar->getDomainSize() - 1){
                //std::cout << "Aucune valeur consistante trouvée pour la variable " << currentVar->getIdentifier() << std::endl;
                //On récupère le nombre de variables modifiées par la dernière valuation
                int nbVarModifAtStep = nbVarModif.top();
                nbVarModif.pop();
                int oldSize = variablesModif.size();
                //On rétablit les domaines des variables modifiées
                for(int i = (oldSize - 1); i >= (oldSize - nbVarModifAtStep); i--){
                    int removedSize = variablesModif[i]->getRemovedSizes()[variablesModif[i]->getRemovedSizes().size() - 1];
                    variablesModif[i]->getRemovedSizes().pop_back();

                    variablesModif[i]->setDomainSize(
                        variablesModif[i]->getDomainSize() + removedSize
                    );

                    variablesModif.pop_back();
                }
                //On réinitialise la valeur de la variable courante à 0
                currentVar->setValue(0);
                --k;
                //On dépile la variable courante pour revenir à la variable précédente
                process.pop();
            }

            //Sinon, si on a un domaine vide mais qu'on est pas dans la dernière valeur possible du domaine
            //on annule les modifications des variables et on passe à l'itération suivante de la boucle sur le domaine
            else{
                //std::cout << "Domaine vide, passage à la valeur suivante" << std::endl;
                int nbVarModifAtStep = nbVarModif.top();
                nbVarModif.pop();
                int oldSize = variablesModif.size();
                for(int i = (oldSize - 1); i >= (oldSize - nbVarModifAtStep); i--){
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
    return globalVars;
}
