#pragma once
#include <stdlib.h>
#include <vector>
#include <string>

class Variable{
	private:
		int m_identifier;
		std::vector<int> m_domain;
		int m_value;
	public:
		Variable(int identifier, std::vector<int> domain, int value);
		int getIdentifier();
		void setIdentifier(int identifier);
		std::vector<int> getDomain();
		void setDomain(std::vector<int> domain);
		void addToDomain(int value);
		void removeFromDomain(int value);
		int getValue();
		void setValue(int value);
};
