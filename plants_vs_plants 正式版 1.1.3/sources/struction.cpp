
#define _STRUCTION_CPP_

#ifndef _COLOR_AND_PLACE_CPP_ 
    #define _COLOR_AND_PLACE_CPP_
    #include "color_and_place.cpp"
#endif

#ifndef  _PICTURE_CPP_ 
    #define  _PICTURE_CPP_
    #include "picture.cpp"
#endif

#ifndef _BASICDATA_CPP_ 
    #define _BASICDATA_CPP_
    #include "basicdata.cpp"
#endif

#ifndef _PROBABLITY_AND_CACULATION_CPP_ 
    #define _PROBABLITY_AND_CACULATION_CPP_
    #include "probablity_and_caculation.cpp"
#endif

#ifndef _USERS_CPP_ 
    #define _USERS_CPP_
    struct BOOK;
    #include "users.cpp"
#endif

POINT p;

struct EFFECT;
class Player;
class Plant;

#define ALL 0
#define ONLYNUM 1
#define SPECIAL 2	

const int everyL=15;
const int lts=26;
const int no_num=50;
const int keys=no_num+10;

typedef union {int d;double lf;char c;char s[NameLenthMax];} VaryType;
VaryType keyboard(VaryType *value,int x,int y,int input_x,int input_y,int color,int mode);

typedef int SKILL_t; 
typedef SKILL_t (STD_SKILL)(int P,int T,int K,int aim,Player *doer,EFFECT *E);

struct TXTF
{
	void newtxtf(int x,int y,int dx,int dy,int side,int dftc)
	{
		this->x=x;
		this->y=y;
		this->dx=dx;
		this->dy=dy;
		this->side=side; 
		line=x+side;
		Dyearea(x,y,dx,dy,dftc);
		return;	
	}
	void say(const char *information)
	{
		Place(line++,y+side*2);printf(information);//�Զ����� 
		return;
	}
	private:
		int x;
		int y;
		int dx;
		int dy;
		int side;
		int line;
		int dftc;
};

TXTF tf;//ȫ�ļ����� 

struct BTN/*button*/
{
	int area[4];/*������*/
	int coor[4];/*С����*/ 
	bool jud;   /*�����о�*/
	/*Ϊ��֤�����ԣ�������txt*/
	void judset(bool JUD)
	{
		jud=JUD?true:false; 
		return;
	}
	void set(int x,int y,int dx,int dy,int coor_store_array[4]) 
	{
		int i;
		area[xmin]=x;
		area[xmax]=x+dx;
		area[ymin]=y;		
		area[ymax]=y+dy;
		precise_coord(area,coor,0);
		for(i=0;i<4;i++)
		    coor_store_array[i]=coor[i];
	}
	void dye(const char *txt)  {StdButton(area,jud,txt);return;}
};

struct INP_BAR
{
	int x;
	int y;
	int lenth;
	int dftc;
	int kbd_x,kbd_y; 
	VaryType search;
	BTN inp_btn;
	void newtxt(const char *txt)
	{
		Dyeline(x,y,lenth,dftc);Place(x,y);	
		printf("%s",txt);
		return;		
	}
	void setall(const char *txt,int coor_store_array[4])
	{
		const int std_h=1; 
		kbd_x=Max_dx-14;
		kbd_y=58;
		inp_btn.judset(true);
		inp_btn.set(x,y,std_h,lenth,coor_store_array);Dyeline(x,y,lenth,dftc);Place(x,y);
      	newtxt(txt);
		return;
	}
	bool putin(char format)
	{
		Dyeline(x,y,lenth,dftc);
		Color(dftc);Place(x,y);	
		if(format=='s')
		{    
			char *p=search.s;
			while(*p++=getchar())
			{
				char c=*(p-1);
				if(c=='\n'||c=='\0')
				{ 
					*(p-1)='\0'; 
					return true;
				}
				else if(c==' ')//���� 
					p--; 
				else if(c==MARK||c==INTERVAL||c==ADD||c==NO)//�Ƿ����� 
				    return false;
			}
		}
		else if(format=='c')			
			search.c=getchar();
		else if(format=='d')			
			scanf("%d",&search.d);
		else 
			system("pause");
		return true;
	}
	bool putin_vk(char format)
	{
		Dyeline(x,y,lenth,dftc);Place(x,y);
		keyboard(&search,kbd_x,kbd_y,x,y,dftc,format=='s'?ALL:ONLYNUM);
		if(format=='s')
		{
			char *p=search.s;
			char c;
			while(c=*p++)
				if(c==MARK||c==INTERVAL||c==ADD||c==NO)//�Ƿ����� 
				    return false;
		}
		return true;
	}
	void clearboard(int clearcolor)
	{
		Dyearea(kbd_x,kbd_y,14,96,clearcolor);	
		return;		
	}	 
};

struct PW/*pop window*/ 
{
	int x;
	int y;
	int dx;
	int dy;
	int dftc;/*defalt color����������������*/;
	bool aut;/*ϵͳ�Զ�*/ 
	
