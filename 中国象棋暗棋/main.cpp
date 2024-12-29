#include <graphics.h>
#include <conio.h>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <list>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>

#pragma comment(lib, "winmm.lib")

#define BUFFSIZE 1024

using namespace std;

class Qizi {
public:
	int imgflag;					// imgflag，从map中选择图片
	bool killed;					// 已经被杀
	bool hide;						// 反转状态
	bool isRed;						// 红方还是黑方
	int qizi;						// 棋子类型，0-6,将士相车马炮卒
	IMAGE img;						// 存储img
};

map <int, string>img_map = {
	{0,".\\Image\\qipan.png"},

	{1,".\\Image\\jiang_black.png"},
	{2,".\\Image\\shi_black.png"},
	{3,".\\Image\\xiang_black.png"},
	{4,".\\Image\\che_black.png"},
	{5,".\\Image\\ma_black.png"},
	{6,".\\Image\\pao_black.png"},
	{7,".\\Image\\zu_black.png"},

	{8,".\\Image\\jiang_red.png" },
	{9,".\\Image\\shi_red.png"},
	{10,".\\Image\\xiang_red.png"},
	{11,".\\Image\\che_red.png"},
	{12,".\\Image\\ma_red.png"},
	{13,".\\Image\\pao_red.png"},
	{14,".\\Image\\zu_red.png"},


	{29,".\\Image\\back.png"},
	{30,".\\Image\\null.png"}
};

IMAGE qipan;
Qizi qizi[32];
int black_num = 16, red_num = 16;

// 1号和2号与黑棋红棋的对应关系
bool firstmode[2];
int step = 0;
// 有没有点击
bool startmode = true;

int prevCheckNum = -1;


TCHAR* Transform(string s) {
	TCHAR result[BUFFSIZE];
	char c[BUFFSIZE];
	strcpy_s(c, s.c_str());
	MultiByteToWideChar(CP_ACP, 0, c, -1, result, BUFFSIZE);
	return result;
}

void random_qizi()
{
	srand(time(0));
	for (int i = 31; i > 0; i--) {
		int j = rand() % 32;
		Qizi tmp = qizi[i];
		qizi[i] = qizi[j];
		qizi[j] = tmp;
	}
}

void init()
{
	for (int i = 0; i < 32; i++) {
		qizi[i].hide = true;
		qizi[i].killed = false;
		if (i <= 15)
			qizi[i].isRed = false;
		else
			qizi[i].isRed = true;
	}
	qizi[0].imgflag = 1;	qizi[0].qizi = 0;
	qizi[1].imgflag = 2;	qizi[1].qizi = 1;
	qizi[2].imgflag = 2;	qizi[2].qizi = 1;
	qizi[3].imgflag = 3;	qizi[3].qizi = 2;
	qizi[4].imgflag = 3;	qizi[4].qizi = 2;
	qizi[5].imgflag = 4;	qizi[5].qizi = 3;
	qizi[6].imgflag = 4;	qizi[6].qizi = 3;
	qizi[7].imgflag = 5;	qizi[7].qizi = 4;
	qizi[8].imgflag = 5;	qizi[8].qizi = 4;
	qizi[9].imgflag = 6;	qizi[9].qizi = 5;
	qizi[10].imgflag = 6;	qizi[10].qizi = 5;
	qizi[11].imgflag = 7;	qizi[11].qizi = 6;
	qizi[12].imgflag = 7;	qizi[12].qizi = 6;
	qizi[13].imgflag = 7;	qizi[13].qizi = 6;
	qizi[14].imgflag = 7;	qizi[14].qizi = 6;
	qizi[15].imgflag = 7;	qizi[15].qizi = 6;

	qizi[16].imgflag = 8;	qizi[16].qizi = 0;
	qizi[17].imgflag = 9;	qizi[17].qizi = 1;
	qizi[18].imgflag = 9;	qizi[18].qizi = 1;
	qizi[19].imgflag = 10;	qizi[19].qizi = 2;
	qizi[20].imgflag = 10;	qizi[20].qizi = 2;
	qizi[21].imgflag = 11;	qizi[21].qizi = 3;
	qizi[22].imgflag = 11;	qizi[22].qizi = 3;
	qizi[23].imgflag = 12;	qizi[23].qizi = 4;
	qizi[24].imgflag = 12;	qizi[24].qizi = 4;
	qizi[25].imgflag = 13;	qizi[25].qizi = 5;
	qizi[26].imgflag = 13;	qizi[26].qizi = 5;
	qizi[27].imgflag = 14;	qizi[27].qizi = 6;
	qizi[28].imgflag = 14;	qizi[28].qizi = 6;
	qizi[29].imgflag = 14;	qizi[29].qizi = 6;
	qizi[30].imgflag = 14;	qizi[30].qizi = 6;
	qizi[31].imgflag = 14;	qizi[31].qizi = 6;
}

