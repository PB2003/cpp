
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
		Place(line++,y+side*2);printf(information);//自动换行 
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

TXTF tf;//全文件公用 

struct BTN/*button*/
{
	int area[4];/*大坐标*/
	int coor[4];/*小坐标*/ 
	bool jud;   /*点亮判据*/
	/*为保证兼容性，不包括txt*/
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
				else if(c==' ')//忽略 
					p--; 
				else if(c==MARK||c==INTERVAL||c==ADD||c==NO)//非法输入 
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
				if(c==MARK||c==INTERVAL||c==ADD||c==NO)//非法输入 
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
	int dftc;/*defalt color，包括背景和文字*/;
	bool aut;/*系统自动*/ 
	
	BTN  end_btn;/*默认的按钮*/
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
		end_btn.set(  x+dx-Stdheight-1  ,  y+(dy-Stdwidth)/2  ,  Stdheight  ,  Stdwidth   ,  inner_s1[btnN-1]/*规定该按钮必须为最后一个*/);
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
    void do_confirm(int max_wait_time)/*只牵涉end_btn*/
    {
		Effective(p,&end_btn.coor,1,true,max_wait_time,Std_flush_period,false);
		return;
	}
};

struct BOOK/*相比PW，略去了bool aut（一定为玩家操作），修改newpage函数，新添page等*/ 
{
	int x;
	int y;
	int dx;
	int dy;
	int dftc;/*defalt color，包括背景和文字*/;
	
    int maxpage;
    int page; 
	BTN end_btn;/*默认的按钮*/
	BTN page_btn[2];/*默认的翻页按钮*/
	int action;
	int btnN;
	int (*inner_s1)[4];
	void newpage(int value_of_maxpage,int value_of_page)/*clear window同时设定好page和maxpage*/   {Dyearea(x,y,dx,dy,dftc);maxpage=value_of_maxpage;page=value_of_page;return;}
	void hint   (int rela_x,int real_sizeof_message,const char*message) {Color(dftc);Place(x+rela_x,y+(dy-real_sizeof_message)/2);printf("%s",message);return;}
	void newline(int rela_x,int real_sizeof_message,const char*message) {Dyeline(x+rela_x,y,dy,dftc);Place(x+rela_x,y+(dy-real_sizeof_message)/2);printf("%s",message);return;}
	void RPlace (int rela_x,int rela_y)                                 {Place  (x+rela_x,y+rela_y);return;}
	void end_setall(const char *txt)
	{
		end_btn.set(  x+dx-Stdheight-1  ,  y+(dy-Stdwidth)/2  ,  Stdheight  ,  Stdwidth   ,  inner_s1[btnN-1]/*规定该按钮必须为最后一个*/);
		end_btn.judset(true);
		end_btn.dye(txt);
		return;
	}
	void page_setall(int page_btn_rela_x,int page_btn_rela_y)
	{
		page_btn[0].judset(  page>1        );
	    page_btn[1].judset(  page<maxpage  );
	    page_btn[0].set( x+page_btn_rela_x , y+page_btn_rela_y              ,  Stdheight  ,  Stdwidth  ,inner_s1[btnN-3]/*规定该按钮必须为倒数第3个*/);
	    page_btn[1].set( x+page_btn_rela_x , y+dy-page_btn_rela_y-Stdwidth  ,  Stdheight  ,  Stdwidth  ,inner_s1[btnN-2]/*规定该按钮必须为倒数第2个*/);
        page_btn[0].dye("上一页");
        page_btn[1].dye("下一页");
		Color(dftc);RPlace(page_btn_rela_x+1,(dy-sizeof("第0页/共0页"))/2);
		printf("第%d页/共%d页",page,maxpage);
		return;
	}
	int set_btnN(int total_number_of_buttons){return btnN=total_number_of_buttons;}
	void s1_link(int s1[][4])                {inner_s1=s1;return;}
	int do_action()//左右翻页可以直接按键翻
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
    void do_confirm(int max_wait_time)/*只牵涉end_btn*/
    {
		Effective(p,&end_btn.coor,1,true,max_wait_time,Std_flush_period,false);
		return;
	}
};

