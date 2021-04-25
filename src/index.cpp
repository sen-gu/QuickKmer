#include "head.h"
using namespace std;
unsigned int Index[pow4k + 1];
unsigned int *TempKmer;
unsigned int *TempAddress;
unsigned int ResultAddress[1000000 * (100 - kk + 1)];
void ReadOriginDate(void)
{
	unsigned char readin_char[25];
	unsigned char readin_2b[100];
	filein = fopen(file_yssj, "rb");
	for (unsigned int DNA_NUM = 0; DNA_NUM < 1000000; DNA_NUM++)
	{
		/**************LOAD READIN_CHAR START*************************************/
		for (int i = 0; i < 25; i++)
		{
			readin_char[i] = fgetc(filein);
			unsigned char temp = readin_char[i];
			readin_2b[4 * i + 3] = (temp & 3);
			temp = temp >> 2;
			readin_2b[4 * i + 2] = (temp & 3);
			temp = temp >> 2;
			readin_2b[4 * i + 1] = (temp & 3);
			temp = temp >> 2;
			readin_2b[4 * i] = (temp & 3);
		}
		/**************LOAD READIN_CHAR END*************************************/
		for (unsigned int kmer_ID = 0; kmer_ID < 100 - kk + 1; kmer_ID++)
		{
			unsigned int SingleKmer = 0;
			for (int i = 0; i < kk; i++)
			{
				SingleKmer = SingleKmer << 2;
				SingleKmer = (SingleKmer | readin_2b[i + kmer_ID]);
			}
			TempKmer[kmer_id_inall] = SingleKmer;
			TempAddress[kmer_id_inall] = ((DNA_NUM << 7) | kmer_ID);
		}

	}
	fclose(filein);
}
void BuildIndexAndSort(void)
{
	unsigned int *IndexCount = (unsigned int*)malloc(pow4k*sizeof(unsigned int));
	unsigned int *p_kmer = TempKmer;
	for (unsigned int i = 0; i < pow4k; i++)
	{
		IndexCount[i] = 0;
	}
	for (unsigned int i = 0; i < 1000000 * (100 - kk + 1); i++)
	{
		IndexCount[*p_kmer]++;
		p_kmer++;
	}
	p_kmer = NULL;
	Index[0] = 0;
	for (unsigned int i = 1; i < pow4k; i++)
	{
		Index[i] = (Index[i - 1] + IndexCount[i - 1]);
	}
	p_kmer = (unsigned int*)malloc(pow4k*sizeof(unsigned int));//更改变量用途，p_kmer可看做Index_temp
	for (unsigned int i = 0; i < pow4k; i++)
	{
		p_kmer[i] = Index[i];
	}
	for (unsigned int i = 0; i < 1000000 * (100 - kk + 1); i++)
	{
		unsigned int temp = (p_kmer[TempKmer[i]]);
		ResultAddress[temp] = TempAddress[i];
		p_kmer[TempKmer[i]]++;
	}
	free(p_kmer);
	free(IndexCount);
	return;
}
unsigned int get_HashVal(unsigned char *temp, unsigned int length)
{
	unsigned int res = 0;
	for (unsigned int i = 0; i < length; i++)
	{
		if (*temp == 'A')
		{
			res = res << 2;
		}
		if (*temp == 'G')
		{
			res = res << 2;
			res = (res | 1);
		}
		if (*temp == 'T')
		{
			res = res << 2;
			res = (res | 2);
		}
		if (*temp == 'C')
		{
			res = res << 2;
			res = (res | 3);
		}
		temp++;
	}
	return res;
}
void ApplyTempMemory(void)
{
	TempKmer = (unsigned int*)malloc(1000000 * (100 - kk + 1)*sizeof(unsigned int));
	TempAddress = (unsigned int*)malloc(1000000 * (100 - kk + 1)*sizeof(unsigned int));
	if ((TempKmer == NULL) || (TempAddress) == NULL)
	{
		cout << "ERROR";
		exit(0);
	}
}
void build_index(void)
{
	ApplyTempMemory();
	ReadOriginDate();
	BuildIndexAndSort();
	free(TempKmer);
	free(TempAddress);
}
void search_index(unsigned char* pch)
{
	unsigned int num_ = get_HashVal(pch, kk);
	unsigned int *p_s = &ResultAddress[Index[num_]] - 1;
	unsigned int *p_e = &ResultAddress[Index[num_ + 1]] + 1;
	while ((++p_s) != p_e)
	{
		unsigned int tempp = *p_s;
		if (k>11)
		{
			check_and_OutPut(pch, k, tempp);
		}
		else
		{
			unsigned int DNA_num = (tempp >> 7);
			unsigned int kmer_num = (tempp & 0x7F);
			OutPut(DNA_num, kmer_num);
		}
	}
}