	BTN  end_btn;/*Ĭ�ϵİ�ť*/
	int action;
	int btnN;
	int (*inner_s1)[4];
	void newpage()/*clear window*/                                        			{Dyearea(x,y,dx,dy,dftc);return;}
	void hint    (int rela_x,int real_sizeof_message,const char*message) 			{Color(dftc);Place(x+rela_x,y+(dy-real_sizeof_message)/2);printf("%s",message);return;}
	void spe_hint(int rela_x,int real_sizeof_message,const char*message,int color) 	{Color(color);Place(x+rela_x,y+(dy-real_sizeof_message)/2);printf("%s",message);return;}
	void newline (int rela_x,int real_sizeof_message,const char*message)			{Dyeline(x+rela_x,y,dy,dftc);Place(x+rela_x,y+(dy-real_sizeof_message)/2);printf("%s",message);return;}
	void RPlace  (int rela_x,int rela_y)                                 			{Place(x+rela_x,y+rela_y);return;}
	void end_setall(const char *txt)
	{
		end_btn.set(  x+dx-Stdheight-1  ,  y+(dy-Stdwidth)/2  ,  Stdheight  ,  Stdwidth   ,  inner_s1[btnN-1]/*�涨�ð�ť����Ϊ���һ��*/);
		end_btn.judset(true);
		end_btn.dye(txt);
		return;
	}
	int set_btnN(int total_number_of_buttons)    {return btnN=total_number_of_buttons;}
	void s1_link(int s1[][4])                    {inner_s1=s1;return;}
	int do_action()
	{
	    return action=Effective(p,inner_s1,btnN,true,Notcount,Std_flush_period,false);
    }
    void do_confirm(int max_wait_time)/*ֻǣ��end_btn*/
    {
		Effective(p,&end_btn.coor,1,true,max_wait_time,Std_flush_period,false);
		return;
	}
};

struct BOOK/*���PW����ȥ��bool aut��һ��Ϊ��Ҳ��������޸�newpage����������page��*/ 
{
	int x;
	int y;
	int dx;
	int dy;
	int dftc;/*defalt color����������������*/;
	
    int maxpage;
    int page; 
	BTN end_btn;/*Ĭ�ϵİ�ť*/
	BTN page_btn[2];/*Ĭ�ϵķ�ҳ��ť*/
	int action;
	int btnN;
	int (*inner_s1)[4];
	void newpage(int value_of_maxpage,int value_of_page)/*clear windowͬʱ�趨��page��maxpage*/   {Dyearea(x,y,dx,dy,dftc);maxpage=value_of_maxpage;page=value_of_page;return;}
	void hint   (int rela_x,int real_sizeof_message,const char*message) {Color(dftc);Place(x+rela_x,y+(dy-real_sizeof_message)/2);printf("%s",message);return;}
	void newline(int rela_x,int real_sizeof_message,const char*message) {Dyeline(x+rela_x,y,dy,dftc);Place(x+rela_x,y+(dy-real_sizeof_message)/2);printf("%s",message);return;}
	void RPlace (int rela_x,int rela_y)                                 {Place  (x+rela_x,y+rela_y);return;}
	void end_setall(const char *txt)
	{
		end_btn.set(  x+dx-Stdheight-1  ,  y+(dy-Stdwidth)/2  ,  Stdheight  ,  Stdwidth   ,  inner_s1[btnN-1]/*�涨�ð�ť����Ϊ���һ��*/);
		end_btn.judset(true);
		end_btn.dye(txt);
		return;
	}
	void page_setall(int page_btn_rela_x,int page_btn_rela_y)
	{
		page_btn[0].judset(  page>1        );
	    page_btn[1].judset(  page<maxpage  );
	    page_btn[0].set( x+page_btn_rela_x , y+page_btn_rela_y              ,  Stdheight  ,  Stdwidth  ,inner_s1[btnN-3]/*�涨�ð�ť����Ϊ������3��*/);
	    page_btn[1].set( x+page_btn_rela_x , y+dy-page_btn_rela_y-Stdwidth  ,  Stdheight  ,  Stdwidth  ,inner_s1[btnN-2]/*�涨�ð�ť����Ϊ������2��*/);
        page_btn[0].dye("��һҳ");
        page_btn[1].dye("��һҳ");
		Color(dftc);RPlace(page_btn_rela_x+1,(dy-sizeof("��0ҳ/��0ҳ"))/2);
		printf("��%dҳ/��%dҳ",page,maxpage);
		return;
	}
	int set_btnN(int total_number_of_buttons){return btnN=total_number_of_buttons;}
	void s1_link(int s1[][4])                {inner_s1=s1;return;}
	int do_action()//���ҷ�ҳ����ֱ�Ӱ�����
	{
		do
	    {
			action=Effective(p,inner_s1,btnN,true,1,Std_flush_period,false);
			if     (IfpushLeft)  	action=btnN-3;		   
			else if(IfpushRight)    action=btnN-2;
		}
		while(  (action==Fail)  ||  (action==btnN-3&&page_btn[0].jud==false)  ||  (action==btnN-2&&page_btn[1].jud==false)  );
		return action; 
    }
    void do_confirm(int max_wait_time)/*ֻǣ��end_btn*/
    {
		Effective(p,&end_btn.coor,1,true,max_wait_time,Std_flush_period,false);
		return;
	}
};

