#include "ContrainteSomme.hpp"

ContrainteSomme::ContrainteSomme(std::vector<Variable*> variables, int arite, int resultat)
	: Contrainte::Contrainte(variables, arite), m_resultat(resultat){}

bool ContrainteSomme::evaluation(){
	int somme = 0;
	for(Variable* v : this->getVariables()){
		somme += v->getValue();
	}
	if(m_resultat == somme){
		return true;
	}
	return false;
}

std::string ContrainteSomme::getType(){
	return "ContrainteSomme";
}

int ContrainteSomme::getResultat(){
	return this->m_resultat;
}

void ContrainteSomme::remove(Variable *currentVar, Variable *v2, int *removedSize){
	for(int i = 0; i < v2->getDomainSize(); ++i){
		printf("%d + %d = %d ", v2->getDomain()[i], currentVar->getValue(), this->getResultat());
		if((v2->getDomain()[i] + currentVar->getValue()) > this->getResultat()){
			printf("Removed from %d domain", v2->getIdentifier());
			v2->removeFromDomain(v2->getDomain()[i]);
			--i;
			++*removedSize;
		}
		printf("\n");
	}
}
