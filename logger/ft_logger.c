#include "ft_logger.h"

static Logger *logger;

static const char *LOG_LEVELS_MSG[] = {
    "INFO    : ",
    "WARNING : ",
    "ERROR   : ",
    "DEBUG   : "
};

/**
 * @brief 
 * 
 * @param log_level 
 * @param prefix 
 * @param msg 
 * @param ... 
 * 
 * log function buffer limit is 1024 bytes
 */
static void logger_func(const u_int8_t log_level, const bool prefix, const char *__restrict __format, ...) __attribute__((format (printf, 3, 4)));

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

/** 
 * @brief 
 * 
 * @param log_level 
 * @param prefix 
 * @param msg 
 * @param ... 
 * 
 * log function buffer limit is 1024 bytes
 * 
 * the prefix is used to add the log level to the message (e.g INFO, WARNING, ERROR, DEBUG)
 */
static void logger_func(const u_int8_t log_level, const bool prefix, const char *msg, ...)
{
    char format[1024] = {0};

    va_list args;
    va_start(args, msg);
    vsprintf(format, msg, args);
    va_end(args);
    #ifdef FILE_LOG
        fprintf(logger->file, "%s%s%s", LOG_LEVELS_MSG[log_level], format, COLOR_RESET);
    #endif
    if (prefix)
        dprintf(LOG_STD(log_level), "%s%s%s%s", COLOR_MSG(log_level), LOG_LEVELS_MSG[log_level], format, COLOR_RESET);
    else
        dprintf(LOG_STD(log_level), "%s%s%s", COLOR_MSG(log_level), format, COLOR_RESET);
}