class Plant
{
	public:
		const char 	*name;							//ֲ������ 
		int 		plantnum;						//ֲ���� 
		Player     	*belong;						//������� 
		STD_SKILL	*skill[SkillMax];				//����ָ�� 
		const char  *skill_name[SkillMax];			//�������� 
 		int         skill_avalible[SkillMax];	    //����[i]��Ӧ���ܸ���[i]
 		int			skill_aim[SkillMax];			//������Ե�Ŀ������ 
 		int			skill_intensity[SkillMax];		//����ǿ�ȣ��ȼ��� 
 		int			skill_favor[SkillMax];		//����ǿ�ȣ��ȼ��� 
		Plant()  {/*printf("���캯��\n");*/} 
		~Plant() {/*printf("��������\n");*/}
		//��ʼ��   
		    void set_all(int plantnum,const char *name,const int a[],struct Skill sk,int map);
		//��ʾ
		    void card_demon(int x,int y,int dT,int size);
			void skill_demon(const char *information,int skill_No)       
			{
				if(strcmp(information,"name")==0)
				{
					if(skill[skill_No]!=NULL)
						printf("%s%s",skill_name[skill_No],roman_n[	skill_intensity[skill_No]	]);
				}
				else if(strcmp(information,"avalible")==0)
				{
					if(skill[skill_No]!=NULL)
						switch(skill_avalible[skill_No])
						{
							case Passive	:printf("������");break;
							case Passive_S	:printf("������");break;
							case Always 	:printf("������");break;
							case Adjunct	:printf("���Ӽ�");break;
							case 0			:break;
							default:
								if(skill_avalible[skill_No] >=100)	printf("ʣ�����������"); 
								else								printf("ʣ�������%d",skill_avalible[skill_No]);
						}
				}
				else if(strcmp(information,"describe")==0)
				{
					if(skill[skill_No]!=NULL)
						;//���� 
				}
				else system("pause");return;//����������
				return;
			}  
        //�����ຯ��
		    int attack(int T,int aim_tag);		    
			#define Fail_fre 0
		    int freeze(int aim_tag)				{return (iftrig(freeze_P))? (  (aim_tag&FA)==0?  freeze_T :  Fail_fre)  :  0  ;}   //�����Ͳ��ܱ��� 
		    int sun_produce(int T) 				{last_action=T;return produce;}
		    bool tick()							{return disposable!=0/*�۶ϱ���*/&&--explode_tick==0;  }
		    bool if_go_exploding()				{return disposable!=0/*�۶ϱ���*/&&explode_tick==0;  }
		    bool if_havenot_explode()			{return disposable!=0/*�۶ϱ���*/&&explode_tick!=0;  }
		    int skill_use(int i,int T)			{last_action=T;/*ˢ���ж�ʱ��*/return skill_avalible[i]<0?skill_avalible[i]/*���޴�*/:(--skill_avalible[i]);}
		//�޸��ຯ��
		    int add(const char *information,int num)
			{
				if(strcmp(information,"attack")==0)         	return attack_C+=num;
				else if(strcmp(information,"defence")==0)       return defence_C+=num;
				else if(strcmp(information,"sputter")==0)		return sputter+=num;
				else if(strcmp(information,"produce")==0) 		return produce+=num;
				else if(strcmp(information,"speed")==0)			return speed+=num;
				else if(strcmp(information,"freeze_T")==0)		return freeze_T!=0?freeze_T+=num:0;
				else if(strcmp(information,"miss_P")==0)		return miss_P+=num;
				else system("pause");
				return 0;//���������� 
			}
 		    int defence_clear()								{return defence_C=0;}
		    int double_P_clear()							{return double_P=0;}
		    int HP_modify(const char *information,int num)
		    {
				if(strcmp(information,"gain")==0)         		return HP_L+=num;
				else if(strcmp(information,"boost")==0)         return HP_M+=num;
				else if(strcmp(information,"expand")==0)        return HP_M+=num,HP_L+=num;
				else if(strcmp(information,"full")==0)         	return HP_L=HP_M;
				else system("pause");
				return 0;//����������
			}
			void last_action_T_reset(int T)		{last_action=T+1-speed-!(!disposable)/*0or1*/;}
		//�����ຯ�� 
		    int damage(int att,int att_kind,int *dam);
			void belong_change(Player *p);        
		    void strenth(int A,int deltaT)     	{attack_A= deltaT<0?0:A;return;} 
            void shield (int A,int deltaT)     	{defence_A=deltaT<0?0:A;return;}     
        //getϵ�к���
		    int get(const char *information)
			{
				if(strcmp(information,"HP_M")==0)         		return HP_M;
				else if(strcmp(information,"HP_L")==0)         	return HP_L;
				else if(strcmp(information,"attack average")==0)return attack_C+attack_A;
				else if(strcmp(information,"attack least")==0) 	return attack_C+attack_A-attack_R;
				else if(strcmp(information,"freeze average")==0)return freeze_T*freeze_P;
				else if(strcmp(information,"sputter")==0)     	return sputter;
				else if(strcmp(information,"weaken")==0)       	return weaken;
				else if(strcmp(information,"value")==0)       	return value;
				else if(strcmp(information,"speed")==0)        	return speed;
				else if(strcmp(information,"tag")==0)        	return tag;
				else if(strcmp(information,"level")==0)        	return level;
				else if(strcmp(information,"disposable")==0)    return disposable;
				else if(strcmp(information,"explode_tick")==0)  return explode_tick;
				else if(strcmp(information,"T last_act")==0)   	return last_action;
				else if(strcmp(information,"T next_actable")==0)return last_action+speed+disposable;//ͬʱ����˲ʱ�빥�� 
				else if(strcmp(information,"T last_att+")==0)	return last_aA;
				else if(strcmp(information,"T last_def+")==0) 	return last_dA;
				else system("pause");
				return 0;//���������� 
			} 
            bool tag_j(int a_kind_of_tag)      {return tag&a_kind_of_tag;}
            int demand(bool strict)            {return strict?player_level_demand:1;}
            bool univ_demand(int u_level,bool if_use_self_def,bool unlocked,bool if_pierce)
			{
				bool accept;
				switch(demand(true))
				{
					case Selfdef:
						accept=if_use_self_def;
						break;
					case Collect:
						accept=unlocked;
						break;
					default:
						accept=demand(true)<=u_level;
						if(accept==false&&if_pierce!=0)
							accept=iftrig(Pierce_P);
				} 
				return accept;
			}
	private://��׺��M���ֵ Lʣ��ֵ C����ֵ A����ֵ R�����Χ Pǧ�ָ���(0~1000����λΪ��) 
		int HP_M;		//������� 
		int HP_L;		//ʣ������ 
		int attack_C;	//��������ֵ
		int attack_A;	//�������� 
		int attack_R;	//�������ֵ
		int freeze_T;	//����ǿ�� 
		int freeze_P;	//�������� 
		int weaken;		//����ֵ 
		int defence_C;	//��������ֵ
		int defence_A;	//��������ֵ 
		int miss_P;		//������ 
		int double_P;	//������ 
		int sputter;	//����ֵ 
		int value;		//���Ƽ�ֵ 
		int produce;	//�������� 
		int speed;		//�����ٶȣ�ֵԽ���ٶ�Խ���� 
		int disposable;	//һ��������ʱʱ�� 
	public:///	
		int explode_tick;//��ը����ʱ 
		int last_action;//�ϴ��ж��غ� 
		int last_aA;	//�ϴι������ӵĻغ� 
		int last_dA;	//�ϴη������ӵĻغ�
		
