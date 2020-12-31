
#ifndef _RULE_TEXT_H_ 
    #define _RULE_TEXT_H_
    #include "rule_text.h"
#endif

#ifndef _RECORD_CPP_ 
    #define _RECORD_CPP_
    #include "record.cpp"
#endif

#ifndef _USERS_CPP_ 
    #define _USERS_CPP_
    #include "users.cpp"
#endif

#ifndef _GAMES_CPP_ 
    #define _GAMES_CPP_
    #include "game.cpp"
#endif

#ifndef _FOR_NEW_CPP_ 
    #define _FOR_NEW_CPP_
    #include "for_new.cpp"
#endif

#define BRIEF 0
#define RULES 1
#define FOR_NEW 2
#define QUIT 3 

 
void print_long(int x,int y,int dy,char* s) 
{
	string p=s;
	int i;
	for(i=0;*s!='\0';i++,s+=dy)
	{
		Place(x++,y);cout<<p.substr(i*dy,dy)<<endl;
    }
	return;
}
void file_print_long(int x,int y,int dy,const char* path) 
{
	FILE *fp;
	if((fp=fopen(path,"r"))==NULL)
	{
		system("pause");
		exit(0);
	}
	char *long_s;
	fscanf(fp,"%s",long_s);
	fclose(fp);
	print_long(x,y,dy,long_s);
	return;
}
void brief(PW w)
{
	char long_s[LongN]="    ��ֲ���սֲ����ԡ�ֲ���ս��ʬ������ֲ���ս��ʬ 2������ֲ���ս��ʬOnline��Ϊ��ɫԭ�ʹ����ġ�"
	"����DEV C++5.2.0.3���������ġ���DOS �����µ�C++ ����ģ�⿨����Ϸ����Ϸ������������ˣ���ϸ�������Ը��ӡ�"
	"��Ϸ����������ģ��ġ���ť����ɣ������Ѻá�ϵͳ�ȶ��Ժá��˻��������㡣�ܼ���ȱ��Windows��̻����Ͳ���ʹ��graphics.h����"
	"ʹ��C++��������д���׵Ŀ��ӻ�С��Ϸ����������ѧϰC++ ���Ե�ѧԱ�ı����Ȥ��";
	w.newpage();
	w.hint(1,sizeof("����Ϸ������2020��12��30�գ�Ϊ���߸��汾"),"����Ϸ������2020��12��30�գ�Ϊ���߸��汾");
	w.hint(3,sizeof("��Ȩ���У��й���ѧ������ѧ ��ѧ����Ͽ�ѧѧԺ PB20030773���ӿ�"),"��Ȩ���У��й���ѧ������ѧ ��ѧ����Ͽ�ѧѧԺ PB20030773���ӿ�"); 
	print_long(w.x+5,w.y+2,w.dy-4,long_s);
	w.end_setall("�������˵�"); 
	w.do_confirm(Notcount);
	return;
}

void rules(BOOK w,int page)
{
	int i,line=5;
	char (*p_l)[LongN];
	char *long_s=NULL; 
	const int parts=3; 
	const int space=(w.dy-Stdwidth*parts)/(parts+1);
	const char txt[parts][sizeof("��Ϸ���")]={"����","ս��","�û�"};
	w.newpage(Rulepages,page);
	int s1[w.set_btnN(parts+3)][4];
	w.s1_link(s1);
	if(page==ABSTRACT)
	{
		Color(_White|_Light|Yellow|Light);
		w.hint(3,sizeof("����Ŀ¼"),"����Ŀ¼");
		BTN part_btn[parts];	    
		for(i=0;i<parts;i++)
		{
	    	part_btn[i].judset(  true  );
			part_btn[i].set(  w.x+10  ,  w.y+i*(Stdwidth+space)+space  ,  Stdheight  ,  Stdwidth  ,s1[i]);
			part_btn[i].dye(txt[i]);
    	}
	}
	else
	{	
		w.s1_link(s1+parts);
	    Color(_Black|Yellow|Light);
	    switch(page)
	    {
			case P_CARDS:
				w.RPlace(3,(w.dy-sizeof("����"))/2);printf("����"); 
				plant[0].card_demon(w.x+6,w.y+w.dy-BIG_dy-4,1-plant[0].get("T next_actable"),BIG);
				break;
			case P_CARDS+1:
				plant[0].card_demon(w.x+6,w.y+w.dy-BIG_dy-4,1-plant[0].get("T next_actable"),BIG);
				break;
		
			case P_BATTLE:
				w.RPlace(3,(w.dy-sizeof("ս��"))/2);printf("ս��"); 
				break;

			case P_USER:
				w.RPlace(3,(w.dy-sizeof("�û�"))/2);printf("�û�"); 
				break;
		}
		p_l=rule[page-2];
		Color(w.dftc);
		for(i=0;(*p_l)[0]!='#'/*������*/;i++)
		{
			w.RPlace(line++,2);printf("%s",p_l++);
		}
		const char *skill_kind;
		int start_i;
		int end_i;
		if(page==P_SKILLS||page==P_SKILLS+1)
		{
			start_i=(page==P_SKILLS?	1/*����0*/			:	Skill_of_first_page);
			end_i=	(page==P_SKILLS?	Skill_of_first_page	:	AllSkills+1);
			for(i=start_i;i<end_i;i++)
			{
				w.RPlace(line++,2);
				switch(skillname[i].act_kind)
				{
					case Passive	:skill_kind="������";break;
					case Passive_S	:skill_kind="������";break;
					case Always 	:skill_kind="������";break;
					case Adjunct	:skill_kind="���Ӽ�";break;
					default			:skill_kind="������";
				}
				printf("%d.%s\t[%s]����ߵȼ�%s������%d�غϣ���%s",
						i,
						skillname[i].name,
						skill_kind,
						roman_n[skillname[i].max_intensity],
						skillname[i].effected_Ts,
						skillname[i].describe);
			}
		}   
	}
	w.page_setall(w.dx-8,5);
	w.end_setall("�������˵�");
    w.do_action();
	switch(w.action)
	{
		case 5:
			return; 
			break;
		case 3:
			rules(w,page-1);
			break;
		case 4:
			rules(w,page+1);
			break;
		case 0:
			rules(w,P_CARDS);
			break;
		case 1:
			rules(w,P_BATTLE);
			break;
		case 2:
			rules(w,P_USER);
			break;
	}
	return;
}
#define USERNAME 0
#define PSWD 1
#define LOGIN 2
#define SIGNIN 3
#define LASTTIME 4 
bool log_in(PW w,User *p_user)
{
	const int btns=5;
	int i;
	BTN in_btn[btns-2];
	int s1[w.set_btnN(btns+1)][4];
	w.s1_link(s1);
	const char txt[btns-2][sizeof("��¼")]={"��¼","ע��","�ϴ�"};
	const char in_txt[2][sizeof("���������루�����û�����...")]={"�������û���...","���������루�����û�����..."};
	bool put_username=false; 
	bool put_pswd=false; 
	bool right_put_username=false;
	bool right_put_pswd=false;	
	const int in_x[2]={w.x+7,w.x+13};
	const int in_y=w.y+4;
	INP_BAR in[2]={{  in_x[0]  ,  in_y  ,  sizeof("���������루�����û�����...")+6  ,  White|Light  }, 
				   {  in_x[1]  ,  in_y  ,  sizeof("���������루�����û�����...")+6  ,  White|Light  }};
	for(i=0;i<btns-2;i++)
		in_btn[i].set(  w.x+6+6*i ,  w.y+w.dy-Stdwidth-4  ,  Stdheight  ,  Stdwidth  ,s1[2+i]);
	in_btn[2].judset(  last_user(p_user)  );//������˺� 
    while(1)
	{
		w.newpage();
		w.hint(1,sizeof("������෽�������û��������룬���Կո��û���������ʱ��Ĭ��Ϊע��״̬��"),"������෽�������û��������룬���Կո��û���������ʱ��Ĭ��Ϊע��״̬��");
		w.hint(16,sizeof("����ϴα��������룬����ֱ�ӵ�¼"),"����ϴα��������룬����ֱ�ӵ�¼"); 
		w.hint(3,sizeof("ע�⣬�û���������ֻ��Ϊ��%c��%c��%c��%c��\\n��\\0�����ASCII�ַ���"),"ע�⣬�û���������ֻ��Ϊ");
		printf("��%c��%c��%c��%c��\\n��\\0�����ASCII�ַ���",MARK,INTERVAL,ADD,NO);	
		for(i=0;i<2;i++)
    		in[i].setall(	in[i].search.s[0]=='\0'?	in_txt[i]:(const char*)in[i].search.s	,s1[i]);
		Color(w.dftc);w.RPlace(6*3+3,w.dy-Stdwidth-4); 
		if(  in_btn[2].jud  )
			printf("�û���%s",p_user->name);
		else
		    printf("�ϴ�δ����");
		w.end_setall("�������˵�");
		
		in_btn[0].judset(  right_put_username&&right_put_pswd  );//��¼ 
		in_btn[1].judset(  put_username&&!right_put_username&&put_pswd  );//ע��
		for(i=0;i<btns-2;i++)			
			in_btn[i].dye(txt[i]);
		do
			i=w.do_action(); 
		while(  (i==2&&in_btn[0].jud==false)  ||  (i==3&&in_btn[1].jud==false));
		
		switch(w.action)
		{
			case USERNAME:
				while(in[USERNAME].putin_vk('s')==false)
				{
					in[USERNAME].newtxt("�Ƿ����룡"); 
					Sleep(500);
				}
				put_username=true;
				Color(_Light|_White|Green);Place(in_x[0]+1,in_y);
				if(right_put_username=find_user(in[USERNAME].search.s))  //��ͬ���û� 
				 	printf("�û�����ȷ��");
				else
					printf("���û���");
				Sleep(500);
				in[USERNAME].clearboard(_Blue);
				break;
			case PSWD:
				while(in[PSWD].putin_vk('s')==false)
				{
					in[PSWD].newtxt("�Ƿ����룡"); 
					Sleep(500);
				}		
				Place(in_x[1]+1,in_y);
				if(right_put_username)
					if(find_pswd(in[USERNAME].search.s,in[PSWD].search.s))					
					{ 
						Color(_Light|_White|Green);
						printf("������ȷ��");
						right_put_pswd=true;
					} 
					else
					{
						Color(_Light|_White|Red);
						printf("�������");
					} 
				Sleep(500);
				in[PSWD].clearboard(_Blue);
				put_pswd=true;
				break;
			case LOGIN:
				p_user->get_users_information(in[USERNAME].search.s);
				return true;
			case SIGNIN:
				p_user->new_user(in[USERNAME].search.s,in[PSWD].search.s);
				p_user->get_users_information(in[USERNAME].search.s);
				return true;
			case LASTTIME:
				return true;
			default:
				return false;
		}
	}

}

