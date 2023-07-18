#include<iostream>
#include<cstring>
#include<conio.h>
#include<ctime>

#include<list>
#include <cstdlib> //for using srand() and rand()
#include <string>

using namespace std;
//Defining Macros
#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 // (25 * 25 - 99)

///////////////////////////////////TIC TAC TOE DEFINITIONS////////////////////////////////////////////////
    typedef struct{
    int *row;
}WinList;
 
 
class Player {
    //player class with name and score.
private:
    string name;
    int score;
public:
//default constructor if no name assigned
    Player() :Player {""}
    {
    }
    //parameterised constructor 
    Player(string n) :score{0}, name{n}
    {}
 
    void won(){
        //increment the score
        score++;
    }
    int getScore(){ return this->score;}
 
    string getName(){ return this->name;}
};
 
class Game {
private:
    char tictacboard[9];
    int emptyIndex[9];
    int gameOn, againstComputer;
    int emptyCount;
    
    //For storing all 8 types of win combinations........
    WinList winlist[8]; 
 
    void displayBoard(){
        cout <<endl;
        cout << "   |   |   "<<endl;

        cout << " "<< tictacboard[0] <<" | "<<tictacboard[1]<<" | "<<tictacboard[2]<<endl;

        cout << "   |   |   "<<endl;

        cout << "-----------"<<endl;

        cout << "   |   |   "<<endl;
        
        cout << " "<< tictacboard[3] <<" | "<<tictacboard[4]<<" | "<<tictacboard[5]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;

        cout << "   |   |   "<<endl;

        cout << " "<< tictacboard[6] <<" | "<<tictacboard[7]<<" | "<<tictacboard[8]<<endl;

        cout << "   |   |   "<<endl;

        cout <<endl;

    }
 
    void computerInput(){
        //pos for assigning position for input
        int pos;
        //pos takes a random value between 1 to 9

        pos = rand()%10;
        //checking if that random value is empty for input or not
        if(emptyIndex[pos] == 1){

            /*check if we are getting non empty index then
             check whether empty count(no. of empty boxes left) is >0 or not*/
            if(emptyCount < 0)
                return;
            computerInput();
        } else {

            cout<< "Computer choose: " << pos+1 << endl;
            emptyIndex[pos] =1;
            emptyCount-=1;

            tictacboard[pos] = 'O';
        }
 
    }
 
    void playerInput(Player &player){
        int pos;
        cout << endl;

        cout << "\t" << player.getName() <<" Turn: ";
        cout <<"\t Enter the position " << endl;

        cin >> pos;

        //POS needs actual index value so subtracting by 1
        
        pos =pos-1;
        if(emptyIndex[pos] == 1){

            cout << "-----Position not empty-------"<< endl;
            playerInput(player);


        } else {
            emptyIndex[pos] =1;
            
            emptyCount-=1;     //no. of empty places for input has now decreased by 1.

            
            /*compare current player with string "player 1";
            
             If true then assign X at the input position; If false assign O*/

            player.getName().compare("Player I") == 0 ? tictacboard[pos] ='X': tictacboard[pos] ='O';
        }
 
    }
 
    void checkWin(Player &p1,Player &p2){
        int i,j,k;
        bool flag = false;

        char first_symbol;
        //Start checking all the possible combination to win as stored in the winlist struct


        for(i=0; i<8; i++){
            //Assign the first character of win combination to char first_symbol
            first_symbol = tictacboard[winlist[i].row[0]];

 
            //IF first_symbol is neither X nor o then win combination not possible...continue and move onto next win combination.

            if((first_symbol != 'X') && (first_symbol != 'O')){ 
                flag = false;
                continue;
            }
            /*IF first_symbol is X or O then check for all the index required to complete a combination
            if anywhere combination breaks make flag= false.*/
            flag = true;
            for(j=0;j<3;j++){

                if(first_symbol != tictacboard[winlist[i].row[j]]){
                    flag = false;
                    break;


                }
            }
            /*If flag is still true means we got one whole win combination correct. Check whether the first_symbol was X(player 1 wins)
            or O(player 2 wins)*/
            if(flag){

                //if flag is true means combination completed then assign gameon=0 that is game ended.
                gameOn = 0;
               
                /*Check whether the first_symbol was X(player 1 wins)

            or O(player 2 wins)*/
            
                if(first_symbol == 'X'){
                    cout << "-----------------------"<< endl;
                    cout << "\t Player I WON"<< endl;
                    cout << "-----------------------"<< endl;

                    p1.won();
                } else {
                    p2.won();
                    if(againstComputer){
                        cout << "-----------------------"<< endl;
                        cout << "\t Computer WON"<< endl;


                        cout << "-----------------------"<< endl;
                    } else {
                        cout << "-----------------------"<< endl;
                        cout << "\t Player II WON"<< endl;
                        cout << "-----------------------"<< endl;
 
                    }
                }
                displayScore(p1,p2);
                break;
            }



        }
    }
    
 

