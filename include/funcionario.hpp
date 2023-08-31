#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP
#include "../include/pessoa.hpp"
#include "../include/util.hpp"

// classe mãe que cria um funcionário
class Funcionario{
	// declaração de variáveis com informações de um funcionário
	string salario;
	string matricula;
	Data ingressoEmpresa;
	int diasFalta;

	public:
	
	// declaração de funções
	string getSalario();
    void setSalario(std::string salario);
    string getMatricula();
    void setMatricula(std::string matricula);
	Data getIngresso();
	void setIngresso(Data ingressoEmpresa);
	int getFaltas();
    void setFaltas(int diasFalta);
    virtual float calcularSalario(int diasFalta) = 0;
    virtual float calcularRescisao(Data desligamento) = 0;
	
};

#endif