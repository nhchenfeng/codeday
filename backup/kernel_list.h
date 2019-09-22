#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)


#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) (type *)( (char *)ptr - offsetof(type,member) )

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline int list_empty(const struct list_head *head)
{
        return head->next == head;
}

static inline void __list_add(struct list_head *_new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = _new;
	_new->next = next;
	_new->prev = prev;
	prev->next = _new;
}

static inline void list_add(struct list_head *_new, struct list_head *head)
{
	__list_add(_new, head, head->next);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

static inline void
list_add_tail(struct list_head *entry, struct list_head *head)
{
    __list_add(entry, head->prev, head);
}

static int list_insert(struct list_head *entry, struct list_head *head)
{
	struct list_head *curr, *next;
	list_for_each_safe(curr, next, head) {
		if (entry == curr) {
			printf("already insert");
			return -1;
		}
	}
	list_add_tail(entry, head);
	return 0;
}

static inline struct list_head *
list_remove(struct list_head *head)
{
	struct list_head *tmp = head->next;
	if (!list_empty(head)) {
		list_del(tmp);
		return tmp;
	}
	return NULL;
}

static int list_push(struct list_head *entry, struct list_head *head)
{
	struct list_head *curr, *next;
	list_for_each_safe(curr, next, head) {
		if (entry == curr) {
			printf("alread insert");
			return -1;
		}
	}
	list_add(entry, head);
	return 0;
}

static inline struct list_head *
list_pop(struct list_head *head)
{
	struct list_head *tmp = head->next;
	if (!list_empty(head)) {
		list_del(tmp);
		return tmp;
	}
	return NULL;
}

static inline void list_replace(struct list_head *old,
                                struct list_head *_new)
{
        _new->next = old->next;
        _new->next->prev = _new;
        _new->prev = old->prev;
        _new->prev->next = _new;
}
