#include <iostream> 
#include <pthread.h>
#include "gpio.h"

volatile int i;
volatile int j;

using namespace std;

pthread_mutex_t mutex;
pthread_cond_t cond; 

void *workerThread(void *arg)
{
    while(1)
    {
        cout <<"we are in thread" <<endl;
        pthread_mutex_lock(&mutex);
        i = i+1;
        j= j+10; 
        pthread_mutex_unlock(&mutex);
        if(i ==10)
          i =0;
        RaspiGpio::milisecondDelay(500);
    }
    pthread_exit(NULL);
}


int main()
{

    pthread_t threads;
    i = 0; 
    j = 0;
    cout <<"begin in Main"<<endl;
    pthread_mutex_init(&mutex ,0);
    pthread_cond_init(&cond,0);
    pthread_create(&threads,NULL,workerThread,NULL);
    
    while(1)
    {   
     pthread_mutex_lock(&mutex);
     cout <<"i = " <<i <<endl;
     cout <<"j = "<< j<<endl;
     pthread_mutex_unlock(&mutex);
    }

    
    return 0;
}
