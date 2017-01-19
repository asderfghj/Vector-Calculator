#include "allegro.h" //adds allegro to project 
#include "vector.h" //adds vector files to project
#include "matrices.h" //adds matrix files to project

void StartAddition();//See line 92
void StartTransform();//See line 237
void Scale();//See line 275
void Translate();//See line 381
void ScalTrans();//See line 537
Vector4 LineToPxConvert(Vector4 _vector);//See line 726
void Scroller(float &_number, float _range);//See line 741
void SlowTick();//See line 772

BITMAP *g_buffer;
BITMAP *g_graph;
BITMAP *g_titleScreen;
BITMAP *g_cursor;
volatile int g_tick;

int main(void)
{
	float i = 0.0;
	bool exit = false;
	allegro_init();//allegro initialisations
	install_keyboard();
	install_mouse();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 600, 800, 0, 0);//end of allegro initialisations
	g_buffer = create_bitmap(SCREEN_W, SCREEN_H);//creates buffer bitmap for double buffering
	g_titleScreen = load_bitmap("images/titlescreen.bmp", NULL);//locates and adds the title screen bitmap to the program
	g_graph = load_bitmap("images/graph.bmp", NULL);//locates and adds the graph bitmap to the program
	g_cursor = load_bitmap("images/cursor.bmp", NULL);//locates and adds the cursor screen bitmap to the program
	if(g_titleScreen == NULL ||
		 g_graph == NULL ||
		 g_cursor == NULL)//checks that the external bitmaps have been located successfully, if they return NULL message appears and game quits
	{
		allegro_message("ERROR: Bitmap not found");
	}
	else
	{
		while(exit == false)//starts the while loop for main menu
		{ 
		
			blit(g_titleScreen, g_buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//blits title screen to buffer
			masked_blit(g_cursor, g_buffer, 0, 0, mouse_x, mouse_y, g_cursor->w, g_cursor->h);//blits cursor to buffer 
			blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);//blits buffer to screen
		
			if (mouse_x > 150 && 
				mouse_x < 450 && 
				mouse_y > 300 && 
				mouse_y < 400 && 
				mouse_b & 1)/*Mouse button for addition function*/
			{
				clear_bitmap(g_buffer);
				StartAddition();
			}

			if (mouse_x > 150 && 
				mouse_x < 450 && 
				mouse_y > 425 && 
				mouse_y < 525 && 
				mouse_b & 1)/*Mouse button for transformation functions*/
			{
				clear_bitmap(g_buffer);
				StartTransform();
			}

			if (mouse_x > 150 && 
				mouse_x < 450 && 
				mouse_y > 550 && 
				mouse_y < 650 && 
				mouse_b & 1)/*mouse button for exit*/
			{
				exit = true;
			}
		
			if(4 - g_tick > 0)//slows the framerate so that the mouse will appear
			{
				rest(4 - g_tick);
			}
		}
	}
	destroy_bitmap(g_buffer);//destroys bitmaps to prevent memory leaks
	destroy_bitmap(g_cursor);
	destroy_bitmap(g_graph);
	destroy_bitmap(g_titleScreen);

	return 0;
}
END_OF_MAIN()