bool surface(PW w,User *p_user,bool logged_in)
{
	int i;
	const int btns=4;
	const int space=(w.dy-Stdwidth*2)/3;
	const char *operate_ways="��������Ҽ��������¡���ctrl��ģ����굥�����������ҷ�ҳ��ť��������Ҳ��Ч��";
	const char *about_buttons="ע�⣺������ɫ��ťΪ�ɵ��״̬����ɫ��ťΪ���ɵ��״̬";
	const char txt[btns][sizeof("��Ϸ���")]={"��Ϸ���","��Ϸ����","���ֵ���","�˳���Ϸ"}; 
	BTN menu_btn[btns];
	int s1[w.set_btnN(btns+1)][4];
	w.s1_link(s1);
	while(logged_in==false)
	{
		system("color 1e");
		system(size_cmd);
		Place(4,(Max_dy-sizeof("ֲ���սֲ�� v1.0.0"))/2);printf(title); 	
		w.newpage();
		for(i=0;i<btns;i++)
		{
	    	menu_btn[i].judset(  true  );
			menu_btn[i].set(  w.x+6+(Stdheight+4)*(i/2)  ,  w.y+(i%2)*(Stdwidth+space)+space  ,  Stdheight  ,  Stdwidth  ,s1[i]);
			menu_btn[i].dye(txt[i]);
    	}
		w.end_setall("��¼/ע��");
		w.do_action();
		switch(w.action)
		{
			case BRIEF:
				brief(w);
			    break;
			case RULES:
				rules(rules_bk,ABSTRACT);
			    break;
			case FOR_NEW:
				for_freshman();
			    break;
			case QUIT:
				return false; 
			default:
				if(log_in(w,p_user))
				{
					logged_in=true;
				    return true;
			    }
		}
	}
}
#define Labs 2
const int built_max=1000;
void synthesis(BOOK w,User *p_user,int page)
{
	int i,j;
	const int btns_1=9;
	const int btns_2=6;
	int btns=(page==1?btns_1:btns_2);
	const int colors=7;
	int *ingred=p_user->all_have;
	int s1[btns+3][4];
	int s2[3][4];
	w.newpage(Labs,page);
	BTN 	syn_btn[btns];
	w.set_btnN(elem(s1));
	w.s1_link(s1);	
	if(page==1)
	{
		w.hint(1,sizeof("�л�ʵ����"),"�л�ʵ����");
		w.hint(3,sizeof("��ʵ������Ѱ�����Ҽӹ�ԭ���ϣ������ఴť���кϳɣ�"),"��ʵ������Ѱ�����Ҽӹ�ԭ���ϣ������ఴť���кϳɣ�");
		w.hint(5,sizeof("ͨ���ϳɿ��Ի��ϡ��ֲ��ͳɾ�Ŷ��"),"ͨ���ϳɿ��Ի��ϡ��ֲ��ͳɾ�Ŷ��");
		tf.newtxtf(w.x+9,w.y+80,14,54,1,_Light|_White); 
		tf.say("�ϳ��䷽��"); 
		tf.say("");
		tf.say("�߲ʽ�����7��ֲ����Ƭ*��1");
		tf.say("ӣ��ը������ɫ��Ƭ*4+�߲ʽ���*1+������֮Ҷ*1");
		tf.say("�������ӣ���ɫ��Ƭ*4+�߲ʽ���*1+������֮Ҷ*1");
		tf.say("��褽��󣺻�ɫ��Ƭ*4+�߲ʽ���*1+������֮Ҷ*1");
		tf.say("�㶹��  ����ɫ��Ƭ*4+�߲ʽ���*1+������֮Ҷ*1");
		tf.say("����ˮ�ɣ���ɫ��Ƭ*4+�߲ʽ���*1+������֮Ҷ*1");
		tf.say("�¹��  ����ɫ��Ƭ*4+�߲ʽ���*1+������֮Ҷ*1");
		tf.say("�ϰٺ�  ����ɫ��Ƭ*4+�߲ʽ���*1+������֮Ҷ*1");
		tf.say("������֮�����߲ʽ���*1+������֮Ҷ*3");	
	}
	else
	{
		w.hint(1,sizeof("����ʵ����"),"����ʵ����");
		int built=p_user->building;
		if(built<built_max)
		{
			w.set_btnN(elem(s2));
			w.s1_link(s2);
			w.hint(3,sizeof("��ѧ�����˰�����ը�ˣ����ڻ����ޡ�Ҫ������æ��"),"��ѧ�����˰�����ը�ˣ����ڻ����ޡ�Ҫ������æ��");
			Strip(w.x+7,w.y+20,built,built_max,100,4,_Red,_Black,w.dftc);
			w.hint(8,sizeof("ʩ������"),"ʩ������");
			w.page_setall(w.dx-8,5);
			w.end_setall("����");
			if(w.do_action()==2)
				return;
			else
				return;
		}
		w.hint(3,sizeof("��ʵ�����շѰ����������װ�����㻹��֪������ʲô�������ˣ��ܿ찡��"),"��ʵ�����շѰ����������װ�����㻹��֪������ʲô�������ˣ��ܿ찡��");
		tf.newtxtf(w.x+9,w.y+70,14,64,1,_Light|_White); 
		tf.say("�ϳ��䷽��"); 
		tf.say("");
		tf.say("�׳ǵ�ͼ��$200������ɫ��Ƭ*2+�̱�ʯ*1+����*1+ĩӰ����*1");
		tf.say("���ɺϳɵ���Ʒ���һ�û���");
		tf.say("������ҩ��$75��������*1+�̱�ʯ*1+�߲ʽ���*1");
		tf.say("��Ų��ѥ��$75��������*2+ĩӰ����*1+������֮��*1");
		tf.say("�����ؽ���$150��������*1+�̱�ʯ*1+�½�Ͻ�*2");
		tf.say("��ջ��ף�$150�����½�Ͻ�*3+ĩӰ����*1+������֮��*1");

	}
	for(i=0;i<btns;i++)
		syn_btn[i].set(w.x+9+(i/3)*6,w.y+10+(i%3)*20,Stdheight,Stdwidth,s1[i]);
	w.page_setall(w.dx-8,5);
	w.end_setall("����");
	bool 		con=true;
	const char 	txt1[2][btns_1][sizeof("������֮��")]=
	{
		{"�߲ʽ���","ӣ��ը��","��������","��褽���","�㶹��","����ˮ��","�¹��","�ϰٺ�","������֮��"},
		{"�׳ǵ�ͼ","���ɺϳ�","������ҩ","��Ų��ѥ","�����ؽ�","��ջ���"}
	};
	const char  (*txt)[sizeof("������֮��")]=txt1[page-1];
	do
	{	
		int money=p_user->get("coins");
		for(i=0;i<btns;i++)
		{
			if(page==1)
				switch(i)
				{
					case 0://�߲ʽ��� 
						for(j=0;j<colors;j++) 
							con=(con&&(ingred[j]>0));
						break;
					case 8://������֮��
					 	con=(ingred[The_fruit]>0	&&	ingred[The_leaf]>=3	);
					 	break;
					default:
						con=(ingred[i-1]>=4	&&	ingred[The_fruit]>0	&&	ingred[The_leaf]>=1	);
						if(p_user->unlocked[i-1]!=0)
						{ 
							Color(w.dftc); 
							Place(w.x+12+(i/3)*6,w.y+14+(i%3)*20);printf("�ѻ��"); 
						} 
				}
			else
				switch(i)
				{
					case 0://�׳ǵ�ͼ 
						con=(ingred[0]>=2	&&	ingred[The_emerald]>=1	&&	ingred[The_ice]>=1	&&	ingred[The_perl]>=1	&&money>=200);
						break;
					case 1://���ɺϳ�
						con=false;
						break;
					case 2://������ҩ 
						con=(ingred[The_ice]>=1	&&	ingred[The_emerald]>=1	&&	ingred[The_fruit]>=1	&&money>=75);
						break;
					case 3://��Ų��ѥ
						con=(ingred[The_ice]>=2	&&	ingred[The_perl]>=1		&&	ingred[The_flower]>=1	&&money>=75);
						break;
					case 4://�����ؽ�
						con=(ingred[The_ice]>=1	&&	ingred[The_emerald]>=1	&&	ingred[The_ingot]>=2	&&money>=150);
						break;
					case 5://��ջ���
						con=(ingred[The_ingot]>=3	&&	ingred[The_perl]>=1	&&	ingred[The_flower]>=1	&&money>=150);
						break;
						
				}
			syn_btn[i].judset(con);
			syn_btn[i].dye(txt[i]);					
		} 	
		do
			w.do_action();		
		while(w.action<btns  &&  syn_btn[w.action].jud==false	);
		if(page==1)
			switch(w.action)
			{
				case 0://�߲ʽ��� 
					for(i=0;i<colors;i++) 
						p_user->obtain(i,-1);
					p_user->obtain(The_fruit,1);
					w.newline(5,sizeof("һ���߲ʽ����ѷ������Ĳֿ�"),"һ���߲ʽ����ѷ������Ĳֿ�");
					break;
				case 8://������֮��
					p_user->obtain(The_fruit,-1);
					p_user->obtain(The_leaf,-3);
					p_user->obtain(The_flower,1);
					w.newline(5,sizeof("һ��������֮���ѷ������Ĳֿ�"),"һ��������֮���ѷ������Ĳֿ�");
				 	break;
				case 9:
					synthesis(w,p_user,page-1);
					break; 
				case 10:
					synthesis(w,p_user,page+1);
					break; 
				case 11:
					break;
				default:
					p_user->obtain(w.action-1,-4);
					p_user->obtain(The_fruit,-1);
					p_user->obtain(The_leaf,-1);
					p_user->unlock(w.action-1);//����ֲ��
					w.newline(5,sizeof("�ɹ������ÿ���"),"�ɹ������ÿ���");
			}
		else
			switch(w.action)
			{
				case 0://�׳ǵ�ͼ 
					p_user->obtain(0,-2);
					p_user->obtain(The_emerald,-1);
					p_user->obtain(The_ice,-1);
					p_user->obtain(The_perl,-1);
					p_user->obtain(The_map,1);
					p_user->add("coins",-200);
					w.newline(5,sizeof("һ���׳ǵ�ͼ�ѷ������Ĳֿ�"),"һ���׳ǵ�ͼ�ѷ������Ĳֿ�");
					break;
				case 2://������ҩ 
					p_user->obtain(The_fruit,-1);
					p_user->obtain(The_ice,-1);
					p_user->obtain(The_emerald,-1);
					p_user->obtain(The_potion,1);
					p_user->add("coins",-75);
					w.newline(5,sizeof("һ��������ҩ�ѷ������Ĳֿ�"),"һ��������ҩ�ѷ������Ĳֿ�");
				 	break;
				case 3://��Ų��ѥ 
					p_user->obtain(The_flower,-1);
					p_user->obtain(The_ice,-2);
					p_user->obtain(The_perl,-1);
					p_user->obtain(The_boots,1);
					p_user->add("coins",-75);
					w.newline(5,sizeof("һ����Ų��ѥ�ѷ������Ĳֿ�"),"һ����Ų��ѥ�ѷ������Ĳֿ�");
				 	break;
				case 4://�����ؽ� 
					p_user->obtain(The_ice,-1);
					p_user->obtain(The_emerald,-1);
					p_user->obtain(The_ingot,-2);
					p_user->obtain(The_sword,1);
					p_user->add("coins",-150);
					w.newline(5,sizeof("һ�������ؽ��ѷ������Ĳֿ�"),"һ�������ؽ��ѷ������Ĳֿ�");
				 	break;
				case 5://��ջ��� 
					p_user->obtain(The_ingot,-3);
					p_user->obtain(The_perl,-1);
					p_user->obtain(The_flower,-1);
					p_user->obtain(The_shield,1);
					p_user->add("coins",-150);
					w.newline(5,sizeof("һ����ջ����ѷ������Ĳֿ�"),"һ����ջ����ѷ������Ĳֿ�");
				 	break;
				case 6:
					synthesis(w,p_user,page-1);
					break; 
				case 7:
					synthesis(w,p_user,page+1);
					break; 
				case 8:
					break;
			}
		p_user->record_users_information();	
	}
	while(w.action<btns);
	return; 
}
void inventory(BOOK w,User *p_user,int page)
{
	const int frame_x=w.x+3;
	const int frame_y=w.y+2;
	const int frame_size=12; 
	const int everyL=6;
	const int everyR=2;
	const int everyP=everyL*everyR;
	const int btns=1;
	int i,n,k;
	int sx;
	int sy;
	int s1[w.set_btnN(btns+3)][4];
	BTN syn_btn;
	syn_btn.judset(true);
	syn_btn.set(w.x+29,w.y+90,Stdheight,Stdwidth,s1[0]);
	w.s1_link(s1);
	do
	{
		w.newpage((ThingsMax-1)/everyP+1,page);
		w.hint(1,sizeof("�ҵĲֿ�"),"�ҵĲֿ�");
		Dyeslots(frame_x,frame_y,frame_size,frame_size*2,everyR,everyL,_Cyan);
		syn_btn.dye("�ϳ���Ʒ"); 
		n=0;
		for(i=0;i<ThingsMax;i++)
			if((k=p_user->all_have[i])!=0)
			{
				if(n>=everyP*(page-1)&&n<everyP*page)
				{			
					sx=frame_x+(n%everyP/everyL)*(frame_size-1);
					sy=frame_y+(n%everyP%everyL)*(frame_size-1)*2;
					Color(_Cyan);Place(sx+(frame_size-1),sy+8);
					printf("%s",thingname[i]);
					Color(_White);Place(sx+(frame_size-2),sy+(frame_size-3)*2);
					printf("%4d",k);
					switch(i)
					{
						case The_clover:
							draw(four_leaf_clover_img,sx+1,sy+6,9,13,_Green|_Light);
							break;
						case The_medel:
							medal_pict.set(sx+1,sy+6);
							medal_pict.draw(-1);
							break;
						case The_fruit:
							fruit_pict.set(sx+1,sy+6);
							fruit_pict.draw(-1);
							break;
						case The_leaf:
							draw(leaf_img,sx+2,sy+6,8,11,_Green);
							break;
						case The_flower:
							flower_pict.set(sx+3,sy+6);
							flower_pict.draw(-1);
							break;
						case The_ice:
							blue_ice_pict.set(sx+4,sy+7);
							blue_ice_pict.draw(-1);
							break; 
						case The_emerald:
							emerald_pict.set(sx+3,sy+5);
							emerald_pict.draw(-1);
							break;
						case The_ingot:
							ingot_pict.set(sx+2,sy+4);
							ingot_pict.draw(-1);
							break;
						case The_perl:
							perl_pict.set(sx+2,sy+4);
							perl_pict.draw(-1);
							break;
						case The_map:
							map_pict.set(sx+3,sy+4);
							map_pict.draw(_Red);
							break;
						case The_potion:
							potion_pict.set(sx+1,sy+6);
							potion_pict.draw(-1);
							break;
						case The_boots:
							boots_pict.set(sx+4,sy+4);
							boots_pict.draw(-1);
							break;
						case The_sword:
							sword_pict.set(sx+2,sy+4);
							sword_pict.draw(-1);
							break;
						case The_shield:
							shield_pict.set(sx+2,sy+4);
							shield_pict.draw(-1);
							break;										
						default:
							draw(scrap_img,sx+3,sy+5,6,12,_Rand_color(i));
					}				
				}
				++n;//������ 
			}
		w.page_setall(w.dx-7,5);
		w.end_setall("����"); 
		w.do_action();
		BOOK w2=w;	
		switch(w.action)
		{
			case 0:				
				synthesis(w2,p_user,1);	
				break;
			case 1:	
				inventory(w2,p_user,page-1);
				break;
			case 2:	
				inventory(w2,p_user,page+1);
				break;
			case 3:	
				break; 
				
		}
	}
	while(0);
	return;
}

