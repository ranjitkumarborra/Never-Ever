

/*	Vivek Seetharaman
 *  This program can generate a Bezier Curve for upto 6 control points.
 *  It uses the recursive definition of bezier cureves to create higher order curves by linear interpolating progressively higher order curves
 */



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <OpenGL/gl.h>     // The GL Header File
#include <OpenGL/glext.h>
#include <GLUT/GLUT.h>  
#include "Point2f.h"
#include <vector>
#include "Tile.h"
#include "TileMap.h"
#include "PathFinder_DFS.h"
#include "PathFinder_BFS.h"
#include "PathFinder_Dijkstra.h"
#include "DTimer.h"
#include "PathFinder_A_STAR.h"
#include "UnitManager.h"
#include "glui.h"
#include "PathManager.h"

#define INDEX(i,j) ((j)*100+(i))

using namespace std;
using namespace vektor3d::core;

// Global Variables

// Global Map Objects
TileMap     *tileMap = NULL;
PathFinder  *pPathfinder;
UnitManager *pUnitManager;
Path path;
DTimer timer;

Point2f selectionStart, selectionEnd;

// Global Map Parameters 
int w = 1000;  int h= 1000;
int rows        = 80;
int cols        = 80;
int cellSize    = w/(rows);


// Global Input Variables
Point2f mouseClickPos;
bool bLeftButtonDown = false;
bool bRightButtonDown = false;
bool begin = false;


enum E_INPUT_STATE
{
    EIS_DRAW_WALL = 0,
    EIS_PLACE_TOWER,
    EIS_PLACE_HOUSE,
    EIS_PLACE_BARRACKS,
    EIS_PLACE_UNIT,
    
    EIS_SELECT_ITEMS,
    EIS_MOVE_SELECTED_ITEMS,
    
    
    EIS_SOURCE_SET,
    EIS_TARGET_SET,
    EIS_COLLIDER_DRAW,  // Walls
    EIS_CREATE_UNIT,
    EIS_MOVE_UNITS
};
E_INPUT_STATE eInputState = EIS_COLLIDER_DRAW;

int   main_window;

void display();
void HandleInputFromUI();
void InitGame();


// Used to draw selection box
void DrawRect( Point2f p1, Point2f p2 )
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glPointSize(8.0f);
    glColor4f( 0.5, 0.7, 0.8, 0.25);
	glBegin( GL_QUADS );
        glVertex2f( p1.x, p1.y);
        glVertex2f( p2.x, p1.y);
        glVertex2f( p2.x, p2.y);
        glVertex2f( p1.x, p2.y);
	glEnd();
	
    glPopMatrix();
	glFlush();
	
}

void myGlutIdle( void )
{
    /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
    if ( glutGetWindow() != main_window ) 
        glutSetWindow(main_window);  
    
    glutPostRedisplay();
}

void InitGL ( void )     // Create Some Everyday Functions
{
	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	
    glClearDepth(1.0f);									// Depth Buffer Setup
	
    glPointSize(4.0f);
	
    glColor3f( 1.0f, 0.0f,0.0f );
	
	glEnable( GL_LINE_SMOOTH );
    
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	
    glLineWidth(1.0f);
	
	glMatrixMode(GL_PROJECTION);
	
    glLoadIdentity();
	
    gluOrtho2D(0.0, w, 0.0, h);
	
	glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable( GL_POINT_SMOOTH );
    
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    glEnable( GL_BLEND );
}

// GLUI OBJECTS
GLUI_Spinner     *pMap_Row_Spinner;
GLUI_Spinner     *pMap_Col_Spinner;
GLUI_Button      *pButton_CreateMap;
GLUI_RadioGroup  *pRadioGroupBuildOptions;
GLUI_RadioGroup  *pRadioGroupGameMode;

// LIVE VARIABLES
//  These are the live variables passed into GLUI 
int   wireframe = 0;
int   nMapRowCount = rows;
int   nMapColCount = cols;

