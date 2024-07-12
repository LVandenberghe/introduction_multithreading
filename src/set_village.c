/*
** EPITECH PROJECT, 2024
** B-CCP-400-REN-4-1-panoramix-ludwig.vandenberghe [WSL: Ubuntu]
** File description:
** set_village
*/

#include "../includes/panoramix.h"

village_t *set_threads(village_t *village)
{
    village->pot_mutex = malloc(sizeof(pthread_mutex_t));
    if (pthread_mutex_init((village->pot_mutex), NULL) != 0)
        return NULL;
    village->refill_mutex = malloc(sizeof(pthread_mutex_t));
    if (pthread_mutex_init((village->refill_mutex), NULL) != 0)
        return NULL;
    village->pot_access = malloc(sizeof(sem_t));
    if (sem_init(village->pot_access, 0, 1) != 0)
        return NULL;
    village->druid = malloc(sizeof(sem_t));
    if (sem_init(village->druid, 0, 1) != 0)
        return NULL;
    return village;
}

village_t *set_village(char **av)
{
    village_t *village = malloc(sizeof(village_t));

    if (village == NULL)
        return NULL;
    village->nb_villagers = atoi(av[1]);
    village->pot_size = atoi(av[2]);
    village->nb_fights = atoi(av[3]);
    village->nb_refills = atoi(av[4]);
    village->id = 0;
    village->serving_left = village->pot_size;
    return set_threads(village);
}
