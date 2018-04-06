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

void ContrainteSomme::remove(Variable *v){
	bool isInVars = false;
	for(unsigned i = 0; i < this->getVariables().size(); ++i){
		if(this->getVariables()[i]->getIdentifier() == v->getIdentifier()){
			isInVars = true;
			break;
		}
	}
	if(isInVars){
		for(unsigned i = 0; i < this->getVariables().size(); ++i){
			if(this->getVariables()[i]->getIdentifier() != v->getIdentifier()){
				int removedSize;
				for(int j = 0; j < this->getVariables()[j]->getDomainSize(); ++j){
					if((this->getVariables()[i]->getDomain()[j] + v->getValue()) > this->getResultat()){
						this->getVariables()[i]->removeFromDomain(this->getVariables()[i]->getDomain()[j]);
						++removedSize;
					}
				}
				this->getVariables()[i]->getRemovedSizes().push_back(removedSize);
			}
		}
	}
}
