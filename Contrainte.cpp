#include "Contrainte.hpp"

Contrainte::Contrainte(std::vector<Variable*> variables, int arite){
	this->m_variables = variables;
	this->m_arite = arite;
}

std::vector<Variable*> Contrainte::getVariables(){
	return this->m_variables;
}

void Contrainte::setVariables(std::vector<Variable*> variables){
	this->m_variables = variables;
}

void Contrainte::addVariable(Variable* variable){
	this->m_variables.push_back(variable);
}

int Contrainte::getArite(){
	return this->m_arite;
}

void Contrainte::setArite(int arite){
	this->m_arite = arite;
}
