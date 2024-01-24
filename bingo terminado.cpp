#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;




string Vermelho = "\u001b[31m"; //cor vermelho
string resetCor = "\u001b[0m" ; //resetar a cor 

void setColor(string color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    cout << color;
#endif
}

int const gerarNumeroUnico(const vector<int>& numerosUsados, int limiteSuperior) {
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

void esperarPorSegundos(int segundos) {
    this_thread::sleep_for(chrono::seconds(segundos));
}

int main() {
    srand(unsigned (time(0)));

    int escolha;
    cout << "Escolhe até quantos numeros queres:\n";
    cout << "1. 1 a 75\n";
    cout << "2. 1 a 90\n";
    cout << "3. 1 a 100\n";
    cin >> escolha;

    int numeroCartoes;
    cout << "Quantos cartões queres gerar? " << endl;
    cin >> numeroCartoes;

    int limiteSuperior;
    limiteSuperior = (escolha == 1) ? 75 : (escolha == 2) ? 90 : 100;

    // Geração de cartões
    vector<vector<vector<int>>> cartasBingo(numeroCartoes);
    for (int i = 0; i < numeroCartoes; ++i) {
        cartasBingo[i] = gerarCartaBingo(escolha);
        salvarCartaEmArquivo(cartasBingo[i], i + 1);
    }

    // Escolher sorteio automático ou manual
    cout << "Escolha o modo de sorteio (0 - Manual, 1 - Automático): ";
    int modoSorteio;
    cin >> modoSorteio;

    vector<int> numerosSorteados;
    if (modoSorteio == 1) {
        // Sorteio automático de números
        cout << "\nSorteio automático \n";
        bool continuarSorteio = true;

       if (modoSorteio == 1) {
    // Sorteio automático de números
    cout << "\nSorteio automático \n";

    while (true) {  // Loop infinito
        int sorteio = gerarNumeroUnico(numerosSorteados, limiteSuperior);
        numerosSorteados.push_back(sorteio);

       

        esperarPorSegundos(1);  // Aguarda 1 segundo antes de mostrar o próximo número

        cout << "Número sorteado: " << sorteio << "\n";

        // Exibir números sorteados nos cartões
        for (int i = 0; i < numeroCartoes; ++i) {
            cout << "Cartão " << i + 1 << ": ";
            for (int linha = 0; linha < 5; ++linha) {
                for (int coluna = 0; coluna < 5; ++coluna) {
                    int numeroCarta = cartasBingo[i][linha][coluna];
                    if (find(numerosSorteados.begin(), numerosSorteados.end(), numeroCarta) != numerosSorteados.end()) {
                        setColor(Vermelho);  // Vermelho
                        cout << numeroCarta << "\t";
                        setColor(resetCor);  // Resetar cor
                    } else {
                        cout << numeroCarta << "\t";
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    cout << "Fim do sorteio automático.\n";
}
    } else if (modoSorteio == 0) {
        // Sorteio manual de números
        int sorteioAnterior = -1;

        cout << "Sorteio manual iniciado...\n";
        for (int i = 0; i < limiteSuperior; ++i) {
            cout << "Pressione Enter para sortear um número...";
            cin.ignore();  // Ignora qualquer entrada anterior

            int sorteio = gerarNumeroUnico(numerosSorteados, limiteSuperior);
            numerosSorteados.push_back(sorteio);

            esperarPorSegundos(1);  // Aguarda 1 segundo antes de mostrar o próximo número

            cout << "Número sorteado: " << sorteio << "\n";

            // Exibir números sorteados nos cartões
            for (int i = 0; i < numeroCartoes; ++i) {
                cout << "Cartão " << i + 1 << ": ";
                for (int linha = 0; linha < 5; ++linha) {
                    for (int coluna = 0; coluna < 5; ++coluna) {
                        int numeroCarta = cartasBingo[i][linha][coluna];
                        if (find(numerosSorteados.begin(), numerosSorteados.end(), numeroCarta) != numerosSorteados.end()) {
                            setColor("\u001b[31m");  // Vermelho
                            cout << numeroCarta << "\t";
                            setColor("\u001b[0m");  // Resetar cor
                        } else {
                            cout << numeroCarta << "\t";
                        }
                    }
                    cout << endl;
                }
                cout << endl;
            }

            if (sorteioAnterior != -1) {
                cout << "Número sorteado: " << sorteio << ", Número anterior: " << sorteioAnterior << endl;
            } else {
                cout << "Primeiro número sorteado: " << sorteio << endl;
            }

            sorteioAnterior = sorteio;
        }

        cout << "Fim do sorteio manual.\n";
    } else {
        cerr << "Opção de sorteio inválida. Saindo do programa.\n";
        return 1;
    }

    return 0;
}