class Plant
{
	public:
		const char 	*name;							//植物名称 
		int 		plantnum;						//植物编号 
		Player     	*belong;						//所属玩家 
		STD_SKILL	*skill[SkillMax];				//技能指针 
		const char  *skill_name[SkillMax];			//技能名称 
 		int         skill_avalible[SkillMax];	    //技能[i]对应技能个数[i]
 		int			skill_aim[SkillMax];			//技能针对的目标类型 
 		int			skill_intensity[SkillMax];		//技能强度（等级） 
 		int			skill_favor[SkillMax];		//技能强度（等级） 
		Plant()  {/*printf("构造函数\n");*/} 
		~Plant() {/*printf("析构函数\n");*/}
		//初始化   
		    void set_all(int plantnum,const char *name,const int a[],struct Skill sk,int map);
		//显示
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
							case Passive	:printf("被动技");break;
							case Passive_S	:printf("临死技");break;
							case Always 	:printf("背景技");break;
							case Adjunct	:printf("附加技");break;
							case 0			:break;
							default:
								if(skill_avalible[skill_No] >=100)	printf("剩余次数：无限"); 
								else								printf("剩余次数：%d",skill_avalible[skill_No]);
						}
				}
				else if(strcmp(information,"describe")==0)
				{
					if(skill[skill_No]!=NULL)
						;//留空 
				}
				else system("pause");return;//防错误输入
				return;
			}  
        //发动类函数
		    int attack(int T,int aim_tag);		    
			#define Fail_fre 0
		    int freeze(int aim_tag)				{return (iftrig(freeze_P))? (  (aim_tag&FA)==0?  freeze_T :  Fail_fre)  :  0  ;}   //火焰型不受冰冻 
		    int sun_produce(int T) 				{last_action=T;return produce;}
		    bool tick()							{return disposable!=0/*熔断保护*/&&--explode_tick==0;  }
		    bool if_go_exploding()				{return disposable!=0/*熔断保护*/&&explode_tick==0;  }
		    bool if_havenot_explode()			{return disposable!=0/*熔断保护*/&&explode_tick!=0;  }
		    int skill_use(int i,int T)			{last_action=T;/*刷新行动时间*/return skill_avalible[i]<0?skill_avalible[i]/*无限次*/:(--skill_avalible[i]);}
		//修改类函数
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
				return 0;//防错误输入 
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
				return 0;//防错误输入
			}
			void last_action_T_reset(int T)		{last_action=T+1-speed-!(!disposable)/*0or1*/;}
		//被动类函数 
		    int damage(int att,int att_kind,int *dam);
			void belong_change(Player *p);        
		    void strenth(int A,int deltaT)     	{attack_A= deltaT<0?0:A;return;} 
            void shield (int A,int deltaT)     	{defence_A=deltaT<0?0:A;return;}     
        //get系列函数
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
				else if(strcmp(information,"T next_actable")==0)return last_action+speed+disposable;//同时考虑瞬时与攻速 
				else if(strcmp(information,"T last_att+")==0)	return last_aA;
				else if(strcmp(information,"T last_def+")==0) 	return last_dA;
				else system("pause");
				return 0;//防错误输入 
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
	private://后缀：M最大值 L剩余值 C中心值 A附加值 R随机范围 P千分概率(0~1000，单位为‰) 
		int HP_M;		//最大生命 
		int HP_L;		//剩余生命 
		int attack_C;	//攻击中心值
		int attack_A;	//攻击附加 
		int attack_R;	//攻击随机值
		int freeze_T;	//冰冻强度 
		int freeze_P;	//冰冻几率 
		int weaken;		//弱化值 
		int defence_C;	//防御中心值
		int defence_A;	//防御附加值 
		int miss_P;		//闪避率 
		int double_P;	//暴击率 
		int sputter;	//溅射值 
		int value;		//卡牌价值 
		int produce;	//生产能力 
		int speed;		//攻击速度（值越大，速度越慢） 
		int disposable;	//一次性与延时时间 
	public:///	
		int explode_tick;//爆炸倒计时 
		int last_action;//上次行动回合 
		int last_aA;	//上次攻击附加的回合 
		int last_dA;	//上次防御附加的回合
		
		int level;		//植物等阶 
		int tag;		//植物标签 
		int player_level_demand;//对玩家的等级或解锁要求 
};