/*
	FUNCTION:		StartAddition()
	PARAMETERS:		None
	RETURNS:		None (void function)
	DESCRIPTION:	This function performs addition or subtraction
					between two vectors and then displays them on
					the screen for the user to see.
*/
void StartAddition()
{
	float x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;//sets up the user inputs
	bool flag1 = false, flag2 = false, flag3 = false, flag4 = false, flag5 = false, addOrSub = true;//sets up the flags for each user input and the user input deciding addition or subtraction
	Vector4 vec1, pVec1, vec2, pVec2, vec3, pVec3;//sets up vectors (vectors with 'p' at the front of the name stands for pixels, this variable is used for when the vector has been converted to pixels 
	while (flag1 == false)
	{
		Scroller(x1, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the first vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,0,0), -1, "Vector 1 x: %1.1f", x1);//displays the value the user has selected
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag1 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while (flag2 == false)
	{
		Scroller(y1, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the first vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,0,0), -1, "Vector 1 y: %1.1f", y1);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag2 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while (flag3 == false)
	{
		Scroller(x2, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the second vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(0,200,255), -1, "Vector 2 x: %1.1f", x2);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag3 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while (flag4 == false)
	{
		Scroller(y2, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the second vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(0,200,255), -1, "Vector 2 y: %1.1f", y2);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag4 = true;
		}
	}

	vec1.Setx(x1);//these 4 lines allocate the x and y values to the respective vector
	vec1.Sety(y1);
	vec2.Setx(x2);
	vec2.Sety(y2);

	while (flag5 == false)//this segment asks the user whether they want to add or subtract their vectors
	{
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "To add vector 1 to vector 2 press 1");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "To subtract vector 1 from vector 2 press 2");
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_1])
		{
			addOrSub = true;
			flag5 = true;
		}
		else if (key[KEY_2])
		{
			addOrSub = false;
			flag5 = true;
		}
	}

	while(!key[KEY_ESC])
	{
		blit(g_graph, g_buffer, 0, 0, 0, 0, g_graph->w, g_graph->h);
		if(addOrSub == true)
		{
		vec3 = VecAdd(vec1, vec2);
		}
		else if(addOrSub == false)
		{
		vec3 = VecSub(vec1, vec2);
		}
		pVec1 = LineToPxConvert(vec1);
		pVec2 = LineToPxConvert(vec2);
		pVec3 = LineToPxConvert(vec3);

		line(g_buffer, 300, 300, pVec1.Getx(), pVec1.Gety(), makecol(255, 0, 0));
		circlefill(g_buffer, pVec1.Getx(), pVec1.Gety(), 2, makecol(255, 0, 0));
		line(g_buffer, pVec1.Getx(), pVec1.Gety(), pVec3.Getx(), pVec3.Gety(), makecol(0, 200, 255));
		circlefill(g_buffer, pVec3.Getx(), pVec3.Gety(), 2, makecol(0, 200, 255));
		if(!key[KEY_H])
		{
			line(g_buffer, 300, 300, pVec3.Getx(), pVec3.Gety(), makecol(0, 255, 0));
			circlefill(g_buffer, pVec3.Getx(), pVec3.Gety(), 2, makecol(0, 255, 0));
		}
		textprintf_ex(g_buffer, font, 10, 600, makecol(255,0,0), -1, "Vector 1:");
		textprintf_ex(g_buffer, font, 10, 610, makecol(255,0,0), -1, "X: %1.1f", vec1.Getx());
		textprintf_ex(g_buffer, font, 10, 620, makecol(255,0,0), -1, "Y: %1.1f", vec1.Gety());
		textprintf_ex(g_buffer, font, 110, 600, makecol(0,200,255), -1, "Vector 2:");
		textprintf_ex(g_buffer, font, 110, 610, makecol(0,200,255), -1, "X: %1.1f", vec2.Getx());
		textprintf_ex(g_buffer, font, 110, 620, makecol(0,200,255), -1, "Y: %1.1f", vec2.Gety());
		textprintf_ex(g_buffer, font, 150, 650, makecol(255,255,255), -1, "Hold 'H' to hide the green line");
		textprintf_ex(g_buffer, font, 150, 660, makecol(255,255,255), -1, "Press escape to return to the main menu");

		if(addOrSub == true)
		{
			textprintf_ex(g_buffer, font, 210, 600, makecol(0,255,0), -1, "Added Vectors:");
		}
		else if(addOrSub == false)
		{
			textprintf_ex(g_buffer, font, 210, 600, makecol(0,255,0), -1, "Subtracted Vectors:");
		}
		textprintf_ex(g_buffer, font, 210, 610, makecol(0,255,0), -1, "X: %1.1f", vec3.Getx());
		textprintf_ex(g_buffer, font, 210, 620, makecol(0,255,0), -1, "Y: %1.1f", vec3.Gety());
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}


}

