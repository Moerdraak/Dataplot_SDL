#include "Jbw_Grid.h"

/*---------------------------------------------------------------
CONSTRUCTOR: 
------------------------------------------------------------------------------------------*/
Jbw_Grid::Jbw_Grid(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColCnt, int RowCnt)
{
	InitGrd(Rdr, GridName, x, y, ColCnt, RowCnt);
}

/*---------------------------------------------------------------
DESTRUCTOR:
------------------------------------------------------------------------------------------*/
Jbw_Grid::~Jbw_Grid()
{
	for (int I = 0; I < Rows; I++) {
			delete Element[I];
	}
	delete Element;
}

/*---------------------------------------------------------------
	FUNCTION: InitGrd
------------------------------------------------------------------------------------------*/
bool Jbw_Grid::InitGrd(SDL_Renderer* Rdr, std::string GridName, int x, int y, int ColCnt, int RowCnt) {
	Tag = GridName;
	GridX = x;
	GridY = y;
	if (ColCnt > 99) {
		ColCnt = 99; // This is way past ridiculous
	}
	Cols = ColCnt;
	Rows = RowCnt + 1;
	Prdr = Rdr;

	//	Header = new Jbw_EditBox[ColCnt];

	int Xs = GridX;
	int Ys = GridY;
	int w = 50; // Startup values To Be Deleted
	int h = 15; // Startup values To Be Deleted

	/*   Setting up the initial Frame  */
	CreateFrame(Rdr, GridX, GridY, ColCnt * (w - 2) + 1, (RowCnt + 1) * h - (RowCnt + 1));

	char TmpName[] = "Col 99 ";

	Element = new Jbw_EditBox * [(double)Rows + 1]; // Xtra 1 for heading
	// Do Heading - Row 0
	Element[0] = new Jbw_EditBox[Cols];
	for (int I = 0; I < ColCnt; I++) {
		Element[0][I].InitEbx(Rdr, Xs, Ys, w, h, 10);
		Element[0][I].Align = J_CENTRE;
		Element[0][I].BackColor = { 220, 220, 220, 255 };
		Element[0][I].LineColor = { 100, 100, 100, 255 };

		sprintf_s(TmpName, "Col %02d", I);
		Element[0][I].New(TmpName);
		Xs += w - 2;
	}

	//  Element = new Jbw_EditBox *[Rows];
	for (int I = 1; I < Rows; I++) {
		Element[I] = new Jbw_EditBox[Cols];
		Ys += h - 1;
		Xs = GridX;
		for (int J = 0; J < Cols; J++) {
			Element[I][J].InitEbx(Rdr, Xs, Ys, w, h, 10);
			Element[I][J].LineColor = { 200, 200, 200, 255 };
			Xs += w - 2;
		}
	}
	return true;
}

