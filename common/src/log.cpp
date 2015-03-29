#include <syslog.h>
#include <stdio.h>

bool __useSysLog = false;

void initLog(bool useSysLog){
    __useSysLog = useSysLog;
    if(__useSysLog){
        openlog("chapi", LOG_PID, LOG_DAEMON );
    }
}

void cleanLog(){
    if(__useSysLog){
        closelog();
    }
    else {
        fflush(stdout);
    }
}