/*
	FUNCTION:		StartTransform()
	PARAMETERS:		None
	RETURNS:		None (void function)
	DESCRIPTION:	This function acts a a secondary menu for the transformations
					that are performed on vectors
*/
void StartTransform()
{
	bool flag1 = false;
	while (flag1 == false)
	{
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Press 1 for scaling");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "Press 2 for translation");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,255,255), -1, "Press 3 for scaling and translation");
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		if(key[KEY_1])
		{
			Scale();
			clear_bitmap(g_buffer);
			flag1 = true;
		}
		else if (key[KEY_2])
		{
			Translate();
			clear_bitmap(g_buffer);
			flag1 = true;
		}
		else if(key[KEY_3])
		{
			ScalTrans();
			clear_bitmap(g_buffer);
			flag1 = true;
		}
	}

}

/*
	FUNCTION:		Scale()
	PARAMETERS:		None
	RETURNS:		None (void function)
	DESCRIPTION:	This is the scale function for vectors, user inputs data then
					matrix scales the vector and displays on a graph 
*/
void Scale()
{
	Vector4 preVec, scaVec, pPreVec, pScaVec;
	preVec.Setw(1);
	Matrix scaleMatrix;
	float x = 0.0, y = 0.0, sX = 0.0, sY = 0.0;
	bool flag1 = false, flag2 = false, flag3 = false, flag4 = false, flag5 = false;
	while(flag1 == false)
	{
		Scroller(x, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,222,0), -1, "Vector x: %1.1f", x);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag1 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag2 == false)
	{
		Scroller(y, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,222,0), -1, "Vector y: %1.1f", y);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag2 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag3 == false)
	{
		Scroller(sX, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x scale value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the matrix (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "matrix scale x: %1.1f", sX);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag3 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag4 == false)
	{
		Scroller(sY, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y scale value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the matrix (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "matrix scale y: %1.1f", sY);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag4 = true;
			clear_keybuf();
		}
	}
	clear_keybuf();
	scaleMatrix.SetMatrix(0,0,sX);
	scaleMatrix.SetMatrix(1,1,sY);
	scaleMatrix.SetMatrix(3,3,1);
	preVec.Setx(x);
	preVec.Sety(y);
	pPreVec = LineToPxConvert(preVec);

	scaVec = MatVecMulti(scaleMatrix, preVec);
	pScaVec = LineToPxConvert(scaVec);

	while(!key[KEY_ESC])
	{
		blit(g_graph, g_buffer, 0, 0, 0, 0, g_graph->w, g_graph->h);
		line(g_buffer, 300, 300, pPreVec.Getx(), pPreVec.Gety(), makecol(255, 222, 0));
		circlefill(g_buffer, pPreVec.Getx(), pPreVec.Gety(), 2, makecol(255, 222, 0));
		line(g_buffer, 300, 300, pScaVec.Getx(), pScaVec.Gety(), makecol(88,248,255));
		circlefill(g_buffer, pScaVec.Getx(), pScaVec.Gety(), 2, makecol(88,248,255));
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		textprintf_ex(g_buffer, font, 10, 600, makecol(255, 222, 0), -1, "Original Vector:");
		textprintf_ex(g_buffer, font, 10, 610, makecol(255, 222, 0), -1, "X: %1.1f", preVec.Getx());
		textprintf_ex(g_buffer, font, 10, 620, makecol(255, 222, 0), -1, "Y: %1.1f", preVec.Gety());
		textprintf_ex(g_buffer, font, 150, 600, makecol(88,248,255), -1, "Scaled Vector:");
		textprintf_ex(g_buffer, font, 150, 610, makecol(88,248,255), -1, "X: %1.1f", scaVec.Getx());
		textprintf_ex(g_buffer, font, 150, 620, makecol(88,248,255), -1, "Y: %1.1f", scaVec.Gety());
		textprintf_ex(g_buffer, font, 150, 650, makecol(255,255,255), -1, "Press escape to return to the main menu");

	}

}

