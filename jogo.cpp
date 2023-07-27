#include <jogo.h>
#include <windows.h>
#include <forca.h>
#include <timer.h>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>



using namespace std;

class Jogo;
int set_tema_aleatoria();
int set_tema_utilizador();
void  menu_funcionamento();
void print_ganhou();
void print_perdeu();
void draw_border();
void print_tenta_falhadas(char c[]);

void configTemasPalavras();
void configTemas(string temasTab[], int &numTemas);
void modifica();
bool removeWord(string tab[], int dim);
void apagarFicheiro(string fileName, string tema, string temasTab[], int numTemas);
bool temaExiste(string tema, string tab[], int dim);
int obterTemas(string temasTab[]);
void readTemas(string temasTab[], int numTemas);



//const string temas[]={"Animais","Marcas","Capitais"};
//const int Num_Temas = 3;
const string Escalao[]={"Elementar","Basico","Medio"};
const int MAX_PALAVRAS = 8;
//const int MAX_JOGADORES = 10;

const int Menu_Pos_X = 45;
const int Menu_Pos_Y = 20;

const int PONTOS = 10;

const int MAX_JOGADORES = 20;


const string File_Jogo = "Jogo_Backup.txt";


/*********************************************************************************************************************/

/*********************************************************************************************************************/


void Jogo::print(){

    cout<<" O Tema e: "<<tema<<endl;
    cout<<" A palavra e: "<<palavra<<endl;

}

/*********************************************************************************************************************/

void Jogo::Load_Jogo(jogador p[]){

    fstream fp;
    int i=0;


    fp.open(File_Jogo, ios::in);

    if(!fp.is_open()){

        cout<<" ERRO AO CARREGADR A DATA!! ";
        fp.close();
        exit(1);
    }
    else{

        if(fp.peek() == EOF){
            NumJogadores = 0;
        }else{
            NumJogadores = -1;

            while(fp.peek() != EOF){

                fp >> p[i].nome >> p[i].escalao >> p[i].score >> p[i].JogoAtivo ;
                fp >> this[i].dificuldade >> this[i].timer >> this[i].tema_alea >> this[i].palavra ;
                fp >> this[i].NumTentativas >> this[i].tempo[0] >> this[i].tempo[1];
                i++;
                NumJogadores++;
            }
        }

        fp.close();
    }
}



/*********************************************************************************************************************/

void Jogo::Inicio(jogador p[]){

    int ind;

    Load_Jogo(p);

    ind = p->menu_jogador(*this);

    this[ind].NumJogadores=this->NumJogadores;

    this->menu(p, ind);
}

/*********************************************************************************************************************/
/*
void Jogo::set_palavra(){

    fstream fp;
    string temp[MAX_PALAVRAS];
    string words;

    //random para escolher o indice da tabela aleatoriamente
    int ind=0;
    srand(time(NULL)); // Seed the time
    ind = rand()%8;         // Gerar um Numero entre 0 e 7 --> 8 palavras por tema

    if(tema==temas[0])//Animais
    {
        fp.open("Animais.txt", ios::in);
        if(!fp.is_open()){
            cout<<" Erro ao abrir o Ficheiro Animais"<<endl;
            fp.close();
            exit(1);
        }

        while(!fp.eof()){

            for(int i=0; i<MAX_PALAVRAS; i++){
                getline(fp, temp[i]);

            }
        }
        palavra=temp[ind];
        fp.close();
    }


    else if(tema==temas[1])//Marcas
    {
        fp.open("Marcas.txt", ios::in);
        if(!fp.is_open()){
            cout<<" Erro ao abrir o Ficheiro Marcas"<<endl;
            fp.close();
            exit(1);
        }


        while(!fp.eof()){

            for(int i=0; i<MAX_PALAVRAS; i++){
                getline(fp, temp[i]);

            }
        }

        palavra=temp[ind];
        fp.close();
    }


    else//Capitais
    {
        fp.open("Capitais.txt", ios::in);
        if(!fp.is_open()){
            cout<<" Erro ao abrir o Ficheiro Capitais"<<endl;
            fp.close();
            exit(1);
        }


        while(!fp.eof()){

            for(int i=0; i<MAX_PALAVRAS; i++){
                getline(fp, temp[i]);
            }
        }
        fp.close();
        palavra=temp[ind];
    }

};

*/
/*********************************************************************************************************************/

void Jogo::set_palavra(){


    string Temp = {};
    string Palavras[MAX_PALAVRAS];
    int Num_Palavras=0;

    Temp = tema + ".txt";

    ifstream fp;



    fp.open(Temp, ios::in);

    if(!fp.is_open()){
        cout<<" Erro ao abrir o Ficheiro"<<endl;
        fp.close();
        exit(1);
    }


    while(!fp.eof()){

        for(int i=0; i<MAX_PALAVRAS; i++){
            cin.sync();
            getline(fp, Palavras[i]);
            Num_Palavras++;
        }
    }

    //random para escolher o indice da tabela aleatoriamente
    int ind=0;
    srand(time(NULL)); // Seed the time
    ind = rand()%Num_Palavras;         // Gerar um Numero entre 0 e 7 --> 8 palavras por tema
    fp.close();

    palavra=Palavras[ind];


}

/*********************************************************************************************************************/

void Jogo::menu(jogador *p, int ind){

    system("cls");

    string n;

    draw_border();
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+2);  cout<<"*******************|MENU|*******************";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+1+2);cout<<"*                                          *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+2+2);cout<<"*        1 -> Iniciar Jogo                 *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+3+2);cout<<"*        2 -> Modo de funcionamento        *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+4+2);cout<<"*        3 -> Mostrar Pontuacoes           *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+5+2);cout<<"*        4 -> Selecionar Novo Jogador      *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+6+2);cout<<"*                                          *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+7+2);cout<<"*        0 -> Sair                         *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+8+2);cout<<"*                                          *";
    gotoxy(Menu_Pos_X-1,Menu_Pos_Y+9+2);cout<<"********************************************";


    while(1){

        gotoxy(Menu_Pos_X +3, Menu_Pos_Y + 13);cout<<" Selecione uma Opcao: ";

        cin>>n;

        if(n=="1" || n=="2" || n=="3" || n=="0" || n=="4"){
            break;
        }
    }

    switch (stoi(n)) {


    case 1:
        system("cls");
        this->inicia_jogo(p, ind);
        menu(p, ind);
        break;

    case 2:

        system("cls");
        this->menu_funcionameno(p, ind);
        menu(p, ind);

    case 3:

        system("cls");
        draw_border();
        p->Mostrar_Pontuacoes(*this);
        menu(p, ind);
        break;

    case 4:

        system("cls");
        this->Save_Jogo(p);
        Inicio(p);
        break;

    case 0:

        system("pause");
        this->Save_Jogo(p);
        exit(1);
        break;

    default:

        menu(p, ind);


    }

};