int have_unlocked(User *p_user,bool only)
{
	int have=0;
	int level=p_user->get("level");
	int i;
	if(!only)//���� 
		for(i=0;i<Pkind;i++)
			switch(plant[i].demand(true)) 
			{
				case Selfdef:	if(p_user->self_ctrl[adapt_selfdef]!=0)	++have;		break;
				case Collect:	if(p_user->unlocked[i-Cherry]!=0)		++have;		break;
				default:if(plant[i].demand(true)<=level)				++have;
			}
	else//���� 
		for(i=0;i<Pkind;i++)
    		if(plant[i].demand(true)==level)   		
    			++have;
    return have;
} 

void my_collection(BOOK w,int page,User *p_user)
{
	int level=p_user->get("level");
	const int total=Pkind;
	const int everyL=w.dy/(SMA_dy+2);
	const int everyR=(w.dx-10)/(SMA_dx+1);
	const int everyP=everyL*everyR; 
	w.newpage((total-1)/everyP+1,page);
	int s1[w.set_btnN(3)][4];
	w.s1_link(s1);
	int i,j,k=0,dem;
	int P_total=(page==w.maxpage?(total-1)%everyP+1:everyP);
	for(i=0;i<everyR;i++)
		for(j=0;j<everyL;j++)
		{
			if((k=(page-1)*everyP+i*everyL+j)>=Pkind)
				goto GOTOHERE_BREAK_OUT;
			dem=plant[k].demand(true);
			if	(	(dem>0	&&	dem<=level)	||	
					dem==Selfdef			||
					(dem==Collect	&& p_user->unlocked[k-Cherry]!=0/*�ѽ���*/)
				)
				plant[k].card_demon(w.x+i*(SMA_dx+1)+2,w.y+j*(SMA_dy+2)+4,1-plant[k].get("T next_actable"),SMA); 
			else
			{
				Dyearea(w.x+i*(SMA_dx+1)+2,       w.y+j*(SMA_dy+2)+4,       SMA_dx,SMA_dy,_Light);
				Place(w.x+i*(  SMA_dx+1)+2+SMA_dx/2,w.y+j*(SMA_dy+2)+4+(SMA_dy-sizeof("???"))/2);printf("???");
			}
		}
	GOTOHERE_BREAK_OUT:
	w.end_setall("����ͼ��");  
	w.page_setall(w.dx-8,5);
	w.do_action();
	switch(w.action)
	{
		case 2:
			return;
		case 0:
			my_collection(w,page-1,p_user);
			break;
		case 1:
			my_collection(w,page+1,p_user);
			break;
    }
    return;
}                  
#define Cardspages (Pkind/2+3)
#define Skillpage 2
#define MY_CARDS 0
#define SKILL_DESCRIBE 1
#define SEARCH_MORE 2
void collection(BOOK w,int page,User *p_user)
{
	int level=p_user->get("level"); 
	int i,j;
	const int cpx=w.x+7;
	const int cpy=w.y+w.dy-18;
	const int search_x=w.x+17;
	const int search_y=w.y+6;
	int line=5;
	char (*p_l)[LongN];
	char *long_s=NULL; 
	const int btns=3; 
	GOTOHERE_FINISH_MY:
	w.newpage(Cardspages,page);
	INP_BAR input={search_x ,  search_y ,sizeof("�����������...")+6,White|Light };//������ 
	int s1[w.set_btnN(btns+3)][4];
	w.s1_link(s1);
	if(page==ABSTRACT)
	{ 
		Color(_White|_Light|Yellow|Light);
		w.hint(3,sizeof("ֲ��ͼ��"),"ֲ��ͼ��");
		BTN a_btn[btns-1];//����һ��INPUT��;	    
		for(i=0;i<btns-1;i++)
	    	a_btn[i].judset(  true  );
	    a_btn[0].set(  w.x+6  ,  w.y+6  ,  Stdheight ,  Stdwidth  ,s1[0]);
		a_btn[1].set(  w.x+12 ,  w.y+6  ,  Stdheight , Stdwidth   ,s1[1]);
		a_btn[0].dye("�ҵĿ���");
    	a_btn[1].dye("���Ŀ¼");
    	input.setall(	"�����������...",s1[2]);
		int have=have_unlocked(p_user,false); 
    	int   color=have>=30?(have>=50?(have>=70?_Cyan|_Light:_Yellow|_Light):_White|_Light):_Yellow;
    	const char *dan=have>=30?(have>=50?(have>=70?"��ʯ":"�ƽ�"):"����"):"��ͭ";
    	Color(w.dftc);Place(cpx-1,cpy-3);printf("�����ռ�����������");
    	w.hint(9,sizeof("��ܰ��ʾ�����ڿ��Ŀ¼�в鵽��������ٽ������أ�����ӷ��㣡"),"��ܰ��ʾ�����ڿ��Ŀ¼�в鵽��������ٽ������أ�����ӷ��㣡");
    	//����ͼ��
		draw(cup_img,cpx,cpy,9,11,color);
		//�ռ��� 
    	Strip(cpx+10,cpy,have,Pkind,11,3,_Green,_Black,w.dftc);
    	Place(cpx+11,cpy+4);printf("%s",dan);
    	w.end_setall("�������˵�"); 
	}
	else if(page==2||page==3)
	{
		const int everyR=22;
		const int everyL=2;
		const int everyP=everyR*everyL;
		int n; 
		w.hint(1,sizeof("���Ŀ¼"),"���Ŀ¼");
		Color(w.dftc);
		for(	i=(page-2)*everyP,n=0;	i<Pkind&&n<everyP;	i++,n++) 
		{
			w.RPlace(3+n%everyR,30+(n/everyR)*45);
			printf("%2d.%s",i,plant[i].name); 
		}
		w.end_setall("����Ŀ¼");
	}
	else
	{
		int P=(page-4)*2;
		const int cdx[2]={w.x+2,w.x+2};
		const int cdy[2]={w.y+4,w.y+w.dy-BIG_dy-4};
		const int y_ofs[2]={BIG_dy+2,-BIG_dy-2};
		int skl;
		int level_demand;
		w.s1_link(s1+btns);
		for(i=0;i<=1;i++)
		{
			level_demand=plant[P+i].demand(true);
		    if(level>=level_demand)
		    {
		    	plant[P+i].card_demon(cdx[i],cdy[i],1-plant[P+i].get("T next_actable"),BIG);
		    	Color(w.dftc);
				Place(cdx[i]+BIG_dx+1,cdy[i]+BIG_dy/2-4);			
				switch(level_demand)
				{
					case Selfdef:	printf("�Զ��忨��");					break;
					case Collect:	if(level_demand==Collect	&& p_user->unlocked[P+i-Cherry]!=0/*�ѽ���*/)
										printf("���Ѻϳɸÿ��ƣ�");
									else
									{
										printf("�ÿ����豻�ϳɣ�");
										print_long_word(_Red,cdx[i]+BIG_dx-8,i*70+BIG_dy/2+6,(char *)"LOCK");
										Color(w.dftc);
									}				
									break;
					default: 		printf("�����ȼ���%d",level_demand);
				}
		    	Place(cdx[i],cdy[i]+y_ofs[i]);printf("���ܣ�");
		    	for(j=0;j<SkillMax;j++)
		    	    if((skl=plant[P+i].skill_avalible[j])!=0)
		    	    {
						Place(cdx[i]+2+6*j,cdy[i]+y_ofs[i]);
						plant[P+i].skill_demon("name",j);
						Place(cdx[i]+3+6*j,cdy[i]+y_ofs[i]);
						plant[P+i].skill_demon("avalible",j);
				    }
	        }
			else
		    {
				Dyearea(cdx[i],cdy[i],BIG_dx,BIG_dy,_Light);
				Color(_Light|White|Light);
				Place((cdx[i]+BIG_dx)/2,cdy[i]+BIG_dy/2-4);printf("%s",plant[P+i].name);
				Color(w.dftc);
				Place(cdx[i]+BIG_dx+1,cdy[i]+(BIG_dy-8)/2-6);printf("�ÿ�����Ҫ%d�����ܽ�����",level_demand);
			} 
		}  
	    w.end_setall("����Ŀ¼");  
    }
	w.page_setall(w.dx-8,5);
	w.do_action();
	BOOK w2=w;
	switch(w.action)
	{
		case 5:
			if(page!=ABSTRACT)
				collection(w2,ABSTRACT,p_user);
			return;
		case 3:
			collection(w2,page-1,p_user);
			break;
		case 4:
			collection(w2,page+1,p_user);
			break;
		case MY_CARDS:
			my_collection(sub_cards_bk,1,p_user);
			goto GOTOHERE_FINISH_MY;				
		case SKILL_DESCRIBE:
			collection(w2,Skillpage,p_user);
            break;
		case SEARCH_MORE:			
			do 
				input.putin_vk('d');
			while(	input.search.d<0  ||  input.search.d>Pkind	);
			input.newtxt(plant[input.search.d].name);
			printf("��1�����ת��");
			Sleep(1000); 
			input.clearboard(_Black);
			collection(w2,4+input.search.d/2,p_user);  
	}
	return;
}	
void activity(PW w,User *p_user)
{
	int evt=-1;
	const int period=86400;
	const int ckin_y=w.y+(w.dy-Stdwidth*3)/2; 
	int left;
	w.newpage();
	int s1[w.set_btnN(2)][4];
	w.s1_link(s1);
	BTN ckin;
	ckin.set(w.x+5,ckin_y,3*Stdheight,3*Stdwidth,s1[0]);
	w.end_setall("�������˵�");
	do
	{
		if((left=period+p_user->get("last_ck")-time(NULL))<=0)
		{
			left=0;
			ckin.judset(  true  );
			ckin.dye(""); 
			Place(w.x+9,ckin_y+15);printf("���ҽ���ÿ��ǩ����");
		}
		else
		{ 
			ckin.judset(  false  );
			ckin.dye("");
			Place(w.x+9,ckin_y+15);printf("ǩ������ʱ��%d s",left);
		} 
		if((evt=Effective(p,w.inner_s1,w.btnN,true,1,Std_flush_period,false))==0&&ckin.jud==true)//1��ˢ��һ�� 
		{
			w.hint(1,sizeof("ǩ���ɹ�����ý�ң�00"),"ǩ���ɹ�����ý�ң�");
			printf("%d",p_user->add("coins",10+rand()%41));
			p_user->check_in();
		}		
	}
	while(evt!=1);
	return;
}