class Item
{
	
};

class Player
{
	public:
		Player()	{/*printf("构造函数\n");*/} 
	    ~Player()   {/*printf("析构函数\n");*/}
        //初始化
		     void set_all			(User *p_user,int hard/*难度*/,int p,int C,bool fortune,int map); 
		//set系列函数
		 	 void cards_set			(User *p_user,bool if_use_self_def,bool if_pierce,int K,int map);
		 	 void rank_set			(int R) 						{if((rank=R)!=1){luck=-10;}return;}    //机会值总和为0不能再参与比赛 
		//判据
		     int gesture			(PW w,int T,int K,bool be_ctrled);
		     int system_action		(int T,int dT,int K,unsigned int seed,bool mainskill_not_forbidden);
		     int system_aim			(int K); 
		//经济 
		     bool shopping			(PW w,int T,int K,unsigned int seed);
			 void produce			(PW w,int T);
			 int sun_add			(int add/*可负*/)     			{return sun+=add;}//返回阳光总值 
        //战斗
		     int card_choose		(BOOK w,int T,int hard,int K,int page);
			 int card_reload		(int T,int K,bool ifrealplayer);
			 int random_choose		();
		     Plant* card_change		(int situation,int T,int hard,int K,bool ifrealplayer,Plant* the_plant/*用不到时传NULL也行*/);		    
		     void act     			(EFFECT *head,User *p_user,PW w,int T,int dT,int K,bool will_explode,int GT[][6]/*储存信息用*/);    	     
		     bool switch_of_act		(EFFECT *head,User *p_user,PW w,int T,int K,int seed,int GT[][6],int choice);
			 int aim_at  			(EFFECT *head,PW w,int T,int K,int aim_kind,int GT[][6],bool sideskill_not_forbidden);
		     SKILL_t using_skill	(EFFECT *head,PW w,int T,int K,int sk_num,int aim);
		     void make_attack		(EFFECT *head,PW w,int T,int K,int A,int aim,int *GT,bool sideskill_not_forbidden);
		     int be_attacked		(int T,int A,int F,int W,int att_kind,int *real_damage);
		     int luck_add			(int deluck_T0,int add)			{deluck_T=deluck_T0;luck+=add;return luck;}
		//分数 
			 void points_add		(int add)						{points+=add;return;}
			 void coins_add			(int add)						{sigma_coins+=add;return;}
	    //显示
		     void cards_information	(int x,int y);
		     void cards_showall		(PW w,int K,int you,bool cheating_state);  //仅在开局被调用
		     void combat_message	(int x,int y,int T); 
		     void storage_list		(int x,int y,int dy/*不设最大高度*/);
		     void cards_showleft	(PW w);
		     void show_hurt			(int *GT); 
		//get系列函数 
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
				system("pause");return 0;//防错误输入 	
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
				else system("pause");return 0;//防错误输入 
			 } 	
	public:
		const char *name;		//玩家名称 
		int playernum;			//玩家编号 
		int level;				//玩家等级 
		Plant *have[HaveMax];	//指向所有拥有卡牌 
		Plant *now; 			//指向当前使用卡牌
		Plant *now2; 			//指向当前副卡（尚未加入） 
	private:
		bool unlocked[Locked_plants];//玩家解锁的有解锁要求的卡牌 
		
		int now_in_have; 		//now在have中的编号
		int nowi_in_have; 		//nowi在have中的编号 
 
		int cards;  			//卡牌总数，为0时触发出局 
		int sun;    			//阳光点数
		int chance; 			//猜拳机会值，默认为50，随游戏难度而改变 
		int luck;   			//幸运值，可正可负 
		int unfrozen_T;			//解冻的回合 
		int deluck_T;			//消除幸运的回合 
		
		int sigma_produce;		//全局生产总值 
		int sigma_consume;		//全局消费总值 
		int sigma_coins;		//全局金币总值 
		int rank;   			//排名，未出局时为0
		int points;				//得分
		
		bool i_and_f; 
		int ally [PMax];
};

