#include <string>
#include <iostream>

class Evt
{
protected:
    std::string sujet;

public:
    explicit Evt(const std::string &s);
    virtual ~Evt() = default;

    // Template Method 的“可变步骤”
    virtual std::string toString() const = 0;

    // Template Method 的“模板方法”（固定流程）
    virtual void afficher(std::ostream &f = std::cout) const;
};