int   nBuildRadioValue;
int   nRadioBtnValue_GameMode;

/********** User IDs for callbacks ********/
#define ID_BTN_CREATE_MAP      100
#define ID_RADIO_BUILD_ITEM    101
#define ID_RADIO_GAME_MODE     102

void pointer_cb( GLUI_Control* control )
{
    if (control->get_id() == ID_BTN_CREATE_MAP ) 
    {
        cellSize = w/(nMapRowCount+2);
        InitGame();
        // Disable Controls because you cannot change the dimensions
        pMap_Row_Spinner->disable();
        pMap_Col_Spinner->disable();
        control->disable();
    }
    if (control->get_id() == ID_RADIO_BUILD_ITEM ) 
    {
        printf("\n Radio Button Value: %d", nBuildRadioValue);
        
        /*if( eInputState == EIS_PLACE_UNIT )
        {
            
        }*/
        //else
        {
            eInputState = (E_INPUT_STATE) nBuildRadioValue;
            //pRadioGroupGameMode->set_int_val(0);
        }
    }
    if (control->get_id() == ID_RADIO_GAME_MODE ) 
    {
        printf("\n Game Mode Radio Button Value: %d", nRadioBtnValue_GameMode);
        if( nRadioBtnValue_GameMode == 0 )
            eInputState = (E_INPUT_STATE) nBuildRadioValue;
        
        if( nRadioBtnValue_GameMode == 1 )
            eInputState = EIS_SELECT_ITEMS;

    }
}

void InitUI()
{
    GLUI *glui = GLUI_Master.create_glui( "Navigation System", 0, 160, 0 );
    
    /*** Add invisible panel to hold rest of controls ***/
    GLUI_Panel *rootPanel = new GLUI_Panel(glui, "",GLUI_PANEL_NONE );
    
    
    // MAP SETUP CONTROLS
    GLUI_Panel *pPanelMap= new GLUI_Panel(rootPanel, "Map" );
    
    pMap_Row_Spinner  = new GLUI_Spinner( pPanelMap, "Rows :", &nMapRowCount);
    pMap_Row_Spinner->set_int_val(nMapRowCount);
    pMap_Row_Spinner->set_alignment(GLUI_ALIGN_LEFT);
    
    
    pMap_Col_Spinner  = new GLUI_Spinner( pPanelMap, "Cols :", &nMapColCount);
    pMap_Col_Spinner->set_int_val(nMapColCount);
    pMap_Col_Spinner->set_alignment(GLUI_ALIGN_LEFT);
    
    pButton_CreateMap = new GLUI_Button(pPanelMap, "Create", ID_BTN_CREATE_MAP, pointer_cb);
    pButton_CreateMap->w = 50;
    pButton_CreateMap->set_alignment(GLUI_ALIGN_RIGHT);
    
    // BUILD OPTIONS
    GLUI_Panel *pPanelBuild = new GLUI_Panel( rootPanel, "Build Options" );
    
    pRadioGroupBuildOptions = new GLUI_RadioGroup( pPanelBuild, &nBuildRadioValue, ID_RADIO_BUILD_ITEM, pointer_cb );
    new GLUI_RadioButton( pRadioGroupBuildOptions, "Wall 2x2" );
    new GLUI_RadioButton( pRadioGroupBuildOptions, "Tower 3x3" );
    new GLUI_RadioButton( pRadioGroupBuildOptions, "House 4x4" );
    new GLUI_RadioButton( pRadioGroupBuildOptions, "Barracks 5x5" );
    new GLUI_RadioButton( pRadioGroupBuildOptions, "Spawn Unit" );
    
    GLUI_Panel *pPanelGameMode = new GLUI_Panel( rootPanel, "Game Mode" );
    pRadioGroupGameMode = new GLUI_RadioGroup( pPanelGameMode, &nRadioBtnValue_GameMode, ID_RADIO_GAME_MODE, pointer_cb );
    new GLUI_RadioButton( pRadioGroupGameMode, "Build" );
    new GLUI_RadioButton( pRadioGroupGameMode, "Play" );
    
    
    //qnew GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );
    // new GLUI_Separator( glui );
    //new GLUI_Column( pPanelMap, false ); /* 'false' means don't draw bar */
    //new GLUI_StaticText( glui, "Map Parameters" );
    //new GLUI_Checkbox( glui, "Wireframe", &wireframe );
    //new GLUI_Checkbox( glui, "Vektor", &wireframe );
    //(new GLUI_Spinner( glui, "Segments:", &segments ))->set_int_limits( 3, 60 ); 
    glui->set_main_gfx_window( main_window );
    
    /* We register the idle callback with GLUI, *not* with GLUT */
    GLUI_Master.set_glutIdleFunc( myGlutIdle ); 
}


