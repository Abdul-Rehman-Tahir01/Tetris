//---Title: PF-Project, Fall-2022 for BS(CS)---//
const char title[] = "FoP-Project, Fall-2023";

// Some globally declared varaibles used in program
int n, m, score=0, level=1  , lines_cl = 0, colorNum_next=1, colorNum=1 ;
bool start_game=1;

//---Height and Width of the Actual Interactive Game---//
const int M = 20;   //Number of rows for a piece to cover on the screen (not the entire screen) = 20
const int N = 10;   //Number of columns for a piece to cover on the screen (not the entire screen) = 10

//---The Actual Interactive Game Grid - Built Over (MxN)---//
int gameGrid[M][N] = {0};

//---To Hold the Coordinates of the Piece---//
int point_1[4][2], point_2[4][2],
    point_3[4][2],  // For shadow
    point_4[4][2] ; // for the next piece    

// For main menu
enum MenuOption {
    START,
    EXIT_GAME
};

//---Check Uncertain Conditions---//
// Checks the anamoly for actual pieces
bool anamoly(){
    for (int i=0;i<4;i++)
        if (point_1[i][0]<0 || point_1[i][0]>=N || point_1[i][1]>=M)
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;
        
    return 1;
};

// Checks the anamoly for shadow of pieces
bool shadowAnamoly(){
    for (int i=0;i<4;i++)
        if (point_3[i][0]<0 || point_3[i][0]>=N || point_3[i][1]>=M)
            return 0;
        else if (gameGrid[point_3[i][1]][point_3[i][0]])
            return 0;

    return 1;
}