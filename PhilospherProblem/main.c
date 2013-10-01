//
//  main.c
//  PhilospherProblem
//
//  Created by Omar Gudino on 9/30/13.
//  Copyright (c) 2013 Omar Gudino. All rights reserved.
//

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

typedef struct Philosopher{
    int thinkingCount;
    int eatingCount;
    int index;
    int leftChopstick;
    int rihtChopstick;
}philosopher;

sem_t mutex = 1;
int chopSticks = 5;

void philosopherActive(struct Philosopher *philosopher)
{
    philosopher->eatingCount = 0;
    philosopher->thinkingCount = 0;
    philosopher->leftChopstick = 0;
    philosopher->rihtChopstick = 0;
    while (1) {
        sleep(1);
        philosopher->thinkingCount++;
        printf("El filosofo %d esta pensando\n", philosopher->index);
        waitChopststicks(1);
        waitChopststicks(1);
        philosopher->leftChopstick++;
        philosopher->rihtChopstick++;
        waitSignal(1);
        if (philosopher->leftChopstick == 1 && philosopher->rihtChopstick == 1) {
            philosopher->eatingCount++;
            printf("El filosofo %d esta comiendo\n", philosopher->index);
        }
        printf("El filosofo %d tiene una cuenta de %d comidas\n", philosopher->index, philosopher->eatingCount);
        post(1);
        philosopher->rihtChopstick--;
        philosopher->leftChopstick--;
        postChopsticks(1);
        postChopsticks(1);
        
        
    }
}

int main(int argc, const char * argv[])
{
    struct Philosopher philosopher1, philosopher2, philosopher3, philosopher4, philosopher5;
    pthread_t philosopherT1, philosopherT2, philosopherT3, philosopherT4, philosopherT5;
    
    philosopher1.index = 1;
    philosopher2.index = 2;
    philosopher3.index = 3;
    philosopher4.index = 4;
    philosopher5.index = 5;
    
    pthread_create(&philosopherT1, NULL, philosopherActive, &philosopher1);
    pthread_create(&philosopherT2, NULL, philosopherActive, &philosopher2);
    pthread_create(&philosopherT3, NULL, philosopherActive, &philosopher3);
    pthread_create(&philosopherT4, NULL, philosopherActive, &philosopher4);
    pthread_create(&philosopherT5, NULL, philosopherActive, &philosopher5);
    
    pthread_join(philosopherT1, NULL);
    pthread_join(philosopherT2, NULL);
    pthread_join(philosopherT3, NULL);
    pthread_join(philosopherT4, NULL);
    pthread_join(philosopherT5, NULL);
    
    return 0;
}

sem_t post(int value)
{
    mutex = mutex + value;
    return mutex;
}

sem_t waitSignal(int value)
{
    while (1) {
        if (mutex > 0) {
            mutex = mutex - value;
            break;
        }
    }
    return mutex;
}

sem_t postChopsticks(int value)
{
    chopSticks = chopSticks + value;
    return chopSticks;
}

sem_t waitChopststicks(int value)
{
    while (1) {
        if (chopSticks > 0) {
            chopSticks = chopSticks - value;
            break;
        }
    }
    return chopSticks;
}
