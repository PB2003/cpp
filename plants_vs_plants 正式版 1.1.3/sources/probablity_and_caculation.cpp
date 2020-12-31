
#define _PROBABLITY_AND_CACULATION_CPP_

#ifndef _COLOR_AND_PLACE_CPP_ 
    #define _COLOR_AND_PLACE_CPP_
    #include "color_and_place.cpp"
#endif

#ifndef _WINDOWS_H_ 
    #define _WINDOWS_H_
    #include<windows.h>
#endif

#ifndef DEF_TIME_H_  //如果前后为下划线不会包入 
    #define DEF_TIME_H_
    #include<time.h>
#endif

#define random(C,R)  	((C)+rand()%((R)+1)+rand()%((R)+1)-(R))     //产生C-R~C+R随机整数且近C概率高 
#define iftrig(P)    	((P)>rand()%1000)
#define max(a,b)	 	((a)>(b)?(a):(b))
#define elem(s)			(sizeof(s)/sizeof((s)[0]))

#define Ten	10
const char roman_n[Ten+1][sizeof("Ⅰ")]={"〇","Ⅰ","Ⅱ","Ⅲ","Ⅳ","Ⅴ","Ⅵ","Ⅶ","Ⅷ","Ⅸ","Ⅹ"};

int log_2(int x)
{
	int y=0;
	while((x>>=1)!=0)
	    ++y;
	return y;
}
#define Absent -3
int weighted_random(int *weight,int N)
{
	int S_weight[N+1]={0};
	int i;
	for(i=1;i<=N;i++)
	{
        S_weight[i]=S_weight[i-1]+weight[i-1];
    	rand();//增加随机性 
	}
	if(S_weight[N]==0)
		return Absent;
	else
	{
		int X=rand()%S_weight[N];
		for(i=0;i<N;i++)
	        if(  S_weight[i]<=X  &&  X<S_weight[i+1] )
		        return i;/*从0到N-1*/		
	}
}

void level_color(int L)
{
	switch(L)
	{
		case 5:
		case 6:Color(Light|Green);break; 
		case 7:Color(Light|Cyan);break;
		case 8:Color(Light|Purple);break;
		case 9:Color(Light|Red);break;
		case 10:Color(Light|Yellow);break;	
		default:Color(White|Light);	
	}
	return;
}
/*int main()
{
	int i,N=4,j,k;
	int w[4]={1,2,3,4};int a[4]={0};
	srand(time(NULL));
	for(k=0;k<10;k++) 
	{
	for(i=0;i<10000;i++)
	{
		j=weighted_random(w,N);
		//printf("%X ",rand()+(rand()<<15));
		a[j]++;
	}
	for(i=0;i<4;i++)
	{	
		printf("\na[%d】=%d ",i,a[i]);
	}printf("\n\n");}
}*/ 
