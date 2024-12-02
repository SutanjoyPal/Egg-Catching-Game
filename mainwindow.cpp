#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QTimer>
#include <QMouseEvent>
#include <bits/stdc++.h>
#include <QElapsedTimer>
#include <QDebug>
#include <QMessageBox>
#include <random>
#include <fstream>


#define GridOffset 1
#define fps 20
// #define initial_eggs 4
#define Delay delay(1)
#define A 10
#define B 15
#define baseLine_y -240
#define basket_height 40
#define basket_width 100
#define min_X -500
#define max_X 500
#define start_Y 300
#define basket_offset 120

using namespace std;
int score=0;
int lives=5;
int prev_score=0;
int level=1;
int speed_parameter=10;
int egg_production_rate=25;

bool game_closed=false;

string filename = "C:/Users/Sutanjoy Pal/Downloads/Egg-catcher-game/Egg-catcher-game/highscore.txt";

Basket bs;
QVector<Egg> egg_array;
//int lanes[]={-270,-150,-60,60,150,270};
int lanes[] = {0,120,-120,240,-240,360,-360};
int getRandomNum(int x,int y){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(x, y);
    return distrib(gen);
}

void saveHighScore(const std::string& filename, int highScore) {
    std::ofstream outFile(filename, std::ios::out); // Open in write mode
    if (outFile) {
        outFile << highScore;
        std::cout << "High score saved successfully.\n";
    } else {
        std::cerr << "Error: Unable to open file for writing.\n";
    }
    outFile.close();
}

int readHighScore(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::in); // Open in read mode
    int highScore = 0;

    if (inFile) {
        inFile >> highScore;
        if (inFile.fail()) {
            std::cerr << "Error: File read error or invalid format. Setting high score to 0.\n";
            highScore = 0;
        }
    } else {
        std::cerr << "Error: Unable to open file for reading. Setting high score to 0.\n";
    }

    inFile.close();
    return highScore;
}

class MainWindow::myObj{
public:
    QPoint objCentre;
    QMap<QPair<int,int>,QColor> objDetails;
    MainWindow* mainWindow; // Add a reference to MainWindow


    myObj(QPoint objCentre,MainWindow* mainWindow){
        this->objCentre = objCentre;
        this->mainWindow = mainWindow;

    }

    myObj(){

    }

    void setDetails(int dx,int dy,QColor clr){
        objDetails[{dx,dy}] = clr;
    }
    void render(){
        for(auto it = objDetails.cbegin();it!=objDetails.cend();it++){
            mainWindow->colorPoint(QPoint(objCentre.x()+it.key().first,objCentre.y()+it.key().second),it.value());
        }
    }

    void reset(){
        for(auto it = objDetails.cbegin();it!=objDetails.cend();it++){
            objDetails[it.key()] = mainWindow->colorPalette["white"];
        }
        render();
    }


    void move(int x=1,int y=1){
        reset();
        objCentre = QPoint(objCentre.x()+x,objCentre.y()+y);
        render();
    }

    void reverse(){
        QMap<QPair<int,int>,QColor> tempDetails;
        for(auto it = objDetails.cbegin();it!=objDetails.cend();it++){
            tempDetails[{-(it.key().first),it.key().second}] = it.value();
        }
        reset();
        objDetails = tempDetails;
        render();
    }
};

class MainWindow::hen : public MainWindow::myObj{
public:
    hen(QPoint objCentre,MainWindow* mainWindow): myObj(objCentre,mainWindow){

    }

