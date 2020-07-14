//---------------图标按钮类----------------
class Button{
	friend class APP;
	private :
		uint16_t x_coord;
	  uint16_t y_coord;
		uint16_t xSize;
		uint16_t ySize;
		uint16_t selectFlag;
		const TCHAR* iconFile;
		uint16_t ButtonColor;
		const TCHAR* text;
		
		
	public :
		void (*buttonFun)(void);
		Button(uint16_t x,uint16_t y,const TCHAR* iFname,uint16_t Color = WHITE,const TCHAR* Text = NULL);
		Button(uint16_t x,uint16_t y,const TCHAR* iFname,uint16_t X_Size,uint16_t Y_Size,void (*ptr)(void) = NULL,uint16_t Color = WHITE,const TCHAR* Text = NULL);
		void Show(void);
		uint8_t ButtonIfBeSelected(void);
};
//--------------应用APP类--------------------
class APP{
	
	private :	
		
		const TCHAR* name;
		void (*appFun)(void);
		Button appButton;
	public :
		bool ifShowTitle;
		bool ifLandscapeMode;
		APP(const TCHAR* backGroundName,bool titleFlag,bool LandscapeMode,void (*ptr)(void),uint16_t x,uint16_t y,const TCHAR* iFname);
		APP(const TCHAR* backGroundName,bool titleFlag,bool LandscapeMode,void (*ptr)(void),uint16_t x,uint16_t y,const TCHAR* iFname,uint16_t X_Size,uint16_t Y_Size);
		void ShowButton(void);
		uint8_t AppIfBeSelected(void);
		void GetProgramPointToApp(void);
};
//----------------------------------------------------------
