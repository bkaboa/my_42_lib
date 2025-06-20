#include "ft_logger.h"
#include "libft.h"

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
            #ifdef WRITE_LOG
                logger->u_logger.fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (logger->u_logger.fd < 0)
                {
                    perror("Failed to open log file");
                    exit(EXIT_FAILURE);
                }
            #else
                logger->u_logger.file = fopen("log.txt", "a");
                if (logger->u_logger.file == NULL)
                {
                    perror("Failed to open log file");
                    exit(EXIT_FAILURE);
                }
            #endif
        #endif
        logger->log = &logger_func;
    }
    return logger;
}

void logger_destructor()
{
    if (logger)
    {
        #ifdef FILE_LOG
            #ifdef WRITE_LOG
                close(logger->u_logger.fd);
            #else
                fclose(logger->u_logger.file);
            #endif
        #endif
        free(logger);
        logger = NULL;
    }
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
#if defined (WRITE_LOG)
    static void logger_func(const u_int8_t log_level, const bool prefix, const char *__restrict __format, ...)
    {
        char format[1024] = {0};
        unsigned long last_percent = 0;

        va_list args;
        va_start(args, __format);
        if (prefix)
        {
            ft_strcat(format, LOG_LEVELS_MSG[log_level]);
        }
        for (int i = 0; __format[i] && i < (int)sizeof(format); i++)
        {
            if (__format[i] == '%')
            {
                ft_strncat(format, __format + last_percent, i - last_percent);
                last_percent = i;
                i += 1; // skip the '%'
                if (__format[i] == '\0')
                    break;
                else if (__format[i] == 's')
                {
                    const char *str_arg = va_arg(args, const char *);
                    ft_strcat(format, str_arg);
                }
                else if (__format[i] == 'd' || __format[i] == 'i' || __format[i] == 'u' || (__format[i] == 'l' && __format[i + 1] == 'd'))
                {
                    int int_arg = va_arg(args, int);
                    char *str_arg = ft_itoa(int_arg);
                    ft_strcat(format, str_arg);
                    free(str_arg);
                }
                else if (__format[i] == '%')
                {
                    ft_strcat(format, "%");
                }
                else if (__format[i] == 'c')
                {
                    char arg = (char)va_arg(args, int);
                    char str_arg[2] = {arg, '\0'};
                    ft_strcat(format, str_arg);
                }
                last_percent = i + 1;
            }
        }
        ft_strcat(format, __format + last_percent);
        va_end(args);
        write(LOG_STD(log_level), COLOR_MSG(log_level), ft_strlen(COLOR_MSG(log_level)));
        write(LOG_STD(log_level), format, ft_strlen(format));
        write(LOG_STD(log_level), COLOR_RESET, ft_strlen(COLOR_RESET));
        #ifdef FILE_LOG
            write(logger->u_logger.fd, COLOR_MSG(log_level), ft_strlen(COLOR_MSG(log_level)));
            write(logger->u_logger.fd, format, ft_strlen(format));
            write(logger->u_logger.fd, COLOR_RESET, ft_strlen(COLOR_RESET));
        #endif
    }
#else
    static void logger_func(const u_int8_t log_level, const bool prefix, const char *__restrict __format, ...)
    {
        char format[1024] = {0};

        va_list args;
        va_start(args, __format);
        vsnprintf(format, sizeof(format), __format, args);
        va_end(args);
        #ifdef FILE_LOG
            fprintf(logger->u_logger.file, "%s%s%s", LOG_LEVELS_MSG[log_level], format, COLOR_RESET);
        #endif
        if (prefix)
            dprintf(LOG_STD(log_level), "%s%s%s%s", COLOR_MSG(log_level), LOG_LEVELS_MSG[log_level], format, COLOR_RESET);
        else
            dprintf(LOG_STD(log_level), "%s%s%s", COLOR_MSG(log_level), format, COLOR_RESET);
    }
#endif