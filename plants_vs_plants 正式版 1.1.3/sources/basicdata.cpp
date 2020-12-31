
#define _BASICDATA_CPP_

#ifndef _COLOR_AND_PLACE_CPP_ 
    #define _COLOR_AND_PLACE_CPP_
    #include "color_and_place.cpp"
#endif

const char title[sizeof("植物大战植物 v1.1.3")]={"植物大战植物 v1.1.3"};
const char *size_cmd="mode con cols=150 lines=40";

//Plant_related 
#define Pkind           84
#define NPCkind 		3
#define Locked_plants	7 
#define Cherry			(Pkind-Locked_plants)//改 
#define Ikind           20
#define Properties      17
#define NameLenthMax    20
#define SentenceLenthMax  200
#define SkillMax        3
const int pros=Properties+SkillMax;
//Card_size_related
#define BIG 1
    #define BIG_dx 17
    #define BIG_dy 22
#define DEAD_BIG 2
#define ICY_BIG 3
#define EXP_BIG 5
#define SMA 4
    #define SMA_dx 6
    #define SMA_dy 14
//Player_related
#define PMax            4
#define CardsMax        (Pkind*PMax)
#define Initial_cards   3
#define HaveMax         10
#define NOBODY          NULL
//User_related
#define UNameMax 20 
#define MARK '#'
#define INTERVAL '^'
#define ADD '&'
#define NO '!'
//name
#define Maps 6
#define Tundra			1
#define Badland			2
#define Mansion			3 
#define Crimson_forest	4
#define End_city		5 
#define Fire_city		6 
const char map_name[Maps+1][sizeof("稀树草原")]={"稀树草原","积雪冻原","风蚀恶地","林地府邸","绯红森林","游戏尽头","炎城"}; 
const char default_player_name	[PMax][sizeof("玩家0")]=	{"玩家0","玩家1","玩家2","玩家3"};
const char new_player_name[Maps+1][PMax][sizeof("玩家名称")]=
														{
															{"僵尸","骷髅","爬行者","玩家"},
															{"雪傀儡","流浪者","冰术师","玩家"},
															{"尸壳","蜘蛛","杀手兔","玩家"},														
															{"掠夺者","卫道士","唤魔者","玩家"},														
															{"岩浆怪","疣猪兽","恶魂","玩家"},
															{"末影螨","潜影贝","末影人","玩家"},
															{"魔化陈刚","魔化小A","魔化小B","玩家"},
														};
//hardship
#define HARMONY 1
#define EASY 2
#define NORMAL 3
#define HARD 4
//Buttom_and_PW_related
#define Max_dx 40
#define Max_dy 150
//record
#define MaxRecord    5
//size 
#define Stdheight       3
#define Stdwidth        15

#define Std_dx 24
#define Std_dy 90
#define Std_Uboundry ((Max_dx-Std_dx)/2)
#define Std_Lboundry ((Max_dy-Std_dy)/2)

#define Larger_dx 32
#define Larger_dy 120
#define Larger_Uboundry ((Max_dx-Larger_dx)/2)
#define Larger_Lboundry ((Max_dy-Larger_dy)/2)

#define Smaller_dx 17
#define Smaller_dy 50

#define Std_flush_period 100
#define Std_wait_periods 5
//Rule_related
#define Pierce_P 250
#define Attack_fly_P 667
#define Shoot_fly_P 375
#define Cast_fly_P 833
#define Flat_fly_P 0
#define Cast_cover_P 333
//battle_related
#define Fail_att -1
#define MISS 0 
#define HURT 1 
#define KILL 2 
//card_change
#define Buy 1
#define Sell 0/*未实装*/
#define Plant_die -1
#define Explode -2
#define Captivate -3
#define Be_Captivate -4
//go_through_system 
#define GO_THROUGH 6
#define AIMED      0
#define REALHURT   1
#define SPUTTER    2 
#define WEAKEN     3
#define FROZEN     4 
#define MFKCD      5//miss,fail,kill,crit,dark
    #define MFKCD_Max 5
    #define MFKCD_M   1
    #define MFKCD_F   2
    #define MFKCD_K   4
    #define MFKCD_C   8
    #define MFKCD_D   16
#define DIDNOT -2
//skills
#define AllSkills 36

#define Ordinate 0
#define Specific 1
#define Self -1
#define Others -2

