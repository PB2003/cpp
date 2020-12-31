
#define _BASICDATA_CPP_

#ifndef _COLOR_AND_PLACE_CPP_ 
    #define _COLOR_AND_PLACE_CPP_
    #include "color_and_place.cpp"
#endif

const char title[sizeof("ֲ���սֲ�� v1.1.3")]={"ֲ���սֲ�� v1.1.3"};
const char *size_cmd="mode con cols=150 lines=40";

//Plant_related 
#define Pkind           84
#define NPCkind 		3
#define Locked_plants	7 
#define Cherry			(Pkind-Locked_plants)//�� 
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
const char map_name[Maps+1][sizeof("ϡ����ԭ")]={"ϡ����ԭ","��ѩ��ԭ","��ʴ���","�ֵظ�ۡ","糺�ɭ��","��Ϸ��ͷ","�׳�"}; 
const char default_player_name	[PMax][sizeof("���0")]=	{"���0","���1","���2","���3"};
const char new_player_name[Maps+1][PMax][sizeof("�������")]=
														{
															{"��ʬ","����","������","���"},
															{"ѩ����","������","����ʦ","���"},
															{"ʬ��","֩��","ɱ����","���"},														
															{"�Ӷ���","����ʿ","��ħ��","���"},														
															{"�ҽ���","������","���","���"},
															{"ĩӰ��","ǱӰ��","ĩӰ��","���"},
															{"ħ���¸�","ħ��СA","ħ��СB","���"},
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
#define Sell 0/*δʵװ*/
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
	"�㶹����",
	"���տ�",
	"��������",
	"˫������",
	"�ѹ�",
	"���Ĳ�Ͷ��",
	"����Ͷ��",
	"����Ͷ��",
	"˫�����տ�",
	"С�繽",
	"���繽",
	"�Ȼ�",
	"����",
	"���⹽",
	"��С��",
	"������",
	"������",
	"��ǹ����",
	"·���㶹",
	"��Ͱ�㶹",
	"��������",
	"���ߺ���",
	"����Ͷ��",
	"������",
	"��Ģ��",
	"���׼�ũ��",
	"��������",
	"����",
	"����������",
	"������",
	"����«έ",
	"���«",
	"����",
	"�⾵��",
	"��������",
	"��ת��ݼ",
	"����Ͷ��",
	"��������",
	"쫷����",
	"�Ϲ�ͷ",
	"�߼��",
	"��ը���",
	"ȫϢ���", 
	"Ҷ�ӱ���ɡ",
	"��ת����",
	"�����׮",
	"˯��",
	"����",
	"��ʹ�ƶ���", 
	"����ƶ���",
	"����������", 
	"��������",
	"����ս��",
	"�����Ϲ���",
	"��������", 
	"��β����",
	"���̹��",
	"����Ů��",
	"«��ս��",
	"��ը����", 
	"ԭʼ�㶹����",
    "ԭʼ���տ�",
    "���۰Ͷ�",
    "����Ģ��",
    "���۱���",
    "��������",
    "ǿ������",
    "�ѹ�Ӣ",
    "�ش���",
    "����",
    "��������",
    "��ͷ����",
    "Ҭ�Ӽ�ũ��",
	"��յ��",
	"������",
	"�Զ���1",
	"�Զ���2",
	"ӣ��ը��",
    "��������",
    "��褽���",
    "�㶹��",
    "����ˮ��",
    "�¹��",
    "�ϰٺ�" 
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
#define IT/*item�Ӵ˹���ֲ��*/   131072
#define Special/*���������������׮��ע����*/  40 
#define NONE 30
const char tag_name[][sizeof("��")]={"��","��","��","Ͷ","��","��","��","��","��","ˮ","��","ƽ","��","��","��"};
void tag_show(int tag,int interval_space)
{
	int i,t;
	for(i=0,t=1;t<=AS;i++,t<<=1)	if(tag&t)	{printf("%s",tag_name[i]);Tab(interval_space);}
	return;
}
const char *tempname[pros]= 
{"HP","����","��������","����","����","����","����","����","����","����","��ֵ","����","����","˲ʱ","�Ƚ�","��ǩ","�����ȼ�","һ��","����","����"}; 
const int tempmin[pros]=
{1	 ,0     ,0         ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,25    ,0     ,0     ,0     ,1     ,0     ,1         ,0     ,0     ,0     };
const int tempmax[pros]=
{9999,999   ,999       ,3     ,1000  ,80    ,40    ,750   ,750   ,999   ,995   ,100   ,5     ,5     ,3     ,AM-1 ,10,AllSkills,AllSkills,AllSkills};
#define Collect -1
#define Selfdef -2 
const int ability[Pkind][Properties]=
{
	              /*  Hp ���� ���� ���� ���� ���� ���� ���� ���� ���� ��ֵ ���� ���� ˲ʱ �Ƚ� ��ǩ  �����ȼ�*/
/*0.�㶹����  */  {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,PN|ST   ,1   },
/*1.���տ�    */  {   98 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,100 ,25  ,Fast,0   ,1   ,AL|PD   ,1   },
/*2.��������  */  {  100 ,40  ,7   ,0   ,0   ,12  ,4   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,PN|ST|IA,1   },
/*3.˫������  */  {  108 ,60  ,10  ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,100 ,0   ,Fast,0   ,1   ,PN|ST   ,1   },
/*4.�ѹ�      */  {    1 ,180 ,0   ,0   ,0   ,0   ,999 ,0   ,167 ,0   ,100 ,0   ,0   ,Fast,1   ,$       ,1   },
/*5.���Ĳ�Ͷ��*/  {   80 ,50  ,5   ,0   ,0   ,0   ,2   ,0   ,83  ,0   ,50  ,0   ,Fast,0   ,1   ,CT      ,1   },
/*6.����Ͷ��  */  {  116 ,80  ,12  ,0   ,0   ,0   ,3   ,0   ,83  ,10  ,125 ,0   ,Fast,0   ,1   ,CT      ,4   },
/*7.����Ͷ��  */  {   90 ,32  ,5   ,1   ,333 ,0   ,2   ,0   ,333 ,0   ,75  ,0   ,Fast,0   ,1   ,CT      ,3   },
/*8.˫�����տ�*/  {  150 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,250 ,50  ,Fast,0   ,1   ,AL|PD   ,5   },
/*9.С�繽    */  {   70 ,35  ,2   ,0   ,0   ,0   ,10  ,167 ,50  ,0   ,35  ,0   ,Fast,0   ,1   ,MS|ST   ,1   },
/*10.���繽   */  {  100 ,40  ,2   ,0   ,0   ,0   ,3   ,0   ,50  ,12  ,75  ,0   ,Fast,0   ,1   ,MS      ,3   },
/*11.�Ȼ�   */  {    1 ,0   ,0   ,0   ,0   ,5   ,999 ,0   ,0   ,0   ,125 ,0   ,0   ,Fast,1   ,MS|AL   ,6   },
/*12.����   */  {    1 ,240 ,100 ,0   ,0	 ,0   ,999 ,0   ,167 ,120 ,200 ,0   ,0   ,Fast,2   ,MS|BA   ,4   },
/*13.���⹽   */  {   70 ,0   ,0   ,0   ,0   ,0   ,0   ,167 ,167 ,0   ,90  ,15  ,Fast,0   ,1   ,MS|AL|PD,2   },
/*14.��С��   */  {   80 ,36  ,10  ,0   ,0   ,0   ,3   ,500 ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,MS|ST   ,2   },
/*15.������   */  {    1 ,7   ,5   ,2   ,750 ,15  ,999 ,0   ,0   ,5   ,60  ,0   ,0   ,Fast,1   ,MS|BA|IA,2   },
/*16.������   */  {   85 ,180 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,0   ,Slo4,1   ,BA      ,3   },
/*17.��ǹ���� */  {  150 ,90  ,5   ,0   ,0   ,0   ,6   ,0   ,50  ,0   ,150 ,0   ,Fast,0   ,2   ,PN|ST   ,1   },
/*18.·������ */  {  150 ,40  ,5   ,0   ,0   ,0   ,6   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,PN|ST   ,2   },
/*19.��Ͱ���� */  {  250 ,40  ,5   ,0   ,0   ,0   ,10  ,0   ,50  ,0   ,125 ,0   ,Fast,0   ,1   ,PN|ST   ,5   },
/*20.�������� */  {  125 ,40  ,5   ,0   ,0   ,0   ,6   ,0   ,50  ,30  ,100 ,0   ,Fast,0   ,1   ,PN|ST   ,1   },
/*21.���ߺ��� */  {  125 ,40  ,7   ,0   ,0   ,12  ,6   ,0   ,50  ,30  ,135 ,0   ,Fast,0   ,1   ,PN|ST|IA,3   },
/*22.����Ͷ�� */  {  116 ,90  ,14  ,1   ,167 ,20  ,3   ,0   ,83  ,15  ,175 ,0   ,Fast,0   ,2   ,CT|IA   ,6   },
/*23.������   */  {  148 ,50  ,0   ,0   ,0   ,0   ,8   ,0   ,0   ,0   ,100 ,0   ,Fast,0   ,1   ,ST      ,3   },
/*24.��Ģ��   */  {   70 ,35  ,2   ,0   ,0   ,0   ,12  ,167 ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,MR|ST   ,2   },
/*25.���׼�ũ��*/ {  175 ,200 ,30  ,0   ,0   ,0   ,5   ,0   ,50  ,30  ,225 ,0   ,Slo4,0   ,2   ,BA      ,6   },
/*26.�������� */  {    1 ,1   ,0   ,2   ,833 ,0   ,999 ,0   ,0   ,0   ,25  ,0   ,0   ,Fast,1   ,IA      ,1   },
/*27.����     */  {  100 ,53  ,7   ,0   ,0   ,0   ,4   ,0   ,167 ,0   ,100 ,0   ,Fast,0   ,1   ,$       ,4   },
/*28.����������*/ {  100 ,36  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,100 ,0   ,Fast,0   ,1   ,ST      ,2   },
/*29.������   */  {   75 ,0   ,0   ,0   ,0   ,0   ,1   ,0   ,167 ,0   ,175 ,0   ,Slo4,0   ,1   ,AL      ,7   },
/*30.����«έ */  {   60 ,40  ,10  ,1   ,167 ,0   ,1   ,0   ,50  ,40  ,100 ,0   ,Fast,0   ,1   ,EA      ,3   },
/*31.���«   */  {  100 ,56  ,0   ,0   ,0   ,0   ,5   ,0   ,167 ,0   ,100 ,0   ,Slo2,0   ,1   ,FA      ,4   },
/*32.����     */  {   90 ,20  ,0   ,0   ,0   ,0   ,5   ,167 ,0   ,20  ,75  ,0   ,Fast,0   ,1   ,$       ,1   },
/*33.�⾵��   */  {  100 ,10  ,10  ,0   ,0   ,0   ,3   ,0   ,0   ,0   ,75  ,0   ,Fast,0   ,1   ,$       ,7   },
/*34.�������� */  {  100 ,40  ,0   ,0   ,0   ,0   ,3   ,167 ,50  ,0   ,100 ,0   ,Slo2,0   ,1   ,MR      ,4   },
/*35.��ת��ݼ */  {   90 ,25  ,0   ,0   ,0   ,0   ,2   ,83  ,50  ,25  ,125 ,0   ,Fast,0   ,1   ,ST|FL   ,4   },
/*36.����Ͷ�� */  {  110 ,65  ,12  ,0   ,0   ,0   ,3   ,0   ,50  ,10  ,115 ,0   ,Fast,0   ,1   ,CT|FA   ,4   },
/*37.�������� */  {  100 ,60  ,10  ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,PN|ST|FA,1   },
/*38.쫷���� */  {    1 ,6   ,0   ,1   ,167 ,25  ,999 ,0   ,0   ,2   ,40  ,0   ,0   ,Fast,1   ,$       ,4   },
/*39.�Ϲ�ͷ   */  {  170 ,NONE,0   ,0   ,0   ,0   ,10  ,0   ,0   ,0   ,125 ,0   ,Fast,0   ,1   ,AS      ,3   },
/*40.�߼��   */  {  250 ,NONE,0   ,0   ,0   ,0   ,12  ,0   ,0   ,0   ,175 ,0   ,Fast,0   ,1   ,AS      ,4   },
/*41.��ը��� */  {  130 ,NONE,0   ,0   ,0   ,0   ,6   ,0   ,167 ,0   ,200 ,0   ,Fast,0   ,1   ,AS      ,5   },
/*42.ȫϢ��� */  {  120 ,NONE,0   ,0   ,0   ,0   ,2   ,0   ,0   ,0   ,125 ,0   ,Fast,0   ,1   ,AS      ,6   },
/*43.Ҷ�ӱ���ɡ*/ {  100 ,NONE,0   ,0   ,0   ,0   ,2   ,0   ,0   ,0   ,75  ,0   ,Fast,0   ,1   ,AS|CV	,5   },
/*44.��ת���� */  {  110 ,NONE,0   ,0   ,0   ,0   ,4   ,0   ,0   ,0   ,85  ,0   ,Fast,0   ,1   ,AS|FL   ,7   },
/*45.�����׮ */  {  100 ,NONE,0   ,0   ,0   ,0   ,2   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,AS|FA   ,4   },
/*46.˯��     */  {   90 ,NONE,0   ,0   ,0   ,0   ,7   ,0   ,0   ,0   ,65  ,0   ,Fast,0   ,1   ,AS|MR|FT,1   },
/*47.����     */  {  100 ,50  ,0   ,0   ,0   ,0   ,8   ,0   ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,MR      ,3   },
/*48.��ʹ�ƶ���*/ {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,125 ,25  ,Fast,0   ,1   ,ST|PD   ,6   },
/*49.����ƶ���*/ {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,ST|DA   ,6   },
/*50.����������*/ {  100 ,50  ,5   ,0   ,0   ,0   ,4   ,0   ,50  ,0   ,150 ,0   ,Fast,0   ,1   ,CT|DA   ,7   },
/*51.�������� */  {  280 ,60  ,7   ,0   ,0   ,0   ,10  ,0   ,50  ,0   ,200 ,0   ,Fast,0   ,1   ,DA      ,9   },
/*52.����ս�� */  {  160 ,45  ,5   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,225 ,20  ,Fast,0   ,1   ,PD      ,8   },
/*53.�����Ϲ���*/ {  175 ,10+NONE,1,0   ,0   ,0   ,10  ,0   ,0   ,0   ,125 ,0   ,Fast,0   ,1   ,FA|AS   ,8   },
/*54.�������� */  {  200 ,60  ,20  ,0   ,0   ,0   ,10  ,0   ,50  ,20  ,150 ,0   ,Slo2,0   ,1   ,EA      ,8   },
/*55.��β���� */  {  100 ,35  ,10  ,0   ,0   ,0   ,5   ,83  ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,$       ,6   },
/*56.���̹�� */  {  140 ,40  ,5   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,100 ,0   ,Fast,0   ,1   ,DA      ,6   },
/*57.����Ů�� */  {  125 ,96  ,24  ,0   ,0   ,0   ,9   ,125 ,125 ,0   ,300 ,0   ,Fast,0   ,3   ,PN|ST   ,10  },
/*58.«��ս�� */  {  110 ,40  ,5   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,125 ,0   ,Slo3,0   ,1   ,FL|ST   ,7   },
/*59.��ը���� */  {    1 ,180 ,10  ,0   ,0   ,0   ,999 ,0   ,0   ,0   ,175 ,0   ,0   ,Fast,1   ,BA      ,9   },
/*60.ԭʼ�㶹����*/{ 120 ,55  ,10  ,1   ,750 ,0   ,5   ,0   ,167 ,0   ,75  ,0   ,Slo2,0   ,1   ,PN|ST   ,4   },
/*61.ԭʼ���տ�*/ {  118 ,0   ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,150 ,50  ,Slo2,0   ,1   ,PD|AL   ,5   },
/*62.���۰Ͷ�  */ {  100 ,40  ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,EA      ,2   },
/*63.����Ģ�� */  {  100 ,40  ,0   ,0   ,0   ,0   ,10  ,0   ,50  ,40  ,150 ,0   ,Fast,0   ,1   ,MS      ,5   },
/*64.���۱��� */  {  100 ,40  ,0   ,1   ,167 ,10  ,5   ,0   ,50  ,0   ,125 ,0   ,Fast,0   ,1   ,MS|IA|AM,7   },
/*65.�������� */  {   60 ,0	  ,0   ,0   ,0   ,0   ,0   ,83  ,0   ,0   ,85  ,0   ,0   ,Slo7,1   ,BA      ,8   },
/*66.ǿ������ */  {  100 ,40  ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,0   ,90  ,0   ,Fast,0   ,1   ,ST      ,4   },
/*67.�ѹ�Ӣ   */  {  100 ,98  ,0   ,0   ,0   ,0   ,5   ,0   ,50  ,5   ,175 ,0   ,Fast,0   ,1   ,BA      ,6   },
/*68.�ش���   */  {  180 ,15  ,0   ,0   ,0   ,0   ,5   ,0   ,500 ,0   ,150 ,0   ,Fast,0   ,1   ,FT      ,3   },
/*69.����   */  {  100 ,45  ,0   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,FL|FA   ,2   },
/*70.�������� */  {   50 ,29  ,0   ,0   ,0   ,0   ,5   ,0   ,0   ,0   ,50  ,0   ,Fast,0   ,1   ,FL      ,3   },
/*71.��ͷ���� */  {   90 ,90  ,0   ,0   ,0   ,0   ,0   ,0   ,50  ,0   ,150 ,0   ,Slo2,0   ,1   ,$       ,7   },
/*72.Ҭ�Ӽ�ũ��*/ {  160 ,150 ,0   ,0   ,0   ,0   ,0   ,0   ,167 ,20  ,175 ,0   ,Slo3,0   ,1   ,BA      ,9   },
/*73.��յ��	  */  {   75 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,100 ,0   ,Slo2,0   ,2   ,AL      ,2   },
/*74.������   */  {  100 ,50  ,0   ,0   ,0   ,0   ,0   ,0   ,50  ,50  ,175 ,0   ,Fast,0   ,1   ,FA      ,7   },
/*75.�Զ���1  */  {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,PN|ST   ,Selfdef},
/*76.�Զ���2  */  {  100 ,40  ,5   ,0   ,0   ,0   ,3   ,0   ,50  ,0   ,50  ,0   ,Fast,0   ,1   ,PN|ST   ,Selfdef},
/*#1.ӣ��ը�� */  {    1 ,160 ,20  ,0   ,0   ,0   ,999 ,0   ,333 ,100 ,125 ,0   ,0   ,Fast,1   ,BA      ,Collect},
/*#2.�������� */  {  100 ,100 ,20  ,1   ,83  ,0   ,4   ,0   ,333 ,100 ,165 ,0   ,Slo3,0	  ,1   ,EA      ,Collect},
/*#3.��褽��� */  {  112 ,30  ,5   ,0   ,0   ,0   ,4   ,0   ,50  ,4	  ,75  ,0   ,Fast,0	  ,1   ,$       ,Collect},
/*#4.�㶹��   */  {  100 ,40  ,5   ,0   ,0   ,0   ,4   ,0   ,50  ,0   ,115 ,0   ,Fast,0   ,1   ,PN|ST   ,Collect},
/*#5.����ˮ�� */  {  140 ,70  ,8   ,1   ,500 ,12  ,7   ,0   ,50  ,0   ,125 ,0   ,Fast,0	  ,1   ,IA	    ,Collect},
/*#6.�¹��   */  {  100 ,0   ,0   ,0   ,0   ,0   ,0   ,83  ,0   ,0   ,100 ,25  ,Fast,0   ,1   ,DA|AL|PD,Collect},
/*#7.�ϰٺ�   */  {   75 ,20  ,5   ,0   ,0   ,0   ,2   ,0   ,50  ,0   ,75  ,0   ,Fast,0   ,1   ,$		,Collect},
///*I1.������� */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
///*I2.���ⱦ�� */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
///*I3.������   */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
///*I4.�ɿ���   */  {    1 ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,0   ,75  ,0   ,	 ,Fast,1   ,IT		,1   },
	              /*  Hp ���� ���� ���� ���� ���� ���� ���� ���� ���� ��ֵ ���� ���� ˲ʱ �Ƚ� ��ǩ  �����ȼ�*/
};
const char itemsname[Ikind][NameLenthMax]=
{
	"�������",
	"���ⱦ��",
	"������",
	"�ɿ���",
	"�����ͷ��",
	"��żϻ", 
	"Ͷʯ��е��",
	"�����", 
	"��������",
	"Ӿ������", 
	"������",
	"�ƽ��ש", 
	"�鼮������", 
	"1�ǹ�����",
	"2�ǹ�����",
	"3�ǹ�����",
	"4�ǹ�����",
	"5�ǹ�����",
}; 
 

