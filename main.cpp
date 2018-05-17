#include "parser.hpp"
#include "algorithm.hpp"
#include "utils.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>


int main (int argc, char *argv[]) {

    if (argc - 1 != 1) {
        fprintf (stderr,"Utilisation: %s <fichier>\n",argv[0]);
        exit (-1);
    }

    std::vector<Variable*> globalVars;
    std::vector<Contrainte*> globalContraintes;
    std::vector<int> domain = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::clock_t start;
    double duration;

    std::vector<Variable*> solutions;

    parse(argv[1], globalVars, globalContraintes, domain);
    displayCSP(globalVars, globalContraintes);

    std::cout << "--------- BACKTRACK ---------" << std::endl;
    start = std::clock();
    solutions = backTrack(globalVars, globalContraintes);
    duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "Réalisé en " << duration << " secondes" << std::endl;
    for(unsigned i = 0; i < solutions.size(); ++i){
        std::cout << "Variable " << solutions[i]->getIdentifier() << " --> " << solutions[i]->getValue() << std::endl;
    }

    // Reset
    for(unsigned i = 0; i < globalVars.size(); ++i){
        globalVars[i]->setValue(0);
    }

    std::cout << "--------- FORWARD CHECKING ---------" << std::endl;
    start = std::clock();
    solutions = forwardChecking(globalVars, globalContraintes);
    duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "Réalisé en " << duration << " secondes" << std::endl;
    for(unsigned i = 0; i < solutions.size(); ++i){
      std::cout << "Variable " << solutions[i]->getIdentifier() << " --> " << solutions[i]->getValue() << std::endl;
    }

    return 0;
}
