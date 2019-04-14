//
//  main.cpp
//  game
//
//  Created by xujin liu on 2019/2/10.
//  Copyright © 2019 xujin liu. All rights reserved.
//
#include <stdlib.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<fstream>
using namespace std;
struct datemob
{
    string name;
    int hp;
    int att;
    int def;
};
string User_name;//用于存放用户名。
string item_name[100]={"木头","铜矿","煤炭","小型魔法水晶","木棍","铜","锡矿"};
int  item_num[100];
string tool_name[20]={" ","1.铜质长剑","2.铜质战斧","3.简易法杖"};
string tool_name_1[20]={" ","铜质长剑","铜质战斧","简易法杖"};
string tool_show[20]={" ","攻击力+5","攻击力+8","法强+5"};
int  tool_num[20];
int tool_att[20]={0,5,8,1};
int tool_att_mana[20]={0,0,0,5};
int pass_level=1;
struct datemob mob[1000];

string mob_name[99]={" ","史莱姆","地鼠","狼","熊","巨象","剑龙","红色史莱姆","橙色史莱姆","黄色史莱姆","绿色史莱姆","粉色史莱姆","紫色史莱姆","青色史莱姆","黑色史莱姆","白色史莱姆","灰色史莱姆"} ;
int mob_hp[20]={100000,10,15,20,40,60,50,20,20,20,20,20,20,20,20,20,20};
int mob_att[20]={100000,5,3,8,10,6,7,5,5,5,5,5,5,5,5,5,5};
int mob_def[20]={100000,0,0,1,2,3,2,1,1,1,1,1,1,1,1,1,1};
int mob_expget[20]={100000,10,10,20,40,40,40,10,10,10,10,10,10,10,10,10,10};
string boss_name[5]={"史莱姆王"};
int hero_hp_game,hero_attact_base=5;
int hero_mana=50,hero_mana_game;
int hero_mana_att=0;
int hero_tool=0;
string mana_skill_name[5]={"法术冲击（无属性）"};
string mana_skill_name1[5]={"1.法术冲击（无属性）消耗20点法术值"};
int mana_needed[5]={20};
int mana_attack_skill[5]={10};
int mana_skill_studied[5]={0};
int coin=0,exp=0;
int input;
int shibai=0;
int slime=0;//猜猜这个变量是干什么的
ifstream fin("cundang.txt");
ofstream fout("cundang.txt");
//----------------------以下为可能调用的部分函数-------------------------------
int level()
{
    int a;
    if(exp<=50)
        a=1;
    else if(exp<=100)
        a=2;
    else if (exp<=200)
        a=3;
    else if (exp<=500)
        a=4;
    else if (exp<=1000)
        a=5;
    else if (exp<=1500)
        a=6;
    else if (exp<=2000)
        a=7;
    else if (exp<=2500)
        a=8;
    else if (exp<=3000)
        a=9;
    else
        a=10;
    return a;
}

//--------------------------血量计算---------------------------------------
int hero_hp()
{
    return 20*level()+130;
}
//----------------------攻击力计算------------------------------------------
int hero_attact()
{
    return 3+2*level()+tool_att[hero_tool];
}
//----------------------魔法伤害计算------------------------------------

double mana_attact(int skill_kind)
{
    int a=rand()%10-6;
    return hero_mana_att+level()*5+mana_attack_skill[skill_kind]+tool_att_mana[hero_tool]+a;
}

//----------------------武器库-------------------------------------------

void tool_pack()
{
    for(int i=0;i<=20;i++)
    {
        if(tool_num[i]!=0){
            cout<<tool_name[i]<<":"<<tool_show[i];
            if (hero_tool==i) {
                cout<<" 已装备";
            }
            cout<<endl;
        }
    }
    cout<<"请问您要装备的是(摁0退出)";
    cin>>input;
    if (tool_num[input]!=0)
    {
        hero_tool=input;
        cout<<"装备成功"<<endl;
    }
    else if(input!=0)
    {
        cout<<"你还没有这种武器哦"<<endl;
    }
}
//-------------------------法术学习----------------------------------------
void mana_study()
{
    while (true) {
        cout<<"欢迎来到魔法屋"<<endl;
        cout<<"现在可供学习的法术有"<<endl;
        if (level()>=5) {
            cout<<mana_skill_name[0];
            if (mana_skill_studied[0]==1) {
                cout<<"（已学习）";}
            else {
                cout<<"学习花费：金币x500，小型魔法水晶x10  学习条件：拥有简易法杖，等级>=5";
            }
            cout<<endl;
        }
        
        cout<<"您要学习的是";
        cin>>input;
        if(input==1)
        {
            if (mana_skill_studied[0]!=1&&item_num[3]>=10&&coin>=500&&tool_num[3]>=1) {
                coin-=500;
                item_num[3]-=10;
                mana_skill_studied[0]=1;
                cout<<"学习成功"<<endl;
            }
            else if (mana_skill_studied[0]==1){
                cout<<"您已经学习过了哦"<<endl;
            }
            else if(item_num[3]<10||coin<500||tool_num[3]==0){
                cout<<"材料不够"<<endl;
            }
            
        }
        if (input==0) {
            break;
        }
    }
}

