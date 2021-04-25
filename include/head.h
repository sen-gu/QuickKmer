#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<string>
#include"getpow4k.h"
#define fileread1 "solexa_100_170_1.fa"
#define fileread2 "solexa_100_170_2.fa"
#define file_yssj "data.dna"
#define kmer_id_inall  DNA_NUM*(100 - kk+1) + kmer_ID
void OutPut(unsigned int address);
void OutPut(unsigned int DNA_num, unsigned int kmer_num);
void check_and_OutPut(unsigned char* char_from_user, unsigned int length_of_char_from_user, unsigned int address);
void search_index(unsigned char*);
void build_index(void);
void ApplyTempMemory(void);
unsigned int get_HashVal(unsigned char *temp, unsigned int length);
void BuildIndexAndSort(void);
void ReadOriginDate(void);
void CompressEntry(void);
extern FILE *filein;
extern FILE *fileout;
extern unsigned int mode;