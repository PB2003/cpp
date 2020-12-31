
#define _PLAYERS_CPP_

#ifndef _BASICDATA_CPP_ 
    #define _BASICDATA_CPP_
    #include "basicdata.cpp"
#endif

#ifndef _STRUCTION_CPP_ 
    #define _STRUCTION_CPP_
    #include "struction.cpp"
#endif

#ifndef _CARDS_CPP_ 
    #define _CARDS_CPP_
    #include "cards.cpp"
#endif

#ifndef _BIGCHAR_CPP_ 
    #define _BIGCHAR_CPP_
    #include "bigchar.cpp"
#endif

int field_show(User *p_user,EFFECT *head,FIELD f,int T,int hard,int K,int R,int you,bool ifinstant,int map);//置顶声明 

#define Luck_continue_dT 20 
#define Luck_eff 20
#define Enermy			0
#define No_ally 		1
#define Complete_ally 	2
/*初始化*/void Player::set_all(User *p_user,int hard/*难度*/,int p,int C,bool fortune,int map)
{
	int i;
	if(p_user==NULL) //假用户 
	{
		if(map<0)
			name=default_player_name[p];//注意是p不是i
		else
			name=new_player_name[map][p];	
		switch(hard)
		{
			case HARMONY:	level=1;			break;
			case EASY:		level=random(2,1);	break;
			case NORMAL:	level=random(5,2);	break;
			case HARD:		level=7+rand()%4;	break;
		}		
		cards=C;
		for(i=0;i<Locked_plants;i++)
			this->unlocked[i]=(hard==HARD?	(rand()%2):false	);
		chance=50+level;
		luck=0;
		deluck_T=0;
		if(map==Fire_city) 
		{
			for(i=0;i<PMax;i++)
				if(i!=3/*真玩家*/)
					ally[i]=Complete_ally;
				else
					ally[i]=Enermy; 
			cards=1;//一张boss 
		}				 
	}
	else			//真用户
	{ 
		name=p_user->name;	
		level=p_user->get("level");
		cards=C+(	(hard==HARMONY||hard==EASY)	&&	C>=3); //和平、简单难度下，3张以上卡牌时多1张卡
		for(i=0;i<Locked_plants;i++)
			this->unlocked[i]=(p_user->unlocked[i]!=0);
		chance=(hard==HARMONY?250:(hard==EASY?75:(hard==NORMAL?50:50)))+level; //难度越大，chance越低
		luck=fortune?Luck_eff:0; 
		deluck_T=fortune?Luck_continue_dT:0;	
		for(i=0;i<PMax;i++)
			ally[i]=Enermy;
	}
	//玩家编号 
	playernum=p;
	for(i=0;i<HaveMax;i++) 
		have[i]=NULL;
	now=NULL;
	now2=NULL;	
	now_in_have=0;
	//等级权利
	if(map!=Fire_city||p==3) 
		if(level<6)
		    sun=0;
		else if(level<8)
			sun=25;
		else if(level<10)
			sun=50;
		else
		    sun=50+(rand()%11)*5;
	else
		sun=0; 
	//杂项 		
	unfrozen_T=0;
	//总体性质
	sigma_produce=0;
	sigma_consume=0; 
	sigma_coins=0; 
	rank=0;
	points=0;	
	i_and_f=false;
	return;
} 

void Player::cards_set(User *p_user,bool if_use_self_def,bool if_pierce,int K,int map)
{
	int i,j,r,x; 
	bool accept;
	bool icy=false;
	bool fire=false;
	const int start_r=playernum*Pkind;
	if(map==Fire_city&&playernum!=3) 
		have[0]=&npc[playernum];
	else
		for(i=0;i<cards;i++)
		{
			rand()+rand();//增大随机性 
			do
			{ 			
				x=rand()%Pkind; 
				r=x+start_r;     //随机给予一张植物卡牌
				j=x-Cherry;
				accept=plant[r].univ_demand(level,if_use_self_def,(0<=j&&j<Locked_plants?unlocked[j]:false),if_pierce);
				if(map==Fire_city)
					switch(x) 
					{
						case 12:/*毁灭菇*/
						case 11:/*魅惑菇*/
						case 27:/*菜问*/
							accept=false; 
					}
				//else 			
			}
			while(	!accept || plant[r].belong!=NOBODY	);//如果有人拿了，或等级要求过高，则换一张
			if(plant[r].tag_j(IA))
				icy==true;
			else if(plant[r].tag_j(FA))
				fire==true;
			have[i]=&plant[r];
			plant[r].belong=&player[playernum];          //标记这张牌被拿了
			if(playernum==K-1) 
			{
				if(p_user->have(The_potion)&&!plant[r].tag_j(FA)) 
					plant[r].add("freeze_T",1);
				if(p_user->have(The_boots)&&!plant[r].tag_j(AS)) 
					plant[r].add("miss_P",42);
				if(p_user->have(The_sword)&&!plant[r].tag_j(AL))
				{
					plant[r].add("attack",5);
					if(iftrig(167))	
					{
						plant[r].add("sputter",7);
						if(plant[r].get("speed")>=Fast)
							plant[r].add("speed",-1);
					}
				}	
				if(p_user->have(The_shield))
				{
					plant[r].add("defence",4);	
					if(iftrig(250))		
					{
						plant[r].add("miss_P",42);
						plant[r].HP_modify("expand",12);
					}		
				}				
			}
		}
	i_and_f=(icy&&fire&&(cards<=4));
	return;
}