/*********************************************************************************************************************/


void Jogo::Save_Jogo(jogador p[]){

    fstream fp;

    fp.open(File_Jogo, ios::in);

    if(fp){
        // Yes, trucate it
        fp.close();
        fp.open(File_Jogo, ios::out | ios::trunc);
        if(!fp){
            cerr<<" Nao foi possivel truncar\n";
            fp.close();
        }else{

            for(int i=0; i<NumJogadores; i++){

                fp << p[i].nome << " " << p[i].escalao << " " << p[i].score << " " << p[i].JogoAtivo << " ";
                fp << this[i].dificuldade << " " << this[i].timer << " " << this[i].tema_alea << " " << this[i].palavra;
                fp << " " << this[i].NumTentativas << " " << this[i].tempo[0] << " " << this[i].tempo[1];
                fp <<"\n";

            }

        }

        fp.close();
    }

    fp.close();

}

/*********************************************************************************************************************/


void Jogo::menu_funcionameno(jogador p[], int ind){

    string n;

    draw_border();
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+1);  cout<<"********************|MENU|*********************";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+1+1);cout<<"*                                             *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+2+1);cout<<"*        1 -> Dificuldade                     *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+3+1);cout<<"*        2 -> Cronometro                      *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+4+1);cout<<"*        3 -> Tema                            *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+5+1);cout<<"*        4 -> Config Temas e Palavras         *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+6+1);cout<<"*                                             *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+7+1);cout<<"*        0 -> Voltar ao Menu Principal        *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+8+1);cout<<"*                                             *";
    gotoxy(Menu_Pos_X-3,Menu_Pos_Y+9+1);cout<<"***********************************************";

    while(!kbhit()){

        gotoxy(Menu_Pos_X,Menu_Pos_Y + 11);cout<<" Selecione uma Opcao: ";


        cin>>n;

        if(n=="1" || n=="2" || n=="3" || n=="0" || n=="4"){
            break;
        }
    }

    switch (stoi(n)) {


    case 1:
        system("cls");
        this[ind].set_dificuldade();
        this->Save_Jogo(p);
        this->menu_funcionameno(p, ind);
        break;
    case 2:
        system("cls");
        this[ind].set_timer(p);
        this->Save_Jogo(p);
        this->menu_funcionameno(p, ind);
        break;

    case 3:
        system("cls");
        this[ind].set_tema_alea(p);
        this->Save_Jogo(p);
        this->menu_funcionameno(p, ind);
        break;

    case 4:
        system("cls");
        this->configTemasPalavras();


    case 0:
        //this->menu(p);

        break;

    }
};


/*********************************************************************************************************************/


void Jogo::set_dificuldade(){

    draw_border();

    string n;

    gotoxy(Menu_Pos_X + 5, Menu_Pos_Y);cout<<" Dificuldade Atual: ";

    if(dificuldade==1){
        gotoxy(Menu_Pos_X + 30, Menu_Pos_Y);cout<<"Facil";
    }else if(dificuldade==2){
        gotoxy(Menu_Pos_X + 30, Menu_Pos_Y);cout<<"Medio";
    }else{
        gotoxy(Menu_Pos_X + 30, Menu_Pos_Y);cout<<"Dificil";
    }

    gotoxy(Menu_Pos_X+ 5 , Menu_Pos_Y+2);cout<<"**********Dificuldade*********";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y +3);cout<<"*                            *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y +4);cout<<"*        1 -> Facil          *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y +5);cout<<"*        2 -> Medio          *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y +6);cout<<"*        3 -> Dificil        *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y +7);cout<<"*                            *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y +8);cout<<"******************************";


    while(!kbhit()){

        gotoxy(Menu_Pos_X+5, Menu_Pos_Y + 10);cout<<" Selecione a Dificuldade: ";

        cin>>n;

        if(n=="1" || n=="2" || n=="3"){
            break;
        }
    }

    dificuldade = stoi(n);


    system("cls");
    //this->menu_funcionameno(p, ind);
};


/*********************************************************************************************************************/


void Jogo::set_timer(jogador p[]){

    string n;

    draw_border();
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y+2);cout<<" Cronometro: ";
    if(timer==1){
        gotoxy(Menu_Pos_X+ 21 , Menu_Pos_Y+2);cout<<"       ON"<<endl;
    }else{
        gotoxy(Menu_Pos_X+ 21 , Menu_Pos_Y+2);cout<<"      OFF"<<endl;
    }

    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +4);cout<<"********Cronometro********";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +5);cout<<"*                        *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +6);cout<<"*        1 -> ON         *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +7);cout<<"*        0 -> OFF        *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +8);cout<<"*                        *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +9);cout<<"**************************";

    while(!kbhit()){

        gotoxy(Menu_Pos_X+ 8 ,  Menu_Pos_Y + 11);cout<<" Selecione uma Opcao: ";
        cin>>n;


        if(n=="1" || n=="0"){
            break;
        }
    }
    timer = stoi(n);

    //Save_Jogo(p);

    system("cls");
    //this->menu_funcionameno(p);
};

/*********************************************************************************************************************/

void Jogo::set_tema_alea(jogador p[]){

    draw_border();

    string n;


    gotoxy(Menu_Pos_X+ 8, Menu_Pos_Y+2);cout<<" Tema Aleatorio: ";
    if(tema_alea==1){
        gotoxy(Menu_Pos_X+ 24, Menu_Pos_Y+2);cout<<"       ON";
    }else{
        gotoxy(Menu_Pos_X+ 24, Menu_Pos_Y+2);cout<<"      OFF";
    }

    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +4);cout<<"******Tema Aleatorio******";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +5);cout<<"*                        *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +6);cout<<"*        1 -> ON         *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +7);cout<<"*        0 -> OFF        *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +8);cout<<"*                        *";
    gotoxy(Menu_Pos_X+ 8 , Menu_Pos_Y +9);cout<<"**************************";


    while(!kbhit()){

        gotoxy(Menu_Pos_X+ 8, Menu_Pos_Y+11);cout<<" Selecione uma Opcao: ";
        cin>>n;


        if(n=="1" || n=="0"){
            break;
        }
    }
    tema_alea = stoi(n);

    //Save_Jogo(p);

    system("cls");
    //this->menu_funcionameno(p);

}


