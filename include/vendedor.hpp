#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP
#include "../include/pessoa.hpp"
#include "../include/funcionario.hpp"
#include "../include/util.hpp"

// classe filha que herda da classe Pessoa e Funcionario ao mesmo tempo
class Vendedor : public Pessoa, public Funcionario{
	char tipoVendedor;

	public:
	// construtor vazio
	Vendedor();

	//construtor parametrizado
	Vendedor(std::string nome, std::string cpf, Data dataNascimento, Endereco enderecoPessoal, std::string estadoCivil, int qtdFilhos, std::string salario, std::string matricula, Data ingressoEmpresa, char tipoVendedor, int diasFalta);

	// declaração das funções
	char getTipo();
    void setTipo(char tipoVendedor);
	float calcularSalario(int diasFalta);
    float calcularRescisao(Data desligamento);
};

#endif