void Player::cards_showall(PW w,int K,int you,bool cheating_state)
{
	int i,j;
	int s1[w.set_btnN(K+1)][4];
	w.s1_link(s1);
	int card_num_of_line=(w.dy-8)/(SMA_dy+4);
	int imaginary_width=SMA_dy+4;
	int imaginary_width_2=w.dy/K;
	w.newpage();
	w.hint(2,sizeof("您获得如下**张卡牌："),"");
	if(playernum==you)
	    printf("您获得如下%d张卡牌：",cards); 
    else
        printf("这是%s的%d张卡牌：",name,cards);
    for(i=0;i<cards;i++)
	    have[i]->card_demon(  w.x+5+(SMA_dx+1)*(i/card_num_of_line)  ,  w.y+(i%card_num_of_line)*imaginary_width+4 ,1-have[i]->get("T next_actable"),SMA  );
	if(cheating_state)
	{
		//按钮相关设置 
	    BTN cheat_btn[K];
	    for(i=0;i<K;i++)
	        cheat_btn[i].judset(  i!=playernum  ); 
	    for(i=0;i<K;i++)
		    cheat_btn[i].set(  w.x+w.dx-8  ,  w.y+i*imaginary_width_2+(imaginary_width_2-Stdwidth)/2  ,  Stdheight  ,  Stdwidth  ,s1[i]);
        for(i=0;i<K;i++)
            cheat_btn[i].dye(player[i].name);
	    w.end_setall("开始游戏");
	    if(  w.do_action()!=K  )
	        player[  w.action  ].cards_showall(w,K,you,true);
    }
    else
    {
		w.hint(w.dx-10,sizeof("禁止查看他人卡牌"),"禁止查看他人卡牌");
		w.end_setall("开始游戏");
	    w.do_confirm(Notcount);
	}
	return;
}


void Player::storage_list(int x,int y,int dy/*不设最大高度*/)
{
	int i;
	int counter=0;
	int imaginary_width=sizeof("至少六个汉字");
	const int laidmax=dy/imaginary_width;
	for(i=0;i<cards;i++) 
	    if(have[i]!=now)
		{
			Place(x,y+counter*imaginary_width); 
			printf(have[i]->name);
			if(++counter==laidmax)
			{
				counter=0;
				++x;
				printf("\n");
			}
		}
	return;
}

void Player::combat_message(int x,int y,int T)
{
	
	level_color(level); 
	Place(x++,y);printf(" %s",name);
	Place(x++,y);printf(" 等级：%2d",level);
	Color(Light|White);
	Place(x++,y);printf(" 得分：%d",points);
	Place(x++,y);
	if(rank==0) 
	{
		printf(" 还剩%d张卡牌",cards);
		Place(x++,y);printf(" 阳光点数：%d",sun);
		Place(x++,y);
		if(T<unfrozen_T)
		{
			Color(Light|Cyan);
		    printf(" 冰冻状态(%d)",unfrozen_T-T);
		    Color(Light|White);
	    }
	} 
	else
	    printf("本局排名：%d",rank);
    return;
}
#define All_frozen -1
#define Break_up   -7 
int Player::gesture(PW w,int T,int K,bool be_ctrled)
{
	int i,p;
	int actable=0;
	int weight[K]={0};
	const char txt[3][5]={"锤子","剪刀","布"}; 
	int s1[3+1][4];
	int s2[K+1][4];
	const int imaginary_width=w.dy/3;
	w.newpage();
	for(i=0;i<K;i++)
	    if(player[i].unfrozen_T<=T/*包含T*/	&&	player[i].get("rank")==0/*没死*/ ) 
	    	{
	        	weight[i]=player[i].sigma_chance_get(T);
	        	++actable;
	    	}
	if(actable==0)
	    return All_frozen;
	if(!be_ctrled) 
	{
		if(unfrozen_T>T)//严格大 
		{
			w.hint(1,sizeof("你已被冰冻！"),"你已被冰冻！");
			w.hint(2,sizeof("其他玩家猜拳中..."),"其他玩家猜拳中...");
		}
		else
		{
			w.hint(1,sizeof("请选择“锤子、剪刀、布”："),"请选择“锤子、剪刀、布”：");
		    BTN gst_btn[3+1];
		    w.set_btnN(3+1);
		    w.s1_link(s1);
			for(i=0;i<3;i++)
			{
				gst_btn[i].judset(true);
				gst_btn[i].set(  w.x+3  ,  w.y+i*imaginary_width+3  ,  Stdheight  ,  Stdwidth-4  ,s1[i]);
				gst_btn[i].dye(txt[i]);
	    	}
	    	w.end_setall("退出战斗"); 
			w.do_action();
			if(w.action==3) 
				return Break_up;
		} 		
		p=weighted_random(weight,K);
	}
	else
	{
		w.hint(1,sizeof("请选择本回合主动玩家："),"请选择本回合主动玩家：");
	    BTN act_btn[K+1];
	    w.set_btnN(K+1);
	    w.s1_link(s2);
		for(i=0;i<K;i++)
		{
			act_btn[i].judset(player[i].unfrozen_T<=T/*包含T*/	&&	player[i].get("rank")==0/*没死*/);
			act_btn[i].set(  w.x+3+(i/2)*4  ,  w.y+6+(i%2)*22  ,  Stdheight  ,  Stdwidth  ,s2[i]);
			act_btn[i].dye(player[i].name);
    	}
    	w.end_setall("退出战斗"); 
    	do
			p=w.do_action(); 
		while(act_btn[p].jud==false);
		if(w.action==K) 
			return Break_up;
	}
	w.hint(11,sizeof("玩家获得本回合主动权"),"");
    if(  p==playernum  )
        printf("你获得本回合主动权");
    else
        printf("%s获得本回合主动权",player[p].name);
    Sleep(Std_flush_period*Std_wait_periods);
	return p;	
} 

