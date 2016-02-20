#include<stdio.h>
#include <unistd.h>

int fork1()
{
	printf("fork.\n");
    int pid = 0;
    pid = fork();
    if (pid == 0) {
        printf("child=%d.\n", getpid());
        return -1;
    }
    printf("father=%d.\n", getpid());
    return 0;
}
int fork2()
{
	 printf("fork.\n");
    int pid = 0;
    pid = fork();
    if (pid == 0) {
        printf("child=%d.\n", getpid());        
    }
    printf("father=%d.\n", getpid());
    return 0;
}
int fork3()
{
    int pid = 0;
    int i;
    for (i = 0; i < 3; i++) {

        pid = fork();
        printf("%d*",getpid());
    }

}
int fork4()
{
   int i=0;  
   printf("i son/pa ppid pid  fpid\n");  
   //ppid指当前进程的父进程pid  
   //pid指当前进程的pid,  
   //fpid指fork返回给当前进程的值  
   for(i=0;i<2;i++){  
       pid_t fpid=fork();  
       if(fpid==0)  
           printf("%d child  %4d %4d %4d\n",i,getppid(),getpid(),fpid);  
       else  
           printf("%d parent %4d %4d %4d\n",i,getppid(),getpid(),fpid);  
   }  
   return 0; 
}
int main(void)
{
	fork4();
    return 0;
}
