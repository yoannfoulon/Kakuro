#include "parser.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf (stderr,"Utilisation: %s fichier\n",argv[0]);
    exit (-1);
  }

  std::vector<Variable*> globalVars;
  std::vector<Contrainte*> globalContraintes;
  std::vector<int> domain = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  parse (argv[1], globalVars, globalContraintes, domain);

  std::cout << "----------------- VARIABLES -------------------" << "\n";

  for(unsigned i = 0; i < globalVars.size(); ++i){
     std::cout << "Variable " << globalVars[i]->getIdentifier() << " -> " << globalVars[i]->getValue() << "\n";
  }

  std::cout << "----------------- CONTRAINTES -------------------" << "\n";

  for(unsigned i = 0; i < globalContraintes.size(); ++i){
      std::cout << globalContraintes[i]->getType() << "\n";
      for(unsigned j = 0; j < globalContraintes[i]->getVariables().size(); ++j){
         std::cout << "Variable " << globalContraintes[i]->getVariables()[j]->getIdentifier() << " -> " << globalContraintes[i]->getVariables()[j]->getValue() << "\n";
      }
     std::cout << "Arité " << globalContraintes[i]->getArite() << "\n\n";
  }

  return 0;
}