    void exsist(){
        reset();
        setDetails( -16 , -9 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -16 , -8 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -16 , -7 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -16 , -5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -15 , -14 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -15 , -13 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -15 , -12 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -15 , -11 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -15 , -10 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -15 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -15 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -15 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -15 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -15 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -15 , -4 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -14 , -15 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -14 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -14 , -3 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -13 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -13 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -13 , -2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -12 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -12 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -13 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -12 , -12 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -12 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -12 , -3 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -11 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -11 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -11 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -14 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -11 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -11 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -11 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -11 , -4 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -10 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -10 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -10 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -15 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -10 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -12 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -10 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -10 , -5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -10 , -4 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -9 , -21 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -9 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -9 , -19 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -9 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -13 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -9 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -9 , -5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -8 , -21 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -8 , -20 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -8 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -8 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -13 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -8 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -8 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -7 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -7 , -21 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -7 , -19 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -7 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -7 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -7 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -6 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -6 , -21 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -6 , -20 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -6 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -6 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -12 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -6 , -11 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -6 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -6 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -5 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -5 , -21 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -5 , -19 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -5 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -5 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -10 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -5 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -5 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -4 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -4 , -21 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -4 , -20 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -4 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -4 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -9 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -4 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -4 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -3 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -3 , -21 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -3 , -19 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -3 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -3 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -9 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -3 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -3 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -2 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -2 , -21 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -2 , -20 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -2 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -2 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -9 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -2 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -2 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -1 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -1 , -21 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -1 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -1 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -15 ,mainWindow->colorPalette[ "black" ]);
        setDetails( -1 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( -1 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -21 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -20 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -14 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -8 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -7 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 0 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 0 , -5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -22 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -21 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -19 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -13 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 1 , -4 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -3 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , -1 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , 0 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 1 , 1 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 2 , -21 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 2 , -20 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -19 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 2 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 2 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 2 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , -1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , 0 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , 1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 2 , 2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 3 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 3 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 3 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 3 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , -1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , 0 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , 1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , 2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 3 , 3 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 3 , 4 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 3 , 5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 4 , -20 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 4 , -19 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 4 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 4 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , -1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , 0 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , 1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , 2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , 3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 4 , 4 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 4 , 5 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 4 , 6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 5 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 5 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 5 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , -1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , 0 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , 1 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 5 , 2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 5 , 3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 5 , 4 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 5 , 5 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 5 , 6 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 5 , 7 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 6 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 6 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 6 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 6 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , -1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , 0 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 6 , 1 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 6 , 2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 6 , 3 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 6 , 4 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 6 , 5 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 6 , 6 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 6 , 7 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 6 , 8 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 7 , -20 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -19 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 7 , -18 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 7 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -3 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -2 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , -1 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 7 , 0 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 7 , 1 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 7 , 2 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 7 , 3 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 7 , 4 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 7 , 5 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 7 , 6 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 7 , 7 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 8 , -18 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 8 , -17 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 8 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -4 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 8 , -3 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 8 , -2 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 8 , -1 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 8 , 0 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 8 , 1 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 8 , 2 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 8 , 3 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 8 , 4 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 8 , 5 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 8 , 6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 9 , -17 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 9 , -16 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -15 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 9 , -14 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -7 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -6 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -5 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 9 , -4 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 9 , -3 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 9 , -2 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 9 , -1 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 9 , 0 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 9 , 1 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 9 , 2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 9 , 3 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 9 , 4 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 9 , 5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , -16 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , -15 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 10 , -14 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , -13 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 10 , -12 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 10 , -11 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 10 , -10 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 10 , -9 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 10 , -8 ,mainWindow->colorPalette[ "white" ]);
        setDetails( 10 , -7 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , -6 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , -5 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 10 , -4 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , -3 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , -2 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 10 , -1 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 10 , 0 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 10 , 1 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , 2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 10 , 3 ,mainWindow->colorPalette[ "red" ]);
        setDetails( 10 , 4 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -15 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -14 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -13 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -12 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -11 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -10 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -9 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -8 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -5 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -2 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , -1 ,mainWindow->colorPalette[ "yellow" ]);
        setDetails( 11 , 0 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 11 , 3 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 12 , -1 ,mainWindow->colorPalette[ "black" ]);
        setDetails( 12 , 0 ,mainWindow->colorPalette[ "white" ]);
        render();
    }
};

QPoint MainWindow:: point_transform(QPoint pt){
    float x_float = centerX + pt.x() * unitDistance + unitDistance / 2.0;
    float y_float = centerY - pt.y() * unitDistance - unitDistance / 2.0;
    int xn = static_cast<int>(x_float);
    int yn = static_cast<int>(y_float);
    return QPoint(xn,yn);
}

void MainWindow::colorPoint(QPoint curPt, QColor color) {
    int penwidth=unitDistance;
    QPixmap canvas=ui->Hens->pixmap();
    QPainter painter(&canvas);
    QPen pen=QPen(color,penwidth);
    painter.setPen(pen);
    QPoint pt = point_transform(curPt);
    painter.drawPoint(pt.x(), pt.y());
    ui->Hens->setPixmap(canvas);
    //qDebug()<<"Point Coloured: "<<curPt.x()<<"  "<<curPt.y();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->workArea->setMouseTracking(true);
    ui->Hens->setMouseTracking(true);

    this->installEventFilter(this);
    QPixmap canvas = ui->workArea->pixmap(Qt::ReturnByValue);
    if (canvas.isNull()) {
        canvas = QPixmap(ui->workArea->size());
        canvas.fill(Qt::white);
        ui->workArea->setPixmap(canvas);
    }
    QPixmap canvas2 = ui->Hens->pixmap(Qt::ReturnByValue);
    if (canvas2.isNull()) {
        canvas2 = QPixmap(ui->Hens->size());
        canvas2.fill(Qt::white);
        ui->Hens->setPixmap(canvas2);
    }
    highscore = readHighScore(filename);
    draw_canvas();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 5);
    initializeColorPalette();

