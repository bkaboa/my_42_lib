#include "optLib/optlib.h"
#include "test_assert.h"

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	int		verbose;
	int		count;
	char	*value;
	char	*file;
} t_ctx;

static int set_verbose(const char *arg, void *obj)
{
	(void)arg;
	((t_ctx *)obj)->verbose = 1;
	return (OPT_SUCCESS);
}

static int set_value(const char *arg, void *obj)
{
	((t_ctx *)obj)->value = (char *)arg;
	return (OPT_SUCCESS);
}

static int set_file(const char *arg, void *obj)
{
	((t_ctx *)obj)->file = (char *)arg;
	return (OPT_SUCCESS);
}

static int count_empty(const char *arg, void *obj)
{
	(void)arg;
	((t_ctx *)obj)->count++;
	return (OPT_SUCCESS);
}

static int fail_cb(const char *arg, void *obj)
{
	(void)arg;
	(void)obj;
	return (OPT_ERROR);
}

static void init_opts(t_opt_list *opts)
{
	memset(opts, 0, sizeof(*opts));
}

static void silence_stderr(int *saved)
{
	int	devnull;

	*saved = dup(STDERR_FILENO);
	devnull = open("/dev/null", O_WRONLY);
	if (devnull >= 0) {
		dup2(devnull, STDERR_FILENO);
		close(devnull);
	}
}

static void restore_stderr(int saved)
{
	if (saved >= 0) {
		dup2(saved, STDERR_FILENO);
		close(saved);
	}
}

