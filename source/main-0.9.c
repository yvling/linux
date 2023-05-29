#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#define MAX_SIZE 100

void addWord(char dict[][20], char meaning[][20], char rank[][20], int* wordCount); // 添加单词
void searchWord(char dict[][20], char meaning[][20],  char rank[][20], int wordCount); // 查找单词
int chooseRank(char dict[][20],char meaning[][20], char rank[][20], char result[][20], int wordCount);//选择难度
void randomWord(char dict[][20], char meaning[][20], char rank[][20], int wordCount); // 随机输出单词
void review(char dict[][20], char meaning[][20], char rank[][20], int wordCount); // 复习单词
void handle_sigint();

int main() {
    char dict[MAX_SIZE][20]; // 单词字典
    char meaning[MAX_SIZE][20];//意思
    char rank[MAX_SIZE][20];//难度
    char result[MAX_SIZE][20];//难度选择结果
    int wordCount = 0;
    srand(time(NULL)); // 初始化随机数种子
    addWord(dict,meaning,rank,&wordCount);
    pid_t pid = fork(); // 创建子进程
    if (pid == 0) { // 子进程
        printf("单词数量：%d\n", wordCount); // 统计单词数量
        exit(0); // 子进程结束
    } else if (pid > 0) { // 父进程
        int choice;
        while (1) {
            printf("请选择功能：\n"); // 选择功能
            printf("1. 添加单词\n"); // 添加单词
            printf("2. 查找单词\n"); // 查找单词
            printf("3. 随机输出单词\n"); // 随机输出单词
            printf("4. 复习单词\n"); // 复习单词
            printf("5. 退出程序\n"); // 退出程序
            scanf("%d", &choice); // 输入选择
            switch (choice) {
                case 1:
                    addWord(dict, meaning, rank, &wordCount); // 添加单词
                    break;
                case 2:
                    searchWord(dict, meaning, rank, wordCount); // 查找单词
                    break;
                case 3:
                    randomWord(dict, meaning, rank, wordCount); // 随机输出单词
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
                    review(dict, meaning, rank, wordCount); // 复习单词
                    exit(0);
                    }
                case 5:
                    kill(pidr,SIGKILL);
                    kill(pid, SIGKILL); // 结束子进程
                    exit(0); // 父进程结束
                default:
                    printf("输入错误，请重新选择\n"); // 输入错误
            }
        }
    } else { // 创建子进程失败
        fprintf(stderr, "创建子进程失败\n"); // 输出错误信息
        exit(1);
    }
    return 0;
}

void addWord(char dict[][20],char meaning[][20], char rank[][20], int* wordCount) {
    char word[20], mean[20] ,rk[20];
    printf("请输入单词：\n"); // 输入单词
    scanf("%s", word);
    printf("请输入汉语释义：\n"); // 输入汉语释义
    scanf("%s", mean);
    printf("请输入难度：\n"); // 输入汉语释义
    scanf("%s", rk);
    strcpy(dict[*wordCount], word); // 复制单词
    strcpy(meaning[*wordCount], mean); // 复制汉语释义
    strcpy(rank[*wordCount],rk);//复制难度
    (*wordCount)++; // 单词数量加一
    printf("添加成功\n"); // 添加成功
}

void searchWord(char dict[][20], char meaning[][20], char rank[][20], int wordCount) {
    char word[20];
    printf("请输入要查找的单词：\n"); // 输入要查找的单词
    scanf("%s", word);
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(dict[i], word) == 0) { // 如果找到单词
            printf("%s：%s\n难度：%s\n", dict[i], meaning[i],rank[i]); // 输出单词和汉语释义和难度
            return;
        }
    }
    printf("未找到该单词\n"); // 未找到该单词
}
void searchRank(char dict[][20],char meaning[][20],char rank[][20],int wordCount);
int chooseRank(char dict[][20],char meaning[][20], char rank[][20], char result[][20], int wordCount)//选择难度
{
    int j=0;
    char r[20];
    scanf("%s",r);
    for(int i = 0;i<wordCount;i++){
      if(strcmp(rank[i], r)==0){
        strcpy(result[j],rank[i]);
        j++;
      }
    }
    return j;
}

void randomWord(char dict[][20], char meaning[][20], char rank[][20], int wordCount) {
    if (wordCount == 0) { // 如果单词列表为空
        printf("单词列表为空\n"); // 输出单词列表为空
        return;
    }
    int index = rand() % wordCount; // 随机生成单词下标
    printf("%s：%s\n难度：%s\n", dict[index], meaning[index],rank[index]); // 输出单词和汉语释义和难度
}

void review(char dict[][20], char meaning[][20], char rank[][20], int wordCount) {
    while (1) {
        randomWord(dict, meaning, rank, wordCount); // 随机输出单词
        printf("按Ctrl+c返回主界面\n"); // 提示按Ctrl+c返回主界面
        sleep(1); // 等待1秒
    }
}

void handle_sigint(int sig) {
    // do nothing
}