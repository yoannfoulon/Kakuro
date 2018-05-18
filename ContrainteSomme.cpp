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
	int currentResult = 0;
	int nbValued = 0;
	for(int i = 0; i < this->m_variables.size(); ++i){
		if(this->m_variables[i]->getValue() != 0){
			++nbValued;
			currentResult += this->m_variables[i]->getValue();
		}
	}

	//std::cout << "nbVars: " << this->getVariables().size() << std::endl;
	//std::cout << "nbValued: " << nbValued << std::endl;
	//std::cout << "currentResult: " << currentResult << std::endl;
	//std::cout << "Resultat attendu: " << this->getResultat() << std::endl;

	if(nbValued == this->m_variables.size() - 1){
		int result = this->getResultat() - currentResult;
		for(int i = 0; i < v2->getDomainSize(); ++i){
			if(v2->getDomain()[i] != result){
				v2->removeFromDomain(v2->getDomain()[i]);
				--i;
				++*removedSize;
			}
		}
	}

	else{
		for(int i = 0; i < v2->getDomainSize(); ++i){
		std::cout << v2->getDomain()[i] << "+" << currentResult << "=" << v2->getDomain()[i] + currentResult << std::endl;
		if(v2->getDomain()[i] + currentResult > this->getResultat()){
			v2->removeFromDomain(v2->getDomain()[i]);
			--i;
			++*removedSize;
		}
	}
	}
}
