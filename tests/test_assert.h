#ifndef TEST_ASSERT_H
# define TEST_ASSERT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

static int g_test_failures = 0;
static int g_test_count = 0;

# define TEST_CASE(name) \
	do { \
		g_test_count++; \
		fprintf(stderr, "  RUN  %s\n", name); \
	} while (0)

# define ASSERT_TRUE(cond) \
	do { \
		if (!(cond)) { \
			fprintf(stderr, "    FAIL %s:%d: expected true: %s\n", \
				__FILE__, __LINE__, #cond); \
			g_test_failures++; \
		} \
	} while (0)

# define ASSERT_FALSE(cond) \
	do { \
		if (cond) { \
			fprintf(stderr, "    FAIL %s:%d: expected false: %s\n", \
				__FILE__, __LINE__, #cond); \
			g_test_failures++; \
		} \
	} while (0)

# define ASSERT_EQ_INT(expected, actual) \
	do { \
		long long _e = (long long)(expected); \
		long long _a = (long long)(actual); \
		if (_e != _a) { \
			fprintf(stderr, "    FAIL %s:%d: expected %lld, got %lld (%s)\n", \
				__FILE__, __LINE__, _e, _a, #actual); \
			g_test_failures++; \
		} \
	} while (0)

# define ASSERT_EQ_SIZE(expected, actual) \
	do { \
		size_t _e = (size_t)(expected); \
		size_t _a = (size_t)(actual); \
		if (_e != _a) { \
			fprintf(stderr, "    FAIL %s:%d: expected %zu, got %zu (%s)\n", \
				__FILE__, __LINE__, _e, _a, #actual); \
			g_test_failures++; \
		} \
	} while (0)

# define ASSERT_EQ_STR(expected, actual) \
	do { \
		const char *_e = (expected); \
		const char *_a = (actual); \
		if ((_e == NULL && _a != NULL) || (_e != NULL && _a == NULL) \
			|| (_e && _a && strcmp(_e, _a) != 0)) { \
			fprintf(stderr, "    FAIL %s:%d: expected \"%s\", got \"%s\" (%s)\n", \
				__FILE__, __LINE__, \
				_e ? _e : "(null)", _a ? _a : "(null)", #actual); \
			g_test_failures++; \
		} \
	} while (0)

# define ASSERT_NULL(ptr) \
	do { \
		if ((ptr) != NULL) { \
			fprintf(stderr, "    FAIL %s:%d: expected NULL: %s\n", \
				__FILE__, __LINE__, #ptr); \
			g_test_failures++; \
		} \
	} while (0)

# define ASSERT_NOT_NULL(ptr) \
	do { \
		if ((ptr) == NULL) { \
			fprintf(stderr, "    FAIL %s:%d: expected non-NULL: %s\n", \
				__FILE__, __LINE__, #ptr); \
			g_test_failures++; \
		} \
	} while (0)

# define ASSERT_SIGN(expected_sign, actual) \
	do { \
		int _a = (actual); \
		int _s = ((_a) > 0) - ((_a) < 0); \
		if (_s != (expected_sign)) { \
			fprintf(stderr, "    FAIL %s:%d: expected sign %d, got %d (%s)\n", \
				__FILE__, __LINE__, (int)(expected_sign), _a, #actual); \
			g_test_failures++; \
		} \
	} while (0)

static inline int test_report(const char *suite)
{
	if (g_test_failures == 0) {
		fprintf(stderr, "OK   %s (%d tests)\n", suite, g_test_count);
		return 0;
	}
	fprintf(stderr, "FAIL %s (%d/%d failed)\n",
		suite, g_test_failures, g_test_count);
	return 1;
}

#endif