/*********************************************************************************************************************/



void Jogo::set_tema(){

    /* Verificar o Modo de funcionamento:
        on -> option aleatoria do tema
        off -> option do tema pelo utilizador*/

    string Temas[20];

    int ind=0;

    switch(tema_alea) {

    case true : {

        int Num_Temas=obterTemas(Temas);

        tema = Temas[ind];
        srand(time(NULL)); // Seed the time
        ind = rand() % Num_Temas ;    // 3 temas (0, 1, 2)

        tema = Temas[ind];



        break;

    }

    case false: {

        //ind = set_tema_utilizador();
        tema = Temas[ind];


        break;

    }

    }

}

/*********************************************************************************************************************/



int set_tema_aleatoria(){

    /*int n;              // num indice do tema
    srand(time(NULL)); // Seed the time
    n = rand() % 3 ;    // 3 temas (0, 1, 2)

    return n; */

    //int Num_Temas = 0;

    //Num_Temas

};


/*********************************************************************************************************************/
/*
int set_tema_utilizador(){

    int n;


    draw_border();
    gotoxy(Menu_Pos_X, Menu_Pos_Y+2);cout<<"********Temas Disponiveis*******";

    int Num_Temas;

    for(int i=0; i<Num_Temas; i++){
        gotoxy(Menu_Pos_X , Menu_Pos_Y + 4 + i); cout<<" Tema "<<i+1<<" -> "<<temas[i]<<endl;

    }

    gotoxy(Menu_Pos_X , Menu_Pos_Y +9); cout<<"********************************";

    gotoxy(Menu_Pos_X , Menu_Pos_Y + 11); cout<<" option o tema: ";

    while(1){

        cin>>n;

        if(n==1 || n==2 || n==3){
            break;
        }

    }

    system("cls");

    return n-1; // Retornar o numero do indice (0,1,2)
};
*/

/*********************************************************************************************************************/

void Jogo::calcula_timer(int ind){

    // O tempo deve de ser diretamente propocional ao Numero de Letras da palavra e inversamente a Dificuldade

    *tempo = {0};

    int tam = palavra.length();
    const int Tempo_Letra = 20;
    int temp = 0;

    if(this[ind].dificuldade==1){

        temp = tam * Tempo_Letra;        //dificuldade basica

    }else if(this[ind].dificuldade==2){

        temp = tam * Tempo_Letra * 0.75;        // *3/4 dificuldade media

    }else{

        temp = tam * Tempo_Letra * 0.5;          // 1/2 Dificuldade dificil

    }

    while(temp>=60){
        this[ind].tempo[0]+=1;
        temp -=60;
    }

    this[ind].tempo[1] = temp;

}

/*********************************************************************************************************************/


void Jogo::inicia_jogo(jogador *p, int ind){

    //int ind = 0;        //Serve para selecionar o perfil do jogador que vai jogar

    //ind=p->menu_jogador(*this);     //Encontrar o indice do Jogaador

    /* Aplicaçao dos Diferentes Modos */

    string escalao;

    escalao=p[ind].escalao;


    if(p->JogoAtivo==true){

        // Volta ao Jogo

    }

    if(escalao==Escalao[0])     //Modo Elementar de Funcionamento
    {
        this->modo_elementar(&p[ind], ind);
        this->Save_Jogo(p);

        menu(p, ind);

    }

    else if(escalao==Escalao[1]){
        /*Basico tem o Elementar + o possibilidade de usar o cronometro (O cronometro ativa-se no menu de funcionamento) */

        if(this[ind].dificuldade==1){
            this[ind].dificuldade=2;
        }

        if(this[ind].timer==false){
            this->modo_elementar(&p[ind], ind);
            this->Save_Jogo(p);
            menu(p, ind);



        }else {
            if(this[ind].dificuldade==2){         // A dificuldade tem de ser no minimo 2
                this->modo_basico(&p[ind],ind);
                this->Save_Jogo(p);
                this->menu(p, ind);


            }else{
                this->modo_basico(&p[ind],ind);
                this->Save_Jogo(p);
                this->menu(p,ind);

            }

        }

    }

    else{
        timer = true;          //No Modo Medio o timer esta sempre ligado

        if(this[ind].dificuldade==1){     //A dificuldade tem de ser No minimo 2
            this[ind].dificuldade=2;
        }

        this->modo_Medio(&p[ind], ind);
        this->Save_Jogo(p);
        this->menu(p, ind);

    }
    p->JogoAtivo=false;
}
/*********************************************************************************************************************/


bool Menu_pausa(){

    system("cls");

    draw_border();
    bool pausa=true;
    bool temp=true;

    string n;

    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y+2);cout<<"***********Menu Pausa***********";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y+3);cout<<"*                              *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y+4);cout<<"*        1 -> Continuar        *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y+5);cout<<"*        0 -> Sair             *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y+6);cout<<"*                              *";
    gotoxy(Menu_Pos_X+ 5, Menu_Pos_Y+7);cout<<"********************************";


    while(!kbhit()){

        gotoxy(Menu_Pos_X+ 6, Menu_Pos_Y+9);cout<<" Selecione uma Opcao: ";
        cin>>pausa;

        if(pausa==1 || pausa==0){
            break;
        }
    }

    if(pausa==1){
        return pausa;
    }else{
        system("cls");
        draw_border();

        gotoxy(Menu_Pos_X, Menu_Pos_Y);  cout<<"***************Menu Pausa****************";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+1);  cout<<"*   O progresso do jogo sera perdido!   *";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+2);  cout<<"*                                       *";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+3);  cout<<"*     Quer Mesmo sair?                  *";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+4);  cout<<"*                                       *";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+5);  cout<<"*            1 -> Sim                   *";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+6); cout<<"*            0 -> Nao                   *";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+7); cout<<"*                                       *";
        gotoxy(Menu_Pos_X, Menu_Pos_Y+8); cout<<"*****************************************";

        while(!kbhit()){

            gotoxy(Menu_Pos_X + 2, Menu_Pos_Y+10);cout<<" Selecione uma Opcao: ";
            cin>>temp;

            if(temp==1 || temp==0){
                break;
            }
        }

        if (temp==1){
            return pausa;
        }else{
            Menu_pausa();
        }
    }
}


