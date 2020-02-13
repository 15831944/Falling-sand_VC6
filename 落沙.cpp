// ��ɳ.cpp : Defines the entry point for the application.
//
#include "E:/Library/VisualStudioHeadFiles/TouchImage.h"

enum :COLORREF
{
	AIR
	, MAGMA = 0XFF0000
	, WATER = 0X0000FF
	, STRUCTOR = 0X8080FF
	, SAND = 0XD5D558
	, DEVOURER = 0X800080
	, PRODUCER_0 = 0X402020
	, PRODUCER_1 = 0XD86080
};

#include <cstdlib>
#include <ctime>
#include <cstdio>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	srand(time(0));

	const int WinWidth = GetSystemMetrics(SM_CXSCREEN);
	const int WinHeight = GetSystemMetrics(SM_CYSCREEN);

	HWND hwnd;

	hwnd=TouchImage::Initgraph(WinWidth,WinHeight);		//��ʼ������
	
	SetWindowLong(TouchImage::GetHwnd(),GWL_STYLE,GetWindowLong(TouchImage::GetHwnd(),GWL_STYLE)&(~WS_CAPTION));//ȡ�����
	SetWindowText(TouchImage::GetHwnd(), "��ɳ");

#ifdef _DEBUG

	//�����ޱ߿�
	::SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)&(~(WS_CAPTION | WS_SYSMENU | WS_SIZEBOX)));
	//����͸������
	::SetWindowLong(hwnd, GWL_EXSTYLE, (GetWindowLong(hwnd, GWL_EXSTYLE)&(~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME))) | WS_EX_LAYERED);
#endif // _DEBUG
	//���þ��п�ǰ
	SetWindowPos(hwnd, HWND_TOPMOST, (GetSystemMetrics(SM_CXSCREEN) - getwidth()) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - getheight()) / 2, getwidth(), getheight(), SWP_SHOWWINDOW | SWP_FRAMECHANGED | SWP_DRAWFRAME);

	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

	MOUSEMSG Msg={NULL};						//�����Ϣ
	DWORD*Pscreen=TouchImage::GetWndPtDword();	//�����ڴ�ָ��
	COLOR*Cscreen=(COLOR*)Pscreen;
	char Dir;
	WORD i,j;
	DWORD PpP;
	BYTE JMPL;
	WORD Rdius=15;
	DWORD Tick=0;
	
	settextcolor(BGR(STRUCTOR));
	settextstyle(90,0,"����");
	outtextxy((WinWidth - textwidth("��㻭���ʲô")) / 2, (WinHeight - textheight("0")) / 2, "��㻭���ʲô");
	setbkmode(TRANSPARENT);
	setfillstyle(BS_SOLID,NULL,NULL);
	
	

	