#define Arch_pages ArchMax
#define Std_archiv_dx 15
#define Std_archiv_dy 30


void archiv(BOOK w,User *p_user,int page)
{
	int archieved_demand[ArchMax]={MaxLevel,100,5000,10,Locked_plants-2,10,built_max,1,The_shield-The_potion+1};
	int i;
	int left;
	int max; 
	const int ar_x=w.x+6;
	const int ar_y=w.y+8; 
	const int tf_w=50; 
	w.newpage(Arch_pages,page);
	int s1[w.set_btnN(3)][4];
	w.s1_link(s1);
	w.hint(1,sizeof("�ɾ�չ����"),"�ɾ�չ����");
	Dyearea(ar_x,ar_y,Std_archiv_dx,Std_archiv_dy,_Light);
	switch(page)
	{
		case 1:
			print_big_number(_Yellow|_Light,ar_x+3,ar_y+2,MaxLevel);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ�ֲ���ʦ"); 
			tf.say("");
			tf.say("��������������");
			p_user->archiv[0]=p_user->get("level");
			break;
		case 2:
			draw(wing_img,ar_x+3,ar_y+10,7,12,_White|_Light);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ���û����"); 
			tf.say("");
			tf.say("��������ս������������");
			tf.say("      �ﵽ100��");
			p_user->archiv[1]=p_user->get("tt_miss");
			break;
		case 3:
			draw(sun_img,ar_x+2,ar_y+6,9,17,_Yellow|_Light); 
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ������Դ"); 
			tf.say("");
			tf.say("��������ս�����ۼ�����");
			tf.say("      5000������");
			p_user->archiv[2]=p_user->get("tt_prod");
			break;
		case 4:
			snow_and_spark_pict.set(ar_x+3,ar_y+8);
			snow_and_spark_pict.draw(-1);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ�������Ե"); 
			tf.say("");
			tf.say("��������һ�ֳ�ʼ���Ʋ�����4��ս����");
			tf.say("	  ͬʱ�鵽�������Կ���һ�ţ�");
			tf.say("	  ��������ȡ��ʤ����10�Ρ�");
			p_user->archiv[3]=p_user->get("ice&fire");
			break;
		case 5:
			plant[Cherry+5].card_demon(ar_x+3,ar_y+14,0,SMA);
			plant[Cherry+0].card_demon(ar_x+2,ar_y+4,0,SMA);
			plant[Cherry+2].card_demon(ar_x+4,ar_y+1,0,SMA);
			plant[Cherry+6].card_demon(ar_x+6,ar_y+10,0,SMA);
			plant[Cherry+4].card_demon(ar_x+7,ar_y+5,0,SMA);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ��ɻ�ѧ��"); 
			tf.say("");
			tf.say("�������ϳ�����5�ֿɺϳ�ֲ�");
			p_user->archiv[4]=0; 
			for(i=0;i<Locked_plants;i++)
				if(p_user->unlocked[i]!=0)
					p_user->archiv[4]++;
			break;
		case 6:
			Draw_medals(ar_x+1,ar_y+4,_Green);
			Draw_medals(ar_x+2,ar_y+17,_Purple);
			Draw_medals(ar_x+3,ar_y+10,_Red);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ��Ҳ����"); 
			tf.say("");
			tf.say("����������ʮ����������");
			p_user->archiv[5]=p_user->all_have[The_medel];
			break;
		case 7:
			building_pict.set(ar_x+5,ar_y+7);
			building_pict.draw(-1);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ���ש����"); 
			tf.say("");
			tf.say("��������1000���ש��ô���ʵ���ҡ�");
			p_user->archiv[6]=p_user->get("building");
			break;
		case 8:
			crimson_forest_pict.set(ar_x+2,ar_y+7);
			crimson_forest_pict.draw(-1);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ������׳�"); 
			tf.say("");
			tf.say("���������׳ǰ����¸ջָ����ǡ�");
			p_user->archiv[7]=p_user->battle_temp[5];
			break;
		case 9:
			potion_pict.set(ar_x+4,ar_y+17);
			potion_pict.draw(-1);
			sword_pict.set(ar_x+4,ar_y+2);
			sword_pict.draw(-1);
			boots_pict.set(ar_x+9,ar_y+7);
			boots_pict.draw(-1);
			shield_pict.set(ar_x+2,ar_y+7);
			shield_pict.draw(-1);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("�ɾͣ�ȫ������"); 
			tf.say("");
			tf.say("����������һ�״���װ����");
			p_user->archiv[8]=0;
			for(i=The_potion;i<=The_shield;i++)
				if(p_user->have(i)!=0)
					p_user->archiv[8]++;		
			break;
	}
    Strip(  ar_x+Std_archiv_dx  ,  ar_y  ,p_user->archiv[page-1],archieved_demand[page-1] ,Std_archiv_dy,3,_Red,_Black,w.dftc);
	w.page_setall(w.dx-8,5);
	w.end_setall("����");
	w.do_action();
	switch(w.action)//û��������ť 
	{
		case 0:archiv(w,p_user,page-1);break;
		case 1:archiv(w,p_user,page+1);break;
		case 2:return;		
	}	
	return;
}

