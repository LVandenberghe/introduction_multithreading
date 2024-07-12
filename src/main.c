/*
** EPITECH PROJECT, 2024
** B-CCP-400-REN-4-1-panoramix-ludwig.vandenberghe [WSL: Ubuntu]
** File description:
** locate
*/

#include "../includes/panoramix.h"

static void show_usage(void)
{
    printf("nb_villagers: indicates the number of villagers (must be >0)\n");
    printf("pot_size: indicates the maximum number that can be contained in ");
    printf("the cooking pot (must be >0);\n");
    printf("nb_fights: indicates the maximum number of fights a villager ");
    printf("will engage in (must be >0)\n");
    printf("nb_refills: incicates the maximum number of time the druid will ");
    printf("refill the pot (must be >0)\n");
}

static bool warn_wrong_imput(char **av)
{
    if (av[1] == 0) {
        printf("Values must be >0.\n");
        return true;
    }
    if (av[2] == 0) {
        printf("Values must be >0.\n");
        return true;
    }
    if (av[3] == 0) {
        printf("Values must be >0.\n");
        return true;
    }
    if (av[4] == 0) {
        printf("Values must be >0.\n");
        return true;
    }
    return false;
}

static bool check_input(char **av)
{
    char *endptr;
    long value;

    for (int i = 1; i <= 4; ++i) {
        value = strtol(av[i], &endptr, 10);
        if (*endptr != '\0' || value <= 0) {
            printf("Invalid input: %s must be a number and superior to 0.\n",
            av[i]);
            return true;
        }
    }
    return false;
}

static bool is_winnable(char **av)
{
    int nb_villagers = atoi(av[1]);
    int pot_size = atoi(av[2]);
    int nb_fights = atoi(av[3]);
    int nb_refills = atoi(av[4]);

    if (nb_villagers * nb_fights > pot_size * (nb_refills + 1))
        return true;
    return false;
}

static bool check_error(char **av)
{
    if (warn_wrong_imput(av))
        return true;
    if (check_input(av))
        return true;
    if (is_winnable(av)) {
        perror("there is too much roman or not enough potion to win this"
            " fight");
        return true;
    }
    return false;
}

void init_village(village_t *village)
{
    pthread_t druid_tid;
    pthread_t villagers_tid[village->nb_villagers];

    village->serving_left = village->pot_size;
    if (pthread_create(&druid_tid, NULL, druid_thread, (void *)village) != 0)
        return;
    for (; village->id < village->nb_villagers; village->id++) {
        if (pthread_create(&villagers_tid[village->id], NULL, villager_thread,
            (void *)village) != 0) {
            pthread_cancel(druid_tid);
            return;
        }
    }
    for (int i = 0; i < village->nb_villagers; i++)
        pthread_join(villagers_tid[i], NULL);
    pthread_cancel(druid_tid);
}

int main(int ac, char **av)
{
    village_t *village;

    if (ac != 5 && (strcmp(av[1], "-h") == 0)) {
        show_usage();
        return 0;
    }
    if (check_error(av))
        return 84;
    village = set_village(av);
    if (village == NULL) {
        perror("Failed to allocate memory for village");
        return 84;
    }
    init_village(village);
    return 0;
}