/*********************************************************************************************************************/


void Jogo::modo_elementar(jogador *p, int ind){

    bool play = true;
    bool pause = true;

    char c;


    //if(p[ind].JogoAtivo==false){

    while (play){

        p->JogoAtivo=true;

        this[ind].tema.clear();
        this[ind].palavra.clear();

        this[ind].set_tema();
        this[ind].set_palavra();
        // Defenimos o tema e a palavra

        int size = palavra.size();
        this->clear_palavra(size, ind);

        this[ind].NumTentativas=0;
        // Defenimos o tema e a palavra

        while(1){

            system("cls");
            draw_border();

            if (this[ind].NumTentativas==9){

                this[ind].desenha_forca();
                break;
            }

            if (this[ind].palavra_acertada==true){

                gotoxy(50, 12); cout<<" Acertou a PALAVRA";
                print_ganhou();
                this[ind].verifica_ganhou(p);
                break;
            }


            //system("cls");

            this[ind].desenha_forca();

            gotoxy(55, 18); cout<<" Tema: "<<tema;

            this->print_palavra(ind); //Print da Palavra antes de pedir a letra

            c = this[ind].pedir_letra();

            if(c=='0'){

                pause = Menu_pausa();

                if(pause==false){

                    break;

                    //menu(p);
                }
            }


            this[ind].verifica_palavra(c);
            this->print_palavra(ind);     // Print depois de verificar a letra  para terminar o ciclo no timiing correto

        }
        //his[ind].verifica_ganhou(p);
        play = this->reset_game(ind);

    }

}

//}else {
/*
        while(1){

            system("cls");
            draw_border();

            if (this[ind].NumTentativas==9){

                this[ind].desenha_forca();
                break;
            }

            if (this[ind].palavra_acertada==true){

                gotoxy(50, 12); cout<<" Acertou a PALAVRA";
                print_ganhou();
                this[ind].verifica_ganhou(p);
                break;
            }


            //system("cls");

            this[ind].desenha_forca();

            gotoxy(55, 18); cout<<" Tema: "<<tema;

            this[ind].print_palavra(ind); //Print da Palavra antes de pedir a letra

            c = this[ind].pedir_letra();

            if(c=='0'){

                pause = Menu_pausa();

                if(pause==false){

                    break;

                    //menu(p);
                }
            }


            this[ind].verifica_palavra(c);
            this[ind].print_palavra(ind);     // Print depois de verificar a letra  para terminar o ciclo no timiing correto

        }

        this[ind].verifica_ganhou(p);
        play = this->reset_game(ind);
    }
    p->JogoAtivo=false;

}
*/


/*********************************************************************************************************************/

void Jogo::modo_basico(jogador *p, int ind){

    char c;
    Timer t1;

    bool play = true;
    bool pause = true;

    while(play){

        t1.reset();
        p->timer_state  = true;

        this[ind].NumTentativas=0;

        this[ind].tema.clear();
        this[ind].palavra.clear();

        this[ind].set_tema();
        this[ind].set_palavra();                              // Defenimos o tema e a palavra

        int size = palavra.size();
        this->clear_palavra(size,ind);

        //this[ind].palavra_jogador= {};

        this->calcula_timer(ind);                            // Define o Tempo de Jogo
        t1.run();

        while(1){

            system("cls");
            draw_border();

            if (this[ind].NumTentativas==9 || p->timer_state == false){

                this[ind].desenha_forca();
                t1.stop();
                break;

            }

            if (this[ind].palavra_acertada==true){

                t1.stop();

                break;

            }


            //system("cls");


            this[ind].desenha_forca();

            gotoxy(55, 18); cout<<" Tema: "<<tema;

            this->print_palavra(ind); //Print da Palavra antes de pedir a letra


            gotoxy(45, 29); cout<<" Introduza uma letra: ";
            while(p->timer_state){

                while(kbhit() == false && p->timer_state == true){
                    p->timer_state = t1.set_cronometro(this[ind].tempo);
                }

                gotoxy(67, 29); cin>>c;

                if(c=='0'){

                    t1.run_Pausa();

                    pause = Menu_pausa();


                    if(pause==false){

                        break;

                        //menu(p);
                    }

                    t1.stop_Pausa();

                    break;
                }


                c = tolower(c);
                if(c>='a' && c<='z'){
                    break;
                }
            }

            this[ind].verifica_palavra(c);
            this->print_palavra(ind);     // Print depois de verificar a letra  para terminar o ciclo no timiing correto

        }

        //Caso saia do loop é porque o Temporizador chegou ao fim --> Neste caso o Jogador perde por causa do tempo
        t1.stop();

        // t1.time --> Tempo em segundos


        this[ind].desenha_forca();

        p->bonus_time = (int *)tempo - (int *)t1.time;
        p->bonus_time *= 0.05;
        this[ind].verifica_ganhou(p);
        play = this->reset_game(ind);
    }

    this->Save_Jogo(p);

}

/*********************************************************************************************************************/

