/* hash table with doubly linked list
 * 84 ms
 * 65.69%
 * 5.84%
 */
#include <stdlib.h>

#define TABLESIZE 101


struct node {
	int key;
	int val;
	struct node *prev;  /* hash table list */
	struct node *next;
	struct node *older;  /* time queue */
	struct node *newer;
};
typedef struct node *kvpp;

kvpp tdeq(kvpp *oldest, kvpp *newest);
void tenq(kvpp *oldest, kvpp *newest, kvpp *pair);
kvpp makekvpp(int key, int val);
void tqfree(kvpp oldest);

typedef struct {
	kvpp *table;  /* hash table */
	kvpp oldest;  /* oldest element */
	kvpp newest;  /* newest element */
	int count;  /* number of elements */
	int cap;  /* capacity */
} LRUCache;

void time_update(LRUCache *obj, kvpp *pair, int val);

int hash(int key);
kvpp table_lookup(kvpp *table, int key);
void lru_ins(LRUCache *obj, kvpp *pair);
void lru_evict(LRUCache *obj);


LRUCache *
lRUCacheCreate(int capacity)
{
	LRUCache *lruc = (LRUCache *) malloc(sizeof(LRUCache));
	lruc->table = (kvpp *) calloc(TABLESIZE, sizeof(kvpp));
	lruc->oldest = NULL;
	lruc->newest = NULL;
	lruc->count = 0;
	lruc->cap = capacity;
	return lruc;
}

int
lRUCacheGet(LRUCache* obj, int key)
{
	kvpp pair = table_lookup(obj->table, key);
	if (pair) {
		time_update(obj, &pair, pair->val);
	}

	return pair ? pair->val : -1;
}

void
lRUCachePut(LRUCache* obj, int key, int value)
{
	kvpp pair = table_lookup(obj->table, key);
	if (pair) {
		pair->val = value;
		time_update(obj, &pair, value);
	} else {
		pair =  makekvpp(key, value);
		lru_ins(obj, &pair);
		if (obj->count > obj->cap) {
			(obj->count)--;
			lru_evict(obj);
		}
	}
}

void
lRUCacheFree(LRUCache* obj)
{
	tqfree(obj->oldest);
	free(obj->table);
	free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
 */

kvpp
tdeq(kvpp *oldest, kvpp *newest)
{
	kvpp pair = *oldest;
	if (*oldest != *newest) {
		 *oldest = (*oldest)->newer;
		(*oldest)->older = NULL;
	} else {
		 *oldest = *newest = NULL;
	}
	pair->older = NULL;
	pair->newer = NULL;
	return pair;
}

void
tenq(kvpp *oldest, kvpp *newest, kvpp *pair)
{
	(*pair)->older = NULL;
	(*pair)->newer = NULL;
	if (*oldest != *newest) {
		(*newest)->newer = *pair;
		(*pair)->older = *newest;
		 *newest = *pair;
	} else if (*oldest) {
		 *newest = *pair;
		(*oldest)->newer = *newest;
		(*newest)->older = *oldest;
	} else {
		 *oldest = *newest = *pair;
	}
}

kvpp
makekvpp(int key, int val)
{
	kvpp pair = (kvpp) malloc(sizeof(struct node));
	pair->key = key;
	pair->val = val;
	pair->prev = NULL;
	pair->next = NULL;
	pair->older = NULL;
	pair->newer = NULL;
	return pair;
}

void
tqfree(kvpp oldest)
{
	if (oldest) {
		tqfree(oldest->newer);
		free(oldest);
	}
}

int
hash(int key)
{
	key %= TABLESIZE;
	key *= 33;
	key %= TABLESIZE;
	return (key < 0) ? key+TABLESIZE : key;
}

kvpp
table_lookup(kvpp *table, int key)
{
	int h = hash(key);
	for (kvpp curr = table[h]; curr; curr = curr->next) {
		if (curr->key == key) {
			return curr;
		}
	}
	return NULL;
}

void
time_update(LRUCache *obj, kvpp *pair, int val)
{
	/* time_update time */
	if ((*pair)->older && (*pair)->newer) {
		(*pair)->older->newer = (*pair)->newer;
		(*pair)->newer->older = (*pair)->older;
		tenq(&(obj->oldest), &(obj->newest), pair);
	} else if ((*pair)->newer) {
		obj->oldest = (*pair)->newer;
		obj->oldest->older = NULL;
		tenq(&(obj->oldest), &(obj->newest), pair);
	}
}

void
lru_ins(LRUCache *obj, kvpp *pair)
{
	/* add to table */
	int h = hash((*pair)->key);
	kvpp *table = obj->table;
	if (table[h]) {
		(*pair)->prev = NULL;
		(*pair)->next = table[h];
		(table[h])->prev = *pair;
	}
	table[h] = *pair;
	/* add to time queue */
	tenq(&(obj->oldest), &(obj->newest), pair);

	(obj->count)++;
}

void
lru_evict(LRUCache *obj)
{
	/* remove from time queue */
	kvpp pair = tdeq(&(obj->oldest), &(obj->newest));
	/* remove from hash table */
	if (pair->prev && pair->next) {
		pair->prev->next = pair->next;
		pair->next->prev = pair->prev;
	} else if (pair->prev) {
		pair->prev->next = NULL;
	} else if (pair->next) {
		int h = hash(pair->key);
		kvpp *table = obj->table;
		table[h] = pair->next;
		if (table[h]) {
			(table[h])->prev = NULL;
		}
	} else {
		int h = hash(pair->key);
		(obj->table)[h] = NULL;
	}
	pair->prev = NULL;
	pair->next = NULL;
	free(pair);
}
