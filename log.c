
#include "log.h"
#include <stdio.h> 
#include <stdarg.h> 
#define LOG_BUF_SIZE 1024

FILE* g_log = NULL; 
void openLog (char const* filename)
{
    if (g_log)
        return; 

    g_log = fopen (filename, "w+"); 
}

void writeLog(const char *fmt, ...)
{
    // can dump to DebugView even if log open failed !
    //if (!log_)
    //    return; 

    char buf[LOG_BUF_SIZE] = { 0 }; 

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF_SIZE - 1, fmt, ap);
    va_end(ap);

    if (g_log)
    {
        fputs (buf, g_log); 
        fflush (g_log); 
    }
}


void closeLog ()
{
    if (g_log)
    {
        fclose (g_log); 
        g_log = NULL; 
    }
}