void Jogo::modo_Medio(jogador *p , int  ind){

    // Falta dar o print das letras

    char c;
    char Tent_falhadas[10] ;
    Timer t1;

    bool play = true;
    bool pause = true;
    bool acertou = true;


    while(play){

        t1.reset();
        p->timer_state  = true;

        this[ind].tema.clear();
        this[ind].palavra.clear();

        this[ind].set_tema();
        this[ind].set_palavra();
        // Defenimos o tema e a palavra

        int size = palavra.size();
        this->clear_palavra(size, ind);

        this[ind].NumTentativas=0;


        this->calcula_timer(ind);
        //gotoxy(45, 23);
        t1.run();

        while(1){

            system("cls");
            draw_border();

            if (this[ind].NumTentativas==9 || p->timer_state == false){

                this[ind].desenha_forca();
                t1.stop();
                break;


            }

            if (this[ind].palavra_acertada==true){


                t1.stop();

                break;

            }
            //system("cls");

            this[ind].desenha_forca();

            gotoxy(55, 18); cout<<" Tema: "<<tema;

            this->print_palavra(ind); //Print da Palavra antes de pedir a letra
            this[ind].print_tenta_falhadas(Tent_falhadas);
            //c = pedir_letra();

            gotoxy(45, 29); cout<<" Introduza uma letra: ";
            while(p->timer_state){

                while(kbhit() == false && p->timer_state == true){
                    p->timer_state = t1.set_cronometro(this[ind].tempo);


                }

                gotoxy(67, 29) ; cin>>c;

                if(c=='0'){

                    t1.run_Pausa();

                    pause = Menu_pausa();


                    if(pause==false){

                        break;

                        //menu(p);
                    }

                    t1.stop_Pausa();

                    break;
                }


                c = tolower(c);
                if(c>='a' && c<='z'){
                    break;
                }
            }


            acertou = this[ind].verifica_palavra(c);

            if(!acertou){
                //Imprime as letras das quais o utilizador tentou e nao aacertou
                Tent_falhadas[this[ind].NumTentativas-1] = c;

            }


            this->print_palavra(ind);     // Print depois de verificar a letra  para terminar o ciclo no timiing correto
            this[ind].print_tenta_falhadas(Tent_falhadas);
        }

        //Caso saia do loop é porque o Temporizador chegou ao fim --> Neste caso o Jogador perde por causa do tempo
        t1.stop();

        // t1.time --> Tempo em segundos


        //Calcula o Bonus pelo Tempo
        p->bonus_time = (long *)tempo - (long *)t1.time;
        p->bonus_time *= 0.05;

        //system("cls");
        // print_ganhou();
        //gotoxy(50 , 35);cout<<"O Seu Score atual e: "<<p->bonus_time;   // NOVO
        //cout<<" "<<endl;
        //system("pause");

        this[ind].desenha_forca();
        this[ind].verifica_ganhou(p);
        play = this->reset_game(ind);
    }

    this->Save_Jogo(p);
}

/*********************************************************************************************************************/

void Jogo::print_tenta_falhadas(char c[]){


    gotoxy(45, 33); cout<<" Tentativas Falhadas: ";

    for(int i=0; i<NumTentativas; i++){

        gotoxy(45 + 2*i, 35); cout<<c[i];

    }

}


/*********************************************************************************************************************/

void Jogo::desenha_forca(){

    Forca f;

    switch(NumTentativas)
    {
    case 0:
        f.forca_00();
        break;
    case 1:
        f.forca_09();
        break;
    case 2:
        f.forca_08();
        break;
    case 3:
        f.forca_07();
        break;
    case 4:
        f.forca_06();
        break;
    case 5:
        f.forca_05();
        break;
    case 6:
        f.forca_04();
        break;
    case 7:
        f.forca_03();
        break;
    case 8:
        f.forca_02();
        break;
    case 9:
        f.forca_01();
        break;
    }
}

/*********************************************************************************************************************/

void Jogo::print_palavra(int ind){

    int tam_palavra=0;
    tam_palavra = this[ind].palavra.size();
    bool acabado = true;


    for(int i=0; i<tam_palavra; i++)    //Print dos Traços
    {
        if(this[ind].palavra_jogador[i]=='*'){

            gotoxy(50 + 2*i, 27);cout<<"_";

            acabado = false;
        }else{
            gotoxy(50 + 2*i, 27);cout<<this[ind].palavra_jogador[i]<<" ";
        }
    }


    if(acabado==true){
        this[ind].palavra_acertada = true;
    }
    //Verificar se as letras Introduzidas correspondem com a palavra;


}

/*********************************************************************************************************************/

void Jogo::clear_palavra(int size, int ind){

    this[ind].palavra_jogador.clear();

    for(int i=0; i<size; i++){

        this[ind].palavra_jogador[i] = '*';

    }

}


/*********************************************************************************************************************/


char Jogo::pedir_letra(){

    char c;     //Carater que o utilizador introduziu


    gotoxy(45, 29); cout<<" Introduza uma letra: ";
    while(1){

        cin>>c;

        if(c=='0'){
            return c;
        }

        c = tolower(c);
        if(c>='a' && c<='z'){

            return c;
            break;
        }

    }
    puts("");
}


/*********************************************************************************************************************/


bool Jogo::verifica_palavra(char c){

    int n = palavra.size();
    bool acertou=false;


    for(int i=0; i<n; i++){
        if(c == palavra[i]){

            palavra_jogador[i] = c;
            acertou = true;
        }

    }

    if(acertou==false){
        NumTentativas+=1;
    }

    return acertou;

}


/*********************************************************************************************************************/



void Jogo::verifica_ganhou(jogador *p){

    if(palavra_acertada==true){ //Se Ganhou

        atualiza_score(p);
        system("cls");
        print_ganhou();

        gotoxy(50 , 35);cout<<"O Seu Score atual e: "<<p->score;
        cout<<" "<<endl;
        cout<<" "<<endl;
        gotoxy(50 , 37);system("pause");

    }else {

        system("cls");
        draw_border();
        print_perdeu();
        gotoxy(50 , 37);system("pause");
    }


}



/*********************************************************************************************************************/

/*void Jogo::Save_tab_jogadores(jogador p[]){

    fstream fp;

    fp.open(File_Jogadores, ios::in);

    if(fp){
        // Yes, trucate it
        fp.close();
        fp.open(File_Jogadores, ios::out | ios::trunc);
        if(!fp){
            cerr<<" Nao foi possivel truncar\n";
        }else{
            for(int i=0; i<NumJogadores; i++){

                fp<<p[i].nome<< " " <<p[i].escalao<< " " <<p[i].score;
                fp<<"\n";
            }
        }

        fp.close();

    }

    fp.close();
}


*/
/*********************************************************************************************************************/


