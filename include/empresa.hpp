#ifndef EMPRESA_HPP
#define EMPRESA_HPP
#include <vector>
#include "../include/pessoa.hpp"
#include "../include/funcionario.hpp"
#include "../include/asg.hpp"
#include "../include/vendedor.hpp"
#include "../include/gerente.hpp"

class Empresa{
    float faturamentoMensal;
    std::string nomeEmpresa;
    std::string cnpj;
	Pessoa dono;
	std::vector<Asg> asgs;
	std::vector<Vendedor> vendedores;
	std::vector<Gerente> gerentes;
    
	public:
	
	// construtor vazio
	Empresa();

	// construtor parametrizado
	Empresa(std::string nomeEmpresa, std::string cnpj, float faturamentoMensal);
	
	// declaração de funções
	float getFaturamentoMensal();
	void setFaturamentoMensal(float faturamentoMensal);
	string getNomeEmpresa();
	void setNomeEmpresa(std::string nomeEmpresa);
	string getCnpj();
	void setCnpj(std::string cnpj);
	Pessoa getDono();
	vector<Gerente>& getGerentes();
	vector<Asg>& getAsgs();
	vector<Vendedor>& getVendedores();
	void carregaFuncoes();
	void carregarEmpresa();
	void carregarAsg();
	void carregarVendedor();
	void carregarGerente();
	void carregaDono();
	void imprimeAsgs();
	void imprimeVendedores();
	void imprimeGerentes();
	void imprimeDono();
	bool buscaFuncionario(std::string matricula);
	bool calculaSalarioFuncionario(std::string matricula);
	void calculaTodoOsSalarios();
	bool calcularRescisao(std::string matricula, Data desligamento);
	void demitirFuncionario(std::string matricula,Data desligamento);
	void contratarFuncionario();
};

#endif
