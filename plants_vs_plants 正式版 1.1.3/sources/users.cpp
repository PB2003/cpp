
#define _USERS_CPP

#ifndef _COLOR_AND_PLACE_CPP_ 
    #define _COLOR_AND_PLACE_CPP_
    #include "color_and_place.cpp"
#endif

#ifndef _BASICDATA_CPP_ 
    #define _BASICDATA_CPP_
    #include "basicdata.cpp"
#endif

#define ArchMax 9

#define ThingsMax 	22
#define The_clover 	7
#define The_medel 	8
#define The_fruit 	9
#define The_leaf 	10
#define The_flower 	11
#define The_ice 	12
#define The_emerald	13
#define The_ingot	14
#define The_perl 	15
#define The_map		16
#define The			17
#define The_potion	18
#define The_boots	19
#define The_sword	20
#define The_shield	21
const char thingname[ThingsMax][sizeof("������֮Ҷ")]=
{
	"��ɫ��Ƭ", "��ɫ��Ƭ", "��ɫ��Ƭ", "��ɫ��Ƭ", 
	"��ɫ��Ƭ", "��ɫ��Ƭ", "��ɫ��Ƭ", "��Ҷ��ޣ", 
	"��������", "�߲ʽ���", "������֮Ҷ", "������֮��",
	"����","�̱�ʯ","�½�Ͻ�","ĩӰ����", 
	"�׳ǵ�ͼ","���ɺϳ�","������ҩ","��Ų��ѥ",
	"�����ؽ�","��ջ���"
};
#define Battle_temps 6
#define Self_Ctrl_temps 6
#define INFOKIND 8 
const int	statistic[INFOKIND]=	{Battle_temps	,ArchMax	,ThingsMax	,Locked_plants	,pros	,pros	,3,Self_Ctrl_temps};
	//��Ϣ�Ĵ洢Ϊ��<����>#<����>#<���>#<ǩ��>#<��߷�>^<�ܻ�ɱ>^<������>^<������>^
	//				#<�ɾ�1>^...#<��Ʒ1>^...#<����ֲ��1>^...#<�Զ���ֲ������1>^...#<Ĭ��ս������1...>#<�Զ����Ƿ���>#<�鿴���˿���> 