		int level;		//ֲ��Ƚ� 
		int tag;		//ֲ���ǩ 
		int player_level_demand;//����ҵĵȼ������Ҫ�� 
};

class Item
{
	
};

class Player
{
	public:
		Player()	{/*printf("���캯��\n");*/} 
	    ~Player()   {/*printf("��������\n");*/}
        //��ʼ��
		     void set_all			(User *p_user,int hard/*�Ѷ�*/,int p,int C,bool fortune,int map); 
		//setϵ�к���
		 	 void cards_set			(User *p_user,bool if_use_self_def,bool if_pierce,int K,int map);
		 	 void rank_set			(int R) 						{if((rank=R)!=1){luck=-10;}return;}    //����ֵ�ܺ�Ϊ0�����ٲ������ 
		//�о�
		     int gesture			(PW w,int T,int K,bool be_ctrled);
		     int system_action		(int T,int dT,int K,unsigned int seed,bool mainskill_not_forbidden);
		     int system_aim			(int K); 
		//���� 
		     bool shopping			(PW w,int T,int K,unsigned int seed);
			 void produce			(PW w,int T);
			 int sun_add			(int add/*�ɸ�*/)     			{return sun+=add;}//����������ֵ 
        //ս��
		     int card_choose		(BOOK w,int T,int hard,int K,int page);
			 int card_reload		(int T,int K,bool ifrealplayer);
			 int random_choose		();
		     Plant* card_change		(int situation,int T,int hard,int K,bool ifrealplayer,Plant* the_plant/*�ò���ʱ��NULLҲ��*/);		    
		     void act     			(EFFECT *head,User *p_user,PW w,int T,int dT,int K,bool will_explode,int GT[][6]/*������Ϣ��*/);    	     
		     bool switch_of_act		(EFFECT *head,User *p_user,PW w,int T,int K,int seed,int GT[][6],int choice);
			 int aim_at  			(EFFECT *head,PW w,int T,int K,int aim_kind,int GT[][6],bool sideskill_not_forbidden);
		     SKILL_t using_skill	(EFFECT *head,PW w,int T,int K,int sk_num,int aim);
		     void make_attack		(EFFECT *head,PW w,int T,int K,int A,int aim,int *GT,bool sideskill_not_forbidden);
		     int be_attacked		(int T,int A,int F,int W,int att_kind,int *real_damage);
		     int luck_add			(int deluck_T0,int add)			{deluck_T=deluck_T0;luck+=add;return luck;}
		//���� 
			 void points_add		(int add)						{points+=add;return;}
			 void coins_add			(int add)						{sigma_coins+=add;return;}
	    //��ʾ
		     void cards_information	(int x,int y);
		     void cards_showall		(PW w,int K,int you,bool cheating_state);  //���ڿ��ֱ�����
		     void combat_message	(int x,int y,int T); 
		     void storage_list		(int x,int y,int dy/*�������߶�*/);
		     void cards_showleft	(PW w);
		     void show_hurt			(int *GT); 
		//getϵ�к��� 
			 int sigma_chance_get	(int T)								{return T>=deluck_T?chance:(chance+luck>0?chance+luck:0);}
			 bool i_and_f_mission	()									{return i_and_f&&(rank==1);}
		     Plant *pget(const char *information)
		     {
				if(strcmp(information,"main")==0)           			return now;
				if(strcmp(information,"assistant")==0)      			return now2;				
				{
					int i,n;char part_info[6];
					for(i=0;i<6;i++) part_info[i]=information[i];
					part_info[5]='\0';
					if(strcmp(information,"have ")==0)
					{n=10*(information[5]-'0')+information[6]-'0';return have[n];}	
				}
				system("pause");return 0;//���������� 	
			 }
		     int get(const char *information)
			 {
				if(strcmp(information,"cards")==0)          			return cards;
				else if(strcmp(information,"rank")==0)           		return rank;
				else if(strcmp(information,"points")==0)         		return points;
				else if(strcmp(information,"sun")==0)            		return sun;    		
				else if(strcmp(information,"now_in_have")==0)    		return now_in_have;
				else if(strcmp(information,"chance")==0)      	 		return chance;
				else if(strcmp(information,"unfrozen_T")==0)     		return unfrozen_T;
				else if(strcmp(information,"deluck_T")==0)      	 	return deluck_T;
				else if(strcmp(information,"sigma_produce")==0)       	return sigma_produce;
				else if(strcmp(information,"sigma_consume")==0)       	return sigma_consume;
				else if(strcmp(information,"sigma_coins")==0)       	return sigma_coins;
				else system("pause");return 0;//���������� 
			 } 	
	public:
		const char *name;		//������� 
		int playernum;			//��ұ�� 
		int level;				//��ҵȼ� 
		Plant *have[HaveMax];	//ָ������ӵ�п��� 
		Plant *now; 			//ָ��ǰʹ�ÿ���
		Plant *now2; 			//ָ��ǰ��������δ���룩 
	private:
		bool unlocked[Locked_plants];//��ҽ������н���Ҫ��Ŀ��� 
		
