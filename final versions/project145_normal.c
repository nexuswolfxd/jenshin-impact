#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

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

int existing_account(FILE *player_data);
int create_account(FILE *player_data);
int dupe_check(FILE *player_data, char temp_username[]);
void score_update(FILE *player_data, int highscore, char temp_username[], char temp_password[], int line);
void delay(int);
void delay_n(int number_of_seconds);

int ran_num_gen();

// displays------------------------------------------------------------
void health_bar(int ph, int eh, int pa, int ea, int domain, char playername[], int enemy);
void enemyslime(int state);
void enemy_hilichurl(int state);
void enemy_abyssmage(int state);
void player(int p_state);
void transitionscreen(int mode);
void enemy_display(int enemy, int state);
void continue_round_display(int round);
void gameover_display(int round);
void display(int transition, int mode, int enemy);
void genshintext();
void gamemenu_buttons();
void domain_clear_reward();
void player_decisions_ui();
void thanks();

//
int game(char playername[], int current_highscore);

int main()
{
    int state = 0;
    char choice;

    user_info temp;

    FILE *player_data;

    do
    {
        choice = title_screen();
        if (choice == 'y')
        {
            state = create_account(player_data);
        }
        else if (choice == 'n')
        {
            state = existing_account(player_data);
        }
        else if (choice == 'e')
        {
            exit(1);
        }
    } while (state != 1);
}
char title_screen()
{
    char choice;
    genshintext();
    printf("\n");
    printf("\t\t              are you a new player?\n");
    printf("\t\t\t              y / n ");
    printf("\n\t\t\t\t    e to exit\n\n");

    scanf("%c", &choice);
    Beep(1123, 50);
    return choice;
}
int existing_account(FILE *player_data)
{
    int highscore, line = 0, temp_comp;

    char temp_username[10], temp_password[10];
    user_info acc[10];
    system("cls");
    genshintext();
    printf("\n\t\t\t    Login to existing account..\n");
    player_data = (fopen("player_data.txt", "r+"));
    for (int x = 0; x < MAX; ++x)
    {
        fscanf(player_data, "%s", acc[x].username);
        fscanf(player_data, "%s", acc[x].password);
        fscanf(player_data, "%d", &(acc[x].max_level));
    }

    printf("\n\t\tUsername: ");
    scanf("%s", temp_username);
    Beep(1123, 50);
    printf("\t\tPassword: ");
    scanf("%s", temp_password);
    Beep(1123, 50);
    for (int x = 0; x < MAX; ++x)
    {
        line += 3;
        if (strcmp(acc[x].username, temp_username) == 0)
        {
            if (strcmp(acc[x].password, temp_password) == 0)
            {
                system("cls");
                genshintext();
                printf("\n\n\t\t\t\tLogin Successful!\n\n");
                delay(1);

                for (int looper = 0; looper < 2; looper++)
                {
                    highscore = game(acc[x].username, acc[x].max_level); // entire game
                    temp_comp = acc[x].max_level;

                    if (highscore == 0)
                    {

                        fclose(player_data);
                        return 0;
                    }
                    else
                    {
                        if (temp_comp <= highscore)
                        {

                            fclose(player_data);
                            score_update(player_data, highscore, temp_username, temp_password, line);
                        }
                        else
                        {

                            fclose(player_data);
                        }
                    }
                    if (looper == 1)
                    {
                        looper = 0;
                    }
                }
            }
        }
    }
    system("cls");
    printf("\n\n\n\n\t\t\tAccount does not exist!\n\n");
    fclose(player_data);
    delay(1);
    return 0;
}
int create_account(FILE *player_data)
{
    char temp_username[10], temp_password[10];
    int check;
    user_info acc[10];
    system("cls");
    genshintext();
    printf("\n\t\t\t\tCreating account..\n");
    printf("\n\t\tEnter username: ");
    scanf("%s", temp_username);
    Beep(1123, 50);
    printf("\t\tEnter password: ");
    scanf("%s", temp_password);
    Beep(1123, 50);
    check = dupe_check(player_data, temp_username);

    if (check == 1)
    {
        return 0;
    }
    else if (check == 0)
    {
        player_data = fopen("player_data.txt", "a+");
        fprintf(player_data, "%s\n", temp_username);
        fprintf(player_data, "%s\n", temp_password);
        fprintf(player_data, "0\n");
        fclose(player_data);
        delay(1);
        system("cls");
        genshintext();
        printf("\n\n\t\t\t\tAccount created!\n\n");
        delay(1);
        return 0;
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
    gamemenu_buttons();
    scanf("\n%c", &confirm);
    Beep(1123, 50);
    if (confirm == 'y')
    {

        while (confirm == 'y')
        {

            int p_inc = 0;
            int round = 1;
            int p_at_inc = 0, p_health_inc = 0;

            int en_at_inc = 0, en_health_inc = 0;
            int flag = 0;
            int enemy = 0;

            // Round ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

            while (round > 0)
            {

                int health = 5, attack = 1, en_health = 3, en_attack = 1;
                int turn = 0;

                health += p_health_inc;
                attack += p_at_inc;
                en_health += en_health_inc;

                en_attack += en_at_inc;

                system("cls");
                health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                display(0, 0, enemy);

                int blocking_state = 0;
                int enb_state = 0;

                //▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄

                while (turn < 2)
                {
                    int decision = 0, en_decision = 0;

                    if (turn == 0) // PLAYER TURN
                    {
                        player_decisions_ui();
                        scanf("%d", &decision);
                        Beep(3000, 50);
                        if (decision == 1)
                        {
                            system("cls");

                            health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                            display(1, 1, enemy);
                            delay(1);

                            if (ran_num_gen() <= 7)
                            {
                                if (enb_state == 1)
                                {
                                    display(2, 8, enemy);
                                    delay(1);
                                }
                                else
                                {
                                    display(2, 2, enemy);
                                    en_health -= attack;
                                    delay_n(4);
                                    delay(1);

                                    system("cls");
                                    health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                                    display(3, 0, enemy);

                                    delay_n(8);
                                }
                            }
                            else
                            {
                                display(2, 3, enemy);
                                delay(1);
                            }
                        }
                        if (decision == 2)
                        {
                            system("cls");
                            health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                            display(1, 4, enemy);
                            delay_n(8);
                            blocking_state = 1;
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

                        printf("                                       Enemy turn                                                              \n\n");
                        Beep(3000, 50);
                        delay(2);

                        en_decision = ran_num_gen();

                        if (en_decision <= 6)
                        {
                            system("cls");
                            health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                            display(1, 5, enemy);

                            if (ran_num_gen() <= 6)
                            {
                                if (blocking_state == 1)
                                {
                                    display(2, 7, enemy);
                                    delay(1);
                                }
                                else
                                {
                                    display(2, 2, enemy);
                                    health -= en_attack;
                                    delay(1);

                                    system("cls");
                                    health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                                    display(4, 0, enemy);
                                    delay_n(8);
                                }
                            }
                            else
                            {
                                display(2, 3, enemy);
                                delay(1);
                            }
                        }
                        else
                        {
                            system("cls");
                            health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                            display(1, 6, enemy);
                            enb_state = 1;
                            delay(1);
                        }

                        blocking_state = 0;
                        turn = -1;
                    }

                    if (health <= 0 || en_health <= 0)
                    {
                        turn = 1;
                    }
                    else if (turn != 2)
                    {
                        system("cls");
                        health_bar(health, en_health, attack, en_attack, round, playername, enemy);
                        display(0, 0, enemy);
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
                    en_health_inc += 1;
                    if (round % 2 == 0)
                    {
                        en_at_inc += 1;
                    }

                    system("cls");
                    display(5, 0, enemy);
                    domain_clear_reward();
                    scanf("%d", &p_inc);
                    if (p_inc == 1)
                    {
                        p_health_inc += 1;
                    }
                    else
                    {
                        p_at_inc += 1;
                    }

                    system("cls");
                    Beep(1123, 50);
                    continue_round_display(round);
                    scanf("%d", &round_exit);
                    Beep(1123, 50);
                    if (round > 9)
                    {
                        enemy = 2;
                    }
                    else if (round > 4)
                    {
                        enemy = 1;
                    }

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
                Beep(1123, 50);
                delay(3);
                return last_round;
            }
            else if (flag == 2 || flag == 3)
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
void delay_n(int number_of_seconds)
{
    int milli_seconds = 100 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}
int ran_num_gen()
{
    int whole_num;
    float with_deci, final;
    int number;

    srand(time(NULL));
    number = rand() % 100;

    if (number > 9)
    {
        with_deci = number * 0.1;
        whole_num = with_deci;
        final = (with_deci - whole_num) * 10;
        whole_num = final;
        return whole_num;
    }
    else
    {
        return number;
    }
}

void health_bar(int ph, int eh, int pa, int ea, int domain, char playername[], int enemy)
{
    char en_name[10];
    if (enemy == 1)
    {
        strcpy(en_name, "Hilichurl");
    }
    else if (enemy == 2)
    {
        strcpy(en_name, "Abyss Mage");
    }
    else
    {
        strcpy(en_name, "Slime");
    }
    printf("[ DOMAIN :: %d ] \n\n", domain);
    printf("================================================================================================\n");
    printf(YELLOW "%s" RESET " HP : [ %d ] ", playername, ph);
    for (int i = 1; i <= ph; i++)
    {
        printf(GREEN "O");
    }
    printf(RESET "  ATTACK : [%i] ", pa);
    printf(YELLOW "            %s " RESET " HP: [ %d ] ", en_name, eh);
    for (int j = 1; j <= eh; j++)
    {
        printf(RED "O");
    }
    printf(RESET "  ATTACK : [ %d ]  \n", ea);
    printf("================================================================================================\n");
}
void enemy_abyssmage(int state)
{
    if (state == 1)
    {
        printf("||                                                           " RED " /|      /|" RESET "                      ||\n"
               "||                                                          " RED " | |     | | " RESET "                     ||\n"
               "||                                                         " RED "  | |_____| |  " RESET "                    ||\n"
               "||                                             " YELLOW "< H I T ! >   " RED "/ ________ |" RESET "                       ||\n"
               "||                                                         " RED " / /        | |" RESET "                    ||\n"
               "||                                                          " RED "| |  >  <  | |" RESET "                    ||\n"
               "||                                                      " RED "___/  |__  ___ |  |__" RESET "                 ||\n"
               "||                                                    " RED " /         |/         |" RESET "                 ||\n"
               "||                                                   " RED "  /                     |" RESET "                ||\n");
    }

    else if (state == 2)
    {
        printf("                                                           " RED " /|      /|" RESET "                           \n"
               "                                                          " RED " | |     | | " RESET "                          \n"
               "                                                         " RED "  | |_____| |  " RESET "                         \n"
               "                                           " YELLOW "< D E A D ! >   " RED "/ ________ |" RESET "                          \n"
               "                                                         " RED " / /        | |" RESET "                         \n"
               "                                                          " RED "| |  X  X  | |" RESET "                         \n"
               "                                                      " RED "___/  |__  ___|  |__" RESET "                       \n"
               "                                                    " RED " /         |/         |" RESET "                      \n"
               "                                                   " RED "  /                     |" RESET "                     \n");
        printf(GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" RESET "");
        delay(1);
        system("cls");
        printf("                                                                                                                 \n"
               "                                                                                                             \n"
               "                                                         " RED "   / }_____| }  " RESET "                     \n"
               "                                                          " RED " /_/______/_/|" RESET "            \n"
               "                                                         " RED " / /        | |" RESET "                       \n"
               "                                                  " RED "___     | |  X  X  | |    ___" RESET "                \n"
               "                                                 " RED "/   }___/  |__  ___ |  |__/   }" RESET " \n");
        printf(GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" RESET "");
        delay(3);
    }
    else
    {
        printf("||                                                           " RED " /|      /|" RESET "                      ||\n"
               "||                                                          " RED " | |     | | " RESET "                     ||\n"
               "||                                                         " RED "  | |_____| |  " RESET "                    ||\n"
               "||                                                           " RED "/ ________ |" RESET "                     ||\n"
               "||                                                         " RED " / /        | |" RESET "                    ||\n"
               "||                                                          " RED "| |  o  o  | |" RESET "                    ||\n"
               "||                                                      " RED "___/  |__  ___ |  |__" RESET "                 ||\n"
               "||                                                    " RED " /         |/         |" RESET "                 ||\n"
               "||                                                   " RED "  /                     |" RESET "                ||\n");
    }
}
void enemy_hilichurl(int state)
{
    if (state == 1)
    {
        printf("||                                                           " RED "|^^^^^^^^^^/" RESET "                     ||\n"
               "||                                                          " RED "^ /|______/| ^" RESET "                    ||\n"
               "||                                                         " RED " ^ |   /}   |  ^" RESET "                   ||\n"
               "||                                              " YELLOW "< H I T ! > " RED "^ | > {/ < |  ^" RESET "                   ||\n"
               "||                                                          " RED " ^|________| ^" RESET "                    ||\n"
               "||                                                          " RED "/^__________^}" RESET "                    ||\n"
               "||                                                         " RED "/              }" RESET "                   ||\n"
               "||                                                         " RED "|  }        /  |}" RESET "                  ||\n");
    }

    else if (state == 2)
    {
        printf("                                                           " RED "|^^^^^^^^^^/" RESET "                         \n"
               "                                                          " RED "^ /|______/| ^" RESET "                        \n"
               "                                                         " RED " ^ |   /}   |  ^" RESET "                       \n"
               "                                            " YELLOW "< D E A D ! > " RED "^ | X {/ X |  ^" RESET "             \n"
               "                                                          " RED " ^|________| ^" RESET "                        \n"
               "                                                          " RED "/^__________^}" RESET "                        \n"
               "                                                         " RED "/              }" RESET "                       \n"
               "                                                         " RED "|  }        /  |}" RESET "                      \n");

        printf(GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" RESET "");
        delay(1);
        system("cls");
        printf("                                                                                                                \n"
               "                                                                                                                \n"
               "                                                                                                                \n"
               "                                                           " RED "|^^^^^^^^^^/" RESET "                         \n"
               "                                                          " RED "^ /|______/| ^" RESET "                        \n"
               "                                                         " RED " ^ |   /}   |  ^" RESET "                       \n"
               "                                                    " RED " ____ ^ | X {/ X |  ^" RED "____                     \n"
               "                                                   " RED " (    ) ^|________| ^(    )" RESET "                  \n");
        printf(GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" RESET "");
        delay(3);
    }
    else
    {
        printf("||                                                           " RED "|^^^^^^^^^^/" RESET "                     ||\n"
               "||                                                          " RED "^ /|______/| ^" RESET "                    ||\n"
               "||                                                         " RED " ^ |   /}   |  ^" RESET "                   ||\n"
               "||                                                          " RED "^ | O {/ O |  ^" RESET "                   ||\n"
               "||                                                          " RED " ^|________| ^" RESET "                    ||\n"
               "||                                                          " RED "/^__________^}" RESET "                    ||\n"
               "||                                                         " RED "/              }" RESET "                   ||\n"
               "||                                                         " RED "|  }        /  |}" RESET "                  ||\n");
    }
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
    else if (state == 2)
    {
        printf("                                                            " RED "______" RESET "                          \n"
               "                                                          " RED "/ ^   ^  }" RESET "                        \n"
               "                                             " YELLOW "< D E AD >   " RED "| X    X |" RESET "                        \n"
               "                                                          " RED "{________}" RESET "                        \n");
        printf(GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" RESET);
        delay(1);

        system("cls");
        printf("                                                                                                           \n"
               "                                                                                                               \n"
               "                                                           " RED "_________" RESET "                          \n"
               "                                                         " RED "{__x____x__}" RESET "                        \n");
        printf(GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n" RESET);
        delay(3);
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
        printf("||" GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" RESET "||\n");
        printf("================================================================================================\n");
    }
    else
    {
        printf("||           _____      / 7                  VS                                               ||\n"
               "||          /      }   / /                                                                    ||\n"
               "||          |  O_O |  / /                                                                     ||\n"
               "||          {______/ / /                                                                      ||\n");
        printf("||" GREEN "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" RESET "||\n");
        printf("================================================================================================\n");
    }
}
void genshintext()
{
    system("cls");
    printf(YELLOW "       _____                _     _         _                           _   \n"
                  "      /_  __|              | |   (_)       (_)                         | |  \n"
                  "        | |   __ _____  ___| |__  _ _ __    _ _ __ ___  _ __   __ _  __| |_ \n"
                  "        | |  / _ | '_ |/ __| '_  | | '_  | | | '_ ` _  | '_  / _` |/ __| __|\n"
                  "     | || | |  __/ | | |__ | | | | | | | | | | | | | | | |_) | (_|| (__| |_ \n"
                  "     |___ / | ___|_| |_|___/_| |_|_|_| |_| |_|_| |_| |_| .__/|__,_||___|__|\n"
                  "                             but its made in terminal\n" RESET);
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
    Beep(2000, 500);
}
void gameover_display(int round)
{
    printf("================================================================================================\n");
    printf("||                                G A M E      O V E R                                         ||\n"
           "||                                  Rounds survived= %d                                      ||\n",
           round);
    printf("================================================================================================\n");
    printf("\n                                 Will be returning you to main menu\n");
    Beep(2000, 500);
}

void gamemenu_buttons()
{
    printf("\n                                  ---------------                                \n"
           "                                 |  START GAME ? |                               \n"
           "                                  ---------------                                \n"
           "                                  type y to start\n");
    printf("                             --------------------------                                                                \n"
           "                            |   EXIT /CHANGE ACCOUNT ? |                               \n"
           "                            ----------------------------                          \n"
           "                                  type x to exit\n");
}
void domain_clear_reward()
{

    printf("================================================================================================\n");
    printf("|| You have cleared the domain! pick a reward                                                 ||\n"
           "||                     _____________                    _____________                         ||\n"
           "||                    |1  +1 HEALTH |                  |2  +1 ATTACK |                        ||\n"
           "||                     -------------                    --------------                        ||\n");
    printf("================================================================================================\n");
}
void player_decisions_ui()
{
    printf("                                           Player's turn                      \n\n");
    printf("                                    what would you like to do                  \n\n"
           "                ___________                 ___________              ___________       \n"
           "               |  ATTACK   |               |   DODGE   |            |  Q U I T  |      \n"
           "               |_____1_____|               |_____2_____|            |_____3_____|       \n");
}
void thanks()
{

    system("cls");
    printf("\n\n                               Thanks for playing!  ");
    printf("\n                           Made by nexus  \n\n");
    delay(1);
    system("cls");
}
void enemy_display(int enemy, int state)
{
    if (enemy == 1)
    {
        enemy_hilichurl(state);
    }

    else if (enemy == 2)
    {
        enemy_abyssmage(state);
    }
    else
    {
        enemyslime(state);
    }
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
    Beep(3000, 50);
    delay_n(4);
}

void display(int transition, int mode, int enemy)
{
    if (transition == 0) // enemy display normal
    {
        enemy_display(enemy, 0);
        player(0);
    }
    else if (transition == 1) // 1st transition rolling text
    {
        enemy_display(enemy, 0);
        player(0);
        transitionscreen(mode);
    }
    else if (transition == 2) // 2nd transition below
    {
        transitionscreen(mode);
    }
    else if (transition == 3) // enemy hurt
    {
        enemy_display(enemy, 1);
        player(0);
        Beep(2000, 500);
    }
    else if (transition == 4) // player hurt
    {
        enemy_display(enemy, 0);
        player(1);
        Beep(2000, 500);
    }
    else if (transition == 5) // enemy death end screen
    {
        enemy_display(enemy, 2);
    }
}
int dupe_check(FILE *player_data, char temp_username[10])
{
    user_info atemp[MAX];

    player_data = fopen("player_data.txt", "r");

    for (int x = 0; x < MAX; ++x)
    {
        fscanf(player_data, "%s", atemp[x].username);
        fscanf(player_data, "%s", atemp[x].password);
        fscanf(player_data, "%d", &(atemp[x].max_level));
    }

    for (int x = 0; x < MAX; ++x)
    {
        if (strcmp(atemp[x].username, temp_username) == 0)
        {
            system("cls");
            printf("\n\n\n\n\t\t\tThat username already exists!\n\n");
            fclose(player_data);
            delay(1);
            return 1;
        }
    }
    fclose(player_data);
    return 0;
}
void score_update(FILE *player_data, int highscore, char temp_username[], char temp_password[], int line)
{
    FILE *fPtr;
    FILE *fTemp;

    char buffer[100];
    char newline[100];
    char temp_store[100];
    int count, check_line;

    check_line = line;

    sprintf(newline, "%d\n", highscore);

    fPtr = fopen("player_data.txt", "r");
    fTemp = fopen("replace.tmp", "w");

    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\n\n\t\tSAVE ERROR! EXITING!\n\n");
        exit(EXIT_SUCCESS);
    }
    count = 0;
    while ((fgets(buffer, 100, fPtr)) != NULL)
    {
        count++;

        if (count == check_line)
            fputs(newline, fTemp);
        else
            fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove("player_data.txt");
    rename("replace.tmp", "player_data.txt");
}
