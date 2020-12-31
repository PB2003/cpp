
#ifndef _GAMES_CPP_ 
    #define _GAMES_CPP_
    #include "game.cpp"
#endif

void for_freshman()
{
	BOOK w={Std_Uboundry   ,Std_Lboundry   ,Std_dx   ,Std_dy   ,/*dftc*/_White|_Light,/*aut*/false};	
	int s1[w.set_btnN(4)][4]={0};
	w.s1_link(s1);
	system("color 1e");
	Place(2,(Max_dy-sizeof("游戏前特别注意：请不要尝试改变窗口大小！！！"))/2);printf("游戏前特别注意：请不要尝试改变窗口大小！！！");
	Place(4,(Max_dy-sizeof("植物大战植物 v1.1.2"))/2);printf(title);
	Place(6,(Max_dy-sizeof("新手导引"))/2);printf("新手导引");
	GOTOHERE_PAGE_1:
	w.newpage(3,1);
	w.hint(3,sizeof("欢迎您成为植物大战植物益智小游戏的尊贵用户！"),"欢迎您成为植物大战植物益智小游戏的尊贵用户！");
	w.hint(5,sizeof("在开始游戏之前，您需要了解本游戏的操控方式和一些基本规则。"),"在开始游戏之前，您需要了解本游戏的操控方式和一些基本规则。");
	w.hint(7,sizeof("在游戏中会出现很多的按钮。按钮可点击与否分别表现为绿色和青色。"),"在游戏中会出现很多的按钮。按钮可点击与否分别表现为绿色和青色。");
	w.hint(9,sizeof("（在新手导引部分，若不按提示操作，某些绿色按钮也无法点击。）"),"（在新手导引部分，若不按提示操作，某些绿色按钮也无法点击。）");	
	w.hint(11,sizeof("当您把鼠标移动到按钮上，按下鼠标左键、右键、键盘↓键或ctrl键均被视为点击一次。"),
					"当您把鼠标移动到按钮上，按下鼠标左键、右键、键盘↓键或ctrl键均被视为点击一次。");
	w.hint(13,sizeof("点击后不需要输入回车。"),"点击后不需要输入回车。");
	w.hint(15,sizeof("如果鼠标左右键有一边不能使用，或需要输入回车，为正常现象。换用另一边即可。"),"如果鼠标左右键有一边不能使用，或输入需要回车，为正常现象。换用另一边即可。");
	w.hint(17,sizeof("试试看！"),"试试看！");
	w.end_setall("点我继续");
	w.do_confirm(Notcount);
	w.newpage(3,1);
	w.hint(3,sizeof("做得很好！"),"做得很好！");  
	w.hint(5,sizeof("有一类特殊的按钮为翻页按钮，既可以通过如上方法点击，"),"有一类特殊的按钮为翻页按钮，既可以通过如上方法点击，");
	w.hint(7,sizeof("又可以用←→键直接控制，不需鼠标配合。"),"又可以用←→键直接控制，不需鼠标配合。");
	w.hint(9,sizeof("试试看！"),"试试看！");  
	w.page_setall(w.dx-8,5);
	w.end_setall("我知道了");
	w.end_btn.judset(false);
	do
		w.do_action();
	while(w.action!=2); 	
	const int hello_x=w.x+9;
	const int hello_y=w.y+8;	  
	INP_BAR hello={  hello_x  ,  hello_y  ,  sizeof("请输入\"Hello USTC\"...")+6  ,  White|Light  };
	bool right_putin=false;	
	do
	{
		w.newpage(3,2); 
		w.hint(3,sizeof("做得很好！"),"做得很好！");
		w.hint(5,sizeof("形如图中黑框的输入栏，点击后可以用虚拟键盘输入文本。按Enter确认。"),"形如图中黑框的输入栏，点击后可以用虚拟键盘输入文本。按Enter确认。");
		w.hint(7,sizeof("试试输入\"USTC++\"（不含引号）！"),"试试输入\"USTC++\"（不含引号）！");
		hello.setall("请输入\"USTC++\"...",s1[0]);
		w.page_setall(w.dx-8,5);
		w.page_btn[0].judset(false);
		w.page_btn[1].judset(false);
		w.end_setall("继续浏览");
		w.end_btn.judset(false);
	 	do
			w.do_action();
		while(w.action!=0); 	
		while(hello.putin_vk('s')==false)
		{
			hello.newtxt("非法输入！"); 
			Sleep(500);
		}
		Color(_Light|_White|Green);Place(hello_x+1,hello_y);
		if(right_putin=(strcmp(hello.search.s,"USTC++")==0))
		 	printf("输入正确！");
		else
			printf("输入错误！");
		Sleep(500);
		hello.clearboard(_Blue);
	}
	while(!right_putin);
	w.newpage(3,2); 
	w.hint(3,sizeof("做得很好！"),"做得很好！");
	w.hint(5,sizeof("您可以继续浏览"),"您可以继续浏览");
	w.page_setall(w.dx-8,5);
	w.end_setall("继续浏览");
	do
		w.do_action();
	while(w.action==0); 
	if(w.action==1)
		goto GOTOHERE_PAGE_1; 
	w.newpage(3,3);
	w.hint(3,sizeof("关于操作，我们就介绍到这里。以下是对游戏核心内容——植物间战斗的简略介绍："),
					"关于操作，我们就介绍到这里。以下是对游戏核心内容——植物间战斗的简略介绍：");
	w.hint(5,sizeof("操控你的植物卡牌，与对手进行战斗，直到对手的卡牌耗尽。"),
					"操控你的植物卡牌，与对手进行战斗，直到对手的卡牌耗尽。");
	w.hint(7,sizeof("战斗的过程不只是攻击与HP下降，还有生产、技能发动等许多有趣的功能。"),
					"战斗的过程不只是攻击与HP下降，还有生产、技能发动等许多有趣的功能。");
	w.hint(9,sizeof("下面我们来看一个例子。"),"下面我们来看一个例子。");
	w.page_setall(w.dx-8,5);
	w.end_setall("查看卡牌");
	do
		w.do_action();
	while(w.action!=3);	
	w.hint(9,sizeof("下面我们来看一个例子。"),"下面我们来看一个例子。");
	w.newpage(3,3);
	plant[52/*葵花战车*/].card_demon(w.x+1,w.y+92,0,BIG);  
	w.hint(1,sizeof("这张卡牌为葵花战车，源自《植物大战僵尸Online》里的一个角色。"),"这张卡牌为葵花战车，源自《植物大战僵尸Online》里的一个角色。");
	w.hint(3,sizeof("这张卡牌的一个特性是既能攻击，又能生产，这在植物里是不多见的。"),"这张卡牌的一个特性是既能攻击，又能生产，这在植物里是不多见的。");
	w.hint(5,sizeof("你问我什么是生产？看到右上角的“225”了么？这代表了它的价值。"),"你问我什么是生产？看到右上角的“225”了么？这代表了它的价值。");
	w.hint(7,sizeof("简单来说，可以用生产出的阳光在战斗商店里按价值购买对应卡牌。"),"简单来说，可以用生产出的阳光在战斗商店里按价值购买对应卡牌。");
	w.hint(9,sizeof("生产出的阳光还有其他用处，比如作为棱镜草专属技能“折射”的消耗资源等等。"),
					"生产出的阳光还有其他用处，比如作为棱镜草专属技能“折射”的消耗资源等等。");
	w.hint(11,sizeof("啊，又引出了新概念“技能”！技能的种类和功能很复杂，建议登录后查看详细的游戏规则。"),
					"啊，又引出了新概念“技能”！技能的种类和功能很复杂，建议登录后查看详细的游戏规则。");
	w.hint(13,sizeof("顺便一提，葵花战车的技能是生产攻击...很直白的名字。"),"顺便一提，葵花战车的技能是生产攻击...很直白的名字。");
	w.hint(15,sizeof("点击下方按钮，我们继续来了解其它属性。"),"点击下方按钮，我们继续来了解其它属性。");
	w.page_setall(w.dx-8,5);
	w.end_setall("了解更多");
	do
		w.do_action();
	while(w.action!=3);
	w.newpage(3,3);
	w.hint(1,sizeof("血量条上的红字表示它每回合可以行动一次，但不是所有植物都这样。"),"血量条上的红字表示它每回合可以行动一次，但不是所有植物都这样。");
	w.hint(3,sizeof("有些植物的血量条为蓝色，请你在游戏中自己摸索其用意。"),"有些植物的血量条为蓝色，请你在游戏中自己摸索其用意。");	
	w.hint(5,sizeof("各种具体属性除了牌身展示出来的以外，还有冰冻、弱化等。"),"各种具体属性除了牌身展示出来的以外，还有冰冻、弱化等。");
	w.hint(7,sizeof("冰冻能使对手暂时无法行动，弱化能暂时削弱对手攻击力。葵花战车不具备这些性质，故不显示。"),
					"冰冻能使对手暂时无法行动，弱化能暂时削弱对手攻击力。葵花战车不具备这些性质，故不显示。");
	w.hint(9,sizeof("左下角的“产”则是定义葵花战车植物类型的标签。"),"左下角的“产”则是定义葵花战车植物类型的标签。");
	w.hint(11,sizeof("葵花战车卡牌的底色为绿色，表明它是1阶卡。2阶和3阶卡分别为紫底和金底。"),
					"葵花战车卡牌的底色为绿色，表明它是1阶卡。2阶和3阶卡分别为紫底和金底。");
	w.hint(13,sizeof("在目前这个版本，不同阶卡牌没有本质区别，但你应该猜到了，卡牌越高阶，性能越变态。"),
					"在目前这个版本，不同阶卡牌没有本质区别，但你应该猜到了，卡牌越高阶，性能越变态。");
	w.page_setall(w.dx-8,5);
	w.end_setall("了解其他");
	do
		w.do_action();
	while(w.action!=3);
	w.newpage(3,3);
	w.hint(1,sizeof("游戏中不只有战斗，用户系统也能满足您对于养成和收集的喜好。"),
					"游戏中不只有战斗，用户系统也能满足您对于养成和收集的喜好。");
	w.hint(3,sizeof("例如，使用卡牌是有等级限制的。8级以上用户才有权限使用葵花战车卡。"),
					"例如，使用卡牌是有等级限制的。8级以上用户才有权限使用葵花战车卡。");
	w.hint(5,sizeof("而对于某些卡牌，比如樱桃炸弹，单纯的升级对解锁并没有帮助；你需要从收集物品合成而来。"),
					"而对于某些卡牌，比如樱桃炸弹，单纯的升级对解锁并没有帮助；你需要从收集物品合成而来。");
	w.hint(7,sizeof("成就系统为您提供了挑战自我的动力，图鉴能让您回顾升级路上的点点滴滴。"),
					"成就系统为您提供了挑战自我的动力，图鉴能让您回顾升级路上的点点滴滴。");
	w.hint(9,sizeof("用户商店是个购物的好地方。缺钱？在战斗中获得吧！（当然这不是唯一方式）"),
					"用户商店是个购物的好地方。缺钱？在战斗中获得吧！（当然这不是唯一方式）");
	w.hint(11,sizeof("如果您对游戏规则有些许不满，自定义则是个不错的注意。"),
					"如果您对游戏规则有些许不满，自定义则是个不错的注意。");
	w.hint(13,sizeof("自定义为1.1.1版新增特性，它使游戏更富多样性，但使用不慎也可能让游戏乐趣下降。"),
					"自定义为1.1.1版新增特性，它使游戏更富多样性，但使用不慎也可能让游戏乐趣下降。");
	w.page_setall(w.dx-8,5);
	w.end_setall("我知道了");
	do
		w.do_action();
	while(w.action!=3);
	w.newpage(3,3);
	w.hint(1,sizeof("去注册个用户名吧！在从1级升到10级获得的2000点经验中，也获得游戏的乐趣。"),
					"去注册个用户名吧！在从1级升到10级获得的2000点经验中，也获得游戏的乐趣。");
	w.hint(3,sizeof("此后，本导引将不再在游戏开头自动展现，但你可以在主界面找到它。"),
					"此后，本导引将不再在游戏开头自动展现，但你可以在主界面找到它。");
	w.page_setall(w.dx-8,5);
	w.end_setall("去注册");
	do
		w.do_action();
	while(w.action!=3);	
	return; 
} 
int first_come_judge()
{
	int back_value;
	FILE *fp;
	if((fp=fopen("system\\for_new.txt","r+"))==NULL)
		system("pause");
	fscanf(fp,"%d",&back_value);
	fseek(fp,-1,SEEK_CUR);
	fprintf(fp,"%d",0);
	fclose(fp); 
	return back_value;
}