		int now_in_have; 		//now��have�еı��
		int nowi_in_have; 		//nowi��have�еı�� 
 
		int cards;  			//����������Ϊ0ʱ�������� 
		int sun;    			//�������
		int chance; 			//��ȭ����ֵ��Ĭ��Ϊ50������Ϸ�Ѷȶ��ı� 
		int luck;   			//����ֵ�������ɸ� 
		int unfrozen_T;			//�ⶳ�Ļغ� 
		int deluck_T;			//�������˵Ļغ� 
		
		int sigma_produce;		//ȫ��������ֵ 
		int sigma_consume;		//ȫ��������ֵ 
		int sigma_coins;		//ȫ�ֽ����ֵ 
		int rank;   			//������δ����ʱΪ0
		int points;				//�÷�
		
		bool i_and_f; 
		int ally [PMax];
};

Plant  plant[Pkind*PMax]; 
Plant  npc[NPCkind];
Player player[PMax];


#define REALPERSON 3
struct FIELD/*����Ϊȫ��*/ 
{
	int side_dx;
	int side_dy;
	int dftc;/*defalt color��Ĭ��Ϊ��ɫ����������������*/
	const int info_dy;
	
	int people;/*�������*/ 
	int main_num;/*�����*/ 
    int round;/*�غ���*/
	
    void set_players(int value_of_people,int value_of_main_num)   {people=value_of_people;main_num=value_of_main_num;return;}
    void player_place_get(int i,int *start)
    {
		int *p=start,*q=start+1,*r=start+2,*s=start+3,*t=start+4;
		switch(i)
		{
			case 0:
				*p=side_dx;
				*r=(*q=side_dy)+BIG_dy;
				*t=*q+2;
				break;
			case 1:
				*p=side_dx;
				*r=(*q=Max_dy-side_dy-BIG_dy)-info_dy;
				*t=*r-8;
				break;
			case REALPERSON:
				*p=Max_dx-BIG_dx-side_dx;
				*r=(*q=side_dy)+BIG_dy;
				*t=*q+2;
				break;
			case 2:
				*p=Max_dx-BIG_dx-side_dx;
				*r=(*q=Max_dy-side_dy-BIG_dy)-info_dy;
				*t=*r-8;
				break;
		}
		*s=*p+8;
		return;
	}
	void renew(int i,int T,int dT, int BIG_TYPE)
	{
		int stxy[5];/*�������δ���x,y,y2(information_place),x3(number_place),y3(number_place)*/
		if(i==main_num)
		    player_place_get(REALPERSON,stxy);
		else
		{
		    if(i>main_num)
		        --i;
		    player_place_get(i,stxy);
		}
		if(player[i].now==NULL)
		{
			Dyearea(stxy[0],stxy[1],BIG_dx,BIG_dy,_Light|White);
			Place(stxy[0]+BIG_dx/2,stxy[1]+(BIG_dy-sizeof("???"))/2);printf("???");
		}
		else
			player[i].now->card_demon(stxy[0],stxy[1],dT,BIG_TYPE);
		Dyearea(stxy[0],stxy[2],BIG_dx,info_dy,dftc);
		player[i].combat_message (stxy[0],stxy[2],T);
	}
	void renew_s(int T,int dT[],int BIG_TYPE)
	{
		int i;
		for(i=0;i<people;i++)
			renew(i,T,dT[i],BIG_TYPE);
		return;
	}
    void show_cards(int T,int dT[],int hard)
	{
		int i;
		const int storage_height=12;
		const int storage_width=42;
		int nest_x=Max_dx-side_dx-storage_height;
		int nest_y=(Max_dy-storage_width)/2;
		int x_a=side_dx;
		int x_a_dx=Max_dx-2*side_dx;
		int y_a=side_dy+BIG_dy;
		int y_a_dy=Max_dy-2*y_a;
		int x_b=side_dx+BIG_dx;
		int x_b_dx=Max_dx-2*x_b;
		Dyearea(x_a,1               ,x_a_dx,side_dy-1,dftc);
		Dyearea(x_a,Max_dy-side_dy+1,x_a_dx,side_dy,dftc);
		Dyearea(x_b,side_dy         ,x_b_dx,Max_dy-2*side_dy,dftc);	
		Dyearea(x_a+2,y_a           ,x_a_dx-2,y_a_dy ,dftc);		
		Dyenest(nest_x,nest_y,storage_height,storage_width,_Yellow,_Cyan);
		
		Place(nest_x+2,nest_y+4);printf("�ҵĿ��ƣ�");
		player[main_num].storage_list(nest_x+4,nest_y+4,storage_width-6);
		renew_s(T,dT/*����*/,BIG);
		const char hard_txt[4][sizeof("��ƽ")]={"��ƽ","��","��ͨ","����"};
		Place(2,(Max_dy-sizeof("��ƽģʽ  ��1�غ�"))/2);
		printf("%sģʽ  ��%d�غ�",hard_txt[hard-1],T);
	} 
}; 

#define Locked -9
#define Max_Goods 4
int limited_goods(int level) 
{
	return (level>=3?level>=5?Max_Goods:Max_Goods-1:Max_Goods-2);
}
struct SHOP_SYSTEM
{
	int laidible[Pkind];
	int randcard[Max_Goods];
	int cost[Max_Goods];
	int unoccupied_find(int level)
    {
	    int i;
	    int avalible=0;
	    for(i=0;i<Pkind;i++)
	        if(  plant[i].belong==NULL  &&  plant[i].univ_demand(level,false,false,false)/*�Զ��岻�ɹ���*/  )
	            laidible[avalible++]=i;
	    return avalible;
    } 
    void laid_find(int seed,int level)
    {
		srand(seed);  //���ÿ�غ����ݲ��� 
		int i;
		int ava=unoccupied_find(level);
		int rav; 
		const int really_laid=limited_goods(level);
		for(i=0;i<really_laid;i++)
    	{
		    if(i<ava)
		    {
			    do
			        randcard[i]=laidible[rav=rand()%ava/*ȷ��ֻ��ava���ڵĿ��ƿɼ�*/];
			    while(  randcard[i]==0  );
			    cost[i]=plant[  randcard[i]  ].get("value");
			    laidible[rav]=0;
	 	    }
	 	    else
	 	    { 
	 	        randcard[i]=Fail;
	 	        cost[i]=0; 
	 	    } 
	    }
	    while(i<Max_Goods)
	    {
	        randcard[i]=Locked;
	        cost[i++]=0; 
		}
	    return;
	}  
}shop_system; 