#define Shop_pages 3

void user_shop(BOOK w,User *p_user,int page)
{
	int i;
	int scrap_kind;
	const int btns=1;
	const char txt[Shop_pages][sizeof("�ɹ������������£�")]={"�ɹ������������£�","�ɹ�������Ҷ��ޣ��","�ɹ�����ֲ����Ƭ��"};
	w.newpage(Shop_pages,page);
	int s1[w.set_btnN(btns+3)][4];
	w.s1_link(s1);
	w.hint(1,sizeof("��ӭ�����̵꣡"),"��ӭ�����̵꣡");
	BTN goods_btn;
	int price[Shop_pages]={1000,45,60};
	goods_btn.set(     w.x+19  ,w.y+5,  Stdheight  ,  Stdwidth  ,s1[i]);
	GOTOHERE_CONTINUE_BUYING:
	do
	{
		switch(page)
		{
			case 1:
				Draw_medals(w.x+8,w.y+7,_Blue);
				tf.newtxtf(w.x+8,w.y+22,10,50,1,_Light|_White); 
				tf.say("��������"); 
				tf.say("");
				tf.say("��������������֤�������ж����⣬");
				tf.say("	  ����û�б������...");
				break;
			case 2:
				draw(four_leaf_clover_img,w.x+8,w.y+6,9,13,_Green|_Light);
				tf.newtxtf(w.x+8,w.y+22,10,50,1,_Light|_White); 
				tf.say("��Ҷ��ޣ"); 
				tf.say("");
				tf.say("��������²¸����õģ�");
				break; 
			case 3:
				srand(time(NULL)/300);//5min�ű�һ��
				price[3-1]+=rand()%41;
				scrap_kind=rand()%7;
				draw(scrap_img,w.x+10,w.y+6,6,12,_Rand_color(scrap_kind));
				tf.newtxtf(w.x+8,w.y+22,10,50,1,_Light|_White); 
				tf.say("ֲ����Ƭ"); 
				tf.say("");
				tf.say("��������������صĲ�ɫ��Ƭ��");
				tf.say("	  ������ǲ�ɫ��Ŷ����5�������������ɣ�");			
				break;			
		}
		w.page_setall(w.dx-8,5);
		w.end_setall("����");
		w.hint(3,sizeof("���Ľ�ң�0000"),"���Ľ�ң�");
		printf("%d",p_user->get("coins"));
		goods_btn.judset(  p_user->get("coins")>=price[page-1]  );	
		goods_btn.dye("$ ");
		printf("%d",price[page-1]);
		do
			w.do_action();
		while(  w.action==0&&goods_btn.jud==false  );
		switch(w.action)
		{
			case 0:
				p_user->add("coins",-price[page-1]);
				switch(page)
				{
					case 1:p_user->obtain(8,1);
					case 2:p_user->obtain(7,1);
					case 3:p_user->obtain(scrap_kind,1);
				}				
				w.hint(5,sizeof("�ɹ������������£�"),txt[page-1]);
				p_user->record_users_information();
				Sleep(Std_flush_period*5);				
				break;
			case 1:
				user_shop(w,p_user,page-1);
				break;
			case 2:
				user_shop(w,p_user,page+1);
				break;
			default:
				return;
		}	
	}
	while(w.action==0);
	return;
}

