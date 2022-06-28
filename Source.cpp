#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

struct HTree
{
	int count;
	char symbol;
	HTree *l, *r, *p;
};

struct freq
{
	int count;
	char symbol;
	HTree *p;
	freq *next;
};

struct code
{
	char data;
	code *down;
	code *next;
};

struct string
{
	char data;
	string *next;
};

freq* insertFirstf(freq* l, int item, char symbol, HTree *p)
{
	if (l == NULL)
	{
		l = (freq*)malloc(sizeof(freq));
		l->symbol = symbol;
		l->p = p;
		l->count = item;
		l->next = NULL;
	}
	else
	{
		freq* tmp = (freq*)malloc(sizeof(freq));
		tmp->symbol = symbol;
		tmp->p = p;
		tmp->count = item;
		tmp->next = l;
		l = tmp;
	}
	return l;
}

freq* insertFirstfp(freq* l, int item, char symbol, HTree *p)
{
	if (l == NULL)
	{
		l = (freq*)malloc(sizeof(freq));
		l->symbol = symbol;
		l->p = p;
		l->count = item;
		l->next = NULL;
	}
	else if (l->count > item)
	{
		freq* tmp = (freq*)malloc(sizeof(freq));
		tmp->symbol = symbol;
		tmp->p = p;
		tmp->count = item;
		tmp->next = l;
		l = tmp;
	}
	else
	{
		freq *itr;
		itr = l;
		while (itr->next && itr->next->count <= item)
			itr = itr->next;
		freq *tmp = (freq*)malloc(sizeof(freq));
		tmp->symbol = symbol;
		tmp->p = p;
		tmp->count = item;
		tmp->next = itr->next;
		itr->next = tmp;
	}
	return l;
}

code* removeLast(code* l)
{
	if (l == NULL)
		return NULL;
	if (l->next == NULL)
	{
		free(l);
		l = NULL;
	}
	else
	{
		code* it = l;
		while (it->next->next != NULL)
			it = it->next;
		free(it->next);
		it->next = NULL;
	}
	return l;
}

string* removeLasts(string* l)
{
	if (l == NULL)
		return NULL;
	if (l->next == NULL)
	{
		free(l);
		l = NULL;
	}
	else
	{
		string* it = l;
		while (it->next->next != NULL)
			it = it->next;
		free(it->next);
		it->next = NULL;
	}
	return l;
}

code* insertFirstC(code* l, char data)
{
	if (l == NULL)
	{
		l = (code*)malloc(sizeof(code));
		l->data = data;
		l->down = NULL;
		l->next = NULL;
	}
	else
	{
		code* tmp = (code*)malloc(sizeof(code));
		tmp->data = data;
		tmp->down = NULL;
		tmp->next = l;
		l = tmp;
	}
	return l;
}

code* insertLastC(code *l, char data)
{
	if (l == NULL)
	{
		l = (code*)malloc(sizeof(code));
		l->data = data;
		l->next = NULL;
	}
	else
	{
		code* it = l;
		while (it->next)
			it = it->next;
		code *tmp = (code*)malloc(sizeof(code));
		tmp->data = data;
		tmp->next = NULL;
		it->next = tmp;
	}
	return l;
}

string* remove(string* l, string *remove)
{
	if (remove == l)
	{
		l = l->next;
		free(remove);
	}
	else
	{
		string* it = l;
		while (it->next != remove)
			it = it->next;
		string* tmp = it->next;
		it->next = it->next->next;
		free(tmp);
	}
	return l;
}

freq* removef(freq* l, freq *remove)
{
	if (remove == l)
	{
		l = l->next;
		free(remove);
	}
	else
	{
		freq* it = l;
		while (it->next != remove)
			it = it->next;
		freq* tmp = it->next;
		it->next = it->next->next;
		free(tmp);
	}
	return l;
}

freq* freqTable(char item, freq* table)
{
	freq *iter;
	if (table==NULL)
		table = insertFirstf(table, 1, item, NULL);
	else
	{
			iter = table;
		while (iter->next && item != iter->symbol)
			iter = iter->next;
		if (iter->next == NULL && iter->symbol != item)
			table = insertFirstf(table, 1, item, NULL);
		else
			iter->count = iter->count + 1;
	}
	return table;
}

freq* sortTest(freq *table)
{
	int tmp;
	freq* iter = table;
	char tmpS;
	HTree *tmpT;
	int count = 0;
	while (iter->next)
	{
		count++;
		iter = iter->next;
	}
	count++;
	iter = table;
	for (int i = 0; i < count; i++)
	{
		iter = table;
		while (iter->next)
		{
			if (iter->next->count < iter->count)
			{
				tmp = iter->count;
				tmpS = iter->symbol;
				tmpT = iter->p;
				iter->count = iter->next->count;
				iter->p = iter->next->p;
				iter->symbol = iter->next->symbol;
				iter->next->count = tmp;
				iter->next->p = tmpT;
				iter->next->symbol = tmpS;
			}
			iter = iter->next;
		}
	}
	return table;
}

