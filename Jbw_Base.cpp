#include "Jbw_Base.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
//Jbw_Base::~Jbw_Base()
//{
//
//}

/*-----------------------------------------------------------------------------------------
	COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
//Jbw_Base::Jbw_Base(Jbw_Base& cp) {
//	Jhandle = cp.Jhandle;
//}
//
///*-----------------------------------------------------------------------------------------
//	ASIGNMENT OPERATOR OVERLOAD
//------------------------------------------------------------------------------------------*/
//void Jbw_Base::operator=(Jbw_Base& cp) {
//
//	delete Jhandle;
//	Jhandle = new Jbw_Handles;
//	*Jhandle = *cp.Jhandle;
//}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuEvent
------------------------------------------------------------------------------------------*/
SDL_Texture* Jbw_Base::CopyArea(Jbw_Handles* handles, int x, int y, int w, int h)
{
	// Hmmm Seems that you have to set the viewport first ?!?
	SDL_Rect GuiArea = handles->GuiArea;
	GuiArea.x = 0;
	GuiArea.y = 0;
	SDL_RenderSetViewport(handles->Rdr, &GuiArea);

	SDL_Surface* GetSurf = SDL_GetWindowSurface(handles->Gui);
	unsigned char* pixels = new (std::nothrow) unsigned char[GetSurf->w * GetSurf->h * GetSurf->format->BytesPerPixel];
	SDL_Rect CopyArea = { x, y, w, h };
	SDL_RenderReadPixels(handles->Rdr, &CopyArea, GetSurf->format->format, pixels, GetSurf->w * GetSurf->format->BytesPerPixel);
	SDL_Surface* saveSurface = SDL_CreateRGBSurfaceFrom(pixels, CopyArea.w, CopyArea.h,
		GetSurf->format->BitsPerPixel, GetSurf->w * GetSurf->format->BytesPerPixel,
		GetSurf->format->Rmask, GetSurf->format->Gmask, GetSurf->format->Bmask, GetSurf->format->Amask);

	// Create an SDL_Texture from the SDL_Surface -> Moving from RAM to Graphics card RAM
	SDL_Texture*  AreaImage = SDL_CreateTextureFromSurface(handles->Rdr, saveSurface);
	
	// Clean up memory
	SDL_FreeSurface(saveSurface); saveSurface = NULL;
	delete[] pixels; pixels = NULL;

	return AreaImage;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuEvent
------------------------------------------------------------------------------------------*/
void Jbw_Base::PasteArea(Jbw_Handles* handles, SDL_Texture* Image, int x, int y, int w, int h)
{
	SDL_Rect Area = { x, y, w, h };
	// Set the Vieport for pasting AreaImage and Render the AreaImage
	SDL_RenderSetViewport(handles->Rdr, &Area);
	SDL_RenderCopy(handles->Rdr, Image, NULL, NULL);
	SDL_RenderPresent(handles->Rdr);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: MnuEvent
------------------------------------------------------------------------------------------*/
void Jbw_Base::FreeArea(SDL_Texture* Image)
{
	if(Image != NULL){
		SDL_DestroyTexture(Image);
		Image = NULL;
	}
} 
/*
	SDL_Surface* GetSurf = SDL_GetWindowSurface(handles.Gui);
	unsigned char* pixels = new (std::nothrow) unsigned char[GetSurf->w * GetSurf->h * GetSurf->format->BytesPerPixel];
	SDL_Rect CopyArea = { 500, 100, 500, 300 };
	SDL_RenderReadPixels(handles.Rdr, &CopyArea, GetSurf->format->format, pixels, GetSurf->w* GetSurf->format->BytesPerPixel);
	SDL_Surface* saveSurface = SDL_CreateRGBSurfaceFrom(pixels, CopyArea.w, CopyArea.h,
		GetSurf->format->BitsPerPixel, GetSurf->w * GetSurf->format->BytesPerPixel,
		GetSurf->format->Rmask, GetSurf->format->Gmask, GetSurf->format->Bmask, GetSurf->format->Amask);

	// Create an SDL_Texture from the SDL_Surface -> Moving from RAM to Graphics card RAM
	SDL_Texture* AreaImage = SDL_CreateTextureFromSurface(handles.Rdr, saveSurface);

	// Set the Vieport for pasting AreaImage and Render the AreaImage
	SDL_RenderSetViewport(handles.Rdr, &CopyArea);
	SDL_RenderCopy(handles.Rdr, AreaImage, NULL, NULL);
	SDL_RenderPresent(handles.Rdr);

	// Clean up memory
	SDL_FreeSurface(saveSurface); saveSurface = NULL;
	delete[] pixels; pixels = NULL;
	SDL_DestroyTexture(AreaImage); AreaImage = NULL;
*/