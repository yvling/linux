#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void addWord(char dict[][20], char meaning[][20], int* wordCount); // 添加单词
void searchWord(char dict[][20], char meaning[][20], int wordCount); // 查找单词
void randomWord(char dict[][20], char meaning[][20], int wordCount); // 随机输出单词
void review(char dict[][20], char meaning[][20], int wordCount); // 复习单词
void handle_sigint();

int main() {
    char dict[100][20]; // 单词字典
    char meaning[100][20];
    int wordCount = 0;
    srand(time(NULL)); // 初始化随机数种子
    addWord(dict,meaning,&wordCount);
    pid_t pid = fork(); // 创建子进程
    if (pid == 0) { // 子进程
        printf("单词数量：%d\n", wordCount); // 统计单词数量
        exit(0); // 子进程结束
    } else if (pid > 0) { // 父进程
        int choice;
        while (1) {
            printf("请选择功能：\n");
            printf("1. 添加单词\n");
            printf("2. 查找单词\n");
            printf("3. 随机输出单词\n");
            printf("4. 复习单词\n");
            printf("5. 退出程序\n");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    addWord(dict, meaning, &wordCount);
                    break;
                case 2:
                    searchWord(dict, meaning, wordCount);
                    break;
                case 3:
                    randomWord(dict, meaning, wordCount);
                    break;
                case 4:;
                    pid_t pidr = fork(); // 创建子进程
                    if(pidr>0)
                    {//父进程
                    signal(SIGINT, handle_sigint);//阻塞ctrl+c
                    waitpid(pidr,NULL,0);
                    kill(pidr, SIGKILL); // 结束子进程
                    signal(SIGINT, SIG_DFL);//恢复ctrl+c
                    break;
                    }
                    else if(pidr<0)
                    {//错误
                      printf("创建子进程失败");
                    }
                    else
                    {//子进程
                    review(dict, meaning, wordCount);
                    exit(0);
                    }
                case 5:
                    kill(pid, SIGKILL); // 结束子进程
                    exit(0); // 父进程结束
                default:
                    printf("输入错误，请重新选择\n");
            }
        }
    } else { // 创建子进程失败
        fprintf(stderr, "创建子进程失败\n");
        exit(1);
    }
    return 0;
}

void addWord(char dict[][20], char meaning[][20], int* wordCount) {
    char word[20], mean[20];
    printf("请输入单词：\n");
    scanf("%s", word);
    printf("请输入汉语释义：\n");
    scanf("%s", mean);
    strcpy(dict[*wordCount], word);
    strcpy(meaning[*wordCount], mean);
    (*wordCount)++;
    printf("添加成功\n");
}

void searchWord(char dict[][20], char meaning[][20], int wordCount) {
    char word[20];
    printf("请输入要查找的单词：\n");
    scanf("%s", word);
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(dict[i], word) == 0) {
            printf("%s：%s\n", dict[i], meaning[i]);
            return;
        }
    }
    printf("未找到该单词\n");
}

void randomWord(char dict[][20], char meaning[][20], int wordCount) {
    if (wordCount == 0) {
        printf("单词列表为空\n");
        return;
    }
    int index = rand() % wordCount;
    printf("%s：%s\n", dict[index], meaning[index]);
}

void review(char dict[][20], char meaning[][20], int wordCount) {
    while (1) {
        randomWord(dict, meaning, wordCount);
        printf("按Ctrl+c返回主界面\n");
        sleep(1);
    }
}

void handle_sigint(int sig) {
    // do nothing
}