PW log_in_pw=       {Std_Uboundry   ,Std_Lboundry   ,Std_dx   ,Std_dy   ,/*dftc*/_White|_Light|Purple,/*aut*/false};
PW entering_pw=     {Std_Uboundry   ,Std_Lboundry   ,Std_dx   ,Std_dy   ,/*dftc*/_Green|White,     /*aut*/false};
PW p_start_pw=      {1              ,1              ,Max_dx   ,Max_dy   ,/*dftc*/_Yellow|Red,      /*aut*/false};
PW p_action_pw=     {Std_Uboundry   ,Std_Lboundry   ,Std_dx   ,Std_dy   ,/*dftc*/_White|Blue,      /*aut*/false};
PW s_action_pw=     {Std_Uboundry   ,Std_Lboundry   ,Std_dx   ,Std_dy   ,/*dftc*/_White|Light|Blue,/*aut*/true };
PW p_gesture_pw=    {4      ,(Max_dy-Smaller_dy)/2  ,Smaller_dx ,Smaller_dy   ,/*dftc*/_White|Light|Blue,/*aut*/false };

BOOK rules_bk={1,1,Max_dx,Max_dy,/*dftc*/_Black|White|Light/*û��aut����*/};
BOOK cards_bk=        {Larger_Uboundry,Larger_Lboundry,Larger_dx,Larger_dy,/*dftc*/_White|Blue/*û��aut����*/};
BOOK sub_cards_bk=    {Larger_Uboundry,Larger_Lboundry,Larger_dx,Larger_dy,_White|Blue};
BOOK p_choose_card_bk={Larger_Uboundry,Larger_Lboundry,Larger_dx,Larger_dy,/*dftc*/_White|Blue/*û��aut����*/};
BOOK p_inventory_bk={Larger_Uboundry-1,Larger_Lboundry-10,Larger_dx+4,Larger_dy+20,/*dftc*/_White|Blue/*û��aut����*/};

FIELD std_combat_f= {2,4,/*dftc*/_Black|Light|White,16/*info_dy*/};



char trans(int key_get,int CapsLock)
{
	if(key_get<lts)
		return (CapsLock?'A':'a')+key_get;
	else if(key_get>=no_num)
		return '0'+(key_get-no_num);
	else 
		return "+-*/.,:;\'\"~<>()[]{}_@$%?"[key_get-lts];		
}
VaryType keyboard(VaryType *value,int x,int y,int input_x,int input_y,int color,int mode) 
{
	value->d=0;
	const int blank=1;
	const int ddx=1;
	const int ddy=5;
	const int dx=2*blank+((keys-1)/everyL+1)*(ddx+1)+4;
	const int dy=2*blank+(everyL)*(ddy+1);
		
	PW kbd={x,y,dx,dy,/*dftc*/_White,/*aut*/false};
	BTN key[keys];
	BTN Bksp;
	BTN Enter;	
	BTN Caps;	
	int s1[kbd.set_btnN(keys+4)][4];
	kbd.s1_link(s1);
	
	int i,j=0,b;
	char c;
	bool capital=false;
	Color(_White);
	kbd.newpage();
	kbd.hint(0,sizeof("�����"),"�����");
	for(i=0;i<keys;i++)
	{
		if(mode==ONLYNUM)
			key[i].judset( 	i>=no_num	);
		else
			key[i].judset(	true  );
		key[i].set(  x+blank+1+(i/everyL)*(ddx+1)  ,  y+blank+(i%everyL)*(ddy+1)  ,  ddx	,ddy,s1[i]);				
	}
	
	Caps.judset(  true  );
	Caps.set(  	x+dx-3, y+2  ,  ddx , 2*ddy, s1[keys]		);		
	Bksp.set(  	x+dx-3, (y+dy-3-4*ddy)  ,  ddx , 2*ddy, s1[keys+1]		);	
	Enter.set(  x+dx-3, (y+dy-2-2*ddy)  ,  ddx , 2*ddy, s1[keys+2]		);
			
	kbd.end_setall("ȡ������");
	while(1)
	{
		Bksp.judset( 	j>0  );
		Enter.judset(  	j>0  );
		Caps.dye("CapsLock");
		Bksp.dye("Backspace");
		Enter.dye("Enter");	
		for(i=0;i<keys;i++)	 
		{
			key[i].dye("");
			Place(	1+x+blank+(i/everyL)*(ddx+1),y+blank+(i%everyL)*(ddy+1)+2);printf("%c",trans(i,capital));
		}
		Color(color);
		do
			b=kbd.do_action();
		while(	b<keys&&key[b].jud==false	||
				b==keys+1&&Bksp.jud==false	||
				b==keys+2&&Enter.jud==false		);
		Place(input_x,input_y+j);//�ظ�ԭλ			
		switch(		c=(b==keys?'\r':(b==keys+1?'\t':(b==keys+2?'\n':(b==keys+3?'\0':trans(b,capital)))))		)
		{
			case '\r':/*��д*/
				capital=!capital;
				break;			
			case '\t':/*ɾ��*/
				--j;//s[j]ֱ��Ĩȥ 
				if(mode==ONLYNUM)
					value->d/=10;
				Place(input_x,input_y+j);printf(" "); 
				break;
			case '\0':/*��������*/
				if(mode==ONLYNUM)
					value->d=-1;
				else
					value->s[0]='\0';
				return *value;
			case '\n':/*ȷ������*/
				if(mode!=ONLYNUM)
					value->s[j]='\0';
				return *value;	
			default://jֻ����������
				Place(input_x,input_y+j);printf("%c",c);
				if(mode==ONLYNUM)
				{ 
					value->d=value->d*10+(c-'0'); 
					j++;
				} 
				else
					value->s[j++]=c; 
		}
	}
};

