#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define YELLOW "\x1b[33m"

#define MAX 10

typedef struct
{
    char username[10];
    char password[10];
    int max_level;

} user_info;

char title_screen();
void invalid(char choice);
int existing_account(FILE *player_data);
void create_account(FILE *player_data);
void delay(int);
void delay_n(int number_of_seconds);

int ran_num_gen();

// displays------------------------------------------------------------
void health_bar(int ph, int eh, int pa, int ea, int domain, char playername[]);
void enemyslime(int state);
void player(int p_state);
void transitionscreen(int mode);
void enter();
void continue_round_display(int round);
void gameover_display(int round);
void display(int transition, int mode);
void genshintext();

//
int game(char playername[], int current_highscore);

int main()
{
    char choice;

    user_info temp;

    FILE *player_data;
    FILE *numofaccs;
    FILE *checker;

    choice = title_screen();

    if (choice == 'y')
    {
        create_account(player_data);
        delay(1);
        system("cls");
        printf("\n\n\t\tAccount created!\n\n");
        delay(1);
        existing_account(player_data);
    }
    else if (choice == 'n')
    {
        existing_account(player_data);
    }
    else
        invalid(choice);

    return 0;
}
char title_screen()
{
    char choice;
    genshintext();
    printf("\n");
    printf("\t\t              are you a new player?\n");
    printf("\t\t\t              y / n \n\n");
    scanf("%c", &choice);
    return choice;
}
int existing_account(FILE *player_data)
{
    int highscore;

    char temp_username[10], temp_password[10];
    user_info acc[10];
    system("cls");
    printf("\n\n\t\tLogin to existing account..\n");
    player_data = (fopen("player_data.txt", "r+"));
    for (int x = 0; x < MAX; ++x)
    {
        fscanf(player_data, "%s", acc[x].username);
        fscanf(player_data, "%s", acc[x].password);
        fscanf(player_data, "%d", &(acc[x].max_level));
    }

    printf("\n\tUsername: ");
    scanf("%s", temp_username);
    printf("\tPassword: ");
    scanf("%s", temp_password);

    for (int x = 0; x < MAX; ++x)
    {
        if (strcmp(acc[x].username, temp_username) == 0)
        {
            if (strcmp(acc[x].password, temp_password) == 0)
            {
                system("cls");
                printf("\n\n\t\tLogin Successful!\n\n");
                delay(1);
                fclose(player_data);

                for (int grand_looper = 0; grand_looper < 2; grand_looper++)
                {
                    highscore = game(acc[x].username, acc[x].max_level); // entire game
                    if (highscore == 0)
                    {
                        system("cls");
                        printf("\n                               Thanks for playing!  ");
                        printf("\n                           Made by Clyde, Jamil & Ara  ");
                        return 0;
                    }
                    else
                    {
                        // WRITE HERE SAVING system use      highscore variable
                    }
                    if (grand_looper == 1)
                    {
                        grand_looper = 0;
                    }
                }
            }
        }
        system("cls");
        printf("\n\n\t\tAccount does not exist!\n\n");
        fclose(player_data);
    }
}
void create_account(FILE *player_data)
{
    char temp_username[10], temp_password[10];
    user_info acc[10];
    system("cls");
    printf("\n\t\tCreating account..\n");
    printf("\n\tEnter username: ");
    scanf("%s", temp_username);
    printf("\tEnter password: ");
    scanf("%s", temp_password);
    player_data = (fopen("player_data.txt", "a+"));
    fprintf(player_data, "%s\n", temp_username);
    fprintf(player_data, "%s\n", temp_password);
    fprintf(player_data, "0\n");
    fclose(player_data);
}
void invalid(char choice)
{
    while (choice != 'y' || choice != 'n')
    {
        system("cls");
        printf("\n\n\t\tInvalid choice!\n\n");
        exit(0);
    }
}
void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

//▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
int game(char playername[], int current_highscore)
{
    int last_round = 0;
    char confirm;
    system("cls");
    genshintext();
    printf("\n                                Welcome Traveler,  ");
    puts(playername);
    printf("\n                                  High Score: %d   ", current_highscore);

    printf("\n                                  ---------------                                \n"
           "                                 |  START GAME ? |                               \n"
           "                                  ---------------                                \n"
           "                                  type y to start\n");
    printf("                                  ---------------                                \n"
           "                                 |   EXIT GAME ? |                               \n"
           "                                  ---------------                                \n"
           "                                  type x to exit\n");

    scanf("\n%c", &confirm);

    if (confirm == 'y')
    {

        while (confirm == 'y')
        {

            char next;

            int p_inc = 0;
            int round = 1;
            int incrementor = 0;
            int neutral = 0;
            int display_mode = 0;
            int flag = 0;

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
                if (round % 2 != 0)
                {
                    en_attack += incrementor;
                }

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

                        printf("                                           Player's turn                      \n\n");
                        printf("                                    what would you like to do                  \n\n"
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
                                    display(2, 8);
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
                            delay_n(8);
                            int blocking_state = 1;
                        }
                        if (decision == 3)
                        {
                            system("cls");
                            turn = 2;
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

                            display(5, 6);
                            enb_state = 1;
                            scanf("%c", &next);
                        }

                        blocking_state = 0;
                        turn = -1;
                    }

                    if (health <= 0)
                    {
                        turn = 1;
                        delay_n(8);
                    }
                    else if (en_health <= 0)
                    {
                        turn = 1;
                        delay_n(8);
                    }
                    else if (turn != 2)
                    {
                        system("cls");
                        health_bar(health, en_health, attack, en_attack, round, playername);
                        display(neutral, 0);
                    }

                    turn += 1;
                }

                int round_exit;

                if (health <= 0)
                {
                    last_round += round;
                    flag = 1;
                    round = 0;
                }
                else if (turn == 2)
                {
                    incrementor += 1;
                    system("cls");
                    printf("================================================================================================\n");
                    printf("|| You have cleared the domain! pick a reward                                                 ||\n"
                           "||                     _____________                    _____________                         ||\n"
                           "||                    |1  +1 HEALTH |                  |2  +1 ATTACK |                        ||\n"
                           "||                     -------------                    --------------                        ||\n");
                    printf("================================================================================================\n");
                    scanf("%d", &p_inc);
                    system("cls");
                    continue_round_display(round);
                    scanf("%d", &round_exit);
                    if (round_exit == 1)
                    {
                        round += 1;
                    }
                    else
                    {
                        last_round += round;
                        flag = 3;
                        round = 0;
                    }
                }
                else
                {
                    last_round += round;
                    flag = 2;
                    round = 0;
                }
            }

            int exiter = 0;

            if (flag == 1)
            {
                system("cls");
                gameover_display(last_round);
                scanf("%d", &exiter);
                if (exiter == 0)

                {
                    return last_round;
                }
            }
            if (flag == 2 || flag == 3)
            {
                return last_round;
            }
        }
    }
    else
    {
        return 0;
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
void health_bar(int ph, int eh, int pa, int ea, int domain, char playername[])
{
    printf("[ DOMAIN :: %d ] \n\n", domain);
    printf("================================================================================================\n");
    printf("%s HP : [ %d ] ", playername, ph);
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
void genshintext()
{
    printf(YELLOW "       _____                _     _         _                           _   \n"
                  "      /_  __|              | |   (_)       (_)                         | |  \n"
                  "        | |   __ _____  ___| |__  _ _ __    _ _ __ ___  _ __   __ _  __| |_ \n"
                  "        | |  / _ | '_ |/ __| '_  | | '_  | | | '_ ` _  | '_  / _` |/ __| __|\n"
                  "     | || | |  __/ | | |__ | | | | | | | | | | | | | | | |_) | (_|| (__| |_ \n"
                  "     |___ / | ___|_| |_|___/_| |_|_|_| |_| |_|_| |_| |_| .__/|__,_||___|__|\n"
                  "                             but its made in terminal\n" RESET);
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
void continue_round_display(int round)
{
    printf("================================================================================================\n");
    printf("||                                                                                            ||\n"
           "||                         R O U N D  %d    C L E A R E D   ! !                               ||\n"
           "||                                                                                            ||\n",
           round);
    printf("================================================================================================\n");
    delay_n(4);
    printf("What would you like to do?                                                                      \n"
           "1  Continue                                                                        2   Exit Game\n");
}
void gameover_display(int round)
{
    printf("================================================================================================\n");
    printf("||                                G A M E      O V E R                                         ||\n"
           "||                                    Rounds survived=  %d                                      ||\n",
           round + 1);
    printf("================================================================================================\n");
    printf("\n                                      Play again ?\n"
           "                          ___________                 ___________            \n"
           "                         |  RESTART  |               |    EXIT   |           \n"
           "                         |_____0_____|               |_____1_____|           \n");
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
    char en_dodge_attack[] = "Enemy dodged the attack";

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
    case 8:
        strcat(screen_text, en_dodge_attack);
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
    if (transition == 5)
    {

        enemyslime(0);
        player(0);
        transitionscreen(mode);
        enter();
    }
}