void InitGame()
{
    
    tileMap = new TileMap( nMapColCount, nMapRowCount, cellSize );
    
    tileMap->SetOffset( 0, 0);
    
    pPathfinder = new PathFinder_A_STAR( tileMap->GetCollisionGraph(), tileMap );
     //pPathfinder = new PathFinder_Dijkstra( tileMap->GetCollisionGraph(), tileMap );
    
    pUnitManager = new UnitManager();
    
    pUnitManager->m_PathFinder = pPathfinder;
    
    pUnitManager->m_TileMap = tileMap;
}


void InitApp()
{
    InitUI();
    
    InitGL();
    
    //InitGame();
}

void TestPathFinder()
{
    printf("\n BEGIN ");
    
    int sourceID = tileMap->GetSourceNodeID();
    int targetID = tileMap->GetTargetNodeID();
    
    //  sourceID = INDEX( 1, 1);
    //  targetID = INDEX( 99,99 );
    
    Node* pSourceNode = tileMap->GetCollisionGraph()->GetNode(sourceID);
    Node* pTargetNode = tileMap->GetCollisionGraph()->GetNode(targetID);
    
    double t1 = timer.getCurrentTime();
    
    Path path = pPathfinder->GetPath(  pSourceNode->m_Coord, pTargetNode->m_Coord );
    
    double t2 = timer.getCurrentTime();
    
    printf("\n Time Taken: %f ms", t2-t1);
    
    tileMap->HighlightTiles( path.vecNodeID );
}

void display ( void )   // Create The Display Function
{
    if( begin )
    {
        TestPathFinder();
        begin = false;
    }
    
    HandleInputFromUI();
    
    glClear(GL_COLOR_BUFFER_BIT);	// Clear Screen And Depth Buffe
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    if( tileMap )
    {
        
        tileMap->Render();
        
        PathManager::GetInstance()->Update();
    
        pUnitManager->Update(0.01);
    
        pUnitManager->Render();
    }
    
    if( eInputState == EIS_SELECT_ITEMS )
    {
                
        //Draw Selection Window
        DrawRect(  selectionStart, selectionEnd);
    }
    
    glutSwapBuffers();
}

void HandleInputFromUI()
{
    
}

