
#define _CARDS_CPP_

#ifndef _BASICDATA_CPP_ 
    #define _BASICDATA_CPP_
    #include "basicdata.cpp"
#endif

#ifndef _STRUCTION_CPP_ 
    #define _STRUCTION_CPP_
    #include "struction.cpp"
#endif

#ifndef _SKILLS_CPP_ 
    #define _SKILLS_CPP_
    #include "skills.cpp"
#endif

#ifndef _PROBABLITY_AND_CACULATION_CPP_ 
    #define _PROBABLITY_AND_CACULATION_CPP_
    #include "probablity_and_caculation.cpp"
#endif

/*��ʼ��*/void Plant::set_all(int plantnum,const char *name,const int a[],struct Skill skl,int map)
{
	int i,j; 
	/*  Hp ���� ���� ���� ���� ���� ���� ���� ���� ���� ��ֵ ���� ���� ˲ʱ �Ƚ� ��ǩ*/	
	this->name=name;
	this->plantnum=plantnum;
	HP_M=      a[0];
	if(map==Badland) 
		HP_M=(2*HP_M+1)/3;//ը��Ѫ������1 
	HP_L=        HP_M;
	attack_C=  a[1];
	if(map==Mansion)
		attack_C=3*attack_C/2;
	attack_A=    0;
	attack_R=  a[2];
	freeze_T=  a[3];
	freeze_P=  a[4];
	if(map==Tundra&&(tag&(FA|AL))==false)  
	{
		freeze_T+=1;
		freeze_P+=42;
	}		
	weaken=    a[5];
	defence_C= a[6];
	defence_A=   0;
	miss_P=    a[7]; 
	double_P=  a[8];
	if(map==Crimson_forest)  
		double_P*=3; 
	sputter=   a[9];                  
	value=     a[10];
	produce=   a[11]; 
	speed=     a[12]; 
	disposable=a[13]; 
	level=     a[14]; 
	tag=       a[15];
	if(	map==End_city)
	{
		miss_P+=83;
		if((tag&PD)!=0) /*ը����*/
		{
			if((tag&AL)!=0)
				tag-=AL;
			produce=0;
			attack_C=180;
			HP_M=HP_L=1;
			tag-=PD;
			tag|=BA;
			speed=0;
			disposable=1;			
		}
	}
	player_level_demand=a[16];
	for(i=0;i<SkillMax;i++)
	{ 
	    skill_avalible[i]=	skl.count[i];
	    skill_aim[i]=     	skl.aim[i];
	    skill_intensity[i]=	skl.intensity[i];
	    skill_favor[i]=		skl.favor[i];
		skill[i]=         	skl.use[i];
		for(j=0;j<AllSkills+1+4;j++)
			if(skill[i]==skillname[j].content)
			{
				skill_name[i]=skillname[j].name;
				break;
			}
	} 
	belong=NULL;  	
	last_aA=last_dA=0; 
	last_action=-speed/*��֤��һ��*/;
	explode_tick=disposable;
	return;
}
void Plant::belong_change(Player *p)
{ 
	belong=p;
	int i=plantnum;
	if(p==NULL)//��������
		plant[i].set_all(i,plantsname[i],ability[i],skill_temp[i],0);
	return; 
}

int Plant::attack(int T,int aim_tag)
{
	int att_P=(tag&ST)!=0 ?  Shoot_fly_P  :   (tag&CT)!=0 ?  Cast_fly_P  :   (tag&FT)!=0 ? Flat_fly_P  : Attack_fly_P ;
	int att_P_2=(tag&CT)!=0 ? Cast_cover_P  :	1000;
	if(  (  tag&  (FL|EA)  )==0  &&   (aim_tag&FL)!=0   )  //�Ƿ���(�ҷǵ��)�����
	    if(  iftrig(att_P)==0  ) 
	        return Fail_att;                    //δ���У�������0��ͬ 
	if(	 (aim_tag&CV)!=0   )  					//��Ҷ�ӱ���ɡ 
	    if(  iftrig(att_P_2)==0  ) 
	        return Fail_att;            
	int att=attack_C+attack_A;
	if(  (tag&MR)==0  &&   (aim_tag&MR)!=0   )  //��ˮ����ˮ�� 
	    att-=attack_R;         //��С���� 
	else
	    att=random(att,attack_R); 
	if(	(tag&DA)!=0  &&   (aim_tag&PD)!=0)	   //�ڰ������� 
		att=3*att/2; 
	if(att<0)
		att=0;
	else if(iftrig(double_P))
		att*=2;
	last_action=T;                              //ˢ���ж�ʱ�� 
	return att;                                 //���ص��ǹ����˺���С 
} 

int Plant::damage(int att,int att_kind,int *dam/*����ֵ��*/) 
{	
	if(att_kind!=REAL)//��ʵ�˺�ֱ�ӿ� 
	{
		if(iftrig(miss_P))
			return MISS;
		else
		    att=att-defence_C-defence_A;   //�����۳�		
	}
	if(att<0)
		att=0;
	if(*dam==DIDNOT)//��� 
		*dam=0;
	*dam+=att;//damֻ��¼������ 
	if(HP_L<=att) 
	{ 
		HP_L=0; 	
		return KILL;
	} 
	else
	{ 
		HP_L-=att;
		return HURT; 
	} 
}