void print_perdeu(){

    gotoxy(40,17);  cout<<" ________  ________  _____ ______   _______  ";
    gotoxy(40,18);  cout<<" |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\   ";
    gotoxy(40,19);  cout<<"\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|   ";
    gotoxy(40,20);  cout<<" \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  ";
    gotoxy(40,21);  cout<<"  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\   ";
    gotoxy(40,22);  cout<<"   \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\   ";
    gotoxy(40,23);  cout<<"    \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|   ";
    gotoxy(40,24);  cout<<"                                                    ";

    gotoxy(40,25);  cout<<"      ________  ___      ___ _______   ________ ";
    gotoxy(40,26);  cout<<"     |\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\ ";
    gotoxy(40,27);  cout<<"     \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\ ";
    gotoxy(40,28);  cout<<"      \\ \\  \\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\ ";
    gotoxy(40,29);  cout<<"       \\ \\  \\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\  \\| ";
    gotoxy(40,30);  cout<<"        \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\ _\\ ";
    gotoxy(40,31);  cout<<"         \\|_______|\\|__|/       \\|_______|\\|__|\\|__|";

    puts("\n");

}

/*********************************************************************************************************************/


void print_ganhou(){

    draw_border();
    gotoxy(45,20);cout<<"         PARABENS VOCE ACERTOU          ";
    gotoxy(45,21);cout<<"----------------------------------------";
    gotoxy(45,22);cout<<"             ___________                ";
    gotoxy(45,23);cout<<"            '._==_==_=_.'               ";
    gotoxy(45,24);cout<<"            .-\\:      /-.               ";
    gotoxy(45,25);cout<<"           | (|:.     |) |              ";
    gotoxy(45,26);cout<<"            '-|:.     |-'               ";
    gotoxy(45,27);cout<<"              \\::.    /                 ";
    gotoxy(45,28);cout<<"               '::. .'                  ";
    gotoxy(45,29);cout<<"                 ) (                    ";
    gotoxy(45,30);cout<<"               _.' '._                  ";
    gotoxy(45,31);cout<<"               '-----'                 ";
    gotoxy(45,32);cout<<"----------------------------------------";
    gotoxy(45,33);cout<<" "<<endl;

}
/*********************************************************************************************************************/


void Jogo::atualiza_score(jogador *p){

    int N_tentativas_restantes = 9 - NumTentativas;
    // Adicionar o Tempo Restante

    if(p->escalao==Escalao[0])     //Modo Elementar de Funcionamento
    {
        p->score += PONTOS + 1 * N_tentativas_restantes;              //2 Pontos se Acertar a Palavra no Modo Elementar
    }
    if(p->escalao==Escalao[1])
    {
        if(timer==true){

            if(dificuldade==2){

                p->score += PONTOS + 2 * N_tentativas_restantes + p->bonus_time/5000;      // Falta ADICIONAR O BONUS DO TEMPO!!
            }
            else{

                p->score += PONTOS + 1 * N_tentativas_restantes + 2*p->bonus_time/5000;      // Falta ADICIONAR O BONUS DO TEMPO!!
            }

        }
        else{

            if(dificuldade==2){

                p->score += PONTOS + 2 * N_tentativas_restantes;
            }
            else{

                p->score += PONTOS + 2 * N_tentativas_restantes;
            }
        }
    }
    if(p->escalao==Escalao[2]){

        if(dificuldade==2){

            p->score += PONTOS + 4 * N_tentativas_restantes + 2*p->bonus_time/5000;      // Falta ADICIONAR O BONUS DO TEMPO!!
        }
        else{

            p->score += PONTOS + 6 * N_tentativas_restantes + 2*p->bonus_time/5000;      // Falta ADICIONAR O BONUS DO TEMPO!!
        }
    }
}


/*********************************************************************************************************************/


bool Jogo::reset_game(int ind){

    system("cls");
    bool state;

    this[ind].NumTentativas=0;
    this[ind].palavra_acertada=false;

    this[ind].tempo[0] = 0;
    this[ind].tempo[1] = 0;

    draw_border();

    char c;


    gotoxy(50, 24); cout<<" Quer Jogar Novamente (Y\\N) ?";
    while(1){
        cin>>c;
        c = tolower(c);
        if(c=='y' || c == 'n' ){
            break;
        }
    }

    switch (c){

    case 'y':

        return state=true;

    case 'n':

        return state=false;
    }
}

/*********************************************************************************************************************/




/*********************************************************************************************************************/

void draw_border(){

    gotoxy(30,10);cout<<".......................................................................";
    gotoxy(30,11);cout<<".   o   \\ o /  _ o        __|    \\ /     |__         o _  \\ o /   o   .";
    gotoxy(30,12);cout<<".  /|\\    |     /\\   __\\o   \\o    |    o/     o/__   /\\     |    /|\\  .";
    gotoxy(30,13);cout<<".  / \\   / \\   | \\  /) |    ( \\  /o\\  / )    |   (\\  / |   / \\   / \\  .";
    gotoxy(30,14);cout<<".       .....................JOGO DA FORCA.....................       .";
    gotoxy(30,15);cout<<". \\ o / .                                                     . \\ o / .";
    gotoxy(30,16);cout<<".   |   .                                                     .   |   .";
    gotoxy(30,17);cout<<".  / \\  .                                                     .  / \\  .";
    gotoxy(30,18);cout<<".       .                                                     .       .";
    gotoxy(30,19);cout<<".  _ o  .                                                     .  _ o  .";
    gotoxy(30,20);cout<<".   /\\  .                                                     .   /\\  .";
    gotoxy(30,21);cout<<".  | \\  .                                                     .  | \\  .";
    gotoxy(30,22);cout<<".       .                                                     .       .";
    gotoxy(30,23);cout<<".       .                                                     .       .";
    gotoxy(30,24);cout<<".  __\\o .                                                     .  __\\o .";
    gotoxy(30,25);cout<<". /) |  .                                                     . /) |  .";
    gotoxy(30,26);cout<<".       .                                                     .       .";
    gotoxy(30,27);cout<<". __|   .                                                     . __|   .";
    gotoxy(30,28);cout<<".   \\o  .                                                     .    \\o .";
    gotoxy(30,29);cout<<".   ( \\ .                                                     .   ( \\ .";
    gotoxy(30,30);cout<<".       .                                                     .       .";
    gotoxy(30,31);cout<<".  \\ /  .                                                     .  \\ /  .";
    gotoxy(30,32);cout<<".   |   .                                                     .   |   .";
    gotoxy(30,33);cout<<".  /o\\  .                                                     .  /o\\  .";
    gotoxy(30,34);cout<<".       .                                                     .       .";
    gotoxy(30,35);cout<<".  o _  .                                                     .  o _  .";
    gotoxy(30,36);cout<<".  /\\   .                                                     .  /\\   .";
    gotoxy(30,37);cout<<".  / |  .                                                     .  / |  .";
    gotoxy(30,38);cout<<".       .....................JOGO DA FORCA.....................       .";
    gotoxy(30,39);cout<<".   o   \\ o /  _ o        __|    \\ /     |__         o _  \\ o /   o   .";
    gotoxy(30,40);cout<<".  /|\\    |     /\\   __\\o   \\o    |    o/     o/__   /\\     |    /|\\  .";
    gotoxy(30,41);cout<<".  / \\   / \\   | \\  /) |    ( \\  /o\\  / )    |   (\\  / |   / \\   / \\  .";
    gotoxy(30,42);cout<<".......................................................................";
}