Plant  plant[Pkind*PMax]; 
Plant  npc[NPCkind];
Player player[PMax];


#define REALPERSON 3
struct FIELD/*锁定为全屏*/ 
{
	int side_dx;
	int side_dy;
	int dftc;/*defalt color，默认为黑色，包括背景和文字*/
	const int info_dy;
	
	int people;/*玩家总数*/ 
	int main_num;/*主玩家*/ 
    int round;/*回合数*/
	
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
		int stxy[5];/*参数依次代表x,y,y2(information_place),x3(number_place),y3(number_place)*/
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
		
		Place(nest_x+2,nest_y+4);printf("我的卡牌：");
		player[main_num].storage_list(nest_x+4,nest_y+4,storage_width-6);
		renew_s(T,dT/*数组*/,BIG);
		const char hard_txt[4][sizeof("和平")]={"和平","简单","普通","困难"};
		Place(2,(Max_dy-sizeof("和平模式  第1回合"))/2);
		printf("%s模式  第%d回合",hard_txt[hard-1],T);
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
	        if(  plant[i].belong==NULL  &&  plant[i].univ_demand(level,false,false,false)/*自定义不可购买*/  )
	            laidible[avalible++]=i;
	    return avalible;
    } 
    void laid_find(int seed,int level)
    {
		srand(seed);  //造成每回合内容不变 
		int i;
		int ava=unoccupied_find(level);
		int rav; 
		const int really_laid=limited_goods(level);
		for(i=0;i<really_laid;i++)
    	{
		    if(i<ava)
		    {
			    do
			        randcard[i]=laidible[rav=rand()%ava/*确保只有ava以内的卡牌可见*/];
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

BOOK rules_bk={1,1,Max_dx,Max_dy,/*dftc*/_Black|White|Light/*没有aut参数*/};
BOOK cards_bk=        {Larger_Uboundry,Larger_Lboundry,Larger_dx,Larger_dy,/*dftc*/_White|Blue/*没有aut参数*/};
BOOK sub_cards_bk=    {Larger_Uboundry,Larger_Lboundry,Larger_dx,Larger_dy,_White|Blue};
BOOK p_choose_card_bk={Larger_Uboundry,Larger_Lboundry,Larger_dx,Larger_dy,/*dftc*/_White|Blue/*没有aut参数*/};
BOOK p_inventory_bk={Larger_Uboundry-1,Larger_Lboundry-10,Larger_dx+4,Larger_dy+20,/*dftc*/_White|Blue/*没有aut参数*/};

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
	kbd.hint(0,sizeof("软键盘"),"软键盘");
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
			
	kbd.end_setall("取消输入");
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
		Place(input_x,input_y+j);//回复原位			
		switch(		c=(b==keys?'\r':(b==keys+1?'\t':(b==keys+2?'\n':(b==keys+3?'\0':trans(b,capital)))))		)
		{
			case '\r':/*大写*/
				capital=!capital;
				break;			
			case '\t':/*删除*/
				--j;//s[j]直接抹去 
				if(mode==ONLYNUM)
					value->d/=10;
				Place(input_x,input_y+j);printf(" "); 
				break;
			case '\0':/*结束输入*/
				if(mode==ONLYNUM)
					value->d=-1;
				else
					value->s[0]='\0';
				return *value;
			case '\n':/*确认输入*/
				if(mode!=ONLYNUM)
					value->s[j]='\0';
				return *value;	
			default://j只在这里增加
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
	/*依次为：+HP_M、+HP_L、伤害、伤害类型、att加成、def加成、冰冻、弱化、闪避、暴击、生产、黑暗*/
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
	void draw(int monocolor/*输入-1得彩图*/)
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
	"..AAAAAAA.."//没有逗号 
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