void Plant::card_demon(int x,int y,int dT,int size)
{
	int dx=BIG_dx,dy=BIG_dy,small_dx=4;
	int bgc;//backgrond color
	int b=3;
	int i;
	int line;
	const int t=30;
	const int window_color=_White;
	const int blood_color=(disposable?_Blue:_Red|_Light);
    bool deadprint=false;
	switch(level)
	{
		case 2:  bgc=_Purple|White;     break;
		case 3:  bgc=_Yellow|_Light|Blue|Light;break;
		default :bgc=_Green |_Light|Blue;break;
	}
	if(size==SMA)
	{
		dx=SMA_dx;
		dy=SMA_dy;
		Dyearea(x,y,dx,dy,bgc);
		Color(_Black|White);Place(x,y);printf("%s",name);
	    Color(_Red|Yellow);Place(x,y+dy-3);printf("%3d",value);
	    line=x+1;
	    Color(bgc);
	    Place(++line,y+2);printf(" HP ��%3d",HP_M);
	    Place(++line,y+2);printf("������%3d",attack_C);
	    Place(++line,y+2);printf("������%3d",defence_C);
	    Place(++line,y+2);printf("(������Ϣ)"); 
		return;
	}
	Dyewindow(x,y,dx,dy,bgc,1,2,small_dx,window_color);
	GOTOHERE_DEAD:
	line=x+1+small_dx;
	if(deadprint)
		{Sleep(t);Dyeline(x,y,dy,bgc);}
	if(!deadprint||size!=EXP_BIG)
	{
		Color(_Black|White);Place(x,y);     printf("%s",name);
		Color(_Red|Yellow); Place(x,y+dy-3);printf("%3d",value);			
	}
	  if(deadprint)for(i=1;i<=5;i++){Sleep(t);Dyeline(x+i,y,dy,bgc);}
	if(!deadprint||size!=EXP_BIG)
    	Strip(line,y+2,HP_L,HP_M,dy-4,b,blood_color,_Black,bgc);//˲ʱ�Ϳ���Ѫ��Ϊ��ɫ
	if(deadprint)
	{
		Sleep(t);
		Dyeline(line+1,y,dy,bgc|White|Light);Place(++line,y+dy/2-2);
		printf("%s",  size==DEAD_BIG?  "DIED!"  :  (size==ICY_BIG?  "FROZEN!":"BOOM!"  )  );
	}
	else
	{
		Place(++line,y+dy/2);printf("HP");	
		if(disposable) 
		{
			Color(window_color|Blue);Place(line-2,y+dy/2-4);
			printf("����ʱ��%d",explode_tick-1);
		}
		else
		{
			Color(window_color|Red);Place(line-2,y+dy/2-6);
			if(speed!=Fast) 
				if(dT<0)
					printf("���ߵ���ʱ��%d",-dT);
				else
			    	printf("�������"); 
			else
				printf("�����ж��ٶ�"); 
		}
		Color(bgc);
	}
	  if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
	Place(++line,y+2);printf("������%3d����%2d��",attack_C,attack_R);
	if(attack_A!=0)
	    printf("%+3d",attack_A);
	  if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
	Place(++line,y+2);printf("������%3d",defence_C);
	if(defence_A!=0)
	    printf("% +3d",defence_A);
	  if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
	Place(++line,y+2); printf("���ʣ�%3d��",miss_P);
	  if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
	Place(++line,y+2); printf("���ʣ�%3d��",double_P);
	  if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
	Place(++line,y+2); 
	for(int i=0;i<dy-4;i+=2)
	    printf("��");
	if(produce!=0) 
	{
		if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
		Place(++line,y+2); printf("������%3d",produce);
	}
	if(freeze_T!=0)
	{
		if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
		Place(++line,y+2); printf("������%3d��%3d�룩",freeze_T,freeze_P);
	}
	if(weaken!=0) 
	{
		if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
		Place(++line,y+2); printf("������%3d",weaken);
	}
	if(sputter!=0) 
	{
		if(deadprint){Sleep(t);Dyeline(line+1,y,dy,bgc);}
		Place(++line,y+2); printf("���䣺%3d",sputter);
	}
	if(deadprint) while(line+1<=x+dx-1){Sleep(t);Dyeline(++line,y,dy,bgc);}
	Place(x+dx-1,y);
	tag_show(tag,1);
	if(  deadprint==false  &&  size!=BIG  &&  size!=SMA )
	{
		bgc=	size==DEAD_BIG?	_Light|White|Light	:	(  size==ICY_BIG?	 _Cyan|_Light|White|Light  :  _Black)	;
		deadprint=true;
		goto GOTOHERE_DEAD;
	}
	Color(_Black);
	return; 
}