    width = ui->Hens->width();
    height = ui->Hens->height();
    centerX = width / 2;
    centerY = height / 2;
    colorPoint2(width/2,height/2,135, 206, 235,width);
    hen h0(QPoint(0,0),this);
    h0.exsist();
    hen h(QPoint(40,0),this);
    h.exsist();
    hen h1(QPoint(-40,0),this);
    h1.exsist();
    hen h2(QPoint(-80,0),this);
    h2.exsist();
    hen h3(QPoint(80,0),this);
    h3.exsist();
    hen h4(QPoint(-120,0),this);
    h4.exsist();
    hen h5(QPoint(120,0),this);
    h5.exsist();
    ui->level->setText("    "+QString::number(level));

    // Generate random number in the range [min, max]
    int index= distrib(gen);
    egg_array.push_back(Egg(lanes[index],start_Y));
    int r = getRandomNum(1,3);
    if(r==1) egg_array.back().clr = colorPalette["gold"];
    else if(r==2) egg_array.back().clr = colorPalette["silver"];
    else  egg_array.back().clr = colorPalette["white"];

    bs=Basket(0,baseLine_y);
    ui->lives->setText("    "+QString::number(lives));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    timer->start(1000/fps);
}

void MainWindow::initializeColorPalette(){
    colorPalette["white"] = QColor(255, 255, 255);
    colorPalette["gold"] = QColor(255, 215, 0);
    colorPalette["silver"] = QColor(96, 96, 96);
    colorPalette["red"] = QColor(255, 0, 0);
    colorPalette["yellow"] = QColor(255, 255, 0);
    colorPalette["black"] = QColor(0, 0, 0);
}

void MainWindow::delay(int ms){
    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec();
}

void MainWindow::colorPoint(int x, int y, int r, int g, int b, int penwidth=1) {
    QPixmap canvas=ui->workArea->pixmap();
    QPainter painter(&canvas);
    QPen pen=QPen(QColor(r,g,b),penwidth);
    painter.setPen(pen);
    painter.drawPoint(x, y);
    ui->workArea->setPixmap(canvas);
}

void MainWindow::colorPoint2(int x, int y, int r, int g, int b, int penwidth=1) {
    QPixmap canvas2=ui->Hens->pixmap();
    QPainter painter(&canvas2);
    QPen pen=QPen(QColor(r,g,b),penwidth);
    painter.setPen(pen);
    painter.drawPoint(x, y);
    ui->Hens->setPixmap(canvas2);
}

