#include "sort.h"

static void *list_merge(void *left, void *right,
	t_list_get_next get_next, t_list_set_next set_next,
	t_list_set_prev set_prev, t_list_cmp cmp, void *ctx)
{
	void *head;
	void *tail;
	void *next;

	if (left == NULL)
		return (right);
	if (right == NULL)
		return (left);
	if (cmp(left, right, ctx) <= 0)
	{
		head = left;
		left = get_next(left);
	}
	else
	{
		head = right;
		right = get_next(right);
	}
	set_prev(head, NULL);
	tail = head;
	while (left != NULL && right != NULL)
	{
		if (cmp(left, right, ctx) <= 0)
		{
			next = left;
			left = get_next(left);
		}
		else
		{
			next = right;
			right = get_next(right);
		}
		set_next(tail, next);
		set_prev(next, tail);
		tail = next;
	}
	next = (left != NULL) ? left : right;
	set_next(tail, next);
	if (next != NULL)
		set_prev(next, tail);
	return (head);
}

static void *list_split(void *list, t_list_get_next get_next,
	t_list_set_next set_next, t_list_set_prev set_prev)
{
	void *slow;
	void *fast;
	void *mid;

	slow = list;
	fast = get_next(list);
	while (fast != NULL && get_next(fast) != NULL)
	{
		slow = get_next(slow);
		fast = get_next(get_next(fast));
	}
	mid = get_next(slow);
	set_next(slow, NULL);
	if (mid != NULL)
		set_prev(mid, NULL);
	return (mid);
}

static void *list_merge_sort_rec(void *list,
	t_list_get_next get_next, t_list_set_next set_next,
	t_list_get_prev get_prev, t_list_set_prev set_prev,
	t_list_cmp cmp, void *ctx, int limit_depth)
{
	void *right;
	void *left_sorted;
	void *right_sorted;

	if (list == NULL || get_next(list) == NULL)
		return (list);
	if (limit_depth <= 0)
		return (list_insert_sort(list, get_next, set_next,
				get_prev, set_prev, cmp, ctx));
	right = list_split(list, get_next, set_next, set_prev);
	left_sorted = list_merge_sort_rec(list, get_next, set_next,
			get_prev, set_prev, cmp, ctx, limit_depth - 1);
	right_sorted = list_merge_sort_rec(right, get_next, set_next,
			get_prev, set_prev, cmp, ctx, limit_depth - 1);
	return (list_merge(left_sorted, right_sorted, get_next, set_next,
			set_prev, cmp, ctx));
}

void *list_merge_sort(void *list,
	t_list_get_next get_next, t_list_set_next set_next,
	t_list_get_prev get_prev, t_list_set_prev set_prev,
	t_list_cmp cmp, void *ctx, int limit_depth)
{
	return (list_merge_sort_rec(list, get_next, set_next,
			get_prev, set_prev, cmp, ctx, limit_depth));
}
