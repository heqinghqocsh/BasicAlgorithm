#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

node *create(int n)
{
	node *p = NULL,*head;
	node *s;
	int i = 1;
	head = (node *)malloc(sizeof(node));
	p = head;
	
	if(0 != n)
	{
		while(i <= n)
		{
			s = (node *)malloc(sizeof(node));
			s->data = i++;
			p->next = s;
			p = s;
		}
		s->next = head->next;
	}
	free(head);
	return s->next;
}

int main()
{
	int n = 41;
	int m = 3;
	int i;
	node *p = create(n);
	node *tmp;
	m %= n;
	while(p != p->next)
	{
		for(i = 1;i < m-1; i++)
		{
			p=p->next;
		}
		printf("%d->",p->next->data);
		tmp = p->next;
		p->next = tmp->next;
		free(tmp);
		p = p->next;
	}
	printf("%d\n",p->data);
	return 0;
}