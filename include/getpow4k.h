#define k 13
#if (k==0)
#define  pow4k 1
#elif(k==1)
#define pow4k 4
#elif(k==2)
#define pow4k 16
#elif(k==3)
#define pow4k 64
#elif(k==4)
#define pow4k 256
#elif(k==5)
#define pow4k 1024
#elif(k==6)
#define pow4k 4096
#elif(k==7)
#define pow4k 16384
#elif (k==8)
#define pow4k 65536
#elif(k==9)
#define pow4k 262144
#elif(k==10)
#define pow4k 1048576
#else
#define pow4k 4194304
#endif
#if(k<11)
#define kk k
#else
#define kk 11
#endif
#if(k<12)
#define pow4kk pow4k
#elif(k==12)
#define pow4kk 16777216
#elif(k==13)
#define pow4kk 67108864
#elif(k==14)
#define pow4kk 268435456
#elif(k==15)
#define pow4kk 1073741824
#endif
	
