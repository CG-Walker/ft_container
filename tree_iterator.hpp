#include "Utils.hpp"
#include "Tree.hpp"
#include "IteratorTrait.hpp"

namespace ft
{
template <class T>
    class tree_iterator_ : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        // Types
        typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<T>::value_type value_type;
        typedef typename ft::iterator_traits<T>::difference_type difference_type;
        typedef typename ft::iterator_traits<T>::pointer pointer;
        typedef typename ft::iterator_traits<T>::reference reference;

    private:
        typedef ft::node<value_type> *link_type;

    public:
        // Member functions
        // constructor
        tree_iterator_() : current_(NULL) {}
        explicit tree_iterator_(link_type ptr, link_type nil)
            : current_(ptr), nil_(nil) {}

        // copy constructor
        template <class Iter>
        tree_iterator_(const tree_iterator_<Iter> &other)
        {
            *this = other;
        }

        // assignment operator
        template <class Iter>
        tree_iterator_ &operator=(const tree_iterator_<Iter> &other)
        {
            current_ = other.base();
            nil_ = other.get_nil();
            return *this;
        }

        // dereference operator
        reference operator*() const
        {
            return current_->value;
        }
        pointer operator->() const
        {
            return &current_->value;
        }

        // prefix/postfix increment
        tree_iterator_ &operator++()
        {
            current_ = utils_.search_next_node(current_, nil_);
            return *this;
        }
        tree_iterator_ operator++(int)
        {
            tree_iterator_ tmp(*this);
            ++(*this);
            return tmp;
        }

        // prefix/postfix decrement
        tree_iterator_ &operator--()
        {
            current_ = utils_.search_prev_node(current_, nil_);
            return *this;
        }
        tree_iterator_ operator--(int)
        {
            tree_iterator_ tmp(*this);
            --(*this);
            return tmp;
        }

        link_type base() const
        {
            return current_;
        }

        link_type get_nil() const
        {
            return nil_;
        }

    private:
        link_type current_;
        link_type nil_;
        rb_node_utils_<value_type> utils_;
    };
}