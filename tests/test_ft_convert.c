#include "libft.h"
#include "test_assert.h"

int main(void)
{
	char	buf[32];
	char	*s;

	TEST_CASE("ft_atoi");
	ASSERT_EQ_INT(42, ft_atoi("42"));
	ASSERT_EQ_INT(-42, ft_atoi("-42"));
	ASSERT_EQ_INT(0, ft_atoi("0"));
	ASSERT_EQ_INT(-1, ft_atoi(NULL));

	TEST_CASE("ft_atol");
	ASSERT_EQ_INT(123456789L, ft_atol("123456789"));
	ASSERT_EQ_INT(-7L, ft_atol("-7"));

	TEST_CASE("ft_atoi_base");
	ASSERT_EQ_INT(255, ft_atoi_base("FF", 16));
	ASSERT_EQ_INT(10, ft_atoi_base("a", 16));
	ASSERT_EQ_INT(8, ft_atoi_base("10", 8));
	ASSERT_EQ_INT(-1, ft_atoi_base("G", 16));
	ASSERT_EQ_INT(-1, ft_atoi_base(NULL, 10));

	TEST_CASE("ft_itoa");
	s = ft_itoa(42);
	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR("42", s);
	free(s);
	s = ft_itoa(100);
	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR("100", s);
	free(s);

	TEST_CASE("ft_tolower / ft_toupper");
	ASSERT_EQ_INT('a', ft_tolower('A'));
	ASSERT_EQ_INT('z', ft_tolower('z'));
	ASSERT_EQ_INT('A', ft_toupper('a'));
	ASSERT_EQ_INT('Z', ft_toupper('Z'));

	TEST_CASE("ft_strToupper / ft_strTolower");
	ft_memcpy(buf, "Hello", 6);
	ASSERT_EQ_INT(0, ft_strToupper(buf));
	ASSERT_EQ_STR("HELLO", buf);
	ASSERT_EQ_INT(0, ft_strTolower(buf));
	ASSERT_EQ_STR("hello", buf);
	ASSERT_EQ_INT(-1, ft_strToupper(NULL));
	ASSERT_EQ_INT(-1, ft_strTolower(NULL));

	TEST_CASE("ft_toascii / ft_tochar");
	ASSERT_EQ_INT(0x7F, ft_toascii(0x1FF));
	ASSERT_EQ_INT(0xAB, ft_tochar(0x1AB));

	return test_report("test_ft_convert");
}
