#include <stdio.h>

#include <stdlib.h>

 

struct hlist_head {

struct hlist_node *first;

};

 

struct hlist_node {

struct hlist_node *next, **pprev;

};

 

#define HLIST_HEAD_INIT { .first = NULL }

#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }

#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)

static inline void INIT_HLIST_NODE(struct hlist_node *h)

{

h->next = NULL;

h->pprev = NULL;

}

 

static inline int hlist_unhashed(const struct hlist_node *h)

{

return !h->pprev;

}

 

static inline int hlist_empty(const struct hlist_head *h)

{

return !h->first;

}

 

static inline void __hlist_del(struct hlist_node *n)

{

struct hlist_node *next = n->next;

struct hlist_node **pprev = n->pprev;

*pprev = next;

if (next)

next->pprev = pprev;

}

 

static inline void hlist_del(struct hlist_node *n)

{

__hlist_del(n);

#define LIST_POISON1  ((void *) 0x00100100)

#define LIST_POISON2  ((void *) 0x00200200)

n->next = LIST_POISON1;

n->pprev = LIST_POISON2;

}

#define offset_of(type, memb) \

((unsigned long)(&((type *)0)->memb))

 

#define container_of(obj, type, memb) \

((type *)(((char *)obj) - offset_of(type, memb)))

#define hlist_entry(ptr, type, member) container_of(ptr,type,member)

 


#define hlist_for_each_entry(tpos, pos, head, member) \

for (pos = (head)->first; \

    pos && ({ (pos->next); 1;}) && \

({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \

    pos = pos->next)

 

struct hlist_head nf_sockopts;


struct nf_sockopt_node

{

struct hlist_node node;

int data;

};

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)

{

struct hlist_node *first = h->first;

n->next = first;

if (first)

first->pprev = &n->next;

h->first = n;

n->pprev = &h->first;

}

HLIST_HEAD(nf_sockopts);

 

void nf_register_sockopt(struct nf_sockopt_node *node )

{

hlist_add_head(&node->node,&nf_sockopts);

}

 

void nf_unregister_sockopt(struct nf_sockopt_node *node)

{

hlist_del(&node->node);

}

int main(void)

{

struct nf_sockopt_node node1,node2,*ops_node;

node1.data = 1;

node2.data = 2;

struct hlist_node *node11;

INIT_HLIST_NODE(&node1.node);

INIT_HLIST_NODE(&node2.node);

nf_register_sockopt(&node1);

nf_register_sockopt(&node2);

hlist_for_each_entry(ops_node,node11,&nf_sockopts,node){

printf("%d\n",ops_node->data);

}


nf_unregister_sockopt(&node1);

nf_unregister_sockopt(&node2);


 

return 0;

}
