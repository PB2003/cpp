
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

int field_show(User *p_user,EFFECT *head,FIELD f,int T,int hard,int K,int R,int you,bool ifinstant,int map);//�ö����� 

#define Luck_continue_dT 20 
#define Luck_eff 20
#define Enermy			0
#define No_ally 		1
#define Complete_ally 	2
/*��ʼ��*/void Player::set_all(User *p_user,int hard/*�Ѷ�*/,int p,int C,bool fortune,int map)
{
	int i;
	if(p_user==NULL) //���û� 
	{
		if(map<0)
			name=default_player_name[p];//ע����p����i
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
				if(i!=3/*�����*/)
					ally[i]=Complete_ally;
				else
					ally[i]=Enermy; 
			cards=1;//һ��boss 
		}				 
	}
	else			//���û�
	{ 
		name=p_user->name;	
		level=p_user->get("level");
		cards=C+(	(hard==HARMONY||hard==EASY)	&&	C>=3); //��ƽ�����Ѷ��£�3�����Ͽ���ʱ��1�ſ�
		for(i=0;i<Locked_plants;i++)
			this->unlocked[i]=(p_user->unlocked[i]!=0);
		chance=(hard==HARMONY?250:(hard==EASY?75:(hard==NORMAL?50:50)))+level; //�Ѷ�Խ��chanceԽ��
		luck=fortune?Luck_eff:0; 
		deluck_T=fortune?Luck_continue_dT:0;	
		for(i=0;i<PMax;i++)
			ally[i]=Enermy;
	}
	//��ұ�� 
	playernum=p;
	for(i=0;i<HaveMax;i++) 
		have[i]=NULL;
	now=NULL;
	now2=NULL;	
	now_in_have=0;
	//�ȼ�Ȩ��
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
	//���� 		
	unfrozen_T=0;
	//��������
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
			rand()+rand();//��������� 
			do
			{ 			
				x=rand()%Pkind; 
				r=x+start_r;     //�������һ��ֲ�￨��
				j=x-Cherry;
				accept=plant[r].univ_demand(level,if_use_self_def,(0<=j&&j<Locked_plants?unlocked[j]:false),if_pierce);
				if(map==Fire_city)
					switch(x) 
					{
						case 12:/*����*/
						case 11:/*�Ȼ�*/
						case 27:/*����*/
							accept=false; 
					}
				//else 			
			}
			while(	!accept || plant[r].belong!=NOBODY	);//����������ˣ���ȼ�Ҫ����ߣ���һ��
			if(plant[r].tag_j(IA))
				icy==true;
			else if(plant[r].tag_j(FA))
				fire==true;
			have[i]=&plant[r];
			plant[r].belong=&player[playernum];          //��������Ʊ�����
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
	w.hint(2,sizeof("���������**�ſ��ƣ�"),"");
	if(playernum==you)
	    printf("���������%d�ſ��ƣ�",cards); 
    else
        printf("����%s��%d�ſ��ƣ�",name,cards);
    for(i=0;i<cards;i++)
	    have[i]->card_demon(  w.x+5+(SMA_dx+1)*(i/card_num_of_line)  ,  w.y+(i%card_num_of_line)*imaginary_width+4 ,1-have[i]->get("T next_actable"),SMA  );
	if(cheating_state)
	{
		//��ť������� 
	    BTN cheat_btn[K];
	    for(i=0;i<K;i++)
	        cheat_btn[i].judset(  i!=playernum  ); 
	    for(i=0;i<K;i++)
		    cheat_btn[i].set(  w.x+w.dx-8  ,  w.y+i*imaginary_width_2+(imaginary_width_2-Stdwidth)/2  ,  Stdheight  ,  Stdwidth  ,s1[i]);
        for(i=0;i<K;i++)
            cheat_btn[i].dye(player[i].name);
	    w.end_setall("��ʼ��Ϸ");
	    if(  w.do_action()!=K  )
	        player[  w.action  ].cards_showall(w,K,you,true);
    }
    else
    {
		w.hint(w.dx-10,sizeof("��ֹ�鿴���˿���"),"��ֹ�鿴���˿���");
		w.end_setall("��ʼ��Ϸ");
	    w.do_confirm(Notcount);
	}
	return;
}


