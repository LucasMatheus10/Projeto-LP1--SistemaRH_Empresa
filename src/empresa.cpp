#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "../include/empresa.hpp"
using namespace std;

//construtor vazio
Empresa::Empresa(){}

//construtor parametrizado
Empresa::Empresa(string nomeEmpresa, string cnpj, float faturamentoMensal){
	Empresa::setNomeEmpresa(nomeEmpresa);
	Empresa::setCnpj(cnpj);
	Empresa::setFaturamentoMensal(faturamentoMensal);
}

//gets e sets:
//faturamento mensal
float Empresa::getFaturamentoMensal(){
	return this->faturamentoMensal;
}
void Empresa::setFaturamentoMensal(float faturamentoMensal){
	this->faturamentoMensal = faturamentoMensal;
}

//nome da empresa
string Empresa::getNomeEmpresa(){
	return this->nomeEmpresa;
}
void Empresa::setNomeEmpresa(string nomeEmpresa){
	this->nomeEmpresa = nomeEmpresa;
}

//cnpj
string Empresa::getCnpj(){
	return this->cnpj;
}
void Empresa::setCnpj(string cnpj){
	this->cnpj = cnpj;
}

//dono da empresa
Pessoa Empresa::getDono(){
	return this->dono;
}

//gerentes
vector<Gerente>& Empresa::getGerentes(){
	return this->gerentes;
}

//asgs
vector<Asg>& Empresa::getAsgs(){
	return this->asgs;
}

//vendedores
vector<Vendedor>& Empresa::getVendedores(){
	return this->vendedores;
}

//funcao para carregar todas as funcoes
void Empresa::carregaFuncoes() {
    try {
        fstream arquivo;
        arquivo.open("funcoes.txt", ios::in);
        vector<string> temp;
        string linha;

        while (getline(arquivo, linha)) {
            temp.push_back(linha);
        }

        arquivo.close();

        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == "carregarEmpresa()") {
                cout << "\nCarregando empresa..." << endl;
                carregarEmpresa();
            } else if (temp[i] == "carregarAsg()") {
                cout << "\nCarregando asgs..." << endl;
                carregarAsg();
            } else if (temp[i] == "carregarVendedor()") {
                cout << "\nCarregando vendedores..." << endl;
                carregarVendedor();
            } else if (temp[i] == "carregarGerente()") {
                cout << "\nCarregando gerentes..." << endl;
                carregarGerente();
            } else if (temp[i] == "carregaDono()") {
                cout << "\nCarregando dono..." << endl;
                carregaDono();
            } else if (temp[i] == "imprimeAsgs()") {
                imprimeAsgs();
            } else if (temp[i] == "imprimeVendedores()") {
                imprimeVendedores();
            } else if (temp[i] == "imprimeGerentes()") {
                imprimeGerentes();
            } else if (temp[i] == "imprimeDono()") {
                imprimeDono();
            } else if (temp[i] == "buscaFuncionario()") {
				string matricula = temp[i + 1];
				i++;
				buscaFuncionario(matricula);
            } else if (temp[i] == "calculaSalarioFuncionario()") {
					string matricula = temp[i + 1];
					i++;
					calculaSalarioFuncionario(matricula);
            } else if (temp[i] == "calculaTodoOsSalarios()") {
                calculaTodoOsSalarios();
            } else if (temp[i] == "calcularRescisao()") {
				string matricula = temp[i + 1];
				Data desligamento;
				desligamento.ano = stoi(temp[i + 2]);
				desligamento.mes = stoi(temp[i + 3]);
				desligamento.dia = stoi(temp[i + 4]);
				i += 4;
				calcularRescisao(matricula, desligamento);
            } else if (temp[i] == "demitirFuncionario()") {
				string matricula = temp[i + 1];
				Data desligamento;
				desligamento.ano = stoi(temp[i + 2]);
				desligamento.mes = stoi(temp[i + 3]);
				desligamento.dia = stoi(temp[i + 4]);
				i += 4;
				demitirFuncionario(matricula, desligamento);
            } else if (temp[i] == "contratarFuncionario()") {
                contratarFuncionario();
            }
        }
    } catch (exception &erro) {
        cout << "Não foi possível abrir o arquivo de funções. Erro: " << erro.what() << endl;
    }
}

// função para carregar a empresa com as suas informações
void Empresa::carregarEmpresa(){
	ifstream arquivo("empresa.txt");
    if (!arquivo.is_open()){
        cout << "Erro ao tentar abrir o arquivo!!" << std::endl;
        return;
	}

    string linha;
	Empresa* empresa = new Empresa;

    while (getline(arquivo, linha)){
    	if (linha.find("DADOS DA EMPRESA:") != string::npos){
        	getline(arquivo, linha); //leitura do nome da empresa
        	empresa->setNomeEmpresa(linha);
        	
			getline(arquivo, linha); //leitura do cnpj
        	empresa->setCnpj(linha);
        	
			getline(arquivo, linha); //leitura do faturamento mensal
        	empresa->setFaturamentoMensal(stof(linha));
        }
    }
    arquivo.close();
}

// função para carregar os asgs da empresa
void Empresa::carregarAsg(){
	ifstream arquivo("asg.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao tentar abrir o arquivo!!" << std::endl;
        return;
	}

    string linha;
    Asg asg;

    while (getline(arquivo, linha)) {
    if (linha.find("ASG Nº") != string::npos) {
        
		getline(arquivo, linha); //ignora uma linha
        
		getline(arquivo, linha); //leitura do nome
        asg.setNome(linha);
        
		getline(arquivo, linha); //leitura do cpf
        asg.setCpf(linha);
        
		getline(arquivo, linha); //leitura da quantidade de filhos
        asg.setFilhos(stoi(linha));
        
		getline(arquivo, linha); //leitura do estado civil
        asg.setEstadoCivil(linha);
        
		getline(arquivo, linha); 
        
		getline(arquivo, linha); //leitura da cidade
        string cidade = linha;
        
		getline(arquivo, linha); //leitura do cep
        string cep = linha;
        
		getline(arquivo, linha); //leitura do bairro
        string bairro = linha;
        
		getline(arquivo, linha); //leitura da rua
        string rua = linha;
        
		getline(arquivo, linha); //leitura do nº da casa
        int numero = stoi(linha);
        Endereco endereco{cidade, bairro, rua, cep, numero};
        asg.setEndereco(endereco);
        
		getline(arquivo, linha);
        
		getline(arquivo, linha); //leitura do ano que nasceu
        int anoNascimento = stoi(linha);
        
		getline(arquivo, linha); //leitura do mes
        int mesNascimento = stoi(linha);
        
		getline(arquivo, linha); //leitura do dia
        int diaNascimento = stoi(linha);
        Data dataNascimento{anoNascimento, mesNascimento, diaNascimento};
        asg.setData(dataNascimento);
        
		getline(arquivo, linha);
        
		getline(arquivo, linha); //leitura da matricula
        asg.setMatricula(linha);
        
		getline(arquivo, linha); //leitura do salario
        asg.setSalario(linha);
        
		getline(arquivo, linha); //leitura da taxa de insalubridade
        asg.setAdicional(stof(linha));
        
		getline(arquivo, linha); //leitura dos dias que ele(a) faltou
		asg.setFaltas(stoi(linha));
        
		getline(arquivo, linha);
        
		getline(arquivo, linha); //leitura do ano de ingresso na empresa
        int anoIngresso = stoi(linha);
        
		getline(arquivo, linha); //leitura do mes
        int mesIngresso = stoi(linha);
        
		getline(arquivo, linha); //leitura do dia
        int diaIngresso = stoi(linha);
        Data dataIngresso{anoIngresso, mesIngresso, diaIngresso};
        asg.setIngresso(dataIngresso);
        asgs.push_back(asg);
        }
    }
    arquivo.close();
	
}