pair<int,int> MainWindow::markBox(int x,int y)
{
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    int centerX=width/2;
    int centerY=height/2;
    clickedPoint.setX(x);
    clickedPoint.setY(y);
    int X=floor((x-centerX)*1.0/GridOffset);
    int Y=floor((centerY-y)*1.0/GridOffset);
    int calcX=X*GridOffset+centerX+GridOffset/2.0;
    int calcY=centerY-Y*GridOffset-GridOffset/2.0;
    return {calcX,calcY};
}

pair<int,int> MainWindow::plotPixel(int x,int y)
{
    int centerX=(ui->workArea->width())/2;
    int centerY=ui->workArea->height()/2;
    int newX=x*GridOffset+centerX;
    int newY=centerY-y*GridOffset;
    return markBox(newX,newY);
}

void MainWindow::resetGame() {
    lives = 5;
    score = 0;
    prev_score=0;
    level=1;
    speed_parameter=10;
    egg_production_rate=25;
    egg_array.clear();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 5);

    // Generate a new egg to start the game again
    int index = distrib(gen);
    egg_array.push_back(Egg(lanes[index], start_Y));
    int r = getRandomNum(1,3);
    if(r==1) egg_array.back().clr = colorPalette["gold"];
    else if(r==2) egg_array.back().clr = colorPalette["silver"];
    else  egg_array.back().clr = colorPalette["white"];
    bs = Basket(0, baseLine_y);

    ui->lives->setText("    "+QString::number(lives));
    ui->score->setText("    "+QString::number(score));
    ui->level->setText("    "+QString::number(level));

    // Restart the timer
    timer->start(1000 / fps);
}

void MainWindow::gameLoop() {
    // Update the game state and repaint the scene
    static int frame_count=1;
    clear_canvas();
    ui->score->setText("    "+QString::number(score));
    QVector<Egg>::Iterator iter=egg_array.begin();
    for(iter=egg_array.begin();iter!=egg_array.end();)
    {
        if(iter->x>bs.x-basket_width/2 && iter->x<bs.x+basket_width/2 && iter->y>bs.y-basket_height/2 && iter->y<bs.y+basket_height/2)
        {
            if(iter->clr == colorPalette["gold"]) score+=3;
            else if(iter->clr == colorPalette["silver"]) score+=2;
            else score++;

            if(score%2==0)
            {
                speed_parameter=min(speed_parameter+1,20);
                egg_production_rate=max(egg_production_rate-1,15);
            }
            iter=egg_array.erase(iter);
        }
        else if(iter->y<=baseLine_y)
        {
            iter=egg_array.erase(iter);
            lives--;
            ui->lives->setText("    "+QString::number(lives));
            if(lives<=0)
            {
                timer->stop();
                QMessageBox msgBox;
                msgBox.setText("Game Over");
                QString str1 = "Score: ";
                str1 += to_string(score);
                str1+= "\n";
                bool f=(score > highscore);
                str1+="HighScore: ";
                highscore = fmax(highscore,score);
                saveHighScore(filename,highscore);
                str1+=to_string(highscore);
                if(f){
                    str1+=("\nNew Highscore !😊😊");
                }
                msgBox.setInformativeText(str1);

                msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
                msgBox.setDefaultButton(QMessageBox::Retry);

                int ret = msgBox.exec();

                switch (ret) {
                case QMessageBox::Retry:
                    // Reset the game state
                    resetGame();
                    break;
                case QMessageBox::Close:
                    // Close the game
                    game_closed = true;
                    QApplication::quit();
                    break;
                default:
                    // Should never be reached
                    break;
                }
            }

        }
        else
        {
            iter->fall(speed_parameter);
            iter++;
        }
    }
    if(frame_count%egg_production_rate==0)        //egg generation
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 5);

        // Generate random number in the range [min, max]
        int index= distrib(gen);
        egg_array.push_back(Egg(lanes[index],start_Y));
        int r = getRandomNum(1,3);
        if(r==1) egg_array.back().clr = colorPalette["gold"];
        else if(r==2) egg_array.back().clr = colorPalette["silver"];
        else  egg_array.back().clr = colorPalette["white"];
    }
    if(score>=10 && prev_score<10)
    {
        level++;
        prev_score=10;
        ui->level->setText("    "+QString::number(level));
    }
    else if(score>=20 && prev_score<20 )
    {
        level++;
        prev_score=20;
        ui->level->setText("    "+QString::number(level));
    }
    else if(score>=50 && prev_score<50)
    {
        level++;
        prev_score=50;
        ui->level->setText("    "+QString::number(level));
    }


    frame_count++;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event); // Cast the event to QKeyEvent
        int key = keyEvent->key(); // Get the key code

        switch (key) {
        case Qt::Key_Left:
            if(bs.x-basket_offset>=-500)bs.x-=basket_offset;
            break;
        case Qt::Key_Right:
            if(bs.x+basket_offset<=500)bs.x+=basket_offset;
            break;
        default:
            break;
        }
        return true;  // Mark the event as handled, no further processing

    }
    return QMainWindow::eventFilter(watched, event);
}
void MainWindow::paintEvent(QPaintEvent *event) {

    for(int i=0;i<egg_array.size();i++)
    {
        draw_bressenham_ellipse2(egg_array[i].x,egg_array[i].y,A,B,egg_array[i].clr.red(), egg_array[i].clr.green(), egg_array[i].clr.blue());
    }
    draw_basket(bs.x,bs.y);
}


