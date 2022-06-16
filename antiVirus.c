/*********************************
* Class: MAGSHIMIM C2			 *
* Week:8		    			 *
* Name:adir cohen                *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define FIRST_PART 4
#define LAST_PART 5
#define Infected 0
#define SAFE 1
int virusCheck(char* path, char* virusPath);
int fastVirusCheck(char* path, char* virusPath);

int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		printf("how to run - 'antiVirus.exe' ,Dirctory path ,virus path\n");

		return 1;
	}
	
	FILE* log = NULL;
	char path[255] = { 0 };//path of current file
	char pathOfLog[MAX] = { 0 };//path of the log
	char whatScan[MAX] = { 0 };//what kind of scan
	char choose = ' ';
	char names[20][MAX] = { 0 };
	int n = 0;
	strcat(path, argv[1]);// path += dir path
	DIR* d = 0;
	struct dirent* dir = 0;
	//printf("%s", argv[1]);
	d = opendir(argv[1]);
	int bool = 0;

	
	printf("wellcome to my anti-virus ;) hope you like it\n");
	printf("\nFolder to scan: %s\n", argv[1]);
	printf("Virus signature: %s\n", argv[2]);
	printf("\npress 0 for a normal scan or any other key fo quick scan: ");
	choose = getchar();
	printf("procces may take a few minutes\n");
	

	
	if (choose == '0')
	{
		strcat(pathOfLog, argv[1]);
		strcat(pathOfLog, "/slowScanLog.txt");
		strcpy(whatScan, "Normal scan");
		log = fopen(pathOfLog, "w");//open file to wirte
		
	}
	else
	{
		
		strcat(pathOfLog, argv[1]);
		strcat(pathOfLog, "/fastScanLog.txt");
		strcpy(whatScan, "Quick Scan");
		log = fopen(pathOfLog, "w");//open file to wirte
	}

	fputs("wellcome to my anti-virus ;) hope you like it\n",log);
	
	fprintf(log, "\nFolder to scan:\n%s\n", argv[1]);//fprintf = printf to file
	

	fprintf(log, "Virus signature:\n%s\n", argv[2]);

	if (d == NULL)
	{
		fputs("Error opening file\nhow to run - file.exe Dirctory path virus path (for fast scan do 1 other for slow)\n", log);

		printf("Error opening file\n");
		printf("how to run - file.exe Dirctory path virus path (for fast scan do 1 other for slow)\n");
		return 1;
	}
	

	

	fprintf(log, "\nScanning option:\n%s\n\n", whatScan);


	fputs("results:\n", log);
	printf("\nscanning:\n", log);
	while ((dir = readdir(d)) != NULL)
	{
		if (strcmp(dir->d_name, ".") &&
			strcmp(dir->d_name, ".."))
		{
			strcpy(names[n], dir->d_name);
			
			n++;
			//printf("File name: %s\n", dir->d_name); 
			
		}

		
	}

	
	char temp[30];

	//Sort array using the Buuble Sort algorithm
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (strcmp(names[j], names[j + 1]) > 0) {
				//swap array[j] and array[j+1]
				strcpy(temp, names[j]);
				strcpy(names[j], names[j + 1]);
				strcpy(names[j + 1], temp);
			}
		}
	}
	for (int k = 0; k < n; k++)//for every file scan and do things
	{
		strcat(path, "/");
		strcat(path, names[k]);


		if (choose == '0')//normal scan = 0 ,  fast scan = else
		{
			if ((bool = virusCheck(path, argv[2])) == Infected)
			{
				printf("%s - Infected!\n", path);
				fprintf(log, "%s - Infected!\n", path);



			}
			else if (bool == SAFE)
			{
				printf("%s - Clean\n", path);
				fprintf(log, "%s - Clean\n", path);


			}
			else
			{
				printf("could not open the file - %s\n", path);
				fprintf(log, "could not open the file - %s\n", path);


			}
			strcpy(path, argv[1]);


		}
		else
		{
			if ((bool = fastVirusCheck(path, argv[2])) == FIRST_PART)
			{
				fprintf(log, "%s - Infected! (first 20%)\n", path);
				printf("%s - Infected! (first 20%)\n", path);
			}
			else if (bool == LAST_PART)
			{
				fprintf(log, "%s - Infected! (last 20%)\n", path);

				printf("%s - Infected! (last 20%)\n", path);
			}
			else if (bool == Infected)
			{
				fprintf(log, "%s - Infected!\n", path);

				printf("%s - Infected!\n", path);
			}
			else if (bool == SAFE)
			{
				printf("%s - Clean\n", path);
				fprintf(log, "%s - Clean\n", path);

			}
			else
			{
				printf("could not open the file - %s\n", path);
				fprintf(log, "could not open the file - %s\n", path);


			}
			strcpy(path, argv[1]);

		}
		


	}

	
	closedir(d);
	printf("Scan Completed.\nsee log path for result: %s", pathOfLog);
	fclose(log);
	getchar();
	getchar();
	return 0;
}


/*
that func check if the file have the virus
input:path of current file in dir , path of virus sign

output:infcted or not and where its Infected

*/
int fastVirusCheck(char* path, char* virusPath)
{
	FILE* virusFile = fopen(virusPath, "rb");
	FILE* scanFile = fopen(path, "rb");

	long int i = 0;
	long int j = 0;
	long int size = 0;
	long int virusSize = 0;
	char ch = ' ';
	char ch1 = ' ';




	if (virusFile == NULL || scanFile == NULL)
	{
		printf("Error opening file");
		return 2;
	}
	fseek(scanFile, 0, SEEK_END);
	size = ftell(scanFile);
	fseek(scanFile, 0, SEEK_SET);
	fseek(virusFile, 0, SEEK_END);
	virusSize = ftell(virusFile);
	fseek(virusFile, 0, SEEK_SET);
	
	if (size < virusSize)
	{
		return 1;
	}
	fseek(scanFile, 0, SEEK_SET);
	while (i < size / 5)
	{

		ch = (char)fgetc(scanFile);
		ch1 = (char)fgetc(virusFile);
		if (ch == ch1)
		{
			j++;
			if (j >= virusSize)
			{

				return FIRST_PART;
			}
		}

		else
		{
			fseek(virusFile, 0, SEEK_SET);
			j = 0;
		}

		i++;

	}
	
	fseek(scanFile, size - (size / 5), SEEK_SET);
	i = 0;
	j = 0;
	while (i < size / 5)
	{

		ch = (char)fgetc(scanFile);
		ch1 = (char)fgetc(virusFile);
		if (ch == ch1)
		{
			j++;
			if (j >= virusSize)
			{
				printf("the virus is in the last 20% of the file   -     ", '%');

				return LAST_PART;
			}
		}
		else
		{
			fseek(virusFile, 0, SEEK_SET);
			j = 0;
		}

		i++;

	}

	fseek(scanFile, 0, SEEK_SET);
	i = 0;
	j = 0;
	while (i < size )
	{

		ch = (char)fgetc(scanFile);
		ch1 = (char)fgetc(virusFile);
		if (ch == ch1)
		{
			j++;
			if (j == virusSize)
			{
				return 0;
			}
		}

		else
		{
			fseek(virusFile, 0, SEEK_SET);
			j = 0;
		}

		i++;

	}
	
	fclose(virusFile);
	fclose(scanFile);




	return 1;
}


