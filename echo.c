#include<stdio.h>
#include<unistd.h>
#include<string.h> 

ssize_t my_write(int fd, const void *buf, size_t count)
{
        register ssize_t result asm("rax");
        register int rdi asm("rdi") = fd
        register const void *rsi asm("rsi") = buf;
        register size_t rdx asm("rdx") = count;

        asm volatile(
                "mov $1, %%eax\n\t"
                "syscall"
                : "=r"(result)
                : "r"(rdi), "r"(rsi), "r"(rdx)
                : "rcx", "rll", "memory"
        );

        return result;
}

int main(int argc, char **argv)
{
        for(int i = 1; i < argc; i++)
        {
                my_write(1, argv[i], strlen(argv[i]));
                if(i < argc - 1){
                        my_write(1, " ", 1);   //try to find out  smth make oc calls only once
                }
                //printf((i != argc - 1) ? "%s " : "%s", argv[i]);
        }
        my_write(1, "\n", 1);

         return 0;
}