void Player::storage_list(int x,int y,int dy/*�������߶�*/)
{
	int i;
	int counter=0;
	int imaginary_width=sizeof("������������");
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
	Place(x++,y);printf(" �ȼ���%2d",level);
	Color(Light|White);
	Place(x++,y);printf(" �÷֣�%d",points);
	Place(x++,y);
	if(rank==0) 
	{
		printf(" ��ʣ%d�ſ���",cards);
		Place(x++,y);printf(" ���������%d",sun);
		Place(x++,y);
		if(T<unfrozen_T)
		{
			Color(Light|Cyan);
		    printf(" ����״̬(%d)",unfrozen_T-T);
		    Color(Light|White);
	    }
	} 
	else
	    printf("����������%d",rank);
    return;
}
#define All_frozen -1
#define Break_up   -7 
int Player::gesture(PW w,int T,int K,bool be_ctrled)
{
	int i,p;
	int actable=0;
	int weight[K]={0};
	const char txt[3][5]={"����","����","��"}; 
	int s1[3+1][4];
	int s2[K+1][4];
	const int imaginary_width=w.dy/3;
	w.newpage();
	for(i=0;i<K;i++)
	    if(player[i].unfrozen_T<=T/*����T*/	&&	player[i].get("rank")==0/*û��*/ ) 
	    	{
	        	weight[i]=player[i].sigma_chance_get(T);
	        	++actable;
	    	}
	if(actable==0)
	    return All_frozen;
	if(!be_ctrled) 
	{
		if(unfrozen_T>T)//�ϸ�� 
		{
			w.hint(1,sizeof("���ѱ�������"),"���ѱ�������");
			w.hint(2,sizeof("������Ҳ�ȭ��..."),"������Ҳ�ȭ��...");
		}
		else
		{
			w.hint(1,sizeof("��ѡ�񡰴��ӡ�������������"),"��ѡ�񡰴��ӡ�������������");
		    BTN gst_btn[3+1];
		    w.set_btnN(3+1);
		    w.s1_link(s1);
			for(i=0;i<3;i++)
			{
				gst_btn[i].judset(true);
				gst_btn[i].set(  w.x+3  ,  w.y+i*imaginary_width+3  ,  Stdheight  ,  Stdwidth-4  ,s1[i]);
				gst_btn[i].dye(txt[i]);
	    	}
	    	w.end_setall("�˳�ս��"); 
			w.do_action();
			if(w.action==3) 
				return Break_up;
		} 		
		p=weighted_random(weight,K);
	}
	else
	{
		w.hint(1,sizeof("��ѡ�񱾻غ�������ң�"),"��ѡ�񱾻غ�������ң�");
	    BTN act_btn[K+1];
	    w.set_btnN(K+1);
	    w.s1_link(s2);
		for(i=0;i<K;i++)
		{
			act_btn[i].judset(player[i].unfrozen_T<=T/*����T*/	&&	player[i].get("rank")==0/*û��*/);
			act_btn[i].set(  w.x+3+(i/2)*4  ,  w.y+6+(i%2)*22  ,  Stdheight  ,  Stdwidth  ,s2[i]);
			act_btn[i].dye(player[i].name);
    	}
    	w.end_setall("�˳�ս��"); 
    	do
			p=w.do_action(); 
		while(act_btn[p].jud==false);
		if(w.action==K) 
			return Break_up;
	}
	w.hint(11,sizeof("��һ�ñ��غ�����Ȩ"),"");
    if(  p==playernum  )
        printf("���ñ��غ�����Ȩ");
    else
        printf("%s��ñ��غ�����Ȩ",player[p].name);
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
	w.hint(1,sizeof("����ѡ���ս���ƣ����Ұ�ť��ҳ��������ʣ��**�ſ��ơ�"),"����ѡ���ս���ƣ����Ұ�ť��ҳ��������ʣ��");
	printf("%2d�ſ���",cards);
	//��ť������� 
	BTN plant_btn[laid];
	int s1[w.set_btnN(laid+3)][4];
	w.s1_link(s1);
	for(i=0;i<laid;i++)
	{
		plant_btn[i].judset(true);
		plant_btn[i].set(  w.x+5  ,  w.y+(i%laidmax)*imaginary_width+1  ,  BIG_dx  ,  BIG_dy  ,s1[i]);/*Ҳ���ǿ�������*/
    }
	for(i=start_card;i<start_card+laid;i++)
	    have[i]->card_demon(  w.x+5 ,  w.y+(i%laidmax)*imaginary_width+1  ,(T==0?1:T)-have[i]->get("T next_actable"),  BIG  );
	w.page_setall(w.dx-8,5);
	w.end_setall("�鿴����");
	w.do_action();
	switch(w.action-laid)
	{
		case 2:
			field_show(NULL/*����������ν*/,NULL/*����������ν*/,std_combat_f,T,hard,K,2/*����������ν*/,playernum,true,7);
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
			w.newline(1,sizeof("��ѡ����********"),"��ѡ����");
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
	         weight[i]=15;//�߽׿� 
	now=have[  now_in_have=weighted_random(weight,cards)  ];
	return now_in_have;
}

Plant* Player::card_change(int situation,int T,int hard,int K,bool ifrealplayer,Plant* the_plant/*�ò���ʱ��NULLҲ��*/)
{
	Plant* back_value=now;
	Player *p=(the_plant->belong);
	const char *illustrate;
	int i;
	if(situation==Plant_die)
		illustrate="��Ŀ�����������";
	else if(situation==Explode)
	 	illustrate="��Ŀ������Ա���";
	else if(situation==Be_Captivate)
	 	illustrate="��Ŀ����ѱ��Ȼ�";	 	 	
	switch(situation)
	{
	    case Buy:
			back_value=have[cards++]=the_plant;//�ӿ� 
			the_plant->belong_change(this);
			break;
		case Captivate:
			have[cards++]=the_plant;//�����ţ������� 
			back_value=p->card_change(Be_Captivate,T,hard,K,  p->playernum==K-1/*K-1Ϊ�����*/  ,the_plant);//ΪNULL��Ϊ����������п��� 
			break; 
		case Explode:
		case Plant_die:
			the_plant->belong_change(NULL);//ֲ����������ʼ����Ч�����ں����и���
		case Be_Captivate:
			now=NULL;/*��break*/
			for(i=now_in_have+1;i<cards;i++) 
			    have[i-1]=have[i];//Ĩ����now_in_have 
			if(ifrealplayer)
	    	{
		    	PW w=p_action_pw;
		    	w.newpage();
		    	int s1[w.set_btnN(1)][4];//ֻ��1��ѡ�� 
				w.s1_link(s1);
				w.hint(1,sizeof("��Ŀ�����������"),illustrate);
				if(--cards==0)//����
				{ 
					w.hint(3,sizeof("���Ѿ��޿���ѡ��"),"���Ѿ��޿���ѡ��");
					Sleep(Std_flush_period*Std_wait_periods);
					back_value=NULL;//����ֵ��
				} 
				else//δ���� 
				{
					w.end_setall("ѡ���¿�");
					w.do_confirm(Notcount); 
					card_choose(p_choose_card_bk,T,hard,K,1);
					now->last_action_T_reset(T);
				}
	    	}
    		else 
    		{				
				have[cards-1]=NULL;//����
				if(--cards==0) 
			        back_value=NULL;//����ֵ�� 
				else//δ����
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
	if(dT<0) //�ϸ�С��
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
	    if(	mainskill_not_forbidden	&&	now->skill_avalible[i]>0/*=0��������ѡ��<0����������*/	)
	    {
	    	x=now->skill_favor[i];
	    	if(Have_to<x&&x<0)
	    	{
				P[3+i]+=skill_trig[-x];
				if (now->skill_avalible[i]>=100/*���޴�*/)
			    	P[3+i]*=2;
			}
			else if(x>0&&x<=sun)//������
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
	const char txt[buttons][5]={"�̵�","����","����","һ��","����","����"}; 
	srand((int)time(NULL));
	unsigned int seed=rand()+T;
	if(dT<0)
	{
		w.hint(3,sizeof("ֲ��������������״̬��ʣ��0�غϣ����޷������ж���"),"");
		printf("%s��������״̬��ʣ��%d�غϣ����޷������ж���",now->name,-dT/*ע��-��*/);
	}	     
	if(w.aut==true)
	{
		//����Ϊϵͳ�ж�
		int sys_act;
		int s2[w.set_btnN(1)][4];
		do 
		{
			w.newpage();
		    w.hint(1,sizeof("������������ж�..."),"");
		    printf("%s�����ж�...",name);
		    Sleep(Std_flush_period*5);
		    sys_act=system_action(T,dT,K,seed,	p_user->self_ctrl[isOthersObjSkillUseful]	);
			if(switch_of_act(head,p_user,w,T,K,seed,GT,sys_act))
			{			
				w.s1_link(s2);
				w.end_setall("����");
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
				player[i].now!=NULL					&&/*���Ȼ󹽶�����*/
				!player[i].now->if_go_exploding()  
			  )//ֻ��Ǽ������Ǳ��ּ�����ը���
			legal_aim=true;
		act_btn[1].judset(  !now->tag_j(AL)  &&  (now->if_go_exploding()||dT>=0/*����ȡ��*/ )  &&	legal_aim	);
		act_btn[2].judset(   now->tag_j(PD)  &&  dT>=0  );
		for(i=0;i<SkillMax;i++)
		{
			if(now->get("disposable"))//��ʱը�������ü� 
				act_btn[i+3].judset(  now->skill_avalible[i]>0	);
			else
		    	act_btn[i+3].judset(  now->skill_avalible[i]>0/*<0��Ϊ�����Լ���*/  &&  dT>=0  );
		}
		for(i=0;i<buttons;i++)
			act_btn[i].set(  btn_line  ,  w.y+i*imaginary_width+1  ,  Stdheight  ,  real_width  ,s1[i]);
	    do
	    {
			w.newpage();
			if(will_explode)
				w.hint(1,sizeof("��Ŀ��Ƽ����Ա���"),"��Ŀ��Ƽ����Ա���");
			else
		    	w.hint(1,sizeof("��ѡ���ж�"),"��ѡ���ж�");
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
	 	    w.end_setall("����");
			do
			    w.do_action();
			while(  w.action!=buttons&&/*�۶ϱ���*/act_btn[  w.action  ].jud==false); 
	   		switch_of_act(head,p_user,w,T,K,seed,GT,w.action);
		}
		while(w.action==SHOP);
	}	
	//�����˵�
	Player *r; 
	for(j=0;j<K;j++)
	{
		r=&player[j];
		if( (j==K-1/*��*/||p_user->self_ctrl[isOthersSideSkillUseful])==true	&&	r->get("rank")==0  &&  r->now!=NULL/*�Ȼ������*/)
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
						w.newline(4,sizeof("���Ӽ���xxxx�����ɹ���"),"���Ӽ���");
						printf("%s�����ɹ���",now->skill_name[i]); 
						if(skill_situation==Can_do_more&&!redid)
						{
							redid=true;
							w.newline(4,sizeof("����һ�ι�������"),"����һ�ι�������");
							Sleep(Std_flush_period*5);
							goto GOTOHERE_REDID; 
						}
					}
					else
					{
						w.newline(4,sizeof("���Ӽ���xxxx����ʧ�ܣ�"),"���Ӽ���");
						printf("%s����ʧ�ܣ�",now->skill_name[i]); 						
					}
					Sleep(Std_flush_period*5); 
				} 
			break;
		case PRODUCE:
			produce(w,T);
			break;
		case No_choice: /*��break*/
		case No_aim: /*��break*/
		case You_No_choice:
			w.newline(1,sizeof("%sû���ж�"),"");
			printf("%sû���ж�",name); 
			break; 
		default:
			i=choice-3;
			if(now->skill[i]==NULL)
				w.newline(2,sizeof("ERROR���˼�����δ����"),"ERROR���˼�����δ����");//���Ż� 
			else
			{	
				aim=aim_at(head,w,T,K,now->skill_aim[i],GT,p_user->self_ctrl[isOthersSideSkillUseful]);
				skill_situation=using_skill(head,w,T,K,i,aim); 
				if(skill_situation>0)
				{ 				
					if(skill_situation==Captivate_kill)//�Ȼ�ר������
						GT[aim][MFKCD]|=MFKCD_K;//�����ɱ 
					if(	aim==K-1	&&	(	skill_situation==Captivate_kill	||	skill_situation==Captivate_notkill	)	)
						return false;//����ͣ���Ҳ���ʾ������ť 
					w.newline(5,sizeof("���ܷ����ɹ���"),"");
					printf("%s�����ɹ���",now->skill_name[i]);
				}
				else
				{
					w.newline(5,sizeof("���ܷ���ʧ�ܣ�"),"");
					printf("%s����ʧ�ܣ�",now->skill_name[i]); 						
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
		aim=playernum;//ת��������aim���岻��ȫһ�� 
	EFFECT *E=apply_for(this,aim); 
	now->skill_use(sk_num,T);//��������  
	back_value=now->skill[sk_num](now->skill_intensity[sk_num],T,K,aim,this,E);	
	new_EFF(head,E);//���뵽������
	return back_value;			
}
void Player::produce(PW w,int T)
{
	int add=now->sun_produce(T);
	sun_add(add);
	w.newpage();
	Color(_White|Red|Light);
	w.RPlace(1,(w.dy-sizeof("����0000�����⣡"))/2);
	if(w.aut==true)
		printf("%s��������%d�����⣡���ܼ�%d�㣩",name,add,sun);
	else//����� 
		printf("����%d�����⣡���ܼ�%d�㣩",add,sun);
	sigma_produce+=add;	
	int s1[w.set_btnN(1)][4];
	w.s1_link(s1);
	w.end_setall("����");	
	w.do_confirm(Std_wait_periods);  //fastback���л�ȴ�1�뼴��
	return;
}
  
bool Player::shopping(PW w,int T,int K,unsigned int seed)
{
	w.newpage();	
	shop_system.laid_find(seed,level/*��ҵ�level*/);
	int i,j;
	bool if_bought_sth=false;
	const int CHAR=3;  
	if(w.aut==true)
	{
		w.hint(1,sizeof("������ƹ�����ĳЩ����"),"");//��ϵͳѡ���̵꣬��һ���Ṻ�� 
		printf("%s������ĳЩ����",name);
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
		sigma_consume+=cost;//�����Լӷ� 
	    card_change(Buy,T,HARD/*�Ժ��Ż�*/,K,false,p_goods);
	    return true;
	} 
	else
	{
		int t;
		int imaginary_width=w.dy/Max_Goods;
		int cardline=w.x+4;
		int cardrow;
		int un_color;
		const char unfound[4][CHAR]=   {"��","δ","��","��"};
		const char ununlocked[4][CHAR]={"��","δ","��","��"};
		const char (*txt)[CHAR];
		w.hint(1,sizeof("��ӭ�����̵꣡��ʣ�������"),"��ӭ�����̵꣡��ʣ������⣺");
		printf("%4d",sun);
		//����Ҳſ����� 
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
		//��ť������� 
		BTN buy_btn[Max_Goods];
		int s1[w.set_btnN(Max_Goods+1)][4];
		w.s1_link(s1);
		for(i=0;i<Max_Goods;i++)
	    	buy_btn[i].judset(  (shop_system.cost[i]!=0)&&(shop_system.cost[i]<=sun)  ); 
		for(i=0;i<Max_Goods;i++)
			buy_btn[i].set(  cardline+8  ,  w.y+i*imaginary_width+(imaginary_width-SMA_dy)/2  ,  Stdheight  ,  SMA_dy  ,s1[i]);
		w.end_setall("����");
		//�������
		do
    	{
			for(i=0;i<Max_Goods;i++)
	        	if(shop_system.randcard[i]>=0)
	        	{
			    	buy_btn[i].dye(" ��   ");
			    	printf("%3d",shop_system.cost[i]);/*�����Ų���Place*/
		    	}
		    	else
					buy_btn[i].dye("---");
			do
		    	w.do_action();
			while(  w.action!=Max_Goods&&/*�۶ϱ���*/buy_btn[  w.action  ].jud==false);
			switch(w.action)
			{
				case Max_Goods:
					break;
				default:
					if_bought_sth=true;
					int cost=shop_system.cost[w.action];
					Plant* p_goods=&plant[  shop_system.randcard[   w.action   ]  ];				
					sigma_consume+=cost;//�����Լӷ� 
			    	w.newline(1,sizeof("�ɹ������ƣ�********"),"�ɹ������ƣ�");
			    	printf("%s",p_goods->name);
			    	w.hint(2,sizeof("��ʣ������⣺"),"��ʣ������⣺");
	            	printf("%4d",sun_add(-cost));
	            	card_change(Buy,T,HARD/*�Ժ��Ż�*/,K,true,p_goods);
			    	for(i=0;i<Max_Goods;i++)//�����ظ����� 
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
		GT[MFKCD]|=MFKCD_F;//����ʧ�� 
		return; 
	}
	else
	{
		int F/*freeze*/=now->freeze(player[aim].now->get("tag"));//ÿ�˵ı��������жϣ������Ż������������ı���������Ч 
	    int W/*weaken*/=now->get("weaken");
		if(  F>0  &&  player[aim].now->tag_j(FL)  ) //�������Դݻٷ���Ŀ�� 
		    A=999;
		Player *p=&player[aim];    
		int attact_situation=p->be_attacked(T,A,F,W,PHYS,&GT[REALHURT]/*ֱ�Ӵ�����*/);
		int passive_info;	
		if(aim==K-1||sideskill_not_forbidden)
			for(i=0;i<SkillMax;i++)
				if(p->now->skill[i]!=NULL)
				{
					int *q	=	&p->now->skill_avalible[i];
					if(*q==Passive	||	(*q==Passive_S&&attact_situation==KILL)	)
					{
						passive_info=p->using_skill(head,w,T,K,i,playernum/*�������������*/);
						if(passive_info==Revive)
						{
							w.newline(6,sizeof("������ƻ��������"),"");
							printf("%s���������",p->name);
							Sleep(Std_flush_period*5);
							revive=true;
						}
						else if(passive_info==Badluck)
						{
							w.newline(6,sizeof("������Ƹо���һ˿����"),"");
							printf("%s�о���һ˿����",this->name);
							Sleep(Std_flush_period*5);
						}
						else if(passive_info==Backharm)
						{
							w.newline(6,sizeof("������Ƹо��е�ʹ"),"");
							printf("%s�о��е�ʹ",this->name);
							Sleep(Std_flush_period*5);
						}
						else if(passive_info==End_blast)
						{
							w.newline(6,sizeof("������Ʊ�������Ƴ��׼�ŭ�ˣ�"),"");
							printf("%s��%s���׼�ŭ�ˣ�",p->name,this->name);
							Sleep(Std_flush_period*5);
						}
						if(*q==Passive_S)
							*q=0;//����һ�� 
					}
				}				
		switch(attact_situation)
		{
			case HURT:
				GT[FROZEN]=F;
				GT[WEAKEN]=W;
				if(now->tag_j(DA))//�ڰ�����������Ҳ��Ч
			        GT[MFKCD]|=MFKCD_D;
			    break;
			case KILL:
				if(!revive)//���Ǹ���� 
					GT[MFKCD]|=MFKCD_K;
				if(now->tag_j(DA))//�ڰ�����������Ҳ��Ч
			    	GT[MFKCD]|=MFKCD_D;
			    break;
			case MISS:
				GT[MFKCD]|=MFKCD_M;
				break;
		}
    }
	return;
} 
void skill_attack(int T,int A,int F,int W,int att_kind,int aim,int *GT)//����player��Ա 
{
	switch(  player[aim].be_attacked(T,A,F,W,att_kind,&GT[REALHURT]/*ֱ�Ӵ�����*/)  )
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
	        return KILL;//ֱ������������ж�
		else
		{
			if(F!=0)	
			    unfrozen_T=T+1+F;//T+1�غϿ�ʼ���� 
	        now->strenth(-W/*ע��������*/,std_weaken_T);
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
			player[i].now!=NULL					&&/*���Ȼ󹽶�����*/
			!player[i].now->if_go_exploding()   &&
			ally[i]!=Complete_ally 
		  )//ֻ��Ǽ������Ǳ��ּ�����ը�����������
	    {
			P[i]+=3;//���� 
			Plant *p=player[i].pget("main");
			if(  p->tag_j(FT)  &&  now->tag_j(ST)  )//�򲻵����� 
			     continue;
			P[i]+=(p->get("value")/45)*3;//�߼�ֵĿ�� 
			if(  p->get("HP_L")  <=  now->get("attack average"))//�߼��ʻ�ɱ
				if(  p->get("HP_L")  <=  now->get("attack least")) 
					P[i]+=80;
				else
					P[i]+=40;
			P[i]+=(p->get("attack average")+p->get("sputter")/3)/5;
			P[i]+=p->get("freeze average")/200;
			if(p->tag_j(FA)&&now->tag_j(IA))//������ƿ���
				if(P[i]-=4<0)
					P[i]=0;
			if(  p->tag_j(MR)  &&  !now->tag_j(MR))//ˮ½���ƿ��� 
				if(P[i]-=3<0)
					P[i]=0;
			if(  p->tag_j(CV)  &&  now->tag_j(CT))//Ͷ�ֿ��ƿ��� 
				if(P[i]-=5<0)
					P[i]=0;
			if(  p->tag_j(PD)  &&  now->tag_j(DA))//�������ƿ��� 
				P[i]+=10;//��+
			if(  p->tag_j(FL)  &&  now->tag_j(FT))//�ؿտ��ƿ��� 
				P[i]=0;
		}
	int S=0;
	for(i=0;i<K;i++)
		S+=P[i];
	if(S==0)//һ��Ҳ�������ѡ��
		for(i=0;i<K;i++)
	    	if( i!=playernum  						&&
			  	player[i].get("rank")==0 			&&
			    player[i].now!=NULL					&&/*���Ȼ󹽶�����*/
				!player[i].now->if_go_exploding()   &&
				ally[i]!=Complete_ally 
			  )//ֻ��Ǽ������Ǳ��ּ�����ը�����������
				P[i]=3;
	for(i=0;i<K;i++)
		S+=P[i];
	if(S==0)//��Ȼһ��Ҳ������ѡ�� 
		return No_aim;
	else 
    	return weighted_random(P,K);	
}

int Player::aim_at(EFFECT *head,PW w,int T,int K,int aim_kind,int GT[][GO_THROUGH]/*go_through*/,bool sideskill_not_forbidden)
{
	int i,j;
	int aim;
	BTN att_btn[K-1];
	int s1[w.set_btnN(K-1)][4];/*ע��-1*/
	w.s1_link(s1);
	w.newpage();
	if(w.aut==true)
	{
		if(aim_kind==Self||aim_kind==Others)
		{ 
			w.hint(1,sizeof("�����ʹ���˼��ܣ�"),"");
			printf("%sʹ���˼��ܣ�",name);
			return aim_kind;//�Ժ�ͳһ��ʽ 
		}
		else
		{
			aim=system_aim(K);
			w.hint(1,sizeof("�����������������˽�����"),"");
			printf("%s��%s������%s��",	name,	player[aim].name,	aim_kind==Ordinate?"����":"����"	);
			GT[aim][AIMED]=1;
		} 		
	}
	else
	{
		if(aim_kind==Self||aim_kind==Others)
		{
			w.hint(1,sizeof("��ʹ���˼��ܣ�"),"��ʹ���˼���");
			w.end_setall("ȷ��"); 
			w.do_confirm(Notcount); 
			return aim_kind;
		}
		else
		{ 
			w.hint(1,sizeof("ѡ�񹥻�����"),"ѡ�񹥻�����"); 
		    //��ť�������  
		    int imaginary_width=w.dy/(K-1);
		    for(i=0;i<K;i++)
				if(i!=playernum)
				{
					j=i>playernum?i-1:i;
					att_btn[j].judset(  player[i].get("rank")==0/*��i����j*/&&  ! player[i].now->if_go_exploding()  ); 
					att_btn[j].set(  w.x+w.dx-8  ,  w.y+i*imaginary_width+(imaginary_width-SMA_dy)/2  ,  Stdheight  ,  Stdwidth  ,s1[i]);
					att_btn[j].dye(  player[i].name/*�����i����j*/  );
		    	}
			aim=w.do_action();
			if(  aim>=playernum/*�۳��Լ�*/  )
		        ++aim; 
		} 
	}
	
	if(aim_kind==Ordinate)//��ͨ����
	{
		GT[aim][AIMED]=1;//������ 
		int A=now->attack(T,player[aim].now->get("tag"));
		make_attack(head,w,T,K,A,aim,GT[aim],sideskill_not_forbidden);
	    
		if(now->get("sputter")!=0&&A!=Fail_att/*ʧ�ܵĹ����޷�����*/)
		    for(i=0;i<K;i++)
		    	if(  i!=playernum  &&  player[i].get("rank")==0  &&! player[i].now->if_go_exploding()  )//�Լ���������ҡ�ը������
		    	{
					GT[i][SPUTTER]=now->get("sputter");//���sputter��һ�������ⲻ�� 
		        	if(  i!=aim  )//��Ŀ����� 
		        	{
						GT[i][AIMED]=2;//������ 
						make_attack(head,w,T,K,now->get("sputter"),i,GT[i],sideskill_not_forbidden);
					} 
				}		
	} 
	else
		GT[aim][AIMED]=1;
	return aim;
}