//=====================一个不知道有没有必要的h属性查看模块=======================
void looker()
{
    cout<<"人物属性"<<endl;
    cout<<"玩家姓名:"<<User_name<<endl;
    cout<<"等级"<<level()<<endl;
    cout<<"血量:"<<hero_attact()<<endl;
    cout<<"战斗力（物理）:"<<hero_attact()<<endl;
    if(level()>=5)
        cout<<"战斗力（魔法）:"<<hero_mana_att+level()*5+tool_att_mana[hero_tool]<<endl;
    cout<<"金币:"<<coin<<endl;
}

//----------------------合成模块--------------------------------------------
void compose()
{
    //"木头","铜矿","煤炭","小型魔法水晶","木棍","铜"
    //system("cls");
    while(true)
    {
        cout<<"欢迎来到合成工坊"<<endl;
        cout<<"1,铜  材料:木炭x1,铜矿x2"<<endl;
        cout<<"2,木棍x4  材料:木头x1"<<endl;
        cout<<"3,铜制长剑  材料:铜x10,木棍x4,木炭x2"<<endl;
        cout<<"4,铜制战斧  材料:铜x15,木棍x8,木炭x3"<<endl;
        cout<<"5,简易法杖  材料:小型魔法水晶x2，木棍x2"<<endl;
        cout<<"输入0退出"<<endl;
        cout<<"您要合成的是";
        cin>>input;
        if(input==5)
        {
            if(item_num[3]>=2&&item_num[4]>=2)
            {
                cout<<"合成成功,获得简易法杖."<<endl;
                item_num[3]-=2;
                item_num[4]-=2;
                tool_num[3]+=1;
            }
            else
                cout<<"材料不足"<<endl;
            system("pause");
        }
        if(input==4)
        {
            if(item_num[5]>=15&&item_num[4]>=8&&item_num[2]>=3)
            {
                cout<<"合成成功,获得铜制战斧."<<endl;
                item_num[5]-=15;
                item_num[4]-=8;
                item_num[2]-=3;
                tool_num[2]+=1;
            }
            else
                cout<<"材料不足"<<endl;
            system("pause");
        }
        if(input==3)
        {
            if(item_num[5]>=10&&item_num[4]>=4&&item_num[2]>=2)
            {
                cout<<"合成成功,获得铜制长剑."<<endl;
                item_num[5]-=10;
                item_num[4]-=4;
                item_num[2]-=2;
                tool_num[1]+=1;
            }
            else
                cout<<"材料不足"<<endl;
            system("pause");
        }
        
        if(input==2)
        {
            if(item_num[0]>=1)
            {
                cout<<"合成成功,获得木棍x4"<<endl;
                item_num[0]-=1;
                item_num[4]+=4;
            }
            else
                cout<<"材料不足"<<endl;
            system("pause");
        }
        if(input==1)
        {
            if(item_num[2]>=1&&item_num[1]>=2)
            {
                cout<<"合成成功,获得铜x1"<<endl;
                item_num[2]-=1;
                item_num[1]-=2;
                item_num[5]+=2;
            }
            else
                cout<<"材料不足"<<endl;
            system("pause");
        }
        if (input==0)
        {
            break;
        }
    }
}

//----------------------以下为背包及其附属模块---------------------------------

void pack()
{
    for(int i=0;i<=99;i++)
    {
        if(item_num[i]!=0)
            cout<<item_name[i]<<"x"<<item_num[i]<<endl;
    }
    system("pause");
}