        void play(Player &p1,Player &p2){
            char rematch ='\0';
            //assigning hand =0 so that player1 starts first. After player 1's turn hand will be assigned 1 so that it is 
            int hand = 0;
            gameOn =1;

            displayBoard();
            /*************************Loop only works until there are input empty boxes left(originally=9)
             * 
            if emptycount variable goes to 0 loop terminates and game ends in draw i.e.,
             no winner _______________--
             or if gameon variable changes value to zero in the checkwin function as a player might have completed a combination already.

             then also the game ends.................*/
            while((emptyCount > 0) && (gameOn != 0)){
 
                if(againstComputer)
                    hand == 1 ? computerInput(): playerInput(p2);
                else
                    hand == 1 ? playerInput(p1): playerInput(p2);
                
                //here assigning hand opposite of current value so that next player can input according to the ternary operator above

                hand= !hand;
                displayBoard();
                checkWin(p1,p2);
            }

            if (emptyCount <=0){
                cout<<"      GAME ENDED ! "<<endl;

                cout << "      -----------------------"<< endl;
                cout << "\t No WINNER"<< endl;

                cout << "      -----------------------"<< endl;
            }
            cout<< endl;
            cout << "Rematch Y/N: ";
            cin >> rematch;
            if((rematch == 'Y')||(rematch == 'y')){
                init();
                play(p1,p2);
            }
 
        }
    void displayScore(Player &p1, Player &p2){
        //display the final score depending on number of matches played consecutively.

        cout << endl;

        cout << "\t SCORE: \t";
        if(againstComputer)

            cout<<" Player I: " <<p1.getScore()<<" \t Computer: "<<p2.getScore()<< endl;
        else
            cout<<" Player I: " <<p1.getScore()<<" \t Player II: "<<p2.getScore()<< endl;
    }
 
public:
//by default giving some default value when creating a new game type object
    Game(): emptyCount{0}, gameOn{1}, againstComputer{0}{
        
        /*init function called to initialise the starting values


         for tictacboard,emptyinex and emptycount arrays and vairable.*/
        
        init();
        /*winlist sstruct has 2d arrays containing no. of possible win combinations=8

        thus each index of winlist is assigned a possible combination array,
        whose members can be accessed using row pointer.*/

        winlist[0].row = new int[3]{0,1,2};

        winlist[1].row = new int[3]{3,4,5};
        
        winlist[2].row = new int[3]{6,7,8};
        winlist[3].row = new int[3]{0,3,6};
        winlist[4].row = new int[3]{1,4,7};
        
        winlist[5].row = new int[3]{2,5,8};
        winlist[6].row = new int[3]{0,4,8};
        
        winlist[7].row = new int[3]{2,4,6};
    }
 
    void init(){


        //game on declares that the game is running if assigned 1
        gameOn = 1;

        //empty count i.e. no. of empty boxes for input assigned 9 as there are 9 boxes at start.
        emptyCount =9;

        srand(time(0));   


        //SRAND() gives a starting point for producing the pseudo-random integer series.



        for(int i=0; i<10; i++){
            /*all position of emptyindex array assigned zero at start,
            indicating that these postitions are open for input*/

            emptyIndex[i] = 0;

            /*tictacboard assigned numbers so that user 
            

            can easily identify the position he wants to assign his move*/
            tictacboard[i] = (i+1) +'0';
            //emptyCount++;
        }
        //emptyCount--;
    }
 
    void onePlayerGame(){
        //Creating Player
        Player p("Player I");
        /*creating second player named computer which will call the computer input function
         for taking values instead of user defined values*/

        Player c("Computer");
        cout << "       -----------------------"<< endl;
        cout << "\t Player I: X \t Computer: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        //as one player game hence assgining againstcomputer=1.


        againstComputer = 1;
        //calling play function to begin the game.
        play(c,p);
 
    }
 
