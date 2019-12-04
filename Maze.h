#pragma
#include<iostream>
#include<string>
#include<stdlib.h>
#include<map>
#include<vector>
#include<time.h>
#include"MyQueue.h"
#include"MyStack.h"
class Maze
{
private:
	char *base;
	int size;
	int pos;
	int start;
	int end;
	void setPoint(int row, int col, char data) {
		if (row < 0 || col < 0 || col >= size || row >= size)
			throw "Parameter out of range!";
		else
		{
			base[(row + 1)*(size + 2) + col + 1] = data;
		}
	}
	char getPoint(int row, int col) {
		if (row < 0 || col < 0 || col >= size || row >= size)
			throw "Parameter out of range!";
		else
			return base[(row + 1)*(size + 2) + col + 1];
	}
	void CreateMaze() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				try {
					setPoint(i, j, '#');
				}
				catch (const char *msg)
				{
					std::cerr << msg << std::endl;
				}
			}
		}
		int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
		srand((unsigned)time(nullptr));
		start = rand() % (size*size);
		try
		{
			setPoint(start / size, start%size, ' ');
			//setPoint(size - 1, size - 1, ' ');
		}
		catch (const char* msg)
		{
			std::cerr << msg << std::endl;
		}
		//MyQueue<int> que;
		std::vector<int>que;
		int nei;
		for (int i = 0; i < 4; i++)
		{
			int nr = start / size + dir[i][0], nc = start % size + dir[i][1];
			if (nr >= 0 && nc >= 0 && nr < size&&nc < size)
			{
				nei = nr * size + nc;
				que.push_back(nei);
			}
		}
		int e;
		while (que.size()) {
			e = 8;
			srand((unsigned)time(NULL)*nei*e + nei);
			int r = rand() % que.size();
			e = que[r];
			que.erase(que.begin() + r);
			int count = 0;
			for (int i = 0; i < 4; i++) {
				int nr = e / size + dir[i][0];
				int nc = e % size + dir[i][1];
				if (nr >= 0 && nr < size&&nc >= 0 && nc < size) {
					char ch = getPoint(nr, nc);
					if (ch == ' ')
						count++;
				}
			}
			if (count <= 1) {
				setPoint(e / size, e%size, ' ');
				end = e;
				for (int i = 0; i < 4; i++) {
					int nr = e / size + dir[i][0];
					int nc = e % size + dir[i][1];
					if (nr >= 0 && nr < size&&nc >= 0 && nc < size) {
						char ch = getPoint(nr, nc);
						if (ch == '#') {
							que.push_back(nr*size + nc);
						}
					}
				}
			}
		}
		try
		{
			setPoint(start / size, start%size, 'p');
			setPoint(end / size, end%size, 'E');
		}
		catch (const char* msg)
		{
			std::cerr << msg << std::endl;
		}
		pos = start;
	}
	void solve() {
		int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
		int *vis = new int[size*size];
		for (int i = 0; i < size*size; i++)
			vis[i] = 0;
		vis[0] = 1;
		MyStack<int> S1;
		MyStack<int> S2;
		MyStack<int> Path;
		S1.push(pos);
		S2.push(0);
		while (S1.empty() == S1.FALSE) {
			int e, d;
			S1.top(e), S2.top(d);
			if (e == end)
				break;
			int nr = e / size + dir[d][0], nc = e % size + dir[d][1];
			if (d<=3&&nr >= 0 && nr < size&&nc >= 0 && nc < size&&getPoint(nr, nc) != '#' && !vis[nr*size + nc]) {
				vis[nr*size + nc] = vis[e] + 1;
				S1.push(nr*size + nc);
				S2.push(0);
				Path.push(nr*size + nc);
			}
			else if (d <= 3) {
				S2.pop();
				d++;
				S2.push(d);
			}
			else
			{
				//vis[e] = 0;
				S2.pop();
				S1.pop();
				Path.pop();
			}
		}
		//exit(0);
		while (Path.empty() == Path.FALSE) {
			int e;
			Path.top(e);
			setPoint(e / size, e%size, '*');
			Path.pop();
		}
	}
