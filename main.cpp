#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <sstream>
#include "utils.h"
#include "pieces.h" 
#include "functionality.h" 
using namespace sf;

int main(){
    srand(time(0));

    // Runs the main menu
    runMainMenu();
    

    // Window for actual game
    RenderWindow window(VideoMode(640, 480), title);
    Texture obj1, obj2, obj3;

    
    
    // Loading textures 
    obj1.loadFromFile("/home/kali/Desktop/First Semester Project/img/tiles.png");
    obj2.loadFromFile("/home/kali/Desktop/First Semester Project/img/tetris background final.png");
    obj3.loadFromFile("/home/kali/Desktop/First Semester Project/img/frame.png");

    // Loading font
    Font font;
    font.loadFromFile("/home/kali/Desktop/First Semester Project/Font/Faster Stroker.ttf");
    
    Sprite sprite(obj1), background(obj2), frame(obj3);
    int delta_x=0;
    float timer=0, delay=0.65;
    bool rotate=0;
    Clock clock;

    // For first block
        n=rand()%4;
        for (int i=0;i<4;i++){
            point_1[i][0] = BLOCKS[n][i] % 2;
            point_1[i][1] = BLOCKS[n][i] / 2;
        }

    // For copied block
        m = rand() % 4;
        for (int i = 0 ; i<4 ; i++)
                {
                    point_4[i][0]=BLOCKS[m][i]%2;
                    point_4[i][1]=BLOCKS[m][i] /2;

                }
        colorNum_next=(rand()%7)+1;
    
    
    // For shadow of pieces
    RectangleShape square(Vector2f(18.f, 18.f));
    square.setFillColor(Color::Transparent);
    square.setOutlineColor(Color::White);
    square.setOutlineThickness(-1.f);

    // Score board
    RectangleShape score_box(Vector2f(190.f, 250.f));
    score_box.setFillColor(Color::White);
    score_box.setPosition(420, 50);

    RectangleShape score_rectangle(Vector2f(160.f, 60.f));
    score_rectangle.setFillColor(Color::Black);
    score_rectangle.setPosition(score_box.getPosition()+Vector2f(15, 10));
    Text score_txt;
    score_txt.setFont(font);
    stringstream scores;
    scores << "Score\n" << score;
    score_txt.setString(scores.str()); 
    score_txt.setCharacterSize(14);
    score_txt.setFillColor(Color::White);
    score_txt.setPosition(score_rectangle.getPosition()+Vector2f(5,1));

    RectangleShape level_rectangle(Vector2f(160.f, 60.f));
    level_rectangle.setFillColor(Color::Black);
    level_rectangle.setPosition(score_box.getPosition()+Vector2f(15, 90));
    Text level_txt;
    level_txt.setFont(font);
    level_txt.setString("Level");
    level_txt.setCharacterSize(14);
    level_txt.setFillColor(Color::White);
    level_txt.setPosition(level_rectangle.getPosition()+Vector2f(5,1));

    RectangleShape lines_rectangle(Vector2f(160.f, 60.f));
    lines_rectangle.setFillColor(Color::Black);
    lines_rectangle.setPosition(score_box.getPosition()+Vector2f(15, 170));
    Text lines_txt;
    lines_txt.setFont(font);
    lines_txt.setString("Lines Completed");
    lines_txt.setCharacterSize(14);
    lines_txt.setFillColor(Color::White);
    lines_txt.setPosition(lines_rectangle.getPosition()+Vector2f(2,1));

    // For Next Pieces
    RectangleShape pieces_box(Vector2f(160.f, 130.f));
    pieces_box.setFillColor(Color::White);
    pieces_box.setPosition(245, 50);

    RectangleShape nextPiece_rectangle(Vector2f(130.f, 110.f));
    nextPiece_rectangle.setFillColor(Color::Black);
    nextPiece_rectangle.setPosition(pieces_box.getPosition()+Vector2f(15, 10));
    Text nextPiece_txt;
    nextPiece_txt.setFont(font);
    nextPiece_txt.setString("Next Piece");
    nextPiece_txt.setCharacterSize(14);
    nextPiece_txt.setFillColor(Color::White);
    nextPiece_txt.setPosition(nextPiece_rectangle.getPosition()+Vector2f(5,1));

    // Theme music
    Music theme_music;
    theme_music.openFromFile("/home/kali/Desktop/First Semester Project/Music/Theme.mp3");
    theme_music.setLoop(true);
    theme_music.play();

    // Game over Music
    Music game_over_music;
    game_over_music.openFromFile("/home/kali/Desktop/First Semester Project/Music/Game_over.wav");

    // The Game Loop
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)
                    suddenDrop();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05


        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        fallingPiece(timer, delay, colorNum_next);               //Example: fallingPiece() function is called here
        move(delta_x);
        rotation(rotate);
        shadowPiece();
        elimination_N_scoring();
        if(gameOver()){
            theme_music.stop();
            game_over_music.play();
            window.close();
            gameOverWindow();
            // break;
        }
        leveling();
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
        delta_x = 0;
        rotate = false;
        
        // Draws the background
        window.clear(Color::Black);        
        window.draw(background);

        // Sets the game grid
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        } 

        
        // Sets the texture to blocks
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }

        // Sets the position of shadow of blocks
        for (int i=0; i<4; i++){
            square.setPosition(point_3[i][0]*18,point_3[i][1]*18);
            square.move(28,31);
            window.draw(square);

          }

        // Setting the scores to the score board
        scores.clear();
        scores.str("");
        scores << "Score\n" << score;
        score_txt.setString(scores.str());

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);

        // Drawing the complete score box
        window.draw(score_box);
        window.draw(score_rectangle);
        window.draw(score_txt);
        window.draw(level_rectangle);
        scores.clear();
        scores.str("");
        scores << "Level\n" << level;
        level_txt.setString(scores.str());
        window.draw(level_txt);
        window.draw(lines_rectangle);
        window.draw(lines_txt);

        // Setting lines completed on the score board
        scores.clear();
        scores.str("");
        scores << "Lines Completed\n" << lines_cl;
        lines_txt.setString(scores.str());

        // Drawing the next pieces box
        window.draw(pieces_box);
        window.draw(nextPiece_rectangle);
        window.draw(nextPiece_txt);

        // Drawing the next piece
        for (int i=0; i<4; i++){
            
            if(m==3){
            sprite.setTextureRect(IntRect(colorNum_next*18,0,18,18));
            sprite.setPosition(nextPiece_rectangle.getPosition()+Vector2f(point_4[i][0]*18+30, point_4[i][1]*18+40));
            window.draw(sprite);
            }
            else{
            sprite.setTextureRect(IntRect(colorNum_next*18,0,18,18));
            sprite.setPosition(nextPiece_rectangle.getPosition()+Vector2f(point_4[i][0]*18+30, point_4[i][1]*18+25));
            window.draw(sprite);
            }
          }

        if(!start_game)
            window.close();

        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }

    return 0;
}
