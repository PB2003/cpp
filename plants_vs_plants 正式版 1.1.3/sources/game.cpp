
#define _GAME_CPP_

#ifndef _PLAYERS_CPP_ 
    #define _PLAYERS_CPP_
    #include "players.cpp"
#endif

#ifndef _RECORD_CPP_ 
    #define _RECORD_CPP_
    #include "record.cpp"
#endif

#ifndef _MAPS_CPP_ 
    #define _MAPS_CPP_
    #include "maps.cpp"
#endif

#define Instant_and_continue		0
#define End_of_battle 				-20
#define All_frozen_and_continue		-30
int field_show(User *p_user,EFFECT *head,FIELD f,int T,int hard,int K,int R,int you,bool ifinstant,int map)
{	
	int i,m,j;
	int winner;
	int set_R_count=0;
	int M=K;//区分不同用途 
	int gothru[M][K][GO_THROUGH];/*发动者、承受者、状态*/ 
	bool will_explode[K];
	for(i=0;i<K;i++)
		will_explode[i]=false;
	bool all_lack_att=true; 			
	for(i=0;i<K;i++)
		if(player[i].get("rank")==0	&& player[i].now!=NULL)//没死 
			all_lack_att=(all_lack_att&&player[i].now->tag_j(AL));
	int exist_explode=0; 
	int dT[K]={0};
	bool skill_sputter=false;
	f.set_players(K,you); 
	//按钮设置 
	if(ifinstant)//临时查看局势用 
	{
		f.show_cards(T,dT,hard);
		int s1[1][4];
		BTN end_btn;
		end_btn.set(  4  ,  (Max_dy-Stdwidth)/2  ,  Stdheight  ,  Stdwidth   ,  s1[0]);
		end_btn.judset(true);
		end_btn.dye("返回"); 
		Effective(p,s1,1,true,Notcount,Std_flush_period,false);
		return Instant_and_continue;
	}	
	else
	{
		for(m=0;m<M;m++)
			for(i=0;i<K;i++)
			{ 
				for(j=0;j<GO_THROUGH;j++)
					gothru[m][i][j]=0;
				gothru[m][i][REALHURT]=DIDNOT;	
			}	
		for(m=0;m<M;m++)
			if(player[m].get("rank")==0) 
				dT[m]=T-player[m].now->get("T next_actable");//千万记得扣除死玩家
		f.show_cards(T,dT,hard);
		for(m=0;m<M;m++)
		{ 
			if(  player[m].get("rank")==0/*熔断保护*/  &&  player[m].now->tick()  )
			{
				 will_explode[m]=true;
				 ++exist_explode;
			}
		}	
		if(exist_explode!=0)//炸弹先行
	 	{ 
			if(exist_explode==K)//全炸了
			{
				for(m=0;m<M;m++)
				{ 
					f.renew(m,T,dT[m],EXP_BIG);
					if(  player[m].get("rank")==0/*熔断保护*/  &&  player[m].card_change(Explode,T,hard,K,m==you,player[m].now)==NULL/*死光*/  )
					{						 
						player[m].rank_set(R);			
						++set_R_count;
					}
					else
						if(m==you)//刷掉弹窗 
							f.show_cards(T,dT,hard);
				}
				return set_R_count;
			} 
			else
				for(m=0;m<K;m++)
					if(will_explode[m])
						player[m].act(head,p_user,  m==you?  p_action_pw:s_action_pw  ,T,dT[m],K,will_explode[m],gothru[m]);	
		}//括号必须打上		
		else
		{

			if(all_lack_att)
			{
				int min_HP=1000,HP_t;
				int useless_dam[1]; 
				for(i=0;i<K;i++)
				{
					HP_t=player[i].now->get("HP_L");
					if(HP_t<min_HP)
						min_HP=HP_t;
				}
				for(i=0;i<K;i++)
				{
					player[i].now->damage(min_HP,REAL,useless_dam);//一起扣到其中一方死
					if(player[i].now->get("HP_L")==0)
						gothru[0][i][MFKCD]|=MFKCD_K;
				}
				f.renew_s(T,dT,BIG); 
			}
			else//玩家猜拳
				if(  (winner=player[you].gesture(p_gesture_pw,T,K,p_user->self_ctrl[controlable]))<0  ) 
				{
					Sleep(Std_flush_period*3);
					if(winner==All_frozen)
						return All_frozen_and_continue;
					else
						return Break_up;
				}
				else
			 		player[winner].act(head,p_user,	winner==you?p_action_pw:s_action_pw,    T,dT[winner],K,will_explode[winner],gothru[winner]);
		} 		    
	}
 
	//必须按照项而不是人来	
	int aim[M];
	register int am;
	int anim[K][5];//为大字显示的定位位置,所有人求和即可 
	bool jud_shu=false;
	bool jud_wea[M]={false};
	bool jud_fro[M]={false};
	bool jud_kil[M]={false};	
	for(i=0;i<K;i++)
		f.player_place_get(i,anim[i]);//显示定位 
	if(all_lack_att)//直接前往死亡界面
		goto GOTOHERE_DEATH; 
	for(m=0;m<M;m++)
	{
		aim[m]=DIDNOT;		
		for(i=0;i<K;i++)		
	    	if(gothru[m][i][AIMED]==1)//确定主目标
				aim[m]=i; 
	}
    for(m=0;m<M;m++) 
		if((am=aim[m])!=DIDNOT)
			if(gothru[m][am][MFKCD]&MFKCD_F)//闪避是全场的
			{
				//printf("%d  %d  ",anim[am][3],anim[am][4]);D("SHUN L144") //debug
				print_long_word(_Green,anim[am][3],anim[am][4],(char*)"SHUN");
				jud_shu=true;
			}
	f.show_cards(T,dT,hard);
	//爆炸显示，不管闪不闪，炸弹都要炸 
	for(i=0;i<K;i++)
		if(will_explode[i])
		{
			f.renew(i,T,dT[i],EXP_BIG);
			if(player[i].card_change(Explode,T,hard,K,i==you,player[i].now)==NULL/*死光*/)
			{						 
				player[i].rank_set(R);			
				++set_R_count;
			}
			else
				if(i==you)//刷掉弹窗 
					f.show_cards(T,dT,hard);
		}
	if(!jud_shu)//遥相呼应 
	//顺序：爆炸、技能、(闪避、伤害、溅射)、弱化、冰冻 
	{	
		//技能部分
				
		EFFECT *p=new EFFECT;
		int *effect; 
		p=head->next;
		while(p!=NULL)
		{	
			if(p->from_T<=T)//已生效技能
				for(i=0;i<K;i++)
					if(player[i].get("rank")==0/*熔断*/	&& player[i].now!=NULL		)/*没死*/
					{ 
						effect=p->eff[i];
						if(effect[e_HP_M]!=0	&&	effect[e_HP_M]<1000/*未知原因错误，不得已而为之*/ )
						{
							player[i].now->HP_modify("boost",effect[e_HP_M]);
							print_big_number(_White|_Light,anim[i][3],anim[i][4]+8,	effect[e_HP_M]	); 
							Sleep(Std_flush_period*3);
							f.renew_s(T,dT,BIG);
						}
						if(effect[e_HP_L]!=0)
						{
							bool die_before_gain=false;
							for(m=0;m<M;m++)//使用m没有问题 
								die_before_gain  =  die_before_gain  ||  (gothru[m][i][MFKCD]&MFKCD_K) ;//一个击杀就死 
							if(!die_before_gain)
							{
								player[i].now->HP_modify("gain",effect[e_HP_L]);
								print_big_number(_White,anim[i][3],anim[i][4]+8,	effect[e_HP_L]	); 
								Sleep(Std_flush_period*3);
								f.renew_s(T,dT,BIG);								
							}
						} 
						if(effect[e_att]!=0||effect[e_frozen]!=0||effect[e_weaken]!=0)
						{							
							int GT[GO_THROUGH]={0};
							int m_value=p->maker->playernum;
							if(i!=p->aim)
								skill_sputter=true;//说明发动了技能溅射 
							skill_attack(T,effect[e_att],effect[e_frozen],effect[e_weaken],effect[e_att_kind],i,GT);
							//攻击叠加 
							int *hurt;
							hurt=&gothru[m_value][i][REALHURT];
							if(*hurt==DIDNOT)
								*hurt=GT[REALHURT];
							else
								*hurt+=GT[REALHURT]; 
							//冰冻弱化叠加 
							gothru[m_value][i][WEAKEN]=max(GT[WEAKEN],gothru[m_value][i][WEAKEN]);
							gothru[m_value][i][FROZEN]=max(GT[FROZEN],gothru[m_value][i][FROZEN]);
							//死亡纪录
							gothru[m_value][i][MFKCD]|=(GT[MFKCD]&MFKCD_K);
						}
						if(effect[e_att_add]!=0)
						{
							player[i].now->strenth( effect[e_att_add],1/*待优化*/);
							print_big_number(_Red|_Light,anim[i][3],anim[i][4],	effect[e_att_add]	); 
							Sleep(Std_flush_period*3);
							f.renew_s(T,dT,BIG);
						}
						if(effect[e_def_add]!=0)
						{
							player[i].now->shield( effect[e_def_add],1/*待优化*/);
							print_big_number(_Purple|_Light,anim[i][3],anim[i][4],	effect[e_def_add]	); 
							Sleep(Std_flush_period*3);
							f.renew_s(T,dT,BIG);
						}
						if(effect[e_produce]!=0)
						{
							player[i].sun_add(effect[e_produce]); 
							print_big_number(_Yellow|_Light,anim[i][3],anim[i][4],effect[e_produce]	); 
							Sleep(Std_flush_period*3);
							f.renew_s(T,dT,BIG);
						}
					}
			p=p->next;    	
		}
		//闪避、伤害、溅射显示
		for(m=0;m<M;m++) 
			for(i=0;i<K;i++)
		    	if(gothru[m][i][MFKCD]&MFKCD_M)
		    	{
					print_long_word(_Green,anim[i][3],anim[i][4],(char*)"MISS");//相对各个攻击的MISS独立 
					if(i==you)
						p_user->add("tt_miss",1);//统计量 
				}
		//伤害显示
		for(m=0;m<M;m++)
			if((am=aim[m])!=DIDNOT)
			{
				if(gothru[m][am][REALHURT]!=DIDNOT/*攻击了*/&&(gothru[m][am][MFKCD]&MFKCD_M)==0/*没能闪*/)
				{
					print_big_number(_Red,anim[am][3],anim[am][4],-gothru[m][am][REALHURT]); 
					player[m].points_add(gothru[m][am][REALHURT]/10); 
	    		}
	    		//溅射显示（全体） 
				if(gothru[m][am][SPUTTER]!=0	||	skill_sputter  )
				{
					if(gothru[m][am][SPUTTER]!=0) 
		    			print_big_number(_Yellow  ,Max_dx/2-6  ,Max_dy/2-14  ,  -gothru[m][am][SPUTTER]  );//屏幕中心打印
					//溅射显示（实际）
					for(i=0;i<K;i++) 
		    			if(  gothru[m][i][AIMED]==2  &&  	(gothru[m][i][MFKCD]&MFKCD_M)==0/*没能闪的副目标*/||
							 skill_sputter 			 && 	gothru[m][i][REALHURT]!=DIDNOT/*技能溅射（本质不可闪避）*/  		)
							print_big_number(_Red,anim[i][3],anim[i][4],-gothru[m][i][REALHURT]);			 
	    		}
				Sleep(Std_flush_period*3);
				f.show_cards(T,dT,hard);
				//弱化显示 
				for(i=0;i<K;i++)
					if(gothru[m][i][WEAKEN]!=0)
					{
						jud_wea[m]=true;
						print_sign(_Blue|_Light,anim[i][3],anim[i][4],'b');
						print_big_number(_Blue|_Light,anim[i][3],anim[i][4]+12,gothru[m][i][WEAKEN]);	
					} 
				if(jud_wea[m]==true)
				{
					Sleep(Std_flush_period*3);
					f.renew_s(T,dT,BIG);
				}
				//冰冻显示 
				for(i=0;i<K;i++)
					if(gothru[m][i][FROZEN]!=0)
					{
						jud_fro[m]=true;
						print_big_number(_Cyan|_Light,anim[i][3],anim[i][4]+12,gothru[m][i][FROZEN]);
						player[m].points_add(Freeze_pt*gothru[m][i][FROZEN]);//冰冻加分 
						f.renew(i,T,dT[i],ICY_BIG);
					}
				if(jud_fro[m]==true)
				{
					Sleep(Std_flush_period*3);
					f.renew_s(T,dT,BIG);
				} 								
			}						
		//黑暗显示略
		
	}
	GOTOHERE_DEATH:
	bool die;
	for(i=0;i<K;i++)//死亡显示,统一最后一起显示
	{
		die=false;
		for(m=0;m<M;m++)
			die  =  die  ||  (gothru[m][i][MFKCD]&MFKCD_K) ;//一个击杀就死，魅惑此时被计入 
		if(  die  &&  (will_explode[i]==false)	)//不是自爆 
		{	
			if(winner==you)//虽然不太合理 
				p_user->add("tt_kill",1);//统计量 
			player[winner].points_add(i==aim[winner]?M_kill_pt:S_kill_pt); 
			if(player[i].now!=NULL) //魅惑致死不显示 
				f.renew(i,T,dT[i],DEAD_BIG);	
			if(player[i].now==NULL/*熔断*/||player[i].card_change(Plant_die,T,hard,K,i==you,player[i].now)==NULL/*死光*/)
			{						 
				player[i].rank_set(R);			
				++set_R_count;	 
			}
			else
				if(i==you)
					f.show_cards(T,dT,hard);
		}
	}
	if(player[you].get("rank")!=0)//真玩家已经结束
	{
		PW w=p_action_pw;
		w.newpage();
		int s1[w.set_btnN(1)][4];//只有1个选项 
		w.s1_link(s1);
		w.hint(1,sizeof("你已出局！"),"你已出局！");
		w.end_setall("查看战绩");
		w.do_confirm(Notcount); 
		return End_of_battle;
	} 
	else
		return set_R_count;
}