    void twoPlayerGame(){
        //Creating Player
        Player p("Player I");
        Player c("Player II");

        cout << "       -----------------------"<< endl;
        cout << "\t Player I: X \t Player II: O"<< endl;

        cout << "       -----------------------"<< endl;

        cout << endl;
        //as two  player game hence assgining againstcomputer=0.
        againstComputer = 0;
        //calling play function to begin the game

        play(c,p);
    }
};
//*********************************MINESWEEPER FUNCTIONS****************************************************************8

    //Functions declarations
//Functions declarations
void title();
bool isValid(int row, int col);
bool isMine (int row, int col, char board[][MAXSIDE]);
void makeMove(int *x, int *y);
void printBoard(char myBoard[][MAXSIDE]);
int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][MAXSIDE]);
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], int mines[][2], int row, int col, int *movesLeft);
void placeMines(int mines[][2], char realBoard[][MAXSIDE]);
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE]);
void cheatMinesweeper (char realBoard[][MAXSIDE]);
void replaceMine (int row, int col, char board[][MAXSIDE]);
void playMinesweeper ();
void chooseDifficultyLevel ();

//Declaring Variables
int SIDE ; // side length of the board
int MINES ; // number of mines on the board

//Game Title Screen
void title()
{
    printf("\n\n\n\n\n\n\n\t\t\t\t*****************************************");
    printf("\n\t\t\t\t*\t\tWELCOME TO\t\t*");
    printf("\n\t\t\t\t*\t     MINESWEEPER GAME !!        *");
    printf("\n\t\t\t\t*****************************************");
    printf("\n\n\n\n\n Press any key to continue......\n");
    getch();        //Use to holds screen for some seconds
    system("cls");  //Use to clear screen
}

// A Function to check whether given cell (row, col) is a valid cell or not
bool isValid(int row, int col)
{
    // Returns true if row number and column number is in range
    return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

// A Function to check whether given cell (row, col) has a mine or not.
bool isMine (int row, int col, char board[][MAXSIDE])
{
    if (board[row][col] == '*')
        return (true);
    else
        return (false);
}

// A Function to get the user's move
void makeMove(int *x, int *y)
{
    // Take the input move
    cout<<"Enter your move, (row, column) -> ";
    cin>>*x>>*y;
    return;
}

// A Function to print the current GamePlay board
void printBoard(char myBoard[][MAXSIDE])
{
    int i, j;

    cout<<"    ";

    for (i=0; i<SIDE; i++)
        cout<<i<<" ";

    cout<<"\n\n";

    for (i=0; i<SIDE; i++)
    {
        cout<<i<<"   ";

        for (j=0; j<SIDE; j++)
        {
            cout<< myBoard[i][j]<<" ";
        }
        cout<<"\n";
    }
    return;
}

// A Function to count the number of mines in the adjacent cells
int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][MAXSIDE])
{

    int i;
    int count = 0;

    /*
        Count all the mines in the 8 adjacent
        cells

            N.W   N   N.E
              \   |   /
               \  |  /
            W----Cell----E
                 / | \
               /   |  \
            S.W    S   S.E

        Cell-->Current Cell (row, col)
        N -->  North        (row-1, col)
        S -->  South        (row+1, col)
        E -->  East         (row, col+1)
        W -->  West         (row, col-1)
        N.E--> North-East   (row-1, col+1)
        N.W--> North-West   (row-1, col-1)
        S.E--> South-East   (row+1, col+1)
        S.W--> South-West   (row+1, col-1)
    */

    //----------- 1st Neighbour (North) ------------

    // Only process this cell if this is a valid one
    if (isValid (row-1, col) == true)
    {
        if (isMine (row-1, col, realBoard) == true)
            count++;
    }

    //----------- 2nd Neighbour (South) ------------

    // Only process this cell if this is a valid one
    if (isValid (row+1, col) == true)
    {
        if (isMine (row+1, col, realBoard) == true)
            count++;
    }

    //----------- 3rd Neighbour (East) ------------

    // Only process this cell if this is a valid one
    if (isValid (row, col+1) == true)
    {
        if (isMine (row, col+1, realBoard) == true)
            count++;
    }

    //----------- 4th Neighbour (West) ------------

    // Only process this cell if this is a valid one
    if (isValid (row, col-1) == true)
    {
        if (isMine (row, col-1, realBoard) == true)
            count++;
    }

    //----------- 5th Neighbour (North-East) ------------

    // Only process this cell if this is a valid one
    if (isValid (row-1, col+1) == true)
    {
        if (isMine (row-1, col+1, realBoard) == true)
            count++;
    }

    //----------- 6th Neighbour (North-West) ------------

    // Only process this cell if this is a valid one
    if (isValid (row-1, col-1) == true)
    {
        if (isMine (row-1, col-1, realBoard) == true)
            count++;
    }

    //----------- 7th Neighbour (South-East) ------------

    // Only process this cell if this is a valid one
    if (isValid (row+1, col+1) == true)
    {
        if (isMine (row+1, col+1, realBoard) == true)
            count++;
    }

    //----------- 8th Neighbour (South-West) ------------

    // Only process this cell if this is a valid one
    if (isValid (row+1, col-1) == true)
    {
        if (isMine (row+1, col-1, realBoard) == true)
            count++;
    }

    return (count);
}

