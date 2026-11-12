#include <pthread.h>
#include <stdio.h>
#define LOOPS 10000
static int count; static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
static void *worker(void *unused) { (void)unused; for(int i=0;i<LOOPS;i++){ pthread_mutex_lock(&lock); count++; pthread_mutex_unlock(&lock); } return NULL; }
int main(void){ pthread_t a,b; pthread_create(&a,NULL,worker,NULL); pthread_create(&b,NULL,worker,NULL); pthread_join(a,NULL); pthread_join(b,NULL); printf("count=%d expected=%d\n",count,2*LOOPS); return count==2*LOOPS?0:1; }
