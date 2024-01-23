#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;


//cerr- utilizado para mensagens de erro como ex numeros invalidos como se fosse ou cout ou ostream


#ifdef _WIN32
#include <windows.h>
#endif

void setColor(string color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    cout << color;
#endif
}

int gerarNumeroUnico(const vector<int>& numerosUsados, int limiteSuperior) {
    int numeroAleatorio;
    do {
        numeroAleatorio = rand() % limiteSuperior + 1;
    } while (find(numerosUsados.begin(), numerosUsados.end(), numeroAleatorio) != numerosUsados.end());
    return numeroAleatorio;
}

vector<vector<int>> gerarCartaBingo(int escolha) {
    int limiteSuperior;
    switch (escolha) {
        case 1:
            limiteSuperior = 75;
            break;
        case 2:
            limiteSuperior = 90;
            break;
        case 3:
            limiteSuperior = 100;
            break;
        default:
            cerr << "Escolha inválida. Saindo do programa.\n";
            exit(1);
    }

    vector<vector<int>> carta(5, vector<int>(5, 0));

    for (int i = 0; i < 5; ++i) {
        vector<int> numerosUsados;
        for (int j = 0; j < 5; ++j) {
            carta[i][j] = gerarNumeroUnico(numerosUsados, limiteSuperior);
            numerosUsados.push_back(carta[i][j]);
        }
    }

    return carta;
}

void salvarCartaEmArquivo(const vector<vector<int>>& carta, int numeroCartao) {
    string nomeArquivo = "carta_bingo_" + to_string(numeroCartao) + ".txt";
    ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        for (const auto& linha : carta) {
            for (int numero : linha) {
                arquivo << numero << "\t";
            }
            arquivo << endl;
        }

        arquivo.close();
        cout << "Carta de Bingo " << numeroCartao << " salva em " << nomeArquivo << endl;
    } else {
        cerr << "Erro ao criar o arquivo " << nomeArquivo << endl;
    }
}

