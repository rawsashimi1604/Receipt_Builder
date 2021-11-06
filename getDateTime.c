#include "getDateTime.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
struct tm {
   int tm_sec;          seconds,  range 0 to 59          
   int tm_min;          minutes, range 0 to 59           
   int tm_hour;         hours, range 0 to 23             
   int tm_mday;         day of the month, range 1 to 31  
   int tm_mon;          month, range 0 to 11             
   int tm_year;         The number of years since 1900   
   int tm_wday;         day of the week, range 0 to 6    
   int tm_yday;         day in the year, range 0 to 365  
   int tm_isdst;        daylight saving time             
};
*/

struct tm *createTimeStruct() {
    time_t currDateTime;
    time(&currDateTime);
    struct tm *myDateTimeStruct = localtime(&currDateTime);
    return myDateTimeStruct;
}

char* getCurrentDateTime(void) {
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    return asctime(timeinfo);
}

char* getCurrentTime(void) {
    struct tm *currLocalTime = createTimeStruct();
    int secsVal = currLocalTime->tm_sec;
    int minsVal = currLocalTime->tm_min;
    int hrsVal = currLocalTime->tm_hour;

    // Convert all int values to strings to output.
    char *output = malloc(9 * sizeof(char));
    snprintf(output, 9, "%02d:%02d:%02d", hrsVal, minsVal, secsVal);

    return output;
}

char* getCurrentDate(void) {
    struct tm *currDateTime = createTimeStruct();
    int dayVal = currDateTime->tm_mday;
    int mnthVal = currDateTime->tm_mon;
    int yearVal = 1900 + currDateTime->tm_year;
    
    char *output = malloc(11 * sizeof(char));
    snprintf(output, 11, "%02d-%02d-%02d", dayVal, mnthVal, yearVal);
    return output;
}
