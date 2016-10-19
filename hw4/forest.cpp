#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#define Data_Index 1200
#define Data_Num 100000
using namespace std;
typedef struct treenode
{	
	int index;
	double value;
	struct treenode *left;
	struct treenode *right;
	bool result;
} Treenode;
typedef struct data
{
	bool label;
	double *value;
} Data;
class compare
{
	private:
		int index;
	public:
		compare(int i):index(i){};
		bool operator()(Data *P1, Data *P2)
		{
			if(P1->value[index] < P2->value[index])
				return 1;
			return 0;
		}
};
double find_min_confusion(int index, Data **start, int size, int a, int b, int total)
{
	int c = 0, d = 0, e = a, f = b; // branch into cYdN and eYfN 
	int i;
	double total_confusion;
	double min_confusion = 10;
	double last = -1;
	sort(start,	(start+size), compare(index)); 
	for(i = 0; i < size; i++)
	{
		if((*(start + i))->value[index] != last && i != 0)
		{
			total_confusion = (double)(2 * c * d)/(double)((c + d) * total) + (double)(2 * e * f)/(double)((e + f) * total);
			if(total_confusion < min_confusion)
				min_confusion = total_confusion;
		}
		if((*(start + i))->label)
		{
			c++;
			e--;
		}
		else
		{
			d++;
			f--;
		}
		last = (*(start + i))->value[index];
	}
	return min_confusion;
}
int find_min_position(int index, Data **start, int size, int a, int b, int total)
{
	int c = 0, d = 0, e = a, f = b, min_position = 0; // branch into cYdN and eYfN
	int i;	
	double total_confusion;
	double min_confusion = 10;
	double last = -1;
	sort(start,	(start+size), compare(index)); 
	for(i = 0; i < size; i++)
	{
		if((*(start + i))->value[index] != last && i != 0)
		{
			total_confusion = (double)(2 * c * d)/(double)((c + d) * total) + (double)(2 * e * f)/(double)((e + f) * total);
			if(total_confusion < min_confusion)
			{
				min_confusion = total_confusion;
				min_position = i;
			}
		}
		if((*(start + i))->label)
		{
			c++;
			e--;
		}
		else
		{
			d++;
			f--;
		}
		last = (*(start + i))->value[index];
	}
	return min_position;
}
Treenode *branch(Data **start, int size, double epsilon, int max_index)
{
	int i, a = 0, b = 0, total; //aYbN
	int index = 0, left_size, right_size;
	double confusion, total_confusion, min_confusion = 10;
	Treenode *T;
	for(i = 0; i < size; i++)
	{
		if((*(start + i))->label)
			a++;
		else  
			b++;
	}
	confusion = (double)(2 * a * b)/(double)((a + b)*(a + b));
	if(confusion <= epsilon)
	{
		T =(Treenode *)malloc(sizeof(Treenode));
		T->left = NULL; 
		T->right = NULL;
		if(a > b)
			T->result = 1;
		else
			T->result = 0;
		return T;
	}
	else 
	{
		total = a + b;
		for(i = 0; i <= max_index; i++) //try max_index value to decide how to branch
		{
			total_confusion = find_min_confusion(i, start, size, a, b, total);
			if(total_confusion < min_confusion)
			{
				min_confusion = total_confusion;
				index = i;
			}
		}
		if(min_confusion == 10) //noise
		{
			T =(Treenode *)malloc(sizeof(Treenode));
			T->left = NULL; 
			T->right = NULL;
			if(a > b)
				T->result = 1;
			else
				T->result = 0;
			return T;
		}
		T =(Treenode *)malloc(sizeof(Treenode));
		left_size = find_min_position(index, start, size, a, b, total); 
		right_size = total - left_size;
		T->index = index;
		T->value = (((*(start+left_size-1))->value[index]) + ((*(start + left_size))->value[index])) / 2.0;
		if(a > b)
			T->result = 1;
		else 
			T->result = 0;
		T->left = branch(start, left_size, epsilon, max_index); 
		T->right = branch((start + left_size), right_size, epsilon, max_index);
		return T;
	}
}
Treenode *random_tree(Data **P, int t, double epsilon, int max_index)
{
	int random_t = t / 3;
	int i, j, tmp;
	Data **random_P = new Data *[random_t];
	int *random_num = new int [t];
	for(i = 0; i < t; i++)
		random_num[i] = i;
	for(i = t - 1; i >= 1; i--) //Knuth shuffle
	{
		j = rand() % (i + 1);
		tmp = random_num[i];
		random_num[i] = random_num[j];
		random_num[j] = tmp;
	}
	for(i = 0; i < random_t; i++)
		random_P[i] = P[random_num[i]];
	Treenode *T = branch(random_P, random_t, epsilon, max_index);
	delete [] random_P;
	delete [] random_num;
	return T;
}
void print_tab(int t)
{
	int i;
	for(i = 1; i <= t; i++)
		cout<<'\t';
}
void print_tree(Treenode *T, int t)
{
	if(T->left == NULL && T->right == NULL)
	{
		print_tab(t);
		if(T->result)
			cout<<"Y++;"<<endl;
		else
			cout<<"N++;"<<endl;
		return;
	}
	print_tab(t);
	cout<<"if(attr["<<T->index<<"] > "<<T->value<<"){"<<endl;
	print_tree(T->right, t+1);
	print_tab(t);
	cout<<"}"<<endl;
	print_tab(t);
	cout<<"else{"<<endl;
	print_tree(T->left, t+1);
	print_tab(t);
	cout<<"}"<<endl;
}
int main(int argc, char **argv)
{
	srand(time(NULL));
	ifstream fin;
	fin.open(argv[1]);
	string str;
	int label, index, t = 0;
	int max_index = 0;
	int i;
	double value;
	int tree_num = atoi(argv[2]);
	Data *D = new Data[Data_Num];
	Data **P = new Data *[Data_Num];
	for(i = 0; i < Data_Num; i++)
		P[i] = (D + i);
	while(getline(fin, str))
	{
		char *cstr = new char [str.size()+1]; 
		char *tmp;
		strncpy(cstr, str.c_str(), str.size()+1);
		tmp = strtok(cstr, ": ");
		label = atoi(tmp);
		if(label == 1)
			D[t].label = 1;
		else
			D[t].label = 0;
		D[t].value = new double [Data_Index];
		for(i = 0; i < Data_Index; i++)
			D[t].value[i] = 0;
		tmp = strtok(NULL, ": ");
		while(tmp != NULL)
		{
			index = atoi(tmp);
			if(index > max_index)
				max_index = index;
			tmp = strtok(NULL, ": ");
			value = atof(tmp);
			tmp = strtok(NULL, ": ");
			D[t].value[index] = value;
		}
		delete[] cstr;
		t++;
	}
	cout<<"int forest_predict(double *attr){"<<endl;
	cout<<"\t"<<"int Y = 0;"<<endl;
	cout<<"\t"<<"int N = 0;"<<endl;
	for(i = 1; i <= tree_num; i++)
	{
		cout<<"\t"<<"// tree "<<i<<"_predict"<<endl;
		Treenode *T = random_tree(P, t, 0, max_index);
		print_tree(T, 1);
	}
	cout<<"\t"<<"// Voting"<<endl;
	cout<<"\t"<<"if(Y > N) return 1;"<<endl;
	cout<<"\t"<<"else return -1;"<<endl;
	cout<<"}"<<endl;
	for(i = 0; i < t; i++)
		delete[] D[i].value;
	delete[] D;
	delete[] P;
	return 0;
}
	
	