int main(void)
{
	t_opt_list	opts;
	t_ctx		ctx;
	const char	*argv[8];
	int			saved_stderr;

	TEST_CASE("opt_set_main / opt_add_new / opt_empty");
	init_opts(&opts);
	ASSERT_EQ_INT(OPT_SUCCESS, opt_set_main(&opts, "test prog", set_file));
	ASSERT_EQ_INT(OPT_SUCCESS, opt_add_new('v', "verbose", "enable verbose",
		false, set_verbose, false, &opts));
	ASSERT_EQ_INT(OPT_SUCCESS, opt_add_new('o', "output", "output file",
		false, set_value, true, &opts));
	ASSERT_EQ_INT(OPT_SUCCESS, opt_empty(&opts, "extra files", count_empty));
	ASSERT_NOT_NULL(opts.head);
	ASSERT_EQ_INT('v', opts.head->short_opt);
	ASSERT_EQ_STR("verbose", opts.head->long_opt);
	ASSERT_NOT_NULL(opts.head->next);
	ASSERT_EQ_INT('o', opts.head->next->short_opt);
	ASSERT_NOT_NULL(opts.by_short[(unsigned char)'v']);
	ASSERT_NOT_NULL(opts.by_short[(unsigned char)'o']);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt null argv");
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	ASSERT_EQ_INT(OPT_ERROR, ft_getopt(NULL, 1, &opts, NULL));

	TEST_CASE("ft_getopt short flag");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "-v";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 2, &opts, &ctx));
	ASSERT_EQ_INT(1, ctx.verbose);
	ASSERT_EQ_INT(1, opts.head->is_set);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt long flag");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "--verbose";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 2, &opts, &ctx));
	ASSERT_EQ_INT(1, ctx.verbose);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt short option with argument");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('o', "output", "output", false, set_value, true, &opts);
	argv[0] = "prog";
	argv[1] = "-o";
	argv[2] = "out.txt";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 3, &opts, &ctx));
	ASSERT_EQ_STR("out.txt", ctx.value);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt long option with argument");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('o', "output", "output", false, set_value, true, &opts);
	argv[0] = "prog";
	argv[1] = "--output";
	argv[2] = "file.bin";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 3, &opts, &ctx));
	ASSERT_EQ_STR("file.bin", ctx.value);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt long option with = argument");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('o', "output", "output", false, set_value, true, &opts);
	argv[0] = "prog";
	argv[1] = "--output=file.bin";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 2, &opts, &ctx));
	ASSERT_EQ_STR("file.bin", ctx.value);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt short cluster");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	opt_add_new('a', "all", "all", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "-va";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 2, &opts, &ctx));
	ASSERT_EQ_INT(1, ctx.verbose);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt main positional argument");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", set_file);
	argv[0] = "prog";
	argv[1] = "input.elf";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 2, &opts, &ctx));
	ASSERT_EQ_STR("input.elf", ctx.file);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt empty option arguments");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", set_file);
	opt_empty(&opts, "extra", count_empty);
	argv[0] = "prog";
	argv[1] = "first";
	argv[2] = "second";
	argv[3] = "third";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 4, &opts, &ctx));
	ASSERT_EQ_STR("first", ctx.file);
	ASSERT_EQ_INT(2, ctx.count);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt end of options --");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", set_file);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "--";
	argv[2] = "-v";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 3, &opts, &ctx));
	ASSERT_EQ_STR("-v", ctx.file);
	ASSERT_EQ_INT(0, ctx.verbose);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt exact long match rejects overlong prefix");
	silence_stderr(&saved_stderr);
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "--verbosex";
	ASSERT_EQ_INT(OPT_ERROR, ft_getopt(argv, 2, &opts, &ctx));
	ASSERT_EQ_INT(0, ctx.verbose);
	restore_stderr(saved_stderr);

	TEST_CASE("ft_getopt unambiguous long prefix");
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "--verb";
	ASSERT_EQ_INT(OPT_SUCCESS, ft_getopt(argv, 2, &opts, &ctx));
	ASSERT_EQ_INT(1, ctx.verbose);
	opt_destroy(&opts);

	TEST_CASE("ft_getopt ambiguous long prefix");
	silence_stderr(&saved_stderr);
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('a', "verbose", "verbose", false, set_verbose, false, &opts);
	opt_add_new('b', "version", "version", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "--ver";
	ASSERT_EQ_INT(OPT_ERROR, ft_getopt(argv, 2, &opts, &ctx));
	restore_stderr(saved_stderr);

	TEST_CASE("ft_getopt required option missing");
	silence_stderr(&saved_stderr);
	memset(&ctx, 0, sizeof(ctx));
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('o', "output", "output", true, set_value, true, &opts);
	argv[0] = "prog";
	argv[1] = "-v";
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	ASSERT_EQ_INT(OPT_ERROR, ft_getopt(argv, 2, &opts, &ctx));
	restore_stderr(saved_stderr);

	TEST_CASE("ft_getopt invalid option");
	silence_stderr(&saved_stderr);
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "-z";
	ASSERT_EQ_INT(OPT_ERROR, ft_getopt(argv, 2, &opts, &ctx));
	restore_stderr(saved_stderr);

	TEST_CASE("ft_getopt help short");
	silence_stderr(&saved_stderr);
	init_opts(&opts);
	opt_set_main(&opts, "prog help", NULL);
	opt_add_help(&opts);
	opt_add_new('v', "verbose", "verbose", false, set_verbose, false, &opts);
	argv[0] = "prog";
	argv[1] = "-h";
	ASSERT_EQ_INT(OPT_HELP, ft_getopt(argv, 2, &opts, &ctx));
	restore_stderr(saved_stderr);

	TEST_CASE("ft_getopt help long");
	silence_stderr(&saved_stderr);
	init_opts(&opts);
	opt_set_main(&opts, "prog help", NULL);
	opt_add_help(&opts);
	argv[0] = "prog";
	argv[1] = "--help";
	ASSERT_EQ_INT(OPT_HELP, ft_getopt(argv, 2, &opts, &ctx));
	restore_stderr(saved_stderr);

	TEST_CASE("ft_getopt callback error");
	silence_stderr(&saved_stderr);
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('f', "fail", "fail", false, fail_cb, false, &opts);
	argv[0] = "prog";
	argv[1] = "-f";
	ASSERT_EQ_INT(OPT_ERROR, ft_getopt(argv, 2, &opts, &ctx));
	restore_stderr(saved_stderr);

	TEST_CASE("ft_getopt missing argument");
	silence_stderr(&saved_stderr);
	init_opts(&opts);
	opt_set_main(&opts, "prog", NULL);
	opt_add_new('o', "output", "output", false, set_value, true, &opts);
	argv[0] = "prog";
	argv[1] = "-o";
	ASSERT_EQ_INT(OPT_ERROR, ft_getopt(argv, 2, &opts, &ctx));
	restore_stderr(saved_stderr);

	return test_report("test_optlib");
}