int Player::card_choose(BOOK w,int T,int hard,int K,int page)
{
	int i,j;
	const int laidmax=w.dy/(BIG_dy+2);
	GOTOHERE_continue_to_choose:
	w.newpage(  (cards-1)/laidmax+1  ,  page  );
	const int laid=w.page<w.maxpage?  laidmax  :  cards-(w.maxpage-1)*laidmax;
	const int imaginary_width=w.dy/laidmax;
	int start_card=(w.page-1)*laidmax;
	w.hint(1,sizeof("请点击选择出战卡牌（左右按钮翻页）。您还剩余**张卡牌。"),"请点击选择出战卡牌（左右按钮翻页）。您还剩余");
	printf("%2d张卡牌",cards);
	//按钮相关设置 
	BTN plant_btn[laid];
	int s1[w.set_btnN(laid+3)][4];
	w.s1_link(s1);
	for(i=0;i<laid;i++)
	{
		plant_btn[i].judset(true);
		plant_btn[i].set(  w.x+5  ,  w.y+(i%laidmax)*imaginary_width+1  ,  BIG_dx  ,  BIG_dy  ,s1[i]);/*也正是卡牌区域*/
    }
	for(i=start_card;i<start_card+laid;i++)
	    have[i]->card_demon(  w.x+5 ,  w.y+(i%laidmax)*imaginary_width+1  ,(T==0?1:T)-have[i]->get("T next_actable"),  BIG  );
	w.page_setall(w.dx-8,5);
	w.end_setall("查看局势");
	w.do_action();
	switch(w.action-laid)
	{
		case 2:
			field_show(NULL/*在这里无所谓*/,NULL/*在这里无所谓*/,std_combat_f,T,hard,K,2/*在这里无所谓*/,playernum,true,7);
			goto GOTOHERE_continue_to_choose;
			break;
		case 0:
			card_choose(w,T,K,hard,page-1);
			break;
		case 1:
			card_choose(w,T,K,hard,page+1);
			break;
		default:
			now=have[  now_in_have=start_card+w.action  ];
			w.newline(1,sizeof("您选择了********"),"您选择了");
	        printf("%s",now->name);	
	        Sleep(Std_flush_period*Std_wait_periods); 
	}
	return now_in_have;
}

int Player::random_choose()
{
	int i;
	int weight[cards];
	for(i=0;i<cards;i++)
	    if(have[i]->get("level")==1)
	         weight[i]=10;
	    else
	         weight[i]=15;//高阶卡 
	now=have[  now_in_have=weighted_random(weight,cards)  ];
	return now_in_have;
}

Plant* Player::card_change(int situation,int T,int hard,int K,bool ifrealplayer,Plant* the_plant/*用不到时传NULL也行*/)
{
	Plant* back_value=now;
	Player *p=(the_plant->belong);
	const char *illustrate;
	int i;
	if(situation==Plant_die)
		illustrate="你的卡牌已死亡！";
	else if(situation==Explode)
	 	illustrate="你的卡牌已自爆！";
	else if(situation==Be_Captivate)
	 	illustrate="你的卡牌已被魅惑！";	 	 	
	switch(situation)
	{
	    case Buy:
			back_value=have[cards++]=the_plant;//加卡 
			the_plant->belong_change(this);
			break;
		case Captivate:
			have[cards++]=the_plant;//先收着，再抢走 
			back_value=p->card_change(Be_Captivate,T,hard,K,  p->playernum==K-1/*K-1为真玩家*/  ,the_plant);//为NULL则为抢夺玩家所有卡牌 
			break; 
		case Explode:
		case Plant_die:
			the_plant->belong_change(NULL);//植物死亡；初始化副效果已在函数中附带
		case Be_Captivate:
			now=NULL;/*无break*/
			for(i=now_in_have+1;i<cards;i++) 
			    have[i-1]=have[i];//抹掉了now_in_have 
			if(ifrealplayer)
	    	{
		    	PW w=p_action_pw;
		    	w.newpage();
		    	int s1[w.set_btnN(1)][4];//只有1个选项 
				w.s1_link(s1);
				w.hint(1,sizeof("你的卡牌已死亡！"),illustrate);
				if(--cards==0)//减卡
				{ 
					w.hint(3,sizeof("你已经无卡可选！"),"你已经无卡可选！");
					Sleep(Std_flush_period*Std_wait_periods);
					back_value=NULL;//返回值！
				} 
				else//未死光 
				{
					w.end_setall("选择新卡");
					w.do_confirm(Notcount); 
					card_choose(p_choose_card_bk,T,hard,K,1);
					now->last_action_T_reset(T);
				}
	    	}
    		else 
    		{				
				have[cards-1]=NULL;//减卡
				if(--cards==0) 
			        back_value=NULL;//返回值！ 
				else//未死光
				{ 
				    random_choose();
				    now->last_action_T_reset(T); 
				} 
			}     				 
			break;
    }
    return back_value;
}

