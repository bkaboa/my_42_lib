#include "libft.h"
#include "test_assert.h"

int main(void)
{
	TEST_CASE("ft_isdigit");
	ASSERT_TRUE(ft_isdigit('0'));
	ASSERT_TRUE(ft_isdigit('9'));
	ASSERT_FALSE(ft_isdigit('a'));
	ASSERT_FALSE(ft_isdigit('/'));
	ASSERT_FALSE(ft_isdigit(':'));

	TEST_CASE("ft_isalpha");
	ASSERT_TRUE(ft_isalpha('a'));
	ASSERT_TRUE(ft_isalpha('Z'));
	ASSERT_FALSE(ft_isalpha('5'));
	ASSERT_FALSE(ft_isalpha(' '));

	TEST_CASE("ft_isalnum");
	ASSERT_TRUE(ft_isalnum('a'));
	ASSERT_TRUE(ft_isalnum('7'));
	ASSERT_FALSE(ft_isalnum('_'));

	TEST_CASE("ft_isascii");
	ASSERT_TRUE(ft_isascii(0));
	ASSERT_TRUE(ft_isascii(127));
	ASSERT_FALSE(ft_isascii(128));
	ASSERT_FALSE(ft_isascii(-1));

	TEST_CASE("ft_isprint");
	ASSERT_TRUE(ft_isprint(' '));
	ASSERT_TRUE(ft_isprint('~'));
	ASSERT_FALSE(ft_isprint(31));
	ASSERT_FALSE(ft_isprint(127));

	TEST_CASE("ft_isspace");
	ASSERT_TRUE(ft_isspace(' '));
	ASSERT_TRUE(ft_isspace('\t'));
	ASSERT_TRUE(ft_isspace('\n'));
	ASSERT_FALSE(ft_isspace('a'));

	TEST_CASE("ft_islower / ft_isupper");
	ASSERT_TRUE(ft_islower('z'));
	ASSERT_FALSE(ft_islower('Z'));
	ASSERT_TRUE(ft_isupper('A'));
	ASSERT_FALSE(ft_isupper('a'));

	TEST_CASE("ft_isblank");
	ASSERT_TRUE(ft_isblank(' '));
	ASSERT_TRUE(ft_isblank('\t'));
	ASSERT_FALSE(ft_isblank('\n'));

	TEST_CASE("ft_iscntrl");
	ASSERT_TRUE(ft_iscntrl(0));
	ASSERT_TRUE(ft_iscntrl(31));
	ASSERT_FALSE(ft_iscntrl('A'));

	TEST_CASE("ft_isgraph");
	ASSERT_TRUE(ft_isgraph('!'));
	ASSERT_FALSE(ft_isgraph(' '));

	TEST_CASE("ft_ispunct");
	ASSERT_TRUE(ft_ispunct('!'));
	ASSERT_TRUE(ft_ispunct('@'));
	ASSERT_FALSE(ft_ispunct('A'));
	ASSERT_FALSE(ft_ispunct('1'));

	TEST_CASE("ft_isnumber");
	ASSERT_TRUE(ft_isnumber("42"));
	ASSERT_TRUE(ft_isnumber("-42"));
	ASSERT_TRUE(ft_isnumber("+7"));
	ASSERT_FALSE(ft_isnumber("-"));
	ASSERT_FALSE(ft_isnumber("12a"));
	ASSERT_FALSE(ft_isnumber(NULL));

	TEST_CASE("ft_ishex");
	ASSERT_TRUE(ft_ishex("deadbeef"));
	ASSERT_TRUE(ft_ishex("0xFF"));
	ASSERT_TRUE(ft_ishex("0Xabc"));
	ASSERT_FALSE(ft_ishex(""));
	ASSERT_FALSE(ft_ishex("xyz"));
	ASSERT_FALSE(ft_ishex(NULL));

	TEST_CASE("ft_isdecimal");
	ASSERT_TRUE(ft_isdecimal("3.14"));
	ASSERT_TRUE(ft_isdecimal("1.0e10"));
	ASSERT_FALSE(ft_isdecimal("42"));
	ASSERT_FALSE(ft_isdecimal("1.2.3"));
	ASSERT_FALSE(ft_isdecimal(NULL));

	return test_report("test_ft_is");
}