// A Recursive Function to play the Minesweeper Game
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], int mines[][2], int row, int col, int *movesLeft)
{

    // Base Case of Recursion
    if (myBoard[row][col] != '-')
        return (false);

    int i, j;

    // You opened a mine
    // You are going to lose
    if (realBoard[row][col] == '*')
    {
        myBoard[row][col]='*';

        for (i=0; i<MINES; i++)
        {
            myBoard[mines[i][0]][mines[i][1]]='*';
        }
        printBoard (myBoard);
        cout<<"\nYou lost!\n";
        return (true) ;
    }

    else
    {
        // Calculate the number of adjacent mines and put it on the board
        int count = countAdjacentMines(row, col, mines, realBoard);
        (*movesLeft)--;

        myBoard[row][col] = count + '0';

        if (!count)
        {
            /*
            Recur for all 8 adjacent cells

                N.W   N   N.E
                  \   |   /
                      \  |  /
                W----Cell----E
                     / | \
                   /   |  \
                S.W    S   S.E

            Cell-->Current Cell (row, col)
            N -->  North        (row-1, col)
            S -->  South        (row+1, col)
            E -->  East         (row, col+1)
            W -->  West         (row, col-1)
            N.E--> North-East   (row-1, col+1)
            N.W--> North-West   (row-1, col-1)
            S.E--> South-East   (row+1, col+1)
            S.W--> South-West   (row+1, col-1)
            */

            //----------- 1st Neighbour (North) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col) == true)
            {
                if (isMine (row-1, col, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
            }

            //----------- 2nd Neighbour (South) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col) == true)
            {
                if (isMine (row+1, col, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
            }

            //----------- 3rd Neighbour (East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row, col+1) == true)
            {
                if (isMine (row, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
            }

            //----------- 4th Neighbour (West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row, col-1) == true)
            {
                if (isMine (row, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
            }

            //----------- 5th Neighbour (North-East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col+1) == true)
            {
                if (isMine (row-1, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
            }

            //----------- 6th Neighbour (North-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row-1, col-1) == true)
            {
                if (isMine (row-1, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
            }

            //----------- 7th Neighbour (South-East) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col+1) == true)
            {
                if (isMine (row+1, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
            }

            //----------- 8th Neighbour (South-West) ------------

            // Only process this cell if this is a valid one
            if (isValid (row+1, col-1) == true)
            {
                if (isMine (row+1, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
            }
        }

        return (false);
    }
}

// A Function to place the mines randomly on the board
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
    bool mark[MAXSIDE*MAXSIDE];

    memset (mark, false, sizeof (mark));

    // Continue until all random mines have been created.
    for (int i=0; i<MINES; )
    {
        int random = rand() % (SIDE*SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

        // Add the mine if no mine is placed at this
        // position on the board
        if (mark[random] == false)
        {
            // Row Index of the Mine
            mines[i][0]= x;
            // Column Index of the Mine
            mines[i][1] = y;

            // Place the mine
            realBoard[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }

    return;
}

// A Function to initialize the game
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
    // Initiate the random number generator so that the same configuration doesn't arises
    srand(time (NULL));

    // Assign all the cells as mine-free
    for (int i=0; i<SIDE; i++)
    {
        for (int j=0; j<SIDE; j++)
        {
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }

    return;
}

// A Function to cheat by revealing where the mines are
// placed.
void cheatMinesweeper (char realBoard[][MAXSIDE])
{
    cout<<"The mines locations are-\n";
    printBoard (realBoard);
    return;
}

// A function to replace the mine from (row, col) and put
// it to a vacant space
void replaceMine (int row, int col, char board[][MAXSIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        for (int j=0; j<SIDE; j++)
        {
            // Find the first location in the board
            // which is not having a mine and put a mine
            // there.
            if (board[i][j] != '*')
            {
                board[i][j] = '*';
                board[row][col] = '-';
                return;
            }
        }
    }
    return;
}

// A Function to play Minesweeper game
void playMinesweeper ()
{
    // Initially the game is not over
    bool gameOver = false;

    // Actual Board and My Board
    char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];

    int movesLeft = SIDE * SIDE - MINES, x, y;
    int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines.

    initialise (realBoard, myBoard);

    // Place the Mines randomly
    placeMines (mines, realBoard);

    /*
    If you want to cheat and know
    where mines are before playing the game
    then uncomment this part

    cheatMinesweeper(realBoard);
    */

    // You are in the game until you have not opened a mine
    // So keep playing

    int currentMoveIndex = 0;
    while (gameOver == false)
    {
        cout<<"Your current Game Board : \n";
        printBoard (myBoard);
        makeMove (&x, &y);

        // This is to guarantee that the first move is
        // always safe
        // If it is the first move of the game
        if (currentMoveIndex == 0)
        {
            // If the first move itself is a mine
            // then we remove the mine from that location
            if (isMine (x, y, realBoard) == true)
                replaceMine (x, y, realBoard);
        }

        currentMoveIndex ++;

        gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

        if ((gameOver == false) && (movesLeft == 0))
        {
            cout<<"\nYou won !\n";
            gameOver = true;
        }
    }
    return;
}

// A Function to choose the difficulty level
// of the game
void chooseDifficultyLevel ()
{
    /*
    --> BEGINNER = 9 * 9 Cells and 10 Mines
    --> INTERMEDIATE = 16 * 16 Cells and 40 Mines
    --> ADVANCED = 24 * 24 Cells and 99 Mines
    */

    int level;

    cout<<"\t\t**GAME WINDOW**"<<endl<<endl;
    cout<<"Enter the Difficulty Level\n";
    cout<<"Press 0 for BEGINNER (9 * 9 Cells and 10 Mines)\n";
    cout<<"Press 1 for INTERMEDIATE (16 * 16 Cells and 40 Mines)\n";
    cout<<"Press 2 for ADVANCED (24 * 24 Cells and 99 Mines)\n";

    cin>>level;

    if (level == BEGINNER)
    {
        SIDE = 9;
        MINES = 10;
    }

    if (level == INTERMEDIATE)
    {
        SIDE = 16;
        MINES = 40;
    }

    if (level == ADVANCED)
    {
        SIDE = 24;
        MINES = 99;
    }

    return;
}
void rulestoplay()
{
    cout<<"The goal of tic-tac-toe is to be the first player to get three "<<endl;
    cout<<"in a row on a 3-by-3 grid or four in a row in a 4-by-4 grid."<<endl;
    cout<<"In a 3-by-3 grid game, the player who is playing X always goes first."<<endl;
    cout<<"Players alternate placing Xs and Os on the board until either player has three in a row,"<<endl;
    cout<<"horizontally, vertically, or diagonally or until all "<<endl;
    cout<<"squares on the grid are filled. "<<endl;
    cout<<" If a player is able to draw three Xs or three Os in a row, then that player wins."<<endl;
    cout<<" When all 9 squares are full, the game is over."<<endl;
    cout<<"If no player has 3 marks in a row, the game ends in a tie."<<endl;
    cout<<"TIPS FOR BETTER GAMEPLAY"<<endl;
    cout<<"One of the game's best strategies involves creating a fork,"<<endl;
    cout<<"which is placing your mark in such a way that you have the opportunity to win two ways on your next turn."<<endl;
    cout<<"Your opponent can only block one, thereby, you can win after that."<<endl;
    cout<<"If you always pay attention and look ahead,"<<endl;
    cout<<" you'll never lose a game of Tic-Tac-Toe."<<endl;
    cout<<"You may not win, "<<endl;
    cout<<"but at least you'll tie."<<endl;

    cout<<"---------------MINESWEEPER RULES----------------"<<endl;
    cout<<"HOW TO PLAY MINESWEEPER?"<<endl;
    cout<<"Minesweeper is a game where mines are hidden in a grid of squares."<<endl;
    cout<<"Safe squares have numbers telling you how many mines touch the square."<<endl;
    cout<<"You can use the number clues to solve the game"<<endl;
    cout<<" by opening all of the safe squares."<<endl;
    cout<<"If you click on a mine you lose the game!"<<endl;
    cout<<"When you open a square that does not touch any mines, "<<endl;
    cout<<"it will be empty and the adjacent squares will automatically "<<endl;
    cout<<" open in all directions until reaching squares that contain numbers. "<<endl;
    cout<<"A common strategy for starting games is to randomly click until "<<endl;
    cout<<"you get a big opening with lots of numbers."<<endl;
    cout<<" Computer will ask for your input on what row and column you"<<endl;
    cout<<" want to explode."<<endl;
    cout<<" choose wisely as you might explode a mine."<<endl;
    cout<<"You will automatically see safe squares telling you how many mines are there near each square."<<endl;
    cout<<"Around each square there are 8 locations"<<endl;
    cout<<"therefore there could be 8 possible location for mines to be present."<<endl;
    cout<<"You need to avoid those mines and open all safe squares to win the game."<<endl;
    cout<<"THere are three difficulty levels and you can choose as per your skill."<<endl;
    cout<<"Start with easy if you are playing for the first time."<<endl;
}
int main()
{
    char s;
    while(1)
    {
            int mainchoice;
            cout<<"-------------------WELCOME TO GAME ZONE---------------------------"<<endl;
            cout<<"      ----------MENU----------" << endl;
            cout<<"\t 1. Play Tic Tac Toe" <<endl;

            cout<<"\t 2. Play Minesweeper" <<endl;

            cout<<"\t 3. How to Play" <<endl;
            cout<<"\t 4. To exit " <<endl;
            cout<<"      ------------------------" << endl;

            cout<< endl;
            cout<<"\t Select an option" << endl;
            
            cin>>mainchoice;
            switch(mainchoice)
            {
                case 1:
                {
                    int choice;
    
                    while(1){

                        cout<<"---------WELCOME TO TIC TAC TOE----------- !"<<endl;
                        cout<<"      ----------MENU----------" << endl;
                        cout<<"\t 1. 1 Player game" <<endl;
                        cout<<"\t 2. 2 Player game" <<endl;

                        cout<<"\t 3. To exit " <<endl;
                        cout<<"      ------------------------" << endl;
                        
                        cout<< endl;
                        cout<<"\t Select an option" << endl;
                        
                        cin>>choice;
                        switch(choice){
                        case 1:{

                            //if selected choice 1
                            //create new game object and call init to initialise that game
                            // and call oneplayergame() to start player vs cpu game
                            Game *game = new Game;
                            game->init();
                            game->onePlayerGame();
                            break;
                            }



                        case 2:{
                            Game *game = new Game;
                            game->init();
                            game->twoPlayerGame();
                            }


                            break;

                        case 3:


                            cout<<"-------------Thankyou For using the program!----------------"<<endl;
                            return 0;
                        default:
                            cout << "Invalid Option! TRY AGAIN";
                        }
                
                    }
                    break;
                }
                case 2:
                {
                                /* Choose a level between
                        --> BEGINNER = 9 * 9 Cells and 10 Mines
                        --> INTERMEDIATE = 16 * 16 Cells and 40 Mines
                        --> ADVANCED = 24 * 24 Cells and 99 Mines
                                */
                        title();
                        chooseDifficultyLevel ();
                        cout<<endl;
                        char c='n';
                        do
                        {
                            playMinesweeper ();
                            cout<<"Wanna Play again ? ({y or Y} for Yes and {n or N} for No) :";
                            cin>>c;
                            cout<<endl;
                        }
                        while(c=='y' || c=='Y');

                        break;
                }
                case 3:
                {
                    rulestoplay();
                    break;
                }
                case 4:
                {
                    cout<<"-------------Thankyou For using the program!----------------"<<endl;
                    return 0;
                }
                default:
                    cout<<"Invalid choice!!!"<<endl;
                    break;
                        }
            cout<<"SHOW THE MENU AGAIN? PRESS Y/N"<<endl;
            cin>>s;
            if(s=='N')
            {

                cout<<"-------------Thankyou For using the program!----------------"<<endl;
                return 0;
            }
    }
}