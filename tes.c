#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg) {
    pthread_t tid = *((pthread_t*)arg); // Typecast arg to pthread_t pointer and dereference it
    printf("Thread ID: %lu\n", tid); // Assuming pthread_t is unsigned long
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, (void*)&thread); // Pass thread ID as argument
    pthread_join(thread, NULL);
    return 0;
}
