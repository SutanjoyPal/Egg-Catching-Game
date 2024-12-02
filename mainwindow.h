#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<bits/stdc++.h>
#include<QVector>
#include <QMainWindow>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Egg {
public:
    int x, y;  // Egg position
    QColor clr;
    Egg(int startX, int startY) : x(startX), y(startY) {}

    void fall(int speed) {
        y -= speed;  // Move the egg closer to the ground
    }
};

class Basket
{
public:
    int x;
    int y;
    Basket()
    {
        x=0;
        y=0;
    }
    Basket(int startX,int startY)
    {
        x=startX;
        y=startY;
    }
    void move(int delta_x)
    {
        x+=delta_x;
    }

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

void paintEvent(QPaintEvent *event) override;   // For rendering game objects
private slots:
    void gameLoop();

private:
    Ui::MainWindow *ui;
    void colorPoint(int x,int y,int r,int g, int b, int penwidth);
    void colorPoint2(int x,int y,int r,int g, int b, int penwidth);
    void delay(int ms);
    pair<int,int> markBox(int x,int y);
    void draw_dda_line(int x1,int y1,int x2,int y2,int r,int g,int b);
    void draw_bressenham_line(int x1,int y1,int x2,int y2,int r,int g,int b);
    pair<int,int> plotPixel(int x,int y);
    void draw_bressenham_ellipse(int x_center,int y_center,int a,int b);
    void draw_bressenham_ellipse2(int x_center, int y_center, int a, int b, int r, int g, int b_color);

    void updateGame();
    void clear_canvas();
    void draw_canvas();
    void draw_basket();
    void resetGame();
    QPoint clickedPoint;
    QTimer *timer;    // Timer for controlling the game loop
    QMap<QString,QColor> colorPalette;
    void initializeColorPalette();
    class myObj;
    class hen;
    int unitDistance = 3;
    int width;
    int height;
    int centerX;
    int centerY;
    int highscore;
    int sz=5;

    QPoint point_transform(QPoint pt);
    void colorPoint(QPoint curPt, QColor color);
    void draw_basket(int x_center, int y_center);
};
#endif // MAINWINDOW_H
