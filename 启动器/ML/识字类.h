#pragma once
#include <string>

using namespace std;

struct 识字坐标
{
	int x1, y1, x2, y2;
};
class 识字类
{
private:
	识字坐标 AUTO = { 1218,532,1254,552 };
	
	HRESULT hr;
	IDispatch* pDispatch;
	DISPID dispid;
	
public:
	HMODULE LoadDll();
public:
	//示例 识字坐标 字符 = { 0,0,0,0 };
	识字坐标 跳过 = { 1181,58,1216,77 };
	识字坐标 装备坐骑 = { 1014,103,1067,121};
	识字坐标 任务 = { 1014,103,1067,121 };
	/*滑翔翼，坐骑穿戴*/
	识字坐标 穿戴 = { 1158,706,1197,727 }; 
	识字坐标 添加 = { 1158,706,1197,727 };
	识字坐标 装备穿戴 = { 994,463,1020,477 };
	识字坐标 瞬间移动 = {588,269,649,286};
	识字坐标 购买 = { 865,547,903,567 };
	识字坐标 请点击画面 = { 611, 559, 685, 577 };
	识字坐标 武器外形穿戴 = { 1112, 706,1149 , 727 };
	识字坐标 节电模式 = { 639, 140,703 , 158 };
	识字坐标 复活 = { 1161,699,1200,722 };
	识字坐标 小地图_阿维利乌斯城堡 = { 67,84,149,101 };
	识字坐标 小地图_杂货 = { 55,94,84,110 };
	识字坐标 背包 = { 1167,89,1207,110 };
	识字坐标 背包技能书说明 = { 794,121,959,191 };
	识字坐标 主动技能 = { 1094,89,1170,112 };
	识字坐标 技能排序自动释放 = { 199,613,223,632 };
	识字坐标 猎人_决心技能自动开启 = { 1154,356,1180,371 };
	识字坐标 死亡骑士 = { 609,37,669,57 };
	识字坐标 快捷栏药品数量 = { 907,709,934,726 };
	识字坐标 大地图_世界 = { 623,704,657,724 };
	识字坐标 杂货商人 = { 62,42,144,68 };
	识字坐标 结束游戏 = { 625,351,687,370 };
	识字坐标 职业 = { 62,45,105,67 };
	识字坐标 接受任务 = { 1166,105,1194,121 };
	识字坐标 背包物品名称 = { 803,130,950,175 };
	识字坐标 自动开启吃药 = { 906,412,928,425 };
	识字坐标 强化确认弹窗 = { 237,725,295,742 };
	识字坐标 强化最大安全阶段 = { 280,724,338,742 };
	识字坐标 技能书商人 = { 61,43,164,164 };
	识字坐标 技能_失明 = { 1042,556,1075,575 };
	识字坐标 弓箭手_决心开启 = { 1158,193,1180,206 };
	识字坐标 弓箭手_精准射击开启 = { 1157,256,1181,270 };
	识字坐标 弓箭手_开始狩猎开启 = { 1158,321,1180,334 };
	识字坐标 弓箭手_侵蚀技能 = { 1042,528,1075,548 };
	识字坐标 等级 = { 16,701,52,729 };
	识字坐标 修炼之林 = { 64,85,111,99 };
	IDispatch* COM初始化();

	bool 查找跳过();
	bool 查找装备坐骑();
	bool 查找穿戴();
	bool 查找装备穿戴();
	bool 查找添加();
	bool 查找瞬间移动();
	bool 查找购买();
	bool 查找请点击画面();
	bool 查找武器外形穿戴();
	bool 查找节电模式();
	bool 查找复活();
	bool 查找小地图_阿维利乌斯城堡();
	bool 查找小地图_杂货();
	bool 查找背包();
	bool 查找背包技能书说明();
	bool 查找主动技能();
	bool 查找技能排序自动释放();
	bool 查找猎人_决心技能自动开启();
	bool 查找死亡骑士();
	int  查找快捷栏药品数量();
	bool 查找大地图_世界();
	bool 查找杂货商人();
	bool 查找结束游戏();
	bool 查找职业();
	bool 查找接受任务();
	bool 查找自动开启吃药();
	bool 查找强化确认弹窗();
	bool 查找强化最大安全阶段();
	bool 查找技能书商人();
	bool 查找技能_失明();
	bool 查找弓箭手_决心开启();
	bool 查找弓箭手_精准射击开启();
	bool 查找弓箭手_开始狩猎开启();
	bool 查找弓箭手_侵蚀技能();
	int 查找等级();
	std::wstring 获取背包物品名称();
	std::wstring 获取字符(识字坐标 坐标, DOUBLE sim=0.5);
};

