#include <stdio.h>   
#include <stdlib.h>   
#include <linux/rtc.h>   
#include <sys/ioctl.h>   
#include <sys/time.h>   
#include <sys/types.h>   
#include <fcntl.h>   
#include <unistd.h>   
#include <errno.h>   
#include <time.h> 
int main(){ 
        struct timeval tv;  
        struct timezone tz;  
        int res = gettimeofday(&tv, &tz);// 获取当前时间, 秒数 
        printf("%d %ld %ld\n", res, tv.tv_sec, tv.tv_usec); 
        time_t tm = time(NULL); 
        printf("%ld\n", tm); 
        int fd, retval;   
        fd = open("/dev/rtc", O_RDONLY);   
        if (fd == -1) {   
                perror("/dev/rtc");   
                exit(errno);   
        }   
        struct rtc_time rtc_tm;   
        retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);  
        if(retval == -1) 
        { 
                perror("ioctl"); 
        } 
        printf("a %d\n", retval); 
        fprintf(stderr, "RTC date/time: %d/%d/%d %02d:%02d:%02d\n",   
                        rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,   
                        rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec); 
 
} 
