#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

string palavraSecreta;
map<char, bool> chutou;
vector<char> chutesErrados;

bool letraExiste(char chute){
    for (char letra : palavraSecreta){
        if(chute == letra){
            return true;
        }
    }
    return false;
}

bool NaoAcertou(){
    for(char letra : palavraSecreta){
        if (!chutou[letra]){
            return true;
        }
    }
    return false;
}

bool NaoEnforcou(){
    return chutesErrados.size() < 5;
}

void ImprimeCabecalho(){
    cout << "*******************" << endl;
    cout << "***JOGO DA FORCA***" << endl;
    cout << "*******************" << endl;
    cout << endl;
}

void ImprimeErros(){
    cout << "Chutes errados: ";
        for (char letra : chutesErrados){
            cout << letra << " ";
        }
    cout << endl;
}

void ImprimePalavra(){
    for (char letra : palavraSecreta) {
        if (chutou[letra]){
            cout << letra << "";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void Chuta(){
    cout << "Seu chute: ";
    char chute;
    cin >> chute;

    chutou[chute] = true;

    if (letraExiste(chute)){
        cout << "Você acertou!! Seu chute está na palavra." << endl;
    }
    else{
        cout << "Você errou! Seu chute não está na palavra." << endl;
        chutesErrados.push_back(chute);
    }
    cout << endl;
}

vector<string> LeArquivo(){
    ifstream arquivo;
    
    arquivo.open("palavras.txt");
    
    if (arquivo.is_open()){
        int qtdPalavras;
        arquivo >> qtdPalavras;

        cout << "O arquivo possui " << qtdPalavras << " palavras." << endl;

        vector<string> palavraArquivo;

        for (int i = 0; i < qtdPalavras; i++){
            string palavraLida;
            arquivo >> palavraLida;
            palavraArquivo.push_back(palavraLida);
        }

        arquivo.close();
        return palavraArquivo;
    }
    else{
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
    
}

void SorteiaPalavra(){
    vector<string> palavras = LeArquivo();

    srand(time(NULL));
    int indiceSorteado = rand() % palavras.size();

    palavraSecreta = palavras[indiceSorteado];

}

void SalvaArquivo(vector<string> novaLista){
    ofstream arquivo;
    arquivo.open("palavras.txt");

    if (arquivo.is_open()){
        arquivo << novaLista.size() << endl;

        for (string palavra : novaLista){
            arquivo << palavra << endl;
        }
        
        arquivo.close();
    }
    else{
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
   
}

void AdicionaPalavra(){
    cout << "Digite a nova palavra, usando letras maiúsculas." << endl;
    string novaPalavra;
    cin >> novaPalavra;

    vector<string> listaPalavras = LeArquivo();
    listaPalavras.push_back(novaPalavra);

    SalvaArquivo(listaPalavras);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    ImprimeCabecalho();
    SorteiaPalavra();

    while(NaoAcertou() && NaoEnforcou()){

        ImprimeErros();
        ImprimePalavra();
        Chuta();

    }

    cout << "Fim de Jogo!" << endl;
    cout << "A palavra secreta era " << palavraSecreta << endl;

    if (NaoAcertou()){
        cout << "Você perdeu! Tente novamente!" << endl;
    }
    else{
        cout << "Parabéns! Você acertou a palavra secreta!" << endl;

        cout << "Você deseja adicionar uma nova palavra ao banco? (S/N)" << endl;
        char resposta;
        cin >> resposta;
        if (resposta == 'S'){
            AdicionaPalavra();
        }
    }
    
}