void MainWindow::draw_bressenham_line(int x1, int y1, int x2, int y2, int r, int g, int b) {
    QPolygon polygon;

    // Calculate the differences
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // Determine if we are stepping in the positive or negative direction
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    // Initial coordinates
    int x = x1;
    int y = y1;

    // Handle both slope cases |m| <= 1 and |m| > 1
    if (dx >= dy) {
        // Case 1: Slope is less than or equal to 1 (|m| <= 1)
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            pair<int,int> point_pair=plotPixel(x,y);
            polygon << QPoint(point_pair.first, point_pair.second); // Collect points into the polygon
            if (p >= 0) {
                y += sy;
                p -= 2 * dx;
            }
            p += 2 * dy;
            x += sx;
        }
    } else {
        // Case 2: Slope is greater than 1 (|m| > 1)
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            pair<int,int> point_pair=plotPixel(x,y);
            polygon << QPoint(point_pair.first, point_pair.second);
            if (p >= 0) {
                x += sx;
                p -= 2 * dy;
            }
            p += 2 * dx;
            y += sy;
        }
    }

    // Now draw all the points at once using QPainter
    QPixmap canvas = ui->workArea->pixmap();
    QPainter painter(&canvas);
    painter.setPen(QPen(QColor(r, g, b), 1)); // Set the color and pen width
    painter.drawPoints(polygon); // Draw the entire polygon (batch of points)
    ui->workArea->setPixmap(canvas); // Update the canvas
}


void MainWindow::draw_bressenham_ellipse(int x_center, int y_center, int a, int b) {
    QPolygon polygon;

    int x = 0, y = b;
    double d1 = b * b - a * a * b + (0.25 * a * a);

    // First part of the ellipse (where b^2 * x < a^2 * y)
    while (b * b * x < a * a * y) {
        if (y_center - y <= y_center) {  // Draw only the bottom half
            pair<int, int> point_pair = plotPixel(x_center + x, y_center - y);
            polygon << QPoint(point_pair.first, point_pair.second);
            point_pair = plotPixel(x_center - x, y_center - y);
            polygon << QPoint(point_pair.first, point_pair.second);
        }

        if (d1 < 0) {
            d1 += b * b * (2 * x + 3);
        } else {
            d1 += b * b * (2 * x + 3) + a * a * (2 - 2 * y);
            y--;
        }
        x++;
    }

    // Second part of the ellipse (where b^2 * x >= a^2 * y)
    double d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while (y >= 0) {
        if (y_center - y <= y_center) {  // Draw only the bottom half
            pair<int, int> point_pair = plotPixel(x_center + x, y_center - y);
            polygon << QPoint(point_pair.first, point_pair.second);
            point_pair = plotPixel(x_center - x, y_center - y);
            polygon << QPoint(point_pair.first, point_pair.second);
        }

        if (d2 < 0) {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
        } else {
            d2 += a * a * (-2 * y + 3);
        }
        y--;
    }

    // Draw all points in the bottom half of the ellipse at once using QPainter
    QPixmap canvas = ui->workArea->pixmap();
    QPainter painter(&canvas);
    painter.setPen(QPen(Qt::black, 1)); // Set the pen color to black or default
    painter.drawPoints(polygon); // Draw only the bottom half of the ellipse
    ui->workArea->setPixmap(canvas); // Update the canvas
}



