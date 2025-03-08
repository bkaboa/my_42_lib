#include "logger.h"

static Logger *logger;

Logger *get_logger_instance()
{
    if (logger == NULL)
    {
        logger = (Logger *)malloc(sizeof(Logger));
        #ifdef FILE_LOG
            logger->file = fopen("log.txt", "w");
        #endif
        logger->log = &log;
    }
    return logger;
}

#ifdef PRINTF_LOG
    void log(const char *msg, u_int8_t log_level, ...)
    {
        va_list args;
        va_start(args, log_level);
        #ifdef FILE_LOG
            vfprintf(logger->file, msg, args);
        #endif
        vfprintf(stdout, msg, args);
        va_end(args);
    }
#else
    void log(const char *msg, u_int8_t log_level, ...)
    {
        va_list args;
        va_start(args, log_level);
        #ifdef FILE_LOG
            write(fileno(logger->file), msg, sizeof(msg));
        #endif
        va_end(args);
    }
#endif