struct EFFECT
{
	int to_T;
	int from_T; 
	int eff[PMax][Eff_Temp];
	/*			0		1		2		3		4		5		6	*7*		8		9	 10	   11*/
	/*����Ϊ��+HP_M��+HP_L���˺����˺����͡�att�ӳɡ�def�ӳɡ����������������ܡ��������������ڰ�*/
	Player *maker;
	int aim;
	EFFECT *next;
};

#define ColorsMax 16
typedef short unsigned int Color_t; 
typedef struct 
{	
	int picture_height;
	int picture_width;
	const char *pictrue;
	Color_t default_palette[ColorsMax];
	int top_left_x;
	int top_left_y;
	void set(int x,int y)
	{
		top_left_x=x;
		top_left_y=y;
		return;
	}
	void make_b(BTN *p,int s1[4],bool jud)
	{
		p->set(top_left_x,top_left_y,picture_height,picture_width,s1);
		p->judset(jud);
		return;
	}
	void draw(int monocolor/*����-1�ò�ͼ*/)
	{
		const char *p=pictrue;
		int i,j,c;	
			for(i=0;i<picture_height;i++)
				for(j=0;j<picture_width;j++)
					if((c=*p++)!='.')
					{
						Color(monocolor<0?default_palette[c-'A']:monocolor);
						Place(top_left_x+i,top_left_y+j);
						putchar(' ');
					}
		return;		
	}
}PICT;

PW map_pw=      {Larger_Uboundry,Larger_Lboundry,Larger_dx,Larger_dy,/*dftc*/L_Blue|Light|White,      /*aut*/false};

