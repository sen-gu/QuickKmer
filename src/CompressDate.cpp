/*******调用CompressEntry(void)函数即可开始数据压缩（数据压缩引导函数）*****/
#include"head.h"
using namespace std;
unsigned char dna_single_in[100];
int cal_4(int temp)//算出每四位DNA对应的int值
{
	int num = 0;
	temp = temp * 4;
	for (int i = 0; i < 4; i++)
	{
		unsigned char ch = dna_single_in[temp];
		num = num * 4;
		switch (ch)
		{
		case 'C':num++;
		case 'T':num++;
		case 'G':num++;
		}
		temp++;
	}
	return num;
}
int Compress(int num)
{
	switch (num)
	{
	case 1:filein = fopen(fileread1, "r"); break;
	case 2:filein = fopen(fileread2, "r"); break;
	}
	if (filein == NULL)
	{
		system("pause");
		return -1;
	}
	fileout = fopen(file_yssj, "ab");
	char ch = fgetc(filein);
	for (unsigned int a = 0; a<500000; a++)
	{
		while ((int)ch != 10)
			ch = fgetc(filein);
		for (int j = 0; j < 100; j++)
		{
			ch = fgetc(filein);
			dna_single_in[j] = ch;
		}
		for (int i = 0; i < 25; i++)
		{
			int t = cal_4(i);
			unsigned char temp = (unsigned char)t;
			fputc(temp, fileout);
		}
		if (!feof(filein))
			ch = fgetc(filein);
		if (!feof(filein))
			ch = fgetc(filein);
	}
	fclose(filein);
	fclose(fileout);
	return 0;
}
void CompressEntry(void)
{
	int flag;
	flag = Compress(1);
	if (flag == 0)
	{
		cout << "READ FILE 1 SUCCESSFULLY" << endl;
	}
	else
	{
		cout << "READ FILE 1 UNSUCCESSFULLY" << endl;
	}
	flag = Compress(2);
	if (flag == 0)
	{
		cout << "READ FILE 2 SUCCESSFULLY" << endl;
	}
	else
	{
		cout << "READ FILE 2 UNSUCCESSFULLY" << endl;
	}
}