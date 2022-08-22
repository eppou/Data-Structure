#include "fila.h"

// structs

typedef struct XyPoint
{
	double x;
	double y;
} XyPoint;

typedef struct Queue
{
	int size;
	int start;
	int end;
	void *data[1000];
} Queue;

// cria fila
Fila newQueue()
{
	Queue *q = (Queue *)malloc(sizeof(Queue));

	if (q == NULL)
	{
		return q;
	}

	q->size = 0;
	q->start = 0;
	q->end = 0;
	return q;
}

// insere na fila
int enqueue(void *qq, double x, double y)
{
	Queue *q = (Queue *)qq;

	if (q->size == 1000)
	{
		return -1;
	}

	XyPoint *pontoCartesiano = (XyPoint*)malloc(sizeof(XyPoint));

	pontoCartesiano->x = x;
	pontoCartesiano->y = y;
	q->data[q->end] = pontoCartesiano;

	q->size = q->size + 1;
	if (q->end == 999)
	{
		q->end = 0;
	}
	else
	{
		q->end++;
	}

	return q->size;
}

// remove da fila
void *dequeue(void *qq)
{
	Queue *q = (Queue *)qq;
	if (q->size == 0)
	{
		return NULL;
	}

	void *value = q->data[q->start];

	if (q->start == 999)
	{
		q->start = 0;
	}
	else
	{
		q->start++;
	}

	q->size = q->size - 1;

	return value;
}

// limpa fila
void freeQueue(void *qq)
{
	int sizee = ((Queue *)qq)->size;
	while (sizee != 0)
	{
		free(dequeue(qq));
		sizee--;
	}
	free(qq);
}

double pickXfromxyPoint(void *xyptr)
{
	return ((XyPoint *)xyptr)->x;
}

double pickYfromxyPoint(void *xyptr)
{
	return ((XyPoint *)xyptr)->y;
}

int returnQueuesize(Fila q)
{
	return (((Queue *)q)->size);
}

void importQueue(void *ED, Fila qq)
{
	Queue *q = (Queue *)qq;
	int start = q->start;
	int stop = q->end - 1;
	int ind;
	while (start <= stop)
	{
		if(q->data[start]!=NULL){
		void *element = q->data[start];
		lista_inserenofim(ED, element);
		}
		if (start == 999)
		{
			start = 0;
		}
		else if(start != 999)
		{
			start = start + 1;
		}
	}
}