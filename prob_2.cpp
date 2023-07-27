#include <iostream>

using namespace std;


class CClock{

protected:

    int horas;
    int minutos;

public:
    CClock(){
        horas= 0;
        minutos = 0;
    }

    CClock(int h, int m){
        horas = h;
        minutos = m;
    }

    CClock(const CClock&r){ // Construtor por cópia. & significa que é um parametro por referência

        horas = r.horas;
        minutos = r.minutos;

    }

    CClock operator +(int m){
        minutos += m;

        while (minutos >= 60){
            horas += 1;
            minutos -= 60;
        }

    }

    void print (){
        cout << horas << ":" << minutos << endl;
    }

};

class CViagem :  CClock{
private:
    int tempo;

public:

    void simultanea(CViagem &v1);

    CViagem();  // DECLARAÇÃO
    CViagem(int h, int m, int tempo); // DECLARAÇÃO

    void print (){
        cout << horas << ":" << minutos <<"tempo: " <<tempo<<endl;
    }

};


CViagem :: CViagem (){

    tempo = 80;         // DEFINIÇÃO
};



CViagem :: CViagem (int h, int m, int t){
    horas = h;
    minutos = m;        // DEFINIÇÃO
    tempo = t;
};


void CViagem :: simultanea(CViagem &v1){




};




int main()
{
    CViagem v;
    v.print();


    return 0;
}