// função para carregar os vendedores da empresa
void Empresa::carregarVendedor(){
	ifstream arquivo("vendedor.txt");
    if (!arquivo.is_open()){
        cout << "Erro ao abrir o arquivo." << std::endl;
        return;
	}

    string linha;
    Vendedor vendedor;

    while (getline(arquivo, linha)){
    if (linha.find("VENDEDOR Nº") != string::npos){
        getline(arquivo, linha); //ignora uma linha
        
		getline(arquivo, linha); //leitura do nome
        vendedor.setNome(linha);
        
		getline(arquivo, linha); ///leitura do cpf
        vendedor.setCpf(linha);
        
		getline(arquivo, linha); //leitura da quantidade de filhos
        vendedor.setFilhos(stoi(linha));
        
		getline(arquivo, linha); //leitura do estado civil
        vendedor.setEstadoCivil(linha);
        
		getline(arquivo, linha);
        
		getline(arquivo, linha); //leitura da cidade
        string cidade = linha;
        
		getline(arquivo, linha); //leitura do cep
        string cep = linha;
        
		getline(arquivo, linha); //leitura do bairro
        string bairro = linha;
        
		getline(arquivo, linha); //leitura da rua
        string rua = linha;
        
		getline(arquivo, linha); //leitura do nº da casa
        int numero = stoi(linha);
        Endereco endereco{cidade, bairro, rua, cep, numero};
        vendedor.setEndereco(endereco);
        
		getline(arquivo, linha); 
        
		getline(arquivo, linha); //leitura do ano que nasceu
        int anoNascimento = stoi(linha);
        
		getline(arquivo, linha); //leitura do mes
        int mesNascimento = stoi(linha);
        
		getline(arquivo, linha); //leitura do dia
        int diaNascimento = stoi(linha);
        Data dataNascimento{anoNascimento, mesNascimento, diaNascimento};
        vendedor.setData(dataNascimento);
        
		getline(arquivo, linha);
        
		getline(arquivo, linha); //leitura da matricula
        vendedor.setMatricula(linha);
        
		getline(arquivo, linha); //leitura do salario
        vendedor.setSalario(linha);
        
		getline(arquivo, linha); //leitura do tipo do vendedor
		char tipo = linha.front();
        vendedor.setTipo(tipo);
        
		getline(arquivo, linha); //leitura dos dias que ele(a) faltou
		vendedor.setFaltas(stoi(linha));
        
		getline(arquivo, linha); 
        
		getline(arquivo, linha); //leitura do ano de ingresso na empresa
        int anoIngresso = stoi(linha);
        
		getline(arquivo, linha); //leitura do mes
        int mesIngresso = stoi(linha);
        
		getline(arquivo, linha); //leitura do dia
        int diaIngresso = stoi(linha);
        Data dataIngresso{anoIngresso, mesIngresso, diaIngresso};
        vendedor.setIngresso(dataIngresso);
        vendedores.push_back(vendedor);
        }
    }
    arquivo.close();
	
}
// função para carregar os gerentes da empresa
void Empresa::carregarGerente(){
	ifstream arquivo("gerente.txt");
    if (!arquivo.is_open()){
        cout << "Erro ao tentar abrir o arquivo!!" << std::endl;
        return;
    }

    string linha;
    Gerente gerente;

    while (getline(arquivo, linha)){
    if (linha.find("GERENTE Nº") != string::npos){
        getline(arquivo, linha); //ignora uma linha
        
		getline(arquivo, linha); //leitura do nome
        gerente.setNome(linha);
        
		getline(arquivo, linha); //leitura do cpf
        gerente.setCpf(linha);
        
		getline(arquivo, linha); //leitura da quantidade de filhos
        gerente.setFilhos(stoi(linha));
        
		getline(arquivo, linha); //leitura do estado civil
        gerente.setEstadoCivil(linha);
        
		getline(arquivo, linha); 
        
		getline(arquivo, linha); //leitura da cidade
        string cidade = linha;
        
		getline(arquivo, linha); //leitura do cep
        string cep = linha;
        
		getline(arquivo, linha); //leitura do bairro
        string bairro = linha;
        
		getline(arquivo, linha); //leitura da rua
        string rua = linha;
        
		getline(arquivo, linha); //leitura do nº da casa
        int numero = stoi(linha);
        Endereco endereco{cidade, bairro, rua, cep, numero};
        gerente.setEndereco(endereco);
        
		getline(arquivo, linha); 
        
		getline(arquivo, linha); //leitura do ano que nasceu
        int anoNascimento = stoi(linha);
        
		getline(arquivo, linha); //leitura do mes
        int mesNascimento = stoi(linha);
        
		getline(arquivo, linha); //leitura do dia
        int diaNascimento = stoi(linha);
        Data dataNascimento{anoNascimento, mesNascimento, diaNascimento};
        gerente.setData(dataNascimento);
        
		getline(arquivo, linha); 
        
		getline(arquivo, linha); //leitura da matricula
        gerente.setMatricula(linha);
        
		getline(arquivo, linha); //leitura do salario
        gerente.setSalario(linha);
        
		getline(arquivo, linha); //leitura da partic nos lucros
        gerente.setLucros(stof(linha));
        
		getline(arquivo, linha); //leitura dos dias que ele(a) faltou
		gerente.setFaltas(stoi(linha));
        
		getline(arquivo, linha); 

		getline(arquivo, linha); //leitura do ano de ingresso na empresa
        int anoIngresso = stoi(linha);
        
		getline(arquivo, linha); //leitura do mes
        int mesIngresso = stoi(linha);
        
		getline(arquivo, linha); //leitura do dia
        int diaIngresso = stoi(linha);
        Data dataIngresso{anoIngresso, mesIngresso, diaIngresso};
        gerente.setIngresso(dataIngresso);
        gerentes.push_back(gerente);
        }
    }
    arquivo.close();
}
// função para carregar o Dono da empresa
void Empresa::carregaDono(){
    ifstream arquivo("dono.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao tentar abrir o arquivo!!" << std::endl;
        return;
    }

    string linha;

    while (getline(arquivo, linha)){
        if (linha.find("DADOS PESSOAIS DO DONO") != string::npos){
            getline(arquivo, linha); //leitura do nome
            dono.setNome(linha);
            
			getline(arquivo, linha); //leitura do cpf
            dono.setCpf(linha);
            
			getline(arquivo, linha); //leitura da quantidade de filhos
            dono.setFilhos(stoi(linha));
            
			getline(arquivo, linha); //leitura do estado civil
            dono.setEstadoCivil(linha);
            
			getline(arquivo, linha); //leitura da cidade
            string cidade = linha;
            
			getline(arquivo, linha); //leitura do cep
            string cep = linha;
            
			getline(arquivo, linha); //leitura do bairro
            string bairro = linha;
            
			getline(arquivo, linha); //leitura da rua
            string rua = linha;
            
			getline(arquivo, linha); //leitura do nº da casa
            int numero = stoi(linha);
            Endereco endereco{cidade, bairro, rua, cep, numero};
            dono.setEndereco(endereco);
            
			getline(arquivo, linha); //leitura do ano que nasceu
            int anoNascimento = stoi(linha);
            
			getline(arquivo, linha); //leitura do mes
            int mesNascimento = stoi(linha);
            
			getline(arquivo, linha); //leitura do dia
            int diaNascimento = stoi(linha);
            Data dataNascimento{anoNascimento, mesNascimento, diaNascimento};
            dono.setData(dataNascimento);
        }
    }
    arquivo.close();
}

