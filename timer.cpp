#include "timer.h"
#include "gotoxy.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

const double pps = CLOCKS_PER_SEC;
const int Pos_Time_X = 30;
const int Pos_Time_Y = 28;


Timer::Timer(){

    active = false;
    t0 = {};
    t1 = {};

    t0_pausa = {};
    t1_pausa = {};

    pausa = 0;


}

void Timer::run(){

    active = true;
    t0 = clock();
}

void Timer::stop(){
    if(active){
        active = false;
        t1 = clock();
        time = t1 - t0;
    }
}

void Timer::run_Pausa(){

    t0_pausa = clock();
}

void Timer::stop_Pausa(){

    t1_pausa = clock();
    int pausa_temp = t1_pausa - t0_pausa;
    pausa += pausa_temp;
}

void Timer::reset()
{
    active = false;
    t0 = clock_t();
    t1 = clock_t();
    t0_pausa = clock_t();
    t1_pausa = clock_t();
    pausa = 0; //Faz Reset
}

double Timer::get_time()
{

    return ((active ? clock(): t1)-t0)/pps;
}

bool Timer::set_cronometro(int *tempo)       /* tempo[0] --> Minutos; tempo[1] --> Segundos*/
{


    int time_real[] = {};

    int time_set = 0;

    t1 = clock();

    int m = tempo[0];
    int s = tempo[1];

    long int pausa_temp = pausa;

    time = t1 - t0;
    pausa_temp /=1000;
    time /=1000;
    time = time - pausa_temp;

    time_set = m*60;
    time_set += s;

    if(time>time_set){
        return false;
    }

    time = time_set - time;

    time_real[0] = time / 60;
    time_real[1] = time % 60;


    print_time(time_real);
    return true;
}

void Timer::print_time(int *tempo)
{

     gotoxy(50, 23);cout<<"Restam: "<<tempo[0]<<":"<<tempo[1];

}