#define Self_def_pages 3
#define Define_cards 3
#define Definable_L 2
void self_def(BOOK w,User *p_user,int page)
{
	int i,j;
	const int btns=6; 	
	const int cds=2;
	int py;
	const int def_line=6;
	const char txt[btns][sizeof("���÷�������")]={"ֲ���Զ���","����͸��","�괩ЧӦ","����������","���÷�������","�ֶ��ٿ�"};
	int *opt=p_user->self_ctrl;
	w.newpage(Self_def_pages,page);
	int s1[btns+3][4];
	int s2[pros+3][4];
	BTN def_btn[btns];
	for(i=0;i<btns;i++)
	{
		def_btn[i].set((i%3)*6+def_line,10+(i/3)*112,Stdheight,Stdwidth+4,s1[i]);
		def_btn[i].judset(i==0&&p_user->get("level")<Definable_L?false:true);
	}	
	INP_BAR modify[pros];
	const int txtf_x=w.x+2; 
	const int txtf_y=w.y+6;
	for(i=0;i<pros;i++)
	{
		modify[i].x=txtf_x+1+2*(i%(pros/2));
		modify[i].y=txtf_y+50+40*(i/(pros/2));
		modify[i].lenth=2*log_2(AM)+2;
		modify[i].dftc=Light|White;
	}
	switch(page)
	{
		case 1: 
			w.set_btnN(sizeof(s1)/sizeof(s1[0]));
			w.s1_link(s1);
			tf.newtxtf(w.x+def_line-1,w.y+32,18,86,1,_Light|_White); 
			tf.say("�����ť�ڿ���/�ر�֮���л���");
			tf.say("");
			tf.say("ֲ���Զ��壨Ĭ�Ϲرգ���2�����ϣ�����������ս���������Զ��忨�ơ�");
			tf.say("");
			tf.say("����͸�ӣ�Ĭ�Ϲرգ�����������ս��ǰ���Բ鿴���˿��ơ�");
			tf.say("");
			tf.say("�괩ЧӦ��Ĭ�Ϲرգ�����������250�뼸����ս��������ʹ��δ�����Ŀ��ơ�");
			tf.say("");
			tf.say("������������Ĭ�Ͽ�������������������ҿ���ʹ�������������Լ�����������������");
			tf.say("��Ϸ��������ʾ��Ϊ������Ϸ��Ȥ��������ص���");
			tf.say("");
			tf.say("���÷���������Ĭ�Ͽ�������������������ҿ���ʹ�÷������������Լ��ķ���������������");
			tf.say("��Ϸ��������ʾ��Ϊ������Ϸ��Ȥ��������ص���");
			tf.say("");
			tf.say("�ֶ��ٿأ�Ĭ�Ϲرգ���������ս�����û�����˭��ȭ��ʤ��");
			tf.say("��Ϸ��������ʾ��ֻ�������������˰���������Ҳ�PKʱ��������ģʽ��û���κν�����");
			w.page_setall(w.dx-8,5);
			w.end_setall("�������˵�");
			do
			{
				for(i=0;i<btns;i++)
				{
					def_btn[i].dye(txt[i]);
					Color(w.dftc);
					Place((i%3)*6+def_line+3,10+(i/3)*112+6);printf(opt[i]!=0?"�ѿ���":"�ѹر�");
				}
				do
					i=w.do_action();
				while(i<btns&&def_btn[i].jud==false);
				switch(w.action)
				{
					case btns:
						self_def(w,p_user,page-1);
						break;
					case 7:
						self_def(w,p_user,page+1);
						break;
					case 8:
						break;
					default:
						opt[w.action]=!opt[w.action];
						
				}
			}
			while(w.action<btns);
			p_user->record_users_information();
			break;
		case 2:
		case 3:
			w.set_btnN(sizeof(s2)/sizeof(s2[0]));
			w.s1_link(s2);
			w.page_setall(w.dx-8,5);
			w.end_setall("�������˵�");		
			int *temp=p_user->DIY_temp[page-2];
			int line,lines=(AllSkills+1)/2;
			do
			{
				tf.newtxtf(txtf_x,txtf_y,28,125,1,_Light|_White); 
				tf.say("�Զ���ֲ��");printf("%d������",page-1);
				tf.say("");
				tf.say("�����Ӧ�ڿ�����������ԡ�");
				tf.say("����ǩ�����ữΪ������ʽ��");
				tf.say("ע��������������ֵ��");
				tf.say("���ܱ���б���Ĭ��Ϊ1����������Ϊ1�Σ�");
				line=txtf_x+7;
				for(i=0;i<AllSkills;i++)
				{
					Place(line+i%lines,txtf_y+2+(i/lines)*20);
					printf("%d.%s",i+1,skillname[i+1].name);
				}
				for(i=0;i<pros;i++)
				{
					modify[i].setall("",s2[i]);
					Place(modify[i].x,modify[i].y);
					if(i>=Properties)					printf("%s%s",skillname[temp[i]].name,temp[i]==0?"":roman_n[1/*�Ժ��Ż�*/]);
					else if(i==Properties-2/*��ǩ*/)	tag_show(temp[i],0);
					else if(i==Properties-1/*�ȼ�*/&&temp[i]==Selfdef)	printf("�Զ��壨��Ҫ�޸Ĵ�����");
					else 								printf("%d",temp[i]);
					Color(_Light|_White);
					Place(modify[i].x-1,modify[i].y-2);printf("%s����%d~%d��",tempname[i],tempmin[i],tempmax[i]);
				}
				do 
					j=w.do_action();
				while(j==Properties-1);
				if(j<pros)
				{
					do 
						modify[j].putin_vk('d');
					while(	modify[j].search.d<tempmin[j]  ||  modify[j].search.d>tempmax[j]	);
					temp[j]=modify[j].search.d;
					Sleep(1000); 						
				}
				modify[j].clearboard(_Black);
				w.page_setall(w.dx-8,5);
				w.end_setall("�������˵�");	
			}
			while(j<pros);
			p_user->record_users_information();
			if(j==pros)
				self_def(w,p_user,page-1);
			else if(j==pros+1)
				self_def(w,p_user,page+1);
			break;
	}
	return;
}

