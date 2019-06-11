#include <iostream>
#include <pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"
#include <unistd.h> //sleep
#include <time.h>   //nanosleep
#include <sched.h>  //sched

using namespace std;
using namespace BlackLib;

#define MIN_TIME 500
#define MAX_TIME 4500
#define SECOND 1000

enum Rails {
    rail1 = 0,   /* train 1 */
    rail2 = 1,   /* train 1 */
    rail3 = 2,   /* train 1 */
    rail4 = 3,   /* train 2 */
    rail5 = 4,   /* train 2 */
    rail6 = 5,   /* train 2 */
    rail7 = 6,   /* train 3 */
    rail8 = 7,   /* train 3 */
    rail9 = 8,   /* train 4 */
    rail22 = 9,  /* train 2 */       
    rail33 = 10, /* train 4 */
    rail55 = 11, /* train 3 */
    rail66 = 12, /* train 4 */
    rail88 = 13  /* train 4 */
};

enum Trains
{
    train1 = 0,
    train2 = 1,
    train3 = 2,
    train4 = 3
};

/* array Structure to hold the waiting times of each train (or thread) */
struct timespec times[4];

/* GPIO outputs array-like list */
BlackGPIO leds[14] = {BlackGPIO(GPIO_67, output, FastMode),
                      BlackGPIO(GPIO_68, output, FastMode),
                      BlackGPIO(GPIO_44, output, FastMode),
                      BlackGPIO(GPIO_26, output, FastMode),
                      BlackGPIO(GPIO_46, output, FastMode),
                      BlackGPIO(GPIO_65, output, FastMode),
                      BlackGPIO(GPIO_61, output, FastMode),
                      BlackGPIO(GPIO_66, output, FastMode),
                      BlackGPIO(GPIO_69, output, FastMode),
                      BlackGPIO(GPIO_45, output, FastMode),
                      BlackGPIO(GPIO_47, output, FastMode),
                      BlackGPIO(GPIO_27, output, FastMode),
                      BlackGPIO(GPIO_48, output, FastMode),
                      BlackGPIO(GPIO_49, output, FastMode)}; 

/* Mutexes for each Rail */
pthread_mutex_t mtx_rail[9] = {PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER,
                               PTHREAD_MUTEX_INITIALIZER};

/* Mutexes for train velocity changing */
pthread_mutex_t mutex[4] = {PTHREAD_MUTEX_INITIALIZER,
                            PTHREAD_MUTEX_INITIALIZER,
                            PTHREAD_MUTEX_INITIALIZER,
                            PTHREAD_MUTEX_INITIALIZER};    

void* train_1(void* argc){

    struct timespec t;

    while (true){
        /* the current railroad is only available when train 1 
         * is able to lock the mutex of the next railroad.
         */
        
        pthread_mutex_lock(&mtx_rail[rail1]);
        leds[rail3].setValue(low);
        leds[rail1].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail3]);

        /* train 1 stays on the railroad for t nanoseconds */
        pthread_mutex_lock(&mutex[train1]);
        t = times[train1];
        pthread_mutex_unlock(&mutex[train1]);

        cout << "Train 1 is on railroad 1\n";
        nanosleep(&t, NULL);

        /* To avoid deadlock in the region among the rails 2, 3, and 6
         * before holding the railroad 2, train 1 must lock the railroad
         * 3 for himself */

        pthread_mutex_lock(&mtx_rail[rail3]);{
            pthread_mutex_lock(&mtx_rail[rail2]);{
                leds[rail1].setValue(low);
                leds[rail2].setValue(high);
                pthread_mutex_unlock(&mtx_rail[rail1]);

                pthread_mutex_lock(&mutex[train1]);
                t = times[train1];
                pthread_mutex_unlock(&mutex[train1]);

                cout << "Train 1 is on railroad 2\n";
                nanosleep(&t, NULL);

                leds[rail2].setValue(low);
                leds[rail3].setValue(high);
            }
        pthread_mutex_unlock(&mtx_rail[rail2]);

        pthread_mutex_lock(&mutex[train1]);
        t = times[&train1];
        pthread_mutex_unlock(&mutex[train1]);

        cout << "Train 1 is on railroad 3\n";
        nanosleep(&t, NULL);
        }
    }
}

