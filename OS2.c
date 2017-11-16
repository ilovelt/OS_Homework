#include<stdio.h>
#include<sys/socket.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h> 
struct sembuf sops[2];
int sid;
int P(int i)
{
    sops[i].sem_num=0;  
    sops[i].sem_op=-1;  
    sops[i].sem_flg=0;  
    return semop(sid, &sops[i], 1);
}
int V(int i)
{
    sops[i].sem_num=0;  
    sops[i].sem_op= 1;  
    sops[i].sem_flg=0;  
    return semop(sid, &sops[i], 1);
}
int main()
{
    int n;
    int i = 0;
    key_t key = ftok("./OS2.c",1);//创建关键字
    sid = semget(key, 1, IPC_CREAT | 0666);//创建信号量集
    //printf("sid %d:\n",sid);
    //printf("key_t: %c\n",k);
    n = fork();//父进程是公交车司机，子进程是售票员；
    if(n==-1) 
    {
        printf("fork error\n");
        
        exit(1);
    }
    if(n)
    {
        while(1)
        {
          printf("司机正常行车\n");
          sleep(1);
          printf("到站，停车\n");
          V(1);
          P(0);
          printf("离开车站");

        }
        

    }
    else{
        while(1)
        {
          printf("售票\n");
          sleep(1);
          P(1);
          printf("开车门\n");
          printf("上人、下人\n");
          printf("关车门\n");
          sleep(1);
          V(0);
          

        }
        
    }
    return 0;
}