// função para imprimir os asgs com suas informações
void Empresa::imprimeAsgs(){
	cout << "\n-------------> Lista de Asgs <-------------" << endl << endl;
    for (Asg& asg : asgs) {
        cout << "Nome: " << asg.getNome() << endl;
        cout << "CPF: " << asg.getCpf() << endl;
        cout << "Número de filhos: " << asg.getFilhos() << endl;
        cout << "Estado civil: " << asg.getEstadoCivil() << endl;
        cout << "Cidade: " << asg.getEndereco().cidade << endl;
		cout << "CEP: " << asg.getEndereco().cep << endl;
		cout << "Bairro: " << asg.getEndereco().bairro << endl;
		cout << "Rua: " << asg.getEndereco().rua << endl;
		cout << "Número da casa: " << asg.getEndereco().numero << endl;
		cout << "Data de nascimento: " << asg.getData().dia << "/";
		cout << asg.getData().mes << "/";
		cout << asg.getData().ano << endl;
        cout << "Matrícula: " << asg.getMatricula() << endl;
        cout << "Salário: R$" << asg.getSalario() << endl;
        cout << "Adicional de insalubridade: " << asg.getAdicional() << endl;
		cout << "Faltas: " << asg.getFaltas() << endl;
        cout << "Data de ingresso: " << asg.getIngresso().dia << "/";
		cout << asg.getIngresso().mes << "/";
		cout << asg.getIngresso().ano << endl;
        cout << endl << "##################################" << endl << endl;
    }
}

// função para imprimir os vendedores com suas informações
void Empresa::imprimeVendedores(){
	cout << "\n-------------> Lista de Vendedores <-------------" << endl << endl;
    for (Vendedor& vendedor : vendedores) {
        cout << "Nome: " << vendedor.getNome() << endl;
        cout << "CPF: " << vendedor.getCpf() << endl;
        cout << "Número de filhos: " << vendedor.getFilhos() << endl;
        cout << "Estado civil: " << vendedor.getEstadoCivil() << endl;
        cout << "Cidade: " << vendedor.getEndereco().cidade << endl;
		cout << "CEP: " << vendedor.getEndereco().cep << endl;
		cout << "Bairro: " << vendedor.getEndereco().bairro << endl;
		cout << "Rua: " << vendedor.getEndereco().rua << endl;
		cout << "Número da casa: " << vendedor.getEndereco().numero << endl;
		cout << "Data de nascimento: " << vendedor.getData().dia << "/";
		cout << vendedor.getData().mes << "/";
		cout << vendedor.getData().ano << endl;
        cout << "Matrícula: " << vendedor.getMatricula() << endl;
        cout << "Salário: R$" << vendedor.getSalario() << endl;
        cout << "Tipo do vendedor: " << vendedor.getTipo() << endl;
		cout << "Faltas: " << vendedor.getFaltas() << endl;
        cout << "Data de ingresso: " << vendedor.getIngresso().dia << "/";
		cout << vendedor.getIngresso().mes << "/";
		cout << vendedor.getIngresso().ano << endl;
        cout << endl << "##################################" << endl << endl;
    }
}

// função para imprimir os gerentes com suas informações
void Empresa::imprimeGerentes(){
	cout << "\n-------------> Lista de Gerentes <-------------" << endl << endl;
    for (Gerente& gerente : gerentes) {
        cout << "Nome: " << gerente.getNome() << endl;
        cout << "CPF: " << gerente.getCpf() << endl;
        cout << "Número de filhos: " << gerente.getFilhos() << endl;
        cout << "Estado civil: " << gerente.getEstadoCivil() << endl;
        cout << "Cidade: " << gerente.getEndereco().cidade << endl;
		cout << "CEP: " << gerente.getEndereco().cep << endl;
		cout << "Bairro: " << gerente.getEndereco().bairro << endl;
		cout << "Rua: " << gerente.getEndereco().rua << endl;
		cout << "Número da casa: " << gerente.getEndereco().numero << endl;
		cout << "Data de nascimento: " << gerente.getData().dia << "/";
		cout << gerente.getData().mes << "/";
		cout << gerente.getData().ano << endl;
        cout << "Matrícula: " << gerente.getMatricula() << endl;
        cout << "Salário: R$" << gerente.getSalario() << endl;
        cout << "Participação nos lucros: " << gerente.getLucros() << endl;
        cout << "Faltas: " << gerente.getFaltas() << endl;
        cout << "Data de ingresso: " << gerente.getIngresso().dia << "/";
		cout << gerente.getIngresso().mes << "/";
		cout << gerente.getIngresso().ano << endl;
        cout << endl <<"##################################" << endl << endl;
    }
}

