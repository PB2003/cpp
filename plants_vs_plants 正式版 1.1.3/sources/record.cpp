
#define _RECORD_CPP_ 

#ifndef _STRUCTION_CPP_ 
    #define _STRUCTION_CPP_
    #include "struction.cpp"
#endif

#ifndef _BASICDATA_CPP_ 
    #define _BASICDATA_CPP_
    #include "basicdata.cpp"
#endif

void record_init()
{
	FILE *fp;
	int i;
	if((fp=fopen("system\\record.txt","w"))==0)
		system("pause");
	for(i=0;i<MaxRecord;i++)//消耗掉 
		fprintf(fp,"%s%c%d%c","nobody",INTERVAL,0,MARK);
	fclose(fp);
	return;
} 
void get_record(int N,int *points,char (*name)[NameLenthMax])
{
	FILE *fp;
	if((fp=fopen("system\\record.txt","r"))==0)
		system("pause");
	int i;
	for(i=0;i<N;i++)
	{
		char *p=name[i];
		while((*p++=fgetc(fp))!=INTERVAL);
		*(p-1)='\0';
		fscanf(fp,"%d",points+i);
		while(fgetc(fp)!=MARK);
	}
	fclose(fp);
	return;
}
void new_record(int new_points,char *new_name)
{
	FILE *fp;
	int points[MaxRecord];
	char  name[MaxRecord][NameLenthMax];
	get_record(MaxRecord,points,name);
	int i=MaxRecord,j;
	int useless;
	while(  i>=1  &&  new_points>points[i-1])
		--i;
	if((j=i)!=MaxRecord)//刷新纪录
	{
		if((fp=fopen("system\\record.txt","r+"))==0)
			system("pause");
		for(i=0;i<j;i++)//消耗掉 
		{
			while(fgetc(fp)!=INTERVAL);
			fscanf(fp,"%d",&useless);
			while(fgetc(fp)!=MARK);
		} 
		fseek(fp,0,SEEK_CUR);
		fprintf(fp,"%s%c%d%c",new_name,INTERVAL,new_points,MARK);
		while(i<MaxRecord-1)
			{
				fprintf(fp,"%s%c%d%c",name[i],INTERVAL,points[i],MARK);
				i++;
			}
		fputc('\0',fp);//舍掉最后一个纪录
		fclose(fp);		
	} 
	return;
}
void record(PW w)
{
	int i;
	int points[MaxRecord];
	char  name[MaxRecord][NameLenthMax];
	get_record(MaxRecord,points,name);
	w.newpage();
	w.hint(1,sizeof("高分榜"),"高分榜"); 
	int s1[w.set_btnN(3)][4];
	w.s1_link(s1);
	int line=3;
	for(i=0;i<MaxRecord;i++)
	{
		w.RPlace(line+=2,25);printf("%d\t\t\t%s\t\t\t%d",i+1,name[i],points[i]);
	}
	w.end_setall("确定");
	w.do_action();
	return;
}
