#ifndef GERENTE_HPP
#define GERENTE_HPP
#include "../include/pessoa.hpp"
#include "../include/funcionario.hpp"
#include "../include/util.hpp"

// classe filha que herda da classe Pessoa e Funcionario ao mesmo tempo
class Gerente : public Pessoa, public Funcionario{
	float participacaoLucros;

	public:
	//construtor vazio
	Gerente();

	//construtor parametrizado
	Gerente(std::string nome, std::string cpf, Data dataNascimento, Endereco enderecoPessoal, std::string estadoCivil, int qtdFilhos, std::string salario, std::string matricula, Data ingressoEmpresa, float participacaoLucros, int diasFalta);
	
	// declaração de funções 
	char getLucros();
    void setLucros(float participacaoLucros);
	float calcularSalario(int diasFalta);
    float calcularRescisao(Data desligamento);
};

#endif