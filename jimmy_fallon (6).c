#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

//global variables
pthread_t next_id = 0;
static sem_t connected_lock;  
static sem_t operators;

//thread function
void* phonecall(void* vargp) 
{
  static int NUM_OPERATORS = 3;
  static int NUM_LINES = 5;
  static int connected = 0;   // Callers that are connected
  
  //id: variable to store the id of the thread
  pthread_t id = ++next_id;
  
  printf("Thread %lu is attempting to connect\n", id);
  sleep(1); //thread waiting
  
  //the loop breaks when (connected != NUM_LINES)
  while(1)
  {
    //lock the line for the thread
    sem_wait(&connected_lock);
    if (connected == NUM_LINES) //line busy
    {
      //If the line is busy, print a message, and try again
      printf("Thread %lu is calling line, busy signal\n", id);
      sleep(1);  //thread waiting
      //Since the line is busy, unlock the line that 
      //was being used by a thread to make space
      //for another thread
      sem_post(&connected_lock);
    }
    else //line not busy
    {
      //If the line is not busy, update connected, 
      //print a message, and continue to the next step.
      connected++;
      printf("Thread %lu has available line, call ringing\n", id);
      break; //line is available / (connected != NUM_LINES)
    }
  }

  //unlocking the line that was being used by a 
  //thread after the loop breaks
  sem_post(&connected_lock);

  //operator availability
  sem_wait(&operators);
  printf("Thread %lu is speaking to operator\n", id);
  sleep(3);
  printf("Thread %lu has bought a ticket!\n", id);
  //Proceed with ticket ordering process
  sem_post(&operators);
  connected--;
  printf("Thread %lu has hung up\n", id);
}

int main(int argc, char *argv[]) 
{
  int phoneCalls = atoi(argv[1]);
  //threads: array to store number of 'phoneCalls'
  pthread_t threads[phoneCalls];

  sem_init(&connected_lock, 0, 1);
  sem_init(&operators, 0, 3);
  
  int n = 0; //counter
  while (n < phoneCalls)
  {
    pthread_create(&threads[n], NULL, phonecall, NULL);
    n++;
  }

  //resetting n
  n = 0;
  while (n < phoneCalls)
  {
    pthread_join(threads[n], NULL);
    n++;
  }

  sem_destroy(&connected_lock);
  sem_destroy(&operators);
  
  return 0;
}