#pragma once
#include"Config.h"

class Menu
{
	//private varies
	char choice[CHOICE_NUM][MAX_CH_LEN];//all the choices
	void (*Choice[CHOICE_NUM])(Menu* m);//Fuction pointer array
	int current;//index for choice[]
	bool run_tag;//if run

	//private Functions
	void Clear();//clear the content in the bounder range and the guide words
	void ShowGuide();//teach how to play
	void GameProcess();
	void GamePause();
	void GameOver();
	 //static Functions
	static void Start(Menu* m);//run the game
	static void End(Menu* m);//end the program
public:
	Menu();
	void Initial();//output the bounder and welcome the player
	void Infor();//show player the menu information: start or end game
	void OperateMenu();//do operation in menu
};

