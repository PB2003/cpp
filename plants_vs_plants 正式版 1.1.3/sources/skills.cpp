
#define _SKILLS_CPP_

#ifndef _BASICDATA_CPP_ 
    #define _BASICDATA_CPP_
    #include "basicdata.cpp"
#endif

#ifndef _STRUCTION_CPP_ 
    #define _STRUCTION_CPP_
    #include "struction.cpp"
#endif


EFFECT *apply_for(Player *person,int aim0)//自带清零 
{
	EFFECT *p=new EFFECT;
	int i,j;
	for(i=0;i<PMax;i++)
		for(j=0;j<Eff_Temp;j++)
			p->eff[i][j]=0;
	p->maker=person;
	p->aim=aim0;
	p->next=NULL; 
	return p;
} 
EFFECT *new_EFF(EFFECT *head,EFFECT *insert)
{
	int jud_T=insert->to_T;int i;
	EFFECT *p=new EFFECT;
	EFFECT *q=new EFFECT;
	p->next=head;
	while(	p->next->next!=NULL	 &&  p->next->next->to_T  <=  jud_T  )//熔断 
		p->next=p->next->next;/*p自己的值不要乱动，否则删除p时有bug*/
	q->next=p->next->next;
	p->next->next=insert;
	insert->next=q->next;/*无论q是否为NULL都通用*/
	delete p;
	delete q;
	return insert; 
}
void clear_EFF(EFFECT *head,int T)
{
	EFFECT *p;
	while(	head->next!=NULL	&&	head->next->to_T  <=  T  )//熔断 
	{
		p=head->next;
		head->next=p->next;
		delete p;
	}
	return;
}

#define Skill_fail 		0
#define Skill_success 	1 
#define Can_do_more		2
#define Revive 			3
#define Badluck 		4
#define Backharm 		5
#define End_blast		6
#define Captivate_kill	7 
#define Captivate_notkill 8
#define Manygrapes 		9