void start_distribute(int K,int realperson,int start_cards,User *p_user,int map)
{
	int i;
	int rule1=p_user->self_ctrl[adapt_selfdef];
	int rule2=p_user->self_ctrl[pierce];
	for(i=0;i<K;i++)
	    player[i].cards_set(p_user,rule1,rule2,K,map);
    player[realperson].cards_showall(p_start_pw,K,realperson,	p_user->self_ctrl[isOthersCardsVisible]	);
    Color(_Black);
	system("cls");
	return;
}

const int lootkind=4;
struct Loot
{
	const int need_map;
	const int need_hard;
	const int threshold;
	const int P;
	const int item;
}loot[lootkind]={
					{Tundra,NORMAL,6500,100,The_ice},
					{Mansion,NORMAL,6700,80,The_emerald},
					{Crimson_forest,NORMAL,7200,70,The_ingot},
					{End_city,NORMAL,7500,60,The_perl},
				};

void settlement(User *p_user,int hard,int K,int realperson,int back[4],int initial_cards,int map)//得分、最高分和经验结算 
{
	int i;
	int rk_p;
	const int Leaf_threshold=2000;
	const int Leaf_P=50;
	bool no_cheat=p_user->self_ctrl[controlable]==false;
	for(i=0;i<K;i++)
	{
		rk_p=player[i].get("rank");
		player[i].points_add(final_pt[  rk_p==0?0:rk_p-1  ]);
		player[i].points_add(player[i].get("sigma_consume"));
		player[i].points_add(player[i].get("sigma_produce"));
		if(i==realperson)
			p_user->add("tt_prod",player[i].get("sigma_produce"));
	}
	int all_pt=player[realperson].get("points");	
	if(back[0]=(	(  all_pt>  p_user->get("highest_point"))	&&	no_cheat))//最高分是否打破 
		p_user->flush("highest_point",all_pt);
	int exp_add=log_2(initial_cards)*all_pt/(120+rand()%81);
	int d=2000/*经验上限*/-p_user->get("exp");	
	back[1]=(	hard==HARMONY||	!no_cheat	?	0:p_user->add("exp",d>exp_add?exp_add:d));//经验值
	back[2]=back[3]=back[4]=0;
	int basic_coins=all_pt/((map==Badland?(200+rand()%31):(270+rand()%61))-log_2(initial_cards)*35);
	if(no_cheat)
	{	
		if(player[realperson].i_and_f_mission()==true)//冰火成就 
		p_user->add("ice&fire",1);
		if(hard==HARD) basic_coins*=(rand()%5?3:2);
		else if(hard==HARMONY) basic_coins/=2;
		back[2]=p_user->add("coins",basic_coins+player[realperson].get("sigma_coins"));
		if(	back[3]=(	hard==HARD	&&	all_pt>Leaf_threshold	&&	iftrig(	Leaf_P*(all_pt>Leaf_threshold*4?2:1)))	)//是否有条件获得世界树之叶 
			p_user->obtain(The_leaf,1);	
		for(i=0;i<lootkind;i++)
			if(	back[4]=
				(map==loot[i].need_map		&&
				hard>=loot[i].need_hard		&&
				all_pt>loot[i].threshold	&&
				iftrig(loot[i].P))					)
			{
				p_user->obtain(loot[i].item,1);
				break;
			}	
		if(map==Badland&&all_pt>1000)
			p_user->add("building",back[5]=all_pt/(25+rand()%55));
	}
	p_user->record_users_information();//存档 
	return;
}
int plant_init(bool locked_visible,User *p_user,int map)
{
	int i,j,k,n;
	int *p;	
	for(i=0;i<CardsMax;i++)
	{
		if(	((j=i%Pkind)!=Cherry-2&&j!=Cherry-1)||p_user==NULL/*保护*/	)
			plant[i].set_all(j,plantsname[j],ability[j],skill_temp[j],map);
		else
		{	
			p=p_user->DIY_temp[j-(Cherry-2)];
			Skill selfdef_skill=skill_temp[0];
			Skillname *s;
			for(k=0;k<SkillMax;k++)
				if(p[Properties+k]!=0)
				{
					s=&skillname[	p[Properties+k]	];
					selfdef_skill.count[k]=(s->act_kind==Objective?1:s->act_kind);
					selfdef_skill.aim[k]=s->act_aim;
					selfdef_skill.use[k]=s->content;
					selfdef_skill.intensity[k]=1;//以后优化	
					selfdef_skill.favor[k]=s->favor;
				}
			plant[i].set_all(j,plantsname[j],p,selfdef_skill,map);
		}
		++n; 
	}
	if(map==Fire_city)
		for(j=0;j<NPCkind;j++)
			npc[j].set_all(j,NPCsname[j],NPCsability[j],NPCsskill_temp[j],Fire_city);
	return n;
}
void game(  User *p_user,int hard,int K,int start_cards,bool fortune,int map)
{
	PW w={Std_Uboundry,Std_Lboundry,Std_dx,Std_dy,_White|Blue,false};
	int s1[w.set_btnN(1)][4];//只有1个选项 
	w.s1_link(s1);
	int i,r;
	int R=K/*排名*/;
	int realperson=K-1;//规定 
	int T=0;/*回合数*/;
	int back[6]={0};
	//技能链初始化 
	EFFECT *head;
	head=new EFFECT;  
	head->from_T=0;
	head->to_T=0;
	head->next=NULL;
	//全场清零
	system("color 0f");
	system("cls");
	if(map==Fire_city)
	{
		w.newpage();
		tf.newtxtf(w.x+1,w.y+2,18,86,1,_Light|_White); 
		tf.say("阿斯尼坦王国是一个和平安宁的国度。");
		tf.say("王国的边陲小镇炎城盛产火元素结晶，能源产业发达，人民生活富足。");
		tf.say("炎城矿区靠近绯红森林——曾经的魔兽老巢。");
		tf.say("对此，炎城建立了自己的地方武装——炎城自卫队。");
		tf.say("但是有一天，一切突然灰飞烟灭。");
		tf.say("此前，炎城自卫队第三小队队长陈刚发现了魔兽即将大举进攻炎城。");
		tf.say("报信路上，陈刚和AB两个队员突遇火焰巨龙。");
		tf.say("火焰巨龙发出古老的魔音，陈刚听到了死神的低语。");
		tf.say("（不过死神说的是：“不要这个”）");
		tf.say("总之陈刚没有死。（但也差不多了）");
		w.end_setall("继续");
		w.do_confirm(Notcount);
		tf.newtxtf(w.x+1,w.y+2,18,86,1,_Light|_White); 
		tf.say("拖着伤痕累累的身体，陈刚返回了炎城。");
		tf.say("但已经迟了。炎城已经被不可计数的魔兽所包围。");
		tf.say("陈刚失去了意识，永远地闭上了双眼。");
		tf.say("（永远吗？我看不见得......）");
		tf.say("（已经迟了吗？我看不见得......）");
		w.spe_hint(15,sizeof("炎城决战即将开始！"),"炎城决战即将开始！",L_White|Red|Light);
		w.spe_hint(17,sizeof("tips：击败被魔兽操控心智的陈刚，帮其恢复心智"),"tips：击败被魔兽操控心智的陈刚，帮其恢复心智",L_White|Red|Light);
		w.end_setall("巅峰对决");
		w.do_confirm(Notcount); 
	}
	//初始化
	int visP=plant_init(true,p_user,map);
	for(i=0;i<K;i++)
		player[i].set_all(  i==realperson?  p_user/*真*/  :  NULL/*假*/  ,hard,i,start_cards,fortune,map);
	//开始发牌 
	start_distribute(K,3,start_cards,p_user,map);
	//开始选择第一张卡 
	player[realperson].card_choose(p_choose_card_bk,T,hard,K,1);//他人的选择不能一开始被看到 
	for(i=0;i<K;i++)
	    if(i!=realperson)
           	player[i].random_choose();
    //开始战斗
	while(++T)
	{	
        r=field_show(p_user,head,std_combat_f,T,hard,K,R,realperson,false,map);
        if(r>=0)//过滤掉End_of_battle和All_frozen_and_continue 
			R-=r;
		else if(r==Break_up)
			break;		
        clear_EFF(head,T);//清空旧技能 
        for(i=0;i<K;i++)
			if(player[i].get("rank")==0)
			     player[i].points_add(log_2(T));
        if(R==1||R==0/*同归于尽*/||r==End_of_battle)
        {
			int rk; 
			if(R==1)
				for(i=0;i<K;i++)
			    	if(player[i].get("rank")==0)
			        	player[i].rank_set(1);
			w.newpage();
			if(map==Fire_city)
			{
				tf.newtxtf(w.x+1,w.y+2,18,86,1,_Light|_White); 
				int passed=player[realperson].get("rank");
				if(passed==1)
				{
					p_user->add("fire_city_pass",1);
					tf.say("在你的努力之下，陈刚恢复了心智。");
					tf.say("陈刚带领的小队早已获得了大量敌后情报。");
					tf.say("炎城虽然不复以往的样貌，但还可以重建。当务之急是摧毁魔兽的据点。");
					tf.say("在你的鼎力相助之下，陈刚召集到了大量兵源，作为战争领袖开展了反击战。");
					tf.say("然后他们打赢了。（自己脑补场景）");
				}
				else
				{
					tf.say("你的被魔化陈刚打成重伤，捡了一条命逃回来。");
					tf.say("炎城幻灭。");	
					tf.say("据说绯红森林中茂密的垂泪藤就是战争中流离失所和死于非命的士兵的眼泪所化。");	
				} 
				w.spe_hint(16,sizeof("感谢《幻灭炎城》开发团队提供故事素材！"),"感谢《幻灭炎城》开发团队提供故事素材！",L_White|Green);
				w.end_setall("结束了");
				w.do_confirm(Notcount);	
				w.newpage();
			} 
			w.hint(1,sizeof("游戏结束！"),"游戏结束！");
			settlement(p_user,hard,K,realperson,back,start_cards,map);//得分、最高分和经验结算
			for(i=0;i<K;i++)
			{
				w.hint(3+i,sizeof("玩家名字获得第*名，总分：10000"),"");
				if((rk=player[i].get("rank"))!=0)
					printf("%s获得第%d名，总分：%d",player[i].name,rk,player[i].get("points"));
				else
					printf("你没能打败%s，其总分：%d",player[i].name,player[i].get("points"));
			}
			if(p_user->self_ctrl[controlable]==false)
				new_record(player[realperson].get("points"),p_user->name);
			if(back[0])
				w.spe_hint(10,sizeof("恭喜您打破纪录！"),"恭喜您打破纪录！",_White|Red|Light);
			w.spe_hint(12,sizeof("您获得经验：00    金币：00"),"您获得经验：",_White|Green|Light);printf("%d    金币：%d",back[1],back[2]);
			int line=12;
			if(back[3])
				w.spe_hint(line+=2,sizeof("恭喜您获得随机战利品：世界树之叶*1"),"恭喜您获得随机战利品：世界树之叶*1",_White|Green);
			if(back[4])
				for(i=0;i<lootkind;i++)
					if(map==loot[i].need_map)
					{
						w.spe_hint(line+=2,sizeof("恭喜您获得特产战利品：物品名称*1"),"恭喜您获得随机战利品：",_White|Green);
						printf("%s*1",thingname[loot[i].item]); 
						break;
					}
			if(back[5])
			{
				w.spe_hint(line+=2,sizeof("教学楼施工进度+100‰"),"教学楼施工进度+",_White|Cyan);
				printf("%d‰",back[5]);
			}
			#define fire_entering_threshold 3000
			#define fire_entering_P 333
			if(	map==Crimson_forest											&&
				player[realperson].get("points")>=fire_entering_threshold	&&
				p_user->have(The_map)>0										&&
				iftrig(fire_entering_P)
				)
			{
				w.spe_hint(line+=2,sizeof("带着地图，你不经意间找到了炎城的入口。"),"带着地图，你不经意间找到了炎城的入口。",_White|Cyan);
				int s2[w.set_btnN(2)][4];
				w.s1_link(s2);
				BTN choose_btn[2];
				for(i=0;i<2;i++) 
				{
					choose_btn[i].set(w.x+w.dx-5,w.y+20+i*40,Stdheight,Stdwidth,s2[i]);
					choose_btn[i].judset(true);
					choose_btn[i].dye(i==0?"进入炎城":"半途而废");
				}
				if(w.do_action()==0)
				{ 
					game(p_user,HARD,4/*限定*/,10/*卡牌数*/,false/*fortune*/,Fire_city);
					return; 
				} 
			}
			else
			{
				w.end_setall("退出游戏");
				w.do_confirm(Notcount);				
			}
			break;
		}
	} 
	//收拾桌面
	delete head;
	plant_init(true,p_user,0/*map*/);
	return;	
}