/*---------------------------------------------------------------
FUNCTION: 
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddCol(std::string ColName, int Type, int w, int h)
{

}



/*---------------------------------------------------------------
FUNCTION:
------------------------------------------------------------------------------------------*/
void Jbw_Grid::AddRow(int Num)
{
	Jbw_EditBox** Tmp = new Jbw_EditBox * [Rows + Num];

	Element = new Jbw_EditBox * [Rows];
	for (int I = 0; I < Rows; I++) {
		Element[I] = new Jbw_EditBox[Cols];
		for (int J = 0; J < Cols; J++) {
			Element[I][J].Trdr = Prdr;
			Element[I][J].LineColor = { 200, 200, 200, 255 };
		}
	}
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::GrdSet(std::string  *Var, const char* Val)
{
	char* Next;
	// Row Color
	if (Var->compare("RowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Alternative Row Color
	else if (Var->compare("ARowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Header Row Color
	else if (Var->compare("ARowColor") == 0) {
		RowColor.b = (int)strtod(Val, &Next);
		RowColor.g = (int)strtod(Next, &Next);
		RowColor.r = (int)strtod(Next, &Next);
	}
	// Set TxtSize for All Cells
	else if (Var->compare("CellTxtSize") == 0) { 
		int TxtSize = (int)strtod(Val, NULL);
		for (int I = 0; I < Rows; I++) {
			for (int J = 0; J < Cols; J++) {
				SetCellTxtSize(I, J, TxtSize);
			}
		}
	}
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtSize(int Row, int Col, int TxtSize)
{
	Element[Row][Col].TxtSize = TxtSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellFontType(int Row, int Col, int TxtSize)
{
	Element[Row][Col].TxtSize = TxtSize;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellTxtColor(int Row, int Col, SDL_Color Color)
{
	Element[Row][Col].TxtColor = Color;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetCellBackColor(int Row, int Col, SDL_Color Color)
{
	Element[Row][Col].BackColor = Color;
}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetVal(int Row, int Col, int Val)
{

}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
void Jbw_Grid::SetVal(int Row, int Col, std::string Val)
{
	int I = NULL;

}

/*---------------------------------------------------------------
FUNCTION:
---------------------------------------------------------------*/
double Jbw_Grid::GetVal(int Row, int Col )
{
	return Element[Row][Col].Value;
}

/*---------------------------------------------------------------
FUNCTION: GetTxt
---------------------------------------------------------------*/
std::string Jbw_Grid::GetTxt(int Row, int Col)
{
	return Element[Row][Col].Text;
}

/*---------------------------------------------------------------
FUNCTION: RowTxtSize
---------------------------------------------------------------*/
void Jbw_Grid::RowTxtSize(int Row, int FontSize)
{
	for (int I = 0; I < Cols; I++) {
		Element[Row][I].TxtSize = FontSize;
	}
}

/*---------------------------------------------------------------
FUNCTION: RowTxtSize
---------------------------------------------------------------*/
void Jbw_Grid::TxtSize(int Row, int Col, int FontSize)
{
	for (int I = 0; I < Cols; I++) {
		Element[Row][I].TxtSize = FontSize;
	}
}

/*---------------------------------------------------------------
FUNCTION: SetColWidth
---------------------------------------------------------------*/
void Jbw_Grid::SetColWidth(int Col, int w)
{
	int Wdiff = w - Element[0][Col].EditW;

	if (Col == -1){ //Set all Column's the same

	}
	else { // Set Specific Column width
		FrameW += Wdiff - 1; // Set outside Frame with

		for (int I = 0; I < Rows; I++) {
			Element[I][Col].EditW = w - 2;
			Element[I][Col].FrameW = w;
		}
		for (int I = Col + 1; I < Cols; I++) {
			for (int J = 0; J < Rows; J++) {
					Element[J][I].EditX += Wdiff - 1;
					Element[J][I].FrameX += Wdiff - 1;
			}
		}
	}
	SetFrame(); // Set Outside Grid frame
}

/*---------------------------------------------------------------
FUNCTION: SetRowHeight
---------------------------------------------------------------*/
void Jbw_Grid::SetRowHeight(int Row, int h)
{
	int Ys = Element[0][0].EditY;

	if (Row == -1) { //Set all Row's the same
		for (int I = 0; I < Rows; I++) {

			for (int J = 0; J < Cols; J++) {
				Element[I][J].EditH = h;
				Element[I][J].EditY = Ys;
				Element[I][J].FrameH = h + 1;
				Element[I][J].FrameY = Ys;
			}
			Ys += h + 1 ;
		}
		FrameH = (Rows) * h + Rows  ;
	}
	else { // Set Specific Column width
		int Hdiff = h - Element[Row][0].EditH - 2;
		FrameH += Hdiff + 1; // Set outside Frame Height

		for (int I = 0; I < Cols; I++) {
			Element[Row][I].EditH = h - 2;
			Element[Row][I].FrameH = h;
		}
		for (int I = Row + 1; I < Rows; I++) {
			for (int J = 0; J < Cols; J++) {
				Element[I][J].EditY += Hdiff;
				Element[I][J].FrameY += Hdiff;
			}
		}
	}
	SetFrame();
}

/*---------------------------------------------------------------
FUNCTION: Render Grid
---------------------------------------------------------------*/
void Jbw_Grid::Render(void)
{
	for (int I = Rows - 1; I >= 0; I--) { // So that Heading is Rendered last
		for (int J = 0; J < Cols; J++) {
			Element[I][J].CreateTexture();
				Element[I][J].FitText();
			Element[I][J].Render();
		}
	}	

FrameRdr();
}

/*---------------------------------------------------------------
FUNCTION: Event
---------------------------------------------------------------*/
void Jbw_Grid::Event(SDL_Event* e)
{
	for (int I = Rows - 1; I >= 0; I--) { // So that Heading is Rendered last
		for (int J = 0; J < Cols; J++) {
			Element[I][J].Event(e);
		}
	}

	//bool Flag = false;
	////If mouse event happened
	//if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
	//	// Get mouse position
	//	int x, y;
	//	SDL_GetMouseState(&x, &y);

	//	// Mouse pointer inside Edit box
	//	if (x > EditX&& x < EditX + EditW && y > EditY&& y < EditY + EditH)
	//	{
	//		switch (e->type)
	//		{
	//		case SDL_MOUSEMOTION:
	//			LineColor = { 0, 0, 0, 255 };
	//			break;

	//		case SDL_MOUSEBUTTONDOWN:
	//			//	BackColor = { 0, 0, 0, 255 };
	//			Focus = true;
	//			//		SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
	//			break;

	//		case SDL_MOUSEBUTTONUP:
	//			//	BackColor = { 255, 255, 255, 255 };
	//			break;
	//		}
	//	}
	//	else {
	//		LineColor = { 150, 150, 150, 255 };
	//		if (e->type == SDL_MOUSEBUTTONDOWN) {
	//			Focus = false;
	//		}
	//	}
	//}

	//if (Focus == false) {
	//	exit;
	//}
	//else if (e->type == SDL_TEXTINPUT) {
	//	Add(e->text.text);
	//	//		Render();
	//}
	//else if (e->type == SDL_KEYDOWN)
	//{
	//	if (e->key.keysym.sym == SDLK_BACKSPACE) {
	//		BackSpace();
	//		//	Render();
	//	}
	//	else if (e->key.keysym.sym == SDLK_DELETE) {
	//	}
	//	else if (e->key.keysym.sym) {
	//	}
	//}
	//if (Flag == true) {

	//}
	//Render();
}