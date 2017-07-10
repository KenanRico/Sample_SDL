


#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H
class MouseHandler{
	private:
		bool* click;
		int* position;
		int* clickposition;
		//int scroller;
	public:
		enum button{LEFT=0, MIDDLE=1, RIGHT=2}; 
		enum pos{X=0,Y=1};
	public:
		MouseHandler();
		~MouseHandler();
		MouseHandler(const MouseHandler&) = delete;
		MouseHandler& operator=(const MouseHandler&) = delete;
	public:
		void setClick(int, bool);
		void setPosition(int, int);
		void setClickPosition(int,int);
		int getX() const;
		int getY() const;
		int getClickX() const;
		int getClickY() const;
		bool operator[](int) const;

};
#endif