#define SHOP 			0
#define ATTACT 			1
#define PRODUCE 		2
#define No_choice 		Absent
#define No_aim 			-4
#define You_No_choice	6
const int skill_trig[4]={0,12,24,150};
int Player::system_action(int T,int dT,int K,unsigned int seed,bool mainskill_not_forbidden)
{
	int N=3+SkillMax;
	int x;
	int P[N]={0};
	const int wounded=    now->get("HP_L")/2;
	const int dangerous=  40>wounded?wounded:40;
	int i; 
	shop_system.laid_find(seed,level);
	for(i=0;i<Max_Goods;i++)
	    if(  shop_system.randcard[i]>=0  &&  shop_system.cost[i]<=sun)
	        P[SHOP]+=(cards<=3?(cards<=1?35:15):7); 
	if(dT<0) //严格小于
		if(	P[SHOP]!=0	&&	iftrig(	P[SHOP]*20)		)
			return SHOP; 
		else
			return No_choice;
	if(!now->tag_j(AL))
		if(!now->if_havenot_explode())
	    	P[ATTACT]+=(rand()%15+10);
	if(now->tag_j(PD))
	    P[PRODUCE]+=(rand()%5+20);
	for(i=0;i<SkillMax;i++)
	    if(	mainskill_not_forbidden	&&	now->skill_avalible[i]>0/*=0即不可能选择，<0即非主动技*/	)
	    {
	    	x=now->skill_favor[i];
	    	if(Have_to<x&&x<0)
	    	{
				P[3+i]+=skill_trig[-x];
				if (now->skill_avalible[i]>=100/*无限次*/)
			    	P[3+i]*=2;
			}
			else if(x>0&&x<=sun)//付得起
				P[3+i]+=30;
			else if(x==Have_to)
				if(now->get("HP_M")<=dangerous)
			    	P[3+i]+=25;
			    else
			    	P[3+i]+=3;
		}
    return weighted_random(P,N);
} 
void Player::act(EFFECT *head,User *p_user,PW w,int T,int dT,int K,bool will_explode,int GT[][GO_THROUGH]/*go_through*/)
{
	int i,j;
	const int buttons        =3+SkillMax;
	const int imaginary_width=w.dy/buttons;
	const int real_width     =imaginary_width-4;
	const int btn_line		 =w.x+w.dx-9;
	int 	  btn_y;
	const char txt[buttons][5]={"商店","攻击","生产","一技","二技","三技"}; 
	srand((int)time(NULL));
	unsigned int seed=rand()+T;
	if(dT<0)
	{
		w.hint(3,sizeof("植物名称正在休眠状态（剩余0回合），无法正常行动！"),"");
		printf("%s正在休眠状态（剩余%d回合），无法正常行动！",now->name,-dT/*注意-号*/);
	}	     
	if(w.aut==true)
	{
		//以下为系统行动
		int sys_act;
		int s2[w.set_btnN(1)][4];
		do 
		{
			w.newpage();
		    w.hint(1,sizeof("玩家名称正在行动..."),"");
		    printf("%s正在行动...",name);
		    Sleep(Std_flush_period*5);
		    sys_act=system_action(T,dT,K,seed,	p_user->self_ctrl[isOthersObjSkillUseful]	);
			if(switch_of_act(head,p_user,w,T,K,seed,GT,sys_act))
			{			
				w.s1_link(s2);
				w.end_setall("继续");
				w.do_confirm(Notcount);				
			}
		}
		while(sys_act==SHOP);
	}
	else
	{
		BTN act_btn[buttons];
		int s1[w.set_btnN(buttons+1)][4];
		w.s1_link(s1);
		act_btn[0].judset(true);
		bool legal_aim=false;
		for(i=0;i<K;i++)
			if( i!=playernum  						&&
				player[i].get("rank")==0 			&&
				player[i].now!=NULL					&&/*因魅惑菇而加入*/
				!player[i].now->if_go_exploding()  
			  )//只打非己、存活、非本局即将爆炸玩家
			legal_aim=true;
		act_btn[1].judset(  !now->tag_j(AL)  &&  (now->if_go_exploding()||dT>=0/*可以取等*/ )  &&	legal_aim	);
		act_btn[2].judset(   now->tag_j(PD)  &&  dT>=0  );
		for(i=0;i<SkillMax;i++)
		{
			if(now->get("disposable"))//延时炸弹可以用技 
				act_btn[i+3].judset(  now->skill_avalible[i]>0	);
			else
		    	act_btn[i+3].judset(  now->skill_avalible[i]>0/*<0的为永久性技能*/  &&  dT>=0  );
		}
		for(i=0;i<buttons;i++)
			act_btn[i].set(  btn_line  ,  w.y+i*imaginary_width+1  ,  Stdheight  ,  real_width  ,s1[i]);
	    do
	    {
			w.newpage();
			if(will_explode)
				w.hint(1,sizeof("你的卡牌即将自爆！"),"你的卡牌即将自爆！");
			else
		    	w.hint(1,sizeof("请选择行动"),"请选择行动");
		    for(i=0;i<buttons;i++)
		        act_btn[i].dye(txt[i]);
			Color(w.dftc);
		    for(i=0;i<SkillMax;i++)
		    {
				btn_y=w.y+(i+3)*imaginary_width;
				Place(	btn_line-1	,	btn_y+1	 );
				now->skill_demon("name",i);
				Place(	btn_line+3  ,	btn_y+1  );
				now->skill_demon("avalible",i);
			}
	 	    w.end_setall("继续");
			do
			    w.do_action();
			while(  w.action!=buttons&&/*熔断保护*/act_btn[  w.action  ].jud==false); 
	   		switch_of_act(head,p_user,w,T,K,seed,GT,w.action);
		}
		while(w.action==SHOP);
	}	
	//所有人的
	Player *r; 
	for(j=0;j<K;j++)
	{
		r=&player[j];
		if( (j==K-1/*真*/||p_user->self_ctrl[isOthersSideSkillUseful])==true	&&	r->get("rank")==0  &&  r->now!=NULL/*魅惑的问题*/)
			for(i=0;i<SkillMax;i++)
				if(r->now->skill[i]!=NULL	&&	r->now->skill_avalible[i]==Always	&&	r->now->skill_aim[i]==Self)
					r->using_skill(head,w,T,K,i,Self);
	}
	return;
}
bool Player::switch_of_act(EFFECT *head,User *p_user,PW w,int T,int K,int seed,int GT[][GO_THROUGH]/*go_through*/,int choice)
{
	int i;
	int aim;
	SKILL_t skill_situation;
	bool redid=false; 
	switch(choice)
	{
		case SHOP:
			shopping(w,T,K,seed);			    
		    break;
		case ATTACT:
			GOTOHERE_REDID:
			aim=aim_at(head,w,T,K,Ordinate,GT,p_user->self_ctrl[isOthersSideSkillUseful]);
			if(redid)
				break;
			for(i=0;i<SkillMax;i++)
				if(now->skill[i]!=NULL&&now->skill_avalible[i]==Adjunct)
				{ 
					skill_situation=using_skill(head,w,T,K,i,	aim	);
					if(skill_situation>0)
					{ 
						w.newline(4,sizeof("附加技能xxxx发动成功！"),"附加技能");
						printf("%s发动成功！",now->skill_name[i]); 
						if(skill_situation==Can_do_more&&!redid)
						{
							redid=true;
							w.newline(4,sizeof("还有一次攻击机会"),"还有一次攻击机会");
							Sleep(Std_flush_period*5);
							goto GOTOHERE_REDID; 
						}
					}
					else
					{
						w.newline(4,sizeof("附加技能xxxx发动失败！"),"附加技能");
						printf("%s发动失败！",now->skill_name[i]); 						
					}
					Sleep(Std_flush_period*5); 
				} 
			break;
		case PRODUCE:
			produce(w,T);
			break;
		case No_choice: /*无break*/
		case No_aim: /*无break*/
		case You_No_choice:
			w.newline(1,sizeof("%s没有行动"),"");
			printf("%s没有行动",name); 
			break; 
		default:
			i=choice-3;
			if(now->skill[i]==NULL)
				w.newline(2,sizeof("ERROR：此技能尚未加入"),"ERROR：此技能尚未加入");//待优化 
			else
			{	
				aim=aim_at(head,w,T,K,now->skill_aim[i],GT,p_user->self_ctrl[isOthersSideSkillUseful]);
				skill_situation=using_skill(head,w,T,K,i,aim); 
				if(skill_situation>0)
				{ 				
					if(skill_situation==Captivate_kill)//魅惑菇专属技能
						GT[aim][MFKCD]|=MFKCD_K;//变相击杀 
					if(	aim==K-1	&&	(	skill_situation==Captivate_kill	||	skill_situation==Captivate_notkill	)	)
						return false;//无需停留且不显示继续按钮 
					w.newline(5,sizeof("技能发动成功！"),"");
					printf("%s发动成功！",now->skill_name[i]);
				}
				else
				{
					w.newline(5,sizeof("技能发动失败！"),"");
					printf("%s发动失败！",now->skill_name[i]); 						
				}
				Sleep(Std_flush_period*5);
			}
	}
	return true;
}
SKILL_t Player::using_skill(EFFECT *head,PW w,int T,int K,int sk_num,int aim)
{
	SKILL_t back_value;
	if(aim==Self)
		aim=playernum;//转换，两个aim意义不完全一致 
	EFFECT *E=apply_for(this,aim); 
	now->skill_use(sk_num,T);//次数消耗  
	back_value=now->skill[sk_num](now->skill_intensity[sk_num],T,K,aim,this,E);	
	new_EFF(head,E);//插入到技能链
	return back_value;			
}
void Player::produce(PW w,int T)
{
	int add=now->sun_produce(T);
	sun_add(add);
	w.newpage();
	Color(_White|Red|Light);
	w.RPlace(1,(w.dy-sizeof("你获得0000点阳光！"))/2);
	if(w.aut==true)
		printf("%s生产出了%d点阳光！（总计%d点）",name,add,sun);
	else//真玩家 
		printf("你获得%d点阳光！（总计%d点）",add,sun);
	sigma_produce+=add;	
	int s1[w.set_btnN(1)][4];
	w.s1_link(s1);
	w.end_setall("继续");	
	w.do_confirm(Std_wait_periods);  //fastback点中或等待1秒即可
	return;
}
  
