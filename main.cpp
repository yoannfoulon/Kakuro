#include "parser.hpp"
#include "algorithm.hpp"
#include "utils.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ctime>


int main (int argc, char *argv[]) {

    bool BT, FC, FCH;

    if (argc < 2) {
        fprintf (stderr,"Utilisation: %s [-bt] [-fc] [-fch] <fichier>\n", argv[0]);
        exit (-1);
    }

    for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-bt") == 0)
			BT = true;
		if (strcmp(argv[i], "-fc") == 0)
			FC = true;
		if (strcmp(argv[i], "-fch") == 0)
			FCH = true;
	}

    std::vector<Variable*> globalVars;
    std::vector<Contrainte*> globalContraintes;
    std::vector<int> domain = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    long nbNoeuds = 0;
    long nbTests = 0;
    std::clock_t start;
    double duration;

    std::vector<Variable*> solutions;

    parse(argv[argc-1], globalVars, globalContraintes, domain);
    displayCSP(globalVars, globalContraintes);

    if(BT){
        std::cout << "--------- BACKTRACK ---------" << std::endl;
        start = std::clock();
        solutions = backTrack(globalVars, globalContraintes, &nbNoeuds, &nbTests);
        duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;

        std::cout << "Réalisé en " << duration << " secondes" << std::endl;
        std::cout << nbNoeuds << " noeuds" << std::endl;
        std::cout << nbTests << " tests de contrainte" << std::endl;

        for(unsigned i = 0; i < solutions.size(); ++i){
            std::cout << "Variable " << solutions[i]->getIdentifier() << " --> " << solutions[i]->getValue() << std::endl;
        }
    }

    if(FC){
        std::cout << "--------- FORWARD CHECKING ---------" << std::endl;
        start = std::clock();
        solutions = forwardChecking(globalVars, globalContraintes, &nbNoeuds, &nbTests);
        duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;

        std::cout << "Réalisé en " << duration << " secondes" << std::endl;
        std::cout << nbNoeuds << " noeuds" << std::endl;
        std::cout << nbTests << " tests de contrainte" << std::endl;
        
        for(unsigned i = 0; i < solutions.size(); ++i){
          std::cout << "Variable " << solutions[i]->getIdentifier() << " --> " << solutions[i]->getValue() << std::endl;
        }
    }
    return 0;
}