void mouseFunc( int button, int state, int x, int y)
{
    Point2f P( x, h-y );
    
	// On LEFT Mouse Press
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
        bLeftButtonDown = true;	
		
        if( eInputState == EIS_SELECT_ITEMS )
        {
            selectionStart = P;
            selectionEnd   = P;
            printf("\n Selection Start: %f,%f", P.x, P.y);
        }
        
        else if( eInputState == EIS_MOVE_SELECTED_ITEMS )
        {
            
        }

    }
    
	// ON LEFT Mouse Release
	else if( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
	{
        bLeftButtonDown = false;
        
        if( eInputState == EIS_SOURCE_SET )
        {
            tileMap->SetSourcePosition( P );
        }
        else if( eInputState == EIS_TARGET_SET )
        {
            tileMap->SetTargetPosition( P );
            
            vector<int> vecIDs = tileMap->GetSpiralTileIDs(tileMap->GetTargetNodeID(), 8);
            printf("\n\n");
            for( int i=0; i<8;i++ )
                printf("\t ID = %d", vecIDs[i]);
        }
        else if (eInputState == EIS_CREATE_UNIT || eInputState == EIS_PLACE_UNIT)
        {
            P = P - tileMap->m_Offset;
            pUnitManager->CreateUnitAt( P );
        }
        else if (eInputState == EIS_MOVE_UNITS)
        {
            tileMap->SetTargetPosition( P );
            
            P = P - tileMap->m_Offset;
            pUnitManager->MoveUnitsTo( P );
        }
        else if( eInputState == EIS_DRAW_WALL || eInputState == EIS_PLACE_TOWER || eInputState == EIS_PLACE_HOUSE || eInputState == EIS_PLACE_BARRACKS)
        {
            tileMap->SetBrushRadius( ((int)eInputState + 1) );
            tileMap->OnLeftMouseClick( P.x, P.y );
            mouseClickPos = P;
        }
        
        else if( eInputState == EIS_SELECT_ITEMS )
        {
            // Finish creating the selection window
            
            // Select Units
            bool bSelectedUnits = pUnitManager->SelectUnits(selectionStart, selectionEnd);
            
            // If units have ben selected, then change state - The next click should cause these selected units to move the target location
            if( bSelectedUnits )
               eInputState = EIS_MOVE_SELECTED_ITEMS;
            
            // Reset Selction box
            selectionStart = P;
            selectionEnd = P;

        }
        else if( eInputState == EIS_MOVE_SELECTED_ITEMS )
        {
            tileMap->SetTargetPosition( P );
            
            P = P - tileMap->m_Offset;
            
            pUnitManager->MoveUnitsTo( P );
            
            // Once target has been set, unselect all units so that we can select another group
            pUnitManager->ClearSelectedUnitsList();
            
            eInputState = EIS_SELECT_ITEMS;
        }
        
                    
	}
    
    // ON RIGHT BUTTON DOWN
	else if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
	{
        bRightButtonDown = true;
    }
    
    // ON RIGHT Mouse Release
	else if( button == GLUT_RIGHT_BUTTON && state == GLUT_UP )
	{
        bRightButtonDown = false;
        
        tileMap->SetBrushRadius( (int)eInputState + 1 );
        
        tileMap->OnRightMouseClick( P.x, P.y );
        
        mouseClickPos = P;
	}
    
    glutPostRedisplay();
}

void mouseDragFunc(  int x, int y)
{	
    Point2f P( x, h-y );
    
    // DRAG EVENTS ONLY WORK for DRAWING WALLS
    
    if( eInputState == EIS_SELECT_ITEMS )
    {
        if( bLeftButtonDown )
        {
            selectionEnd = P;
            glutPostRedisplay();
            
            printf("\n Selection End: %f,%f", P.x, P.y);
        }
    }
    
    if( eInputState != EIS_COLLIDER_DRAW && eInputState != EIS_DRAW_WALL )
        return;
    
    if( bLeftButtonDown )
        tileMap->OnLeftMouseClick( P.x, P.y );
    
    if( bRightButtonDown )
        tileMap->OnRightMouseClick( P.x, P.y );
    
    glutPostRedisplay();
}


void mouseMoveFunc(  int x, int y)
{	
	/*{
     int index = PickControlPoint(x, y);
     
     if( index >=0 )
     {
     glutSetCursor(GLUT_CURSOR_INFO);
     }
     else
     {
     glutSetCursor(GLUT_CURSOR_CROSSHAIR);
     }
     
     
     }*/
}

void DrawPoint( int x, int y)
{
	glColor4f( 1.0f, 0.0f,0.0f ,1.0f);
	glPointSize(8.0f);
	
	glBegin( GL_POINTS );
		glVertex2f( x, y);
	glEnd();
	
	glFlush();
}

