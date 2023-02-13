#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define YELLOW "\x1b[33m"

int ran_num_gen();
void delay_n(int number_of_seconds);
// displays------------------------------------------------------------
void health_bar(int ph, int eh, int pa, int ea, int domain, char name[]);
void enemyslime(int state);
void player(int p_state);
void transitionscreen(int mode);
void enter();
void display(int transition, int mode);

int game()
{

    char playername[20], confirmation;

    system("cls");

    printf(" ---------------\n"
           "|  START GAME   |\n"
           " ---------------\n");
    printf(" type y to start \n");

    scanf("%c", &confirmation);

    // Higher variables ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
    while (confirmation == 'y')
    {

        char next;

        int p_inc = 0;
        int round = 1;
        int incrementor = 0;
        int neutral = 0;
        int display_mode = 0;

        // Round ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

        while (round > 0)
        {

            int health = 5, attack = 1, en_health = 3, en_attack = 1;
            int turn = 0;

            if (p_inc == 1)
            {
                health += 1;
            }
            else if (p_inc == 2)
            {
                attack += 1;
            }
            en_health += incrementor;
            en_attack += incrementor;

            system("cls");
            health_bar(health, en_health, attack, en_attack, round, playername);
            display(neutral, display_mode);

            int blocking_state = 0;
            int enb_state = 0;

            // Player - Enemy Turn switching ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

            while (turn < 2)
            {
                int decision, en_decision;

                if (turn == 0) // PLAYER TURN
                {

                    printf("Players turn \n\n");
                    printf("what would you like to do\n\n"
                           "                ___________                 ___________              ___________       \n"
                           "               |  ATTACK   |               |   DODGE   |            |  Q U I T  |      \n"
                           "               |_____1_____|               |_____2_____|            |_____3_____|       \n");

                    scanf("%d", &decision);

                    if (decision == 1)
                    {
                        system("cls");

                        health_bar(health, en_health, attack, en_attack, round, playername);
                        display(1, 1);
                        scanf("%c", &next);
                        if (ran_num_gen() == 0)
                        {
                            if (enb_state == 1)

                            {
                                printf(" enemy dodged");
                                scanf("%c", &next);
                            }
                            else
                            {
                                display(2, 2);
                                en_health -= attack;
                                delay_n(4);
                                scanf("%c", &next);

                                system("cls");
                                health_bar(health, en_health, attack, en_attack, round, playername);
                                display(3, 0);

                                delay_n(8);
                            }
                        }
                        else
                        {
                            display(2, 3);

                            scanf("%c", &next);
                        }
                    }
                    if (decision == 2)
                    {
                        system("cls");
                        health_bar(health, en_health, attack, en_attack, round, playername);
                        display(1, 4);
                        int blocking_state = 1;
                        scanf("%c", &next);
                    }
                    if (decision == 3)
                    {
                        system("cls");
                        turn = 3;
                    }
                    enb_state = 0;
                }

                if (turn == 1) // ENEMY TURN
                {

                    printf(" Enemy turn                                                             Press Enter => \n\n");
                    scanf("%c", &next);

                    en_decision = ran_num_gen();

                    if (en_decision == 0)
                    {
                        system("cls");
                        health_bar(health, en_health, attack, en_attack, round, playername);
                        display(1, 5);

                        if (ran_num_gen() == 0)
                        {
                            if (blocking_state == 1)
                            {
                                display(2, 7);
                                scanf("%c", &next);
                            }
                            else
                            {
                                display(2, 2);
                                health -= en_attack;
                                scanf("%c", &next);

                                system("cls");
                                health_bar(health, en_health, attack, en_attack, round, playername);
                                display(4, 0);
                                delay_n(8);
                            }
                        }
                        else
                        {
                            display(2, 3);
                            scanf("%c", &next);
                        }
                    }
                    else
                    {
                        system("cls");
                        health_bar(health, en_health, attack, en_attack, round, playername);
                        display(1, 6);
                        enb_state = 1;
                        scanf("%c", &next);
                    }

                    blocking_state = 0;
                    turn = -1;
                }
                // UI
                system("cls");
                health_bar(health, en_health, attack, en_attack, round, playername);
                display(neutral, 0);

                /*-------------------------*/

                if (health <= 0)
                {
                    printf("player defeated");
                    turn = 1;
                    scanf("%c", &next);
                    // insert defeat sequence here
                }
                else if (en_health <= 0)
                {
                    printf("enemy defeated");
                    turn = 1;
                    scanf("%c", &next);
                    // insert defeat sequence here
                }

                turn += 1;
            }
            // ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
            incrementor += 1;

            /*------------------------------------------*/
            int round_exit;

            if (health <= 0)
            {
                round = 0;
            }
            else if (turn == 2)
            {

                system("cls");
                printf("================================================================================================\n");
                printf("|| You have cleared the domain! pick a reward                                                 ||\n"
                       "||                     _____________                    _____________                         ||\n"
                       "||                    |1  +1 HEALTH |                  |2  +1 ATTACK |                        ||\n"
                       "||                     -------------                    --------------                        ||\n");
                printf("================================================================================================\n");
                scanf("%d", &p_inc);

                system("cls");
                printf("================================================================================================\n");
                printf("||                                                                                            ||\n"
                       "||                         R O U N D  %d    C L E A R E D   ! !                               ||\n"
                       "||                                                                                            ||\n",
                       round);
                printf("================================================================================================\n");
                delay_n(4);
                printf("What would you like to do?                                                                      \n"
                       "1  Continue                                                                        2   Exit Game\n");
                scanf("%d", &round_exit);
            }

            if (round_exit == 1)
            {
                round += 1;
            }
            else
            {
                round = 0;
            }
        }

        // EXIT SEQUENCE ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
        int exiter = 0;
        system("cls");
        printf(" Game over, play again\n  press 0 to restart , 1 to exit");
        scanf("%d", &exiter);
        if (exiter == 1)
        {
            confirmation = 'n';
        }
    }
}

