#include"Window.h"
void Window::paintEvent(QPaintEvent*event)
{
	QPainter painter(this);
	getMaze(painter);
}
void Window::keyPressEvent(QKeyEvent *e)
{
	Maze::Status status;
	switch (e->key())
	{
	case Qt::Key_Left:
		status=ma.Judge(Maze::Up);
		break;
	case Qt::Key_Right:
		status=ma.Judge(Maze::Down);
		break;
	case Qt::Key_Up:
		status=ma.Judge(Maze::Left);
		break;
	case Qt::Key_Down:
		status=ma.Judge(Maze::Right);
		break;
	default:
		QMainWindow::keyPressEvent(e);
		return;
	}
	switch (status)
	{
	case Maze::Win:
		QMessageBox::information(this,tr("Wonderful"), tr("You Win!"));
		emit Win();
		break;
	case Maze::Successful:
		emit Successful();
		break;
	case Maze::Stone:
		break;
	default:
        break;
	}
	repaint();
}
void Window::drawStone(QPainter &painter,int xl, int yl, int xr, int yr)
{
	painter.setPen(Qt::black);
	QBrush brush(QColor(128, 64, 0));
	painter.setBrush(brush);
	painter.drawRect(xl, yl, xr, yr);
	brush.setStyle(Qt::VerPattern);
	brush.setColor(Qt::black);
	painter.setBrush(brush);
	painter.drawRect(xl, yl, xr, yr);
}
void Window::drawPeople(QPainter &painter, int xl, int yl, int xr, int yr)
{
	painter.setPen(Qt::black);
	painter.drawLine(xl, yl + 1, xl + 1, yl + 1);
	painter.drawLine(xl + 1, yl, xl + 6, yl);
	painter.drawLine(xl + 5, yl + 1, xl + 6, yl + 1);
	painter.drawLine(xl + 5, yl + 2, xl + 6, yl + 2);
	painter.drawLine(xl + 1, yl + 9, xl + 2, yl + 9);
	painter.drawLine(xl + 2, yl + 7, xl + 2, yl + 9);
	painter.drawLine(xl + 6, yl + 7, xl + 6, yl + 9);
	painter.drawLine(xl + 4, yl + 9, xl + 5, yl + 9);
	painter.setPen(QColor(128, 64, 0));
	painter.drawLine(xl, yl + 4, xl + 1, yl + 4);
	painter.drawLine(xl, yl + 5, xl + 1, yl + 4);
	painter.drawLine(xl+3, yl + 4, xl + 4, yl + 4);
	painter.drawLine(xl+2, yl + 3, xl + 5, yl + 3);
	painter.drawLine(xl+2, yl + 2, xl + 4, yl + 2);
	painter.drawLine(xl+2, yl + 1, xl + 4, yl + 1);
	painter.setPen(Qt::black);
	painter.drawLine(xl + 3, yl + 2, xl + 3, yl + 2);
	painter.setPen(Qt::blue);
	painter.drawLine(xl + 5, yl + 4, xl + 5, yl + 6);
	painter.drawLine(xl + 4, yl + 5, xl + 4, yl + 7);
	painter.drawLine(xl + 3, yl + 5, xl + 3, yl + 7);
	painter.drawLine(xl + 2, yl + 4, xl + 2, yl + 6);
	painter.setPen(Qt::red);
	painter.drawLine(xl + 8, yl + 5, xl + 8, yl + 6);
	painter.drawLine(xl + 7, yl + 4, xl + 7, yl + 6);
	painter.drawLine(xl + 6, yl + 3, xl + 6, yl + 6);
}
void Window::drawStart(QPainter &painter, int xl, int yl, int xr, int yr)
{
	painter.setPen(Qt::black);
	QBrush brush(Qt::yellow);
	painter.setBrush(brush);
	painter.drawRect(xl, yl, xr, yr);
}
void Window::drawEnd(QPainter &painter, int xl, int yl, int xr, int yr) 
{
	painter.setPen(Qt::black);
	QBrush brush(Qt::green);
	painter.setBrush(brush);
	painter.drawRect(xl, yl, xr, yr);
}
void Window::drawPath(QPainter &painter, int xl, int yl, int xr, int yr)
{
	painter.setPen(Qt::black);
	QBrush brush(Qt::red);
	painter.setBrush(brush);
	painter.drawRect(xl, yl, xr, yr);
}
void Window::ReSize(int size = 10)
{
	setFixedSize(size * 15, size * 15);
	ma.NewMaze(size);
	repaint();
}
void Window::getAnswer() {
	char *maze = ma.getAnswer();
	delete[]maze;
	repaint();
}
void Window::getMaze(QPainter&painter)
{
	char *maze = ma.getMaze();
	int size = ma.getSize();
	for (int i = 0; i < size ; i++) {
		for (int j = 0; j < size; j++) {
			switch (maze[i*(size) + j])
			{
			case '*':
				drawPath(painter, COORD(i, j));
			case 'p':
				drawPeople(painter, COORD(i, j));
				break;
			case '#':
				drawStone(painter, COORD(i, j));
				break;
			case'S':
				drawStart(painter, COORD(i, j));
				break;
			case 'E':
				drawEnd(painter, COORD(i, j));
				break;
			case ' ':
				break;
			default:
				break;
			}
		}
	}
	delete []maze;
}
Window::Window():QMainWindow(),ma(12)
{
	setFixedSize(200, 200);
    Re = new QAction(tr("Reset Maze"), this);
    Answer = new QAction(tr("Get Answer"), this);
    Re->setStatusTip(tr("Reset Maze"));
    Answer->setStatusTip(tr("Get Answer"));
    QMenu *rem = menuBar()->addMenu(tr("Operation"));
	rem->addAction(Re);
	rem->addAction(Answer);
	connect(Answer, &QAction::triggered, this, &Window::getAnswer);
	connect(Re, &QAction::triggered, this, &Window::OpenRe);
	connect(this, &Window::Win, this, &Window::OpenRe);
	statusBar();
}
Window::Window(QWidget*parent) : QMainWindow(parent),ma(12)
{
	setFixedSize(200, 200);
    Re = new QAction(tr("Reset Maze"), this);
    Answer = new QAction(tr("Get Answer"), this);
    Re->setStatusTip(tr("Reset Maze"));
    Answer->setStatusTip(tr("Get Answer"));
    QMenu *rem = menuBar()->addMenu(tr("Operation"));
	rem->addAction(Re);
	rem->addAction(Answer);
	connect(Answer, &QAction::triggered, this, &Window::getAnswer);
	connect(Re, &QAction::triggered, this, &Window::OpenRe);
	connect(this, &Window::Win, this, &Window::OpenRe);
	statusBar();
}
void Window::OpenRe()
{
	QInputDialog input(this);
	input.setInputMode(QInputDialog::IntInput);
    input.setOkButtonText(tr("Fix"));
    input.setCancelButtonText(tr("Cancel"));
    input.setWindowTitle(tr("Please input the map size"));
    input.setLabelText(tr("Please input the map size"));
	if (input.exec() == QInputDialog::Accepted)
	{
		int res = input.intValue();
		if (res <= 6)
            QMessageBox::information(this, tr("Error"), tr("The size of map should greater than 6"));
		else
			ReSize(res);
	}
}
