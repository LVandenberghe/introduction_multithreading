/*
** EPITECH PROJECT, 2024
** B-CCP-400-REN-4-1-panoramix-ludwig.vandenberghe
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <semaphore.h>

    #define ASK_BREW "Villager %d: Hey Pano wake up! We need more potion.\n"
    #define DRINK "Villager %d: I need a drink... I see %d servings left.\n"
    #define FIGHT "Villager %d: Take that roman scum! Only %d left.\n"


typedef struct village {
    int nb_villagers;
    int id;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int serving_left;
    bool request_sent;
    sem_t *pot_access;
    sem_t *druid;
    pthread_mutex_t *pot_mutex;
    pthread_mutex_t *refill_mutex;
} village_t;

village_t *set_village(char **av);
void *villager_thread(void *arg);
void *druid_thread(void *arg);


#endif /* !PANORAMIX_H_ */
