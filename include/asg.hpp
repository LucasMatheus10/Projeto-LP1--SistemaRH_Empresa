#ifndef ASG_HPP
#define ASG_HPP
#include "../include/pessoa.hpp"
#include "../include/funcionario.hpp"
#include "../include/util.hpp"

class Asg : public Pessoa, public Funcionario {
    float adicionalInsalubridade;
	int diasFalta;

	public:
	// construtor vazio
    Asg();

	// construtor parametrizado
    Asg(std::string nome, std::string cpf, Data dataNascimento, Endereco enderecoPessoal, std::string estadoCivil, int qtdFilhos, std::string salario, std::string matricula, Data dataIngresso, float adicionalInsalubridade);
    
	// declaração das funções 
	float getAdicional();
    void setAdicional(float adicionalInsalubridade);
    float calcularSalario(int diasFalta);
    float calcularRescisao(Data desligamento);
};

#endif