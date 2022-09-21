#include <iostream>
#include <cmath>

struct Point {
    unsigned long long x, y;

    Point(unsigned long long x, unsigned long long y) : x(x), y(y) {}

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
        std::cout << "(" << x << "," << y << ")";
    }

};

class Rectangle {
public:
    Point rha;

    Rectangle() : rha(0, 0) {};

    Rectangle(Point const &rha_m) : rha(rha_m.x, rha_m.y) {};

    Rectangle operator+(Rectangle const &rng) const {
        Rectangle c(Point(rha.maxx(rng.rha).x, rha.maxy(rng.rha).y));
        return c;
    };

    Rectangle operator*(Rectangle const &rng) const {
        Rectangle c(Point(rha.minx(rng.rha).x, rha.miny(rng.rha).y));
        return c;
    };

    void print() const {
        std::cout << "(" << rha.x << "," << rha.y << ")";
    }
};

bool have(std::string expression, char symbol) {
    bool ans = false;
    for (int i = 0; i < expression.length(); i++)
        if (expression[i] == symbol) ans = true;
    return ans;
}

long long getNumber(std::string str) {
    long long num = 0;
    for (int i = 0; i < str.length(); i++) {
        num += (str[i] - '0') * pow(10, str.length() - i - 1);
    }
    return num;
}

std::string remo(char operation, std::string expression) {
    while (have(expression, operation)) {

        for (int i = 0; i < expression.length(); i++) {
            if (expression[i] == operation) {
                int m, n = 0;
                for (int s = i; expression[s] != '('; s--)
                    m = s;
                for (int s = i; expression[s] != ')'; s++)
                    n = s;
                long long a1, a2, b1, b2 = 0;
                std::string multstr = expression.substr(m, n - m + 1);
                int count_of_commas = 0;
                int pivot = 0;
                for (int k = 0; k < multstr.length(); k++) {
                    if ((count_of_commas == 0) && (multstr[k] == ',')) {
                        a1 = getNumber(multstr.substr(0, k));
                        count_of_commas = 1;
                        pivot = k + 1;
                    }
                    if (multstr[k] == ')') {
                        a2 = getNumber(multstr.substr(pivot, k - pivot));
                        pivot = k + 5;
                    }
                    if ((count_of_commas == 1) && (multstr[k] == ',')) {
                        b1 = getNumber(multstr.substr(pivot, k - pivot));
                        b2 = getNumber(multstr.substr(k + 1, multstr.length() - k));
                    }
                }
                Rectangle A(Point(a1, a2));
                Rectangle B(Point(b1, b2));
                Rectangle C;
                if (operation == '*')
                    C = A * B;
                if (operation == '+')
                    C = A + B;
                multstr = std::to_string(C.rha.x) + "," + std::to_string(C.rha.y);
                std::string modified_expression =
                        expression.substr(0, m) + multstr + expression.substr(n + 1, expression.length() - n - 1);
                expression = modified_expression;
            }
        };
    };
    return expression;
}

int main() {
    std::string expression;
    std::getline(std::cin, expression);

    expression = remo('*', expression);
    expression = remo('+', expression);
    return 0;
}
