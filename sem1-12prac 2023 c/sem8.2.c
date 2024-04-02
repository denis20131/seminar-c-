#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char** argv)
{
    if(argc != 6) return 0;
    char* prog1 = argv[1];
    char* arg1 = argv[2];
    char* prog2 = argv[3];
    char* arg2 = argv[4];
    int status;
    if((arg1 < 0)||(arg2 < 0)) return 0;
    char flag = argv[5][0];
    int p1, p2; int st1, st2;
    if(flag=='p'){

        if(((p1=fork())==0)||((p2=fork())==0)){
            if(p1==0){
                execl(prog1, prog1,arg1, NULL);
                exit(-1);
            }
            if(p2==0){
                execl(prog2,prog2, arg2,NULL);
                exit(-1);
            }
        }
        waitpid(p1, &st1, 0);
        waitpid(p2, &st2, 0);
        if(WIFEXITED(st1)){
            printf("%s exit %d\n", prog1, WEXITSTATUS(st1));
        }else printf("%s aborted\n", prog1);
        if(WIFEXITED(st2)){
            printf("%s exit %d\n", prog2, WEXITSTATUS(st2));
        }else printf("%s aborted\n", prog2);
    }
     else if(flag=='s'){
        int c = 2;
        char* progs[2] = {prog1, prog2};
        char* args[2] = {arg1,arg2};
        int p, st;
        while(c){

            if((p=fork())==0){
                char* vector[3] = {progs[2-c],args[2-c],NULL};
                execv(progs[2-c], vector);
            }
            waitpid(p, &st, 0);
            if(WIFEXITED(st)){
                printf("%s exit %d\n", progs[2-c], WEXITSTATUS(st));
            }else printf("%s aborted\n", progs[2-c]);
            c--;
        }
    }
    return 0;
}