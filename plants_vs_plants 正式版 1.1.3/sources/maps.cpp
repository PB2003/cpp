
#define _MAPS_CPP_

#ifndef _PLAYERS_CPP_ 
    #define _PLAYERS_CPP_
    #include "players.cpp"
#endif

#ifndef _RECORD_CPP_ 
    #define _RECORD_CPP_
    #include "record.cpp"
#endif

void maps(User *p_user)
{
	int i,map=0;
	const int places=Maps;
	bool jud;
	PW w=map_pw;
	w.newpage();
	int plcx[places],plcy[places];
	int tf_x=w.x+1;
	int tf_y=w.x+63;
	int s1[w.set_btnN(places+1)][4];
	w.s1_link(s1);
	BTN btn[places];
	PICT plc[places]=		{plane_pict	,tundra_pict,badland_pict,mansion_pict	,crimson_forest_pict,end_city_pict	};
	const int L_d[places]=	{1			,1			,2			,3				,4					,5				};
	for(i=0;i<places;i++)
	{
		jud=(p_user->get("level")>=L_d[i]);
		plcx[i]=w.x+2+(i%2)*19;
		plcy[i]=w.y+1+(i/2)*17;
		plc[i].set(	plcx[i]	,	plcy[i]	);
		plc[i].make_b(&btn[i],s1[i],jud);
		plc[i].draw(jud?-1:_Black);
		if(i==2&&p_user->building>=1000)
		{
			building_pict.set(	plcx[i]	,	plcy[i]	);	
			building_pict.draw(-1);
		}
	}	 
	print_long_word(_White,w.x+12,w.y+6,(char *)"MAP");
	tf.newtxtf(tf_x,tf_y,26,66,1,_White|_Light);
	tf.say("点击地图图标选择你要去的地方。");
	tf.say("");
	tf.say("稀树草原：1级解锁；特殊掉落物：无"); 
	tf.say("一片详和中暗藏杀机。");
	tf.say("");
	tf.say("积雪冻原：1级解锁；特殊掉落物：蓝冰");
	tf.say("冰冻，冰冻，冰冻！");  
	tf.say("");
	tf.say("风蚀恶地：2级解锁；特殊掉落物：大量金币");
	tf.say("恶地地下有金矿，建教学楼好地方。不过，注意你的血量！");  
	tf.say("");
	tf.say("林地府邸：3级解锁；特殊掉落物：绿宝石");
	tf.say("小心，卫道士举着能大幅增加攻击的精钢斧头来了！");  
	tf.say("");
	tf.say("绯红森林：4级解锁；特殊掉落物：下界合金");
	tf.say("这里的生物看起来很狂躁！");  
	tf.say("");
	tf.say("游戏尽头：5级解锁；特殊掉落物：末影珍珠");
	tf.say("想要生存吗？先学会闪避。");  
	tf.say("");
	w.end_setall("确定");
	do
	{
		for(i=0;i<places;i++)
		{
			Color(i==p_user->at?L_Blue|Yellow:w.dftc);Place(plcx[i]-1	,	plcy[i]+3	);
			printf("%s%s",map_name[i],i==p_user->at?"(当前)":/*6格*/"      ");
		}
		do
			map=w.do_action();
		while(map<places&&btn[map].jud==false);
		if(map!=places)
			p_user->at=map;
	}
	while(map!=places);
	p_user->record_users_information();
	w.dftc=_Black;
	w.newpage();
	return;
}

