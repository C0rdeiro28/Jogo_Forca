#ifndef TIMER_H
#define TIMER_H

#include <ctime>

using namespace std;

using std::clock;
using std::clock_t;

class Timer
{    
private:

    clock_t t0, t1, t0_pausa, t1_pausa;

public:

    bool active;       /*Variaveis Publicas para poder acder na classe Jogo*/
    long int time;
    long int pausa;
    Timer();
    void run();
    void stop();
    void reset();
    bool set_cronometro(int *tempo); //tempo[0] -> Minutos; tempo[1] --> Segundos
    double get_time();
    void print_time(int tempo[]);
    void run_Pausa();
    void stop_Pausa();



};

#endif // TIMER_H
