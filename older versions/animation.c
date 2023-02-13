#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define GREEN "\x1b[32m"

void delay(int number_of_seconds);

int main()
{
    int x = 1;
    while (x == 1)
    {
        system("cls");

        printf(GREEN
               "                                                                             \n"
               "                                                                             \n"
               "                                                                             \n"
               "                                                           _____                        \n"
               "                                                         / ^   ^  }                       \n"
               "                                                         | 0    0 |                      \n"
               "                                                         {________}                      \n");
        delay(3);
        Beep(1123, 50);
        system("cls");
        printf(
            "                                                                             \n"
            "                                                                             \n"
            "                                                           _____                        \n"
            "                                                         / ^   ^  }                       \n"
            "                                                         | 0    0 |                      \n"
            "                                                         {________}                      \n"
            "                                                          '' ''' '                     \n");
        delay(3);
        system("cls");
        printf(
            "                                                                             \n"
            "                                                            _____                        \n"
            "                                                         { 0    0 }                   \n"
            "                                                        ( ________ )                 \n"
            "                                                          '' ''' '                     \n"
            "                                                                            \n"
            "                                                                             \n");
        delay(3);
        system("cls");
        printf(
            "                                                         _________                     \n"
            "                                                        {__-____-__}                        \n"
            "                                                                         \n"
            "                                                                       \n"
            "                                                                             \n"
            "                                                                            \n"
            "                                                                             \n");
        delay(3);
        system("cls");
        printf(
            "                                                          '' ''' '                           \n"
            "                                                           _____                 \n"
            "                                                         { 0    0 }                \n"
            "                                                        ( ________ )                      \n"
            "                                                                            \n"
            "                                                                             \n");
        delay(3);
        system("cls");
        printf("                                                                               \n"
               "                                                           '' ''' '                       \n"
               "                                                           _____                       \n"
               "                                                         / ^   ^  }                      \n"
               "                                                         | 0    0 |                  \n"
               "                                                         {________}                        \n"
               "                                                                             \n");
        delay(3);
        system("cls");
        printf(
            "                                                                             \n"
            "                                                                                   \n"
            "                                                                           \n"
            "                                                            ''' '              \n"
            "                                                            _____                  \n"
            "                                                          { 0    0 }                    \n"
            "                                                         ( ________ )                     \n");
        delay(3);
        system("cls");
        printf(
            "                                                                             \n"
            "                                                                               \n"
            "                                                                         \n"
            "                                                                       \n"
            "                                                                             \n"
            "                                                         _________                    \n"
            "                                                        {__-____-__}    \n");
        Beep(1123, 50);
        delay(3);
    }
}

void delay(int number_of_seconds)
{
    int milli_seconds = 100 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}
