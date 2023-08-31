#ifndef PESSOA_HPP
#define PESSOA_HPP
#include "../include/util.hpp"
#include "../include/funcionario.hpp"

// classe mãe para criar uma pessoa
class Pessoa{
	// variáveis com informações de uma pessoa a ser criada
	std::string nome;
	std::string cpf;
	Data dataNascimento;
	Endereco enderecoPessoal;
	std::string estadoCivil;
	int qtdFilhos;

	public:
	//construtor vazio
	Pessoa();

	//construtor parametrizado
	Pessoa(std::string nome, std::string cpf, Data dataNascimento, Endereco enderecoPessoal, std::string estadoCivil, int qtdFilhos);

	// declaração das funções 
	std::string getNome();
    void setNome(std::string nome);
    std::string getCpf();
    void setCpf(std::string cpf);
	Data getData();
	void setData(Data dataNascimento);
	Endereco getEndereco();
	void setEndereco(Endereco enderecoPessoal);
	std::string getEstadoCivil();
	void setEstadoCivil(std::string estadoCivil);
	int getFilhos();
	void setFilhos(int qtdFilhos);
};

#endif