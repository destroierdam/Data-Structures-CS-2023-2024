#include <iostream>
#include <cassert>
#include <string>
#include <stack>
#include <cstddef>

bool isOperator(const char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '/':
    case '*':
        return true;    
    default:
        return false;
    }
}

std::string polishNotationConvert(const std::string& rpn)
{
    std::stack<std::string> s;
    for (std::size_t i = 0; i < rpn.size(); i++)
    {
        if (!isOperator(rpn[i]))//bigbrain.begin();
        {
            s.push(std::string(1, rpn[i]));
        } else
        {
            std::string result;
            result+=rpn[i];
            std::string op2 = s.top(); s.pop();
            result+=s.top(); s.pop();
            result+= op2;
            s.push(result);
        } //bigbrain.end();
    }
    std::string result;
    while (!s.empty())
    {
        result+=s.top(); s.pop();
    }
    
    return result;
}

const unsigned int labSize = 5;

struct Point {
    std::size_t row, col;
    Point(std::size_t row, std::size_t col) : row(row), col(col) {}
    
    Point operator+ (const Point &other) const {
        return Point(row + other.row, col + other.col);
    }

    bool operator==(const Point &other) const {
        return row == other.row && col == other.col;
    } 

    bool checkBounds(std::size_t labSize = ::labSize) const {
        return row < labSize && col < labSize;
    }

    friend std::ostream &operator<< (std::ostream &out, const Point &p) {
        return out << "(" << p.row << ", " <<  p.col << ")";
    }
};


int lab[labSize][labSize] = {0, 1, 0, 0, 0,
                             0, 1, 0, 0, 0,
                             0, 0, 0, 1, 0,
                             0, 1, 1, 1, 1,
                             0, 0, 0, 0, 0};
const int LAB_EMPTY = 0;
const int LAB_WALL = 1;
const int LAB_TEMP_WALL = 2;

bool hasRoute(const Point &start, const Point& end, int lab[][labSize]) {
    std::stack<Point> route;
    route.push(start);
    lab[start.row][start.col] = LAB_TEMP_WALL;

    const Point directions[] = {
        Point(0, 1),            // down
        Point(1, 0),            // right
        Point(0, -1),           // up
        Point(-1, 0)            // left
    };
    
    while(!route.empty()) {
        const Point current = route.top();
        if(current == end) {
            break;
        }

        lab[current.row][current.col] = LAB_TEMP_WALL;

        bool found = false;
        for(std::size_t i = 0; i < 4; ++ i) {
            const Point next = current + directions[i];
            if(next.checkBounds() && lab[next.row][next.col] == LAB_EMPTY) {
                // lab[next.row][next.col] = LAB_TEMP_WALL;
                route.push(next);
                found = true;
                break;
            }
        }

        if (!found) {
            route.pop();
        }   
    }

    // Fix lab
    for (std::size_t i = 0; i < labSize; ++i) {
        for (std::size_t j = 0; j < labSize; ++j) {
            if (lab[i][j] == LAB_TEMP_WALL) {
                lab[i][j] = LAB_EMPTY;
            }
        }
    }

    if(route.empty()) return false;
    else {
        std::stack<Point> reversed;
        while(!route.empty()) {
            reversed.push(route.top());
            route.pop();
        }
        while(!reversed.empty()) {
            std::cout << reversed.top() << std::endl;
            reversed.pop();
        }
    }
    return true;
}


int main() {

    // std::cout << polishNotationConvert("AB+CD-*XY-*") << "\n";

    std::cout << hasRoute({0, 0}, {0,4}, lab) << std::endl;
}
















#if 0
#include <string>
#include <stack>

bool isOperator(char c) {
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
        return true;
    default:
        return false;
    }
}

std::string postfixToPrefix(const std::string& expression) {
    std::stack<std::string> stack;

    for (std::size_t i = 0; i < expression.size(); ++i) {
        if (isOperator(expression[i])) {
            assert(stack.size() >= 2);
            std::string op1 = stack.top();
            stack.pop();
            std::string op2 = stack.top();
            stack.pop();

            std::string temp = expression[i] + op2 + op1;
            stack.push(temp);
        } else {
            stack.push(std::string(1, expression[i]));
        }
    }
    std::string ans = "";
    while(stack.empty() == false) {
        ans += stack.top();
        stack.pop();
    }
    return ans;
}

int main() {
    std::string expression = "AB+CD-*XY-*"; // "AB+CD-*AB+CD-*";

    std::string prefix = postfixToPrefix(expression);
    // assert(prefix == "*+AB-CD*+AB-CD");
    std::cout << prefix << "\n";
}
#endif