void Jogo::Apresenta(){

    draw_border();
    gotoxy(45,22);cout<<"*************|Jogo da Forca|**************";
    gotoxy(45,23);cout<<"*                                        *";
    gotoxy(45,24);cout<<"*    Eduardo Marques - 2020233725        *";
    gotoxy(45,25);cout<<"*    Leonardo Cordeiro - 2020228071      *";
    gotoxy(45,26);cout<<"*                                        *";
    gotoxy(45,27);cout<<"*     Mini-Projeto EDA 22/05/2022        *";
    gotoxy(45,27);cout<<"*                                        *";
    gotoxy(45,28);cout<<"******************************************";

    gotoxy(45,35);system("pause");

}




void Jogo::configTemasPalavras(){

    string temasTab[20];
    int numTemas = obterTemas(temasTab);

    //cout << numTemas;

    //system("pause");

    string option;
    int exit_flag = 0;

    do{

        do{
            system("cls");
            draw_border();
            gotoxy(46+2,22);cout<< "****CONFIGURACAO TEMAS & PALAVRAS****";
            gotoxy(46+2,23);cout<< "*                                   *";
            gotoxy(46+2,24);cout<< "*     0 - Configuracao Temas        *";
            gotoxy(46+2,25);cout<< "*     1 - Configuracao Palavras     *";
            gotoxy(46+2,26);cout<< "*     2 - Sair                      *";
            gotoxy(46+2,27);cout<< "*                                   *";
            gotoxy(46+2,28);cout<< "*************************************";
            gotoxy(46+2,29);cout<< " Option: ";
            cin>> option;
        }while(option != "0" && option != "1" && option != "2");

        switch(stoi(option))
        {
        case 0:
        {
            configTemas(temasTab, numTemas);
            break;
        }

        case 1:
        {
            modifica();
            break;
        }
        case 2:
            exit_flag = 1;
            break;
        }

    }while(exit_flag != 1);

    readTemas(temasTab, numTemas);

}


void Jogo::configTemas(string temasTab[], int &numTemas) {
    string option;
    int exit_flag = 0;

    do{
        do{
            system("CLS");
            draw_border();
            gotoxy(46,22);cout<<   "********CONFIGURACAO TEMAS********";
            gotoxy(46,22+1);cout<< "*                                *";
            gotoxy(46,22+2);cout<< "*         1 - Inserir            *";
            gotoxy(46,22+3);cout<< "*         2 - Apagar             *";
            gotoxy(46,22+4);cout<< "*         3 - Modificar          *";
            gotoxy(46,22+5);cout<< "*         0 - Voltar             *";
            gotoxy(46,22+6);cout<< "*                                *";
            gotoxy(46,22+7);cout<< "**********************************";
            gotoxy(46,22+8);cout<< " Option: ";
            cin>> option;
        }while(option != "1" && option != "2" && option != "3" && option != "0");

        switch(stoi(option))
        {
        case 1:
        {


            system("cls");
            draw_border();



            string newTema1;
            gotoxy(46,22);cout << "Tema: ";
            cin >> newTema1;

            string newTema = newTema1 + ".txt";
            fstream tema;
            tema.open(newTema,  fstream::in | fstream::out | fstream::trunc);

            if(!tema){
                cout << "Erro ao criar o ficheiro";
                system("pause");
            }
            else{
                temasTab[numTemas] = newTema1;
                numTemas++;
                readTemas(temasTab, numTemas);

                gotoxy(46,23);cout << "Tema criado com sucesso!";
                gotoxy(46,24);system("pause");
            }

            tema.close();

            string temaTab[20];
            int num_palavras = 0;

            while(num_palavras<8){


                string newWord;
                gotoxy(46,28);cout << "Palavra: ";cin >> newWord;

                for(int i=0; i < newWord.length(); i++){

                    char c = newWord[i];
                    newWord[i] = tolower(c);
                }



                temaTab[num_palavras] = newWord;
                num_palavras++;
                system("cls");
                draw_border();
                gotoxy(46,26);cout << "Palavra adicionada com sucesso! ";


            }

            ofstream Tema_2;
            Tema_2.open(newTema, ios::trunc);
            if(!Tema_2.is_open()){
                cout << "ERRO ao abrir ficheiro";
                system("pause");
            }
            for(int k = 0; k<num_palavras; k++){
                Tema_2 << temaTab[k];
                Tema_2<<endl;
            }
            Tema_2.close();


            break;
        }
        case 2:
        {

            system("cls");
            draw_border();
            string newTema1;
            gotoxy(46,23);cout << "Tema a apagar: ";cin >> newTema1;
            while(newTema1.compare("Animais") == 0 ||newTema1.compare("Marcas") == 0 ||newTema1.compare("Capitais") == 0){
                system("cls");
                gotoxy(46,25);cout<< "ERROR: Impossivel apagar este tema!";
                gotoxy(46,26);cout << "Introduza outro tema a apagar: ";cin >> newTema1;
            }
            string newTema = newTema1 + ".txt";
            apagarFicheiro(newTema, newTema1, temasTab, numTemas);
            numTemas--;


            readTemas(temasTab, numTemas);

            break;
        }
        case 3:
        {

            modifica();
            break;
        }
        case 0:
        {

            exit_flag=1;
            break;
        }

        }

    }while(exit_flag != 1);

}



