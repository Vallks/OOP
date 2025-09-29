#include <iostream>
#include <cmath>
#include <vector>
#include <string>

class Equation 
{
protected:
    std::string equation_name;

public:
    Equation(const std::string& name = "Уравнение") : equation_name(name) {}
    virtual ~Equation() = default;

    virtual std::vector<double> findRoots() const = 0;

    virtual void printEquation() const = 0;

    virtual void printRootsInfo() const {
        std::vector<double> roots = findRoots();
        std::cout << equation_name << ":" << std::endl;
        printEquation();

        if (roots.empty())
        {
            std::cout << "Корней нет" << std::endl;
        }
        else
        {
            std::cout << "Корни: ";
            for (size_t i = 0; i < roots.size(); ++i) 
            {
                std::cout << roots[i];
                if (i < roots.size() - 1) 
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }
};

// Класс линейных уравнений: ax + b = 0
class LinearEquation : public Equation 
{
private:
    double a, b;

public:
    LinearEquation(double a_val, double b_val) : Equation("Линейное уравнение"), a(a_val), b(b_val) { }

    std::vector<double> findRoots() const override 
    {
        std::vector<double> roots;

        if (a == 0) 
        {
            if (b == 0) 
            {
                return roots; 
            }
            else 
            {
                return roots;
            }
        }
        else
        {
            roots.push_back(-b / a);
            return roots;
        }
    }

    void printEquation() const override 
    {
        std::cout << a << "x + " << b << " = 0" << std::endl;
    }
};

class QuadraticEquation : public Equation 
{
private:
    double a, b, c;

public:
    QuadraticEquation(double a_val, double b_val, double c_val): Equation("Квадратное уравнение"), a(a_val), b(b_val), c(c_val) { }

    std::vector<double> findRoots() const override 
    {
        std::vector<double> roots;

        if (a == 0) {
            LinearEquation linear(b, c);
            return linear.findRoots();
        }

        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) 
        {
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            roots.push_back(root1);
            roots.push_back(root2);
        }
        else if (discriminant == 0) 
        {
            double root = -b / (2 * a);
            roots.push_back(root);
        }

        return roots;
    }

    void printEquation() const override 
    {
        std::cout << a << "^2 + " << b << "x + " << c << " = 0" << std::endl;
    }

    void printRootsInfo() const override 
    {
        std::vector<double> roots = findRoots();
        std::cout << equation_name << ":" << std::endl;
        printEquation();

        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) 
        {
            std::cout << "Дискриминант: " << discriminant << " > 0" << std::endl;
            std::cout << "Два действительных корня: " << roots[0] << ", " << roots[1] << std::endl;
        }
        else if (discriminant == 0) 
        {
            std::cout << "Дискриминант: " << discriminant << " = 0" << std::endl;
            std::cout << "Один корень (кратности 2): " << roots[0] << std::endl;
        }
        else 
        {
            std::cout << "Дискриминант: " << discriminant << " < 0" << std::endl;
            std::cout << "Действительных корней нет" << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }
};

int main()
{
    setlocale(LC_ALL, "RU");
    Equation* equations[5];

    equations[0] = new LinearEquation(2, -4);      // 2x - 4 = 0
    equations[1] = new LinearEquation(0, 5);       // 0x + 5 = 0 (нет решений)
    equations[2] = new QuadraticEquation(1, -5, 6); // x^2 - 5x + 6 = 0
    equations[3] = new QuadraticEquation(1, -4, 4); // x^2 - 4x + 4 = 0
    equations[4] = new QuadraticEquation(1, 1, 1);  // x^2 + x + 1 = 0

    for (int i = 0; i < 5; ++i) 
    {
        equations[i]->printRootsInfo();
    }

    for (int i = 0; i < 5; ++i) 
    {
        delete equations[i];
    }

    return 0;
}