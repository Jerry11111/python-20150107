#include<stdio.h>
#include<stdlib.h>

typedef struct min_heap{
	int *queue;
	int index, capacity;

} min_heap_t;
int min_heap_push(min_heap_t *s, int e);
int min_heap_pop(min_heap_t *s);
void min_heap_shift_down_(min_heap_t *s, int index);
void min_heap_shift_up_(min_heap_t *s, int index);
void min_heap_reserve(min_heap_t *s, int size);
void min_heap_ctor(min_heap_t *s);
void min_heap_dtor(min_heap_t *s);
void min_heap_print(min_heap_t *s);


int min_heap_push(min_heap_t *s, int e)
{
	min_heap_reserve(s, s->index + 1);
	s->index++;
	s->queue[s->index] = e;
	min_heap_shift_up_(s, s->index);	
	return 0;
}
int min_heap_pop(min_heap_t *s)
{
	int tmp = s->queue[1];
	s->queue[1] = s->queue[s->index];
	s->queue[s->index] = 0;
	s->index = s->index - 1;
	min_heap_shift_down_(s, 1);
	return tmp;
}
void min_heap_shift_down_(min_heap_t *s, int index)
{
	int child;
	while((child = index * 2) <= s->index)
	{
		if(child < s->index && s->queue[child] > s->queue[child + 1])
		{
			child++;	
		}
		if(s->queue[index] <= s->queue[child])
		{
			break;
		}
		int temp = s->queue[index];
		s->queue[index] = s->queue[child];
		s->queue[child] = temp;
		index = child;
	}
}
void min_heap_shift_up_(min_heap_t *s, int index)
{
	int parent = 0;	
	while((parent = (index / 2)) >= 1)
	{
		if(s->queue[parent] <= s->queue[index])
		{
			break;
		}
		int tmp;
		tmp = s->queue[parent];
		s->queue[parent] = s->queue[index];
		s->queue[index] = tmp;
		index = parent;
	}
}
void min_heap_reserve(min_heap_t *s, int size)
{
	if(size > s->capacity)
	{
		int capacity = s->capacity;
		s->capacity = capacity == 0 ? 8 : capacity * 2;	
		s->queue = realloc(s->queue, capacity * sizeof(int)); 
	}
}
void min_heap_ctor(min_heap_t *s)
{
	s->queue = NULL;
	s->capacity = 0;
	s->index = 0;
}
void min_heap_dtor(min_heap_t *s)
{
	free(s->queue);
}
int min_heap_size(min_heap_t *s)
{
	return s->index;
}
void min_heap_print(min_heap_t *s)
{
	int i = 1;	
	for(; i <= s->index; i++)
	{
		printf("%d ", s->queue[i]);
	}
	printf("\n");
}
void min_heap_test()
{
	min_heap_t s;
	min_heap_ctor(&s);
	min_heap_push(&s, 5);
	min_heap_push(&s, 2);
	min_heap_push(&s, 3);
	min_heap_push(&s, 1);
	min_heap_push(&s, 3);
	min_heap_print(&s);
	printf("size = %d\n", min_heap_size(&s));
	int i = min_heap_pop(&s);
	printf("%d\n", i);
	min_heap_print(&s);
	printf("size = %d\n", min_heap_size(&s));

}
int main(int argc, char **argv)
{
	min_heap_test();
	return 0;
}