bool Player::shopping(PW w,int T,int K,unsigned int seed)
{
	w.newpage();	
	shop_system.laid_find(seed,level/*玩家的level*/);
	int i,j;
	bool if_bought_sth=false;
	const int CHAR=3;  
	if(w.aut==true)
	{
		w.hint(1,sizeof("玩家名称购买了某些卡牌"),"");//若系统选择商店，则一定会购买 
		printf("%s购买了某些卡牌",name);
		int real_max_goods=limited_goods(level);
		int P[real_max_goods]={0};
		for(i=0;i<real_max_goods;i++)
	    	if(  shop_system.randcard[i]>=0  &&  shop_system.cost[i]<=sun)
	    		if(shop_system.cost[i]<=75)
			    	P[i]+=10; 
			    else
			    	P[i]+=15;
		int aim_good=weighted_random(P,real_max_goods);
		int cost=shop_system.cost[aim_good];
		sun_add(-cost); 
		Plant* p_goods=&plant[  shop_system.randcard[aim_good]  ];				
		sigma_consume+=cost;//消费性加分 
	    card_change(Buy,T,HARD/*以后优化*/,K,false,p_goods);
	    return true;
	} 
	else
	{
		int t;
		int imaginary_width=w.dy/Max_Goods;
		int cardline=w.x+4;
		int cardrow;
		int un_color;
		const char unfound[4][CHAR]=   {"尚","未","到","货"};
		const char ununlocked[4][CHAR]={"尚","未","解","锁"};
		const char (*txt)[CHAR];
		w.hint(1,sizeof("欢迎来到商店！您剩余的阳光"),"欢迎来到商店！您剩余的阳光：");
		printf("%4d",sun);
		//真玩家才看货架 
		for(i=0;i<Max_Goods;i++)
		{
			t=shop_system.randcard[i];
			cardrow=w.y+i*imaginary_width+(imaginary_width-SMA_dy)/2;
			if(t>=0)
		    	plant[t].card_demon(  cardline  ,  cardrow  ,1-plant[t].get("T next_actable"),SMA);
			else
			{
		   	 	if(t==Fail)
		        	un_color=_Purple|White|Light,           txt=unfound;
		    	else
		        	un_color=_Purple|_Light|Yellow|Light,   txt=ununlocked;
				Dyearea(  cardline  , cardrow  ,  SMA_dx  ,  SMA_dy  ,un_color);
		    	for(j=0;j<4;j++)
		    	{
		        	Place(cardline+1+j,cardrow+SMA_dy/2);printf("%s",txt[j]);  
		    	}
			}
		}
		//按钮相关设置 
		BTN buy_btn[Max_Goods];
		int s1[w.set_btnN(Max_Goods+1)][4];
		w.s1_link(s1);
		for(i=0;i<Max_Goods;i++)
	    	buy_btn[i].judset(  (shop_system.cost[i]!=0)&&(shop_system.cost[i]<=sun)  ); 
		for(i=0;i<Max_Goods;i++)
			buy_btn[i].set(  cardline+8  ,  w.y+i*imaginary_width+(imaginary_width-SMA_dy)/2  ,  Stdheight  ,  SMA_dy  ,s1[i]);
		w.end_setall("返回");
		//设置完成
		do
    	{
			for(i=0;i<Max_Goods;i++)
	        	if(shop_system.randcard[i]>=0)
	        	{
			    	buy_btn[i].dye(" ¤   ");
			    	printf("%3d",shop_system.cost[i]);/*紧跟着不用Place*/
		    	}
		    	else
					buy_btn[i].dye("---");
			do
		    	w.do_action();
			while(  w.action!=Max_Goods&&/*熔断保护*/buy_btn[  w.action  ].jud==false);
			switch(w.action)
			{
				case Max_Goods:
					break;
				default:
					if_bought_sth=true;
					int cost=shop_system.cost[w.action];
					Plant* p_goods=&plant[  shop_system.randcard[   w.action   ]  ];				
					sigma_consume+=cost;//消费性加分 
			    	w.newline(1,sizeof("成功购买卡牌：********"),"成功购买卡牌：");
			    	printf("%s",p_goods->name);
			    	w.hint(2,sizeof("您剩余的阳光："),"您剩余的阳光：");
	            	printf("%4d",sun_add(-cost));
	            	card_change(Buy,T,HARD/*以后优化*/,K,true,p_goods);
			    	for(i=0;i<Max_Goods;i++)//不可重复购买 
	                 	buy_btn[i].judset(  (i!=w.action)&&(shop_system.cost[i]!=0)&&(shop_system.cost[i]<=sun)  );
			    	break;
			}
    	}
   	 	while(w.action!=Max_Goods);
		return if_bought_sth;
	}	
}

