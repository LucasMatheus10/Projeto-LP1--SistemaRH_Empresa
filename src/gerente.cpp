#include <iostream>
#include "../include/gerente.hpp"
using namespace std;

//construtor vazio
Gerente::Gerente(){}

//construtor parametrizado
Gerente::Gerente(string nome, string cpf, Data dataNascimento, Endereco enderecoPessoal, string estadoCivil, int qtdFilhos, string salario, string matricula, Data ingressoEmpresa, float participacaoLucros, int diasFalta){
	Gerente::setNome(nome);
	Gerente::setCpf(cpf);
	Gerente::setData(dataNascimento);
	Gerente::setEndereco(enderecoPessoal);
	Gerente::setEstadoCivil(estadoCivil);
	Gerente::setFilhos(qtdFilhos);
	Gerente::setSalario(salario);
	Gerente::setMatricula(matricula);
	Gerente::setIngresso(ingressoEmpresa);
	Gerente::setLucros(participacaoLucros);
	Gerente::setFaltas(diasFalta);
}

//get e set lucros
char Gerente::getLucros(){
	return this->participacaoLucros;
}
void Gerente::setLucros(float participacaoLucros){
	this->participacaoLucros = participacaoLucros;
}


//calculo do salario
float Gerente::calcularSalario(int diasFalta){
	float salario = ((stof(getSalario()) / 30) * (30 - diasFalta));
	salario += participacaoLucros;
	salario += getFilhos() * 100;
	return salario;
}

// função que calculaa rescisao
float Gerente::calcularRescisao(Data desligamento){
	// as variaveis guardam a data em que o gerente se desligou da empresa - a data de ingressão para contar o tempo que o gerente trabalhou na empresa
	int anosTrabalhados = desligamento.ano - getIngresso().ano;
    int mesesTrabalhados = desligamento.mes - getIngresso().mes;
    int diasTrabalhados = desligamento.dia - getIngresso().dia;

	// analisa se obteve um número negativo, se sim significa que não trabalhou um ano completo e então decrementamos a variavel que guarda os anos trabalhados inteiros
    if (mesesTrabalhados < 0 || (mesesTrabalhados == 0 && diasTrabalhados < 0)){
        anosTrabalhados--;
		mesesTrabalhados += 12;
    }
	
	// calculo de tempo liquido em anos
    float anosFracionados = anosTrabalhados + (mesesTrabalhados / 12.0f) + (diasTrabalhados / 365.0f);

	// aqui é o calculo do salario minimo por ano
    float salarioBasePorAno = calcularSalario(0) * 12;

	// calculo da rescisao do contrato do funcionario 
    float rescisao = salarioBasePorAno * anosFracionados;

    return rescisao;
}