/*
	FUNCTION:		Translate()
	PARAMETERS:		None
	RETURNS:		None (void function)
	DESCRIPTION:	This is the scale function for vectors, user inputs data then
					matrix translates the vector and displays on a graph 
*/
void Translate()
{
	Vector4 startVec, endVec, tStartVec, tEndVec, pStartVec, pEndVec, tpStartVec, tpEndVec;
	Matrix transMatrix;
	transMatrix.SetMatrix(0, 0, 1);
	transMatrix.SetMatrix(1, 1, 1);
	transMatrix.SetMatrix(2, 2, 1);
	transMatrix.SetMatrix(3, 3, 1);
	startVec.Setw(1);
	endVec.Setw(1);

	float x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, tX = 0.0, tY = 0.0;
	bool flag1 = false, flag2 = false, flag3 = false, flag4 = false, flag5 = false, flag6 = false;
	while(flag1 == false)
	{
		
		Scroller(x1, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the starting point (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255, 222, 0), -1, "Start x: %1.1f", x1);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag1 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag2 == false)
	{
		Scroller(y1, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the starting point(between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,222,0), -1, "Start y: %1.1f", y1);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag2 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag3 == false)
	{
		Scroller(x2, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the end point (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255, 222, 0), -1, "End x: %1.1f", x2);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag3 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag4 == false)
	{
		Scroller(y2, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the end point (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255, 222, 0), -1, "End y: %1.1f", y2);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag4 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag5 == false)
	{
		Scroller(tX, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the translation (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "translation x: %1.1f", tX);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag5 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag6 == false)
	{
		Scroller(tY, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the translation (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "End y: %1.1f", tY);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag6 = true;
		}
	}
	clear_keybuf();
	transMatrix.SetMatrix(3,0,tX);
	transMatrix.SetMatrix(3,1,tY);
	startVec.Setx(x1);
	startVec.Sety(y1);
	endVec.Setx(x2);
	endVec.Sety(y2);

	tStartVec = MatVecMulti(transMatrix, startVec);
	tEndVec = MatVecMulti(transMatrix, endVec);
	pStartVec = LineToPxConvert(startVec);
	pEndVec = LineToPxConvert(endVec);
	tpStartVec = LineToPxConvert(tStartVec);
	tpEndVec = LineToPxConvert(tEndVec);

	while(!key[KEY_ESC])
	{
		blit(g_graph, g_buffer, 0, 0, 0, 0, g_graph->w, g_graph->h);
		line(g_buffer, pStartVec.Getx(), pStartVec.Gety(), pEndVec.Getx(), pEndVec.Gety(), makecol(255, 222, 0));
		circlefill(g_buffer, pEndVec.Getx(), pEndVec.Gety(), 2, makecol(255, 222, 0));
		line(g_buffer, tpStartVec.Getx(), tpStartVec.Gety(), tpEndVec.Getx(), tpEndVec.Gety(), makecol(88,248,255));
		circlefill(g_buffer, tpEndVec.Getx(), tpEndVec.Gety(), 2, makecol(88,248,255));
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		textprintf_ex(g_buffer, font, 10, 600, makecol(255, 222, 0), -1, "Vector Start:");
		textprintf_ex(g_buffer, font, 10, 610, makecol(255, 222, 0), -1, "X: %1.1f", startVec.Getx());
		textprintf_ex(g_buffer, font, 10, 620, makecol(255, 222, 0), -1, "Y: %1.1f", startVec.Gety());
		textprintf_ex(g_buffer, font, 10, 630, makecol(255, 222, 0), -1, "Vector End:");
		textprintf_ex(g_buffer, font, 10, 640, makecol(255, 222, 0), -1, "X: %1.1f", endVec.Getx());
		textprintf_ex(g_buffer, font, 10, 650, makecol(255, 222, 0), -1, "Y: %1.1f", endVec.Gety());
		textprintf_ex(g_buffer, font, 150, 600, makecol(88,248,255), -1, "Translated Vector Start:");
		textprintf_ex(g_buffer, font, 150, 610, makecol(88,248,255), -1, "X: %1.1f", tStartVec.Getx());
		textprintf_ex(g_buffer, font, 150, 620, makecol(88,248,255), -1, "Y: %1.1f", tStartVec.Gety());
		textprintf_ex(g_buffer, font, 150, 630, makecol(88,248,255), -1, "Translated Vector End:");
		textprintf_ex(g_buffer, font, 150, 640, makecol(88,248,255), -1, "X: %1.1f", tEndVec.Getx());
		textprintf_ex(g_buffer, font, 150, 650, makecol(88,248,255), -1, "Y: %1.1f", tEndVec.Gety());
		textprintf_ex(g_buffer, font, 150, 670, makecol(255,255,255), -1, "Press escape to return to the main menu");

	}
}

/*
	FUNCTION:		ScalTrans()
	PARAMETERS:		None
	RETURNS:		None (void function)
	DESCRIPTION:	This is the scale function for vectors, user inputs data then
					matrix translates and scales the vector and displays on a graph 
*/
void ScalTrans()
{
	Vector4  startVec, pStartVec, endVec, pEndVec, stStartVec, stEndVec, stpStartVec, stpEndVec;
	Matrix scaleMatrix, transMatrix, stMatrix;
	scaleMatrix.SetMatrix(3,3,1);
	transMatrix.SetMatrix(0,0,1);
	transMatrix.SetMatrix(1,1,1);
	transMatrix.SetMatrix(2,2,1);
	transMatrix.SetMatrix(3,3,1);
	endVec.Setw(1);
	float x = 0.0, y = 0.0, sX = 0.0, sY = 0.0, tX = 0.0, tY = 0.0;
	bool flag1 = false, flag2 = false, flag3 = false, flag4 = false, flag5 = false, flag6 = false, flag7 = false, flag8 = false;
	while(flag1 == false)
	{
		
		Scroller(x, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,222,0), -1, "Vector x: %1.1f", x);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag1 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag2 == false)
	{
		Scroller(y, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the vector (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(255,222,0), -1, "Vector y: %1.1f", y);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag2 = true;
		}
	}

	clear_keybuf();
	_sleep(500);
		while(flag5 == false)
	{
		Scroller(sX, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x scale value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the matrix (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "matrix scale x: %1.1f", sX);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag5 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag6 == false)
	{
		Scroller(sY, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y scale value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the matrix (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "matrix scale y: %1.1f", sY);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag6 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag7 == false)
	{
		Scroller(tX, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the x value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the translation (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "translation x: %1.1f", tX);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag7 = true;
		}
	}
	clear_keybuf();
	_sleep(500);
	while(flag8 == false)
	{
		Scroller(tY, 2.5);
		SlowTick();
		textprintf_ex(g_buffer, font, 20, 410, makecol(255,255,255), -1, "Use the up and down arrow keys to change the y value");
		textprintf_ex(g_buffer, font, 20, 420, makecol(255,255,255), -1, "of the translation (between 2.5 and -2.5)");
		textprintf_ex(g_buffer, font, 20, 430, makecol(88,248,255), -1, "End y: %1.1f", tY);
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		if(key[KEY_ENTER])
		{
			flag8 = true;
		}
	}
	clear_keybuf();
	startVec.Setx(0);
	startVec.Sety(0);
	startVec.Setw(1);
	endVec.Setx(x);
	endVec.Sety(y);
	scaleMatrix.SetMatrix(0,0,sX);
	scaleMatrix.SetMatrix(1,1,sY);
	transMatrix.SetMatrix(3,0,tX);
	transMatrix.SetMatrix(3,1,tY);
	stMatrix = MatMatMulti(transMatrix, scaleMatrix);
	stStartVec = MatVecMulti(stMatrix, startVec);
	stEndVec = MatVecMulti(stMatrix, endVec);
	pStartVec = LineToPxConvert(startVec);
	pEndVec = LineToPxConvert(endVec);
	stpStartVec = LineToPxConvert(stStartVec);
	stpEndVec = LineToPxConvert(stEndVec);
	while(!key[KEY_ESC])
	{
		blit(g_graph, g_buffer, 0, 0, 0, 0, g_graph->w, g_graph->h);
		line(g_buffer, pStartVec.Getx(), pStartVec.Gety(), pEndVec.Getx(), pEndVec.Gety(), makecol(255, 222, 0));
		circlefill(g_buffer, pEndVec.Getx(), pEndVec.Gety(), 2, makecol(255, 222, 0));
		line(g_buffer, stpStartVec.Getx(), stpStartVec.Gety(), stpEndVec.Getx(), stpEndVec.Gety(), makecol(88,248,255));
		circlefill(g_buffer, stpEndVec.Getx(), stpEndVec.Gety(), 2, makecol(88,248,255));
		blit(g_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		clear_bitmap(g_buffer);
		textprintf_ex(g_buffer, font, 10, 600, makecol(255,222,0), -1, "Vector Start:");
		textprintf_ex(g_buffer, font, 10, 610, makecol(255,222,0), -1, "X: %1.1f", startVec.Getx());
		textprintf_ex(g_buffer, font, 10, 620, makecol(255,222,0), -1, "Y: %1.1f", startVec.Gety());
		textprintf_ex(g_buffer, font, 10, 630, makecol(255,222,0), -1, "Vector End:");
		textprintf_ex(g_buffer, font, 10, 640, makecol(255,222,0), -1, "X: %1.1f", endVec.Getx());
		textprintf_ex(g_buffer, font, 10, 650, makecol(255,222,0), -1, "Y: %1.1f", endVec.Gety());
		textprintf_ex(g_buffer, font, 150, 600, makecol(88,248,255), -1, "Transformed Vector Start:");
		textprintf_ex(g_buffer, font, 150, 610, makecol(88,248,255), -1, "X: %1.1f", stStartVec.Getx());
		textprintf_ex(g_buffer, font, 150, 620, makecol(88,248,255), -1, "Y: %1.1f", stStartVec.Gety());
		textprintf_ex(g_buffer, font, 150, 630, makecol(88,248,255), -1, "Transformed Vector End:");
		textprintf_ex(g_buffer, font, 150, 640, makecol(88,248,255), -1, "X: %1.1f", stEndVec.Getx());
		textprintf_ex(g_buffer, font, 150, 650, makecol(88,248,255), -1, "Y: %1.1f", stEndVec.Gety());
		textprintf_ex(g_buffer, font, 150, 670, makecol(255,255,255), -1, "Press escape to return to the main menu");

	}
}

/*
	FUNCTION:		LineToPxConvert()
	PARAMETERS:		vector, A vector that will have it's values translated so that it will appear on screen
	RETURNS:		pixlvec, the vector with it's x and y co-ordinates changed to appear on screen acurately
	DESCRIPTION:	Function changes the x and y co-ordinates of a vector so that they will appear on screen 
					corresponding to the pre made graph
*/
Vector4 LineToPxConvert(Vector4 _vector)
{
	Vector4 pixlvec;
	pixlvec.Setx((_vector.Getx())/0.02+300);
	pixlvec.Sety((_vector.Gety())/-0.02+300);
	return pixlvec;
}

/*
	FUNCTION:		Scroller()
	PARAMETERS:		number, the number that the user is inputting
					range, the selected range of numbers that the user can enter to
	RETURNS:		none (void function)
	DESCRIPTION:	Modifys a number value within a certain ranges using arrow keys
					because inputting data on keyboard more than 1 digit long is annoying
*/
void Scroller(float &_number, float _range)
{
		if(key[KEY_UP])
		{
			_number += 0.1;
			clear_keybuf();
		}
		else if(key[KEY_DOWN])
		{
			_number -= 0.1;
			clear_keybuf();
		}
		if(_number > _range)
		{
			_number = _range;
		}
		if(_number < _range * (-1))
		{
			_number = _range * (-1);
		}

}

/*
	FUNCTION:		SlowTick()
	PARAMETERS:		none
	RETURNS:		none(void function)
	DESCRIPTION:	Increases frame rate to slow down the scroller function to
					give user more accuracy when trying to enter a number
*/
void SlowTick()
{
	if(60 - g_tick > 0)
	{
		rest(60 - g_tick);
	}
}