freq* max(freq *table, char &symbol, int &max)
{
	freq *it = table;
	freq *tmp = it;
	symbol = it->symbol;
	max = it->count;
	it = it->next;
	while (it)
	{
		if (it->count > max || (max >= it->count && it->symbol == NULL && symbol != NULL))
		{
			max = it->count;
			symbol = it->symbol;
			tmp = it;
			it = it->next;
		}
		else
		{
			it = it->next;
		}
	}
	return tmp;
}

freq* sort(freq *table)
{
	char m;
	int cou;
	HTree *p = NULL;
	freq *tmp = NULL;
	freq* find;
	while (table)
	{
		find = max(table, m, cou);
		p = find->p;
		table = removef(table, find);
		tmp = insertFirstf(tmp, cou, m, p);
	}
	return tmp;
}

string* insertFirsts(string *l, char item)
{
	if (l == NULL)
	{
		l = (string*)malloc(sizeof(string));
		l->data = item;
		l->next = NULL;
	}
	else
	{
		string* tmp = (string*)malloc(sizeof(string));
		tmp->data = item;
		tmp->next = l;
		l = tmp;
	}
	return l;
}

string* insertLasts(string* l, int item)
{
	if (l == NULL)
	{
		l = (string*)malloc(sizeof(string));
		l->data = item;
		l->next = NULL;
	}
	else
	{
		string* it = l;
		while (it->next != NULL)
			it = it->next;
		string* tmp = (string*)malloc(sizeof(string));
		tmp->data = item;
		tmp->next = NULL;
		it->next = tmp;
	}

	return l;
}

void printt(freq *link)
{
	if (link == NULL)
		return;
	freq *it;
	it = link;
	while (it->next != NULL)
	{
		printf("%c:%d\n", it->symbol, it->count);
		it = it->next;
	}
	printf("%c:%d\n", it->symbol, it->count);
}


HTree* huff(HTree *tree, freq *table)
{
	while (table->next)
	{
		if (table->p && table->next->p)
		{
			HTree *l3 = (HTree*)malloc(sizeof(HTree));
			l3->count = table->count + table->next->count;
			l3->symbol = NULL;
			l3->l = table->p;
			l3->r = table->next->p;
			table->p->p = l3;
			table->next->p->p = l3;
			table = removef(table, table);
			table = removef(table, table);
			table = insertFirstf(table, l3->count, l3->symbol, l3);
			table = sort(table);
			printf("\n\n\n\n\n");
			printt(table);
		}
		else if (table->p == NULL && table->next->p)
		{
			HTree *l1 = (HTree*)malloc(sizeof(HTree));
			HTree *l3 = (HTree*)malloc(sizeof(HTree));
			l1->count = table->count;
			l1->symbol = table->symbol;
			l3->count = table->count + table->next->count;
			l3->symbol = NULL;
			l3->l = l1;
			l3->r = table->next->p;
			l1->l = NULL;
			l1->r = NULL;
			table->next->p->p = l3;
			table = removef(table, table);
			table = removef(table, table);
			table = insertFirstf(table, l3->count, l3->symbol, l3);
			table = sort(table);
			printf("\n\n\n\n\n");
			printt(table);
		}
		else if (table->p && table->next->p == NULL)
		{

			HTree *l2 = (HTree*)malloc(sizeof(HTree));
			HTree *l3 = (HTree*)malloc(sizeof(HTree));
			l2->count = table->next->count;
			l2->symbol = table->next->symbol;
			l3->count = table->count + table->next->count;
			l3->symbol = NULL;
			l3->r = l2;
			l2->l = NULL;
			l2->r = NULL;
			l3->l = table->p;
			table->p->p = l3;
			table = removef(table, table);
			table = removef(table, table);
			table = insertFirstf(table, l3->count, l3->symbol, l3);
			table = sort(table);
			printf("\n\n\n\n\n");
			printt(table);
		}
		else
		{
			HTree *l1 = (HTree*)malloc(sizeof(HTree));
			HTree *l2 = (HTree*)malloc(sizeof(HTree));
			HTree *l3 = (HTree*)malloc(sizeof(HTree));
			l1->count = table->count;
			l1->symbol = table->symbol;
			l2->count = table->next->count;
			l2->symbol = table->next->symbol;
			l3->symbol = NULL;
			l3->count = table->count + table->next->count;
			l3->l = l1;
			l3->r = l2;
			l1->p = l3;
			l2->p = l3;
			l1->l = NULL;
			l1->r = NULL;
			l2->l = NULL;
			l2->r = NULL;
			table = removef(table, table);
			table = removef(table, table);
			table = insertFirstf(table, l3->count, l3->symbol, l3);
			table = sort(table);
			printf("\n\n\n\n\n");
			printt(table);
		}
	}
	table->p->p = NULL;
	tree = table->p;
	free(table);
	return tree;
}

