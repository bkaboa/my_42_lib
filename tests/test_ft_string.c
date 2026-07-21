#include "libft.h"
#include "test_assert.h"

int main(void)
{
	char	buf[64];
	char	*dup;

	TEST_CASE("ft_strlen");
	ASSERT_EQ_SIZE(0, ft_strlen(""));
	ASSERT_EQ_SIZE(5, ft_strlen("hello"));
	ASSERT_EQ_SIZE(0, ft_strlen(NULL));

	TEST_CASE("ft_strcmp");
	ASSERT_EQ_INT(0, ft_strcmp("abc", "abc"));
	ASSERT_SIGN(-1, ft_strcmp("abc", "abd"));
	ASSERT_SIGN(1, ft_strcmp("abd", "abc"));
	ASSERT_EQ_INT(0, ft_strcmp(NULL, NULL));
	ASSERT_EQ_INT(-1, ft_strcmp(NULL, "a"));
	ASSERT_EQ_INT(-1, ft_strcmp("a", NULL));

	TEST_CASE("ft_strncmp");
	ASSERT_EQ_INT(0, ft_strncmp("abc", "abc", 3));
	ASSERT_SIGN(-1, ft_strncmp("abc", "abd", 3));
	ASSERT_SIGN(1, ft_strncmp("abd", "abc", 3));

	TEST_CASE("ft_strlowercasecmp");
	ASSERT_EQ_INT(0, ft_strlowercasecmp("AbC", "aBc"));
	ASSERT_SIGN(-1, ft_strlowercasecmp("abc", "abd"));

	TEST_CASE("ft_struppercasecmp");
	ASSERT_EQ_INT(0, ft_struppercasecmp("AbC", "aBc"));
	ASSERT_SIGN(1, ft_struppercasecmp("ABD", "abc"));

	TEST_CASE("ft_strcat");
	buf[0] = '\0';
	ASSERT_EQ_INT(0, ft_strcat(buf, "hello"));
	ASSERT_EQ_STR("hello", buf);
	ASSERT_EQ_INT(0, ft_strcat(buf, " world"));
	ASSERT_EQ_STR("hello world", buf);
	ASSERT_EQ_INT(-1, ft_strcat(NULL, "x"));
	ASSERT_EQ_INT(-1, ft_strcat(buf, NULL));

	TEST_CASE("ft_strncat");
	buf[0] = 'h';
	buf[1] = 'i';
	buf[2] = '\0';
	ASSERT_EQ_INT(0, ft_strncat(buf, " there!!!", 6));
	ASSERT_EQ_STR("hi there", buf);

	TEST_CASE("ft_strdup");
	ASSERT_EQ_INT(0, ft_strdup(&dup, "libft"));
	ASSERT_NOT_NULL(dup);
	ASSERT_EQ_STR("libft", dup);
	free(dup);

	TEST_CASE("ft_strndup");
	ASSERT_EQ_INT(0, ft_strndup(&dup, "abcdef", 3));
	ASSERT_EQ_STR("abc", dup);
	free(dup);

	TEST_CASE("ft_strjoin");
	dup = ft_strjoin("foo", "bar");
	ASSERT_NOT_NULL(dup);
	ASSERT_EQ_STR("foobar", dup);
	free(dup);
	dup = ft_strjoin("", "x");
	ASSERT_EQ_STR("x", dup);
	free(dup);

	TEST_CASE("ft_strncpy");
	ft_memset(buf, 0, sizeof(buf));
	ASSERT_EQ_INT(5, ft_strncpy(buf, "hello", 5));
	ASSERT_EQ_STR("hello", buf);
	ASSERT_EQ_INT(-1, ft_strncpy(NULL, "x", 1));
	ASSERT_EQ_INT(-1, ft_strncpy(buf, NULL, 1));
	ft_strncpy(buf, "ceci est un test long pour regarder si la copi SIMD marche correctement", 100);
	ASSERT_EQ_STR("ceci est un test long pour regarder si la copi SIMD marche correctement", buf);

	TEST_CASE("ft_strchr");
	ASSERT_EQ_STR("llo", ft_strchr("hello", 'l'));
	ASSERT_NULL(ft_strchr("hello", 'z'));
	ASSERT_EQ_STR("", ft_strchr("hello", '\0'));

	TEST_CASE("ft_numlen");
	ASSERT_EQ_INT(1, ft_numlen(1));
	ASSERT_EQ_INT(2, ft_numlen(42));
	ASSERT_EQ_INT(3, ft_numlen(100));
	ASSERT_EQ_INT(3, ft_numlen(-42));

	return test_report("test_ft_string");
}