// função para imprimir o dono da empresa com suas informações
void Empresa::imprimeDono(){
	cout << endl << "-------------> Dono <-------------" << endl << endl;
    cout << "Nome: " << dono.getNome() << endl;
	cout << "CPF: " << dono.getCpf() << endl;
	cout << "Número de filhos: " << dono.getFilhos() << endl;
	cout << "Estado civil: " << dono.getEstadoCivil() << endl;
	cout << "Cidade: " << dono.getEndereco().cidade << endl;
	cout << "CEP: " << dono.getEndereco().cep << endl;
	cout << "Bairro: " << dono.getEndereco().bairro << endl;
	cout << "Rua: " << dono.getEndereco().rua << endl;
	cout << "Número da casa: " << dono.getEndereco().numero << endl;
	cout << "Data de nascimento: " << dono.getData().dia << "/";
	cout << dono.getData().mes << "/";
	cout << dono.getData().ano << endl;
	cout << endl << "##################################" << endl << endl;
}

// função de busca dos funcionarios por matriculas
bool Empresa::buscaFuncionario(string matricula){	
	
	for (auto asg : asgs) {
        if (asg.getMatricula() == matricula) {
            return true;
        }
    }

    for (auto vendedor : vendedores) {
        if (vendedor.getMatricula() == matricula) {
            return true;
        }
    }

    for (auto gerente : gerentes) {
        if (gerente.getMatricula() == matricula) {
            return true;
        }
    }

	cout << "Funcionário não encontrado no sistema";
	cout << "##################################" << endl << endl;
}


// função para calcular salario do funcionario
bool Empresa::calculaSalarioFuncionario(string matricula){
	
	cout << endl << "Busca salário de um funcionário:" << endl << endl;

	for (auto asg : asgs){
        if (asg.getMatricula() == matricula){
			// salA - salario do asg
			float salA = asg.calcularSalario(asg.getFaltas());
			cout << "Salário: R$" << salA << endl;
			cout << endl << "##################################" << endl << endl;
            return true;
        }
    }

    for (auto vendedor : vendedores){
        if (vendedor.getMatricula() == matricula){
			// salV - salario do vendedor
			float salV = vendedor.calcularSalario(vendedor.getFaltas());
			cout << "Salário: R$" << salV << endl;
			cout << endl << "##################################" << endl << endl;
            return true;
        }
    }

    for (auto gerente : gerentes){
        if (gerente.getMatricula() == matricula){
			// salG - salario do gerente
			float salG = gerente.calcularSalario(gerente.getFaltas());
			cout << "Salário: R$" << salG << endl;
			cout << endl << "##################################" << endl << endl;
            return true;
        }
    }
	cout << "Funcionário não encontrado no sistema";
	cout << "##################################" << endl;
}

void Empresa::calculaTodoOsSalarios(){
	// declaração das variáveis dos salários dos funcionários
	float totalAsg = 0.0;
    float totalVendedor = 0.0;
    float totalGerente = 0.0;
    float total = 0.0;
	
	cout << "\nCálculo de todos os Salarios:" << endl << endl;

    // criação do arquivo
    fstream arquivo;
    arquivo.open("relatórioFinanceiro.txt", ios::out);
    arquivo << "######### Relatório Financeiro ########" << endl << endl;
	
    arquivo << "Cargo: ASG" << endl;
	// calcula o total de salario de todos os asgs e escreve no arquivo
	for(auto i : asgs){
        arquivo << i.getMatricula() << " - " << i.getNome() << " - " << i.getSalario() << endl;
        totalAsg += stof(i.getSalario());
	}
	arquivo << "Total ASG: " << totalAsg << endl;
    

    arquivo << "Cargo: VENDEDOR" << endl;
	// calcula o total de salario de todos os vendedores e escreve no arquivo
	for(auto i : vendedores){
		arquivo << i.getMatricula() << " - " << i.getNome() << " - " << i.getSalario() << endl;
		totalVendedor += stof(i.getSalario());
	}
	arquivo << "Total VENDEDOR: " << totalVendedor << endl;
  
	arquivo << "Cargo: GERENTE" <<endl;
	// calcula o total de salario de todos os gerentes e escreve no arquivo
	for(auto i : gerentes){ 
    	arquivo << i.getMatricula() << " - " << i.getNome() << " - " << i.getSalario() << endl;
		  totalGerente += stof(i.getSalario());
      
    }
	
	total = totalAsg + totalVendedor + totalGerente;
		
	arquivo << "Total GERENTE: " << totalGerente << endl << endl;

  	arquivo << "CUSTO TOTAL: " << total << endl << endl;

  	arquivo << "FATURAMENTO MENSAL: " << getFaturamentoMensal() << endl << endl;
  
	arquivo << fixed << setprecision(2);
	
    arquivo << "Custo ASG(%): " << setprecision(2) << (totalAsg / total * 100) << endl;

    arquivo << "Custo VENDEDOR(%): " << setprecision(2) << (totalVendedor / total * 100) << endl;

    arquivo << "Custo GERENTE(%): " << setprecision(2) << (totalGerente / total * 100) << endl << endl;


	float lucro = getFaturamentoMensal() - total;
  	
	arquivo << "LUCRO DA EMPRESA: " << lucro << endl << endl;

	cout << "Salario total dos ASGs: " << totalAsg << endl;
	cout << "Salario total dos vendedores: " << totalVendedor << endl;
	cout << "Salario total dos gerentes: " << totalGerente << endl;
	cout << "Salario total de todos os funcionarios: " << total << endl;
	cout << "Faturamento mensal: " << getFaturamentoMensal() << endl;
	cout << "Lucro: " << lucro << endl;
	cout << "Custo total (%) dos ASGs: " << fixed << setprecision(2) << (totalAsg / total * 100) << endl;
	cout << "Custo total (%) dos Vendedores: " << fixed << setprecision(2) << (totalVendedor / total * 100) << endl;
	cout << "Custo total (%) dos Gerentes: " << fixed << setprecision(2) << (totalGerente / total * 100) << endl;

	// verifica se o valor encontrado no lucro é positivo, negativo ou nulo e descreve a situação da empresa
	if (lucro < 0){
		arquivo << "SITUAÇÃO: prejuízo";
		cout << endl << "SITUAÇÃO: prejuízo" << endl;
	}
	else if(lucro > 0){
		arquivo << "SITUAÇÃO: lucro";
		cout << endl << "SITUAÇÃO: lucro" << endl;
	}
	else{
		arquivo << "SITUAÇÃO: equilíbrio";
		cout << endl << "SITUAÇÃO: equilíbrio" << endl;
	}
	arquivo.close();
	
	cout << endl << "##################################" << endl << endl;
}

