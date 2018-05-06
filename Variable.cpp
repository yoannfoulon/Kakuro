#include "Variable.hpp"

Variable::Variable(int identifier, std::vector<int> &domain, int value){
	this->m_identifier = identifier;
	this->m_domain = domain;
	this->m_value = value;
	this->m_domainSize = this->m_domain.size();
}

int Variable::getIdentifier(){
	return this->m_identifier;
}

void Variable::setIdentifier(int identifier){
	this->m_identifier = identifier;
}

std::vector<int> Variable::getDomain(){
	return this->m_domain;
}

void Variable::setDomain(std::vector<int> domain){
	this->m_domain = domain;
}

void Variable::addToDomain(int value){
	this->getDomain().push_back(value);
}

void Variable::removeFromDomain(int value){
	for(unsigned i = 0; i < this->getDomain().size(); ++i){
		if(this->getDomain()[i] == value){
			std::swap(this->getDomain()[i], this->getDomain()[this->getDomainSize() - 1]);
			this->setDomainSize(this->getDomainSize() - 1);
		}
	}
}

int Variable::getValue(){
	return this->m_value;
}

void Variable::setValue(int value){
	this->m_value = value;
}

int Variable::getDomainSize(){
	return this->m_domainSize;
}

void Variable::setDomainSize(int domainSize){
	this->m_domainSize = domainSize;
}

std::vector<int> Variable::getRemovedSizes(){
	return this->m_removedSizes;
}

int Variable::getNombreContraintes(){
	return this->m_nombreContraintes;
}

void Variable::setNombreContraintes(int nombreContraintes){
	this->m_nombreContraintes = nombreContraintes;
}

float Variable::getHeuristic(){
	return (float) this->m_domainSize / (float) this->m_nombreContraintes;
}