#define PSCR(_x,_y) Pscreen[(_x)+(_y)*WinWidth]
#define CSCR(_x,_y) Cscreen[(_x)+(_y)*WinWidth]
	TouchImage::BatchDraw();					//��ʼ������ͼ


	for(;;){

		++Tick;			//ʱ��仯
		while(MouseHit())	//��ȡ�����Ϣ
		{
			Msg=GetMouseMsg();
		}

		//�����Ϣ
		if(Msg.wheel){					//����
			Msg.wheel/=120;
			if(Rdius+Msg.wheel>1)
				Rdius+=Msg.wheel;
		}
		if(Msg.uMsg==WM_MBUTTONDBLCLK)	//�м�˫��
		{
			if(Msg.mkCtrl){
				for(i=0;i<WinWidth;i++)
					for(j=0;j<WinHeight;j++)
						if(PSCR(i,j)!=0)
							PSCR(i,j)=STRUCTOR;
			}
			else if(Msg.mkShift){
				for(i=0;i<WinWidth;i++)
					for(j=0;j<WinHeight;j++)
						if(PSCR(i,j)!=0)
							PSCR(i,j)=MAGMA;
			}
			else{
				for(i=0;i<WinWidth;i++)
					for(j=0;j<WinHeight;j++)
						if(PSCR(i,j)==STRUCTOR)
							PSCR(i,j)=0;
			}
		}
		else if(Msg.uMsg==WM_LBUTTONDBLCLK)	//���˫��
		{
			if(Msg.mkCtrl){
				for(i=0;i<WinWidth;i++)
					for(j=0;j<WinHeight;j++)
						PSCR(i,j)=0;
			}
			else{
				for(i=0;i<WinWidth;i++)
					for(j=0;j<WinHeight;j++)
						if(PSCR(i,j)==WATER)
							PSCR(i,j)=0;
			}
		}
		else if(Msg.uMsg==WM_RBUTTONDBLCLK)	//�Ҽ�˫��
		{
			if(Msg.mkCtrl){
				for(i=0;i<WinWidth;i++)
					for(j=0;j<WinHeight;j++)
						if(PSCR(i,j)==WHITE)
							PSCR(i,j)=0;
			}
			else{
				for(i=0;i<WinWidth;i++)
					for(j=0;j<WinHeight;j++)
						if(PSCR(i,j)==MAGMA)
							PSCR(i,j)=0;
			}
		}
		else if(Msg.mkLButton){				//�������
			setfillcolor(BGR(Msg.mkCtrl?DEVOURER:Msg.mkShift?PRODUCER_0:WATER));
			solidcircle(Msg.x,Msg.y,Rdius);
		}
		else if(Msg.mkMButton){				//�м�����
			
			setfillcolor(BGR(Msg.mkCtrl?WHITE:STRUCTOR));
			solidcircle(Msg.x,Msg.y,Rdius);
		}
		else if(Msg.mkRButton){				//�Ҽ�����
			setfillcolor(BGR(Msg.mkCtrl?SAND:MAGMA));
			solidcircle(Msg.x,Msg.y,Rdius);
		}
		

		//��ѩ
		PpP=rand()%(WinWidth*WinHeight>>1);
		if(Pscreen[PpP]==0)
			Pscreen[PpP]=WHITE;//��ѩ
		
		
		
		//�����໥����
		for(j=0;j<WinHeight;j++){
			for(i=0;i<WinWidth;i++){
				
				if(PSCR(i,j)==0)
					continue;
				if(PSCR(i,j)==STRUCTOR)
					continue;
				
				if(PSCR(i,j)==SAND){//��ɳ������
					if(j<WinHeight-1){
						if(PSCR(i,j+1)==WATER){
							PSCR(i,j)=WATER;
							PSCR(i,j+1)=SAND;
							continue;
						}
						else if(PSCR(i,j+1)==MAGMA){
							PSCR(i,j)=MAGMA;
							PSCR(i,j+1)=SAND;
							continue;
						}
					}
				}
				else if(PSCR(i,j)==PRODUCER_0||PSCR(i,j)==PRODUCER_1){
					if(Tick&0X40){
						PSCR(i,j)=PRODUCER_1;
						if(j>0&&j<WinHeight-1&&(PSCR(i,j-1)!=PRODUCER_0&&PSCR(i,j-1)!=PRODUCER_1)){
							PSCR(i,j+1)=PSCR(i,j-1);
						}
						//if(j>0&&j<WinHeight-1&&PSCR(i,j-1)!=0&&(PSCR(i,j-1)!=PRODUCER_0&&PSCR(i,j-1)!=PRODUCER_1)&&PSCR(i,j+1)==0&&Tick&1){
						//	PSCR(i,j+1)=PSCR(i,j-1);
						//}
					}
					else{
						PSCR(i,j)=PRODUCER_0;
					}
					continue;
				}
				else if(PSCR(i,j)==DEVOURER){
					if(j>0&&PSCR(i,j-1)!=0&&PSCR(i,j-1)!=STRUCTOR&&PSCR(i,j-1)!=PRODUCER_0&&PSCR(i,j-1)!=PRODUCER_1&&PSCR(i,j-1)!=DEVOURER)
						PSCR(i,j-1)=0;
					if(j<WinHeight-1&&PSCR(i,j+1)!=0&&PSCR(i,j+1)!=STRUCTOR&&PSCR(i,j+1)!=PRODUCER_0&&PSCR(i,j+1)!=PRODUCER_1&&PSCR(i,j+1)!=DEVOURER)
						PSCR(i,j+1)=0;
					if(i>0&&PSCR(i-1,j)!=0&&PSCR(i-1,j)!=STRUCTOR&&PSCR(i-1,j)!=PRODUCER_0&&PSCR(i-1,j)!=PRODUCER_1&&PSCR(i-1,j)!=DEVOURER)
						PSCR(i-1,j)=0;
					if(i<WinWidth-1&&PSCR(i+1,j)!=0&&PSCR(i+1,j)!=STRUCTOR&&PSCR(i+1,j)!=PRODUCER_0&&PSCR(i+1,j)!=PRODUCER_1&&PSCR(i+1,j)!=DEVOURER)
						PSCR(i+1,j)=0;
				}
				else if(PSCR(i,j)==MAGMA)
				{
					if(j>=WinHeight-1)
						continue;
					if(PSCR(i,j+1)==STRUCTOR){
						PSCR(i,j)=0;
						PSCR(i,j+1)=0;
						continue;
					}
					if(j>0&&PSCR(i,j-1)==WATER){
						PSCR(i,j)=SAND;
						PSCR(i,j-1)=SAND;
					}
					if(j<WinHeight-1&&PSCR(i,j+1)==WATER){
						PSCR(i,j)=SAND;
						PSCR(i,j+1)=SAND;
					}
					if(i>0&&PSCR(i-1,j)==WATER){
						PSCR(i,j)=SAND;
						PSCR(i-1,j)=SAND;
					}
					if(i<WinWidth-1&&PSCR(i+1,j)==WATER){
						PSCR(i,j)=SAND;
						PSCR(i+1,j)=SAND;
					}
					continue;
				}
				else if(PSCR(i,j)==WATER){//ˮ
					if(j>=WinHeight-1)
						continue;
					if(PSCR(i,j+1)!=0){//�·��ǿ�
						Dir=rand()%2?1:-1;//���ѡ��һ������
						if(i+Dir>=0&&i+Dir<=WinWidth-1&&PSCR(i+Dir,j)==0)//һ������Ϊ��
						{
							PSCR(i+Dir,j)=WATER;
							PSCR(i,j)=0;
						}
						else if(Dir=-Dir&&i+Dir>=0&&i+Dir<=WinWidth-1&&PSCR(i+Dir,j)==0)//����һ������Ϊ��
						{
							PSCR(i+Dir,j)=WATER;
							PSCR(i,j)=0;
						}
						continue;
					}
				}
				else if(Tick&0X08&&CSCR(i,j).R==CSCR(i,j).G&&CSCR(i,j).G==CSCR(i,j).B&&(j==WinHeight-1||
					(PSCR(i,j+1)!=0&&PSCR(i,j+1)!=PRODUCER_0&&PSCR(i,j+1)!=PRODUCER_1)))//ѩ����ˮ
				{
					if(CSCR(i,j).R>2)//�䰵
					{
						CSCR(i,j).R=CSCR(i,j).G=CSCR(i,j).B=CSCR(i,j).R-1;
					}
					else{//���ˮ������ʧ
						PSCR(i,j)=rand()&1?WATER:0;
					}
				}
			}
		}
			
		
		//��������
		for(i=0;i<WinWidth;i++)
			for(j=WinHeight-2;j>0;j--){
				if(PSCR(i,j)==0)
					continue;
				if(PSCR(i,j)==STRUCTOR)
					continue;
				if(PSCR(i,j)==PRODUCER_0||PSCR(i,j)==PRODUCER_1)
					continue;

				if(PSCR(i,j+1)==0){//�·��ǿ�
					JMPL=rand()%4+1;
					//����
					if(j+JMPL>=WinHeight-1)
						JMPL=WinHeight-j-1;
					switch(JMPL){
					case 4:if(PSCR(i,j+4)!=0)break;
					case 3:if(PSCR(i,j+3)!=0)break;
					case 2:if(PSCR(i,j+2)!=0)break;
					case 1:if(PSCR(i,j+1)!=0)break;
						PSCR(i,j+JMPL)=PSCR(i,j);
						PSCR(i,j)=0;
					}
					continue;
				}
				if(i>0&&PSCR(i-1,j)==0&&PSCR(i-1,j+1)==0)//����
				{
					PSCR(i-1,j)=PSCR(i,j);
					PSCR(i,j)=0;
				}
				else if(i<WinWidth-1&&PSCR(i+1,j)==0&&PSCR(i+1,j+1)==0)//����
				{
					PSCR(i+1,j)=PSCR(i,j);
					PSCR(i,j)=0;
				}
				else if(i>1&&PSCR(i-1,j)==0&&PSCR(i-2,j)==0&&PSCR(i-2,j+1)==0)
				{
					PSCR(i-1,j)=PSCR(i,j);
					PSCR(i,j)=0;
				}
				else if(i<WinWidth-2&&PSCR(i+1,j)==0&&PSCR(i+2,j)==0&&PSCR(i+2,j+1)==0)
				{
					PSCR(i+1,j)=PSCR(i,j);
					PSCR(i,j)=0;
				}
			}
			
			TouchImage::FlushDraw();	//�ػ�
			Sleep(5);					//�ͷ�CPU
	}
	TouchImage::BatchDraw();//����������ͼ
	TouchImage::Closegraph();//�رմ���
	
	return 0;
}



