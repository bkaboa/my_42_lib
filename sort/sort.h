#ifndef SORT_H
#define SORT_H

#include <stddef.h>
#include <stdbool.h>

typedef void *(*t_list_get_next)(void *node);
typedef void *(*t_list_get_prev)(void *node);
typedef void (*t_list_set_next)(void *node, void *next);
typedef void (*t_list_set_prev)(void *node, void *prev);
typedef int (*t_list_cmp)(void *node1, void *node2, void *ctx);

void *list_merge_sort(void *list,
	t_list_get_next get_next, t_list_set_next set_next,
	t_list_get_prev get_prev, t_list_set_prev set_prev,
	t_list_cmp cmp, void *ctx, int limit_depth);

void *list_insert_sort(void *list,
	t_list_get_next get_next, t_list_set_next set_next,
	t_list_get_prev get_prev, t_list_set_prev set_prev,
	t_list_cmp cmp, void *ctx);

#endif
