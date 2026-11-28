#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

static sem_t *done;
static char semaphore_name[32];

/* Post the semaphore once, then leave. */
static void *child(void *p)
{
    (void)p;
    puts("child: post");
    sem_post(done);
    return NULL;
}

int main(void)
{
    pthread_t t;

    snprintf(semaphore_name, sizeof semaphore_name, "/cmsc125-%ld",
             (long)getpid());

    /* Remove a stale name, then create the semaphore with count zero. */
    sem_unlink(semaphore_name);
    done = sem_open(semaphore_name, O_CREAT | O_EXCL, 0600, 0);
    if (done == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    puts("parent: wait");
    if (pthread_create(&t, NULL, child, NULL) != 0) {
        perror("pthread_create");
        sem_close(done);
        sem_unlink(semaphore_name);
        return 1;
    }

    /* The wait returns when the child posts. A failed wait still releases
     * the thread and the name. */
    if (sem_wait(done) != 0) {
        perror("sem_wait");
        pthread_join(t, NULL);
        sem_close(done);
        sem_unlink(semaphore_name);
        return 1;
    }

    puts("parent: continue");
    pthread_join(t, NULL);
    sem_close(done);
    sem_unlink(semaphore_name);
    return 0;
}