const int default_ctrl[Self_Ctrl_temps]={0,0,0,1,1,0};
const int default_battle[3]={4,3,NORMAL};
class User
{
	public:
		char name			[NameLenthMax];	//�û��� 				
		int battle_temp		[Battle_temps];	//ս��ͳ����/*highest_point,tt_kill,tt_miss,tt_prod,ice&fire,fire_city_pass*/
		int archiv			[ArchMax];		//�ɾͻ�ȡ 
		int all_have		[ThingsMax];	//�ֿ�����Ʒ/*0~6��ɫ��Ƭ��7�������¡�8��Ҷ��ޣ��9�߲ʽ�����10������֮Ҷ��11������֮��*/
		int unlocked		[Locked_plants];//�ѽ�������ؿ��� 
		int DIY_temp[2]		[pros];	//�Զ��忨������(��������)
		int default_battle_temp[3];//���������������Ѷ� 
		int self_ctrl		[Self_Ctrl_temps];
			#define adapt_selfdef 			0
			#define isOthersCardsVisible 	1 
			#define pierce					2
			#define isOthersObjSkillUseful	3
			#define isOthersSideSkillUseful	4
			#define controlable				5
		const int*	p_statistic[INFOKIND];/*�ڶ�ȡ��Ϣ�г�ʼ��*/
	    void new_user					(char *name0,char *pswd);
	    void get_users_information		(char *name0);
	    void record_users_information	();
	    void password_alter				();
	    void log_off					(bool save);
	    void unlock						(int unlock_number)		{unlocked[unlock_number]=1;return;}
	    int achi_comp					(int i)					{return archiv[i]+=1;}
		int check_in					()						{last_ck=time(NULL);record_users_information();return last_ck;}
		void set_default(int K,int start_cards,int hard) 
		{
			default_battle_temp[0]=K;
			default_battle_temp[1]=start_cards;
			default_battle_temp[2]=hard;
			record_users_information();
		}
		int flush(const char *information,int new_n)
		{
			if(strcmp(information,"highest_point")==0)		return battle_temp[0]=new_n;
			system("pause");return 0;//���������� 
		}
	    int add(const char *information,int add_num)
    	{
			if(strcmp(information,"coins")==0)        		return coins+=add_num,add_num;
			else if(strcmp(information,"exp")==0)			return exp+=add_num,add_num;
			else if(strcmp(information,"tt_kill")==0)		return battle_temp[1]+=add_num,add_num;
			else if(strcmp(information,"tt_miss")==0)		return battle_temp[2]+=add_num,add_num;
			else if(strcmp(information,"tt_prod")==0)		return battle_temp[3]+=add_num,add_num;
			else if(strcmp(information,"ice&fire")==0)		return battle_temp[4]+=add_num,add_num;
			else if(strcmp(information,"fire_city_pass")==0)return battle_temp[5]+=add_num,add_num;
			else if(strcmp(information,"building")==0)		return building+=add_num,add_num;
			else system("pause");
			return 0;//���������� 
		}
	    int get(const char *information)
		{
			if(strcmp(information,"coins")==0)        			return coins;
			else if(strcmp(information,"exp")==0)				return exp;
			else if(strcmp(information,"level")==0)				return level_get(1);
			else if(strcmp(information,"last_ck")==0)  			return last_ck;
			else if(strcmp(information,"highest_point")==0)		return battle_temp[0];
			else if(strcmp(information,"tt_kill")==0)			return battle_temp[1];
			else if(strcmp(information,"tt_miss")==0)			return battle_temp[2];
			else if(strcmp(information,"tt_prod")==0)			return battle_temp[3];
			else if(strcmp(information,"ice&fire")==0)			return battle_temp[4];
			else if(strcmp(information,"building")==0)			return building; 
			else if(strcmp(information,"default_K")==0)			return default_battle_temp[0];
			else if(strcmp(information,"default_start_cards")==0)return default_battle_temp[1];
			else if(strcmp(information,"default_hard")==0)		return default_battle_temp[2];
			else if(strcmp(information,"color")==0)
				{int L=level_get(1);return L>=4?(L>=6?(L>=8?(L>=9?(L>=10?_Yellow|_Light:_Yellow):_Red|_Light):_Cyan|_Light):_Green|_Light):_White|_Light;}        
			else if(strcmp(information,"unlocked")==0) 			return 0;
			else system("pause");
			return 0;//���������� 
		}
		int have(int thing)										{return all_have[thing];}
	    int level_get(int L)   									{return exp>=exp_demand[L-1]?(L==MaxLevel?MaxLevel:level_get(L+1)):L-1;}
	    void obtain(int thing_No,int num)						{all_have[thing_No]+=num;return;}//�����ɸ� 
	private:
		int exp;							//����ֵ 
		int coins;							//������� 
		int last_ck;						//�ϴ�ǩ��ʱ��
	public:	int building;						//ʩ������
		int at;		
}; 

int archiv_demand[ArchMax]={10,100,5000};

bool find_user(char* name) 
{
	FILE *fp;
	if((fp=fopen("system\\all_users.txt","r"))==NULL)
		system("pause");
	char existed[UNameMax];
	char *p;
	do
	{
		p=existed;
		while((*p++ = fgetc(fp))!=MARK)
			if(feof(fp))
			{
				fclose(fp);
				return false; 
			}
		*(p-1)='\0';
	}
	while(strcmp(name,existed)!=0);
	fclose(fp);
	return true;
}
void make_file(char* name,char* path)
{
	strcat(path,"users\\");
	strcat(path,name);
	strcat(path,".txt");
	return;
}
bool find_pswd(char* name,char* pswd) 
{
	FILE *fp;
 	char path[UNameMax+10]={0};
 	make_file(name,path);
	if((fp=fopen(path,"r"))==NULL)
		system("pause");
	char existed_pswd[UNameMax];
	char *p=existed_pswd;
	while((*p++ = fgetc(fp))!=MARK)
		if(feof(fp))
		{
			fclose(fp);
			return false; 
		}
	*(p-1)='\0';
	fclose(fp);
	if(strcmp((const char *)pswd,(const char *)existed_pswd)==0)
		return true;
	else
		return false;
}

