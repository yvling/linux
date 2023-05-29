
//For C language and Linux environment, design a word memorization program with the following requirements:
// 1. Read in multiple words and their Chinese meanings through the program.
// 2. Complete word meaning search.
// 3. Randomly output words to test learning effect.
// 4. Allow users to dynamically define new words, difficult words, or easily mistaken words.
// 5. Use fork function to create a child program to calculate the number of words and save running time.
// 6. Use signals to allow the Ctrl+c key to exit the review function and end the infinite loop.
// 7. Present options in the form of a menu and execute corresponding operations according to user input.
// These words can also be dynamically defined by the user as new words, difficult words, or easily mistaken words.
// At the beginning of the main program, the program should use the fork function to create a child program to calculate the number of words, so that two processes are running at the same time, saving running time. Through the setting of signals, the Ctrl+c key is used to exit in the review function (for review), enter the main interface, and end the infinite loop. Other functions are improved according to the experience of using electronic dictionaries.
// It is required to present many options in the form of a menu and execute corresponding operations according to user input.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 20
#define MAX_MEANING_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    char meaning[MAX_MEANING_LENGTH];
} Word;

Word words[MAX_WORDS];
int num_words = 0;

void read_words();
void search_meaning();
void test_learning_effect();
void define_new_words();
void calculate_word_number();
void handle_signal(int signal);

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        calculate_word_number();
        exit(0);
    }
    signal(SIGINT, handle_signal);
    read_words();
    while (1) {
        printf("Please select an option:\n");
        printf("1. Search word meaning\n");
        printf("2. Test learning effect\n");
        printf("3. Define new words\n");
        printf("4. Exit\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                search_meaning();
                break;
            case 2:
                test_learning_effect();
                break;
            case 3:
                define_new_words();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

void read_words() {
    // Read in multiple words and their Chinese meanings through the program.
    // These words can also be dynamically defined by the user as new words, difficult words, or easily mistaken words.
    // Allow users to dynamically define new words, difficult words, or easily mistaken words.
    // Present options in the form of a menu and execute corresponding operations according to user input.
    // It is required to present many options in the form of a menu and execute corresponding operations according to user input.
    // Other functions are improved according to the experience of using electronic dictionaries.
    printf("Enter words and their meanings (type '0' to stop):\n");
    while (1) {
        if (num_words == MAX_WORDS) {
            printf("Maximum number of words reached\n");
            break;
        }
        char word[MAX_WORD_LENGTH], meaning[MAX_MEANING_LENGTH];
        scanf("%s", word);
        if (strcmp(word, "0") == 0) {
            break;
        }
        scanf("%s", meaning);
        strcpy(words[num_words].word, word);
        strcpy(words[num_words].meaning, meaning);
        num_words++;
    }
}

void search_meaning() {
    // Complete word meaning search.
    printf("Enter word to search meaning:\n");
    char word[MAX_WORD_LENGTH];
    scanf("%s", word);
    int i;
    for (i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            printf("%s\n", words[i].meaning);
            return;
        }
    }
    printf("Word not found\n");
}
void test_learning_effect() {
    // Randomly output words to test learning effect.
    srand(time(NULL));
    int i;
    char word[MAX_WORD_LENGTH];
    for (i = 0; i < 10; i++) {
        int index = rand() % num_words;
        int ec = rand()%1;
        if(ec==1)
        {
        printf("%s\n", words[index].word);
        scanf("%s",word);
        printf("%s\n", words[index].meaning);
        }
        else //sleep(1);
        {
        printf("%s\n", words[index].meaning);
        }
        sleep(1);
    }
}

void define_new_words() {
    // Allow users to dynamically define new words, difficult words, or easily mistaken words.
    printf("Enter word and its meaning:\n");
    char word[MAX_WORD_LENGTH], meaning[MAX_MEANING_LENGTH];
    scanf("%s %s", word, meaning);
    strcpy(words[num_words].word, word);
    strcpy(words[num_words].meaning, meaning);
    num_words++;
}
void calculate_word_number() {
    // Use fork function to create a child program to calculate the number of words and save running time.
    printf("Number of words: %d\n", num_words);
}
void handle_signal(int signal) {
    // Use signals to allow the Ctrl+c key to exit the review function and end the infinite loop.
    printf("Ctrl+c pressed\n");
    exit(0);
}