int ran_num_gen()
{
    int number;
    srand(time(NULL));
    number = rand() % 10;
    if (number % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void health_bar(int ph, int eh, int pa, int ea, int domain, char name[])
{
    printf("[ DOMAIN :: %d ] \n\n", domain);
    printf("================================================================================================\n");
    printf("%s HP : [ %d ] ", name, ph);
    for (int i = 1; i <= ph; i++)
    {
        printf(GREEN "O");
    }
    printf(RESET "  ATTACK : [%i] ", pa);
    printf("            Slime HP: [ %d ] ", eh);
    for (int j = 1; j <= eh; j++)
    {
        printf(RED "O");
    }
    printf(RESET "  ATTACK : [ %d ]  \n", ea);
    printf("================================================================================================\n");
}

void enemyslime(int state)
{
    if (state == 1)
    {
        printf("||                                                            " RED "______" RESET "                          ||\n"
               "||                                                          " RED "/ ^   ^  }" RESET "                        ||\n"
               "||                                           " YELLOW "< H I T!! >" RED "    | >    < |" RESET "                        ||\n"
               "||                                                          " RED "{________}" RESET "                        ||\n");
    }
    else
    {
        printf("||                                                            " RED "______" RESET "                          ||\n"
               "||                                                          " RED "/ ^   ^  }" RESET "                        ||\n"
               "||                                                          " RED "| 0    0 |" RESET "                        ||\n"
               "||                                                          " RED "{________}" RESET "                        ||\n");
    }
}

void player(int p_state)
{

    if (p_state == 1)

    {
        printf("||           _____                          VS                                                ||\n"
               "||          /      }                                                                          ||\n"
               "||          |  >_< |     " YELLOW "< H I T!!" RESET "                                                            ||\n"
               "||          {______/                                                                          ||\n");
        printf("================================================================================================\n");
    }
    else
    {
        printf("||           _____                          VS                                                ||\n"
               "||          /      }                                                                          ||\n"
               "||          |  O_O |                                                                          ||\n"
               "||          {______/                                                                          ||\n");
        printf("================================================================================================\n");
    }
}
void delay_n(int number_of_seconds)
{
    int milli_seconds = 100 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}
void enter()
{
    printf("                                                                                 Press Enter => \n\n");
}
void transitionscreen(int mode)
{
    char screen_text[50] = "\0";
    char player_attack[] = "Player used an attack";
    char attack_landed[] = "Attack landed";
    char attack_missed[] = "Attack Missed";
    char player_dodge[] = "Player used Dodge";
    char enemy_attack[] = "Enemy used an attack";
    char enemy_dodge[] = "Enemy used Dodge";
    char dodge_attack[] = "You dodged the attack ";

    switch (mode)
    {
    case 1:

        strcat(screen_text, player_attack);
        break;

    case 2:
        strcat(screen_text, attack_landed);
        break;
    case 3:
        strcat(screen_text, attack_missed);
        break;
    case 4:
        strcat(screen_text, player_dodge);
        break;
    case 5:
        strcat(screen_text, enemy_attack);
        break;
    case 6:
        strcat(screen_text, enemy_dodge);
        break;
    case 7:
        strcat(screen_text, dodge_attack);
        break;
    default:
        break;
    }

    printf("                                  ");

    for (int i = 0; i < strlen(screen_text); i++)
    {
        printf("%c", screen_text[i]);
        delay_n(1);
    }

    printf("\n");
    delay_n(4);
}

void display(int transition, int mode)
{
    if (transition == 0)
    {
        enemyslime(0);
        player(0);
    }
    if (transition == 1)
    {

        enemyslime(0);
        player(0);
        transitionscreen(mode);
    }
    if (transition == 2) // transition below
    {
        transitionscreen(mode);
        enter();
    }
    if (transition == 3) // slime hurt
    {
        enemyslime(1);
        player(0);
    }
    if (transition == 4) // player hurt
    {
        enemyslime(0);
        player(1);
    }
}