#define Passive 	-1 
#define Always 		-2
#define Adjunct 	-3
#define Passive_S 	-4
#define Single 		1 
#define Double 		2
#define Triple 		3
#define Tetra 		4
#define Objective	100
#define Nolimit 	9999

#define Unskilled	1
#define Experienced	2
#define Perfect		3

#define Have_to 	-4
#define Must		-3
#define Better		-2
#define Good		-1

//effects
#define Eff_Temp 12 
#define e_HP_M		0
#define e_HP_L		1
#define e_att		2
#define e_att_kind	3
#define e_att_add	4
#define e_def_add	5
#define e_frozen	6
#define e_weaken	7
#define e_produce	10
#define e_dark 		11

#define REAL 1 
#define PHYS 2
//points
int final_pt[4]={6400,1600,400,100};
#define M_kill_pt 200
#define S_kill_pt 100
#define Active_pt 150
#define Freeze_pt 50
//level
#define MaxLevel  10   /*Lv.1 ,2  ,3  ,4  ,5  ,6  ,7   ,8  ,9   ,10  */
int exp_demand[MaxLevel]={ 0 ,100,200,300,450,600,800,1100,1500,2000}; 

const char plantsname[Pkind+Locked_plants][NameLenthMax]=
{
	"豌豆射手",
	"向日葵",
	"寒冰射手",
	"双发射手",
	"窝瓜",
	"卷心菜投手",
	"西瓜投手",
	"玉米投手",
	"双子向日葵",
	"小喷菇",
	"大喷菇",
	"魅惑菇",
	"毁灭菇",
	"阳光菇",
	"胆小菇",
	"寒冰菇",
	"土豆雷",
	"机枪射手",
	"路障豌豆",
	"铁桶豌豆",
	"三线射手",
	"三线寒冰",
	"冰瓜投手",
	"仙人掌",
	"海蘑菇",
	"玉米加农炮",
	"冰冻生菜",
	"菜问",
	"回旋镖射手",
	"能量花",
	"闪电芦苇",
	"火葫芦",
	"竹笋",
	"棱镜草",
	"保龄泡泡",
	"旋转芜菁",
	"辣椒投手",
	"火焰射手",
	"飓风甘蓝",
	"南瓜头",
	"高坚果",
	"爆炸坚果",
	"全息坚果", 
	"叶子保护伞",
	"旋转菠萝",
	"火炬树桩",
	"睡莲",
	"香蒲",
	"天使黄豆炮", 
	"黯灭黄豆炮",
	"幽灵西红柿", 
	"暗铁榴莲",
	"葵花战车",
	"火焰南瓜王",
	"轰鸣核桃", 
	"六尾风王",
	"刺猬坦克",
	"海盗女王",
	"芦笋战机",
	"爆炸葡萄", 
	"原始豌豆射手",
    "原始向日葵",
    "电眼巴豆",
    "忧郁蘑菇",
    "方舟冰菇",
    "逃脱树根",
    "强酸柠檬",
    "蒲公英",
    "地刺王",
    "鬼椒王",
    "幽灵辣椒",
    "三头大嘴",
    "椰子加农炮",
	"金盏花",
	"火龙草",
	"自定义1",
	"自定义2",
	"樱桃炸弹",
    "充能柚子",
    "周瑜蕉弩",
    "豌豆荚",
    "玄冰水仙",
    "月光草",
    "紫百合" 
};
#define Fast 1 
#define Slo2 2 
#define Slo3 3
#define Slo4 4
#define Slo7 7
#define $                    	 0
#define PN/*Peanut*/         	 1
#define MS/*Mushroom*/       	 2
#define ST/*Shooter*/        	 4
#define CT/*Caster*/         	 8
#define IA/*Icy_attack*/     	 16
#define FA/*Fire_attack*/    	 32 
#define EA/*Electro_attack*/ 	 64
#define BA/*Boom_attack*/    	 128
#define DA/*Dark_attack*/    	 256
#define MR/*Marine*/         	 512
#define FL/*Flying*/         	 1024 
#define FT/*Flat*/	 			 2048
#define CV/*cover*/	 			 4096
#define PD/*Productive*/     	 8192
#define AS/*Assistant*/      	 16384 
#define AM/*Assistant_and_main*/ 32768 
#define AL/*attack_lack_main*/	 65536
#define IT/*item从此归入植物*/   131072
#define Special/*仅在下面做火炬树桩的注释用*/  40 
#define NONE 30
const char tag_name[][sizeof("豆")]={"豆","菇","射","投","冰","火","雷","轰","暗","水","飞","平","罩","产","辅"};
void tag_show(int tag,int interval_space)
{
	int i,t;
	for(i=0,t=1;t<=AS;i++,t<<=1)	if(tag&t)	{printf("%s",tag_name[i]);Tab(interval_space);}
	return;
}
const char *tempname[pros]= 
{"HP","攻击","攻击波动","冰冻","冰率","弱化","防御","闪率","暴率","溅射","价值","产能","攻速","瞬时","等阶","标签","解锁等级","一技","二技","三技"}; 
const int tempmin[pros]=
{1	 ,0     ,0         ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,25    ,0     ,0     ,0     ,1     ,0     ,1         ,0     ,0     ,0     };
const int tempmax[pros]=
{9999,999   ,999       ,3     ,1000  ,80    ,40    ,750   ,750   ,999   ,995   ,100   ,5     ,5     ,3     ,AM-1 ,10,AllSkills,AllSkills,AllSkills};
#define Collect -1
#define Selfdef -2 
const int ability[Pkind][Properties]=
{
	              /*  Hp 攻击 波动 冰冻 冰率 弱化 防御 闪率 暴率 溅射 价值 产能 攻速 瞬时 等阶 标签  解锁等级*/
/*0.豌豆射手  */  {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,PN|ST   ,1   },
/*1.向日葵    */  {   98 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,100 ,25  ,Fast,0   ,1   ,AL|PD   ,1   },
/*2.寒冰射手  */  {  100 ,40  ,7   ,0   ,0   ,12  ,4   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,PN|ST|IA,1   },
/*3.双发射手  */  {  108 ,60  ,10  ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,100 ,0   ,Fast,0   ,1   ,PN|ST   ,1   },
/*4.窝瓜      */  {    1 ,180 ,0   ,0   ,0   ,0   ,999 ,0   ,167 ,0   ,100 ,0   ,0   ,Fast,1   ,$       ,1   },
/*5.卷心菜投手*/  {   80 ,50  ,5   ,0   ,0   ,0   ,2   ,0   ,83  ,0   ,50  ,0   ,Fast,0   ,1   ,CT      ,1   },
/*6.西瓜投手  */  {  116 ,80  ,12  ,0   ,0   ,0   ,3   ,0   ,83  ,10  ,125 ,0   ,Fast,0   ,1   ,CT      ,4   },
/*7.玉米投手  */  {   90 ,32  ,5   ,1   ,333 ,0   ,2   ,0   ,333 ,0   ,75  ,0   ,Fast,0   ,1   ,CT      ,3   },
/*8.双子向日葵*/  {  150 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,250 ,50  ,Fast,0   ,1   ,AL|PD   ,5   },
/*9.小喷菇    */  {   70 ,35  ,2   ,0   ,0   ,0   ,10  ,167 ,50  ,0   ,35  ,0   ,Fast,0   ,1   ,MS|ST   ,1   },
/*10.大喷菇   */  {  100 ,40  ,2   ,0   ,0   ,0   ,3   ,0   ,50  ,12  ,75  ,0   ,Fast,0   ,1   ,MS      ,3   },
/*11.魅惑菇   */  {    1 ,0   ,0   ,0   ,0   ,5   ,999 ,0   ,0   ,0   ,125 ,0   ,0   ,Fast,1   ,MS|AL   ,6   },
/*12.毁灭菇   */  {    1 ,240 ,100 ,0   ,0	 ,0   ,999 ,0   ,167 ,120 ,200 ,0   ,0   ,Fast,2   ,MS|BA   ,4   },
/*13.阳光菇   */  {   70 ,0   ,0   ,0   ,0   ,0   ,0   ,167 ,167 ,0   ,90  ,15  ,Fast,0   ,1   ,MS|AL|PD,2   },
/*14.胆小菇   */  {   80 ,36  ,10  ,0   ,0   ,0   ,3   ,500 ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,MS|ST   ,2   },
/*15.寒冰菇   */  {    1 ,7   ,5   ,2   ,750 ,15  ,999 ,0   ,0   ,5   ,60  ,0   ,0   ,Fast,1   ,MS|BA|IA,2   },
/*16.土豆雷   */  {   85 ,180 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,0   ,Slo4,1   ,BA      ,3   },
/*17.机枪射手 */  {  150 ,90  ,5   ,0   ,0   ,0   ,6   ,0   ,50  ,0   ,150 ,0   ,Fast,0   ,2   ,PN|ST   ,1   },
/*18.路障射手 */  {  150 ,40  ,5   ,0   ,0   ,0   ,6   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,PN|ST   ,2   },
/*19.铁桶射手 */  {  250 ,40  ,5   ,0   ,0   ,0   ,10  ,0   ,50  ,0   ,125 ,0   ,Fast,0   ,1   ,PN|ST   ,5   },
/*20.三线射手 */  {  125 ,40  ,5   ,0   ,0   ,0   ,6   ,0   ,50  ,30  ,100 ,0   ,Fast,0   ,1   ,PN|ST   ,1   },
/*21.三线寒冰 */  {  125 ,40  ,7   ,0   ,0   ,12  ,6   ,0   ,50  ,30  ,135 ,0   ,Fast,0   ,1   ,PN|ST|IA,3   },
/*22.冰瓜投手 */  {  116 ,90  ,14  ,1   ,167 ,20  ,3   ,0   ,83  ,15  ,175 ,0   ,Fast,0   ,2   ,CT|IA   ,6   },
/*23.仙人掌   */  {  148 ,50  ,0   ,0   ,0   ,0   ,8   ,0   ,0   ,0   ,100 ,0   ,Fast,0   ,1   ,ST      ,3   },
/*24.海蘑菇   */  {   70 ,35  ,2   ,0   ,0   ,0   ,12  ,167 ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,MR|ST   ,2   },
/*25.玉米加农炮*/ {  175 ,200 ,30  ,0   ,0   ,0   ,5   ,0   ,50  ,30  ,225 ,0   ,Slo4,0   ,2   ,BA      ,6   },
/*26.冰冻生菜 */  {    1 ,1   ,0   ,2   ,833 ,0   ,999 ,0   ,0   ,0   ,25  ,0   ,0   ,Fast,1   ,IA      ,1   },
/*27.菜问     */  {  100 ,53  ,7   ,0   ,0   ,0   ,4   ,0   ,167 ,0   ,100 ,0   ,Fast,0   ,1   ,$       ,4   },
/*28.回旋镖射手*/ {  100 ,36  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,100 ,0   ,Fast,0   ,1   ,ST      ,2   },
/*29.能量花   */  {   75 ,0   ,0   ,0   ,0   ,0   ,1   ,0   ,167 ,0   ,175 ,0   ,Slo4,0   ,1   ,AL      ,7   },
/*30.闪电芦苇 */  {   60 ,40  ,10  ,1   ,167 ,0   ,1   ,0   ,50  ,40  ,100 ,0   ,Fast,0   ,1   ,EA      ,3   },
/*31.火葫芦   */  {  100 ,56  ,0   ,0   ,0   ,0   ,5   ,0   ,167 ,0   ,100 ,0   ,Slo2,0   ,1   ,FA      ,4   },
/*32.竹笋     */  {   90 ,20  ,0   ,0   ,0   ,0   ,5   ,167 ,0   ,20  ,75  ,0   ,Fast,0   ,1   ,$       ,1   },
/*33.棱镜草   */  {  100 ,10  ,10  ,0   ,0   ,0   ,3   ,0   ,0   ,0   ,75  ,0   ,Fast,0   ,1   ,$       ,7   },
/*34.保龄泡泡 */  {  100 ,40  ,0   ,0   ,0   ,0   ,3   ,167 ,50  ,0   ,100 ,0   ,Slo2,0   ,1   ,MR      ,4   },
/*35.旋转芜菁 */  {   90 ,25  ,0   ,0   ,0   ,0   ,2   ,83  ,50  ,25  ,125 ,0   ,Fast,0   ,1   ,ST|FL   ,4   },
/*36.辣椒投手 */  {  110 ,65  ,12  ,0   ,0   ,0   ,3   ,0   ,50  ,10  ,115 ,0   ,Fast,0   ,1   ,CT|FA   ,4   },
/*37.火焰射手 */  {  100 ,60  ,10  ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,PN|ST|FA,1   },
/*38.飓风甘蓝 */  {    1 ,6   ,0   ,1   ,167 ,25  ,999 ,0   ,0   ,2   ,40  ,0   ,0   ,Fast,1   ,$       ,4   },
/*39.南瓜头   */  {  170 ,NONE,0   ,0   ,0   ,0   ,10  ,0   ,0   ,0   ,125 ,0   ,Fast,0   ,1   ,AS      ,3   },
/*40.高坚果   */  {  250 ,NONE,0   ,0   ,0   ,0   ,12  ,0   ,0   ,0   ,175 ,0   ,Fast,0   ,1   ,AS      ,4   },
/*41.爆炸坚果 */  {  130 ,NONE,0   ,0   ,0   ,0   ,6   ,0   ,167 ,0   ,200 ,0   ,Fast,0   ,1   ,AS      ,5   },
/*42.全息坚果 */  {  120 ,NONE,0   ,0   ,0   ,0   ,2   ,0   ,0   ,0   ,125 ,0   ,Fast,0   ,1   ,AS      ,6   },
/*43.叶子保护伞*/ {  100 ,NONE,0   ,0   ,0   ,0   ,2   ,0   ,0   ,0   ,75  ,0   ,Fast,0   ,1   ,AS|CV	,5   },
/*44.旋转菠萝 */  {  110 ,NONE,0   ,0   ,0   ,0   ,4   ,0   ,0   ,0   ,85  ,0   ,Fast,0   ,1   ,AS|FL   ,7   },
/*45.火炬树桩 */  {  100 ,NONE,0   ,0   ,0   ,0   ,2   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,AS|FA   ,4   },
/*46.睡莲     */  {   90 ,NONE,0   ,0   ,0   ,0   ,7   ,0   ,0   ,0   ,65  ,0   ,Fast,0   ,1   ,AS|MR|FT,1   },
/*47.香蒲     */  {  100 ,50  ,0   ,0   ,0   ,0   ,8   ,0   ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,MR      ,3   },
/*48.天使黄豆炮*/ {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,125 ,25  ,Fast,0   ,1   ,ST|PD   ,6   },
/*49.黯灭黄豆炮*/ {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,ST|DA   ,6   },
/*50.幽灵西红柿*/ {  100 ,50  ,5   ,0   ,0   ,0   ,4   ,0   ,50  ,0   ,150 ,0   ,Fast,0   ,1   ,CT|DA   ,7   },
/*51.暗铁榴莲 */  {  280 ,60  ,7   ,0   ,0   ,0   ,10  ,0   ,50  ,0   ,200 ,0   ,Fast,0   ,1   ,DA      ,9   },
/*52.葵花战车 */  {  160 ,45  ,5   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,225 ,20  ,Fast,0   ,1   ,PD      ,8   },
/*53.火焰南瓜王*/ {  175 ,10+NONE,1,0   ,0   ,0   ,10  ,0   ,0   ,0   ,125 ,0   ,Fast,0   ,1   ,FA|AS   ,8   },
/*54.轰鸣核桃 */  {  200 ,60  ,20  ,0   ,0   ,0   ,10  ,0   ,50  ,20  ,150 ,0   ,Slo2,0   ,1   ,EA      ,8   },
/*55.六尾风王 */  {  100 ,35  ,10  ,0   ,0   ,0   ,5   ,83  ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,$       ,6   },
/*56.刺猬坦克 */  {  140 ,40  ,5   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,100 ,0   ,Fast,0   ,1   ,DA      ,6   },
/*57.海盗女王 */  {  125 ,96  ,24  ,0   ,0   ,0   ,9   ,125 ,125 ,0   ,300 ,0   ,Fast,0   ,3   ,PN|ST   ,10  },
/*58.芦笋战机 */  {  110 ,40  ,5   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,125 ,0   ,Slo3,0   ,1   ,FL|ST   ,7   },
/*59.爆炸葡萄 */  {    1 ,180 ,10  ,0   ,0   ,0   ,999 ,0   ,0   ,0   ,175 ,0   ,0   ,Fast,1   ,BA      ,9   },
/*60.原始豌豆射手*/{ 120 ,55  ,10  ,1   ,750 ,0   ,5   ,0   ,167 ,0   ,75  ,0   ,Slo2,0   ,1   ,PN|ST   ,4   },
/*61.原始向日葵*/ {  118 ,0   ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,150 ,50  ,Slo2,0   ,1   ,PD|AL   ,5   },
/*62.电眼巴豆  */ {  100 ,40  ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,EA      ,2   },
/*63.忧郁蘑菇 */  {  100 ,40  ,0   ,0   ,0   ,0   ,10  ,0   ,50  ,40  ,150 ,0   ,Fast,0   ,1   ,MS      ,5   },
/*64.方舟冰菇 */  {  100 ,40  ,0   ,1   ,167 ,10  ,5   ,0   ,50  ,0   ,125 ,0   ,Fast,0   ,1   ,MS|IA|AM,7   },
/*65.逃脱树根 */  {   60 ,0	  ,0   ,0   ,0   ,0   ,0   ,83  ,0   ,0   ,85  ,0   ,0   ,Slo7,1   ,BA      ,8   },
/*66.强酸柠檬 */  {  100 ,40  ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,ST      ,4   },
/*67.蒲公英   */  {  100 ,98  ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,5   ,175 ,0   ,Fast,0   ,1   ,BA      ,6   },
/*68.地刺王   */  {  180 ,15  ,0   ,0   ,0   ,0   ,5   ,0   ,500 ,0   ,150 ,0   ,Fast,0   ,1   ,FT      ,3   },
/*69.鬼椒王   */  {  100 ,45  ,0   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,FL|FA   ,2   },
/*70.幽灵辣椒 */  {   50 ,29  ,0   ,0   ,0   ,0   ,5   ,0   ,0   ,0   ,50  ,0   ,Fast,0   ,1   ,FL      ,3   },
/*71.三头大嘴 */  {   90 ,90  ,0   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,150 ,0   ,Slo2,0   ,1   ,$       ,7   },
/*72.椰子加农炮*/ {  160 ,150 ,0   ,0   ,0   ,0   ,0   ,0   ,167 ,20  ,175 ,0   ,Slo3,0   ,1   ,BA      ,9   },
/*73.金盏花	  */  {   75 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,100 ,0   ,Slo2,0   ,2   ,AL      ,2   },
/*74.火龙草   */  {  100 ,50  ,0   ,0   ,0   ,0   ,0   ,0   ,50  ,50  ,175 ,0   ,Fast,0   ,1   ,FA      ,7   },
/*75.自定义1  */  {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,PN|ST   ,Selfdef},
/*76.自定义2  */  {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,PN|ST   ,Selfdef},
/*#1.樱桃炸弹 */  {    1 ,160 ,20  ,0   ,0   ,0   ,999 ,0   ,333 ,100 ,125 ,0   ,0   ,Fast,1   ,BA      ,Collect},
/*#2.充能柚子 */  {  100 ,100 ,20  ,1   ,83  ,0   ,4   ,0   ,333 ,100 ,165 ,0   ,Slo3,0	  ,1   ,EA      ,Collect},
/*#3.周瑜蕉弩 */  {  112 ,30  ,5   ,0   ,0   ,0   ,4   ,0   ,50  ,4	  ,75  ,0   ,Fast,0	  ,1   ,$       ,Collect},
/*#4.豌豆荚   */  {  100 ,40  ,5   ,0   ,0   ,0   ,4   ,0   ,50  ,0   ,115 ,0   ,Fast,0   ,1   ,PN|ST   ,Collect},
/*#5.玄冰水仙 */  {  140 ,70  ,8   ,1   ,500 ,12  ,7   ,0   ,50  ,0   ,125 ,0   ,Fast,0	  ,1   ,IA	    ,Collect},
/*#6.月光草   */  {  100 ,0   ,0   ,0   ,0   ,0   ,0   ,83  ,0   ,0   ,100 ,25  ,Fast,0   ,1   ,DA|AL|PD,Collect},
/*#7.紫百合   */  {   75 ,20  ,5   ,0   ,0   ,0   ,2   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,$		,Collect},
///*I1.阳光袋子 */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
///*I2.阳光宝箱 */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
///*I3.能量豆   */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
///*I4.巧克力   */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
	              /*  Hp 攻击 波动 冰冻 冰率 弱化 防御 闪率 暴率 溅射 价值 产能 攻速 瞬时 等阶 标签  解锁等级*/
};
const char itemsname[Ikind][NameLenthMax]=
{
	"阳光袋子",
	"阳光宝箱",
	"能量豆",
	"巧克力",
	"橄榄球头盔",
	"玩偶匣", 
	"投石机械臂",
	"阳光铲", 
	"喷气背包",
	"泳池清理车", 
	"武器架",
	"黄金地砖", 
	"书籍：分裂", 
	"1星攻击书",
	"2星攻击书",
	"3星攻击书",
	"4星攻击书",
	"5星攻击书",
}; 
 