void load()
{
	// 加载棋盘
	loadimage(&qipan, Transform(img_map[0]), 450, 850, 1);

	for (int i = 0; i < 32; i++) {
		// 被杀该位置加载空子
		if (qizi[i].killed) {
			loadimage(&qizi[i].img, Transform(img_map[30]), 100, 100, 1);
			continue;
		}
		// 隐藏位置加载
		if (qizi[i].hide) {
			loadimage(&qizi[i].img, Transform(img_map[29]), 100, 100, 1);
			continue;
		}
		// 其他的根据imgflag加载
		loadimage(&qizi[i].img, Transform(img_map[qizi[i].imgflag]), 100, 100, 1);
	}
}
void rectangle_by_num(int num, int mode)
{
	int l, t, r, b;
	int col, row;
	col = num / 4;
	row = num % 4;

	l = row * 100 + 26;
	t = col * 100 + 26;
	r = (row + 1) * 100 + 25;
	b = (col + 1) * 100 + 25;

	if (num >= 0 && num <= 31) {
		if (mode == 1) {
			rectangle(l, t, r, b);
		}
		else {
			clearrectangle(l, t, r, b);
		}
	}
}
void put()
{
	cleardevice();
	putimage(0, 0, &qipan);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 8; y++) {
			putimage(x * 100 + 25, y * 100 + 25, &qizi[y * 4 + x].img);
		}
	}

	if (prevCheckNum != -1) {
		rectangle_by_num(prevCheckNum,true);
	}
}



int get_click_num(int x, int y)
{
	int num = -1;
	int col = -1, row = -1;

	if (x > 25 && x < 125)col = 0;
	if (x > 125 && x < 225)col = 1;
	if (x > 225 && x < 325)col = 2;
	if (x > 325 && x < 425)col = 3;

	if (y > 25 && y < 125)row = 0;
	if (y > 125 && y < 225)row = 1;
	if (y > 225 && y < 325)row = 2;
	if (y > 325 && y < 425)row = 3;
	if (y > 425 && y < 525)row = 4;
	if (y > 525 && y < 625)row = 5;
	if (y > 625 && y < 725)row = 6;
	if (y > 725 && y < 825)row = 7;

	if (row != -1 && col != -1)num = 4 * row + col;
	return num;
}



