#include <iostream>

using namespace std;

class Shapes {
	public:
		void Draw(bool area) {
			int i, j;
			for (i = 0; i < 50; i++) {
				cout << i << ": ";
				for (j = 0; j < 50; j++) {
					if (area){
						if (areaEquation(j, i))
							cout << ".";
					} else {
						if (drawEquation(j, i))
							cout << ".";
					}
				}
				cout << endl;
			}
		}

		virtual void Scale() {
			cout << "Error in scale!";
		}
		virtual void Trans() {
			cout << "Error in trans!";
		}
	private:
		virtual bool drawEquation(int x, int y) = 0;
		virtual bool areaEquation(int x, int y) = 0;
};

class Rectangle : public Shapes {
	public:
		Rectangle(int x, int y, int width, int height) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
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
		int x, y, width, height;

		bool drawEquation(int x, int y) {
			if ((x >= this->x && x < this->x + this->width) &&
					(y >= this->y && y < this->y + this->height))
				return true;

			return false;
		}

		bool areaEquation(int x, int y) {
			if ((x == this->x || x == this->x + this->width) &&
					(y == this->y || y == this->y + this->height))
				return true;

			return false;
		}
};

constexpr unsigned long int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

int main() {
	string buff;

	while (1) {
		cout << "$> ";
		cin >> buff;

		switch (str2int(buff)) {
			case str2int("newrect"):
				break;
			case str2int("newrhomb"):
				break;
			case str2int("newcircle"):
				break;
			case str2int("delete"):
				break;
			case str2int("translate"):
				break;
			case str2int("scaleup"):
				break;
			case str2int("draw"):
				break;
			case str2int("area"):
				break;
			default:
				break;
		}
	}

	return 0;
}
