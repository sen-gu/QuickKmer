#include "head.h"
#include "sys/time.h"
#define fprintf_s fprintf
// #include <windows.h>
// #pragma comment(lib, "winmm.lib ")
using namespace std;
void OutPut(unsigned int address)
{
	unsigned int DNA_num = (address >> 7);
	unsigned int kmer_num = (address & 0x7F);
	if (mode == 1)
	{
		cout << "第" << DNA_num + 1 << "条DNA,第" << kmer_num + 1 << "条" << k << "mer" << endl;
	}
	else
	{
		fprintf_s(fileout, "第%d条DNA,第%d个%dmer\n", DNA_num + 1, kmer_num, k);
		if (mode == 3)
		{
			cout << "第" << DNA_num + 1 << "条DNA,第" << kmer_num + 1 << "条" << k << "mer" << endl;
		}
	}
	return;
}
void OutPut(unsigned int DNA_num, unsigned int kmer_num)
{
	if (mode == 1)
	{
		cout << "第" << DNA_num + 1 << "条DNA,第" << kmer_num + 1 << "条" << k << "mer" << endl;
	}
	else
	{
		fileout = fopen("res.csv", "a");
		fprintf_s(fileout, "第%d条DNA第%d个%dmer\n", DNA_num + 1, kmer_num, k);
		if (mode == 3)
		{
			cout << "第" << DNA_num + 1 << "条DNA,第" << kmer_num + 1 << "条" << k << "mer" << endl;
		}
	}
	return;
}
void check_and_OutPut(unsigned char* char_from_user, unsigned int length_of_char_from_user, unsigned int address)
{
	unsigned int kmer_id = (address & 0x7F);
	if (kmer_id > 100 - k + 1)
	{
		return;
	}
	unsigned char readin_char[25];
	unsigned char readin_2b[100];
	unsigned int kmer_length_zijieshu = ((k + k) >> 2);
	unsigned int DNA_id = (address >> 7);
	unsigned int kmer_id_zijieshu = (kmer_id >> 2);
	unsigned int kmer_id_shengyuweishu = 2 * (kmer_id - 4 * kmer_id_zijieshu);
	filein = fopen(file_yssj, "rb");
	fseek(filein, (25 * DNA_id), 0);
	fread(readin_char, 25, 1, filein);
	for (int i = 0; i < 25; i++)
	{
		unsigned char temp = readin_char[i];
		readin_2b[4 * i + 3] = (temp & 3);
		temp = temp >> 2;
		readin_2b[4 * i + 2] = (temp & 3);
		temp = temp >> 2;
		readin_2b[4 * i + 1] = (temp & 3);
		temp = temp >> 2;
		readin_2b[4 * i] = (temp & 3);
	}
	for (unsigned int i = 0; i < length_of_char_from_user; i++)
	{
		unsigned char num = 0;
		switch (char_from_user[i])
		{
		case 'C':num++;
		case 'T':num++;
		case 'G':num++;
		}
		if (num == readin_2b[kmer_id + i])
			continue;
		else
			return;
	}
	OutPut(DNA_id, kmer_id);
	return;
}
int operator-(const timeval &t2, const timeval &t1)
{
	return ((t2.tv_sec-t1.tv_sec)*1000000+(t2.tv_usec-t1.tv_usec))/1000;
}
int main(void)
{
	timeval t1, t2;
	gettimeofday(&t1,nullptr);
	CompressEntry();
	gettimeofday(&t2,nullptr);
	cout << "数据重新编码完毕，耗时" << (int)(t2 - t1) << "毫秒" << endl;
	gettimeofday(&t1,nullptr);
	build_index();
	gettimeofday(&t2,nullptr);
	cout << "k="<<k<<"索引建立完毕，耗时" << (int)(t2 - t1) << "毫秒" << endl;
	fileout = fopen("res.csv", "a");
	cout << "索引建立完毕，请选择结果输出模式（输入数字并回车）" << endl;
	cout << "1.输出到控制台" << endl;
	cout << "2.输出到文件res.csv" << endl;
	cout << "3.同时输出到控制台和文件" << endl;
	cin >> mode;
	if ((mode > 3) || (mode < 0))
	{
		cout << "TYPE ERROR! RUN THIS PROGRAMMA AGAIN PLEASE." << endl;
		cin.get();/*Replace pause()*/
		exit(0);
	}
	unsigned int num;
	cout << "输入要查询的次数" << endl;
	cin >> num;
	unsigned char* temp = (unsigned char*)malloc(kk*sizeof(unsigned char));
	while (num--)
	{
		for (int i = 0; i < k; i++)
			cin >> temp[i];
		gettimeofday(&t1,nullptr);

		search_index(temp);
		gettimeofday(&t2,nullptr);
		cout << "查询并输出查询结果完毕，耗时" << (int)(t2 - t1) << "毫秒" << endl;
	}
	cin.get();/*Replace pause()*/
	return 0;
}