#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

vector<int> myvector;
vector<int>::iterator it;

void do_cat(const char *name)
{
	FILE * myfile;
	myfile = fopen(name, "r");
	if(myfile == NULL)
	{
		printf("ERR: \"%s\" - file can't read\n", name);
		return;
	}

	int i;
	int a;
	try
        {
	while((a = fscanf(myfile, "%d", &i)) != EOF)
		if(a > 0)
			myvector.push_back(i);
		else
		{
			printf("ERR: \"%s\" - bad content\n", name);
			break;
		}
	}
        catch (exception e)
        {
        	printf("ERR: \"%s\" - big size\n", name);
        }

	if(fclose(myfile) == EOF)
		printf("ERR: \"%s\" - file can't close\n", name);
	return;
}



int main(int argc, char *argv[])
{
	// Он нормально работает с 1м файлом
	if(argc == 0)
	{
		printf("ERR: give me file name\n");
		return 0;
	}
	for(int i=1; i<argc;++i)
	{
		//printf("%s:\n", argv[i]);
		do_cat(argv[i]);
	}
	
	sort (myvector.begin(), myvector.end());
	
	FILE * myfile;
	myfile = fopen(argv[argc-1], "w");
	if(myfile == NULL)
	{
		printf("ERR: \"%s\" - can't open to write\n", argv[argc-1]);
		return 0;
	}	
		
	for (it=myvector.begin(); it!=myvector.end(); ++it)
		if(fprintf(myfile, "%d\n", *it)<0)
		{
			printf("ERR: \"%s\" - can't write\n", argv[argc-1]);
			break;
		}
	
	if(fclose(myfile) == EOF)
		printf("ERR: \"%s\" - file can't close\n", argv[argc-1]);
	return 0;
}
