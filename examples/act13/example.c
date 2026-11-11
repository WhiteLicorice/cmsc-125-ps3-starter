#include <pthread.h>
#include <stdio.h>
static int full, value, consumed; static pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER; static pthread_cond_t cv=PTHREAD_COND_INITIALIZER;
static void *producer(void *p){(void)p; pthread_mutex_lock(&m); value=42; full=1; pthread_cond_signal(&cv); pthread_mutex_unlock(&m); return NULL;}
static void *consumer(void *p){(void)p; pthread_mutex_lock(&m); while(!full) pthread_cond_wait(&cv,&m); consumed=value; full=0; pthread_mutex_unlock(&m); return NULL;}
int main(void){pthread_t p,c; pthread_create(&c,NULL,consumer,NULL); pthread_create(&p,NULL,producer,NULL); pthread_join(p,NULL); pthread_join(c,NULL); printf("consumed=%d full=%d\n",consumed,full); return consumed==42&&!full?0:1;}