//----------------------以下为副本及其附属模块---------------------------------
void getitem(int item_kind,int item_kind_num)
{
    int a;//暂存随机值
    int item_type[11];
    for(int i=0;i<=10;i++){
        item_type[i]=item_kind%100;//读入物品种类
        item_kind/=100;
    }
    a=rand()%item_kind_num;
    cout<<"恭喜你获得了"<<item_name[item_type[a]];
    item_num[item_type[a]]++;
    
}
//-----------------------------------------------------------------------------------
void fight(int mob_type)
{
    int mob_hp_1=mob_hp[mob_type],hero_hp_1=hero_hp_game;
    int hero_mana_1=hero_mana_game;
    cout<<"野生的"<<mob_name[mob_type]<<"出现了"<<endl;
    while (true)
    {
        cout<<mob_name[mob_type]<<":"<<mob_hp_1<<"/"<<mob_hp[mob_type]<<endl<<endl;
        cout<<User_name<<":"<<hero_hp_1<<"/"<<hero_hp()<<endl;
        cout<<"法术值:"<<hero_mana_1<<"/"<<hero_mana+level()*5<<endl;
        cout<<endl<<endl<<"1.攻击 ";
        if (level()>=5) {
            cout<<"2.施放法术 ";
        }
        cout<<endl;
        do {
            cin>>input;
        } while (input!=1&&input!=2);
        if (input==1)
        {
            mob_hp_1-=int(hero_attact()-mob_def[mob_type]);
            cout<<User_name<<"对"<<mob_name[mob_type]<<"造成了"<<int(hero_attact()-mob_def[mob_type])<<"伤害"<<endl;
            
        } else if(input==2)
        {
            cout<<"请选择你要释放的法术"<<endl;
            for (int i=0; i<=5; i++) {
                if (mana_skill_studied[i]==1) {
                    cout<<mana_skill_name1[i]<<endl;
                }
            }
            cin>>input;
            if(mana_skill_studied[input-1]==1&&hero_mana_1>=20)
            {
                double b=mana_attact(input-1);//暂存法术伤害
                mob_hp_1-=b;
                cout<<User_name<<"使用了"<<mana_skill_name[input-1]<<"对"<<mob_name[mob_type]<<"造成了"<<b<<"伤害"<<endl;
                hero_mana_1-=20;
            }
        }
        if(mob_hp_1>0){
            cout<<mob_name[mob_type]<<"对你造成了"<<int(mob_att[mob_type])<<"伤害"<<endl;
            hero_hp_1-=int(mob_att[mob_type]);}
        if (hero_hp_1<=0) {
            cout<<"闯关失败"<<endl;
            shibai=1;
            break;
        }
        if (mob_hp_1<=0) {
            cout<<"你击杀了"<<mob_name[mob_type]<<"获得经验"<<mob_expget[mob_type]<<endl;
            exp+=mob_expget[mob_type];
            hero_hp_game=hero_hp_1;
            hero_mana_game=hero_mana_1;
            break;
        }
    }
    
}

//----------------------------------隐藏关--------------------------------------------
void fuben0(int num_event,int levelk,long long mob_type,int mob_type_num,int item_type,int item_type_num,int get_coin,int get_exp) {
    int mob_type_1[100];
    hero_hp_game=hero_hp();
    hero_mana_game=hero_mana+level()*5;
    for(int i=1;i<=mob_type_num;i++){
        mob_type_1[i]=mob_type%100;//读入怪物种类
        mob_type/=100;
    }
    //cout<<mob_type_1[0]<<mob_type_1[1];
    cout<<"没想到你竟然发现了这个隐藏关！"<<endl;
    system("pause");
    cout<<"迎接超棒的史莱姆雨吧！！！！！！"<<endl;
    system("pause");
    cout<<"本关出现的怪物有：";
    for(int j=1;j<=mob_type_num;j++){
        cout<<mob_name[mob_type_1[j]]<<" ";
        //system("pause");
    }
    cout<<endl;
    srand((unsigned)time(NULL));
    for(int k=1;k<=num_event;k++) {
        if(shibai==1)
        {
            shibai=0;
            break;
        }
        fight(mob_type_1[rand()%mob_type_num+1]);
        slime+=1;
        system("pause");
        cout<<endl<<endl;
        if(k==num_event){
            cout<<"恭喜完成副本,金币+"<<get_coin<<"经验+"<<get_exp<<endl;
            coin+=get_coin;
            exp+=get_exp;
            
        }
    }
    
}


//------------------------------------------------------------------------------------

