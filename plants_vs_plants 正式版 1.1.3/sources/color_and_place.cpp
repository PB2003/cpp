
#ifndef _CSTDIO_ 
    #define _CSTDIO_
    #include<cstdio>
#endif

#ifndef _IOSTREAM_ 
    #define _IOSTREAM_
    #include<iostream>
    using namespace std;
#endif

#ifndef _CONIO_H_ 
    #define _CONIO_H_
    #include<conio.h>
#endif/**/

#ifndef _CSTDLIB_ 
    #define _CSTDLIB_
    #include<cstdlib>
#endif

#ifndef _WINDOWS_H_ 
    #define _WINDOWS_H_
    #include<windows.h>
#endif

#ifndef DEF_TIME_H_  //���ǰ��Ϊ�»��߲������ 
    #define DEF_TIME_H_
    #include<time.h>
#endif

#ifndef _STRING_ 
    #define _STRING_
    #include <string>
#endif

#ifndef _STRING_H_ 
    #define _STRING_H_
    #include <string.h>
#endif

#define D(X)  {printf(X);system("pause");} 

int i1,i2,i3,i4,rcolor,I,J,_part_L,DX,DY,TXTL;
#define Color(c) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(c))
#define Light    FOREGROUND_INTENSITY
#define Green    FOREGROUND_GREEN
#define Red      FOREGROUND_RED
#define Blue     FOREGROUND_BLUE
#define Yellow   Green|Red
#define Cyan     Green|Blue
#define Purple   Red|Blue
#define White    Green|Red|Blue 
#define _Light   BACKGROUND_INTENSITY
#define _Blue    BACKGROUND_BLUE
#define _Red     BACKGROUND_RED 
#define _Green   BACKGROUND_GREEN
#define _Yellow  _Green|_Red
#define _Cyan    _Green|_Blue
#define _Purple  _Red|_Blue
#define _White   _Green|_Red|_Blue
#define L_Red    _Light|_Red
#define L_Green  _Light|_Green
#define L_Blue   _Light|_Blue
#define L_Yellow _Light|_Yellow
#define L_Cyan   _Light|_Cyan
#define L_Purple _Light|_Purple
#define L_White  _Light|_White
#define _Black   0 

#define  Rand_color(r) (rcolor=r%7,\
rcolor>0?(rcolor>1?(rcolor>2?(rcolor>3?(rcolor>4?(rcolor>5? Purple: Blue): Cyan| Light): Green): Yellow| Light): Yellow): Red) 
#define _Rand_color(r) (rcolor=r%7,\
rcolor>0?(rcolor>1?(rcolor>2?(rcolor>3?(rcolor>4?(rcolor>5?_Purple:_Blue):_Cyan|_Light):_Green):_Yellow|_Light):_Yellow):_Red)
 
#define Locate(p); GetCursorPos(&p);ScreenToClient(GetForegroundWindow(),&p);
#define xmin    0
#define xmax    1
#define ymin    2
#define ymax    3
#define Ifout(p,s)   (  p.y<s[xmin]   ||   p.y>s[xmax]   ||   p.x<s[ymin]   ||   p.x>s[ymax]    )    //p=��x��y���Ƿ�����������о�
#define Ifclick      (GetAsyncKeyState(/*VK_RBUTTON*/VK_DOWN)||GetAsyncKeyState(/*VK_RBUTTON*/VK_CONTROL)||GetAsyncKeyState(VK_RBUTTON)||GetAsyncKeyState(VK_LBUTTON)/*&0x8000*/)      //���down��������״̬
#define IfpushLeft   (GetAsyncKeyState(VK_LEFT)/*&0x8000*/)       //���down��������״̬
#define IfpushRight  (GetAsyncKeyState(VK_RIGHT)/*&0x8000*/)      //���down��������״̬
#define Notcount   -10
#define Fail       -1 
 
#define Tab(n)                           for(i1=0;i1<(n);i1++){printf(" ");}
#define Brushline(x,y,dy)                {Place(x,y);Tab(dy);}
#define Brushrow(x,y,dx)                 for(i2=(x);i2<(x)+(dx);i2++){Place(i2,y);Tab(2);} 
#define Brusharea(x,y,dx,dy)             for(i3=(x);i3<(x)+(dx);i3++){Place(i3,y);Tab(dy);}
#define Brushframe(x,y,dx,dy)            {Place(x,y);Tab(dy);for(i4=(x)+1;i4<(x)+(dx)-1;i4++){Place(i4,y);Tab(2);Place(i4,(y)+(dy)-2);Tab(2);}Place((x)+(dx)-1,y);Tab(dy);} 
#define Brushslots(x,y,dx,dy,XN,YN)      {for(I=0;I<(XN);I++){Place((x)+((dx)-1)*I,y);Tab(((dy)-2)*(YN)+2);for(J=0;J<=(YN);J++)/*��֪��Ϊʲô��������Ų���ʡ*/{Brushrow((x)+((dx)-1)*I+1,(y)+((dy)-2)*J,(dx)-2);}}Place((x)+((dx)-1)*(XN),y);Tab(((dy)-2)*(YN)+2);}

