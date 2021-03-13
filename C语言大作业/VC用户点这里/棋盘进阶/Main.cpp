#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<time.h>
#pragma comment ( lib, "Winmm.lib" )//播放音乐用的

#define W 676

void shuaxin(int *a);
void startup();
void fx(int i, int x, int y);
void show();
void change(int input);
void play();
boolean again();
void getscore();
void setscore();
void showinfo();

IMAGE back, replay, win, lose, info;
MOUSEMSG mouse;

int a[10];//棋盘全局变量便于操作
int step[10];// 刷新棋盘的步骤 
int ischeat = 0;//作弊
int count = 0;//步数
int  wintime = 0;
int  losetime = 0;
//赢和输的次数
int w1 = 0, w2 = 0, w3 = 0, l1 = 0, unknow = 0;
//赢得成就123，输的，未知领域

void showinfo() {
	putimage(0, 0, &info);
	//成就
	{
		if (w1)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 30, 30);
		if (w2)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 130, 30);
		if (w3)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 238, 30);
		if (l1)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 350, 30);
		if (unknow)
			setfillcolor(RGB(141, 233, 113));
		else
			setfillcolor(RGB(255, 114, 118));
		fillcircle(240, 467, 30);
	}
	//分数
	{
		settextstyle(100, 0, _T("华文行楷"));
		settextcolor(RGB(255, 255, 255));
		TCHAR a[5], b[5];
		sprintf(a, "%d", wintime);//将整形a转换成字符串
		outtextxy(44, 166, a);
		sprintf(b, "%d", losetime);//将整形a转换成字符串
		outtextxy(44, 508, b);
	}
	//作弊
	{
		if (ischeat) {
			settextstyle(80, 0, _T("华文行楷"));
			settextcolor(RGB(255, 255, 255));
			TCHAR s[15] = { '\0' }, t[15];
			//sprintf(s,"step");//将整形数组step转换成字符串
			for (int i = 0; i < 10; i++) {
				sprintf(t, "%d", step[i]);//每步放到中间变量t中
				strcat(s, t);//切到s里
			}
			outtextxy(233, 580, s);
		}
	}
	FlushBatchDraw();
}
//展示成就和作弊和胜利失败数
void getscore() {
	FILE * fp;
	fp = fopen("rec/score.txt", "r");
	if (fp == NULL) {
		fp = fopen("rec/score.txt", "w");
		fprintf(fp, "%d %d", wintime, losetime);
	}
	else
		fscanf(fp, "%d %d", &wintime, &losetime);

	fclose(fp);
}
//从文件内获取分数并写入wintime和losetime
void setscore() {
	FILE * fp;
	fp = fopen("rec/score.txt", "w");
	fprintf(fp, "%d %d", wintime, losetime);
	fclose(fp);
}
//写入wintime和losetime
boolean again() {
	HWND window = GetHWnd();//获取窗口
	SetWindowText(window, _T("重生室"));//设置窗口标题

	cleardevice();//清空之前所暂留的内容
	putimage(0, 0, &replay);//repaly的图片
	FlushBatchDraw();
	//long timeend,time ;
	//settextstyle(100, 0, _T("楷体"));
	//setcolor(RGB(255, 255, 255));
	TCHAR s[5];
	while (true)//循环实现
	{
		mouse = GetMouseMsg();
		if (mouse.mkLButton) {
			if (mouse.x > 50 && mouse.y > 450 && mouse.x < 200 && mouse.y < 600)
				return false;
			//返回假不进行exit操作函数
			//继续主函数的内容
			if (mouse.x > 470 && mouse.y > 450 && mouse.x < 600 && mouse.y < 600)
				return true;
			//返回真进行exit
		}
		//time做倒计时确实难哪来的思路a 
	}
}
//重新再来的界面
void startup() {
	initgraph(W, W);
	setbkcolor(RGB(32, 13, 6));//不要问为什么是这个颜色问就是曲线救国again

	loadimage(&win, "rec/win.jpg");
	loadimage(&lose, "rec/lose.jpg");
	loadimage(&back, "rec/back.jpg");
	loadimage(&replay, "rec/replay.jpg");
	loadimage(&info, "rec/info.jpg");
	//加载图片
	mciSendString("open rec/bg.mp3 alias bgmusic", NULL, 0, NULL);
	mciSendString("play bgmusic repeat", NULL, 0, NULL);
	//开始播放背景音乐（循环）
	getscore();
	//拿分
	BeginBatchDraw();
	//开始批量画图
}
//初始化
void fx(int i, int x, int y) {
	if (a[i] == -1) {
		setfillcolor(RGB(255, 255, 255));
		setcolor(RGB(0, 0, 0));
	}
	//-1是白色球黑色边
	else {
		setfillcolor(RGB(0, 0, 0));
		setcolor(RGB(255, 255, 255));
	}
	//其他是黑球白边
	fillcircle(x, y, 55);
	//画个圆
}
//棋子颜色
void show() {
	putimage(0, 0, &back);
	//背景图片棋盘
	fx(1, 205, 205);
	fx(2, 335, 205);
	fx(3, 469, 205);
	fx(4, 205, 335);
	fx(5, 335, 335);
	fx(6, 469, 335);
	fx(7, 205, 469);
	fx(8, 335, 469);
	fx(9, 469, 469);
}
//画棋子 
void change(int input) {
	switch (input) {
	case '1':
	case 1://生成棋盘和play时所用的不一样一个是getch一个是数所以写了两个这东西来对应 
		a[1] *= -1;
		a[2] *= -1;
		a[4] *= -1;
		break;
	case '2':
	case 2:
		a[2] *= -1;
		a[1] *= -1;
		a[3] *= -1;
		a[5] *= -1;
		break;
	case '3':
	case 3:
		a[3] *= -1;
		a[2] *= -1;
		a[6] *= -1;
		break;
	case '4':
	case 4:
		a[4] *= -1;
		a[1] *= -1;
		a[5] *= -1;
		a[7] *= -1;
		break;
	case '5':
	case 5:
		a[5] *= -1;
		a[2] *= -1;
		a[4] *= -1;
		a[6] *= -1;
		a[8] *= -1;
		break;
	case '6':
	case 6:
		a[6] *= -1;
		a[3] *= -1;
		a[5] *= -1;
		a[9] *= -1;
		break;
	case '7':
	case 7:
		a[7] *= -1;
		a[4] *= -1;
		a[8] *= -1;
		break;
	case '8':
	case 8:
		a[8] *= -1;
		a[5] *= -1;
		a[7] *= -1;
		a[9] *= -1;
		break;
	case '9':
	case 9:
		a[9] *= -1;
		a[6] *= -1;
		a[8] *= -1;
	}
}
//更改棋盘
void shuaxin(int *a) {
	for (int i = 1; i < 10; i++)
		a[i] = -1;
	//遍历全为-1（也就是成功）
	srand((unsigned)time(NULL));
	//时间做种
	for (int i = 0; i < 10; i++) {
		int suiji = rand() % 9 + 1;
		//1-9随机取值
		step[i] = suiji;
		change(suiji);
		//对成功棋盘随机点击10次保证15次内可以出解
	}
	for (int i = 0; i < 5; i++)	//逆序数组便于作弊
	{
		int p;
		p = step[i];
		step[i] = step[10 - i - 1];
		step[10 - 1 - i] = p;
	}
}
//生成新的棋盘
void play() {
	count = 0;
	//走过的次数
	while (true)
	{
		HWND window = GetHWnd();//获取窗口
		SetWindowText(window, _T("变换棋"));//设置窗口标题

		FlushBatchDraw();
		//对上一帧刷新
		show();
		//调用函数画棋子
		if (count >= 15) {//判断是否死亡	
			count = 0;
			ischeat = 0;
			//初始化
			losetime++;
			//死亡次数将来用文件取代
			putimage(0, 0, &lose);
			//展示失败图片
			FlushBatchDraw();
			//画帧
			Sleep(1000);
			if (again()) {
				setscore();
				exit(0);
			}
			else
				return;
		}
		int winflag = 0;
		for (int i = 1; i < 10; i++) {
			if (a[i] == -1)
				winflag++;
		}// 9个格子都是-1
		if (winflag == 9) {
			winflag = 0;
			ischeat = 0;
			//初始化
			wintime++;
			//胜利次数加一
			putimage(0, 0, &win);
			//赢得图片
			FlushBatchDraw();
			//刷新帧
			Sleep(1000);
			if (again()) {
				setscore();
				exit(0);
			}
			else
				return;
		}
		mouse = GetMouseMsg();
		//循环获取鼠标操作无需mousehit
		switch (mouse.uMsg) {
		case WM_LBUTTONDOWN:
		{
			if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 136 && mouse.y <= 272))
				change(1);
			if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 136 && mouse.y <= 272))
				change(2);
			if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 136 && mouse.y <= 272))
				change(3);

			if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 273 && mouse.y <= 408))
				change(4);
			if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 273 && mouse.y <= 408))
				change(5);
			if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 273 && mouse.y <= 408))
				change(6);

			if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 409 && mouse.y <= 544))
				change(7);
			if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 409 && mouse.y <= 544))
				change(8);
			if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 409 && mouse.y <= 544))
				change(9);
			FlushBatchDraw();
			count++;
			//步数加一
			mciSendString("close click", NULL, 0, NULL);
			mciSendString("open rec/click.mp3 alias click", NULL, 0, NULL);
			mciSendString("play click", NULL, 0, NULL);
			//播放一遍点击声音
		}
		break;
		case WM_RBUTTONDOWN:
			showinfo();
			break;
		case WM_MBUTTONDOWN:
			ischeat = 1;//鼠标中键作弊模式
			unknow = 1;
			break;
		}
		/*if (mouse.mkRButton) {
			//右键按下
			showinfo();
		}

		if (mouse.mkLButton) {
			//左键按下
			//if (mouse.uMsg == WM_LBUTTONDOWN)
			{
				if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 136 && mouse.y <= 272))
					change(1);
				if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 136 && mouse.y <= 272))
					change(2);
				if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 136 && mouse.y <= 272))
					change(3);

				if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 273 && mouse.y <= 408))
					change(4);
				if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 273 && mouse.y <= 408))
					change(5);
				if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 273 && mouse.y <= 408))
					change(6);

				if ((mouse.x >= 136 && mouse.x <= 272) && (mouse.y >= 409 && mouse.y <= 544))
					change(7);
				if ((mouse.x >= 273 && mouse.x <= 408) && (mouse.y >= 409 && mouse.y <= 544))
					change(8);
				if ((mouse.x >= 409 && mouse.x <= 544) && (mouse.y >= 409 && mouse.y <= 544))
					change(9);
				FlushBatchDraw();
				count++;
				//步数加一
				mciSendString("close click", NULL, 0, NULL);
				mciSendString("open rec/click.mp3 alias click", NULL, 0, NULL);
				mciSendString("play click", NULL, 0, NULL);
				//播放一遍点击声音
			}
		}

		if (mouse.mkMButton) {
			ischeat = 1;//鼠标中键作弊模式
			unknow = 1;
		}*/


		if (wintime >= 10)
			w1 = 1;
		if (wintime >= 50)
			w2 = 1;
		if (wintime >= 100)
			w3 = 1;
		if (losetime >= 100)
			l1 = 1;

		if (kbhit())
		{
			int input;
			input = getch();
			if (input == 27) {//结束
				setscore();
				exit(0);
			}
		}
	}
}
//开始游戏（包括但不限于失败、成功判断，棋盘点击实现
int main() {
	startup();
	while (true)
	{
		shuaxin(a);
		show();
		play();
		setscore();
		//每次循环都写入文件
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
//主函数