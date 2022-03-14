#include <vector>

namespace ft
{


template <class T, class Container = std::vector<T>> 
class stack
{
public:
	// Constructeur
	// Destructeur
    ~stack();
	// Operator =
    stack& operator=( const stack& other );
    {
        c = other.c;
        return(*this);
    }
	// Top
    reference top();
    { 
         return (this->ct.back());
    }
    const_reference top() const;
    { 
         return (this->ct.back());
    }
	// Empty
	// Size
	// Push
	// Pop
private:

}; // Class Vector

// Fonctions non membre :
// == != < <= > >=

} // Namespace FT