#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Shape {
	public:
		void Draw(bool area, bool ***fb) {
			int i, j;
			for (i = 0; i < 50; i++) {
				for (j = 0; j < 100; j++) {
					if (area){
						if (areaEquation(i, j))
							(*fb)[i][j] = true;
					} else {
						if (drawEquation(i, j))
							(*fb)[i][j] = true;
					}
				}
			}
		}

		virtual void Scale(int factor) {
			cout << "Error in scale!";
		}
		virtual void Trans(int x, int y) {
			cout << "Error in trans!";
		}
	private:
		virtual bool drawEquation(int x, int y) = 0;
		virtual bool areaEquation(int x, int y) = 0;
};

class Rectangle : public Shape {
	public:
		Rectangle(int x, int y, int width, int height) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;

			this->x2 = this->x + this->width;
			this->y2 = this->y;
			this->x4 = this->x;
			this->y4 = this->y + this->height;
		}

		void Scale(int factor) {
			this->width *= factor;
			this->height *= factor;
		}

		void Trans(int x, int y) {
			this->x = x;
			this->y = y;
		}

	private:
		int x, y, width, height, x2, y2, x4, y4;

		bool drawEquation(int x, int y) {
			int xtmp, ytmp, xn, yn;

			xn = x - this->x;
			yn = y - this->y;
			xtmp = xn * ((this->x2 - this->x) / this->width) + yn * ((this->y2 - this->y) / this->height);
			ytmp = xn * ((this->x4 - this->x) / this->width) + yn * ((this->y4 - this->y) / this->height);

			return ((xtmp >= 0 && xtmp <= this->width) && (ytmp >= 0 && ytmp <= this->height));
		}

		bool areaEquation(int x, int y) {
			int xtmp, ytmp, xn, yn;

			xn = x - this->x;
			yn = y - this->y;
			xtmp = xn * ((this->x2 - this->x) / this->width) + yn * ((this->y2 - this->y) / this->height);
			ytmp = xn * ((this->x4 - this->x) / this->width) + yn * ((this->y4 - this->y) / this->height);

			return ((xtmp == 0 || xtmp == this->width || ytmp == 0 || ytmp == this->height) &&
					x <= this->x2 && y <= this->y4 && x >= this->x && y >= this->y);
		}
};

class Rhombus : public Shape {
	public:
		Rhombus(int x, int y, int s) {
			this->x = x;
			this->y = y;
			this->s = s;
		}

		void Scale(int factor) {
			this->s *= factor;
		}

		void Trans(int x, int y) {
			this->x = x;
			this->y = y;
		}

	private:
		int x, y, s;

		bool drawEquation(int x, int y) {
			return false;
		}

		bool areaEquation(int x, int y) {
			return false;
		}
};

class Circle : public Shape {
	public:
		Circle(int x, int y, int s) {
			this->x = x;
			this->y = y;
			this->s = s;
		}

		void Scale(int factor) {
			this->s *= factor;
		}

		void Trans(int x, int y) {
			this->x = x;
			this->y = y;
		}

	private:
		int x, y, s;

		bool drawEquation(int x, int y) {
			return (pow(x - this->x, 2) + pow(y - this->y, 2) <= pow(this->s, 2));
		}

		bool areaEquation(int x, int y) {
			return (pow(x - this->x, 2) + pow(y - this->y, 2) == pow(this->s, 2));
		}
};

int main() {
	bool **framebuffer;
	map<string, Shape*> drawList;
	map<string, Shape*>::iterator it;
	string buff, name;
	unsigned int i, j, tmp;
	vector<int> arguments;

	framebuffer = new bool*[100];
	for (i = 0; i < 50; i++) {
		framebuffer[i] = new bool[100];

		for (j = 0; j < 100; j++)
			framebuffer[i][j] = false;
	}


	while (1) {
		arguments.clear();
		buff.clear();
		name.clear();

		cout << "$> ";
		cin >> buff;

		if (buff.compare("newrect") == 0) {
			cin >> name;
			for (i = 0; i < 4; i++) {
				buff.clear();
				cin >> buff;
				arguments.push_back(stoi(buff));
			}
			drawList[name] = new Rectangle(arguments[0], arguments[1], arguments[2], arguments[3]);
		} else if (buff.compare("newrhomb") == 0) {
			cin >> name;
			for (i = 0; i < 3; i++) {
				buff.clear();
				cin >> buff;
				arguments.push_back(stoi(buff));
			}
			drawList[name] = new Rhombus(arguments[0], arguments[1], arguments[2]);
		} else if (buff.compare("newcircle") == 0) {
			cin >> name;
			for (i = 0; i < 3; i++) {
				buff.clear();
				cin >> buff;
				arguments.push_back(stoi(buff));
			}
			drawList[name] = new Circle(arguments[0], arguments[1], arguments[2]);
		} else if (buff.compare("delete") == 0) {
			cin >> name;

			drawList.erase(drawList.find(name));
		} else if (buff.compare("translate") == 0) {
			cin >> name;
			for (i = 0; i < 2; i++) {
				buff.clear();
				cin >> buff;
				arguments.push_back(stoi(buff));
			}

			drawList[name]->Trans(arguments[0], arguments[1]);
		} else if (buff.compare("scaleup") == 0) {
			cin >> name;
			for (i = 0; i < 1; i++) {
				buff.clear();
				cin >> buff;
				arguments.push_back(stoi(buff));
			}

			drawList[name]->Scale(arguments[0]);
		} else if (buff.compare("draw") == 0 || buff.compare("area") == 0) {
			for (it = drawList.begin(); it != drawList.end(); it++) {
				if (buff.compare("area") == 0)
					it->second->Draw(true, &framebuffer);
				else
					it->second->Draw(false, &framebuffer);
			}

			tmp = 0;
			for (i = 50; i > 0; i--) {
				for (j = 0; j < 100; j++) {
					if (framebuffer[i -1][j]) {
						tmp = i;
						break;
					}
				}

				if (tmp)
					break;
			}

			for (i = 0; i < tmp; i++) {
				for (j = 0; j < 100; j++) {
					if (framebuffer[i][j] == true)
						cout << ".";
					else
						cout << " ";
				}

				cout << endl;
			}

			for (i = 0; i < 50; i++) {
				for (j = 0; j < 100; j++)
					framebuffer[i][j] = false;
			}
		} else if (buff.compare("quit") == 0) {
			break;
		} else {
		}
	}

	return 0;
}
