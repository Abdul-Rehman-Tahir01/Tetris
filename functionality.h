#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

RenderWindow main_menu;

// Used to print grid in the terminal
void print_grid()
 {   
    for (int i = 0; i < M; i++)
       {
            for (int j = 0; j < N; j++)
                cout << gameGrid[i][j] << ' ';
            cout << '\n';
        }
    cout << "---------------------------------"<<endl;
}


//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum_next){
    print_grid();
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
        // For first level, only first four pieces are unlocked.
            if(level==1)
                {
                
                    
                    for (int i=0;i<4;i++){
                    gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
                    point_1[i][0]=point_4[i][0];
                    point_1[i][1]=point_4[i][1];
                }
                colorNum = colorNum_next;

                m = rand()%4;
                for (int i = 0 ; i<4 ; i++)
                {
                    point_4[i][0]=BLOCKS[m][i]%2;
                    point_4[i][1]=BLOCKS[m][i]/2;
                }

            // Changes the color of each piece as soon as they start falling
                colorNum_next=(rand()%7)+1;
            }

        // For second level, all pieces are unlocked.
            else 
                {
                for (int i=0;i<4;i++){
                    gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
                    point_1[i][0]=point_4[i][0];
                    point_1[i][1]=point_4[i][1];
                }
                colorNum = colorNum_next;

                m = rand()%7;
                for (int i = 0 ; i<4 ; i++)
                {
                    point_4[i][0]=BLOCKS[m][i]%2;
                    point_4[i][1]=BLOCKS[m][i]/2;

                }
            // Changes the color of each piece as soon as they start falling
            colorNum_next=(rand()%7)+1;
            }
        }
        timer=0;
    }
    // Changes the delay time of falling pieces according to level
    level==1 ? delay=0.65 : delay=0.2;
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

// Left Right Movement 
void move(int& delta_x){
    for(int i=0; i<4; i++){
        point_2[i][0]= point_1[i][0];
        point_1[i][0] += delta_x;
    }
    if(!anamoly()){
            for(int i=0; i<4; i++)
                point_1[i][0]= point_2[i][0];
    }
}

// Rotation
void rotation(bool rotate){
    if (rotate && n!=3){
    if (n >= 0 && n < 7){
        int centerX = point_1[1][0];
        int centerY = point_1[1][1];
        

        for (int i = 0; i < 4; ++i) 
        {
            point_2[i][0]= point_1[i][0];
            point_2[i][1]= point_1[i][1];

            int x_not = point_1[i][0]-centerX;
            int y_not = point_1[i][1]-centerY;

            int x_bar = -y_not;
            int y_bar = x_not;
            int newX = x_bar + centerX;
            int newY = y_bar + centerY;

            point_1[i][0] = newX;
            point_1[i][1] = newY;
        }
        
        if(!anamoly()){
            for(int i=0; i<4; i++){
            point_1[i][0]= point_2[i][0];
            point_1[i][1]= point_2[i][1];
            }
        }
    }
    }
}

// To drop piece without any delay
void suddenDrop()
{
    for(int i=0; i<4; i++){
        point_1[i][0] = point_3[i][0];
        point_1[i][1] = point_3[i][1];
    }
}

// Shadow of the piece
void shadowPiece(){
    for(int i=0; i<4; i++){
        point_3[i][0] = point_1[i][0];
        point_3[i][1] = point_1[i][1];
        
    } 
    
    while(shadowAnamoly()){
        for(int i=0; i<4; i++){
            point_3[i][1]++;
        }
    }
    for(int i=0; i<4; i++){
            point_3[i][1]--;
        }
}