void fuben1(int num_event,int levelk,int mob_type,int mob_type_num,int item_type,int item_type_num,int get_coin,int get_exp) {
    int mob_type_1[10];
    int a;//暂存随机值
    hero_hp_game=hero_hp();
    hero_mana_game=hero_mana+level()*5;
    for(int i=1;i<=mob_type_num;i++){
        mob_type_1[i]=mob_type%100;//读入怪物种类
        mob_type/=100;
    }
    //cout<<mob_type_1[0]<<mob_type_1[1];
    cout<<"本关出现的怪物有：";
    for(int j=1;j<=mob_type_num;j++){
        cout<<mob_name[mob_type_1[j]]<<" ";
        //system("pause");
    }
    cout<<endl;
    srand((unsigned)time(NULL));
    for(int k=1;k<=num_event;k++) {
        a=rand()%100;
        if(shibai==1)
        {
            shibai=0;
            break;
        }
        if(a<=60){
            //cout<<"fight";
            fight(mob_type_1[rand()%mob_type_num+1]);
            
        }
        else if(a<=90)
            //cout<<"获得物品"<<endl;
            getitem(item_type,item_type_num);
        else if(a<=100)
        {
            cout<<"遇到魔法阵，回复10hp"<<endl;
            hero_hp_game+=10;
        }
        hero_mana_game+=20;
        if (hero_mana_game>hero_mana+level()*5) {
            hero_mana_game=hero_mana+level()*5;
        }
        system("pause");
        cout<<endl;
        if(k==num_event){
            cout<<"恭喜完成副本,金币+"<<get_coin<<"经验+"<<get_exp<<endl;
            coin+=get_coin;
            exp+=get_exp;
            if (pass_level<levelk+1) {
                pass_level=levelk+1;
            }
        }
    }
    
}

//---------------------------------------------------------------------------

void level_menu(){
    int levelb,levels;
    cout<<"关卡列表："<<endl<<endl;
    for(int i=1;i<=10;i++){
        cout<<"1-"<<i;
        if(pass_level<i)
            cout<<"(未解锁)";
        cout<<" ";
    }//第一大关；
    cout<<endl<<"请输入你要前往的关卡(大关小关以空格隔开)";
    cin>>levelb>>levels;
    if(levelb==1&&levels==1&&pass_level>=1)
        fuben1(10,levels,102,2,10200,3,10,10);
    else if(levelb==1&&levels==2&&pass_level>=2)
        fuben1(12,levels,10203,3,10200,3,20,20);
    else if(levelb==1&&levels==3&&pass_level>=3)
        fuben1(15,levels,20304,3,10200,3,50,50);
    else if(levelb==1&&levels==4&&pass_level>=4)
        fuben1(15,levels,30405,3,1020300,4,100,100);
    else if(levelb==1&&levels==5&&pass_level>=5)
        fuben1(18,levels,3040506,4,1020300,4,100,100);
    else if(levelb==0&&levels==1)
        fuben0(50,levels,7080910111213141516,10,0,0,100,100);
    else
        cout<<"很抱歉，还没有做完哦。"<<endl;
    
}

//--------------------------------------------------------------------------------------
//主用户界面；
void mainmenu() {
    int UserInput;
    system("color 0a");
    if(User_name=="生の灵"||User_name=="网管")
        system("color a0");
    while(true) {
        cout<<"你好啊，"<<User_name<<endl<<"1.副本 2.背包 3.合成 4.武器 5.查看信息 233.存档 234.读档 ";
        if (level()>=5) {
            cout<<"6.法术学习 ";
        }
        cout<<"0.退出"<<endl;
        cin>>UserInput;
        if(UserInput==1) {
            //system("cls");
            system("clear");
            level_menu();
        }
        if(UserInput==0) {
            cout<<"确认要退出吗"<<endl<<"0.确认 1.我手滑了"<<endl;
            cin>>UserInput;
            if(UserInput==0)
                break;
        }
        if(UserInput==2) {
            pack();
        }
        if (UserInput==99) {
            cout<<"请输入要修改的物品序号(从0开始记)和修改的数量,用空格隔开";
            int q,p;
            cin>>q>>p;
            item_num[q]=p;
        }
        if (UserInput==65535) {
            cout<<"请输入要修改的金币数量";
            int q;
            cin>>q;
            coin=q;
        }
        if (UserInput==666) {
            cout<<"请输入要修改的exp数量";
            int q;
            cin>>q;
            exp=q;
        }
        if (UserInput==66) {
            tool_num[3]=1;
        }
        if (UserInput==3) {
            
            compose();
        }
        if (UserInput==4) {
            
            tool_pack();
        }
        if (UserInput==5) {
            
            looker();
        }
        if (UserInput==6) {
            
            mana_study();
        }
        
    }
}

void user_name_input(){
    cout<<"欢迎游玩本游戏，请你的名字是？";
    cin>>User_name;
    mainmenu();
}

int main(){
    cout<<"欢迎游玩本游戏，本游戏十分脆弱，不要试图做一些不在规则内的事，否则游戏会炸......"<<endl;
    cout<<"祝你玩得开心" <<endl;
    system("pause");
    //system("cls");
    system("clear");
    memset(item_num, 0, sizeof(item_num));
    memset(tool_num, 0, sizeof(tool_num));
    user_name_input();
    return 0;
    
}

/*
 
 
 
 
 */