#define INVENTORY 0
#define RULE_2 1
#define RECORD 2
#define COLLECTION 3
#define ARCHIV 4
#define ACTIVITY 5
#define SHOP_ 6			//SHOP�Ѷ������ 
#define DEFINE 7
#define BATTLE 8
#define EXIT 9

bool welcome(PW w,User *p_user)
{
	GOTOHERE_WELCOME:
	plant_init(true,p_user,0/*map*/);
	system("color 0f");
	system(size_cmd);
	const int btns=9;
	const int everyR=4;
	const char txt[btns][sizeof("��Ϸ���")]={"�ҵĲֿ�","��Ϸ����","��Ϸ��¼","ֲ��ͼ��","�ҵĳɾ�","ÿ�ջ","��Ϸ�̵�","�Զ���","ս��"}; 
	BTN chs_btn[btns];
	int s1[w.set_btnN(btns+1)][4];
	w.s1_link(s1);
	int i;
	//��ͼ 
	Place(4,10);printf("��ӭ����%s��",p_user->name);
	Strip(4,50,p_user->get("exp"),exp_demand[MaxLevel-1],70,4,p_user->get("color"),_White,w.dftc);
	Place(5,85);printf("����"); 
	print_big_number(p_user->get("color"),4,122,p_user->get("level"));
	//�� 
	const int swx=14;
	const int swy=Max_dy-25;
	const int swdy=7;
	draw(sword_img,       swx,  swy,7,swdy,_White|_Light);
	draw(sword_img+7*swdy,swx+7,swy,1,swdy,_Red);
	draw(sword_img+8*swdy,swx+8,swy,3,swdy,_Blue);
	//����
	{
		const int cstx=4;
		const int csty=30;
		const int cst_H=6;
	 	const int cst_L=16; 
	 	Dyearea(cstx,csty,2,cst_L,_Yellow);
		Dyearea(cstx+2,csty,cst_H-2,cst_L,Light|Yellow|_Light);
		Place(cstx+4,csty+1);printf("���Ľ�ң�%d",p_user->get("coins"));
		Dyerow(cstx+1,csty+cst_L/2-1,2,_Yellow|_Light);		
	} 
	for(i=0;i<btns;i++)
	{ 
		chs_btn[i].judset(true);
		if(i!=btns-1)
			chs_btn[i].set(12+(i%everyR)*(Stdheight+1),6+(i/everyR)*(Stdwidth+2),Stdheight,Stdwidth,s1[i]);
		else
			chs_btn[i].set(26,120,5,20,s1[btns-1]);
		chs_btn[i].dye(txt[i]);
	}
	w.end_setall("�˳���¼");
	w.do_action();
	switch(w.action)
	{		
		case INVENTORY: 
			inventory(p_inventory_bk,p_user,1);
		 	break;
		case RULE_2:
			rules(rules_bk,ABSTRACT);
			break;
		case RECORD:
			record(log_in_pw);
			break;		
		case COLLECTION:
			collection(cards_bk,1,p_user);
			break;
		case ARCHIV:
			archiv(cards_bk,p_user,1);
			break;
		case ACTIVITY:
			activity(log_in_pw,p_user);
			break;
		case SHOP_:
			user_shop(p_choose_card_bk,p_user,1);
			break;	
		case DEFINE:
			self_def(rules_bk,p_user,1);
			break;
		case BATTLE:
			gamemode(p_user);
			break;
		case EXIT:
			PW w2=log_in_pw;
			w2.newpage();
			BTN ex_btn[4];
			int s2[w2.set_btnN(4+1)][4];
			int ex_x;
			int ex_y;
			w2.s1_link(s2);
			w2.hint(1,sizeof("ѡ���˳���ʽ��"),"ѡ���˳���ʽ��");
			w2.hint(3,sizeof("�����ѡ���˱������룬�´��ڵ�¼/ע��������ֱ�ӵ�¼��"),"�����ѡ���˱������룬�´��ڵ�¼/ע��������ֱ�ӵ�¼��");	
			int len=sizeof("���������룬�л��˺�");
			const char w2_txt[4][len]={"�������룬�л��˺�","���������룬�л��˺�","�������룬�˳���Ϸ","���������룬�˳���Ϸ"}; 
			for(i=0;i<4;i++)
			{
				ex_x=w2.x+9+(i/2)*5;
				ex_y=w2.y+15+(i%2)*35;
				ex_btn[i].judset(  true  );
				ex_btn[i].set(  ex_x  ,  ex_y  ,  Stdheight  ,  len+4  ,s2[i]);
				ex_btn[i].dye("");Place(ex_x+1  ,  ex_y +2  );printf("%s",w2_txt[i]);
				w2.end_setall("�ص���Ϸ");
			}
			w2.do_action();
			p_user->log_off(  w2.action%2==0  );
			if(w2.action==4)
				goto GOTOHERE_WELCOME;
			else if(w2.action<2)
				return true;
			else
				return false; 
	}
	goto GOTOHERE_WELCOME;
}
int main()
{
	system(size_cmd);
	plant_init(true,NULL,0/*map*/);
	if(first_come_judge())
		for_freshman();
	//record_init();
	User user;
	PW w={1,1,Max_dx,Max_dy,_Black|White|Light,false};
	srand((int)time(NULL));	
	system(size_cmd);
	do 
	if(surface(log_in_pw,&user,false)==false)
	    return 0;
	while(welcome(w,&user));
	return 0;
}