// Elimination and scoring of lines that are completed
void elimination_N_scoring(){

        int count=0, j=0, k=0, count1=0;
    for(int i=0; i<M; i++){
        count=0;
        for( j=0; j<N; j++){
            if(gameGrid[i][j]!=0){ 
                count++;
            }
        }

        if(count==10)
         {  
            lines_cl++;
            count1++;
            for (k=0; k<N; k++)
                gameGrid[i][k]=0;

            for (int p = i; p > 0; p--)
            {
                swap(gameGrid[p], gameGrid[p - 1]);
            }

         }
    }
                // Scoring for line deletion  
                    if(count1==1)
                        score += (level*10);
                    if(count1==2)
                        score += (level*30);
                    if(count1==3)
                        score += (level*60);
                    if(count1==4)
                        score += (level*100);
                
                    count1=0;


    // RectangleShape scores(Vector2f(40.f, 40.f));
}

// Game Over
bool gameOver()
{
        int count = 0 ;

        for(int j=0; j<N; j++){
            if(gameGrid[0][j]!=0)
            {   
                cout<<"\n\n GAME OVER ";
                return 1;
            }
            
        }
        return 0 ; 
}

// Generates the game over window
void gameOverWindow(){
    RenderWindow game_over_window(VideoMode(640, 480), "Game Over");

    Font font;
    font.loadFromFile("/home/kali/Desktop/First Semester Project/Font/Faster Stroker.ttf");
    
    Text title("Game\nOver", font, 80);
    title.setPosition(200, 30);

    Texture background;
    background.loadFromFile("/home/kali/Desktop/First Semester Project/img/tetris background final.png");
    Sprite background_game_over(background);

    while(game_over_window.isOpen()){
        
        Event game_over_event;
        while(game_over_window.pollEvent(game_over_event)){
            if(game_over_event.type == Event::Closed) 
                game_over_window.close();
        }
        game_over_window.clear();
        game_over_window.draw(background_game_over);
        game_over_window.draw(title);
        game_over_window.display();
    }

}

// Level up
void leveling(){
    if(score>199)
        level = 2;  // If score reaches 200, level up.

}

// For main menu's mouse click event handling
bool handleMouseClick(const Vector2i& mousePos, const Text& optionText, MenuOption& selectedOption) {
    Font font;
    font.loadFromFile("/home/kali/Desktop/First Semester Project/Font/Faster Stroker.ttf");
    if (optionText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        if (optionText.getString() == "Start") {
            cout << "Starting Tetris Game!" << endl;
            start_game=1;
        }
        else if (optionText.getString() == "Exit Game") {
            cout << "Exiting Game!" << endl;
            start_game=0;
        }

    }
    if(start_game)
        return 1;
    else 
        return 0;
}

// Main menu
void runMainMenu(){
    // Window for tetris main menu
    RenderWindow main_menu(VideoMode(640, 480), "Tetris Main Menu");

    int count=0;
    Font font;
    font.loadFromFile("/home/kali/Desktop/First Semester Project/Font/Faster Stroker.ttf");

    Text title("Tetris", font, 70);
    title.setPosition(200, 10);
    
    Texture background;
    background.loadFromFile("/home/kali/Desktop/First Semester Project/img/tetris background final.png");
    Sprite background_main_menu(background);

    vector<Text> menuOptions;
    menuOptions.emplace_back("Start", font, 30);
    menuOptions.emplace_back("Exit Game", font, 30);

    for (size_t i = 0; i < menuOptions.size(); ++i) {
        menuOptions[i].setPosition(240, 150 + i * 60);
    }

    MenuOption selectedOption = START;

    while (main_menu.isOpen()) {
        count++;
        Event event;
        while (main_menu.pollEvent(event)) {
            if (event.type == Event::Closed) {
                main_menu.close();
                start_game=0;
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(main_menu);
                    for (size_t i = 0; i < menuOptions.size(); ++i) {
                        if (menuOptions[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            start_game = handleMouseClick(mousePos, menuOptions[i], selectedOption);
                            if(start_game)
                                goto close;
                        }
                    }
                }
            }
        }
        
        main_menu.clear();
        main_menu.draw(background_main_menu);
        main_menu.draw(title);
        for (const auto& option : menuOptions) {
            main_menu.draw(option);
        }
        
        main_menu.display();
        if(!start_game)
            goto close;
    }
        if(false)
        {close:
        main_menu.close();}
        
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