void gamemode(User *p_user)
{ 
	PW w={1,1,Max_dx,Max_dy,_Black|White|Light,false};
	int i;
	const int pp_btns=3;
	const int md_btns=4;
	const int swit_btns=pp_btns+1+md_btns; 
  	const int btns=swit_btns+5;//取默认、设默认、开始、四叶苜蓿、地图 
  	const int line[4]={w.x+9,w.x+16,w.x+21,w.x+29};
  	const int pp_imdy=Max_dy/4; 
  	const int st_y=w.y+14;
  	const int md_imdy=Max_dy/4; 
  	const int min_cards=1;
  	const int max_cards=10;
  	
  	int K=0;
  	int start_cards=0;
  	int mode=0;
  	
  	bool p_chosen=false;
  	bool m_chosen=false;
	bool fortune=false;
	
  	int s1[w.set_btnN(btns+1)][4];
	w.s1_link(s1);
  	BTN 	pp[pp_btns]; 
  	INP_BAR cd={  line[1]  ,  st_y  ,  sizeof("请输入初始卡牌数（1~10之间）...")+6  ,  _White|_Light  };
  	BTN 	md[md_btns];
  	BTN     st;
	BTN		defal; 
	BTN		set_defal; 
	BTN		use_fortune; 
	BTN		map_btn; 
	PICT	map=map_pict;
  	const char *pp_txt[pp_btns]={"2人","3人","4人"}; 
  	const char *cd_txt="请输入初始卡牌数（1~10之间）...";
  	const char *md_txt[md_btns]={"和平","简单","普通","困难"};
	system("color 0f");
	system(size_cmd);
	w.hint(1,sizeof("请设置战斗模式"),"请设置战斗模式");
	w.hint(3,sizeof("（有一些模式暂未开放）"),"（有一些模式暂未开放）");
	for(i=0;i<pp_btns;i++) 
	{
		pp[i].judset(  i==2?true:false/*true*/  );
		pp[i].set(  line[0]  ,  15+i*pp_imdy ,  Stdheight,  Stdwidth,  s1[i] ); 
	}
  	for(i=0;i<md_btns;i++) 
	{
		md[i].judset(  true  );
		md[i].set(  line[2]  ,  15+i*md_imdy ,  Stdheight,  Stdwidth,  s1[i+pp_btns+1] ); 
	}
	const int y2=30;
	const int tf_x=3;
	const int tf_y=120;
	const int for_x=28;
	const int for_y=130; 
	defal.set	 	(  line[3]  , y2  				  ,  Stdheight,  Stdwidth,  s1[swit_btns] ); 	
	st.set		 	(  line[3]  , Max_dy-y2-Stdwidth ,  Stdheight,  Stdwidth,  s1[swit_btns+1] ); 
	set_defal.set	(	tf_x+7   , tf_y+5 			  ,  Stdheight,  Stdwidth,  s1[swit_btns+2] );
	use_fortune.set	(	for_x   , for_y	  ,  9,  13,  s1[swit_btns+3] );
	map.set(	Max_dx-11	,	8	); 
	map.make_b(&map_btn,s1[swit_btns+4],true);
	const int temps=3;	
	bool temp_complete[temps]={false};
	bool complete;		
	do
	{
		//jud部分 
		complete=true;
		for(i=0;i<temps;i++)
			complete=(complete&&temp_complete[i]);
		defal.judset(true);
		st.judset(complete);
		set_defal.judset(complete);
		use_fortune.judset(	p_user->all_have[The_clover]>0	); 
		//dye部分 
		for(i=0;i<pp_btns;i++)
			pp[i].dye(pp_txt[i]);
		if(start_cards==0)
			cd.setall(cd_txt,s1[pp_btns]);
		else
			{cd.newtxt("");printf("%d",start_cards);}
		for(i=0;i<md_btns;i++)
			md[i].dye(md_txt[i]);
		Color(w.dftc);Place(Max_dx-3,12);printf("地图");
		map.draw(-1);
		st.dye("开始游戏");
		defal.dye("采用默认");
		//tf框部分 
		tf.newtxtf(tf_x,tf_y,15,25,1,_White|_Light);
		tf.say("当前设置：");
		tf.say("");
		tf.say("玩家人数：");	if(K!=0)printf("%d",K);
		tf.say("初始卡牌数：");	if(start_cards!=0)printf("%d",start_cards);
		tf.say("难度设置：");	if(mode!=0)printf("%s",md_txt[mode-1]);	
		for(i=0;i<5;i++)
			tf.say("");
		tf.say("是否使用四叶苜蓿：");printf("%s",fortune?"是":"否");
		tf.say("当前地图：");printf("%s",map_name[p_user->at]);
		set_defal.dye("设为默认");
		draw(four_leaf_clover_img,for_x,for_y,9,13,use_fortune.jud?_Green|_Light:_Cyan|_Light);
		Place(for_x+10,for_y-4);Color(White|Light);printf("点击上面的四叶苜蓿图标");
		Place(for_x+11,for_y-4);Color(White|Light);printf("在使用和不使用间切换！"); 
		w.end_setall("返回主菜单");
		//action部分 
		do
			i=w.do_action();
		while(	(i>=0&&i<pp_btns					&&pp[i].jud==false)	 			||  
				(i>=pp_btns+1&&i<pp_btns+1+md_btns	&&md[i-(pp_btns+1)].jud==false) || 
				i==8								&&defal.jud==false 				||
				i==9								&&st.jud==false 				||
				i==10								&&set_defal.jud==false 			||
				i==11								&&use_fortune.jud==false 		||
				i==12								&&map_btn.jud==false 
			);
		const int Q1=swit_btns+1;
		const int Q2=swit_btns+2;
		switch(w.action)
		{
			case 3:
				do 
					cd.putin_vk('d');
				while(	cd.search.d<min_cards  ||  cd.search.d>max_cards	);
				start_cards=cd.search.d;
				temp_complete[1]=true;
				cd.clearboard(_Black);
				break;
			case 8:/*取默认*/
				pp[K-2].judset(  true  );//复原
				md[mode-1].judset(  true  );
				K=p_user->get("default_K");
				start_cards=p_user->get("default_start_cards");
				mode/*不是hard*/=p_user->get("default_hard");	
				for(i=0;i<temps;i++)
					temp_complete[i]=true;
				pp[K-2].judset(  false  );//复原
				md[mode+pp_btns-(pp_btns+1)].judset(  false  );
				break;
			case Q1:/*开始游戏*/				
				game(p_user,mode,K,start_cards,fortune,p_user->at);
				if(fortune)
				{
					p_user->obtain(The_clover,-1);//打完才消耗 
					p_user->record_users_information();
				}
				break;
			case Q2:/*设默认*/
				p_user->set_default(K,start_cards,mode); 
				break;
			case 11:/*四叶*/
				fortune=!fortune;
				break;
			case 12:/*地图*/
				maps(p_user);
				break;
			case 13:/*返回主菜单*/
				return;
			default:
				if(w.action<pp_btns)//人数 
				{
					if(K!=0)
						pp[K-2].judset(  true  );//复原 
					pp[w.action].judset(  false  );
					temp_complete[0]=true;
					K=w.action+2;
				}
				else if(	w.action>=pp_btns+1	  &&	w.action<pp_btns+1+md_btns	)
				{
					if(mode!=0)
						md[mode-1].judset(  true  );//复原 
					md[w.action-(pp_btns+1)].judset(  false  );
					temp_complete[2]=true;
					mode=w.action-pp_btns;//-1+1抵消 
				}
		} 
	}
	while(w.action!=9);
	return;
}