void User::get_users_information(char *name0)
{
	p_statistic[0]=battle_temp;
	p_statistic[1]=archiv;
	p_statistic[2]=all_have;
	p_statistic[3]=unlocked;
	p_statistic[4]=DIY_temp[0];
	p_statistic[5]=DIY_temp[1];
	p_statistic[6]=default_battle_temp;
	p_statistic[7]=self_ctrl;
	FILE *fp;
	int i,j;
	char path[NameLenthMax]={0};
	strcpy(name,name0);
	make_file(name0,path);
	if((fp=fopen(path,"r"))==NULL)
		system("pause");
	while(fgetc(fp)!=MARK);//�������� 
	fscanf(fp,"%d",&exp);//���� 
	while(fgetc(fp)!=MARK);
	fscanf(fp,"%d",&coins);//��� 
	while(fgetc(fp)!=MARK);
	fscanf(fp,"%d",&last_ck);//ǩ�� 
	while(fgetc(fp)!=MARK);
	fscanf(fp,"%d",&building);//�������� 
	while(fgetc(fp)!=MARK);
	fscanf(fp,"%d",&at);//�ص� 
	while(fgetc(fp)!=MARK);
	for(i=0;i<INFOKIND;i++)
	{
		j=0;
		do
			fscanf(fp,"%d",	p_statistic[i]	+	(j++)	);
		while(fgetc(fp)!=MARK);
	}
	fclose(fp);
	return;
}
void User::record_users_information()
{
	FILE *fp; 
	int i,j;
	char path[NameLenthMax]={0};
	make_file(name,path);	
	if((fp=fopen(path,"r+"))==NULL)
		system("pause");
	while(fgetc(fp)!=MARK);//��������
	fseek(fp,0,SEEK_CUR); 
	fprintf(fp,"%d%c%d%c%d%c%d%c%d%c",exp,MARK,coins,MARK,last_ck,MARK,building,MARK,at,MARK);
	for(i=0;i<INFOKIND;i++)
		for(j=0;j<statistic[i];j++)	
			fprintf(fp,"%d%c",p_statistic[i][j]	,  (j!=statistic[i]-1)  ?  INTERVAL  :  MARK  );
	fclose(fp);
	return;
}
void User::new_user(char *name0,char *pswd)
{
	FILE *fp;
	int i,j;
	char path[NameLenthMax]={0};
	strcpy(name,name0);
	make_file(name0,path);
	if((fp=fopen(path,"w"))==NULL)//�������û��ļ� 
		system("pause");
	fprintf(fp,"%s%c",pswd,MARK); 
	fprintf(fp,"%d%c%d%c%d%c%d%c%d%c",0/*exp*/,MARK,0/*coins*/,MARK,0/*last_ck*/,MARK,0/*building*/,MARK,0/**/,MARK);
	for(i=0;i<INFOKIND;i++)
	{
		if(i==4||i==5)
			for(j=0;j<statistic[i];j++)
				fprintf(fp,"%d%c",j<Properties?ability[75/*�Զ����㶹����*/][j]:0,  (j!=statistic[i]-1)  ?  INTERVAL  :  MARK  );
		else if(i==7)
			for(j=0;j<statistic[i];j++)
				fprintf(fp,"%d%c",default_ctrl[j]	,  (j!=statistic[i]-1)  ?  INTERVAL  :  MARK  );
		else if(i==6)
			for(j=0;j<statistic[i];j++)	
				fprintf(fp,"%d%c",default_battle[j]	,  (j!=statistic[i]-1)  ?  INTERVAL  :  MARK  );
		else
			for(j=0;j<statistic[i];j++)	
				fprintf(fp,"%d%c",		0			,  (j!=statistic[i]-1)  ?  INTERVAL  :  MARK  );
	}
	fclose(fp);
	if((fp=fopen("system\\all_users.txt","r+"))==NULL)
		system("pause");
	while(fgetc(fp)!=ADD);
	fseek(fp,-1,SEEK_CUR);
	fprintf(fp,"%s%c%c",name0,MARK,ADD);//�ܵǼ�	
	fclose(fp);
	return;
} 
bool last_user(User *p_user)
{
	FILE *fp;
	if((fp=fopen("system\\last_user.txt","r"))==NULL)
		system("pause");
	if(fgetc(fp)!=MARK)
	{
		fclose(fp);
		return false;
	}
	else
	{
		char *p=p_user->name;
		while((*p++=fgetc(fp))!=MARK);
		*(p-1)='\0';
		fclose(fp);
		p_user->get_users_information(p_user->name);
		return true;			
	}
}
void User::log_off(bool save)
{
	FILE *fp;
	record_users_information();//��ֹ��Ϣ��ʧ 
	if((fp=fopen("system\\last_user.txt","w"))==NULL) 
		system("pause");	
	if(save)
		fprintf(fp,"%c%s%c",MARK,name,MARK);	
	else
		fprintf(fp,"%c%c",NO,MARK);
	fclose(fp);
	return;
}




























