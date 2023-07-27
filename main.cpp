#include <jogo.h>
#include <timer.h>
#include <fstream>

using namespace std;

const int MAX_JOGADORES = 20;


const string File_Jogo = "Jogo_backup.txt";

int main(){

    /*  bool state = true;

    int tempo[2] = {1, 15};
    Timer t1;

    t1.run();

    while(state){
        state = t1.set_cronometro(tempo);
    }
*/



    //memory allocation


    //jogador p[MAX_JOGADORES];


    //  Load DATA Jogadores Anteriores

/*    fstream myfile;

    myfile.open(File_Jogadores, ios::in);

    if(!myfile.is_open()){

        cout<<" ERRO AO CARREGADR A DATA!! ";
        return -1;
    }

    if(myfile.peek() == EOF){

        j1.NumJogadores = 0;

    }else{

        j1.NumJogadores = -1;

        while(myfile.peek() != EOF){

            j1.NumJogadores++;

            myfile >> p[j1.NumJogadores].nome >> p[j1.NumJogadores].escalao >>  p[j1.NumJogadores].score;
            //cout << p[j1.NumJogadores].nome << p[j1.NumJogadores].escalao <<  p[j1.NumJogadores].score;
        }
    }

    myfile.close();

    */

    // Load das settings do jogo anterior, timer dificuldade e tema aleatorio

    while(1){

         Jogo * j1= new Jogo[MAX_JOGADORES];
         jogador *p = new jogador[MAX_JOGADORES];

         int ind;

         j1->Load_Jogo(p);

         ind = p->menu_jogador(*j1);

         j1[ind].NumJogadores=j1->NumJogadores;

         j1->menu(p, ind);

         delete [] p;
         delete [] j1;

    }



    //j1->Apresenta();

    //j1->menu(p);




    return 0;
}


