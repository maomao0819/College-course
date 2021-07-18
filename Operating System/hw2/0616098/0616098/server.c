#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 123456
#define SHMSZ 27

int *ptr;

int main () {

    // share memory id
    int id;

    /************************* TODO 1 *************************/
    // Create a shared memory section
    /************************* TODO 1 *************************/

    id = shmget(SHM_KEY, SHMSZ, IPC_CREAT | 0666);
    if (id < 0) 
    {
        perror("Shared memory create");
        return 1;
    }

    /************************* TODO 2 *************************/
    // Attach the memory section
    // the return value is a pointer to the shared memory section
    /************************* TODO 2 *************************/

    int *shm = shmat(id, NULL, 0);
    if (shm == (int *) -1) 
    {
        perror("Shared memory attach");
        return 1;
    }

    ptr = shm;

    ptr[0] = 0;

    printf("\033[1;32m[server] The value is %d\033[0m\n", ptr[0]);

    while(1) 
    {
        int cmd;

        printf("\n");
        printf("1: Show the value\n");
        printf("2: Modify the value\n");
        printf("3: Exit\n");
        printf("Enter commands: ");
        scanf("%d", &cmd);

        if (cmd == 1)
            printf("\033[1;32m[server] The value is %d\033[0m\n", ptr[0]);
        else if (cmd == 2) 
	{
            printf("Input new value: ");
            scanf("%d", &ptr[0]);
        }
        else
            break;  
        sleep(1);      
    } 

    return 0;
}

