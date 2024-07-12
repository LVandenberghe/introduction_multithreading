/*
** EPITECH PROJECT, 2024
** B-CCP-400-REN-4-1-panoramix-ludwig.vandenberghe [WSL: Ubuntu]
** File description:
** villager_behavior
*/

#include "../includes/panoramix.h"

void call_druid(village_t *args, int id)
{
    if (!args->request_sent) {
        printf(ASK_BREW, id);
        args->request_sent = true;
    }
    sem_post(args->druid);
    return;
}

void *villager_thread(void *arg)
{
    village_t *args = (village_t *)arg;
    int id = args->id - 1;
    int fight = args->nb_fights;

    printf("Villager %d: Going into battle!\n", id);
    while (fight > 0) {
        sem_wait(args->pot_access);
        if (args->serving_left > 0) {
            // pthread_mutex_lock(args->pot_mutex);
            printf(DRINK, id, (args->serving_left--));
            printf(FIGHT, id, --fight);
            // pthread_mutex_unlock(args->pot_mutex);
            sem_post(args->pot_access);
            args->request_sent = false;
        } else {
            call_druid(args, id);
        }
    }
    printf("Villager %d: I'm going to sleep now.\n", id);
    pthread_exit(NULL);
}

void *druid_thread(void *arg)
{
    village_t *village = (village_t *)arg;

    printf("Druid: I'm ready... but sleepy...\n");
    while (village->nb_refills) {
        sem_wait(village->druid);
        pthread_mutex_lock(village->pot_mutex);
        if (village->serving_left == 0) {
            printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I "
                "can only make %d more refills after this one.\n",
                village->nb_refills);
            village->serving_left = village->pot_size;
            village->nb_refills--;
            village->request_sent = false;
        }
        pthread_mutex_unlock(village->pot_mutex);
        sem_post(village->pot_access);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    pthread_exit(NULL);
}