code *gen;
code *tmp = NULL;
code *it = NULL;

code* copy(code *table, code *tmp)
{
	table = table->next;
	while (table->next)
	{
		tmp = insertLastC(tmp, table->data);
		table = table->next;
	}
	tmp = insertLastC(tmp, table->data);
	return tmp;
}

void HCodeGen(HTree *tree, code *table)
{
	if (tree->r == NULL && tree->l == NULL)
	{
		if (it == NULL)
			table = insertFirstC(table, tree->symbol);
		else
		{
			tmp = insertFirstC(tmp, tree->symbol);
		}
		if (table->down == NULL)
			gen = table;
		table = gen;
		it = table;
		while (it->down)
			it = it->down;
		if (tmp)
		{
			if (tmp->data != 1 && tmp->data != 0)
			{
				it->down = tmp;
				it = it->down;
				it->down = NULL;
			}
		}
		tmp = NULL;
		tmp = copy(it, tmp);
	}
	if (tree->l)
	{
		if (it == NULL)
			table = insertLastC(table, 0);
		else
			tmp = insertLastC(tmp, 0);
		HCodeGen(tree->l, table);
	}
	if (tree->r)
	{
		if (it == NULL)
			table = insertLastC(table, 1);
		else
			tmp = insertLastC(tmp, 1);
		HCodeGen(tree->r, table);
	}
	if (tmp)
		tmp = removeLast(tmp);
}

string* copys(string *str, string *str1)
{
	while (str->next)
	{
		str1 = insertFirsts(str1, str->data);
		str = str->next;
	}
	str1 = insertFirsts(str1, str->data);
	return str1;
}

string* removeFirst(string* l)
{
	if (l == NULL)
		return NULL;
	if (l->next == NULL)
	{
		free(l);
		l = NULL;
	}
	else
	{
		string* tmp = l->next;
		free(l);
		l = tmp;
	}
	return l;
}

int convToBit(string *bit,int &count2)
{
	long count=0;
	long count1 = 0;
	long count3 = 0;
	int count4 = 0;
	int count5 = 0;
	string *bit1;
	count2 = 0;
	long sum;
	code *pt;
	FILE* fp = fopen("input.txt", "r");
	FILE *fo = fopen("output.txt", "w+");
	char item;
	fprintf(fo, "%d", count);
	while (!feof(fp))
	{
		fscanf(fp, "%c", &item);
		if (item == 'g')
			count5 = 0;
		count2++;
		if (!feof(fp))
		{
			pt = gen;
			while (item != pt->data)
				pt = pt->down;
			pt = pt->next;
			while (pt)
			{
				//printf("%d", pt->data);
				bit = insertLasts(bit, pt->data);
				bit1 = bit;
				pt = pt->next;
				count++;
				if (count % 8 == 0)
				{
					sum = 0;
					for (int j = 0; j < 8; j++)
					{
							sum = pow(2, j) * bit->data + sum;
							bit = removeFirst(bit);
					}
					count1++;
					fprintf(fo, "%c", sum);
					if ((char)sum == '\n')
						count3++;
				}
			}
			free(pt);
			pt = NULL;
		}
	}
	sum = 0;
	bit1 = bit;
	for (int i = 0; i < count % 8; i++)
		if (bit)
		{
			sum = pow(2, i) * bit->data + sum;
			bit = removeFirst(bit);
		}
	if (count%8!=0)
		fprintf(fo, "%c", sum);
	fclose(fp);
	count = 8 - (count % 8);
	if (count==8)
		count=0;
	rewind(fo);
	fprintf(fo, "%c", count);
	fclose(fo);
	return count1;
}

int count(string *bit)
{
	int i = 0;
	while (bit)
	{
		i++;
		bit = bit->next;
	}
	return i;
}

void compressRatio(int counts, int strCom)
{
	printf("compression ratio: %f", ((float)counts-1) / (strCom + 1));
}

void print(string *link)
{
	if (link == NULL)
		return;
	string *it;
	it = link;
	while (it->next != NULL)
	{
		printf("%c", it->data);
		it = it->next;
	}
	printf("%c", it->data);
}