void Jogo::modifica(){


    system("cls");
    draw_border();
    string newTema1;
    gotoxy(46,23);cout << "Tema: ";
    cin >> newTema1;

    string newTema = newTema1 + ".txt";
    fstream tema;
    tema.open(newTema);

    while(!tema.is_open()){

        gotoxy(46,25);cout << "ERROR: Tema nao Existente.";
        gotoxy(46,26);system("pause");

        system("cls");
        newTema1.clear();
        draw_border();
        gotoxy(46,23);cout << "Tema: ";
        cin >> newTema1;

        newTema = newTema1 + ".txt";
        tema.open(newTema);
    }

    string temaTab[20];
    int i = 0;
    int num_palavras = 0;
    while(tema.peek() != EOF){
        tema >> temaTab[i];
        i++;
        num_palavras++;
    }
    tema.close();



    string option;
    int terminar = 0;
    while(terminar != 1)
    {
        system("CLS");
       draw_border();

        gotoxy(46,21 -5);cout<< "**************TEMA**************";
        for(int j = 0; j < num_palavras ; j++){
            gotoxy(46,22+j +1 -5);cout << newTema1 << "[" << j << "]: " << temaTab[j];;
        }
        gotoxy(46, 22+num_palavras);cout<< "********************************";

        do{
            gotoxy(46,22+num_palavras+2 -5);cout<< "********CONFIGURACAO PALAVRAS********";
            gotoxy(46,22+num_palavras+3 -5);cout<< "*                                   *";
            gotoxy(46,22+num_palavras+4-5);cout<< "*         1 - Alterar Palavra       *";
            gotoxy(46,22+num_palavras+5-5);cout<< "*         2 - Apagar Palavra        *";
            gotoxy(46,22+num_palavras+6-5);cout<< "*         3 - Acrescentar Palavra   *";
            gotoxy(46,22+num_palavras+7-5);cout<< "*         0 - Terminar              *";
            gotoxy(46,22+num_palavras+8-5);cout<< "*                                   *";
            gotoxy(46,22+num_palavras+9-5);cout<< "*************************************";
            gotoxy(46,22+num_palavras+10-5);cout<< " Option: ";
            cin>> option;
        }while(option != "0" && option != "1" && option != "2" && option != "3");

        switch(stoi(option))
        {
        case 1 :
        {
            int linha;
            do{
                system("cls");
                draw_border();
                gotoxy(46,23);cout << "Linha: ";cin >> linha;
            }while(linha < 1 || linha > num_palavras);

            string newWord;
            gotoxy(46,24);cout << "Palavra Nova: "; cin >> newWord;

            temaTab[linha-1].clear();
            temaTab[linha-1].insert(0,newWord);

            system("cls");
            draw_border();
            gotoxy(46,23);cout << "Palavra alterada com sucesso! ";
            gotoxy(46,24);system("pause");

            break;

        }
        case 2 :
        {
            system("cls");
            draw_border();
            if(removeWord(temaTab, num_palavras)){
                gotoxy(46,23);cout << "Palavra removida com sucesso";
                num_palavras--;
                gotoxy(46,24);system("pause");
            }else{
                gotoxy(46,26);cout << "Impossivel remover. Minimo de 8 words";
                system("pause");
            }

            break;
        }
        case 3 :
        {
            string newWord;
            gotoxy(46, 37);cout << "Palavra Nova: ";cin >> newWord;
            for(int i=0; i < newWord.length(); i++){

                char c = newWord[i];
                newWord[i] = tolower(c);
            }
            temaTab[num_palavras] = newWord;
            num_palavras++;
            system("cls");
            draw_border();
            gotoxy(46,26);cout << "Palavra adicionada com sucesso! ";
            gotoxy(46,27);system("pause");
            break;
        }

        case 0 :
        {
            terminar = 1;
            break;
        }
        }


        ofstream Tema_2;
        Tema_2.open(newTema, ios::trunc);
        if(!Tema_2.is_open()){
            gotoxy(46,23); cout << "Erro ao abrir ficheiro";
            gotoxy(46,24); system("pause");
        }
        for(int k = 0; k<num_palavras; k++){
            Tema_2 << temaTab[k];
            Tema_2<<endl;
        }
        Tema_2.close();



    }
}

bool Jogo::removeWord(string tab[], int dim){

    if(dim < 9) return false;

    int linha;
    do{
        system("cls");
        draw_border();
        gotoxy(46,23);cout << "Linha: ";cin >> linha;
    }while(linha <= 1 || linha >= dim);

    string aux[dim];
    int j = 0;

    for(int i = 0; i<dim ; i++){
        if(i != linha){
            aux[j] = tab[i];
            j++;
        }
    }

    tab = aux;

    return true;
}



void Jogo::apagarFicheiro(string fileName, string tema, string temasTab[], int numTemas){

    string aux[numTemas];
    int j = 0;

    for(int i = 0; i<numTemas ; i++){
        if(temasTab[i].compare(tema) != 0){
            aux[j] = temasTab[i];
            j++;
        }
    }

    temasTab = aux;

    int status;
    const char *filename = fileName.c_str();
    status = remove(filename);
    if(status==0)
    {
        gotoxy(46,23);cout<<"Tema apagado com sucesso!";
        gotoxy(46,24);system("pause");
    }
    else
    {
        gotoxy(46,27);cout<<"Erro!!";
        gotoxy(46,27);system("pause");
    }
}


int Jogo::obterTemas(string *temasTab){

    int contaTemas = 0;

    ifstream filetemas;
    filetemas.open("Temas.txt");
    if ( !filetemas.is_open() ) {
        cout << "Erro ao abrir o ficheiro para leitura!" << endl;
        system("pause");
    }

    while(filetemas.peek() != EOF){
        filetemas >> temasTab[contaTemas];
        contaTemas++ ;
    }

    filetemas.close();

    return contaTemas;
}


void Jogo::readTemas(string temasTab[], int numTemas){

    ofstream filetemas;
    filetemas.open("Temas.txt", ios::trunc);
    if ( !filetemas.is_open() ) {
        cout << "Erro ao abrir o ficheiro para leitura!" << endl;
        system("pause");
    }

    for(int i = 0; i < numTemas; i++){
        filetemas << temasTab[i];

        if(i != numTemas-1){
            filetemas << endl;
        }
    }

    filetemas.close();
}



bool Jogo::temaExiste(string tema, string tab[], int dim){
    for(int i=0; i<dim; i++){
        if(tab[i].compare(tema) == 0){
            return true;
        }
    }
    return false;
}










