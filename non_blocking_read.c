/* A simple program to receive input from users only when
they entered input otherwise continue with the loop. */
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    char buf[1025];
    ssize_t rlen;
    fd_set read_fds;
    /* For defining time to wait. */
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    /* Uncomment setvbuf(stdout, NULL, _IONBF, 0); if you dont want 
    output to be buffered. There are instances when you wonder why 
    printf isn't printing and it is because it is buffered. */
    //setvbuf(stdout, NULL, _IONBF, 0);
    while(*buf!='q') {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        /* Wait for connections for tv.tv_sec(seconds) and tv_usec. 
           (milliseconds) */
        select(1,&read_fds,0,0,&tv);
        /* If there is input waiting then we read stdin  */
        if(FD_ISSET(STDIN_FILENO,&read_fds)) {
            rlen = read(STDIN_FILENO, buf, 1024);
            if(rlen > -1)
            {
                buf[rlen] = 0;
                printf("%s", buf);
            }
            else {
                perror("Error reading input.");
            }
        }
    }
}
