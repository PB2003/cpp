
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
	char long_s[LongN]="    《植物大战植物》是以《植物大战僵尸》、《植物大战僵尸 2》、《植物大战僵尸Online》为角色原型创作的、"
	"基于DEV C++5.2.0.3开发出来的、在DOS 界面下的C++ 语言模拟卡牌游戏。游戏基本规则简单明了，详细规则略显复杂。"
	"游戏操作基本用模拟的“按钮”完成，界面友好、系统稳定性好、人机交互方便。能激发缺乏Windows编程基础和不会使用graphics.h的人"
	"使用C++语言来编写简易的可视化小游戏，提升正在学习C++ 语言的学员的编程兴趣。";
	w.newpage();
	w.hint(1,sizeof("本游戏发行于2020年12月30日，为第七个版本"),"本游戏发行于2020年12月30日，为第七个版本");
	w.hint(3,sizeof("版权所有：中国科学技术大学 化学与材料科学学院 PB20030773彭子骏"),"版权所有：中国科学技术大学 化学与材料科学学院 PB20030773彭子骏"); 
	print_long(w.x+5,w.y+2,w.dy-4,long_s);
	w.end_setall("返回主菜单"); 
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
	const char txt[parts][sizeof("游戏简介")]={"卡牌","战斗","用户"};
	w.newpage(Rulepages,page);
	int s1[w.set_btnN(parts+3)][4];
	w.s1_link(s1);
	if(page==ABSTRACT)
	{
		Color(_White|_Light|Yellow|Light);
		w.hint(3,sizeof("规则目录"),"规则目录");
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
				w.RPlace(3,(w.dy-sizeof("卡牌"))/2);printf("卡牌"); 
				plant[0].card_demon(w.x+6,w.y+w.dy-BIG_dy-4,1-plant[0].get("T next_actable"),BIG);
				break;
			case P_CARDS+1:
				plant[0].card_demon(w.x+6,w.y+w.dy-BIG_dy-4,1-plant[0].get("T next_actable"),BIG);
				break;
		
			case P_BATTLE:
				w.RPlace(3,(w.dy-sizeof("战斗"))/2);printf("战斗"); 
				break;

			case P_USER:
				w.RPlace(3,(w.dy-sizeof("用户"))/2);printf("用户"); 
				break;
		}
		p_l=rule[page-2];
		Color(w.dftc);
		for(i=0;(*p_l)[0]!='#'/*结束号*/;i++)
		{
			w.RPlace(line++,2);printf("%s",p_l++);
		}
		const char *skill_kind;
		int start_i;
		int end_i;
		if(page==P_SKILLS||page==P_SKILLS+1)
		{
			start_i=(page==P_SKILLS?	1/*不是0*/			:	Skill_of_first_page);
			end_i=	(page==P_SKILLS?	Skill_of_first_page	:	AllSkills+1);
			for(i=start_i;i<end_i;i++)
			{
				w.RPlace(line++,2);
				switch(skillname[i].act_kind)
				{
					case Passive	:skill_kind="被动技";break;
					case Passive_S	:skill_kind="临死技";break;
					case Always 	:skill_kind="背景技";break;
					case Adjunct	:skill_kind="附加技";break;
					default			:skill_kind="主动技";
				}
				printf("%d.%s\t[%s]（最高等级%s，持续%d回合）：%s",
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
	w.end_setall("返回主菜单");
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
	const char txt[btns-2][sizeof("登录")]={"登录","注册","上次"};
	const char in_txt[2][sizeof("请输入密码（先输用户名）...")]={"请输入用户名...","请输入密码（先输用户名）..."};
	bool put_username=false; 
	bool put_pswd=false; 
	bool right_put_username=false;
	bool right_put_pswd=false;	
	const int in_x[2]={w.x+7,w.x+13};
	const int in_y=w.y+4;
	INP_BAR in[2]={{  in_x[0]  ,  in_y  ,  sizeof("请输入密码（先输用户名）...")+6  ,  White|Light  }, 
				   {  in_x[1]  ,  in_y  ,  sizeof("请输入密码（先输用户名）...")+6  ,  White|Light  }};
	for(i=0;i<btns-2;i++)
		in_btn[i].set(  w.x+6+6*i ,  w.y+w.dy-Stdwidth-4  ,  Stdheight  ,  Stdwidth  ,s1[2+i]);
	in_btn[2].judset(  last_user(p_user)  );//保存的账号 
    while(1)
	{
		w.newpage();
		w.hint(1,sizeof("请点击左侧方框输入用户名和密码，忽略空格。用户名不存在时，默认为注册状态。"),"请点击左侧方框输入用户名和密码，忽略空格。用户名不存在时，默认为注册状态。");
		w.hint(16,sizeof("如果上次保存了密码，可以直接登录"),"如果上次保存了密码，可以直接登录"); 
		w.hint(3,sizeof("注意，用户名和密码只能为除%c、%c、%c、%c、\\n、\\0以外的ASCII字符。"),"注意，用户名和密码只能为");
		printf("除%c、%c、%c、%c、\\n、\\0以外的ASCII字符。",MARK,INTERVAL,ADD,NO);	
		for(i=0;i<2;i++)
    		in[i].setall(	in[i].search.s[0]=='\0'?	in_txt[i]:(const char*)in[i].search.s	,s1[i]);
		Color(w.dftc);w.RPlace(6*3+3,w.dy-Stdwidth-4); 
		if(  in_btn[2].jud  )
			printf("用户：%s",p_user->name);
		else
		    printf("上次未保存");
		w.end_setall("返回主菜单");
		
		in_btn[0].judset(  right_put_username&&right_put_pswd  );//登录 
		in_btn[1].judset(  put_username&&!right_put_username&&put_pswd  );//注册
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
					in[USERNAME].newtxt("非法输入！"); 
					Sleep(500);
				}
				put_username=true;
				Color(_Light|_White|Green);Place(in_x[0]+1,in_y);
				if(right_put_username=find_user(in[USERNAME].search.s))  //有同名用户 
				 	printf("用户名正确！");
				else
					printf("新用户！");
				Sleep(500);
				in[USERNAME].clearboard(_Blue);
				break;
			case PSWD:
				while(in[PSWD].putin_vk('s')==false)
				{
					in[PSWD].newtxt("非法输入！"); 
					Sleep(500);
				}		
				Place(in_x[1]+1,in_y);
				if(right_put_username)
					if(find_pswd(in[USERNAME].search.s,in[PSWD].search.s))					
					{ 
						Color(_Light|_White|Green);
						printf("密码正确！");
						right_put_pswd=true;
					} 
					else
					{
						Color(_Light|_White|Red);
						printf("密码错误！");
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
	const char *operate_ways="请用鼠标右键单击或按下↓或ctrl键模拟鼠标单击。对于左右翻页按钮，←→键也有效果";
	const char *about_buttons="注意：所有绿色按钮为可点击状态，青色按钮为不可点击状态";
	const char txt[btns][sizeof("游戏简介")]={"游戏简介","游戏规则","新手导引","退出游戏"}; 
	BTN menu_btn[btns];
	int s1[w.set_btnN(btns+1)][4];
	w.s1_link(s1);
	while(logged_in==false)
	{
		system("color 1e");
		system(size_cmd);
		Place(4,(Max_dy-sizeof("植物大战植物 v1.0.0"))/2);printf(title); 	
		w.newpage();
		for(i=0;i<btns;i++)
		{
	    	menu_btn[i].judset(  true  );
			menu_btn[i].set(  w.x+6+(Stdheight+4)*(i/2)  ,  w.y+(i%2)*(Stdwidth+space)+space  ,  Stdheight  ,  Stdwidth  ,s1[i]);
			menu_btn[i].dye(txt[i]);
    	}
		w.end_setall("登录/注册");
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
		w.hint(1,sizeof("有机实验室"),"有机实验室");
		w.hint(3,sizeof("本实验室免费帮助大家加工原材料，点击左侧按钮进行合成！"),"本实验室免费帮助大家加工原材料，点击左侧按钮进行合成！");
		w.hint(5,sizeof("通过合成可以获得稀有植物和成就哦！"),"通过合成可以获得稀有植物和成就哦！");
		tf.newtxtf(w.x+9,w.y+80,14,54,1,_Light|_White); 
		tf.say("合成配方："); 
		tf.say("");
		tf.say("七彩浆果：7种植物碎片*各1");
		tf.say("樱桃炸弹：红色碎片*4+七彩浆果*1+世界树之叶*1");
		tf.say("充能柚子：橙色碎片*4+七彩浆果*1+世界树之叶*1");
		tf.say("周瑜蕉弩：黄色碎片*4+七彩浆果*1+世界树之叶*1");
		tf.say("豌豆荚  ：绿色碎片*4+七彩浆果*1+世界树之叶*1");
		tf.say("玄冰水仙：青色碎片*4+七彩浆果*1+世界树之叶*1");
		tf.say("月光草  ：蓝色碎片*4+七彩浆果*1+世界树之叶*1");
		tf.say("紫百合  ：紫色碎片*4+七彩浆果*1+世界树之叶*1");
		tf.say("世界树之花：七彩浆果*1+世界树之叶*3");	
	}
	else
	{
		w.hint(1,sizeof("大雾实验室"),"大雾实验室");
		int built=p_user->building;
		if(built<built_max)
		{
			w.set_btnN(elem(s2));
			w.s1_link(s2);
			w.hint(3,sizeof("上学期有人把这里炸了，现在还在修。要不你帮个忙？"),"上学期有人把这里炸了，现在还在修。要不你帮个忙？");
			Strip(w.x+7,w.y+20,built,built_max,100,4,_Red,_Black,w.dftc);
			w.hint(8,sizeof("施工进度"),"施工进度");
			w.page_setall(w.dx-8,5);
			w.end_setall("返回");
			if(w.do_action()==2)
				return;
			else
				return;
		}
		w.hint(3,sizeof("本实验室收费帮助大家制造装备，你还不知道干了什么就造完了，很快啊。"),"本实验室收费帮助大家制造装备，你还不知道干了什么就造完了，很快啊。");
		tf.newtxtf(w.x+9,w.y+70,14,64,1,_Light|_White); 
		tf.say("合成配方："); 
		tf.say("");
		tf.say("炎城地图（$200）：红色碎片*2+绿宝石*1+蓝冰*1+末影珍珠*1");
		tf.say("不可合成的物品：我还没想好");
		tf.say("大雾迷药（$75）：蓝冰*1+绿宝石*1+七彩浆果*1");
		tf.say("腾挪幻靴（$75）：蓝冰*2+末影珍珠*1+世界树之花*1");
		tf.say("玄铁重剑（$150）：蓝冰*1+绿宝石*1+下界合金*2");
		tf.say("金刚护甲（$150）：下界合金*3+末影珍珠*1+世界树之花*1");

	}
	for(i=0;i<btns;i++)
		syn_btn[i].set(w.x+9+(i/3)*6,w.y+10+(i%3)*20,Stdheight,Stdwidth,s1[i]);
	w.page_setall(w.dx-8,5);
	w.end_setall("返回");
	bool 		con=true;
	const char 	txt1[2][btns_1][sizeof("世界树之花")]=
	{
		{"七彩浆果","樱桃炸弹","充能柚子","周瑜蕉弩","豌豆荚","玄冰水仙","月光草","紫百合","世界树之花"},
		{"炎城地图","不可合成","大雾迷药","腾挪幻靴","玄铁重剑","金刚护甲"}
	};
	const char  (*txt)[sizeof("世界树之花")]=txt1[page-1];
	do
	{	
		int money=p_user->get("coins");
		for(i=0;i<btns;i++)
		{
			if(page==1)
				switch(i)
				{
					case 0://七彩浆果 
						for(j=0;j<colors;j++) 
							con=(con&&(ingred[j]>0));
						break;
					case 8://世界树之花
					 	con=(ingred[The_fruit]>0	&&	ingred[The_leaf]>=3	);
					 	break;
					default:
						con=(ingred[i-1]>=4	&&	ingred[The_fruit]>0	&&	ingred[The_leaf]>=1	);
						if(p_user->unlocked[i-1]!=0)
						{ 
							Color(w.dftc); 
							Place(w.x+12+(i/3)*6,w.y+14+(i%3)*20);printf("已获得"); 
						} 
				}
			else
				switch(i)
				{
					case 0://炎城地图 
						con=(ingred[0]>=2	&&	ingred[The_emerald]>=1	&&	ingred[The_ice]>=1	&&	ingred[The_perl]>=1	&&money>=200);
						break;
					case 1://不可合成
						con=false;
						break;
					case 2://大雾迷药 
						con=(ingred[The_ice]>=1	&&	ingred[The_emerald]>=1	&&	ingred[The_fruit]>=1	&&money>=75);
						break;
					case 3://腾挪幻靴
						con=(ingred[The_ice]>=2	&&	ingred[The_perl]>=1		&&	ingred[The_flower]>=1	&&money>=75);
						break;
					case 4://玄铁重剑
						con=(ingred[The_ice]>=1	&&	ingred[The_emerald]>=1	&&	ingred[The_ingot]>=2	&&money>=150);
						break;
					case 5://金刚护甲
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
				case 0://七彩浆果 
					for(i=0;i<colors;i++) 
						p_user->obtain(i,-1);
					p_user->obtain(The_fruit,1);
					w.newline(5,sizeof("一个七彩浆果已放入您的仓库"),"一个七彩浆果已放入您的仓库");
					break;
				case 8://世界树之花
					p_user->obtain(The_fruit,-1);
					p_user->obtain(The_leaf,-3);
					p_user->obtain(The_flower,1);
					w.newline(5,sizeof("一个世界树之花已放入您的仓库"),"一个世界树之花已放入您的仓库");
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
					p_user->unlock(w.action-1);//解锁植物
					w.newline(5,sizeof("成功解锁该卡牌"),"成功解锁该卡牌");
			}
		else
			switch(w.action)
			{
				case 0://炎城地图 
					p_user->obtain(0,-2);
					p_user->obtain(The_emerald,-1);
					p_user->obtain(The_ice,-1);
					p_user->obtain(The_perl,-1);
					p_user->obtain(The_map,1);
					p_user->add("coins",-200);
					w.newline(5,sizeof("一个炎城地图已放入您的仓库"),"一个炎城地图已放入您的仓库");
					break;
				case 2://大雾迷药 
					p_user->obtain(The_fruit,-1);
					p_user->obtain(The_ice,-1);
					p_user->obtain(The_emerald,-1);
					p_user->obtain(The_potion,1);
					p_user->add("coins",-75);
					w.newline(5,sizeof("一个大雾迷药已放入您的仓库"),"一个大雾迷药已放入您的仓库");
				 	break;
				case 3://腾挪幻靴 
					p_user->obtain(The_flower,-1);
					p_user->obtain(The_ice,-2);
					p_user->obtain(The_perl,-1);
					p_user->obtain(The_boots,1);
					p_user->add("coins",-75);
					w.newline(5,sizeof("一个腾挪幻靴已放入您的仓库"),"一个腾挪幻靴已放入您的仓库");
				 	break;
				case 4://玄铁重剑 
					p_user->obtain(The_ice,-1);
					p_user->obtain(The_emerald,-1);
					p_user->obtain(The_ingot,-2);
					p_user->obtain(The_sword,1);
					p_user->add("coins",-150);
					w.newline(5,sizeof("一个玄铁重剑已放入您的仓库"),"一个玄铁重剑已放入您的仓库");
				 	break;
				case 5://金刚护甲 
					p_user->obtain(The_ingot,-3);
					p_user->obtain(The_perl,-1);
					p_user->obtain(The_flower,-1);
					p_user->obtain(The_shield,1);
					p_user->add("coins",-150);
					w.newline(5,sizeof("一个金刚护甲已放入您的仓库"),"一个金刚护甲已放入您的仓库");
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
		w.hint(1,sizeof("我的仓库"),"我的仓库");
		Dyeslots(frame_x,frame_y,frame_size,frame_size*2,everyR,everyL,_Cyan);
		syn_btn.dye("合成物品"); 
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
				++n;//计数器 
			}
		w.page_setall(w.dx-7,5);
		w.end_setall("返回"); 
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
	if(!only)//广义 
		for(i=0;i<Pkind;i++)
			switch(plant[i].demand(true)) 
			{
				case Selfdef:	if(p_user->self_ctrl[adapt_selfdef]!=0)	++have;		break;
				case Collect:	if(p_user->unlocked[i-Cherry]!=0)		++have;		break;
				default:if(plant[i].demand(true)<=level)				++have;
			}
	else//狭义 
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
					(dem==Collect	&& p_user->unlocked[k-Cherry]!=0/*已解锁*/)
				)
				plant[k].card_demon(w.x+i*(SMA_dx+1)+2,w.y+j*(SMA_dy+2)+4,1-plant[k].get("T next_actable"),SMA); 
			else
			{
				Dyearea(w.x+i*(SMA_dx+1)+2,       w.y+j*(SMA_dy+2)+4,       SMA_dx,SMA_dy,_Light);
				Place(w.x+i*(  SMA_dx+1)+2+SMA_dx/2,w.y+j*(SMA_dy+2)+4+(SMA_dy-sizeof("???"))/2);printf("???");
			}
		}
	GOTOHERE_BREAK_OUT:
	w.end_setall("返回图鉴");  
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
	INP_BAR input={search_x ,  search_y ,sizeof("搜索卡牌序号...")+6,White|Light };//输入栏 
	int s1[w.set_btnN(btns+3)][4];
	w.s1_link(s1);
	if(page==ABSTRACT)
	{ 
		Color(_White|_Light|Yellow|Light);
		w.hint(3,sizeof("植物图鉴"),"植物图鉴");
		BTN a_btn[btns-1];//还有一个INPUT的;	    
		for(i=0;i<btns-1;i++)
	    	a_btn[i].judset(  true  );
	    a_btn[0].set(  w.x+6  ,  w.y+6  ,  Stdheight ,  Stdwidth  ,s1[0]);
		a_btn[1].set(  w.x+12 ,  w.y+6  ,  Stdheight , Stdwidth   ,s1[1]);
		a_btn[0].dye("我的卡牌");
    	a_btn[1].dye("快捷目录");
    	input.setall(	"搜索卡牌序号...",s1[2]);
		int have=have_unlocked(p_user,false); 
    	int   color=have>=30?(have>=50?(have>=70?_Cyan|_Light:_Yellow|_Light):_White|_Light):_Yellow;
    	const char *dan=have>=30?(have>=50?(have>=70?"钻石":"黄金"):"白银"):"青铜";
    	Color(w.dftc);Place(cpx-1,cpy-3);printf("卡牌收集·荣誉奖杯");
    	w.hint(9,sizeof("温馨提示：先在快捷目录中查到卡牌序号再进行搜素，会更加方便！"),"温馨提示：先在快捷目录中查到卡牌序号再进行搜素，会更加方便！");
    	//奖杯图案
		draw(cup_img,cpx,cpy,9,11,color);
		//收集度 
    	Strip(cpx+10,cpy,have,Pkind,11,3,_Green,_Black,w.dftc);
    	Place(cpx+11,cpy+4);printf("%s",dan);
    	w.end_setall("返回主菜单"); 
	}
	else if(page==2||page==3)
	{
		const int everyR=22;
		const int everyL=2;
		const int everyP=everyR*everyL;
		int n; 
		w.hint(1,sizeof("快捷目录"),"快捷目录");
		Color(w.dftc);
		for(	i=(page-2)*everyP,n=0;	i<Pkind&&n<everyP;	i++,n++) 
		{
			w.RPlace(3+n%everyR,30+(n/everyR)*45);
			printf("%2d.%s",i,plant[i].name); 
		}
		w.end_setall("返回目录");
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
					case Selfdef:	printf("自定义卡牌");					break;
					case Collect:	if(level_demand==Collect	&& p_user->unlocked[P+i-Cherry]!=0/*已解锁*/)
										printf("你已合成该卡牌！");
									else
									{
										printf("该卡牌需被合成！");
										print_long_word(_Red,cdx[i]+BIG_dx-8,i*70+BIG_dy/2+6,(char *)"LOCK");
										Color(w.dftc);
									}				
									break;
					default: 		printf("解锁等级：%d",level_demand);
				}
		    	Place(cdx[i],cdy[i]+y_ofs[i]);printf("技能：");
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
				Place(cdx[i]+BIG_dx+1,cdy[i]+(BIG_dy-8)/2-6);printf("该卡牌需要%d级才能解锁！",level_demand);
			} 
		}  
	    w.end_setall("返回目录");  
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
			printf("（1秒后跳转）");
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
	w.end_setall("返回主菜单");
	do
	{
		if((left=period+p_user->get("last_ck")-time(NULL))<=0)
		{
			left=0;
			ckin.judset(  true  );
			ckin.dye(""); 
			Place(w.x+9,ckin_y+15);printf("点我进行每日签到！");
		}
		else
		{ 
			ckin.judset(  false  );
			ckin.dye("");
			Place(w.x+9,ckin_y+15);printf("签到倒计时：%d s",left);
		} 
		if((evt=Effective(p,w.inner_s1,w.btnN,true,1,Std_flush_period,false))==0&&ckin.jud==true)//1秒刷新一次 
		{
			w.hint(1,sizeof("签到成功！获得金币：00"),"签到成功！获得金币：");
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
	w.hint(1,sizeof("成就展览馆"),"成就展览馆");
	Dyearea(ar_x,ar_y,Std_archiv_dx,Std_archiv_dy,_Light);
	switch(page)
	{
		case 1:
			print_big_number(_Yellow|_Light,ar_x+3,ar_y+2,MaxLevel);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("成就：植物大师"); 
			tf.say("");
			tf.say("描述：升到满级");
			p_user->archiv[0]=p_user->get("level");
			break;
		case 2:
			draw(wing_img,ar_x+3,ar_y+10,7,12,_White|_Light);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("成就：我没大意"); 
			tf.say("");
			tf.say("描述：在战斗中闪避总数");
			tf.say("      达到100次");
			p_user->archiv[1]=p_user->get("tt_miss");
			break;
		case 3:
			draw(sun_img,ar_x+2,ar_y+6,9,17,_Yellow|_Light); 
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("成就：清洁能源"); 
			tf.say("");
			tf.say("描述：在战斗中累计生产");
			tf.say("      5000点阳光");
			p_user->archiv[2]=p_user->get("tt_prod");
			break;
		case 4:
			snow_and_spark_pict.set(ar_x+3,ar_y+8);
			snow_and_spark_pict.draw(-1);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("成就：冰火奇缘"); 
			tf.say("");
			tf.say("描述：在一局初始卡牌不超过4的战斗中");
			tf.say("	  同时抽到冰火属性卡各一张，");
			tf.say("	  并在最终取得胜利，10次。");
			p_user->archiv[3]=p_user->get("ice&fire");
			break;
		case 5:
			plant[Cherry+5].card_demon(ar_x+3,ar_y+14,0,SMA);
			plant[Cherry+0].card_demon(ar_x+2,ar_y+4,0,SMA);
			plant[Cherry+2].card_demon(ar_x+4,ar_y+1,0,SMA);
			plant[Cherry+6].card_demon(ar_x+6,ar_y+10,0,SMA);
			plant[Cherry+4].card_demon(ar_x+7,ar_y+5,0,SMA);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("成就：成环学家"); 
			tf.say("");
			tf.say("描述：合成至少5种可合成植物。");
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
			tf.say("成就：家财万贯"); 
			tf.say("");
			tf.say("描述：购买十个土豪奖章");
			p_user->archiv[5]=p_user->all_have[The_medel];
			break;
		case 7:
			building_pict.set(ar_x+5,ar_y+7);
			building_pict.draw(-1);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("成就：红砖并进"); 
			tf.say("");
			tf.say("描述：用1000块红砖搭好大雾实验室。");
			p_user->archiv[6]=p_user->get("building");
			break;
		case 8:
			crimson_forest_pict.set(ar_x+2,ar_y+7);
			crimson_forest_pict.draw(-1);
			tf.newtxtf(ar_x,ar_y+Std_archiv_dy+2,10,tf_w,1,_Light|_White); 
			tf.say("成就：幻灭炎城"); 
			tf.say("");
			tf.say("描述：在炎城帮助陈刚恢复心智。");
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
			tf.say("成就：全副披挂"); 
			tf.say("");
			tf.say("描述：集齐一套大雾装备。");
			p_user->archiv[8]=0;
			for(i=The_potion;i<=The_shield;i++)
				if(p_user->have(i)!=0)
					p_user->archiv[8]++;		
			break;
	}
    Strip(  ar_x+Std_archiv_dx  ,  ar_y  ,p_user->archiv[page-1],archieved_demand[page-1] ,Std_archiv_dy,3,_Red,_Black,w.dftc);
	w.page_setall(w.dx-8,5);
	w.end_setall("返回");
	w.do_action();
	switch(w.action)//没有其他按钮 
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
	const char txt[Shop_pages][sizeof("成功购买土豪奖章！")]={"成功购买土豪奖章！","成功购买四叶苜蓿！","成功购买植物碎片！"};
	w.newpage(Shop_pages,page);
	int s1[w.set_btnN(btns+3)][4];
	w.s1_link(s1);
	w.hint(1,sizeof("欢迎来到商店！"),"欢迎来到商店！");
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
				tf.say("土豪奖章"); 
				tf.say("");
				tf.say("描述：除了用于证明你金币有多以外，");
				tf.say("	  好像没有别的意义...");
				break;
			case 2:
				draw(four_leaf_clover_img,w.x+8,w.y+6,9,13,_Green|_Light);
				tf.newtxtf(w.x+8,w.y+22,10,50,1,_Light|_White); 
				tf.say("四叶苜蓿"); 
				tf.say("");
				tf.say("描述：你猜猜干嘛用的？");
				break; 
			case 3:
				srand(time(NULL)/300);//5min才变一次
				price[3-1]+=rand()%41;
				scrap_kind=rand()%7;
				draw(scrap_img,w.x+10,w.y+6,6,12,_Rand_color(scrap_kind));
				tf.newtxtf(w.x+8,w.y+22,10,50,1,_Light|_White); 
				tf.say("植物碎片"); 
				tf.say("");
				tf.say("描述：随机又神秘的彩色碎片！");
				tf.say("	  （真的是彩色的哦，过5分钟再来看看吧）");			
				break;			
		}
		w.page_setall(w.dx-8,5);
		w.end_setall("返回");
		w.hint(3,sizeof("您的金币：0000"),"您的金币：");
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
				w.hint(5,sizeof("成功购买土豪奖章！"),txt[page-1]);
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
	const char txt[btns][sizeof("启用非主动技")]={"植物自定义","开局透视","钻穿效应","启用主动技","启用非主动技","手动操控"};
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
			tf.say("点击按钮在开启/关闭之间切换。");
			tf.say("");
			tf.say("植物自定义（默认关闭，需2级以上）：开启后在战斗中启用自定义卡牌。");
			tf.say("");
			tf.say("开局透视（默认关闭）：开启后在战斗前可以查看他人卡牌。");
			tf.say("");
			tf.say("钻穿效应（默认关闭）：开启后有250‰几率在战斗中允许使用未解锁的卡牌。");
			tf.say("");
			tf.say("启用主动技（默认开启）：开启后其他玩家可以使用主动技。（自己的主动技常开。）");
			tf.say("游戏开发者提示：为增加游戏乐趣，不建议关掉。");
			tf.say("");
			tf.say("启用非主动技（默认开启）：开启后其他玩家可以使用非主动技。（自己的非主动技常开。）");
			tf.say("游戏开发者提示：为增加游戏乐趣，不建议关掉。");
			tf.say("");
			tf.say("手动操控（默认关闭）：开启后战斗由用户决定谁猜拳获胜。");
			tf.say("游戏开发者提示：只建议在两个真人扮演两个玩家并PK时开启。此模式下没有任何奖励。");
			w.page_setall(w.dx-8,5);
			w.end_setall("返回主菜单");
			do
			{
				for(i=0;i<btns;i++)
				{
					def_btn[i].dye(txt[i]);
					Color(w.dftc);
					Place((i%3)*6+def_line+3,10+(i/3)*112+6);printf(opt[i]!=0?"已开启":"已关闭");
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
			w.end_setall("返回主菜单");		
			int *temp=p_user->DIY_temp[page-2];
			int line,lines=(AllSkills+1)/2;
			do
			{
				tf.newtxtf(txtf_x,txtf_y,28,125,1,_Light|_White); 
				tf.say("自定义植物");printf("%d·属性",page-1);
				tf.say("");
				tf.say("点击对应黑框输入各项属性。");
				tf.say("（标签参数会化为二进制式）");
				tf.say("注意属性有上下限值。");
				tf.say("技能编号列表（均默认为1级，主动技为1次）");
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
					if(i>=Properties)					printf("%s%s",skillname[temp[i]].name,temp[i]==0?"":roman_n[1/*以后优化*/]);
					else if(i==Properties-2/*标签*/)	tag_show(temp[i],0);
					else if(i==Properties-1/*等级*/&&temp[i]==Selfdef)	printf("自定义（不要修改此条）");
					else 								printf("%d",temp[i]);
					Color(_Light|_White);
					Place(modify[i].x-1,modify[i].y-2);printf("%s：（%d~%d）",tempname[i],tempmin[i],tempmax[i]);
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
				w.end_setall("返回主菜单");	
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
#define SHOP_ 6			//SHOP已定义过了 
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
	const char txt[btns][sizeof("游戏简介")]={"我的仓库","游戏规则","游戏纪录","植物图鉴","我的成就","每日活动","游戏商店","自定义","战斗"}; 
	BTN chs_btn[btns];
	int s1[w.set_btnN(btns+1)][4];
	w.s1_link(s1);
	int i;
	//画图 
	Place(4,10);printf("欢迎您，%s！",p_user->name);
	Strip(4,50,p_user->get("exp"),exp_demand[MaxLevel-1],70,4,p_user->get("color"),_White,w.dftc);
	Place(5,85);printf("经验"); 
	print_big_number(p_user->get("color"),4,122,p_user->get("level"));
	//剑 
	const int swx=14;
	const int swy=Max_dy-25;
	const int swdy=7;
	draw(sword_img,       swx,  swy,7,swdy,_White|_Light);
	draw(sword_img+7*swdy,swx+7,swy,1,swdy,_Red);
	draw(sword_img+8*swdy,swx+8,swy,3,swdy,_Blue);
	//宝箱
	{
		const int cstx=4;
		const int csty=30;
		const int cst_H=6;
	 	const int cst_L=16; 
	 	Dyearea(cstx,csty,2,cst_L,_Yellow);
		Dyearea(cstx+2,csty,cst_H-2,cst_L,Light|Yellow|_Light);
		Place(cstx+4,csty+1);printf("您的金币：%d",p_user->get("coins"));
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
	w.end_setall("退出登录");
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
			w2.hint(1,sizeof("选择退出方式："),"选择退出方式：");
			w2.hint(3,sizeof("如果您选择了保存密码，下次在登录/注册界面可以直接登录。"),"如果您选择了保存密码，下次在登录/注册界面可以直接登录。");	
			int len=sizeof("不保存密码，切换账号");
			const char w2_txt[4][len]={"保存密码，切换账号","不保存密码，切换账号","保存密码，退出游戏","不保存密码，退出游戏"}; 
			for(i=0;i<4;i++)
			{
				ex_x=w2.x+9+(i/2)*5;
				ex_y=w2.y+15+(i%2)*35;
				ex_btn[i].judset(  true  );
				ex_btn[i].set(  ex_x  ,  ex_y  ,  Stdheight  ,  len+4  ,s2[i]);
				ex_btn[i].dye("");Place(ex_x+1  ,  ex_y +2  );printf("%s",w2_txt[i]);
				w2.end_setall("回到游戏");
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
