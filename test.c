#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BIG 200000
typedef struct test
{
     pthread_mutex_t a_lock;
     int a;
}test;

void *change_a(void *arg)
{
 test *data = (test *)arg;

 int i = 0; 
 //printf ("a = %d\n",data->a);
// pthread_mutex_lock(&data->a_lock);
 while (i < BIG)
 { 
        data->a++;
        i++; 
} 
 pthread_mutex_unlock(&data->a_lock);
 return (NULL);
}

int main()
{
 pthread_t thread_1;
 pthread_t thread_2;
  pthread_t thread_3;
 
 test data;
 data.a = 0;
 pthread_mutex_init(&data.a_lock, NULL);
 pthread_create(&thread_1, NULL, change_a, &data);
 pthread_create(&thread_2, NULL, change_a, &data);
 pthread_create(&thread_3, NULL, change_a, &data);
 pthread_join(thread_1, NULL);
 pthread_join(thread_2, NULL);
 pthread_join(thread_3, NULL);
 printf("a is: %u\n", data.a);
}