void decomp()
{
	code *r = NULL;
	code *l = NULL;
	code *itr = NULL;
	string *str = NULL;
	string *str1 = NULL;
	string *str2 = NULL;
	int t = 0;
	string *str3 = NULL;
	string *tmp=NULL;
	bool no = false;
	bool flag = false;
	int count1=0;
	int count2 = 0;
	int count3 = 0;
	int lol;
	int loop;
	int lop;
	int remain;
	char txt;
	char y;
	FILE *fc = fopen("codes.dat", "r");
	while (!feof(fc))
	{
		fscanf(fc, "%c", &txt);
		if (!feof(fc))
		{
			if (txt != 1 && txt != 0)
			{
				if (l == r)
					r = NULL;
				else
				{
					itr = l;
					while (itr->down)
						itr = itr->down;
					itr->down = r;
					r = NULL;
				}
				r = insertFirstC(r, txt);
			}
			else
			{
				r = insertLastC(r, txt);
			}
			if (l == NULL)
			{
				l = r;
			}
		}
	}
	if (l == r)
		r = NULL;
	else
	{
		itr = l;
		while (itr->down)
			itr = itr->down;
		itr->down = r;
		r = NULL;
	}
	fclose(fc);
	FILE *fcom = fopen("output.txt", "rb");
	int count = 0;
	int x;
	fseek(fcom, 0L, SEEK_END);
	x = ftell(fcom);
	rewind(fcom);
	x = x - 1;
	fscanf(fcom, "%c", &txt);
	lop = txt;
	txt = NULL;
	while (x != 0)
	{
		if (no == false || (txt == '\n' && y=='\n'))
		{
			//if (!feof(fcom))
				fscanf(fcom, "%c", &txt);
			no = true;
		}
		else
		{
			txt = y;
			t++;
		}
		if (x == 3)
		{
		}
		//if (!feof(fcom))
			fscanf(fcom, "%c", &y);
		if (txt == '\r' && y)
		{
			if (y == '\n')
			{
				txt = y;
				x--;
				count1++;
			}
				lol = txt;
		}
		else
			lol = txt;
		//x--;
		if (lol < 0)
		{
			lol = -lol;
			int flag = 0;
			for (int i = 0; i < 8; i++)
			{
				remain = lol % 2;
				//printf("%d", remain);
				if (lol > 0)
					lol = (lol - remain) / 2;
				else
					remain = 0;
				if (flag == 1)
				{
					if (remain == 1)
						remain = 0;
					else
						remain = 1;
				}
				if (remain == 1)
					flag = 1;
				str1 = insertLasts(str1, remain);
			}
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				remain = lol % 2;
				if (lol > 0)
					lol = (lol - remain) / 2;
				else
					remain = 0;
				str1 = insertLasts(str1, remain);
			}
		}
		if (x==1)
			for (int i = 0; i < lop; i++)
				str1 = removeLasts(str1);
		flag = false;
		while (flag == false)
		{
			r = l;
			itr = r;
				while (itr && r)
				{
					itr = r;
					itr = itr->next;
					str3 = str1;
					loop = 1;
					count = 0;
					while (itr)
					{
						if (itr->data != str3->data)
						{
							loop = 0;
							break;
						}
						if (str3->next == NULL && itr->next)
						{
							loop = 0;
							flag == true;
							break;
						}
						else
						{
							str3 = str3->next;
							count++;
							if (str3 == NULL)
								flag = true;
							itr = itr->next;
						}
					}
					if (loop == 1)
					{
						if (r->data == '.')
						{
							count2++;
							if (count2 == 78)
								count3 = 1;
						}
						printf("%c", r->data);
						for (int i = 0; i < count; i++)
							str1 = removeFirst(str1);
						break;
					}
					r = r->down;
					if (r == NULL)
						flag = true;
				}
		}
		x--;
	}
	fclose(fcom);
}

void main()
{
	char item;
	int count1;
	int count2;
	string *str = NULL;
	string *str1 = NULL;
	string *bit = NULL;
	string *strCom = NULL;
	freq *table = NULL;
	HTree *tree = NULL;
	code *itr;
	code *tmp1;
	code* code = NULL;
	int pop;
	int remain;
	int counts;
	int sum = 0;
	FILE* fp = fopen("input.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%c", &item);
		if (!feof(fp))
			table = freqTable(item, table);
	}
	fclose(fp);
	table = sort(table);
	printt(table);
	tree = huff(tree, table);
	HCodeGen(tree, gen);
	free(tree);
	free(tmp);
	it = NULL;
	free(it);
	count1= convToBit(bit,count2);
	compressRatio(count2, count1);
	printf("\n\n\n");
	FILE *fc = fopen("codes.dat", "w+");
	itr = gen;
	tmp1 = itr;
	while (tmp1)
	{
		while (itr)
		{
			fprintf(fc, "%c", itr->data);
			itr = itr->next;
		}
		tmp1 = tmp1->down;
		itr = tmp1;
	}
	fclose(fc);
	free(gen);
	printf("\n\n\n\n\n");
	decomp();
	getch();
}