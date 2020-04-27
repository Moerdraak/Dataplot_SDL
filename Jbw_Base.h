#pragma once
#include "SDL.h"
#include "Jbw_Frame.h" 
#include <string>


const int J_TXT = 0;
const int J_EBX = 1;
const int J_LBX = 2;
const int J_CBX = 3;
const int J_GRD = 4;
const int J_LEN = 5;


struct J_Properties {
	SDL_Renderer* Rdr;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	int Fsize = 0;
	int ColCnt = 0;
	int RowCnt = 0;
	std::string Tag = "";
	std::string Caption = "";
};

class Jbw_Base
{
public:
	
	short int Id = 0;
	std::string Tag = "";
	SDL_Renderer* Rdr;



	Jbw_Base() {};
	~Jbw_Base() {};
};