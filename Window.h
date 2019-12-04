#pragma once
#include<QtWidgets/QMainWindow>
#include<QtWidgets/QWidget>
#include<QPainter>
#include<QtWidgets/QPushButton>
#include<QObject>
#include<QEvent>
#include<QKeyEvent>
#include<QtWidgets/QPushButton>
#include<QMenuBar>
#include<QMessageBox>
#include"Maze.h"
#include<QtWidgets/QBoxLayout>
#include<QAction>
#include<QLabel>
#include<QInputDialog>
#define COORD(x,y) 10+x*10,30+y*10,10,10
class Window :public QMainWindow 
{
	Q_OBJECT
signals:
	void Win();
	void Successful();
public:
	Window();
	Window(QWidget *parent);
	void OpenRe();
protected:
	void paintEvent(QPaintEvent *event);
	void ReSize(int size);
	void getAnswer();
	void getMaze(QPainter&painter);
	virtual void keyPressEvent(QKeyEvent *ev);
private:
	void drawStone(QPainter &paint,int xl, int yl, int xr, int yr);
	void drawPeople(QPainter &paint, int xl, int yl, int xr, int yr);
	void drawStart(QPainter &paint, int xl, int yl, int xr, int yr);
	void drawEnd(QPainter &paint, int xl, int yl, int xr, int yr);
	void drawPath(QPainter &paint, int xl, int yl, int xr, int yr);
	Maze ma;
	QAction *Re;
	QAction *Answer;
};