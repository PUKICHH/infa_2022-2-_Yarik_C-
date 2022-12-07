#include <iostream>
#include <string>

struct Point {
    unsigned long long x, y;

    Point(unsigned long long x, unsigned long long y) :
            x(x), y(y) {}


    Point minx(Point const &rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }

    Point miny(Point const &rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }

    Point maxx(Point const &rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }

    Point maxy(Point const &rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }

    void print() const {
        std::cout << '(' << x << ',' << y << ')';
    }
};

class Rectangle : public Point {
public:
    Rectangle() : Point(0, 0) {};

    Rectangle &operator=(const Rectangle &other) {};

    Rectangle(Point const &rha) : Point(rha.x, rha.y) {};

    Rectangle operator+(Rectangle const &rha) const {
        Point x = maxx(rha);
        Point y = maxy(rha);
        Point end = Point(x.x, y.y);
        return Rectangle(end);
    }

    Rectangle operator*(Rectangle const &rha) const {
        Point x = minx(rha);
        Point y = miny(rha);
        Point end = Point(x.x, y.y);
        return Rectangle(end);
    }

    void print_rectangle() const {
        print();
    }
};


Rectangle check_point(std::string str, size_t i) {
    std::string str_1 = "";
    std::string str_2 = "";
    while (str[i + 1] != ',') {
        str_1 = str_1 + str[i + 1];
        i++;
    }
    i++;
    while (str[i + 1] != ')') {
        str_2 = str_2 + str[i + 1];
        i++;
    }
    size_t x = std::stoi(str_1);
    size_t y = std::stoi(str_2);
    Rectangle rec_1 = Rectangle(Point(x, y));
    return rec_1;
}


int check_point_score(std::string str, size_t i) {
    int k = 0;
    k++;
    while (str[i + 1] != ',') {
        i++;
        k++;
    }
    i++;
    k++;
    while (str[i + 1] != ')') {
        i++;
        k++;
    }

    return k;
}

Rectangle sum1(Rectangle mas[], int k) {
    for (int i = 0; i <= k; i++) {
        Rectangle tmp = mas[0].operator+(mas[i]);
        mas[0].x = tmp.x;
        mas[0].y = tmp.y;
    }
    return mas[0];
}


Rectangle sum2(std::string str) {
    int score = 0;
    size_t l = str.size();
    Rectangle *mas = new Rectangle[l / 5];
    std::string str_1 = "";
    std::string str_2 = "";
    bool flag = true;
    for (size_t i = 0; i < l; i++) {
        if (str[i] == '*') {
            flag = true;
        } else {
            flag = false;
        }
        if (i != 0) {
            i++;
        }
        Rectangle rec_1 = check_point(str, i);
        if (flag) {
            Rectangle tmp = mas[score].operator*(rec_1);
            mas[score].x = tmp.x;
            mas[score].y = tmp.y;
        } else {
            if (i != 0) {
                score++;
            }
            mas[score].x = rec_1.x;
            mas[score].y = rec_1.y;
        }
        i = i + check_point_score(str, i);
    }
    Rectangle end_rec = sum1(mas, score);
    end_rec.print_rectangle();
    return end_rec;
}


int main() {

    std::string expression;
    std::getline(std::cin, expression);

    sum2(expression);
    return 0;
}