void Player::make_attack(EFFECT *head,PW w,int T,int K,int A/*attact*/,int aim,int *GT,bool sideskill_not_forbidden)
{
	int i;
	bool revive=false;
	if(A==Fail_att)
	{
		GT[MFKCD]|=MFKCD_F;//攻击失败 
		return; 
	}
	else
	{
		int F/*freeze*/=now->freeze(player[aim].now->get("tag"));//每人的冰冻独立判断；若对着火焰冰冻，溅射的冰冻不再有效 
	    int W/*weaken*/=now->get("weaken");
		if(  F>0  &&  player[aim].now->tag_j(FL)  ) //冰冻可以摧毁飞行目标 
		    A=999;
		Player *p=&player[aim];    
		int attact_situation=p->be_attacked(T,A,F,W,PHYS,&GT[REALHURT]/*直接传数据*/);
		int passive_info;	
		if(aim==K-1||sideskill_not_forbidden)
			for(i=0;i<SkillMax;i++)
				if(p->now->skill[i]!=NULL)
				{
					int *q	=	&p->now->skill_avalible[i];
					if(*q==Passive	||	(*q==Passive_S&&attact_situation==KILL)	)
					{
						passive_info=p->using_skill(head,w,T,K,i,playernum/*作用于主攻玩家*/);
						if(passive_info==Revive)
						{
							w.newline(6,sizeof("玩家名称获得重生！"),"");
							printf("%s获得重生！",p->name);
							Sleep(Std_flush_period*5);
							revive=true;
						}
						else if(passive_info==Badluck)
						{
							w.newline(6,sizeof("玩家名称感觉到一丝不祥"),"");
							printf("%s感觉到一丝不祥",this->name);
							Sleep(Std_flush_period*5);
						}
						else if(passive_info==Backharm)
						{
							w.newline(6,sizeof("玩家名称感觉有点痛"),"");
							printf("%s感觉有点痛",this->name);
							Sleep(Std_flush_period*5);
						}
						else if(passive_info==End_blast)
						{
							w.newline(6,sizeof("玩家名称被玩家名称彻底激怒了！"),"");
							printf("%s被%s彻底激怒了！",p->name,this->name);
							Sleep(Std_flush_period*5);
						}
						if(*q==Passive_S)
							*q=0;//仅此一次 
					}
				}				
		switch(attact_situation)
		{
			case HURT:
				GT[FROZEN]=F;
				GT[WEAKEN]=W;
				if(now->tag_j(DA))//黑暗攻击，死了也有效
			        GT[MFKCD]|=MFKCD_D;
			    break;
			case KILL:
				if(!revive)//不是复活的 
					GT[MFKCD]|=MFKCD_K;
				if(now->tag_j(DA))//黑暗攻击，死了也有效
			    	GT[MFKCD]|=MFKCD_D;
			    break;
			case MISS:
				GT[MFKCD]|=MFKCD_M;
				break;
		}
    }
	return;
} 
void skill_attack(int T,int A,int F,int W,int att_kind,int aim,int *GT)//并非player成员 
{
	switch(  player[aim].be_attacked(T,A,F,W,att_kind,&GT[REALHURT]/*直接传数据*/)  )
	{
		case HURT:
			GT[FROZEN]=F;
			GT[WEAKEN]=W;
		    break;
		case KILL:
			GT[MFKCD]|=MFKCD_K;
		    break;
		case MISS:
			GT[MFKCD]|=MFKCD_M;
			break;
	}
	return;	
} 
#define std_weaken_T 2