SKILL_t bigbutter(int L,int T,int K,int aim,Player *doer,EFFECT *E)//大黄油++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P))
	{
		E->eff[aim][e_att]=60;
		E->eff[aim][e_att_kind]=PHYS;
		E->eff[aim][e_frozen]=2;
		return Skill_success;
	} 
	else
		return Skill_fail;
} 
SKILL_t captivate(int L,int T,int K,int aim,Player *doer,EFFECT *E)//魅惑++ 
{
	E->from_T=T;
	E->to_T=T; 
	Plant *the_plant=player[aim].now;
	const int P=1000;
	if(iftrig(P)) 
	{
		if(doer->card_change(Captivate,T,HARD/*以后优化*/ ,K,	aim==K-1	,the_plant)==NULL)
		{
			the_plant->belong_change(doer);//不能过早传递 
			return Captivate_kill;
		}
		else 
			return Captivate_notkill;
	}
	else
	    return Skill_fail;
} 
SKILL_t poison(int L,int T,int K,int aim,Player *doer,EFFECT *E)//中毒++
{
	E->from_T=T;
	E->to_T=T+2; 
	const int P=(	(L==Unskilled||L==Experienced)	?	750:833	);
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=(L==Unskilled?25:(L==Experienced?32:40)); 
		E->eff[aim][e_att_kind]=REAL; 
		E->eff[aim][e_weaken]=((L==Unskilled||L==Experienced)	?	8:15); 
		return Skill_success;
	}
	else
	    return Skill_fail;
} 
SKILL_t knockout(int L,int T,int K,int aim,Player *doer,EFFECT *E)//击飞++
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?250:333);
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=999; 
		E->eff[aim][e_att_kind]=REAL; 
		return Skill_success;
	}
	else
	    return Skill_fail;
}  
SKILL_t shining(int L,int T,int K,int aim,Player *doer,EFFECT *E)//闪耀++
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?750:1000);
	if(iftrig(P)) 
	{
		E->eff[aim][e_produce]=25; 
		return Skill_success;
	}
	else
	{
		E->eff[aim][e_produce]=10; 
		return Skill_fail;
	}
} 
SKILL_t succession(int L,int T,int K,int aim,Player *doer,EFFECT *E)//连发++
{
	E->from_T=T;
	E->to_T=T; 
	int i;
	E->eff[aim][e_att]=0;
	const int P=(L==Unskilled?375:625);
	for(i=0;i<3;i++)//最多附加3回合 
		if(iftrig(P)) 
		{
			rand()+rand();
			E->eff[aim][e_att]+=(L==Unskilled?10:14);
			E->eff[aim][e_att_kind]=PHYS; 		
		}
		else
			if(i==0)
				return Skill_fail;
	return Skill_success;
}
SKILL_t flyback(int L,int T,int K,int aim,Player *doer,EFFECT *E)//回旋++ 
{
	E->from_T=T+1;
	E->to_T=T+1; 
	const int P=333;
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=40; 
		E->eff[aim][e_att_kind]=PHYS; 
		return Skill_success;
	}
	else
	    return Skill_fail;
} 
SKILL_t E_produce(int L,int T,int K,int aim,Player *doer,EFFECT *E)//潮涌能量，以后优化++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P)) 
	{
		E->eff[aim][e_produce]=75+(rand()%6)*5; 
		return Skill_success;
	}
	else
	    return Skill_fail;
} 
SKILL_t refract(int L,int T,int K,int aim,Player *doer,EFFECT *E)//折射++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int consume=25;
	if(doer->get("sun")>=consume) 
	{
		E->eff[aim][e_att]=random(70,15);
		if(player[aim].now!=NULL	&&	player[aim].now->tag_j(DA))
			 E->eff[aim][e_att]*=2;
		E->eff[aim][e_att_kind]=PHYS;
		doer->sun_add(-consume);
		doer->points_add(consume); 
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t focus(int L,int T,int K,int aim,Player *doer,EFFECT *E)//聚焦++ 
{
	E->from_T=T;
	E->to_T=T;  
	const int consume=60;
	if(doer->get("sun")>=consume) 
	{
		E->eff[aim][e_att]=random(180,25);
		if(player[aim].now!=NULL	&&	player[aim].now->tag_j(DA))
			 E->eff[aim][e_att]*=2;
		E->eff[aim][e_att_kind]=PHYS;
		doer->sun_add(-consume);
		doer->points_add(consume);
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t strike(int L,int T,int K,int aim,Player *doer,EFFECT *E) //引雷++ 
{
	E->from_T=T;
	E->to_T=T+2; 
	const int P=750;
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=random((L==Unskilled?32:50),16);
		E->eff[aim][e_att_kind]=PHYS;		
		if(iftrig(L==Unskilled?500:1000))
			E->eff[aim][e_weaken]=8;
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t end_blast(int L,int T,int K,int aim,Player *doer,EFFECT *E) //自爆++
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(	iftrig(P)&&		player[aim].now!=NULL	&&	!player[aim].now->if_go_exploding()) //不打即将炸的炸弹 
	{
		E->eff[aim][e_att]=(L==Unskilled?110:150); 
		E->eff[aim][e_att_kind]=PHYS;
		return End_blast;
	}
	else		
	    return Skill_fail;
}
SKILL_t pass(int L,int T,int K,int aim,Player *doer,EFFECT *E)//传球++ 
{
	E->from_T=T;
	E->to_T=T; 
	int i;
	E->eff[aim][e_att]=0;
	const int P=(L==Unskilled?500:625);
	bool notaim[K]={false};
	notaim[doer->playernum]=notaim[aim]=true;//之后aim做变量用起来  
	for(i=0;i<K-2;i++)//最多附加K-2回合 
		if(iftrig(P)) 
		{
			do
				aim=rand()%K;
			while(notaim[aim]==true);
			notaim[aim]==true;
			E->eff[aim][e_att]=40-i*10; //衰减 
			E->eff[aim][e_att_kind]=PHYS;
			return Skill_success;
		}
		else
			if(i==0)
				return Skill_fail;
	return Skill_success;
}
SKILL_t warmup(int L,int T,int K,int aim,Player *doer,EFFECT *E)//预热++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P) &&	doer->now!=NULL) 
	{ 
		doer->now->add("speed",1);//周期延长 
		doer->now->add("attack",L==Unskilled?32:74);//攻击加大
		if(L==Unskilled)
		{
			int i;
			for(i=0;i<SkillMax;i++)
				if(doer->now->skill[i]==warmup) 
					doer->now->skill_intensity[i]=Experienced;/*进级*/			
		}
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t soulspeed(int L,int T,int K,int aim,Player *doer,EFFECT *E)//灵魂疾行 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?250:375);
	if(iftrig(P)) 
		return Can_do_more;
	else
	    return Skill_fail;
}
SKILL_t vanish(int L,int T,int K,int aim,Player *doer,EFFECT *E)//消失诅咒 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?833:125);
	if(iftrig(P)) 
	{
		E->eff[aim][e_produce]=	- player[aim].get("sun");//负号 
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t sun_att(int L,int T,int K,int aim,Player *doer,EFFECT *E)//生产攻击++
{
	E->from_T=T;
	E->to_T=T; 
	const int P=500;
	int self_num=doer->playernum;
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=40;	
		E->eff[aim][e_att_kind]=PHYS;		
		E->eff[self_num][e_produce]=25;
		return Skill_success;
	}
	else
	{
		E->eff[self_num][e_produce]=10;	
	    return Skill_fail;
	}
}
SKILL_t blow(int L,int T,int K,int aim,Player *doer,EFFECT *E)//飓风++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=333;
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=999;
		E->eff[aim][e_att_kind]=REAL;		
		return Skill_success;
	}
	else
	{
		E->aim=doer->playernum;//自食其果 
		E->eff[E->aim][e_att]=20;
		E->eff[E->aim][e_att_kind]=REAL;		
	    return Skill_fail;
	}
}
SKILL_t recover(int L,int T,int K,int aim,Player *doer,EFFECT *E)//生命恢复++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	const int add=(1+rand()%(L==Unskilled?5:8));
	int d;
	if(iftrig(P)  &&	doer->now!=NULL) 
	{
		d=player[aim].now->get("HP_M")-player[aim].now->get("HP_L");
		E->eff[aim][e_HP_L]=(d>add?add:d);		
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t cooldown(int L,int T,int K,int aim,Player *doer,EFFECT *E)//快速装填++
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?625:750);
	if(iftrig(P)&&	doer->now!=NULL) 
	{
		doer->now->last_action_T_reset(T);		
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t randomfly(int L,int T,int K,int aim,Player *doer,EFFECT *E)//葡萄雨++
{
	E->from_T=T;
	E->to_T=T; 
	int i; 
	const int P=1000;
	int grapes=random(4,2)+(L>Unskilled);
	if(iftrig(P))
	{
		for(i=0;i<grapes;i++)
		{
			while((aim=rand()%K)==doer->playernum	||	player[aim].get("rank")!=0	||	player[aim].now==NULL	);//每次aim会变 
			E->eff[aim][e_att]+=(L==Unskilled?25:35);
		    E->eff[aim][e_att_kind]=PHYS;
		}
		return Manygrapes+grapes;
	} 
	else
		return Skill_fail;
}
SKILL_t lavaball(int L,int T,int K,int aim,Player *doer,EFFECT *E)//火焰附加++
{
	E->from_T=T;
	E->to_T=T; 
	int i; 
	const int P=500;
	if(iftrig(P)	&&	player[aim].now!=NULL)
	{
		for(i=0;i<K;i++)
			if(  i!=doer->playernum  &&  player[i].get("rank")==0  &&	player[i].now!=NULL  &&	!player[i].now->if_go_exploding()  )//自己、死亡玩家、炸弹除外
			{
		    	E->eff[i][e_att]=(player[i].now->tag_j(IA)?18:12);
		    	E->eff[i][e_att_kind]=PHYS;
			}
		E->eff[aim][e_att]=(player[aim].now->tag_j(IA)?105:70);//直接覆盖上面对目标的伤害 
		return Skill_success;
	} 
	else
	{
		E->eff[aim][e_att]=doer->now->get("attack average");
		E->eff[aim][e_att_kind]=PHYS;
		return Skill_fail;
	}
}
SKILL_t corrosion(int L,int T,int K,int aim,Player *doer,EFFECT *E)//腐蚀++ 
{
	E->from_T=T;
	E->to_T=T+9; 
	const int P=250;
	if(iftrig(P)) 
	{ 
		E->eff[aim][e_HP_M]=-5;	
		E->eff[aim][e_att]=5; 
		E->eff[aim][e_att_kind]=REAL;
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t spute(int L,int T,int K,int aim,Player *doer,EFFECT *E)//针刺++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=(L==Unskilled?25:65); 
		E->eff[aim][e_att_kind]=PHYS;
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t backharm(int L,int T,int K,int aim,Player *doer,EFFECT *E)//荆棘++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(	iftrig(P) &&	player[aim].get("rank")==0	&&	player[aim].now!=NULL &&	!player[aim].now->if_go_exploding()	) //不能打即将炸的炸弹 
	{
		E->eff[aim][e_att]=(L==Unskilled?15:25);
		E->eff[aim][e_att_kind]=PHYS;
		return Backharm;
	}
	else		
	    return Skill_fail;
}
SKILL_t strider(int L,int T,int K,int aim,Player *doer,EFFECT *E)//深海探索者++ 
{
	E->from_T=T;
	E->to_T=T; 
	int i; 
	const int P=1000;
	if(iftrig(P)&&player[aim].now!=NULL)
	{
		if(player[aim].now->tag_j(MR)) 
			E->eff[aim][e_att]=2*doer->now->get("attack average"); 
		else if(player[aim].now->tag_j(IA))
			E->eff[aim][e_att]=4*doer->now->get("attack average")/3; 
		else
			goto GOTOHERE_STRIDER_FAIL;
		E->eff[aim][e_att_kind]=PHYS;
		return Skill_success;
	} 
	else
	{
		GOTOHERE_STRIDER_FAIL:
		if(doer->now!=NULL)
		{
			E->eff[aim][e_att]=doer->now->get("attack average");
			E->eff[aim][e_att_kind]=PHYS;			
		}
		return Skill_fail;
	}
}
SKILL_t newlife(int L,int T,int K,int aim,Player *doer,EFFECT *E)//不死图腾++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?500:1000);
	if(iftrig(P)&&doer->now!=NULL) 
	{
		doer->now->HP_modify("full",0);
		return Revive;
	}
	else		
	    return Skill_fail;
}
SKILL_t headchange(int L,int T,int K,int aim,Player *doer,EFFECT *E)//换头术++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P)&&player[aim].now!=NULL) 
	{
		player[aim].now->HP_modify("boost",-30);
		player[aim].now->HP_modify("full",0);
		player[aim].now->add("attack",-30);
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t transfiguration(int L,int T,int K,int aim,Player *doer,EFFECT *E)//变身++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	int i;
	if(iftrig(P)) 
	{
		Plant *p=doer->now;
		if(p!=NULL)
			if(L==Unskilled)
			{
				p->add("attack",180);
				p->name="伪土豆雷";
				for(i=0;i<SkillMax;i++)
					if(p->skill[i]==transfiguration) 
						p->skill_intensity[i]=Experienced;/*进级*/	
			}
			else if(L==Experienced)
			{
				p->add("attack",90);
				p->name="伪爆炸葡萄";
				for(i=0;i<SkillMax;i++)
					if(p->skill[i]==transfiguration) 
						p->skill_intensity[i]=Perfect;/*进级*/				
			}
			else
			{
				p->add("attack",60);
				p->add("sputter",180);
				p->name="伪毁灭菇";				
			}
			return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t boom(int L,int T,int K,int aim,Player *doer,EFFECT *E)//爆炸++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P)) 
	{
		while(doer->now!=NULL&&doer->now->tick());
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t haunted(int L,int T,int K,int aim,Player *doer,EFFECT *E)//怨魂++
{
	E->from_T=T;
	E->to_T=T+2; 
	const int P=(L==Unskilled?500:625);
	if(iftrig(P)) 
	{
		E->eff[aim][e_att]=(L==Unskilled?22:33); 
		E->eff[aim][e_att_kind]=REAL; 
		E->eff[aim][e_weaken]=4; 
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t bad_omen(int L,int T,int K,int aim,Player *doer,EFFECT *E)//不祥之兆++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P)) 
	{
		int luck;
		if(L==Unskilled)
			luck=-1*player[aim].get("chance")/2;
		else
			luck=-3*player[aim].get("chance")/4;
		player[aim].luck_add(T+5,luck);
		return Badluck;
	}
	else		
	    return Skill_fail;
}
SKILL_t creasygrow(int L,int T,int K,int aim,Player *doer,EFFECT *E)//野蛮生长++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	Plant *p=doer->now;
	if(iftrig(P)&&p!=NULL) 
	{
		p->add("attack",25);
		p->HP_modify("expand",10);		
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t darkstrength(int L,int T,int K,int aim,Player *doer,EFFECT *E)//暗能量++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	int i,dark=0;
	for(i=0;i<K;i++) 
		if(	i!=doer->playernum	&&	player[i].get("rank")==0	&&	player[i].now!=NULL	&&	player[i].now->tag_j(DA)	)
			++dark;
	if(iftrig(P)	&&	doer->now!=NULL	&&	dark>0) 
	{
		doer->now->add("produce",25*dark);		
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t alchemy(int L,int T,int K,int aim,Player *doer,EFFECT *E)//炼金术++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P)) 
	{
		if(doer->playernum==K-1) 
			doer->coins_add(15);
		else
			doer->sun_add(15);
		doer->points_add(15); 
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t photosynthesis(int L,int T,int K,int aim,Player *doer,EFFECT *E)//光合炼金++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int consume=50;
	if(doer->get("sun")>=consume) 
	{
		doer->sun_add(-consume);
		if(doer->playernum==K-1) 
			doer->coins_add(75);
		else
			doer->sun_add(consume+15);//赚15 
		doer->points_add(consume+75); 
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t hearttearing(int L,int T,int K,int aim,Player *doer,EFFECT *E)//穿心箭++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=750;
	if(iftrig(P)&&player[aim].now!=NULL) 
	{
		E->eff[aim][e_att]=67; 
		E->eff[aim][e_att_kind]=PHYS;	
		player[aim].now->defence_clear();
		return Skill_success;
	}
	else
	{
		E->eff[aim][e_att]=50;		
	    return Skill_fail;
	}
}
SKILL_t calmdown(int L,int T,int K,int aim,Player *doer,EFFECT *E)//凝神射击++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=750;
	if(iftrig(P)&&player[aim].now!=NULL) 
	{
		E->eff[aim][e_att]=57; 
		E->eff[aim][e_att_kind]=PHYS;	
		player[aim].now->double_P_clear();
		return Skill_success;
	}
	else		
	{
		E->eff[aim][e_att]=50;		
	    return Skill_fail;
	}
}
SKILL_t destroy(int L,int T,int K,int aim,Player *doer,EFFECT *E)//黯灭射击++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=750;
	if(iftrig(P)&&player[aim].now!=NULL) 
	{
		E->eff[aim][e_att]=97; 
		E->eff[aim][e_att_kind]=PHYS;
		return Skill_success;
	}
	else		
	{
		E->eff[aim][e_att]=50;		
	    return Skill_fail;
	}
}
SKILL_t bandage(int L,int T,int K,int aim,Player *doer,EFFECT *E)//绷带包扎++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=800;
	Plant *p=doer->now;
	if(iftrig(P)&&p!=NULL) 
	{
		p->HP_modify("gain",30+rand()%31);		
		return Skill_success;
	}
	else		
	    return Skill_fail;
}
struct Skillname
{
	STD_SKILL *content;
	int act_kind;
	int act_aim;
	int max_intensity;
	int	favor;
	int effected_Ts;
	const char name[NameLenthMax];
	const char describe[SentenceLenthMax];
}skillname[AllSkills+1+4]=
{
	{NULL			,0			,0			,0			,0		,0,	"无"		,"无"},
	{bigbutter		,Objective	,Specific	,Unskilled	,Better	,1,	"大黄油"	,"造成60物理伤害和2回合冰冻。"},
	{captivate		,Objective	,Specific	,Unskilled	,Must	,1,	"魅惑"		,"获得场上其他玩家的一张卡牌"},
	{poison			,Objective	,Specific	,Perfect	,Better	,3,	"中毒"		,"750‰几率造成25真实伤害和8点弱化。"}, 
	{shining		,Objective	,Self		,Unskilled	,Better	,1,	"闪耀"		,"750‰几率生产25点阳光，否则生产10点阳光。"},
	{succession		,Adjunct	,Specific	,Experienced,Better	,1,	"连发"		,"375‰^n几率造成10*n物理伤害，n最多为3。"},
	{knockout		,Objective	,Specific	,Unskilled	,Better	,1,	"击飞"		,"250‰几率秒杀。"},
	{flyback		,Adjunct	,Specific	,Unskilled	,Better	,1,	"回旋"		,"333‰几率在下一回合造成40物理伤害。"},
	{E_produce		,Objective	,Self		,Unskilled	,Better	,1,	"潮涌能量"	,"生产能量豆。目前用生产阳光作为占位符。"},
	{strike			,Objective	,Specific	,Unskilled	,Better	,3,	"引雷"		,"750‰几率造成16~48点物理伤害，在此基础上500‰几率造成8点弱化。"}, 
	{warmup			,Objective	,Self		,Unskilled	,Better	,1,	"预热"		,"休眠回合加长1，攻击力加大32。"},
	{refract		,Objective	,Specific	,Unskilled	,25		,1,	"折射"		,"消耗25阳光，造成55~85点物理伤害。对黑暗植物伤害加倍。"}, 
	{focus			,Objective	,Specific	,Unskilled	,60		,1,	"聚焦"		,"消耗60阳光，造成155~205点物理伤害。对黑暗植物伤害加倍。"},
	{pass	 		,Adjunct	,Specific	,Unskilled	,Better	,1,	"传球"		,"500‰^n几率对目标以外的玩家造成50-10*n物理伤害，n最多为玩家数-2。"}, 
	{end_blast		,Passive_S	,Specific	,Unskilled	,Better	,1,	"自爆"		,"对触发者造成110点物理伤害。"},
	{recover		,Always		,Self		,Experienced,Better	,1,	"生命恢复"	,"每任意回合回复1~5生命。"},
	{soulspeed		,Adjunct	,Specific	,Unskilled	,Better	,1,	"灵魂疾行"	,"250‰几率在同一回合内攻击第二次。"},
	{vanish			,Adjunct	,Specific	,Unskilled	,Better	,1,	"消失诅咒"	,"83‰几率使目标玩家阳光清零。"},//改P
	{sun_att		,Objective	,Specific	,Unskilled	,Better	,1,	"生产攻击"	,"500‰几率对目标玩家造成40点物理伤害，并生产25点阳光，否则无伤害，只生产10点阳光。"},
	{blow			,Objective	,Specific	,Unskilled	,Better	,1,	"飓风"		,"333‰几率秒杀，否则对自己造成20点真实伤害。"},
	{spute			,Objective	,Specific	,Experienced,Better	,1,	"针刺"		,"产生25点物理伤害。"},
	{backharm		,Passive	,Specific	,Unskilled	,Better	,1,	"荆棘"		,"对触发者造成15点物理伤害。"},
	{strider		,Objective	,Specific	,Unskilled	,Better	,1,	"深海探索者","对水生植物和冰系植物分别造成2倍和1.33倍的普通攻击伤害。"},
	{newlife		,Passive_S	,Self		,Unskilled	,Better	,1,	"不死图腾"	,"500‰几率重生。"},
	{cooldown		,Adjunct	,Self		,Experienced,Better	,1,	"快速装填"	,"625‰几率在行动后立刻完成休眠。"},
	{randomfly		,Adjunct	,Specific	,Unskilled	,Better	,1,	"葡萄雨"	,"产生2~6个活蹦乱跳的葡萄，每个对自己以外的随机玩家造成25点物理伤害。"},
	{lavaball		,Objective	,Specific	,Unskilled	,Better	,1,	"火焰附加"	,"500‰几率产生70点物理伤害和12点溅射。对冰系植物伤害为1.5倍。"},
	{transfiguration,Objective	,Self		,Perfect	,Better	,1,	"变身"		,"每次依次变身为伪土豆雷、伪爆炸葡萄和伪毁灭菇，拥有相似的属性。"},
	{boom   		,Objective	,Self		,Unskilled	,Better	,1,	"爆炸"		,"提前引爆延时炸弹。"},
	{corrosion		,Adjunct	,Specific	,Unskilled	,Better	,10,"腐蚀"		,"每回合受到6点真实伤害，并减少6点HP上限。"},//改 
	{haunted		,Objective	,Specific	,Unskilled	,Better	,3,	"怨魂"		,"500‰几率造成22真实伤害和4点弱化。"},
	{bad_omen		,Passive_S	,Specific	,Unskilled	,Better	,2,	"不祥之兆"	,"运气值减半。"},
	{headchange		,Objective	,Self		,Unskilled	,Have_to,1,	"换头术"	,"HP上限和攻击都减少30，HP回满。"},
	{creasygrow		,Objective	,Self		,Unskilled	,Better	,1,	"野蛮生长"	,"多长一个头，HP回复15，攻击增加25。"},
	{darkstrength	,Objective	,Self		,Unskilled	,Better	,1,	"暗能量"	,"场上每多一张其它暗属性卡牌，生产能力就增加25。"},
	{alchemy		,Objective	,Self		,Unskilled	,Better	,1,	"炼金术"	,"获得15金币与得分。"},
	{photosynthesis	,Objective	,Self		,Unskilled	,50		,1,	"光合炼金"	,"消耗50阳光，获得75金币与得分。"},
	{hearttearing	,Objective	,Specific	,Unskilled	,Better	,1,	"穿心箭"	,"降低敌人的护甲。"},
	{calmdown		,Objective	,Specific	,Unskilled	,Better	,1,	"凝神射击"	,"降低敌人的暴击。"},
	{destroy		,Objective	,Specific	,Unskilled	,Have_to,1,	"黯灭射击"	,"造成大量伤害。"},
	{bandage		,Objective	,Self		,Unskilled	,Have_to,1,	"绷带包扎"	,"回复30~60生命。"},
}; 
struct Skill
{
	int 		count[SkillMax];
	int 		aim[SkillMax];
	STD_SKILL 	*use[SkillMax];
	int 		intensity[SkillMax];
	int			favor[SkillMax];
};
Skill skill_temp[Pkind]=
{
	                /*一技   二技   三技   一技   二技   三技*/
/*0.豌豆射手  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }}, 
/*1.向日葵    */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*2.寒冰射手  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*3.双发射手  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*4.窝瓜      */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*5.卷心菜投手*/    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*6.西瓜投手  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*7.玉米投手  */    { Single,0      ,0     ,{Specific,0     ,0     },{bigbutter,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*8.双子向日葵*/    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*9.小喷菇    */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*10.大喷菇   */    { Double,0      ,0     ,{Specific,0     ,0     },{poison   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*11.魅惑菇   */    { Single,0      ,0     ,{Specific,0     ,0     },{captivate,NULL     ,NULL     },{Unskilled	,0			,0			},{Must   ,0      ,0     }},
/*12.毁灭菇   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*13.阳光菇   */    { Triple,0      ,0     ,{Self   ,0      ,0     },{shining  ,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*14.胆小菇   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*15.寒冰菇   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*16.土豆雷   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*17.机枪射手 */    {Adjunct,0      ,0     ,{Specific,0     ,0     },{succession,NULL    ,NULL     },{Experienced,0			,0			},{0      ,0      ,0     }},
/*18.路障射手 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*19.铁桶射手 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*20.三线射手 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*21.三线寒冰 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*22.冰瓜投手 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*23.仙人掌   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*24.海蘑菇   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*25.玉米加农炮*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*26.冰冻生菜 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*27.菜问     */    {Nolimit,0      ,0     ,{Specific,0     ,0     },{knockout ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*28.回旋镖射手*/   {Adjunct,0      ,0     ,{Specific,0     ,0     },{flyback  ,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*29.能量花   */    {Nolimit,0      ,0     ,{Self   ,0      ,0     },{E_produce,NULL     ,NULL     },{Unskilled	,0			,0			},{Must   ,0      ,0     }},
/*30.闪电芦苇 */    { Single,0      ,0     ,{Specific,0     ,0     },{strike   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*31.火葫芦   */    { Double,0      ,0     ,{Self   ,0      ,0     },{warmup   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*32.竹笋     */    { 	 0  ,0      ,0     ,{0      ,0      ,0     },{NULL	   ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*33.棱镜草   */    {Nolimit,Single ,0     ,{Specific,Specific,0   },{refract  ,focus    ,NULL     },{Unskilled	,0			,0			},{25     ,60     ,0     }},
/*34.保龄泡泡 */    {Adjunct,Adjunct,0     ,{Specific,Self  ,0     },{pass     ,cooldown ,NULL     },{Unskilled	,Unskilled	,0			},{0      ,0      ,0     }},
/*35.旋转芜菁 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*36.辣椒投手 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*37.火焰射手 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*38.飓风甘蓝 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*39.南瓜头   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*40.高坚果   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*41.爆炸坚果 */    {Passive_S,0    ,0     ,{Specific,0     ,0     },{end_blast,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*42.全息坚果 */    { Always,0      ,0     ,{Self   ,0      ,0     },{recover  ,NULL     ,NULL     },{Experienced,0			,0			},{0      ,0      ,0     }},
/*43.叶子保护伞*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*44.旋转菠萝 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*45.火炬树桩 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*46.睡莲     */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*47.香蒲     */    { Double,0      ,0     ,{Specific,0     ,0     },{spute    ,NULL     ,NULL     },{Experienced,0			,0			},{Better ,0      ,0     }},
/*48.天使黄豆炮*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*49.黯灭黄豆炮*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*50.幽灵西红柿*/   {Adjunct,Adjunct,0     ,{Specific,Specific,0   },{soulspeed,vanish   ,NULL     },{Unskilled	,Unskilled	,0			},{0      ,0      ,0     }},
/*51.暗铁榴莲 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*52.葵花战车 */    {Adjunct, Triple,0     ,{0      ,0      ,0     },{succession,sun_att ,NULL     },{Unskilled	,Unskilled	,0			},{0      ,Better ,0     }},
/*53.火焰南瓜王*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*54.轰鸣核桃 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*55.六尾风王 */    {Nolimit,0      ,0     ,{Specific,0     ,0     },{blow     ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*56.刺猬坦克 */    { Single,Passive,0     ,{Specific,Specific,0   },{spute    ,backharm ,NULL     },{Experienced,Unskilled	,0			},{Better ,0      ,0     }},
/*57.海盗女王 */    { Single,Always ,Passive_S,{Specific,Self,Self },{strider  ,recover  ,newlife  },{Unskilled	,Unskilled	,Unskilled	},{Good   ,0      ,0     }},
/*58.芦笋战机 */    {Adjunct,Adjunct,0     ,{Specific,Self  ,0     },{succession,cooldown ,NULL    },{Unskilled	,Experienced,0			},{0      ,0      ,0     }},
/*59.爆炸葡萄 */    {Adjunct,0      ,0     ,{Others ,0      ,0     },{randomfly,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*60.原始豌豆射手*/ { Single,0      ,0     ,{Specific,0     ,0     },{lavaball ,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*61.原始向日葵*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*62.电眼巴豆  */   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*63.忧郁蘑菇 */    { Double,0      ,0     ,{0      ,0      ,0     },{poison   ,NULL     ,NULL     },{Experienced,0			,0			},{Better ,0      ,0     }},//与大喷不同 
/*64.方舟冰菇 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*65.逃脱树根 */    { Triple,Single ,0     ,{Self   ,Self   ,0     },{transfiguration,boom,NULL    },{Unskilled	,Unskilled	,0			},{Better ,Good   ,0     }},
/*66.强酸柠檬 */    {Adjunct,0      ,0     ,{0      ,0      ,0     },{corrosion,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*67.蒲公英   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*68.地刺王   */    { Single,0      ,0     ,{Specific,0     ,0     },{spute	   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Must   ,0      ,0     }},
/*69.鬼椒王   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*70.幽灵辣椒 */    { Double,Passive_S,0   ,{Specific,Specific,0   },{haunted  ,bad_omen ,NULL     },{Unskilled	,Unskilled	,0			},{Better ,0      ,0     }},
/*71.三头大嘴 */    { Double,0      ,0     ,{Self   ,0      ,0     },{headchange,NULL    ,NULL     },{Unskilled	,0			,0			},{Have_to,0      ,0     }},
/*72.椰子加农炮*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*73.金盏花   */    {Nolimit,Single ,0     ,{Self   ,Self   ,0     },{alchemy,photosynthesis,NULL  },{Unskilled	,Unskilled	,0			},{Better ,50     ,0     }},
/*74.火龙草   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*75.自定义   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*76.自定义   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#1.樱桃炸弹 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#2.充能柚子 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#3.周瑜蕉弩 */    {Adjunct,Adjunct,0     ,{Specific,Specific,0   },{succession,soulspeed,NULL    },{Unskilled	,Experienced,0			},{0      ,0      ,0     }},
/*#4.豌豆荚   */    {  Tetra,0      ,0     ,{Self   ,0      ,0     },{creasygrow,NULL    ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*#5.玄冰水仙 */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#6.月光草   */    { Single,0      ,0     ,{Self   ,0      ,0     },{darkstrength,NULL  ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*#7.紫百合	  */	{ Triple,0      ,0     ,{Specific,0     ,0     },{poison   ,NULL     ,NULL     },{Perfect	,0			,0			},{Better ,0      ,0     }},
};
//NPCs
const char NPCsname[NPCkind][NameLenthMax]=
{
	"魔化陈刚",
	"魔化小A",
	"魔化小B",
};
const int NPCsability[NPCkind][Properties]=
{
		              /*  Hp 攻击 波动 冰冻 冰率 弱化 防御 闪率 暴率 溅射 价值 产能 攻速 瞬时 等阶 标签  解锁等级*/
	/*0.魔化陈刚  */  {  600 ,50  ,20  ,3   ,83  ,0   ,12  ,83  ,50  ,0   ,995 ,0   ,Slo2,0   ,3   ,ST      ,1   },
	/*1.魔化小A   */  {  275 ,30  ,10  ,0   ,0   ,0   ,9   ,0   ,50  ,0   ,995 ,0   ,Slo2,0   ,2   ,ST      ,1   },
	/*2.魔化小B   */  {  165 ,60  ,5   ,0   ,0   ,5   ,4   ,83  ,167 ,15  ,995 ,0   ,Fast,0   ,2   ,ST      ,1   },
};
Skill NPCsskill_temp[NPCkind]=
{
/*0.魔化陈刚 */    { Triple,Triple ,Triple ,{Specific,Specific,Specific},{hearttearing,calmdown,destroy},{Unskilled	,Unskilled	,Unskilled	},{Better ,Good  ,Have_to}},
/*1.魔化小A  */    {Nolimit,0      ,0      ,{Specific,0      ,0        },{bandage  ,NULL     ,NULL     },{Unskilled	,0			,0			},{Have_to,0      ,0     }},
/*2.魔化小B  */    {Nolimit,0      ,0      ,{Specific,0      ,0        },{bandage  ,NULL     ,NULL     },{Unskilled	,0			,0			},{Have_to,0      ,0     }},
};









