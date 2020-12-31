
#define _SKILLS_CPP_

#ifndef _BASICDATA_CPP_ 
    #define _BASICDATA_CPP_
    #include "basicdata.cpp"
#endif

#ifndef _STRUCTION_CPP_ 
    #define _STRUCTION_CPP_
    #include "struction.cpp"
#endif


EFFECT *apply_for(Player *person,int aim0)//�Դ����� 
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
	while(	p->next->next!=NULL	 &&  p->next->next->to_T  <=  jud_T  )//�۶� 
		p->next=p->next->next;/*p�Լ���ֵ��Ҫ�Ҷ�������ɾ��pʱ��bug*/
	q->next=p->next->next;
	p->next->next=insert;
	insert->next=q->next;/*����q�Ƿ�ΪNULL��ͨ��*/
	delete p;
	delete q;
	return insert; 
}
void clear_EFF(EFFECT *head,int T)
{
	EFFECT *p;
	while(	head->next!=NULL	&&	head->next->to_T  <=  T  )//�۶� 
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

SKILL_t bigbutter(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�����++ 
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
SKILL_t captivate(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�Ȼ�++ 
{
	E->from_T=T;
	E->to_T=T; 
	Plant *the_plant=player[aim].now;
	const int P=1000;
	if(iftrig(P)) 
	{
		if(doer->card_change(Captivate,T,HARD/*�Ժ��Ż�*/ ,K,	aim==K-1	,the_plant)==NULL)
		{
			the_plant->belong_change(doer);//���ܹ��紫�� 
			return Captivate_kill;
		}
		else 
			return Captivate_notkill;
	}
	else
	    return Skill_fail;
} 
SKILL_t poison(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�ж�++
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
SKILL_t knockout(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����++
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
SKILL_t shining(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��ҫ++
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
SKILL_t succession(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����++
{
	E->from_T=T;
	E->to_T=T; 
	int i;
	E->eff[aim][e_att]=0;
	const int P=(L==Unskilled?375:625);
	for(i=0;i<3;i++)//��฽��3�غ� 
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
SKILL_t flyback(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����++ 
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
SKILL_t E_produce(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��ӿ�������Ժ��Ż�++ 
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
SKILL_t refract(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����++ 
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
SKILL_t focus(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�۽�++ 
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
SKILL_t strike(int L,int T,int K,int aim,Player *doer,EFFECT *E) //����++ 
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
SKILL_t end_blast(int L,int T,int K,int aim,Player *doer,EFFECT *E) //�Ա�++
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(	iftrig(P)&&		player[aim].now!=NULL	&&	!player[aim].now->if_go_exploding()) //���򼴽�ը��ը�� 
	{
		E->eff[aim][e_att]=(L==Unskilled?110:150); 
		E->eff[aim][e_att_kind]=PHYS;
		return End_blast;
	}
	else		
	    return Skill_fail;
}
SKILL_t pass(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����++ 
{
	E->from_T=T;
	E->to_T=T; 
	int i;
	E->eff[aim][e_att]=0;
	const int P=(L==Unskilled?500:625);
	bool notaim[K]={false};
	notaim[doer->playernum]=notaim[aim]=true;//֮��aim������������  
	for(i=0;i<K-2;i++)//��฽��K-2�غ� 
		if(iftrig(P)) 
		{
			do
				aim=rand()%K;
			while(notaim[aim]==true);
			notaim[aim]==true;
			E->eff[aim][e_att]=40-i*10; //˥�� 
			E->eff[aim][e_att_kind]=PHYS;
			return Skill_success;
		}
		else
			if(i==0)
				return Skill_fail;
	return Skill_success;
}
SKILL_t warmup(int L,int T,int K,int aim,Player *doer,EFFECT *E)//Ԥ��++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(iftrig(P) &&	doer->now!=NULL) 
	{ 
		doer->now->add("speed",1);//�����ӳ� 
		doer->now->add("attack",L==Unskilled?32:74);//�����Ӵ�
		if(L==Unskilled)
		{
			int i;
			for(i=0;i<SkillMax;i++)
				if(doer->now->skill[i]==warmup) 
					doer->now->skill_intensity[i]=Experienced;/*����*/			
		}
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t soulspeed(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��꼲�� 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?250:375);
	if(iftrig(P)) 
		return Can_do_more;
	else
	    return Skill_fail;
}
SKILL_t vanish(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��ʧ���� 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=(L==Unskilled?833:125);
	if(iftrig(P)) 
	{
		E->eff[aim][e_produce]=	- player[aim].get("sun");//���� 
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t sun_att(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��������++
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
SKILL_t blow(int L,int T,int K,int aim,Player *doer,EFFECT *E)//쫷�++ 
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
		E->aim=doer->playernum;//��ʳ��� 
		E->eff[E->aim][e_att]=20;
		E->eff[E->aim][e_att_kind]=REAL;		
	    return Skill_fail;
	}
}
SKILL_t recover(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�����ָ�++ 
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
SKILL_t cooldown(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����װ��++
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
SKILL_t randomfly(int L,int T,int K,int aim,Player *doer,EFFECT *E)//������++
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
			while((aim=rand()%K)==doer->playernum	||	player[aim].get("rank")!=0	||	player[aim].now==NULL	);//ÿ��aim��� 
			E->eff[aim][e_att]+=(L==Unskilled?25:35);
		    E->eff[aim][e_att_kind]=PHYS;
		}
		return Manygrapes+grapes;
	} 
	else
		return Skill_fail;
}
SKILL_t lavaball(int L,int T,int K,int aim,Player *doer,EFFECT *E)//���渽��++
{
	E->from_T=T;
	E->to_T=T; 
	int i; 
	const int P=500;
	if(iftrig(P)	&&	player[aim].now!=NULL)
	{
		for(i=0;i<K;i++)
			if(  i!=doer->playernum  &&  player[i].get("rank")==0  &&	player[i].now!=NULL  &&	!player[i].now->if_go_exploding()  )//�Լ���������ҡ�ը������
			{
		    	E->eff[i][e_att]=(player[i].now->tag_j(IA)?18:12);
		    	E->eff[i][e_att_kind]=PHYS;
			}
		E->eff[aim][e_att]=(player[aim].now->tag_j(IA)?105:70);//ֱ�Ӹ��������Ŀ����˺� 
		return Skill_success;
	} 
	else
	{
		E->eff[aim][e_att]=doer->now->get("attack average");
		E->eff[aim][e_att_kind]=PHYS;
		return Skill_fail;
	}
}
SKILL_t corrosion(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��ʴ++ 
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
SKILL_t spute(int L,int T,int K,int aim,Player *doer,EFFECT *E)//���++ 
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
SKILL_t backharm(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����++ 
{
	E->from_T=T;
	E->to_T=T; 
	const int P=1000;
	if(	iftrig(P) &&	player[aim].get("rank")==0	&&	player[aim].now!=NULL &&	!player[aim].now->if_go_exploding()	) //���ܴ򼴽�ը��ը�� 
	{
		E->eff[aim][e_att]=(L==Unskilled?15:25);
		E->eff[aim][e_att_kind]=PHYS;
		return Backharm;
	}
	else		
	    return Skill_fail;
}
SKILL_t strider(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�̽����++ 
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
SKILL_t newlife(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����ͼ��++ 
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
SKILL_t headchange(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��ͷ��++ 
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
SKILL_t transfiguration(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����++ 
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
				p->name="α������";
				for(i=0;i<SkillMax;i++)
					if(p->skill[i]==transfiguration) 
						p->skill_intensity[i]=Experienced;/*����*/	
			}
			else if(L==Experienced)
			{
				p->add("attack",90);
				p->name="α��ը����";
				for(i=0;i<SkillMax;i++)
					if(p->skill[i]==transfiguration) 
						p->skill_intensity[i]=Perfect;/*����*/				
			}
			else
			{
				p->add("attack",60);
				p->add("sputter",180);
				p->name="α����";				
			}
			return Skill_success;
	}
	else		
	    return Skill_fail;
}
SKILL_t boom(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��ը++ 
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
SKILL_t haunted(int L,int T,int K,int aim,Player *doer,EFFECT *E)//Թ��++
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
SKILL_t bad_omen(int L,int T,int K,int aim,Player *doer,EFFECT *E)//����֮��++ 
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
SKILL_t creasygrow(int L,int T,int K,int aim,Player *doer,EFFECT *E)//Ұ������++ 
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
SKILL_t darkstrength(int L,int T,int K,int aim,Player *doer,EFFECT *E)//������++ 
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
SKILL_t alchemy(int L,int T,int K,int aim,Player *doer,EFFECT *E)//������++ 
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
SKILL_t photosynthesis(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�������++ 
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
			doer->sun_add(consume+15);//׬15 
		doer->points_add(consume+75); 
		return Skill_success;
	}
	else
	    return Skill_fail;
}
SKILL_t hearttearing(int L,int T,int K,int aim,Player *doer,EFFECT *E)//���ļ�++ 
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
SKILL_t calmdown(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�������++ 
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
SKILL_t destroy(int L,int T,int K,int aim,Player *doer,EFFECT *E)//�������++ 
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
SKILL_t bandage(int L,int T,int K,int aim,Player *doer,EFFECT *E)//��������++ 
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
	{NULL			,0			,0			,0			,0		,0,	"��"		,"��"},
	{bigbutter		,Objective	,Specific	,Unskilled	,Better	,1,	"�����"	,"���60�����˺���2�غϱ�����"},
	{captivate		,Objective	,Specific	,Unskilled	,Must	,1,	"�Ȼ�"		,"��ó���������ҵ�һ�ſ���"},
	{poison			,Objective	,Specific	,Perfect	,Better	,3,	"�ж�"		,"750�뼸�����25��ʵ�˺���8��������"}, 
	{shining		,Objective	,Self		,Unskilled	,Better	,1,	"��ҫ"		,"750�뼸������25�����⣬��������10�����⡣"},
	{succession		,Adjunct	,Specific	,Experienced,Better	,1,	"����"		,"375��^n�������10*n�����˺���n���Ϊ3��"},
	{knockout		,Objective	,Specific	,Unskilled	,Better	,1,	"����"		,"250�뼸����ɱ��"},
	{flyback		,Adjunct	,Specific	,Unskilled	,Better	,1,	"����"		,"333�뼸������һ�غ����40�����˺���"},
	{E_produce		,Objective	,Self		,Unskilled	,Better	,1,	"��ӿ����"	,"������������Ŀǰ������������Ϊռλ����"},
	{strike			,Objective	,Specific	,Unskilled	,Better	,3,	"����"		,"750�뼸�����16~48�������˺����ڴ˻�����500�뼸�����8��������"}, 
	{warmup			,Objective	,Self		,Unskilled	,Better	,1,	"Ԥ��"		,"���߻غϼӳ�1���������Ӵ�32��"},
	{refract		,Objective	,Specific	,Unskilled	,25		,1,	"����"		,"����25���⣬���55~85�������˺����Ժڰ�ֲ���˺��ӱ���"}, 
	{focus			,Objective	,Specific	,Unskilled	,60		,1,	"�۽�"		,"����60���⣬���155~205�������˺����Ժڰ�ֲ���˺��ӱ���"},
	{pass	 		,Adjunct	,Specific	,Unskilled	,Better	,1,	"����"		,"500��^n���ʶ�Ŀ�������������50-10*n�����˺���n���Ϊ�����-2��"}, 
	{end_blast		,Passive_S	,Specific	,Unskilled	,Better	,1,	"�Ա�"		,"�Դ��������110�������˺���"},
	{recover		,Always		,Self		,Experienced,Better	,1,	"�����ָ�"	,"ÿ����غϻظ�1~5������"},
	{soulspeed		,Adjunct	,Specific	,Unskilled	,Better	,1,	"��꼲��"	,"250�뼸����ͬһ�غ��ڹ����ڶ��Ρ�"},
	{vanish			,Adjunct	,Specific	,Unskilled	,Better	,1,	"��ʧ����"	,"83�뼸��ʹĿ������������㡣"},//��P
	{sun_att		,Objective	,Specific	,Unskilled	,Better	,1,	"��������"	,"500�뼸�ʶ�Ŀ��������40�������˺���������25�����⣬�������˺���ֻ����10�����⡣"},
	{blow			,Objective	,Specific	,Unskilled	,Better	,1,	"쫷�"		,"333�뼸����ɱ��������Լ����20����ʵ�˺���"},
	{spute			,Objective	,Specific	,Experienced,Better	,1,	"���"		,"����25�������˺���"},
	{backharm		,Passive	,Specific	,Unskilled	,Better	,1,	"����"		,"�Դ��������15�������˺���"},
	{strider		,Objective	,Specific	,Unskilled	,Better	,1,	"�̽����","��ˮ��ֲ��ͱ�ϵֲ��ֱ����2����1.33������ͨ�����˺���"},
	{newlife		,Passive_S	,Self		,Unskilled	,Better	,1,	"����ͼ��"	,"500�뼸��������"},
	{cooldown		,Adjunct	,Self		,Experienced,Better	,1,	"����װ��"	,"625�뼸�����ж�������������ߡ�"},
	{randomfly		,Adjunct	,Specific	,Unskilled	,Better	,1,	"������"	,"����2~6��������������ѣ�ÿ�����Լ���������������25�������˺���"},
	{lavaball		,Objective	,Specific	,Unskilled	,Better	,1,	"���渽��"	,"500�뼸�ʲ���70�������˺���12�㽦�䡣�Ա�ϵֲ���˺�Ϊ1.5����"},
	{transfiguration,Objective	,Self		,Perfect	,Better	,1,	"����"		,"ÿ�����α���Ϊα�����ס�α��ը���Ѻ�α���𹽣�ӵ�����Ƶ����ԡ�"},
	{boom   		,Objective	,Self		,Unskilled	,Better	,1,	"��ը"		,"��ǰ������ʱը����"},
	{corrosion		,Adjunct	,Specific	,Unskilled	,Better	,10,"��ʴ"		,"ÿ�غ��ܵ�6����ʵ�˺���������6��HP���ޡ�"},//�� 
	{haunted		,Objective	,Specific	,Unskilled	,Better	,3,	"Թ��"		,"500�뼸�����22��ʵ�˺���4��������"},
	{bad_omen		,Passive_S	,Specific	,Unskilled	,Better	,2,	"����֮��"	,"����ֵ���롣"},
	{headchange		,Objective	,Self		,Unskilled	,Have_to,1,	"��ͷ��"	,"HP���޺͹���������30��HP������"},
	{creasygrow		,Objective	,Self		,Unskilled	,Better	,1,	"Ұ������"	,"�೤һ��ͷ��HP�ظ�15����������25��"},
	{darkstrength	,Objective	,Self		,Unskilled	,Better	,1,	"������"	,"����ÿ��һ�����������Կ��ƣ���������������25��"},
	{alchemy		,Objective	,Self		,Unskilled	,Better	,1,	"������"	,"���15�����÷֡�"},
	{photosynthesis	,Objective	,Self		,Unskilled	,50		,1,	"�������"	,"����50���⣬���75�����÷֡�"},
	{hearttearing	,Objective	,Specific	,Unskilled	,Better	,1,	"���ļ�"	,"���͵��˵Ļ��ס�"},
	{calmdown		,Objective	,Specific	,Unskilled	,Better	,1,	"�������"	,"���͵��˵ı�����"},
	{destroy		,Objective	,Specific	,Unskilled	,Have_to,1,	"�������"	,"��ɴ����˺���"},
	{bandage		,Objective	,Self		,Unskilled	,Have_to,1,	"��������"	,"�ظ�30~60������"},
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
	                /*һ��   ����   ����   һ��   ����   ����*/
/*0.�㶹����  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }}, 
/*1.���տ�    */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*2.��������  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*3.˫������  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*4.�ѹ�      */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*5.���Ĳ�Ͷ��*/    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*6.����Ͷ��  */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*7.����Ͷ��  */    { Single,0      ,0     ,{Specific,0     ,0     },{bigbutter,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*8.˫�����տ�*/    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*9.С�繽    */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*10.���繽   */    { Double,0      ,0     ,{Specific,0     ,0     },{poison   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*11.�Ȼ�   */    { Single,0      ,0     ,{Specific,0     ,0     },{captivate,NULL     ,NULL     },{Unskilled	,0			,0			},{Must   ,0      ,0     }},
/*12.����   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*13.���⹽   */    { Triple,0      ,0     ,{Self   ,0      ,0     },{shining  ,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*14.��С��   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*15.������   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*16.������   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*17.��ǹ���� */    {Adjunct,0      ,0     ,{Specific,0     ,0     },{succession,NULL    ,NULL     },{Experienced,0			,0			},{0      ,0      ,0     }},
/*18.·������ */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*19.��Ͱ���� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*20.�������� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*21.���ߺ��� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*22.����Ͷ�� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*23.������   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*24.��Ģ��   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*25.���׼�ũ��*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*26.�������� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*27.����     */    {Nolimit,0      ,0     ,{Specific,0     ,0     },{knockout ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*28.����������*/   {Adjunct,0      ,0     ,{Specific,0     ,0     },{flyback  ,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*29.������   */    {Nolimit,0      ,0     ,{Self   ,0      ,0     },{E_produce,NULL     ,NULL     },{Unskilled	,0			,0			},{Must   ,0      ,0     }},
/*30.����«έ */    { Single,0      ,0     ,{Specific,0     ,0     },{strike   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*31.���«   */    { Double,0      ,0     ,{Self   ,0      ,0     },{warmup   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*32.����     */    { 	 0  ,0      ,0     ,{0      ,0      ,0     },{NULL	   ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*33.�⾵��   */    {Nolimit,Single ,0     ,{Specific,Specific,0   },{refract  ,focus    ,NULL     },{Unskilled	,0			,0			},{25     ,60     ,0     }},
/*34.�������� */    {Adjunct,Adjunct,0     ,{Specific,Self  ,0     },{pass     ,cooldown ,NULL     },{Unskilled	,Unskilled	,0			},{0      ,0      ,0     }},
/*35.��ת��ݼ */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*36.����Ͷ�� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*37.�������� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*38.쫷���� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*39.�Ϲ�ͷ   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*40.�߼��   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*41.��ը��� */    {Passive_S,0    ,0     ,{Specific,0     ,0     },{end_blast,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*42.ȫϢ��� */    { Always,0      ,0     ,{Self   ,0      ,0     },{recover  ,NULL     ,NULL     },{Experienced,0			,0			},{0      ,0      ,0     }},
/*43.Ҷ�ӱ���ɡ*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*44.��ת���� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*45.�����׮ */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*46.˯��     */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*47.����     */    { Double,0      ,0     ,{Specific,0     ,0     },{spute    ,NULL     ,NULL     },{Experienced,0			,0			},{Better ,0      ,0     }},
/*48.��ʹ�ƶ���*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*49.����ƶ���*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*50.����������*/   {Adjunct,Adjunct,0     ,{Specific,Specific,0   },{soulspeed,vanish   ,NULL     },{Unskilled	,Unskilled	,0			},{0      ,0      ,0     }},
/*51.�������� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*52.����ս�� */    {Adjunct, Triple,0     ,{0      ,0      ,0     },{succession,sun_att ,NULL     },{Unskilled	,Unskilled	,0			},{0      ,Better ,0     }},
/*53.�����Ϲ���*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*54.�������� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*55.��β���� */    {Nolimit,0      ,0     ,{Specific,0     ,0     },{blow     ,NULL     ,NULL     },{Unskilled	,0			,0			},{Good   ,0      ,0     }},
/*56.���̹�� */    { Single,Passive,0     ,{Specific,Specific,0   },{spute    ,backharm ,NULL     },{Experienced,Unskilled	,0			},{Better ,0      ,0     }},
/*57.����Ů�� */    { Single,Always ,Passive_S,{Specific,Self,Self },{strider  ,recover  ,newlife  },{Unskilled	,Unskilled	,Unskilled	},{Good   ,0      ,0     }},
/*58.«��ս�� */    {Adjunct,Adjunct,0     ,{Specific,Self  ,0     },{succession,cooldown ,NULL    },{Unskilled	,Experienced,0			},{0      ,0      ,0     }},
/*59.��ը���� */    {Adjunct,0      ,0     ,{Others ,0      ,0     },{randomfly,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*60.ԭʼ�㶹����*/ { Single,0      ,0     ,{Specific,0     ,0     },{lavaball ,NULL     ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*61.ԭʼ���տ�*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*62.���۰Ͷ�  */   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*63.����Ģ�� */    { Double,0      ,0     ,{0      ,0      ,0     },{poison   ,NULL     ,NULL     },{Experienced,0			,0			},{Better ,0      ,0     }},//����粻ͬ 
/*64.���۱��� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*65.�������� */    { Triple,Single ,0     ,{Self   ,Self   ,0     },{transfiguration,boom,NULL    },{Unskilled	,Unskilled	,0			},{Better ,Good   ,0     }},
/*66.ǿ������ */    {Adjunct,0      ,0     ,{0      ,0      ,0     },{corrosion,NULL     ,NULL     },{Unskilled	,0			,0			},{0      ,0      ,0     }},
/*67.�ѹ�Ӣ   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*68.�ش���   */    { Single,0      ,0     ,{Specific,0     ,0     },{spute	   ,NULL     ,NULL     },{Unskilled	,0			,0			},{Must   ,0      ,0     }},
/*69.����   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*70.�������� */    { Double,Passive_S,0   ,{Specific,Specific,0   },{haunted  ,bad_omen ,NULL     },{Unskilled	,Unskilled	,0			},{Better ,0      ,0     }},
/*71.��ͷ���� */    { Double,0      ,0     ,{Self   ,0      ,0     },{headchange,NULL    ,NULL     },{Unskilled	,0			,0			},{Have_to,0      ,0     }},
/*72.Ҭ�Ӽ�ũ��*/   {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*73.��յ��   */    {Nolimit,Single ,0     ,{Self   ,Self   ,0     },{alchemy,photosynthesis,NULL  },{Unskilled	,Unskilled	,0			},{Better ,50     ,0     }},
/*74.������   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*75.�Զ���   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*76.�Զ���   */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#1.ӣ��ը�� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#2.�������� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#3.��褽��� */    {Adjunct,Adjunct,0     ,{Specific,Specific,0   },{succession,soulspeed,NULL    },{Unskilled	,Experienced,0			},{0      ,0      ,0     }},
/*#4.�㶹��   */    {  Tetra,0      ,0     ,{Self   ,0      ,0     },{creasygrow,NULL    ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*#5.����ˮ�� */    {    0  ,0      ,0     ,{0      ,0      ,0     },{NULL     ,NULL     ,NULL     },{0			,0			,0			},{0      ,0      ,0     }},
/*#6.�¹��   */    { Single,0      ,0     ,{Self   ,0      ,0     },{darkstrength,NULL  ,NULL     },{Unskilled	,0			,0			},{Better ,0      ,0     }},
/*#7.�ϰٺ�	  */	{ Triple,0      ,0     ,{Specific,0     ,0     },{poison   ,NULL     ,NULL     },{Perfect	,0			,0			},{Better ,0      ,0     }},
};
//NPCs
const char NPCsname[NPCkind][NameLenthMax]=
{
	"ħ���¸�",
	"ħ��СA",
	"ħ��СB",
};
const int NPCsability[NPCkind][Properties]=
{
		              /*  Hp ���� ���� ���� ���� ���� ���� ���� ���� ���� ��ֵ ���� ���� ˲ʱ �Ƚ� ��ǩ  �����ȼ�*/
	/*0.ħ���¸�  */  {  600 ,50  ,20  ,3   ,83  ,0   ,12  ,83  ,50  ,0   ,995 ,0   ,Slo2,0   ,3   ,ST      ,1   },
	/*1.ħ��СA   */  {  275 ,30  ,10  ,0   ,0   ,0   ,9   ,0   ,50  ,0   ,995 ,0   ,Slo2,0   ,2   ,ST      ,1   },
	/*2.ħ��СB   */  {  165 ,60  ,5   ,0   ,0   ,5   ,4   ,83  ,167 ,15  ,995 ,0   ,Fast,0   ,2   ,ST      ,1   },
};
Skill NPCsskill_temp[NPCkind]=
{
/*0.ħ���¸� */    { Triple,Triple ,Triple ,{Specific,Specific,Specific},{hearttearing,calmdown,destroy},{Unskilled	,Unskilled	,Unskilled	},{Better ,Good  ,Have_to}},
/*1.ħ��СA  */    {Nolimit,0      ,0      ,{Specific,0      ,0        },{bandage  ,NULL     ,NULL     },{Unskilled	,0			,0			},{Have_to,0      ,0     }},
/*2.ħ��СB  */    {Nolimit,0      ,0      ,{Specific,0      ,0        },{bandage  ,NULL     ,NULL     },{Unskilled	,0			,0			},{Have_to,0      ,0     }},
};