int Player::be_attacked(int T,int A,int F,int W,int att_kind,int *real_damage)
{
	int influence=now->damage(A,att_kind,real_damage);
	if(influence==MISS)
	    return MISS;
	else
	    if(influence==KILL)
	        return KILL;//直接死亡无需多判断
		else
		{
			if(F!=0)	
			    unfrozen_T=T+1+F;//T+1回合开始算起 
	        now->strenth(-W/*注意是削弱*/,std_weaken_T);
	        return HURT; 
		} 	 
}	

int Player::system_aim(int K)
{
	int P[K]={0};
	int i;
	for(i=0;i<K;i++)
	    if( i!=playernum  						&&
			player[i].get("rank")==0 			&&
			player[i].now!=NULL					&&/*因魅惑菇而加入*/
			!player[i].now->if_go_exploding()   &&
			ally[i]!=Complete_ally 
		  )//只打非己、存活、非本局即将爆炸、非盟友玩家
	    {
			P[i]+=3;//基本 
			Plant *p=player[i].pget("main");
			if(  p->tag_j(FT)  &&  now->tag_j(ST)  )//打不到考虑 
			     continue;
			P[i]+=(p->get("value")/45)*3;//高价值目标 
			if(  p->get("HP_L")  <=  now->get("attack average"))//高几率击杀
				if(  p->get("HP_L")  <=  now->get("attack least")) 
					P[i]+=80;
				else
					P[i]+=40;
			P[i]+=(p->get("attack average")+p->get("sputter")/3)/5;
			P[i]+=p->get("freeze average")/200;
			if(p->tag_j(FA)&&now->tag_j(IA))//冰火克制考虑
				if(P[i]-=4<0)
					P[i]=0;
			if(  p->tag_j(MR)  &&  !now->tag_j(MR))//水陆克制考虑 
				if(P[i]-=3<0)
					P[i]=0;
			if(  p->tag_j(CV)  &&  now->tag_j(CT))//投罩克制考虑 
				if(P[i]-=5<0)
					P[i]=0;
			if(  p->tag_j(PD)  &&  now->tag_j(DA))//暗产克制考虑 
				P[i]+=10;//是+
			if(  p->tag_j(FL)  &&  now->tag_j(FT))//地空克制考虑 
				P[i]=0;
		}
	int S=0;
	for(i=0;i<K;i++)
		S+=P[i];
	if(S==0)//一个也不，随机选择
		for(i=0;i<K;i++)
	    	if( i!=playernum  						&&
			  	player[i].get("rank")==0 			&&
			    player[i].now!=NULL					&&/*因魅惑菇而加入*/
				!player[i].now->if_go_exploding()   &&
				ally[i]!=Complete_ally 
			  )//只打非己、存活、非本局即将爆炸、非盟友玩家
				P[i]=3;
	for(i=0;i<K;i++)
		S+=P[i];
	if(S==0)//仍然一个也不，不选择 
		return No_aim;
	else 
    	return weighted_random(P,K);	
}

