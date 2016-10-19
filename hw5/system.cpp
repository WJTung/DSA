#include <stdio.h>
#include <cstring>
#include "binomial_heap.h"
using namespace std;
class task
{
	public:
		int id, priority;
		bool operator>(const task& t) const
		{
			if(this->priority > t.priority)
				return true;
			else if(this->priority < t.priority)
				return false;
			else if(this->id < t.id)
				return true;
			else
				return false;
		}
		void operator=(const task& t)
		{
			this->priority = t.priority;
			this->id = t.id;
		}
};
int main()
{
	char command[10];
	int c, w, cm, id, p, cm1, cm2, max_id, max_priority;
	scanf("%d%d", &c, &w);
	BinomialHeap <task> *Computers = new BinomialHeap <task>[c];
	while(scanf("%s", command) != EOF)
	{
		if(strcmp(command, "assign") == 0)
		{
			scanf("%d%d%d", &cm, &id, &p);
			task t;
			t.id = id;
			t.priority = p;
			Computers[cm].insert(t);
			printf("There are %d tasks on computer %d.\n", Computers[cm].size, cm);
		}
		else if(strcmp(command, "execute") == 0)
		{
			scanf("%d", &cm);
			max_priority = (Computers[cm].find_max()).priority;
			while(Computers[cm].size > 0 && (Computers[cm].find_max()).priority == max_priority)
			{
				max_id = (Computers[cm].find_max()).id;
				Computers[cm].pop();
				printf("Computer %d executed task %d.\n", cm, max_id);
			}
		}
		else if(strcmp(command, "merge") == 0)
		{
			scanf("%d%d", &cm1, &cm2);
			if(Computers[cm2].size >= w)
			{
				Computers[cm1].merge(Computers[cm2]);
				max_priority = (Computers[cm1].find_max()).priority;
				printf("The largest priority number is now %d on %d.\n", max_priority, cm1);
			}
			else
				puts("Merging request failed.");
		}
		else
			puts("Illegal command.");
	}
}
	
