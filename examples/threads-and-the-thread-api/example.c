#include <pthread.h>
#include <stdio.h>

static int shared; static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
static void *worker(void *arg) {
    int private_value = *(int *)arg;
    pthread_mutex_lock(&lock); shared += private_value; pthread_mutex_unlock(&lock);
    return arg;
}
int main(void) {
    pthread_t a, b; int x=1, y=2; void *ra, *rb;
    pthread_create(&a, NULL, worker, &x); pthread_create(&b, NULL, worker, &y);
    pthread_join(a, &ra); pthread_join(b, &rb);
    printf("shared=%d private=%d,%d joined=%s\n", shared, x, y, ra==&x && rb==&y ? "yes" : "no");
    return 0;
}
