#include "gnl/ft_gnl.h"
#include "test_assert.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int make_pipe_with_content(const char *content)
{
	int	fds[2];

	if (pipe(fds) < 0)
		return (-1);
	if (write(fds[1], content, strlen(content)) < 0) {
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	close(fds[1]);
	return (fds[0]);
}

int main(void)
{
	char	*line;
	int		fd;
	char	path[] = "/tmp/ft_gnl_test_XXXXXX";
	int		tmp;

	TEST_CASE("ft_gnl invalid arguments");
	ASSERT_EQ_INT(-1, ft_gnl(-1, &line));
	ASSERT_EQ_INT(-1, ft_gnl(0, NULL));

	TEST_CASE("ft_gnl empty input");
	fd = make_pipe_with_content("");
	ASSERT_TRUE(fd >= 0);
	ASSERT_EQ_INT(0, ft_gnl(fd, &line));
	ASSERT_NULL(line);
	close(fd);

	TEST_CASE("ft_gnl single line with newline");
	fd = make_pipe_with_content("hello\n");
	ASSERT_TRUE(fd >= 0);
	ASSERT_EQ_INT(1, ft_gnl(fd, &line));
	ASSERT_EQ_STR("hello\n", line);
	free(line);
	ASSERT_EQ_INT(0, ft_gnl(fd, &line));
	if (line != NULL) {
		ASSERT_EQ_STR("", line);
		free(line);
	}
	close(fd);

	TEST_CASE("ft_gnl multiple lines");
	fd = make_pipe_with_content("one\ntwo\nthree\n");
	ASSERT_TRUE(fd >= 0);
	ASSERT_EQ_INT(1, ft_gnl(fd, &line));
	ASSERT_EQ_STR("one\n", line);
	free(line);
	ASSERT_EQ_INT(1, ft_gnl(fd, &line));
	ASSERT_EQ_STR("two\n", line);
	free(line);
	ASSERT_EQ_INT(1, ft_gnl(fd, &line));
	ASSERT_EQ_STR("three\n", line);
	free(line);
	ASSERT_EQ_INT(0, ft_gnl(fd, &line));
	if (line != NULL) {
		ASSERT_EQ_STR("", line);
		free(line);
	}
	close(fd);

	TEST_CASE("ft_gnl last line without newline");
	fd = make_pipe_with_content("no-newline");
	ASSERT_TRUE(fd >= 0);
	ASSERT_EQ_INT(0, ft_gnl(fd, &line));
	ASSERT_EQ_STR("no-newline", line);
	free(line);
	close(fd);

	TEST_CASE("ft_gnl mixed ending");
	fd = make_pipe_with_content("first\nsecond");
	ASSERT_TRUE(fd >= 0);
	ASSERT_EQ_INT(1, ft_gnl(fd, &line));
	ASSERT_EQ_STR("first\n", line);
	free(line);
	ASSERT_EQ_INT(0, ft_gnl(fd, &line));
	ASSERT_EQ_STR("second", line);
	free(line);
	close(fd);

	TEST_CASE("ft_gnl from temp file");
	tmp = mkstemp(path);
	ASSERT_TRUE(tmp >= 0);
	ASSERT_TRUE(write(tmp, "a\nb\n", 4) == 4);
	close(tmp);
	fd = open(path, O_RDONLY);
	ASSERT_TRUE(fd >= 0);
	ASSERT_EQ_INT(1, ft_gnl(fd, &line));
	ASSERT_EQ_STR("a\n", line);
	free(line);
	ASSERT_EQ_INT(1, ft_gnl(fd, &line));
	ASSERT_EQ_STR("b\n", line);
	free(line);
	ASSERT_EQ_INT(0, ft_gnl(fd, &line));
	if (line != NULL) {
		ASSERT_EQ_STR("", line);
		free(line);
	}
	close(fd);
	unlink(path);

	TEST_CASE("ft_gnl long line spanning buffers");
	{
		char	big[BUFFER_SIZE * 2 + 16];
		size_t	i;

		memset(big, 'x', BUFFER_SIZE * 2);
		big[BUFFER_SIZE * 2] = '\n';
		big[BUFFER_SIZE * 2 + 1] = '\0';
		fd = make_pipe_with_content(big);
		ASSERT_TRUE(fd >= 0);
		ASSERT_EQ_INT(1, ft_gnl(fd, &line));
		ASSERT_NOT_NULL(line);
		ASSERT_EQ_SIZE(BUFFER_SIZE * 2 + 1, strlen(line));
		ASSERT_EQ_INT('\n', line[BUFFER_SIZE * 2]);
		for (i = 0; i < BUFFER_SIZE * 2; i++)
			ASSERT_EQ_INT('x', line[i]);
		free(line);
		close(fd);
	}

	return test_report("test_gnl");
}
