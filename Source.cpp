#include<iostream>
#include<string>
#include <stdio.h>
#include <string.h>
using namespace std;

struct node
{
	int index[5], number;
	char bundle[10];
	int counter=0,position=0;
};

char* cat(char* temp, char* temp2);
int match(char* temp, char* temp2);
node* cal(int biddernumber, node* bid,int n);
void sort(node* temp);
int payment(node* temp, node max, int n, int *clanumber);
node winner(int n, node** temp);
node* relation(int n1, int n2, int m, node* old, node* ori,int without);
int cla(int n, int m);

int main()
{
	int biddernumber;

	cout << "Input bidder number:";
	cin >> biddernumber;

	
	node* bid = new node[biddernumber];
	node* sum = new node[biddernumber];
	node** temp = new node*[biddernumber];
	for (int i = 0; i < biddernumber; i++)
	{
		cin >> bid[i].number;
		bid[i].index[i] = 1;
		bid[i].position = i + 1;
		bid[0].counter++;
	}
	
	for (int i = 0; i < biddernumber; i++)
	{
		cin >> bid[i].bundle;
	}

	int* clanumber1 = new int[biddernumber];
	for (int i = 1; i <= biddernumber; i++)
	{
		clanumber1[i - 1] = cla(biddernumber, i);//claculate layer number ex:C(4.1),C(5.3)
	}

	for (int i = 0; i < biddernumber; i++)
	{
		temp[i] = new node[clanumber1[i]];
	}

	temp[0] = bid;
	cout << endl;
	for (int i = 1; i < biddernumber; i++)
	{
		temp[i] = relation(clanumber1[i - 1], clanumber1[i], biddernumber, temp[i - 1], temp[0],50);
	}

	node max;
	max = winner(biddernumber,temp);
	payment(bid, max, biddernumber,clanumber1);

	system("pause");
}

int match(char* temp,char* temp2)
{
	size_t loc = strcspn(temp,temp2);
	if (loc == strlen(temp))//no match
		return 0;
	else
		return 1;
}

char* cat(char* temp, char* temp2)
{
	node a1;
	strcpy_s(a1.bundle,10,temp);
	strcat_s(a1.bundle,10,temp2);//problem
	return a1.bundle;
}


int payment(node* temp,node max,int n,int *clanumber)//n:biddernumber   temp:original   max:the winner node
{
	int cost;
	for (int i = 0; i < 5; i++)
	{
		if (max.index[i] == 1)
		{
			node** a1 = new node*[n];
			a1[0] = temp;
			for (int j = 1; j < n; j++)
			{
				a1[j] = relation(clanumber[j - 1], clanumber[j], n,a1[j - 1], a1[0], i);
			}
			node max_payment;//winner
			max_payment = winner(n,a1);
			cost = max.number - temp[i].number;
			cost = max_payment.number - cost;
			//cout << max_payment.number<<endl;
			cout << "P"<<i<<"cost: "<<cost << endl;
			delete []a1;
		}
	}
	return 0;
}

node winner(int n, node** temp)//find max welfare n:biddernumber
{
	node maximum;
	maximum.number = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < temp[i][0].counter; j++)
		{
			if (temp[i][j].number>maximum.number)
				maximum = temp[i][j];
		}
	}
	return maximum;
}

int cla(int n, int m)//claculate n!
{
	if (n == 0 || m == 0 || n <= m) return 1;
	else return (cla(n - 1, m) + cla(n - 1, m - 1));
}

node* relation(int n1, int n2, int m, node* old, node* ori,int without)//n1:upper layer number ,n2:current layer number ori:the first layer
{
	node* b2 = new node[n2];
	int count = 0;
	for (int i = 0; i < n1 - 1; i++)//1~upper layer number
	{
		if (i != without)
		{
			if (old[i].position != NULL)
			{
				for (int j = old[i].position; j < m; j++)//1~providernumber
				{
					if (j != without)
					{
						int k = match(old[i].bundle, ori[j].bundle);
						if (k == 0)
						{
							b2[count].number = old[i].number + ori[j].number;
							strcpy_s(b2[count].bundle, 10, cat(old[i].bundle, ori[j].bundle));//problem
							b2[count].position = ori[j].position;
							for (int z = 0; z < 5; z++)
							{
								if (z == i || z == j)
									b2[count].index[z] = 1;
							}
							b2[0].counter++;
							count++;
						}
					}
				}
			}
		}
	}
	count = 0;
	return b2;
}

