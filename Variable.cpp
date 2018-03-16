#include "Variable.hpp"

Variable::Variable(int identifier, std::vector<int> domain, int value){
	this->m_identifier = identifier;
	this->m_domain = domain;
	this->m_value = value;
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
	for(size_t i = 0; i < this->getDomain().size(); ++i){
		if(this->getDomain()[i] == value){
			this->getDomain().erase(this->getDomain().begin() + i);
		}
	}
}

int Variable::getValue(){
	return this->m_value;
}

void Variable::setValue(int value){
	this->m_value = value;
}
