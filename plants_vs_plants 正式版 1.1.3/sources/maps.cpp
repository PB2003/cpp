
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
	tf.say("�����ͼͼ��ѡ����Ҫȥ�ĵط���");
	tf.say("");
	tf.say("ϡ����ԭ��1������������������"); 
	tf.say("һƬ����а���ɱ����");
	tf.say("");
	tf.say("��ѩ��ԭ��1��������������������");
	tf.say("������������������");  
	tf.say("");
	tf.say("��ʴ��أ�2�����������������������");
	tf.say("��ص����н�󣬽���ѧ¥�õط���������ע�����Ѫ����");  
	tf.say("");
	tf.say("�ֵظ�ۡ��3�����������������̱�ʯ");
	tf.say("С�ģ�����ʿ�����ܴ�����ӹ����ľ��ָ�ͷ���ˣ�");  
	tf.say("");
	tf.say("糺�ɭ�֣�4�����������������½�Ͻ�");
	tf.say("��������￴�����ܿ��꣡");  
	tf.say("");
	tf.say("��Ϸ��ͷ��5����������������ĩӰ����");
	tf.say("��Ҫ��������ѧ�����ܡ�");  
	tf.say("");
	w.end_setall("ȷ��");
	do
	{
		for(i=0;i<places;i++)
		{
			Color(i==p_user->at?L_Blue|Yellow:w.dftc);Place(plcx[i]-1	,	plcy[i]+3	);
			printf("%s%s",map_name[i],i==p_user->at?"(��ǰ)":/*6��*/"      ");
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

