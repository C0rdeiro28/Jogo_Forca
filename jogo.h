#ifndef JOGO_H
#define JOGO_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <locale>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <gotoxy.h>
#include <conio.h>

using namespace std;


class jogador;

class Jogo{

private:

    string palavra;
    string tema;

    string palavra_jogador;

    int dificuldade;
    int tempo[2];
    bool timer;
    bool tema_alea;
    int NumTentativas;
    bool palavra_acertada;
    bool Pausa;



public:

    int NumJogadores;

    Jogo(){
        dificuldade = 1;
        palavra = "empty";
        tema = "empty";
        palavra_jogador = "empty";

        tempo[0] = 0;
        tempo[1] = 0;

        timer = false;
        tema_alea = true;
        NumTentativas = 0;
        palavra_acertada = false;
        Pausa = false;

    }

    void menu(jogador *p, int ind); // Iniciar Novo Jogo; Sair; Mostrar Pontuaçoes
    // Modo de funcionamento{ configuraçoes do jogo, cronometro ou nao;
    //                        Tema automatico on/off; Nivel de dificuldade}
    void menu_funcionameno(jogador p[], int ind);

    void set_tema();    // Escolhe o tema dependendo da dificuldade, e se é aleatorio ou nao;
    void set_palavra(); // Define uma palavra aleatoria dependendo da dificuldade;

    void print_forca(); // Faz o desenho da forca;

    void inicia_jogo(jogador *p, int ind); // Começa o Jogo; //p->tabela de jogadores
    void print_palavra(int);
    char pedir_letra();
    bool verifica_palavra(char c);
    void desenha_forca();

    void verifica_ganhou(jogador *p);

    void atualiza_score(jogador *p);

    void modo_elementar(jogador *p, int );
    void modo_basico(jogador *p, int);
    void modo_Medio(jogador *p , int );

    void print_tenta_falhadas(char c[]);

    void print_score(); // Faz print das pontuaçoes do jogador;

    void set_dificuldade();
    void set_timer(jogador p[]);
    void set_tema_alea(jogador p[]);

    void print();

    bool reset_game(int);

    void calcula_timer(int);


    void Save_tab_jogadores(jogador p[]);

    void Load_Jogo(jogador p[]);
    void Save_Jogo(jogador p[]);

    void Apresenta();

    void Inicio(jogador p[]);

    void clear_palavra(int, int);

    void configTemasPalavras();
    void configTemas(string temasTab[], int &numTemas);
    void modifica();
    bool removeWord(string tab[], int dim);
    void apagarFicheiro(string fileName, string tema, string temasTab[], int numTemas);
    bool temaExiste(string tema, string tab[], int dim);
    int obterTemas(string temasTab[]);
    void readTemas(string temasTab[], int numTemas);



};


class jogador: Jogo{

public:
    string nome;
    int score;
    string escalao;
    bool timer_state;
    float bonus_time;
    bool JogoAtivo;

    jogador(){

        score = 0;
        bonus_time = 0;
        timer_state = true;
        JogoAtivo = 0;

    }

    void set_jogador(Jogo &J1); // Define o Jogador: Nome; //numJogadores é um contador do n de jogadores inscritos
    void print_jogador();
    int menu_jogador(Jogo &J1); //Retornar o indicide da tabela de jogadores, do jogador que vai jogar
    void print_jogadores(Jogo &J1);
    void Mostrar_Pontuacoes(Jogo &J1);


};

#endif // JOGO_H
