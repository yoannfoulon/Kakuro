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
	return "ContrainteSomme : " + std::to_string(m_resultat);
}
