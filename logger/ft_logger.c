#include "ft_logger.h"

static Logger *logger;

static void logger_func(const u_int8_t log_level, const char *msg, ...)
{
    char *format;

    va_list args;
    va_start(args, msg);
    vsprintf(format, msg, args);
    va_end(args);
    #ifdef FILE_LOG
        fprintf(logger->file, "%s%s%s", LOG_LEVELS_MSG[log_level], format, COLOR_RESET);
    #endif
    dprintf(LOG_STD(log_level), "%s%s%s", COLOR_MSG(log_level), format, COLOR_RESET);
}

Logger *get_logger_instance()
{
    if (logger == NULL)
    {
        logger = (Logger *)malloc(sizeof(Logger));
        #ifdef FILE_LOG
            logger->file = fopen("log.txt", "w");
        #endif
        logger->log = &logger_func;
    }
    return logger;
}