public:
	enum Status
	{
		Win,
		Successful,
		Stone
	};
	enum Direction
	{
		Up, Down, Left, Right
	};
	Maze() :base(nullptr), size(0), pos(0) {}
	Maze(const int& size) :base(new char[(size + 2)*(size + 2)]), size(size), pos(0) {
		for (int i = 0; i < size + 2; i++) {
			base[i] = '#';
			base[i*(size + 2)] = '#';
			base[(size + 1)*(size + 2) + i] = '#';
			base[size+1+i*(size+2)] = '#';
		}
		base[0] = base[(size + 2)*(size + 2) - 1] = ' ';
		CreateMaze();
	}
	~Maze()
	{
		delete[]base;
	}
	void NewMaze(const int&sz) {
		size = sz;
		delete[]base;
		base = new char[(size + 2)*(size + 2)];
		for (int i = 0; i < size + 2; i++) {
			base[i] = '#';
			base[i*(size + 2)] = '#';
			base[(size + 1)*(size + 2) + i] = '#';
			base[(i + 1)*(size + 2) - 1] = '#';
		}
		base[0] = base[(size + 2)*(size + 2) - 1] = ' ';
		CreateMaze();
	}
	Status Judge(Direction oper) {
		switch (oper)
		{
		case Maze::Up:
		{
			int nr = pos / size - 1;
			int nc = pos % size;
			if (nr < 0)
				return Status::Stone;
			char ch = getPoint(nr, nc);
			if (ch == '#')
				return Status::Stone;
			setPoint(nr, nc, 'p');
			setPoint(pos / size, pos%size, ' ');
			if (pos == start)
				setPoint(start / size, start%size, 'S');
			pos = nr * size + nc;
		}
		break;
		case Maze::Down:
		{
			int nr = pos / size + 1;
			int nc = pos % size;
			if (nr >= size)
				return Status::Stone;
			char ch = getPoint(nr, nc);
			if (ch == '#')
				return Status::Stone;
			setPoint(nr, nc, 'p');
			setPoint(pos / size, pos%size, ' ');
			if (pos == start)
				setPoint(start / size, start%size, 'S');
			pos = nr * size + nc;
		}
		break;
		case Maze::Left:
		{
			int nr = pos / size;
			int nc = pos % size - 1;
			if (nc < 0)
				return Status::Stone;
			char ch = getPoint(nr, nc);
			if (ch == '#')
				return Status::Stone;
			setPoint(nr, nc, 'p');
			setPoint(pos / size, pos%size, ' ');
			if (pos == start)
				setPoint(start / size, start%size, 'S');
			pos = nr * size + nc;
		}
		break;
		case Maze::Right:
		{
			int nr = pos / size;
			int nc = pos % size + 1;
			if (nc >= size)
				return Status::Stone;
			char ch = getPoint(nr, nc);
			if (ch == '#')
				return Status::Stone;
			setPoint(nr, nc, 'p');
			setPoint(pos / size, pos%size, ' ');
			if (pos == start)
				setPoint(start / size, start%size, 'S');
			pos = nr * size + nc;
		}
		break;
		default:
			break;
		}
		if (pos == end)
			return Status::Win;
		else
			return Status::Successful;
	}
	int getSize() {
		return size + 2;
	}
	char *getMaze() {
		char *maze = new char[(size + 2)*(size + 2)];
		for (int i = 0; i < size + 2; i++) {
			for (int j = 0; j < size + 2; j++) {
				maze[i*(size + 2) + j] = base[i*(size + 2) + j];
			}
		}
		return maze;
	}
	char *getAnswer()
	{
		solve();
		char *maze = new char[(size + 2)*(size + 2)];
		for (int i = 0; i < size + 2; i++) {
			for (int j = 0; j < size + 2; j++) {
				maze[i*(size + 2) + j] = base[(size + 2)*i + j];
			}
		}
		return maze;
	}
};