void DrawLine( Point2f p1, Point2f p2 )
{
	
	glBegin( GL_LINES );
		glVertex2f( p1.x, p1.y);
		glVertex2f( p2.x, p2.y);
	glEnd();
	
	glFlush();
	
}

void reshape ( int w , int h )   // Create The Reshape Function (the viewport)
{
	glViewport     ( 0, 0, w, h );
	
    glMatrixMode   ( GL_PROJECTION );  // Select The Projection Matrix
	
    glLoadIdentity ( );                // Reset The Projection Matrix

    gluOrtho2D(0.0, w, 0.0, h);
    
    glutPostRedisplay();
}

void keyboardPress ( unsigned char keyPress, int x, int y )  // Create Keyboard Function
{
	switch ( keyPress ) 
	{
        // 0-9: sets the brush size
        case '0':
        case '1': 
        case '2':
        case '3': 
        case '4':
        case '5': 
        case '6':
        case '7': 
        case '8':
        case '9': 
            tileMap->SetBrushRadius(keyPress - 48);
            break;
            
		case 'w':   
        {
            begin = true;
//            Point2f source( 25,25 );
//            Point2f target( 2,2 );
//            
//            Path path = pPathfinder->GetPath( source, target);
//            
//            printf("\n Size of Path = %d", path.vecNodeID.size());
//            tileMap->HighlightTiles( path.vecNodeID );
            
        }
			break;
			
		case 's':               // Set Source
            eInputState = EIS_SOURCE_SET;
			break;
			
		case 'a':               // When Down Arrow Is Pressed...
            eInputState = EIS_COLLIDER_DRAW;
			break;
			
		case 'd':               // Set Destination
            eInputState = EIS_TARGET_SET;
			break;
			
        case 'r':               // Refresh
            tileMap->Refresh();
			break;
   
        case 'u':
            eInputState = EIS_CREATE_UNIT;
            break;

        case 'm':
            eInputState = EIS_MOVE_UNITS;
            break;
            
        
		case 'q':               // When Down Arrow Is Pressed...
			exit(0);
			break;
	
		default:
			break;
	}
	
	glutPostRedisplay();
}

void keyboardRelease( unsigned char key, int x, int y )  // Create Keyboard Function
{
	
}

void arrow_keys_Press ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
	
	switch ( a_keys ) 
	{
		case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
			break;
			
		case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
			break;
			
		case GLUT_KEY_LEFT:               // When Down Arrow Is Pressed...
			break;
			
		case GLUT_KEY_RIGHT:               // When Down Arrow Is Pressed...
			break;
			
		default:
			break;
	}
}

void arrow_keys_Release ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
	
	switch ( a_keys ) 
	{
		case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
			break;
			
		case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
			break;
			
		case GLUT_KEY_LEFT:               // When Down Arrow Is Pressed...
			break;
			
		case GLUT_KEY_RIGHT:               // When Down Arrow Is Pressed...
			break;
			
		default:
			break;
	}	 
}

int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
	glutInit            ( &argc, argv ); // Erm Just Write It =
	
    glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE); // Display Mode
	
    glutInitWindowSize  ( w, h ); // If glutFullScreen wasn't called this is the window size
	
    glutInitWindowPosition( 360, 0 );
    main_window =  glutCreateWindow    ( "Path Finder" ); // Window Title (argv[0] for current directory as title)
													   //glutFullScreen      ( );          // Put Into Full Screen
	glutMouseFunc(mouseFunc);
	
    glutMotionFunc(mouseDragFunc);
	
    glutPassiveMotionFunc(mouseMoveFunc);
	
    glutDisplayFunc( display );  // Matching Earlier Functions To Their Counterparts
	
    glutIdleFunc(display);
    
    //glutReshapeFunc     ( reshape );
	
    glutKeyboardFunc    ( keyboardPress );
	
    //glutSpecialFunc     ( arrow_keys );
	
    InitApp();
    
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	
	glutMainLoop( );          // Initialize The Main Loop	
}