bool Empresa::calcularRescisao(string matricula, Data desligamento){

	cout << endl << "Busca valor de rescisão de um funcionário:" << endl;
	//busca pelos asgs
	for (auto asg : asgs) {
        if (asg.getMatricula() == matricula) {
            //resA - rescisao do asgs
			float resA = asg.calcularRescisao(desligamento);
			cout << "Rescisão: R$" << resA << endl;
			cout << "##################################" << endl;
			return true;
        }
    }

    //busca pelos vendedores
    for (auto vendedor : vendedores) {
        if (vendedor.getMatricula() == matricula) {
            //resV - rescisao do vendedor
			float resV = vendedor.calcularRescisao(desligamento);
			cout << "Rescisão: R$" << resV << endl;
			cout << "##################################" << endl;
			return true;
        }
    }

    //busca pelos gerentes
    for (auto gerente : gerentes) {
        if (gerente.getMatricula() == matricula) {
			//resG - rescisao do gerente
            float resG = gerente.calcularRescisao(desligamento);
			cout << "Rescisão: R$" << resG << endl;
			cout << "##################################" << endl;
			return true;
        }
    }
	cout << "##################################" << endl;
	cout << "Funcionário não encontrado no sistema";
	cout << "##################################" << endl;
}

void Empresa::demitirFuncionario(std::string matricula, Data desligamento){

    // cria e lê os arquivos
    fstream arquivo;
    arquivo.open("relatórioDemissional.txt", ios::out | ios::trunc );
  
    // procura nos asgs
	for(auto it = asgs.begin(); it != asgs.end(); ++it){
		// ao achar o funcionario, imprime seu relatorio demissional
		if(it->getMatricula() == matricula){
			cout << endl << "Fazendo relatorio de demissão do ASG..." << endl << endl;
			arquivo << "##############################" << endl;
			arquivo << "Relatorio Demissional" << endl;
			arquivo << "##############################" << endl;
			arquivo << "Cargo: ASG" << endl;
			arquivo << "Nome: " << it->getNome() << endl;              
			arquivo << "CPF: " << it->getCpf() <<endl;
			arquivo << "Matrícula: " << it->getMatricula()<< endl;
			arquivo << "Data de ingresso: " << it->getIngresso().dia <<"/"<< it->getIngresso().mes << "/"<< it->getIngresso().ano << endl;
			arquivo << "Data de demissão: " << desligamento.dia <<"/"<< desligamento.mes << "/"<< desligamento.ano << endl;
			arquivo << "******************************" << endl;
			arquivo << "Valor de rescisão: " << it->calcularRescisao(desligamento)  << endl;
			arquivo << "******************************" << endl;

			// cálculo do tempo trabalhado
			int anosTrabalhados = desligamento.ano - it->getIngresso().ano;
			int mesesTrabalhados = desligamento.mes - it->getIngresso().mes;
			int diasTrabalhados = desligamento.dia - it->getIngresso().dia;
			
			// trata os casos em que se obtem valores negativos nas variavéis de desligamento
			if (mesesTrabalhados < 0){
				anosTrabalhados--;
				mesesTrabalhados += 12;
			}
			if (diasTrabalhados < 0){
				mesesTrabalhados--;
				diasTrabalhados += 30;
			}
			
			arquivo << "Tempo de Trabalho: " << anosTrabalhados <<" anos, "<< mesesTrabalhados << " meses e "<< diasTrabalhados << " dias"<<endl; 
			arquivo.close();
	
		  	asgs.erase(it);

			int i = 0;
			arquivo.open("asg.txt", ios::out);

			// reescreve o arquivo com a nova tabela de asgs
	  		for (Asg& asg : asgs){
				arquivo << "#########################################################" << endl;
				arquivo << "ASG Nº: " << i << endl;
				arquivo << "##### DADOS PESSOAIS #####" << endl;
				arquivo << asg.getNome() << endl;
				arquivo << asg.getCpf() << endl;
				arquivo << asg.getFilhos() << endl;
				arquivo << asg.getEstadoCivil() << endl;
				arquivo << "***** Endereço (cidade, cep, bairro, rua e numero) ****" << endl;
				arquivo << asg.getEndereco().cidade << endl;
				arquivo << asg.getEndereco().cep << endl;
				arquivo << asg.getEndereco().bairro << endl;
				arquivo << asg.getEndereco().rua << endl;
				arquivo << asg.getEndereco().numero << endl;
				arquivo << "##### Data de nascimento (ano, mes, dia) #####" << endl;
				arquivo << asg.getData().ano << endl;
				arquivo << asg.getData().mes << endl;
				arquivo << asg.getData().dia << endl;
				arquivo << "##### DADOS FUNCIONAIS #####" << endl;
				arquivo << asg.getMatricula() << endl;
				arquivo << asg.getSalario() << endl;
				arquivo << asg.getAdicional() << endl;
				arquivo << asg.getFaltas() << endl;
				arquivo << "##### Data de ingresso (ano, mes, dia) #####" << endl;
				arquivo << asg.getIngresso().ano << endl;
				arquivo << asg.getIngresso().mes << endl;
				arquivo << asg.getIngresso().dia << endl;
				
				i++;
			}

			arquivo.close();  
		  	return;     
    	}
	}

	// procura nos vendedores
	for(auto it = vendedores.begin(); it != vendedores.end(); ++it){
		//ao achar o funcionario, imprime seu relatorio demissional
		if(it->getMatricula() == matricula){	
			cout << endl << "Fazendo relatorio de demissão do VENDEDOR..." << endl;
			arquivo << "##############################" << endl;
			arquivo << "Relatorio Demissional" << endl;
			arquivo << "##############################" << endl;
			arquivo << "Cargo: VENDEDOR" << endl;
			arquivo << "Nome: " << it->getNome() << endl;              
			arquivo << "CPF: " << it->getCpf() <<endl;
			arquivo << "Matrícula: " << it->getMatricula()<< endl;
			arquivo << "Data de ingresso: " << it->getIngresso().dia <<"/"<< it->getIngresso().mes << "/"<< it->getIngresso().ano << endl;
			arquivo << "Data de demissão: " << desligamento.dia <<"/"<< desligamento.mes << "/"<< desligamento.ano << endl;
			arquivo << "******************************" << endl;
			arquivo << "Valor de rescisão: " << it->calcularRescisao(desligamento)  << endl;
			arquivo << "******************************" << endl;

			// cálculo do tempo trabalhado
			int anosTrabalhados = desligamento.ano - it->getIngresso().ano;
			int mesesTrabalhados = desligamento.mes - it->getIngresso().mes;
			int diasTrabalhados = desligamento.dia - it->getIngresso().dia;

			// trata os casos em que é obtido um valor negativo nas variavéis
			if (mesesTrabalhados < 0){
				anosTrabalhados--;
				mesesTrabalhados += 12;
			}
			if (diasTrabalhados < 0){
				mesesTrabalhados--;
				diasTrabalhados += 30;
			}
			
			arquivo << "Tempo de Trabalho: " << anosTrabalhados <<" anos, "<< mesesTrabalhados << " meses e "<< diasTrabalhados << " dias"<<endl; 
			
			arquivo.close();
            
			vendedores.erase(it);

			int i = 0;
			arquivo.open("vendedor.txt", ios::out);

			// reescreve o arquivo com a nova tabela de vendedores
		  	for (Vendedor& vendedor : vendedores){
				arquivo << "#########################################################" << endl;
				arquivo << "VENDEDOR Nº: " << i << endl;
				arquivo << "##### DADOS PESSOAIS #####" << endl;
				arquivo << vendedor.getNome() << endl;
				arquivo << vendedor.getCpf() << endl;
				arquivo << vendedor.getFilhos() << endl;
				arquivo << vendedor.getEstadoCivil() << endl;
				arquivo << "***** Endereço (cidade, cep, bairro, rua e numero) ****" << endl;
				arquivo << vendedor.getEndereco().cidade << endl;
				arquivo << vendedor.getEndereco().cep << endl;
				arquivo << vendedor.getEndereco().bairro << endl;
				arquivo << vendedor.getEndereco().rua << endl;
				arquivo << vendedor.getEndereco().numero << endl;
				arquivo << "##### Data de nascimento (ano, mes, dia) #####" << endl;
				arquivo << vendedor.getData().ano << endl;
				arquivo << vendedor.getData().mes << endl;
				arquivo << vendedor.getData().dia << endl;
				arquivo << "##### DADOS FUNCIONAIS #####" << endl;
				arquivo << vendedor.getMatricula() << endl;
				arquivo << vendedor.getSalario() << endl;
				arquivo << vendedor.getTipo() << endl;
				arquivo << vendedor.getFaltas() << endl;
				arquivo << "##### Data de ingresso (ano, mes, dia) #####" << endl;
				arquivo << vendedor.getIngresso().ano << endl;
				arquivo << vendedor.getIngresso().mes << endl;
				arquivo << vendedor.getIngresso().dia << endl;
				
				i++;
			}

			arquivo.close();
           	return;
    	}
	}

	// procura nos gerentes
	for(auto it = gerentes.begin(); it != gerentes.end(); ++it){
		//ao achar o funcionario, imprime seu relatorio demissional
		if(it->getMatricula() == matricula){
			cout << endl << "Fazendo relatorio de demissão do GERENTE" << endl;
			arquivo << "##############################" << endl;
			arquivo << "Relatorio Demissional" << endl;
			arquivo << "##############################" << endl;
			arquivo << "Cargo: GERENTE" << endl;
			arquivo << "Nome: " << it->getNome() << endl;              
			arquivo << "CPF: " << it->getCpf() <<endl;
			arquivo << "Matrícula: " << it->getMatricula()<< endl;
			arquivo << "Data de ingresso: " << it->getIngresso().dia <<"/"<< it->getIngresso().mes << "/"<< it->getIngresso().ano << endl;
			arquivo << "Data de demissão: " << desligamento.dia <<"/"<< desligamento.mes << "/"<< desligamento.ano << endl;
			arquivo << "******************************" << endl;
			arquivo << "Valor de rescisão: " << it->calcularRescisao(desligamento)  << endl;
			arquivo << "******************************" << endl;

			// cálculo do tempo trabalhado
			int anosTrabalhados = desligamento.ano - it->getIngresso().ano;
			int mesesTrabalhados = desligamento.mes - it->getIngresso().mes;
			int diasTrabalhados = desligamento.dia - it->getIngresso().dia;

			// trata os casos em que é obtido um valor negativo nas variavéis
			if (mesesTrabalhados < 0){
				anosTrabalhados--;
				mesesTrabalhados += 12;
			}
			if (diasTrabalhados < 0){
				mesesTrabalhados--;
				diasTrabalhados += 30;
			}
			
			arquivo << "Tempo de Trabalho: " << anosTrabalhados <<" anos, "<< mesesTrabalhados << " meses e "<< diasTrabalhados << " dias"<<endl; 
			arquivo.close();
			
			
			gerentes.erase(it);
			
			int i = 0;
			arquivo.open("gerente.txt", ios::out);
			
			// reescreve o arquivo com a nova tabela de gerentes
			for (Gerente& gerente : gerentes) {
				arquivo << "#########################################################" << endl;
				arquivo << "VENDEDOR Nº: " << i << endl;
				arquivo << "##### DADOS PESSOAIS #####" << endl;
				arquivo << gerente.getNome() << endl;
				arquivo << gerente.getCpf() << endl;
				arquivo << gerente.getFilhos() << endl;
				arquivo << gerente.getEstadoCivil() << endl;
				arquivo << "***** Endereço (cidade, cep, bairro, rua e numero) ****" << endl;
				arquivo << gerente.getEndereco().cidade << endl;
				arquivo << gerente.getEndereco().cep << endl;
				arquivo << gerente.getEndereco().bairro << endl;
				arquivo << gerente.getEndereco().rua << endl;
				arquivo << gerente.getEndereco().numero << endl;
				arquivo << "##### Data de nascimento (ano, mes, dia) #####" << endl;
				arquivo << gerente.getData().ano << endl;
				arquivo << gerente.getData().mes << endl;
				arquivo << gerente.getData().dia << endl;
				arquivo << "##### DADOS FUNCIONAIS #####" << endl;
				arquivo << gerente.getMatricula() << endl;
				arquivo << gerente.getSalario() << endl;
				arquivo << gerente.getLucros() << endl;
				arquivo << gerente.getFaltas() << endl;
				arquivo << "##### Data de ingresso (ano, mes, dia) #####" << endl;
				arquivo << gerente.getIngresso().ano << endl;
				arquivo << gerente.getIngresso().mes << endl;
				arquivo << gerente.getIngresso().dia << endl;
				
				i++;
			}

			arquivo.close();
			return;
    	}
	}
	arquivo.close();
};

