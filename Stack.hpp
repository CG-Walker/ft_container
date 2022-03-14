#include <vector>

namespace ft
{

template <class T, class Container = std::vector<T>>
class stack
{
public:

	typedef Container								container_type;
	typedef typename Container::value_type			value_type;
	typedef typename Container::size_type			size_type;
	typedef typename Container::reference			reference;
	typedef typename Container::constr_reference	const_reference;

	// Constructeur
	explicit stack( const Container & cont = Container() );
	stack( const stack & other );
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
	bool empty() const
	{
		if (size() == 0)
			return (true);
		else
			return (false);
	};
	// Size
	size_type size() const
	{
		return (c.size());
	}
	// Push
	// Pop
private:

}; // Class Vector

// Fonctions non membre :
// == != < <= > >=

} // Namespace FT