#define Dyeline(x,y,dy,color)                        {Color(color);Place(x,y);Tab(dy);}
#define Dyerow(x,y,dx,color)                         {Color(color);Brushrow(x,y,dx);}
#define Dyearea(x,y,dx,dy,color)                     {Color(color);Brusharea(x,y,dx,dy);}
#define Dyeframe(x,y,dx,dy,color)                    {Color(color);Brushframe(x,y,dx,dy);}
#define Dyeslots(x,y,dx,dy,XN,YN,color)              {Color(color);Brushslots(x,y,dx,dy,XN,YN);}
#define Dyenest(x,y,dx,dy,color1,color2)             {Dyeframe(x,y,dx,dy,color1);Dyearea(x+1,y+2,dx-2,dy-4,color2);}
#define Dyewindow(x,y,dx,dy,color1,rela_x,rela_y,small_dx,color2)  {Dyearea(x,y,dx,dy,color1);Dyearea(x+rela_x,y+rela_y,small_dx,dy-2*rela_y,color2);}//�Զ����� 

#define Middleplace(x,y,dy,stringl)       {Place((x),(y)+((dy)-(stringl))/2);}/*����*/
#define Strip(x,y,left,max,L,b,color1,color2,color3)\
{\
    if((_part_L=((left)*(L))/(max))>L)\
    	_part_L=L;\
	Color(color1);Place(x,y);Tab(_part_L);\
    Color(color2);/*������Place*/Tab(L-_part_L);\
    Color(color3);\
    Place(x+1,y);printf("%-*d",b,left);\
    Tab(L-2*b);printf("%*d",b,max);\
}
#define Button(area,JUD,TXT,c0,c1,c2)\
{\
    if(JUD) Color(c1|c0);\
	else    Color(c2|c0);\
	DX=area[xmax]-area[xmin];DY=area[ymax]-area[ymin];\
	    Brusharea(area[xmin],area[ymin],DX,DY);\
	TXTL=sizeof(TXT);\
	Middleplace(area[xmin]+DX/2,area[ymin],DY,TXTL);\
	printf("%s",TXT);\
}
#define StdButton(area,JUD,TXT)   Button(area,JUD,TXT, Purple , _Green|_Light , _Cyan|_Light);  //��Ĭ�ϵ�3������ 
//��λ����
void Place(int x,int y) 
{ 
	COORD PlaceCursorHere;
	PlaceCursorHere.X = y-1;PlaceCursorHere.Y = x-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),PlaceCursorHere);
    return;
}

//��Ч������жϺ���
int Effective(POINT p,int (*s)[4],int chunks_num,bool needclick,int max_round/*��ΪNotcount���൱������*/,int sleep_milisecond,bool coordinate_show)
/*�����б��㣬��������������������Ŀ���Ƿ���Ҫ����������ʱ���غϣ���ÿ�غϺ��������Ƿ���ʾ���꣨�����ã���*/
{
	int round=1,i;Place(1,30);
	bool click=needclick?false:true,out=true;
	while(out||!click)
	{
		if( (max_round!=Notcount) && (--max_round<0))
		    return Fail;     //�����ʱ 
		Locate(p);
		for(i=0;i<chunks_num;i++)
			if(  (out=Ifout(p,s[i]))==false  )
		        break;
		if(needclick==true)
		    click=Ifclick;
		if(coordinate_show)
		{
			Place(1,1);printf("(%d,%d)\n",p.x,p.y);
		    printf("��%d<min:%d?-->%d",p.y,s[0][xmin],p.y<s[0][xmin]);printf("  ��%d<min��%d?-->%d",p.x,s[0][ymin],p.x<s[0][ymin]);
		    printf("��%d>max:%d?-->%d",p.y,s[0][xmax],p.y>s[0][xmax]);printf("  ��%d>max��%d?-->%d",p.x,s[0][ymax],p.x>s[0][ymax]);
			printf("\nCLICK=%d   ",click);
			printf("judge=%d  ",(  p.y<s[0][xmin]   ||   p.y>s[0][xmax]   ||   p.x<s[0][ymin]   ||   p.x>s[0][ymax]    ));
	    }	
		Sleep(sleep_milisecond);
		round++;	
	}
	return i;        //�����˵�i������i=0��ʼ�� 
}
void precise_coord(int area[4],int coor[4],int coordshow)
{
	coor[xmin]=(area[xmin]-1)*16+1;
	coor[xmax]=(area[xmax]-1)*16  ;
	coor[ymin]=(area[ymin]-1)*8+1 ;
	coor[ymax]=(area[ymax]-1)*8   ;
	if(coordshow!=0)
	{
	    Place(coordshow,1);printf("(x %d~%d, y%d~%d)",coor[xmin],coor[xmax],coor[ymin],coor[ymax]);
    }
	return; 
}

