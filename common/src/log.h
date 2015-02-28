#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <syslog.h>
#include <cerrno>

extern void initLog(bool useSysLog);
extern void cleanLog();
extern bool __useSysLog;

#define log(severity, msg, ...) \
   if(__useSysLog){ \
      syslog(severity, msg, ##__VA_ARGS__); \
   } \
   else{ \
      if(severity <= LOG_ERR){ \
         fprintf(stderr, "Error: "); \
         fprintf(stderr, msg, ##__VA_ARGS__); \
         fprintf(stderr, "\n"); \
      } \
      else{ \
         printf(msg, ##__VA_ARGS__); \
         printf("\n"); \
      } \
   }

#endif // LOG_H