void MainWindow::draw_bressenham_ellipse2(int x_center, int y_center, int a, int b, int r, int g, int b_color) {
    QPixmap canvas = ui->workArea->pixmap();
    QPainter painter(&canvas);

    // Set color for the ellipse boundary and fill
    QPen pen(QColor(r, g, b_color), 1);
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(r, g, b_color))); // Set brush color for filling

    // Draw and fill the ellipse at the specified center with radii a and b
    int centerX = ui->workArea->width() / 2 + x_center * GridOffset;
    int centerY = ui->workArea->height() / 2 - y_center * GridOffset;
    painter.drawEllipse(centerX - a * GridOffset, centerY - b * GridOffset, 2 * a * GridOffset, 2 * b * GridOffset);

    // Update the canvas
    ui->workArea->setPixmap(canvas);
}


void MainWindow::draw_canvas(){
    int width = ui->workArea->width();
    int height = ui->workArea->height();
    //int grass = 100;
    // for(auto i:lanes){
    //     draw_bressenham_ellipse2(i,300,A,B,255,255,255);
    // }

    colorPoint(width/2,height/2,135,206, 235,width);

}

void MainWindow::clear_canvas()
{
    QPixmap canvas = ui->workArea->pixmap(Qt::ReturnByValue);
    if (!canvas.isNull()) {
        canvas.fill(Qt::white);
        ui->workArea->setPixmap(canvas);
    }
    draw_canvas();
}

void MainWindow::draw_basket(int x_center, int y_center) {
    const int base_height = 10;    // Thickness of the basket's base

    // Calculate widget center
    int widget_width = ui->workArea->width();
    int widget_height = ui->workArea->height();

    int centerX = widget_width / 2 + x_center;
    int centerY = widget_height / 2 - y_center;

    // Define the four corners of the basket's rim
    QPoint topLeft(centerX - basket_width / 2 -sz, centerY - basket_height / 2);
    QPoint topRight(centerX + basket_width / 2 + sz, centerY - basket_height / 2);
    QPoint bottomRight(centerX + basket_width / 2 -sz, centerY + basket_height / 2 - base_height - 2);
    QPoint bottomLeft(centerX - basket_width / 2 + sz, centerY + basket_height / 2 - base_height - 2);

    // Define the base of the basket
    QPoint baseLeft(centerX - basket_width / 2 +sz, centerY + basket_height / 2);
    QPoint baseRight(centerX + basket_width / 2-sz, centerY + basket_height / 2);

    // Create a polygon representing the basket outline
    QPolygon basketPolygon;
    basketPolygon << topLeft
                  << topRight
                  << bottomRight
                  << baseRight
                  << baseLeft
                  << bottomLeft
                  << topLeft; // Close the polygon

    // Set pen and brush for the basket
    QColor customBrown(139, 69, 19);
    QPen pen(customBrown, 2); // Outline color and thickness
    QBrush brush(QColor(210, 105, 30));    // Fill color (optional)

    // Draw the basket
    QPixmap canvas = ui->workArea->pixmap(Qt::ReturnByValue);
    if (canvas.isNull()) {
        // Initialize the canvas if it's null
        canvas = QPixmap(ui->workArea->size());
        canvas.fill(Qt::white); // Background color
        ui->workArea->setPixmap(canvas);
    }

    QPainter painterCanvas(&canvas);
    painterCanvas.setRenderHint(QPainter::Antialiasing, true); // Smooth edges
    painterCanvas.setPen(pen);
    painterCanvas.setBrush(brush);
    painterCanvas.drawPolygon(basketPolygon);

    // Update the canvas
    ui->workArea->setPixmap(canvas);
}

