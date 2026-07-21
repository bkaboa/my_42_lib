#include "libft.h"
#include "test_assert.h"

int main(void)
{
	unsigned char	a[16];
	unsigned char	b[16];
	void			*ptr;
	char			*str;

	TEST_CASE("ft_memset");
	ASSERT_EQ_INT(0, ft_memset(a, 0xAB, 8));
	for (int i = 0; i < 8; i++)
		ASSERT_EQ_INT(0xAB, a[i]);
	ASSERT_EQ_INT(-1, ft_memset(NULL, 0, 1));

	TEST_CASE("ft_memcpy");
	ASSERT_EQ_INT(0, ft_memcpy(b, "hello\0\0\0", 6));
	ASSERT_EQ_INT(0, ft_memcmp(b, "hello", 5));
	ASSERT_EQ_INT(-1, ft_memcpy(NULL, a, 1));
	ASSERT_EQ_INT(-1, ft_memcpy(a, NULL, 1));

	TEST_CASE("ft_memcmp");
	ASSERT_EQ_INT(0, ft_memcmp("abc", "abc", 3));
	ASSERT_SIGN(-1, ft_memcmp("abc", "abd", 3));
	ASSERT_SIGN(1, ft_memcmp("abd", "abc", 3));
	ASSERT_EQ_INT(0, ft_memcmp(NULL, NULL, 0));
	ASSERT_EQ_INT(-1, ft_memcmp(NULL, a, 1));

	TEST_CASE("ft_realloc grow");
	ptr = malloc(4);
	ASSERT_NOT_NULL(ptr);
	ft_memcpy(ptr, "hi\0", 3);
	ASSERT_EQ_INT(0, ft_realloc(&ptr, 16));
	ASSERT_NOT_NULL(ptr);
	ASSERT_EQ_INT(0, ft_memcmp(ptr, "hi", 2));
	free(ptr);

	TEST_CASE("ft_realloc free on size 0");
	str = malloc(8);
	ASSERT_NOT_NULL(str);
	ASSERT_EQ_INT(0, ft_realloc((void **)&str, 0));
	ASSERT_NULL(str);

	TEST_CASE("ft_realloc null ptr arg");
	ASSERT_EQ_INT(-1, ft_realloc(NULL, 8));

	return test_report("test_ft_memory");
}
