#include <stdio.h>
#include <time.h>

int main(){
    time_t currentTime;
    time(&currentTime);
    printf("%s",ctime(&currentTime));
    struct tm *myTime = localtime(&currentTime);
    printf("%d\n",myTime->tm_mon);
    printf("%d\n",myTime->tm_mday);
}

