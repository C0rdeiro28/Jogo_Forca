#include <jogo.h>
#include <gotoxy.h>


const string Escalao[]={"Elementar","Basico","Medio"};

void draw_border2();
/*********************************************************************************************************************/

void jogador::set_jogador(Jogo &J1){

    score = 0;

    system("cls");
    draw_border2();
    gotoxy(46,25);cout<<" Digite o Seu UserName: ";

    while(1){
        getline(cin, nome);
        if(!nome.empty()){
            break;
        }
    }

    // Escalao do Jogador

    string num ;

    draw_border2();
    gotoxy(49,22);cout<<"***********|Escalao|************";
    gotoxy(49,23);cout<<"*                              *";
    gotoxy(49,24);cout<<"*        1 -> Elementar        *";
    gotoxy(49,25);cout<<"*        2 -> Basico           *";
    gotoxy(49,26);cout<<"*        3 -> Medio            *";
    gotoxy(49,27);cout<<"*                              *";
    gotoxy(49,28);cout<<"********************************";


    while(!kbhit()){

        gotoxy(50,30);cout<<" Selecione o seu Escalao: ";
        cin>>num;

        if(num=="1" || num=="2" || num=="3"){
            break;
        }
    }

    int n = stoi(num);
    switch (n) {

    case 1:
        escalao = Escalao[n-1];
        break;
    case 2:
        escalao = Escalao[n-1];
        break;

    case 3:
        escalao = Escalao[n-1];
        break;
    }

    J1.NumJogadores+=1;

    cin.ignore(20, '\n');


}


/*********************************************************************************************************************/



void jogador::print_jogador(){

    cout<<"Nome: "<<nome<<"\n";
}


/*********************************************************************************************************************/


int jogador::menu_jogador(Jogo &J1){

    system("cls");

    string n;
    int player = 0;
    bool verifica = false;

    draw_border2();
    gotoxy(46,22);cout<<"*************|Iniciar Jogo|*************";
    gotoxy(46,23);cout<<"*                                      *";
    gotoxy(46,24);cout<<"*        1 -> Novo Jogador             *";
    gotoxy(46,25);cout<<"*        2 -> Jogador Existente        *";
    gotoxy(46,26);cout<<"*                                      *";
    gotoxy(46,27);cout<<"*        0 -> Voltar Atras             *";
    gotoxy(46,28);cout<<"*                                      *";
    gotoxy(46,29);cout<<"****************************************";


    while(!kbhit()){

        gotoxy(45,32);cout<<" Selecione uma Opcao: ";
        cin>>n;

        if(n=="1" || n=="2" || n=="0"){
            break;
        }
    }

    switch (stoi(n)) {

    case 1:
        system("cls");
        this[J1.NumJogadores].set_jogador(J1);
        cout<<J1.NumJogadores;
        return J1.NumJogadores-1;
        break;
    case 2:

    {
        system("cls");
        cout<<setw(20)<<"******Jogadores Inscritos******\n"<<endl;

        this->print_jogadores(J1);

        //cout<<setw(20)<<"\n 0 -> Voltar Atras "<<endl;

        while(!verifica){

            //cout<<setw(20)<<"Selecione um jogado: "<<endl;
            cin>>player;

            if(player==0){
                menu_jogador(J1);
            }

            for(int i=0; i<J1.NumJogadores; i++)
                if(player==i+1){

                    verifica = true;
                    return i;
                    break;
                }
        }
    }

        break;

    case 0:

        break;

       // J1.menu(this);
    }
}

/*********************************************************************************************************************/



void jogador::print_jogadores(Jogo &J1){

    //Organizados por ordem Alfabetica

    system("cls");
    draw_border2();

    gotoxy(46,21);cout<<"***************************************";
    gotoxy(46,22);cout<<"                 Nome:                 ";
    cout<<"\n"<<endl;

    int i;
    for( i=0; i<J1.NumJogadores; i++){
        gotoxy(48,24 +i); cout<<i+1<<" - "<<this[i].nome<<endl;
    }
    gotoxy(46,26 +i );cout<<"  0 -> Voltar Atras        ";
    gotoxy(46,27 +i +1);cout<<"***************************************";
    gotoxy(46,29 +i +1);cout<<"         Selecione um jogador: ";


}

/*********************************************************************************************************************/

void jogador::Mostrar_Pontuacoes(Jogo &J1){


    const int Pos_X = 44;
    const int Pos_Y = 19;

    //Ordenar as pontuaçoes da maior para a menor

    int j;
    jogador aux;

    for( int i = 0; i<J1.NumJogadores; i++){  // n-1 interaçoes

        j=i;

        while( (j>0) && (this[j].score > this[j-1].score)){

            aux = this[j];
            this[j] = this[j-1];              //Desloca os elementos para a direita ate chegar
            this[j-1] = aux;                 //à posição de inserção insere o elemento no indice j
            j--;
        }


        gotoxy(Pos_X+10, Pos_Y-2); cout<<"**Tabela de Pontuacoes**";
        gotoxy(Pos_X, Pos_Y); cout<<"Nomes:";
        gotoxy(Pos_X+29, Pos_Y); cout<<"Pontos:";

    }
    int i;
    for(i=0; i<J1.NumJogadores; i++){

        gotoxy(Pos_X +2, Pos_Y+2+i);cout<<i+1<<" - "<<this[i].nome;
        gotoxy(Pos_X+31, Pos_Y+2+i); cout<<this[i].score;

    }

    puts("\n");
    gotoxy(Pos_X, Pos_Y+5+i); system("pause");

}




/*********************************************************************************************************************/





void draw_border2(){

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
    gotoxy(30,35);cout<<".  o _ .                                                       .  o _  .";
    gotoxy(30,36);cout<<".  /\\   .                                                     .  /\\   .";
    gotoxy(30,37);cout<<".  / |  .                                                     .  / |  .";
    gotoxy(30,38);cout<<".       .....................JOGO DA FORCA.....................       .";
    gotoxy(30,39);cout<<".   o   \\ o /  _ o        __|    \\ /     |__         o _  \\ o /   o   .";
    gotoxy(30,40);cout<<".  /|\\    |     /\\   __\\o   \\o    |    o/     o/__   /\\     |    /|\\  .";
    gotoxy(30,41);cout<<".  / \\   / \\   | \\  /) |    ( \\  /o\\  / )    |   (\\  / |   / \\   / \\  .";
    gotoxy(30,42);cout<<".......................................................................";
}