void Empresa::contratarFuncionario(){

	cout << endl << "Contratando funcionário..." << endl << endl;
	// criação do arquivo
	ifstream arquivo("novoFuncionario.txt");
	
    string linha;
	string cargo;

	getline(arquivo, linha); // Lê o cargo do funcionário
	cargo = linha;

	// condicional para saber qual é o cargo do funcionário a ser contratado
	if (cargo == "ASG"){
		Asg asg;
		// leitura do arquivo de modo que pegue as informações do novo contratado (asg.txt)
	    while (getline(arquivo, linha)){
	        getline(arquivo, linha); // Lê o nome
	        asg.setNome(linha);
	        getline(arquivo, linha); // Lê o CPF
	        asg.setCpf(linha);
	        getline(arquivo, linha); // Lê o número de filhos
	        asg.setFilhos(stoi(linha));
	        getline(arquivo, linha); // Lê o estado civil
	        asg.setEstadoCivil(linha);
	        getline(arquivo, linha); // Ignora a linha 
	        getline(arquivo, linha); // Lê a cidade
	        string cidade = linha;
	        getline(arquivo, linha); // Lê o CEP
	        string cep = linha;
	        getline(arquivo, linha); // Lê o bairro
	        string bairro = linha;
	        getline(arquivo, linha); // Lê a rua
	        string rua = linha;
	        getline(arquivo, linha); // Lê o número da casa
	        int numero = stoi(linha);
	        Endereco endereco{cidade, bairro, rua, cep, numero};
	        asg.setEndereco(endereco);
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê o ano de nascimento
	        int anoNascimento = stoi(linha);
	        getline(arquivo, linha); // Lê o mês de nascimento
	        int mesNascimento = stoi(linha);
	        getline(arquivo, linha); // Lê o dia de nascimento
	        int diaNascimento = stoi(linha);
	        Data dataNascimento{anoNascimento, mesNascimento, diaNascimento};
	        asg.setData(dataNascimento);
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê a matrícula
	        asg.setMatricula(linha);
	        getline(arquivo, linha); // Lê o salário
	        asg.setSalario(linha);
	        getline(arquivo, linha); // Lê a taxa de insalubridade
	        asg.setAdicional(stof(linha));
	        getline(arquivo, linha); //Lê os dias de falta
			asg.setFaltas(stoi(linha));
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê o ano de ingresso
	        int anoIngresso = stoi(linha);
	        getline(arquivo, linha); // Lê o mês de ingresso
	        int mesIngresso = stoi(linha);
	        getline(arquivo, linha); // Lê o dia de ingresso
	        int diaIngresso = stoi(linha);
	        Data dataIngresso{anoIngresso, mesIngresso, diaIngresso};
	        asg.setIngresso(dataIngresso);
	        asgs.push_back(asg);
		}
		arquivo.close();

		// criação do novo arquivo
		fstream arquivoEscrita;
		arquivoEscrita.open("asg.txt", ios::app);

		// Acrescenta as informações do novo funcionário (asg)
		arquivoEscrita << "ASG Nº: " << asgs.size()-1 << endl;
		arquivoEscrita << "##### DADOS PESSOAIS #####" << endl;
		arquivoEscrita << asg.getNome() << endl;
		arquivoEscrita << asg.getCpf() << endl;
		arquivoEscrita << asg.getFilhos() << endl;
		arquivoEscrita << asg.getEstadoCivil() << endl;
		arquivoEscrita << "***** Endereço (cidade, cep, bairro, rua e numero) ****" << endl;
		arquivoEscrita << asg.getEndereco().cidade << endl;
		arquivoEscrita << asg.getEndereco().cep << endl;
		arquivoEscrita << asg.getEndereco().bairro << endl;
		arquivoEscrita << asg.getEndereco().rua << endl;
		arquivoEscrita << asg.getEndereco().numero << endl;
		arquivoEscrita << "***** Data de nascimento (ano, mes, dia) ****" << endl;
		arquivoEscrita << asg.getData().ano << endl;
		arquivoEscrita << asg.getData().mes << endl;
		arquivoEscrita << asg.getData().dia << endl;
		arquivoEscrita << "##### DADOS FUNCIONAIS #####" << endl;
		arquivoEscrita << asg.getMatricula() << endl;
		arquivoEscrita << asg.getSalario() << endl;
		arquivoEscrita << asg.getAdicional() << endl;
		arquivoEscrita << asg.getFaltas() << endl;
		arquivoEscrita << "***** Data de ingresso (ano, mes, dia) ****" << endl;
		arquivoEscrita << asg.getIngresso().ano << endl;
		arquivoEscrita << asg.getIngresso().mes << endl;
		arquivoEscrita << asg.getIngresso().dia << endl;
		arquivoEscrita << "#########################################################" << endl;
		arquivoEscrita.close();
    }
	else if(cargo == "VENDEDOR"){
		Vendedor vendedor;
		// leitura do arquivo de modo que pegue as informações do novo contratado (vendedor.txt)
		while (getline(arquivo, linha)){
	        getline(arquivo, linha); // Lê o nome
	        vendedor.setNome(linha);
	        getline(arquivo, linha); // Lê o CPF
	        vendedor.setCpf(linha);
	        getline(arquivo, linha); // Lê o número de filhos
	        vendedor.setFilhos(stoi(linha));
	        getline(arquivo, linha); // Lê o estado civil
	        vendedor.setEstadoCivil(linha);
	        getline(arquivo, linha); // Ignora a linha 
	        getline(arquivo, linha); // Lê a cidade
	        string cidade = linha;
	        getline(arquivo, linha); // Lê o CEP
	        string cep = linha;
	        getline(arquivo, linha); // Lê o bairro
	        string bairro = linha;
	        getline(arquivo, linha); // Lê a rua
	        string rua = linha;
	        getline(arquivo, linha); // Lê o número da casa
	        int numero = stoi(linha);
	        Endereco endereco{cidade, bairro, rua, cep, numero};
	        vendedor.setEndereco(endereco);
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê o ano de nascimento
	        int anoNascimento = stoi(linha);
	        getline(arquivo, linha); // Lê o mês de nascimento
	        int mesNascimento = stoi(linha);
	        getline(arquivo, linha); // Lê o dia de nascimento
	        int diaNascimento = stoi(linha);
	        Data dataNascimento{anoNascimento, mesNascimento, diaNascimento};
	        vendedor.setData(dataNascimento);
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê a matrícula
	        vendedor.setMatricula(linha);
	        getline(arquivo, linha); // Lê o salário
	        vendedor.setSalario(linha);
	        getline(arquivo, linha); // Lê o tipo do vendedor
			char tipo = linha.front();
	        vendedor.setTipo(tipo);
	        getline(arquivo, linha); //Lê os dias de falta
			vendedor.setFaltas(stoi(linha));
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê o ano de ingresso
	        int anoIngresso = stoi(linha);
	        getline(arquivo, linha); // Lê o mês de ingresso
	        int mesIngresso = stoi(linha);
	        getline(arquivo, linha); // Lê o dia de ingresso
	        int diaIngresso = stoi(linha);
	        Data dataIngresso{anoIngresso, mesIngresso, diaIngresso};
	        vendedor.setIngresso(dataIngresso);
	        vendedores.push_back(vendedor);
	    }
		arquivo.close();

		// criação do novo arquivo
		fstream arquivoEscrita;
		arquivoEscrita.open("vendedor.txt", ios::app);
	
		// Acrescenta as informações do novo funcionário (vendedor)
		arquivoEscrita << "VENDEDOR Nº: " << vendedores.size()-1 << endl;
		arquivoEscrita << "##### DADOS PESSOAIS #####" << endl;
		arquivoEscrita << vendedor.getNome() << endl;
		arquivoEscrita << vendedor.getCpf() << endl;
		arquivoEscrita << vendedor.getFilhos() << endl;
		arquivoEscrita << vendedor.getEstadoCivil() << endl;
		arquivoEscrita << "***** Endereço (cidade, cep, bairro, rua e numero) ****" << endl;
		arquivoEscrita << vendedor.getEndereco().cidade << endl;
		arquivoEscrita << vendedor.getEndereco().cep << endl;
		arquivoEscrita << vendedor.getEndereco().bairro << endl;
		arquivoEscrita << vendedor.getEndereco().rua << endl;
		arquivoEscrita << vendedor.getEndereco().numero << endl;
		arquivoEscrita << "***** Data de nascimento (ano, mes, dia) ****" << endl;
		arquivoEscrita << vendedor.getData().ano << endl;
		arquivoEscrita << vendedor.getData().mes << endl;
		arquivoEscrita << vendedor.getData().dia << endl;
		arquivoEscrita << "##### DADOS FUNCIONAIS #####" << endl;
		arquivoEscrita << vendedor.getMatricula() << endl;
		arquivoEscrita << vendedor.getSalario() << endl;
		arquivoEscrita << vendedor.getTipo() << endl;
		arquivoEscrita << vendedor.getFaltas() << endl;
		arquivoEscrita << "***** Data de ingresso (ano, mes, dia) ****" << endl;
		arquivoEscrita << vendedor.getIngresso().ano << endl;
		arquivoEscrita << vendedor.getIngresso().mes << endl;
		arquivoEscrita << vendedor.getIngresso().dia << endl;
		arquivoEscrita << "#########################################################" << endl;
		arquivoEscrita.close();
	}
	else if(cargo == "GERENTE"){
    Gerente gerente;
		// leitura do arquivo de modo que pegue as informações do novo contratado (gerente.txt)
		while (getline(arquivo, linha)){
	        getline(arquivo, linha); // Lê o nome
	        gerente.setNome(linha);
	        getline(arquivo, linha); // Lê o CPF
	        gerente.setCpf(linha);
	        getline(arquivo, linha); // Lê o número de filhos
	        gerente.setFilhos(stoi(linha));
	        getline(arquivo, linha); // Lê o estado civil
	        gerente.setEstadoCivil(linha);
	        getline(arquivo, linha); // Ignora a linha 
	        getline(arquivo, linha); // Lê a cidade
	        string cidade = linha;
	        getline(arquivo, linha); // Lê o CEP
	        string cep = linha;
	        getline(arquivo, linha); // Lê o bairro
	        string bairro = linha;
	        getline(arquivo, linha); // Lê a rua
	        string rua = linha;
	        getline(arquivo, linha); // Lê o número da casa
	        int numero = stoi(linha);
	        Endereco endereco{cidade, bairro, rua, cep, numero};
	        gerente.setEndereco(endereco);
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê o ano de nascimento
	        int anoNascimento = stoi(linha);
	        getline(arquivo, linha); // Lê o mês de nascimento
	        int mesNascimento = stoi(linha);
	        getline(arquivo, linha); // Lê o dia de nascimento
	        int diaNascimento = stoi(linha);
	        Data dataNascimento{anoNascimento, mesNascimento, diaNascimento};
	        gerente.setData(dataNascimento);
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê a matrícula
	        gerente.setMatricula(linha);
	        getline(arquivo, linha); // Lê o salário
	        gerente.setSalario(linha);
	        getline(arquivo, linha); // Lê o valor da participação nos lucros da empresa
	        gerente.setLucros(stof(linha));
	        getline(arquivo, linha); // Lê os dias de falta
			gerente.setFaltas(stoi(linha));
	        getline(arquivo, linha); // Ignora a linha
	        getline(arquivo, linha); // Lê o ano de ingresso
	        int anoIngresso = stoi(linha);
	        getline(arquivo, linha); // Lê o mês de ingresso
	        int mesIngresso = stoi(linha);
	        getline(arquivo, linha); // Lê o dia de ingresso
	        int diaIngresso = stoi(linha);
	        Data dataIngresso{anoIngresso, mesIngresso, diaIngresso};
	        gerente.setIngresso(dataIngresso);
	        gerentes.push_back(gerente);
	    }
		arquivo.close();

		// criação do novo arquivo
		fstream arquivoEscrita;
		arquivoEscrita.open("gerente.txt", ios::app);
	
		// Acrescenta as informações do novo funcionário (gerente)
		arquivoEscrita << "GERENTE Nº: " << gerentes.size()-1 << endl;
		arquivoEscrita << "##### DADOS PESSOAIS #####" << endl;
		arquivoEscrita << gerente.getNome() << endl;
		arquivoEscrita << gerente.getCpf() << endl;
		arquivoEscrita << gerente.getFilhos() << endl;
		arquivoEscrita << gerente.getEstadoCivil() << endl;
		arquivoEscrita << "***** Endereço (cidade, cep, bairro, rua e numero) ****" << endl;
		arquivoEscrita << gerente.getEndereco().cidade << endl;
		arquivoEscrita << gerente.getEndereco().cep << endl;
		arquivoEscrita << gerente.getEndereco().bairro << endl;
		arquivoEscrita << gerente.getEndereco().rua << endl;
		arquivoEscrita << gerente.getEndereco().numero << endl;
		arquivoEscrita << "***** Data de nascimento (ano, mes, dia) ****" << endl;
		arquivoEscrita << gerente.getData().ano << endl;
		arquivoEscrita << gerente.getData().mes << endl;
		arquivoEscrita << gerente.getData().dia << endl;
		arquivoEscrita << "##### DADOS FUNCIONAIS #####" << endl;
		arquivoEscrita << gerente.getMatricula() << endl;
		arquivoEscrita << gerente.getSalario() << endl;
		arquivoEscrita << gerente.getLucros() << endl;
		arquivoEscrita << gerente.getFaltas() << endl;
		arquivoEscrita << "***** Data de ingresso (ano, mes, dia) ****" << endl;
		arquivoEscrita << gerente.getIngresso().ano << endl;
		arquivoEscrita << gerente.getIngresso().mes << endl;
		arquivoEscrita << gerente.getIngresso().dia << endl;
		arquivoEscrita << "#########################################################" << endl;
		arquivoEscrita.close();
	}
	cout <<  endl << "Programa encerrado." << endl;
}