#include "sort.h"

void *list_insert_sort(void *list,
	t_list_get_next get_next, t_list_set_next set_next,
	t_list_get_prev get_prev, t_list_set_prev set_prev,
	t_list_cmp cmp, void *ctx)
{
	void *sorted;
	void *current;
	void *next;
	void *pos;

	(void)get_prev;
	if (list == NULL || get_next(list) == NULL)
		return (list);
	sorted = NULL;
	current = list;
	while (current != NULL)
	{
		next = get_next(current);
		set_next(current, NULL);
		set_prev(current, NULL);
		if (sorted == NULL
			|| cmp(current, sorted, ctx) < 0)
		{
			set_next(current, sorted);
			if (sorted != NULL)
				set_prev(sorted, current);
			sorted = current;
		}
		else
		{
			pos = sorted;
			while (get_next(pos) != NULL
				&& cmp(current, get_next(pos), ctx) >= 0)
				pos = get_next(pos);
			set_next(current, get_next(pos));
			if (get_next(pos) != NULL)
				set_prev(get_next(pos), current);
			set_next(pos, current);
			set_prev(current, pos);
		}
		current = next;
	}
	return (sorted);
}