PICT null_pict=
{
	9,sizeof("................")-1,
	"................"
	"................"
	"................"
	"................"
	"................"
	"................"
	"................"
	"................"
	"................",
	{_Red}
};
PICT right_pict=
{
	9,sizeof("................")-1,
	"................"
	"................"
	"................"
	"................"
	"..............AA"
	"............AA.."
	"...AA.....AA...."
	".....A..AA......"
	"......AA........",
	{_Red}
};
PICT map_pict=
{
	7,sizeof("...............")-1,
	"..........AA..."
	".......AAAAAA.."
	"....AAAAABBAAA."
	".AAAAABABAAAAAA"
	"..AAABABAAAA..."
	"...AAAAAA......"
	"....AA.........",
	{L_Yellow,_Black}
};
PICT plane_pict=
{
	9,sizeof("................")-1,
	"....EEE........."
	"...EEEEE........"
	".....D.........."
	".....D.........."
	".....D...F......"
	".G..AAA..C......"
	".CAAAAAAAABBBBBA"
	"AAAAAAAAAAABBBAA"
	"AAAAAAAAAAAAAAAA",
	{L_Green,L_Blue,_Green,_White,_Green,L_Yellow,L_Cyan}
};
PICT tundra_pict=
{
	9,sizeof("................")-1,
	"...........AEA.."
	"..........AEEEE."
	"...AAA......D..."
	"..AABAA.....D.AA"
	"..AAAAA....ADAAA"
	"AAAACAAAAAAAAAAA"
	"AAAACAAAAAAAAAAA"
	"AAACCCCCAAAAAAAA"
	"AAACCCCCAAAAAAAA",
	{L_White,L_Cyan,_Light,_White,_Green}
};
PICT badland_pict=
{
	9,sizeof("................")-1,
	"................"
	"................"
	"E..............."
	"AA.............."
	"DDD.........D..."
	"CCCC.......CC.C."
	"BBBBBB....BBBBBB"
	"AAAAAAAAAAAAAAAA"
	"AAAAAAAAAAAAAAAA",
	{_Yellow,_Light,L_Yellow,_Red,_White}
};
PICT building_pict=
{
	9,sizeof("................")-1,
	"..AAAAAAAAAAAA.."
	"..ABABABBABABA.."
	"..AAAAAAAAAAAA.."
	"..ABABABBABABA.."
	"..AAAAAAAAAAAA.."
	"..ABABACCABABA.."
	"..AAAAACCAAAAA.."
	"................"
	"................",
	{L_Red,L_Cyan,_Black}
};
PICT mansion_pict=
{
	9,sizeof("................")-1,
	"................"
	"..AAAAAAAAAAAA.."
	"..AEEEAAAAEEEA.."
	"..AAAAEAAEAAAA.."
	"..AACCDAADCCAA.."
	"..AAAAAAAAAAAA.."
	"..AAAAABBAAAAA.."
	"..AAAAABBAAAAA.."
	"..AAAAAAAAAAAA..",
	{_White,0,L_White,_Blue,_Light}
};
PICT ocean_monument_pict=
{
	9,sizeof("................")-1,
	"......ABBA......"
	"......A..A......"
	".....AAAAAA....."
	"...AACCCCCCAA..."
	"..AAACAAAACAAA.."
	".AACAA....AACAA."
	"AAAAAA....AAAAAA"
	".A.A.A....A.A.A."
	".A.A.A....A.A.A.",
	{L_Blue,L_Cyan,_Blue}
};
PICT crimson_forest_pict=
{
	9,sizeof("................")-1,
	"................"
	"................"
	".AAAAAA........."
	"AAAAAACC........"
	"AAAAAAAA........"
	"AAABBAAA........"
	".A.BB..A...AAA.."
	"...BB.......B..."
	"AAAAAAAAAAAAAAAA",
	{_Red,L_Red,_Yellow}
};
PICT end_city_pict=
{
	9,sizeof("AAAAAAAAAAAAAAAA")-1,
	"AAAAAAAAAAAAAAAA"
	".BBBBBBBBBBBBBB."
	".BBCCBBCCBBCCBB."
	".BBBBBBBBBBBBBB."
	".AAAAAAAAAAAAAA."
	"..BBBBBBBBBBBB.."
	"..AAAAAAAAAAAA.."
	"...BBBBBBBBBB..."
	"...AAAAAAAAAA...",
	{L_Purple,L_Yellow,_Purple}
};
PICT snow_and_spark_pict=
{
	10,sizeof(".....AA.......")-1,
	".....AA......."
	"AA...AA...AA.." 
	"..AA.AA.AA...."
	"....AAAA......"
    "....AAAA.B..B."
	"..BA.AA.BB..BB"
	"AABB.AABBB.BBB"
	"..BBBBBBBBBBBB"
	"...BBBBBBBBBB."
	".....BBBBBB...",
	{L_Cyan,L_Red}
};
PICT flower_pict=
{
	6,sizeof("A....B.....C")-1,
	"A....B.....C" 
	"AAA.BBBB..CC" 
	"AAAAABBBBCCC"
	"AAAAAAAAAAAC"
    ".AAAAAAAAAA."
	"...AAAAAA...",
	{L_Red,L_Yellow,_Red}
};
PICT fruit_pict=
{
	9,sizeof("...AAAABBB...")-1,	
	"...AAAABBB..."
	".AAAABBBCCCD." 
	"AAAABBBCCCDDD"
	"AAABBCCCCDDDE"
    ".ABBCCCDDDDE."
	"..BCCCDDDEE.."
	"..FFFFFFFFFF."
	".FFFF.FF.FFFF"
	".F.....F...FF",
	{_Rand_color(0),_Rand_color(1),_Rand_color(2),_Rand_color(4),_Rand_color(6),_Green}
};
PICT medal_pict=
{
	9,sizeof("..AAAAAAA..")-1,
	"..AAAAAAA.."//û�ж��� 
	"...A...A..."
	"...A...A..."
	"....A.A...."
	"..BBBBBBB.."
	".BBCCCCCBB."
	"BBCCCCCCCBB"
	".BBCCCCCBB."
	"..BBBBBBB..",
	{_Blue,_Yellow,L_White}
};
PICT blue_ice_pict=
{
	5,sizeof("AAAAAAAAAA")-1, 
	"AAAAAAAAAA" 
	"AAABBAAAAA"
	"AABAAAABAA"
    "ABAAABBAAA"
	"AAAAAAAAAA",
	{L_Blue,_Cyan}
};
PICT emerald_pict=
{
	6,sizeof("....C.AAAAB.....")-1,
	"....C.AAAAB....."
	"...CCCAAAAAAB..."
	"....CAAAAAAAB..."
	"....AAAAAAAAB..."
	"....AAAAAAAAB..."
	"......AAAAB.....",
	{L_Green,_Green,L_White}
};
PICT ingot_pict=
{
	8,sizeof("..........BB....")-1,
	"..........BB...."
	"........BBBBBB.."
	"....BBBBBBBBBBBB"
	"BBBBBBBBBBBBAAAA"
	"AABBBBBBBAAAAAAA"
	"AAAAABBAAAAAAA.."
	"..AAAAAAAAA....."
	"....AAA.........",
	{_Black,_Light}
};
PICT perl_pict=
{
	8,sizeof("......AAAA......")-1,
	"......AAAA......"
	"...AAAAAAAAAA..."
	".AAAAAABBAAAAAA."
	"AAAAAABBBBAAAAAA"
	"AAAAAABBBBAAAAAA"
	".AAAAAABBAAAAAA."
	"...AAAAAAAAAA..."
	"......AAAA......",
	{_Green,L_Green}
};
PICT potion_pict=
{
	9,sizeof("...DDDDDD...")-1,
	"...DDDDDD..."
	"....DDDD...."
	"....ACCA...."
	"...AACCAAA.."
	".AAACCCCAAA."
	"AACCCCCCCCAA"
	"AABBBBBBBBAA"
	".AAABBBBAAA."
	"...AAAAAA...",
	{L_White,L_Blue,_White,_Yellow}
};
PICT boots_pict=
{
	5,sizeof("....BAA..AAB....")-1,
	"....BAA..AAB...."
	"....BAA..AAB...."
	"...AAAA..AAAA..."
	"AAAAAAA..AAAAAAA"
	"AAAAAA....AAAAAA",
	{_Blue,_Green}
};
PICT sword_pict=
{
	8,sizeof("AAAA............")-1,
	"AAAA............"
	"AADDAA.........."
	"..AADDAA........"
	"....AADDAA..BB.."
	"......AADDBB...."
	"........BBCC...."
	"......BB....CC.."
	"..............EE",
	{_Black,_Red,L_Green,_Cyan,_Purple}
};
PICT shield_pict=
{
	7,sizeof("CCAAAA....AAAACC")-1,
	"CAAAAA....AAAAAC"
	"CAAAAAA..AAAAAAC"
	"...AAAAAAAAAA..."
	"...AAAABBAAAA..."
	"...AAABDDBAAA..."
	"...AAAABBAAAA..."
	"...AAAAAAAAAA...",
	{_Black,_Green,_Red,L_Green}
};
