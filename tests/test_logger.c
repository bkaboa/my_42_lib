#include "logger/ft_logger.h"
#include "test_assert.h"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static int read_fd_all(int fd, char *buf, size_t size)
{
	ssize_t	n;
	size_t	total;

	total = 0;
	while (total + 1 < size) {
		n = read(fd, buf + total, size - 1 - total);
		if (n <= 0)
			break;
		total += (size_t)n;
	}
	buf[total] = '\0';
	return (int)total;
}

int main(void)
{
	Logger	*logger;
	Logger	*again;
	int		pipefd[2];
	int		saved_out;
	int		saved_err;
	char	buf[256];

	TEST_CASE("get_logger_instance singleton");
	logger = get_logger_instance();
	ASSERT_NOT_NULL(logger);
	ASSERT_TRUE(logger->initialized);
	ASSERT_NOT_NULL(logger->log);
	ASSERT_NOT_NULL(logger->destructor);
	again = get_logger_instance();
	ASSERT_TRUE(logger == again);

	TEST_CASE("log info with prefix to stdout");
	ASSERT_EQ_INT(0, pipe(pipefd));
	saved_out = dup(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	logger->log(E_LOG_INFO, true, "hello %s %d", "world", 42);
	fflush(stdout);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_out);
	read_fd_all(pipefd[0], buf, sizeof(buf));
	close(pipefd[0]);
	ASSERT_TRUE(strstr(buf, "INFO") != NULL);
	ASSERT_TRUE(strstr(buf, "hello world 42") != NULL);

	TEST_CASE("log info without prefix");
	ASSERT_EQ_INT(0, pipe(pipefd));
	saved_out = dup(STDOUT_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	logger->log(E_LOG_INFO, false, "plain message");
	fflush(stdout);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_out);
	read_fd_all(pipefd[0], buf, sizeof(buf));
	close(pipefd[0]);
	ASSERT_TRUE(strstr(buf, "plain message") != NULL);
	ASSERT_TRUE(strstr(buf, "INFO") == NULL);

	TEST_CASE("log error goes to stderr");
	ASSERT_EQ_INT(0, pipe(pipefd));
	saved_err = dup(STDERR_FILENO);
	dup2(pipefd[1], STDERR_FILENO);
	close(pipefd[1]);
	logger->log(E_LOG_ERROR, true, "boom");
	fflush(stderr);
	dup2(saved_err, STDERR_FILENO);
	close(saved_err);
	read_fd_all(pipefd[0], buf, sizeof(buf));
	close(pipefd[0]);
	ASSERT_TRUE(strstr(buf, "ERROR") != NULL);
	ASSERT_TRUE(strstr(buf, "boom") != NULL);

	TEST_CASE("log warning / debug / fatal do not crash");
	ASSERT_EQ_INT(0, pipe(pipefd));
	saved_out = dup(STDOUT_FILENO);
	saved_err = dup(STDERR_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(pipefd[1], STDERR_FILENO);
	close(pipefd[1]);
	logger->log(E_LOG_WARNING, true, "warn");
	logger->log(E_LOG_DEBUG, true, "dbg");
	logger->log(E_LOG_FATAL, false, "fatal");
	fflush(stdout);
	fflush(stderr);
	dup2(saved_out, STDOUT_FILENO);
	dup2(saved_err, STDERR_FILENO);
	close(saved_out);
	close(saved_err);
	read_fd_all(pipefd[0], buf, sizeof(buf));
	close(pipefd[0]);
	ASSERT_TRUE(strstr(buf, "warn") != NULL);
	ASSERT_TRUE(strstr(buf, "dbg") != NULL);
	ASSERT_TRUE(strstr(buf, "fatal") != NULL);

	TEST_CASE("destructor");
	logger->destructor(logger);

	return test_report("test_logger");
}