bool check_num_can_go(int cur_num)
{
	bool hasPos = false;
	bool hasEat = false;
	// 如果选中的是炮
	if (qizi[prevCheckNum].qizi == 5) {
		list<int> lst;
		// 获取左边
		int col, row;
		col = prevCheckNum / 4;
		row = prevCheckNum % 4;
		
		// 左边
		int hasFlag = false;
		for (int i = prevCheckNum - 1; i >= col * 4; i--) {
			if (hasFlag && !qizi[i].killed) {
				lst.push_back(i);
				break;
			}
			if (!qizi[i].killed)hasFlag = true;
		}
		// 右边
		hasFlag = false;
		for (int i = prevCheckNum + 1; i <= (((col+1) * 4) - 1); i++) {
			if (hasFlag && !qizi[i].killed) {
				lst.push_back(i);
				break;
			}
			if (!qizi[i].killed)hasFlag = true;
		}
		// 上面
		hasFlag = false;
		for (int i = prevCheckNum - 4; i >= 0; i -= 4) {
			if (hasFlag && !qizi[i].killed) {
				lst.push_back(i);
				break;
			}
			if (!qizi[i].killed)hasFlag = true;
		}
		// 下边
		hasFlag = false;
		for (int i = prevCheckNum + 4; i <= 31; i += 4) {
			if (hasFlag && !qizi[i].killed) {
				lst.push_back(i);
				break;
			}
			if (!qizi[i].killed)hasFlag = true;
		}

		// 如果cur_num存在
		if (std::find(lst.begin(), lst.end(), cur_num) != lst.end()) {
			hasPos = true;
		}

		if (hasPos) {
			// 如果目标是翻面的
			if (qizi[cur_num].hide) {
				hasEat = true;
			}
			else {
				// 如果两个不同阵营
				if (qizi[cur_num].isRed != qizi[prevCheckNum].isRed) {
					hasEat = true;
				}
			}
		}
	}
	else {
		// 如果选中的不是炮
		list<int> lst = { prevCheckNum - 1,prevCheckNum + 1 ,prevCheckNum - 4,prevCheckNum + 4 };
		// 如果cur_num存在
		if (std::find(lst.begin(), lst.end(), cur_num) != lst.end()) {
			hasPos = true;
		}
		if (hasPos) {
			// 如果目标为空
			if (qizi[cur_num].killed) {
				hasEat = true;
			}
			else {
				// 如果目标不是翻面
				if (!qizi[cur_num].hide) {
					// 如果两者不同阵营
					if (qizi[cur_num].isRed != qizi[prevCheckNum].isRed) {
						// 判断大小
						switch (qizi[prevCheckNum].qizi)
						{
						case 0:// 如果先前选中的是将
							// 目标不能是卒
							if (qizi[cur_num].qizi != 6) {
								hasEat = true;
							}
							break;
						case 1:case 2:case 3:case 4:
							// 士 相 车 马能吃类型比它小的
							if (qizi[cur_num].qizi >= qizi[prevCheckNum].qizi) {
								hasEat = true;
							}
							break;
						case 6:
							// 兵 只能吃将和卒
							if (qizi[cur_num].qizi == 0 || qizi[cur_num].qizi == 6) {
								hasEat = true;
							}
						default:
							break;
						}
					}
				}
			}
		}

	}

	if (hasPos && hasEat) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	ExMessage m;

	initgraph(450, 850);
	init();
	load();
	mciSendString(TEXT("open .\\Music\\bg.wav alias bgmusic"), NULL, 0, NULL);
	mciSendString(TEXT("play bgmusic"), NULL, 0, NULL);

	bool hasClickStart = false;
	// 开始游戏点击
	putimage(0, 0, &qipan);
	RECT r = { 30,300,399,449 };
	setfillcolor(0x489be1);
	setbkcolor(0x489be1);
	fillrectangle(50,300,400,450);
	settextstyle(60, 0,_T("黑体"));
	drawtext(_T("开始游戏"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	while (!hasClickStart) {
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x >= 30 && m.x <= 400 && m.y >= 300 && m.y <= 450) {
				hasClickStart = true;
			}

		}
	}
	random_qizi();


	put();
	
	while (true)
	{
		// 获取一条鼠标或按键消息
		m = getmessage(EX_MOUSE | EX_KEY);

		switch (m.message)
		{

		case WM_LBUTTONDOWN:
			int cur_num = get_click_num(m.x, m.y);
			
			if (prevCheckNum == -1) {
				// 翻转
				if (qizi[cur_num].hide) {
					// 根据第一个翻出来的棋子判断谁黑谁红
					if (startmode) {
						// 获取第一个翻得是红棋还是黑棋
						firstmode[0] = qizi[cur_num].isRed;
						firstmode[1] = !firstmode[0];
						startmode = false;
					}
					step++;

					qizi[cur_num].hide = false;
					mciSendString(TEXT("open .\\Music\\move.wav alias mv"), NULL, 0, NULL);
					mciSendString(TEXT("play mv"), NULL, 0, NULL);
					Sleep(100);
					mciSendString(TEXT("close mv"), NULL, 0, NULL);
				}
				else {
					if (!qizi[cur_num].killed) {
						int cur_user = step % 2;
						if (firstmode[cur_user] == qizi[cur_num].isRed) {
							prevCheckNum = cur_num;
						}
					}
				}
			}
			else {
				if (prevCheckNum == cur_num) {
					// 取消选中
					prevCheckNum = -1;
				}
				else {
					if (check_num_can_go(cur_num)) {
						mciSendString(TEXT("open .\\Music\\move.wav alias mv"), NULL, 0, NULL);
						mciSendString(TEXT("play mv"), NULL, 0, NULL);
						Sleep(100);
						mciSendString(TEXT("close mv"), NULL, 0, NULL);
						qizi[cur_num].hide = false;
						qizi[cur_num].killed = true;
						Qizi tmp = qizi[cur_num];
						qizi[cur_num] = qizi[prevCheckNum];
						qizi[prevCheckNum] = tmp;	
						prevCheckNum = -1;
						step++;
					}
				}
			}

			load();
			put();
			break;
		}

		
	}
	mciSendString(TEXT("close bgmusic"),NULL,0,NULL);
	closegraph();
	return 0;
}