/*
that func check if the file have the virus
input:path of current file in dir , path of virus sign

output:infcted or not

*/
int virusCheck(char* path, char* virusPath)
{

	FILE* virusFile = fopen(virusPath,"rb");
	FILE* scanFile = fopen(path, "rb");

	long int i = 0;
	long int j = 0;
	long int size = 0;
	long int virusSize = 0;
	char ch = ' ';
	char ch1 = ' ';
	


	
	if (virusFile == NULL || scanFile == NULL)
	{
		printf("Error opening file");
		return 2;
	}
	fseek(scanFile, 0, SEEK_END);
	size = ftell(scanFile);
	fseek(scanFile, 0, SEEK_SET);
	fseek(virusFile, 0, SEEK_END);
	virusSize = ftell(virusFile);
	fseek(virusFile, 0, SEEK_SET);
	
	while (i < size)
	{
		
		ch = (char)fgetc(scanFile);
		ch1 = (char)fgetc(virusFile);
		if (ch == ch1)
		{
			j++;
			if (j >= virusSize)
			{
				return 0;
			}
		}
		
		else
		{
			fseek(virusFile, 0, SEEK_SET);
			j = 0;
		}
			
		i++;
		
	}


	fclose(virusFile);
	fclose(scanFile);



	
	return 1;
}