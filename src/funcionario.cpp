#include <iostream>
#include "../include/funcionario.hpp"
using namespace std;

//gets e sets:

//salario
string Funcionario::getSalario(){
	return this->salario;
}
void Funcionario::setSalario(std::string salario){
	this->salario = salario;
}

//matricula
string Funcionario::getMatricula(){
	return this->matricula;
}
void Funcionario::setMatricula(std::string matricula){
	this->matricula = matricula;
}

//ingresso na empresa
Data Funcionario::getIngresso(){
	return this->ingressoEmpresa;
}
void Funcionario::setIngresso(Data ingressoEmpresa){
	this->ingressoEmpresa = ingressoEmpresa;
}

//dias que faltou
int Funcionario::getFaltas(){
	return this->diasFalta;
}
void Funcionario::setFaltas(int diasFalta){
	this->diasFalta = diasFalta;
}