void* train_2(void* argc){

    struct timespec t;

    while (true){
        
        /* Getting the lock for the railroad 4 */

        pthread_mutex_lock(&mtx_rail[rail4]);
        leds[rail22].setValue(low);
        leds[rail4].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail2]);

        pthread_mutex_lock(&mutex[train2]);
        t = times[train2];
        pthread_mutex_unlock(&mutex[train2]);

        cout << "Train 2 is on railroad 4\n";
        nanosleep(&t, NULL);

        /* Getting the lock for the railroad 5 */

        pthread_mutex_lock(&mtx_rail[rail5]);
        leds[rail4].setValue(low);
        leds[rail5].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail4]);

        pthread_mutex_lock(&mutex[train2]);
        t = times[train2];
        pthread_mutex_unlock(&mutex[train2]);

        cout << "Train 2 is on railroad 5\n";
        nanosleep(&t, NULL);

        /* Getting the lock for the railroad 6 */

        pthread_mutex_lock(&mtx_rail[rail6]);
        leds[rail5].setValue(low);
        leds[rail6].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail5]);

        pthread_mutex_lock(&mutex[train2]);
        t = times[train2];
        pthread_mutex_unlock(&mutex[train2]);

        cout << "Train 2 is on railroad 6\n";
        nanosleep(&t, NULL);

        /* Getting the lock for the railroad 2 */

        pthread_mutex_lock(&mtx_rail[rail2]);
        leds[rail6].setValue(low);
        leds[rail2].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail6]);

        pthread_mutex_lock(&mutex[train2]);
        t = times[train2];
        pthread_mutex_unlock(&mutex[train2]);

        cout << "Train 2 is on railroad 2\n";
        nanosleep(&t, NULL);
    }
}

void* train_3(void* argc){
    
    struct timespec t;

    while (true){

        /* Getting the lock for the railroad 7 */

        pthread_mutex_lock(&mtx_rail[rail7]);
        leds[rail5].setValue(low);
        leds[rail7].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail5]);

        pthread_mutex_lock(&mutex[train3]);
        t = times[train3];
        pthread_mutex_unlock(&mutex[train3]);

        cout << "Train 3 is on railroad 7\n";
        nanosleep(&t, NULL); 

        /* To avoid deadlock in the region among the rails 5, 6, and 8
         * before holding the railroad 8, train 3 must lock the railroad
         * 5 for himself */

        pthread_mutex_lock(&mtx_rail[rail5]);{
            pthread_mutex_lock(&mtx_rail[rail8]);{
                leds[rail7].setValue(low);
                leds[rail8].setValue(high);
                pthread_mutex_unlock(&mtx_rail[rail7]);

                pthread_mutex_lock(&mutex[train3]);
                t = times[train3];
                pthread_mutex_unlock(&mutex[train3]);

                cout << "Train 3 is on railroad 8\n";
                nanosleep(&t, NULL);

                leds[rail8].setValue(low);
                leds[rail55].setValue(high);
            }
        pthread_mutex_unlock(&mtx_rail[rail8]);

        pthread_mutex_lock(&mutex[train3]);
        t = times[&train3];
        pthread_mutex_unlock(&mutex[train3]);

        cout << "Train 3 is on railroad 5\n";
        nanosleep(&t, NULL);
        }
    }    
}

void* train_4(void* argc){

    struct timespec t;

    while (true){
        
        /* Getting the lock for the railroad 9 */

        pthread_mutex_lock(&mtx_rail[rail9]);
        leds[rail88].setValue(low);
        leds[rail9].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail8]);

        pthread_mutex_lock(&mutex[train4]);
        t = times[train4];
        pthread_mutex_unlock(&mutex[train4]);

        cout << "Train 4 is on railroad 9\n";
        nanosleep(&t, NULL);

        /* Getting the lock for the railroad 3 */

        pthread_mutex_lock(&mtx_rail[rail3]);
        leds[rail9].setValue(low);
        leds[rail33].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail9]);

        pthread_mutex_lock(&mutex[train4]);
        t = times[train4];
        pthread_mutex_unlock(&mutex[train4]);

        cout << "Train 4 is on railroad 3\n";
        nanosleep(&t, NULL);

        /* Getting the lock for the railroad 6 */

        pthread_mutex_lock(&mtx_rail[rail6]);
        leds[rail33].setValue(low);
        leds[rail66].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail3]);

        pthread_mutex_lock(&mutex[train4]);
        t = times[train4];
        pthread_mutex_unlock(&mutex[train4]);

        cout << "Train 4 is on railroad 6\n";
        nanosleep(&t, NULL);

        /* Getting the lock for the railroad 8 */

        pthread_mutex_lock(&mtx_rail[rail8]);
        leds[rail66].setValue(low);
        leds[rail88].setValue(high);
        pthread_mutex_unlock(&mtx_rail[rail6]);

        pthread_mutex_lock(&mutex[train4]);
        t = times[train4];
        pthread_mutex_unlock(&mutex[train4]);

        cout << "Train 4 is on railroad 8\n";
        nanosleep(&t, NULL);
    }
}

