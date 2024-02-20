#include <iterator>
#include <functional>

enum class Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

// This iterator can be used with arithmetic types only
template<typename Iterator1,
         typename Iterator2,
         std::enable_if_t<std::is_arithmetic_v<typename std::iterator_traits<Iterator1>::value_type> &&
                          std::is_arithmetic_v<typename std::iterator_traits<Iterator2>::value_type>, bool> = true>
class UniIterator {
private:
    Iterator1 iter1_begin, iter1, iter1_end;
    Iterator2 iter2_begin, iter2, iter2_end;
    Operation operation;
public:
    // Basic typedefs
    using value_type = decltype(*std::declval<Iterator1>() + *std::declval<Iterator2>());
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator = UniIterator<Iterator1, Iterator2>;
    using iterator_category = std::bidirectional_iterator_tag;

    UniIterator() {
        operation = Operation::ADD;
    };

    UniIterator(Iterator1 iter1, Iterator1 iter1_end, Iterator2 iter2, Iterator2 iter2_end)
                : iter1_begin(iter1), iter1(iter1), iter1_end(iter1_end),
                  iter2_begin(iter2), iter2(iter2), iter2_end(iter2_end),
                  operation(Operation::ADD) {}


    ~UniIterator() = default;

    UniIterator(const UniIterator &o) {
        iter1_begin = o.iter1_begin;
        iter1 = o.iter1;
        iter1_end = o.iter1_end;
        iter2_begin = o.iter2_begin;
        iter2 = o.iter2;
        iter2_end = o.iter2_end;
        operation = o.operation;
    }

    UniIterator& operator=(const UniIterator &o) {
        iter1_begin = o.iter1_begin;
        iter1 = o.iter1;
        iter1_end = o.iter1_end;
        iter2_begin = o.iter2_begin;
        iter2 = o.iter2;
        iter2_end = o.iter2_end;
        return *this;
    }

    bool operator==(const UniIterator &o) {
        return iter1 == o.iter1 && iter2 == o.iter2;
    }

    bool operator!=(const UniIterator &o) {
        return !(this == o); //NOLINT
    }

    UniIterator& operator++() {
        if (iter1 != iter1_end) {
            iter1++;
        }
        if (iter2 != iter2_end) {
            iter2++;
        }
        return *this;
    }

    UniIterator& operator++(int) { //NOLINT
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    UniIterator& operator--() {
        if (iter1 != iter1_begin)
            iter1--;
        if (iter2 != iter2_begin)
            iter2--;
        return *this;
    }

    UniIterator& operator--(int) { //NOLINT
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    /**
     * @brief Overloaded dereference operator that returns the result of chosen operation on two iterators
     * @note The operation is chosen by the setOperation method
     * @note Return type is deduced from the sum operation
     */
    auto operator*() const -> decltype(*iter1 + *iter2) {
        switch (operation) {
            case Operation::ADD:
                return add();
            case Operation::SUBTRACT:
                return subtract();
            case Operation::MULTIPLY:
                return multiply();
            case Operation::DIVIDE:
                return divide();
            default:
                return add();
        }
    }

    auto multiply () const -> decltype(*iter1 * *iter2) {
        return *iter1 * *iter2;
    }

    auto divide () const -> decltype(*iter1 / *iter2) {
        if (*iter2 == 0)
            throw std::runtime_error("Error: Division by zero");
        return *iter1 / *iter2;
    }

    auto add () const -> decltype(*iter1 + *iter2) {
        return *iter1 + *iter2;
    }

    auto subtract () const -> decltype(*iter1 - *iter2) {
        return *iter1 - *iter2;
    }

    /**
     * @brief Function to apply a function to the two iterators
     * @param f The function to apply
     */
    auto apply(std::function<auto(Iterator1, Iterator2) -> decltype(*iter1 + *iter2)> f) {
        return f(*iter1, *iter2);
    }

    void setOperation(Operation op) {
        operation = op;
    }
};
