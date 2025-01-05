#include<iostream>
#include <unistd.h>
#include<cstdlib>
using namespace std;

enum Direction{STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir;
bool GAMEOVER;
const int height = 20;
const int width = 20;
int headX, headY, fruitX, fruitY, score;
int tailx[100], taily[100];
int tail_len = 0;

void setup();
void draw();
void input();
void logic();

int main() {
    char start;
    cout << "\t------------------------------" << endl;
    cout << "\t\t :Snake King:" << endl;
    cout << "\t------------------------------" << endl;
    cout << "\tPress 's' to start: ";
    cin >> start;
    if(start == 's') {
        setup();
        while( !GAMEOVER) {
            draw();
            input();
            logic();
            usleep(30000);

        }
        cout << "\nGame Over!" << endl;
        cout << "Final Score: " << score << endl;
    }
    return 0;
}

void setup(){
    GAMEOVER = false;
    dir = STOP;
    headX = width/2;
    headY = height/2;
    fruitX = rand()%width;
    fruitY = rand()%height;
    score = 0;
    tail_len=0;
}

void draw(){
    system("clear");
    cout << "\t\t";
    for(int i = 0; i < width; i++){
        cout << "||";
    }
    cout << endl;
    for(int i=0; i<height; i++) {
        for(int j=0; j<width;j++){
            if(j==0){
                cout<< "||";
            }
            if(i == headY && j == headX){
                cout << "O";
            }
            else if(i==fruitY && j==fruitX){
                cout << "*";
            }
            else{
                bool print =false;
                for(int k=0;k<tail_len;k++){
                    if(tailx[k]==j && taily[k]==i){
                        cout<<"o";
                        print=true;
                    }

                }
                if(!print){
                    cout<<" ";
                }
            }
            if(j== width-1){
                cout<< "||";
            }

        }
        cout<<endl;

    }
    for(int i = 0; i < width-8; i++){
        cout << "||";
    }
    cout << endl;
    cout << "Score:" << score <<endl;
    if (GAMEOVER) {
        cout << "\nGame Over!" << endl;
        cout << "Final Score: " << score << endl;
    }

}

void input(){
    char ch;
    cin>>ch;
    switch (ch)
    {
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;    
    default:
        break;
    }

}

void logic(){
    int prevx=tailx[0];
    int prevy=taily[0];
    int prev2x, prev2y;
    tailx[0]=headX;
    taily[0]=headY;
    for(int i =1; i<tail_len; i++){
        prev2x= tailx[i];
        prev2y= taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    
    }
    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }
    if(headX>=width){
        headX=0;
    }
    else if(headX < 0){
        headX=width - 1;
    }
    if(headY >= height){
        headY= 0;
    }
    else if(headY < 0){
        headY=height - 1;
    }
    for(int i = 0; i < tail_len; i++){
        if(tailx[i] ==headX && taily[i] ==headY){
            GAMEOVER = true;
        }
    }
    if(headX == fruitX && headY == fruitY){
        score += 10;
        fruitX = rand()%width;
        fruitY = rand()%height;
        tail_len++;
    }
 
}