int main(){
    
    /* allocating an array of threads (trains) */
    pthread_t threads[4];

    /* Speeds of the trains */
    ADC analog_input[4] = {
                            ADC(AIN0), /* potentiometer - speed of the train 1 */
                            ADC(AIN2), /* potentiometer - speed of the train 2 */
                            ADC(AIN6), /* potentiometer - speed of the train 3 */
                            ADC(AIN4)  /* potentiometer - speed of the train 4 */
                          }

    /* Setting threads priorities to the same ground */
    struct sched_param priority;
    priority.sched_priority = 5;

    /* Setting priority of main thread to 5 */
    sched_setscheduler(0, SCHED_FIFO, &priority);

    pthread_create(&threads[train1], NULL, train_1, NULL);
    pthread_create(&threads[train2], NULL, train_2, NULL);
    pthread_create(&threads[train3], NULL, train_3, NULL);
    pthread_create(&threads[train4], NULL, train_4, NULL);

    /* Setting priority of train threads to 1 
     * this ensures that the main thread will 
     * not lose control over the other threads
     */
    priority.sched_priority = 1;
    pthread_setschedparam(threads[train1], SCHED_FIFO, &priority);
    pthread_setschedparam(threads[train2], SCHED_FIFO, &priority);
    pthread_setschedparam(threads[train3], SCHED_FIFO, &priority);
    pthread_setschedparam(threads[train4], SCHED_FIFO, &priority);

    int value = 0;
    
    while (true){

        /* Getting analog input for the train 1 
         * and set the analog input to the range 
         * of 500 to 4500 ms
         */

        value = MIN_TIME + MAX_TIME * analog_input[train1].getPercentValue() / 100.0;

        pthread_mutex_lock(&mutex[train1]);{
            times[train1].tv_sec = value / SECOND;
            times[train1].tv_nsec = (valor % SECOND) * 1000000L;
            cout << "Sleeping time of train 1: " << times[train1].tv_sec << 
                ":" times[train1].tv_nsec << "\n";
        }
        pthread_mutex_unlock(&mutex[train1]);

        /* Getting analog input for the train 2 */
        
        value = MIN_TIME + MAX_TIME * analog_input[train2].getPercentValue() / 100.0;

        pthread_mutex_lock(&mutex[train2]);{
            times[train2].tv_sec = value / SECOND;
            times[train2].tv_nsec = (valor % SECOND) * 1000000L;
            cout << "Sleeping time of train 2: " << times[train2].tv_sec << 
                ":" times[train2].tv_nsec << "\n";
        }
        pthread_mutex_unlock(&mutex[train2]);
        
        /* Getting analog input for the train 3 */
        
        value = MIN_TIME + MAX_TIME * analog_input[train3].getPercentValue() / 100.0;

        pthread_mutex_lock(&mutex[train3]);{
            times[train3].tv_sec = value / SECOND;
            times[train3].tv_nsec = (valor % SECOND) * 1000000L;
            cout << "Sleeping time of train 3: " << times[train3].tv_sec << 
                ":" times[train3].tv_nsec << "\n";
        }
        pthread_mutex_unlock(&mutex[train3]);

        /* Getting analog input for the train 4 */
        
        value = MIN_TIME + MAX_TIME * analog_input[train3].getPercentValue() / 100.0;

        pthread_mutex_lock(&mutex[train4]);{
            times[train4].tv_sec = value / SECOND;
            times[train4].tv_nsec = (valor % SECOND) * 1000000L;
            cout << "Sleeping time of train 4: " << times[train4].tv_sec << 
                ":" times[train4].tv_nsec << "\n";
        }
        pthread_mutex_unlock(&mutex[train4]);

        sleep(1);

    }
    
    return 0;
}
