#ifndef UTIL_HPP
#define UTIL_HPP
using namespace std;

// struct de tipo Data
struct Data{
	int ano;
	int mes;
	int dia;
};

// struct de tipo Endereco
struct Endereco{
	std::string cidade;
	std::string bairro;
	std::string rua;
	std::string cep;
	int numero;
};

#endif