int Player::aim_at(EFFECT *head,PW w,int T,int K,int aim_kind,int GT[][GO_THROUGH]/*go_through*/,bool sideskill_not_forbidden)
{
	int i,j;
	int aim;
	BTN att_btn[K-1];
	int s1[w.set_btnN(K-1)][4];/*注意-1*/
	w.s1_link(s1);
	w.newpage();
	if(w.aut==true)
	{
		if(aim_kind==Self||aim_kind==Others)
		{ 
			w.hint(1,sizeof("玩家名使用了技能！"),"");
			printf("%s使用了技能！",name);
			return aim_kind;//以后统一格式 
		}
		else
		{
			aim=system_aim(K);
			w.hint(1,sizeof("玩家名对玩家名发动了进攻！"),"");
			printf("%s对%s发动了%s！",	name,	player[aim].name,	aim_kind==Ordinate?"进攻":"技能"	);
			GT[aim][AIMED]=1;
		} 		
	}
	else
	{
		if(aim_kind==Self||aim_kind==Others)
		{
			w.hint(1,sizeof("你使用了技能！"),"你使用了技能");
			w.end_setall("确定"); 
			w.do_confirm(Notcount); 
			return aim_kind;
		}
		else
		{ 
			w.hint(1,sizeof("选择攻击对象"),"选择攻击对象"); 
		    //按钮相关设置  
		    int imaginary_width=w.dy/(K-1);
		    for(i=0;i<K;i++)
				if(i!=playernum)
				{
					j=i>playernum?i-1:i;
					att_btn[j].judset(  player[i].get("rank")==0/*是i不是j*/&&  ! player[i].now->if_go_exploding()  ); 
					att_btn[j].set(  w.x+w.dx-8  ,  w.y+i*imaginary_width+(imaginary_width-SMA_dy)/2  ,  Stdheight  ,  Stdwidth  ,s1[i]);
					att_btn[j].dye(  player[i].name/*这个是i不是j*/  );
		    	}
			aim=w.do_action();
			if(  aim>=playernum/*扣除自己*/  )
		        ++aim; 
		} 
	}
	
	if(aim_kind==Ordinate)//普通攻击
	{
		GT[aim][AIMED]=1;//被主攻 
		int A=now->attack(T,player[aim].now->get("tag"));
		make_attack(head,w,T,K,A,aim,GT[aim],sideskill_not_forbidden);
	    
		if(now->get("sputter")!=0&&A!=Fail_att/*失败的攻击无法溅射*/)
		    for(i=0;i<K;i++)
		    	if(  i!=playernum  &&  player[i].get("rank")==0  &&! player[i].now->if_go_exploding()  )//自己、死亡玩家、炸弹除外
		    	{
					GT[i][SPUTTER]=now->get("sputter");//大家sputter都一样，问题不大。 
		        	if(  i!=aim  )//主目标除外 
		        	{
						GT[i][AIMED]=2;//被溅射 
						make_attack(head,w,T,K,now->get("sputter"),i,GT[i],sideskill_not_forbidden);
					} 
				}		
	} 
	else
		GT[aim][AIMED]=1;
	return aim;
}


