#include <nds.h>
#include <stdio.h>
#include <math.h>

void DrawGLScene();

float rtri;				// angle for rotating the triangle

int main() {

	glInit();
	videoSetMode(MODE_0_3D); // Setup the Main screen for 3D
	vramSetBankC(VRAM_C_MAIN_BG_0x06000000); //map some vram to background for printing
	consoleInit(0,1, BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true);
	bgSetPriority(0, 1);//put bg 0 at a lower priority than the text background


	// enable antialiasing
	glEnable(GL_ANTIALIAS);
	// setup the rear plane
	glClearColor(0,0,0,31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);
	// Set our viewport to be the same size as the screen
	glViewport(0,0,255,191);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 100);
	//ds specific, several attributes can be set here
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);
	// Set the current matrix to be the model matrix
	glMatrixMode(GL_MODELVIEW);
	iprintf("\tnds-test\n");
	iprintf("\tThis is a Demo!\n");

	while (pmMainLoop()) {
		DrawGLScene();
		// flush to screen
		glFlush(0);
		// wait for the screen to refresh
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if(keys & KEY_START) break;
		printf("\x1b[15;5H rtri  = %f     \n", rtri);
		rtri+=0.9f;
		rtri  = fmodf( rtri , 360 );
	}

	return 0;
}

void DrawGLScene() {

	//ds does this automagically*open>///glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	glLoadIdentity();								// Reset The Current Modelview Matrix
	//glTranslatef(-1.5f,0.0f,-6.0f);					// Move Left 1.5 Units And Into The Screen 6.0
	glTranslatef(0.0f,0.0f,-6.0f);					// Move Left 1.5 Units And Into The Screen 6.0
	glScalef(2,2,2);					// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(rtri,0.0f,1.0f,0.0f);					// Rotate The Triangle On The Y axis ( NEW )
	glColor3f(1, 1, 1);								// set the vertex color
	glBegin(GL_TRIANGLES);							// Start Drawing A Triangle
		glColor3f(1.0f,0.0f,0.0f);					// Set Top Point Of Triangle To Red
		glVertex3f( 0.0f, 1.0f, 0.0f);				// First Point Of The Triangle
		glColor3f(0.0f,1.0f,0.0f);					// Set Left Point Of Triangle To Green
		glVertex3f(-1.0f,-1.0f, 0.0f);				// Second Point Of The Triangle
		glColor3f(0.0f,0.0f,1.0f);					// Set Right Point Of Triangle To Blue
		glVertex3f( 1.0f,-1.0f, 0.0f);				// Third Point Of The Triangle
	glEnd();										// Done Drawing The Triangle
	glLoadIdentity();								// Reset The Current Modelview Matrix
}
