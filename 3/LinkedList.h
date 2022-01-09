#include <cstddef>
#include <cstdint>
#include <iterator>
#include <iostream>


template<bool is_T, typename T, typename F>
struct conditional {
    using type = F;
};

template<typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};


template<bool is_T, typename T, typename F>
using conditional_t = typename conditional<is_T, T, F>::type;


template<typename T>
class LinkedList {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
private:
    struct Node {
        value_type value;
        Node *prev;
        Node *next;
    };

    Node *mate = reinterpret_cast<Node *>(new int8_t[sizeof(Node)]);
    size_type _size = 0;

    template<bool is_const>
    class typed_iterator : public std::iterator<
            std::bidirectional_iterator_tag,
            LinkedList<T>::value_type,
            LinkedList<T>::difference_type,
            LinkedList<T>::pointer,
            LinkedList<T>::reference> {

        using conditional_value_type = conditional_t<is_const, const value_type, value_type>;

        friend class LinkedList;

    private:
        Node *_ptr;

    public:
        typed_iterator(Node *ptr) : _ptr(ptr) {};

        typed_iterator(const typed_iterator &other) : _ptr(other._ptr) {};

        conditional_value_type &operator*() {
            return _ptr->value;
        }

        conditional_value_type *operator->() {
            return &(_ptr->value);
        }

        typed_iterator &operator++() {
            _ptr = _ptr->next;
            return *this;
        }

        typed_iterator operator++(int) {
            typed_iterator temp(_ptr);
            _ptr = _ptr->next;
            return temp;
        }

        typed_iterator &operator--() {
            _ptr = _ptr->prev;
            return *this;
        }

        typed_iterator operator--(int) {
            typed_iterator temp(_ptr);
            _ptr = _ptr->prev;
            return temp;
        }

        typed_iterator &operator=(const typed_iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

        bool operator==(const typed_iterator &other) {
            return _ptr == other._ptr;
        }

        bool operator!=(const typed_iterator &other) {
            return !(*this == other);
        }

    };

    template<bool is_const>
    class typed_riterator :
            public std::iterator<
                    std::bidirectional_iterator_tag,
                    LinkedList<T>::value_type,
                    LinkedList<T>::difference_type,
                    LinkedList<T>::pointer,
                    LinkedList<T>::reference
            > {

        using conditional_value_type = conditional_t<is_const, const value_type, value_type>;

        friend class LinkedList;

    private:
        Node *_ptr;

    public:
        typed_riterator(Node *ptr) : _ptr(ptr) {};

        typed_riterator(const typed_riterator &other) : _ptr(other._ptr) {};

        conditional_value_type &operator*() {
            return _ptr->value;
        }

        conditional_value_type *operator->() {
            return &(_ptr->value);
        }

        typed_riterator &operator++() {
            _ptr = _ptr->prev;
            return *this;
        }

        typed_riterator operator++(int) {
            typed_iterator temp(_ptr);
            _ptr = _ptr->prev;
            return temp;
        }

        typed_riterator &operator--() {
            _ptr = _ptr->next;
            return *this;
        }

        typed_riterator operator--(int) {
            typed_iterator temp(_ptr);
            _ptr = _ptr->next;
            return temp;
        }

        typed_riterator &operator=(const typed_riterator &other) {
            _ptr = other._ptr;
            return *this;
        }

        bool operator==(const typed_riterator &other) {
            return _ptr == other._ptr;
        }

        bool operator!=(const typed_riterator &other) {
            return !(*this == other);
        }

    };


public:
    using iterator = typed_iterator<false>;
    using const_iterator = typed_iterator<true>;
    using reverse_iterator = typed_riterator<false>;
    using const_reverse_iterator = typed_riterator<false>;

public:
    LinkedList() {
        std::cout << "default constructor" << std::endl;
        mate->next = nullptr;
        mate->prev = nullptr;
        // mate -> value is UB
    }

    LinkedList(const LinkedList &other) : LinkedList() {
        *this = other;
    }

    LinkedList(LinkedList &&other) : LinkedList() {
        *this = std::move(other);
    }

    LinkedList(size_type count, const T &value) : LinkedList() {
        insert(cend(), count, value);
    }

    explicit LinkedList(size_type count) : LinkedList() {
        while (count) {
            insert_without_value(cend());
            --count;
        }
    }

    template<typename InputIt>
    LinkedList(InputIt first, InputIt last) : LinkedList() {
        insert(cend(), first, last);
    }

    LinkedList(std::initializer_list<T> init) : LinkedList() {
        *this = init;
    }

    ~LinkedList() {
        std::cout << this << std::endl;
        if (!empty()) clear();
        std::cout << "delete mate" << std::endl;
        delete mate;
    }

public:
    LinkedList &operator=(const LinkedList &other) {
        assign(other.begin(), other.end());
        return *this;
    }

    LinkedList &operator=(LinkedList &&other) {
        if (!empty()) clear();
        mate->next = other.mate->next;
        mate->prev = other.mate->prev;
        other.mate->next->prev = mate;
        other.mate->prev->next = mate;
        other.mate->next = nullptr;
        other.mate->prev = nullptr;
        _size = other._size;
        other._size = 0;
        std::cout << "move" << std::endl;
        return *this;

    }

    LinkedList &operator=(std::initializer_list<T> ilist) {

        assign(ilist);
        return *this;
    }

    void assign(size_type count, const T &value) {
        if (!empty()) clear();
        insert(cend(), count, value);
    }

    template<typename InputIt>
    void assign(InputIt first, InputIt last) {
        if (!empty()) clear();
        insert(cend(), first, last);
    }

    void assign(std::initializer_list<T> ilist) {
        if (!empty()) clear();
        assign(ilist.begin(), ilist.end());
    }

public:
    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *cbegin();
    }

    reference back() {
        return *rbegin();
    }

    const_reference back() const {
        return *crbegin();
    }

public:
    iterator begin() noexcept {
        return iterator(mate->next);
    }

    const_iterator begin() const noexcept {
        return const_iterator(mate->next);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(mate->next);
    }

    iterator end() noexcept {
        return iterator(mate);
    }

    const_iterator end() const noexcept {
        return const_iterator(mate);
    }

    const_iterator cend() const noexcept {
        return const_iterator(mate);
    }

public:
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(mate->prev);
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(mate->prev);
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(mate->prev);
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(mate);
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(mate);
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(mate);
    }

public:
    size_type size() const noexcept {
        return _size;
    }

    [[nodiscard]] bool empty() const noexcept {
        return _size == 0;
    }

private:
    iterator insert_without_value(const_iterator pos) {
        Node *new_node = new Node;
        if (this->empty()) {
            new_node->prev = pos._ptr;
            std::cout << "1: " << new_node->prev << std::endl;
            new_node->next = pos._ptr;
            std::cout << "2: " << new_node->next << std::endl;
            pos._ptr->next = new_node;
            std::cout << "3: " << pos._ptr->next << std::endl;
            pos._ptr->prev = new_node;
            std::cout << "4: " << pos._ptr->prev << std::endl;

        } else {
            new_node->prev = pos._ptr->prev;
            std::cout << "5: " << new_node->prev << " = " << pos._ptr->prev << std::endl;
            new_node->next = pos._ptr;
            std::cout << "6: " << new_node->next << " = " << pos._ptr << std::endl;
            pos._ptr->prev = new_node;
            std::cout << "7: " << pos._ptr->prev << " = " << new_node << std::endl;
            new_node->prev->next = new_node;
            std::cout << "8: " << new_node->prev->next << " = " << new_node << std::endl;
        }
        ++_size;
        return iterator(new_node);

    }

public:
    iterator insert(const_iterator pos, const T &value) {
        iterator it = insert_without_value(pos);
        it._ptr->value = value;
        return it;
    }

    iterator insert(const_iterator pos, T &&value) {
        iterator it = insert_without_value(pos);
        it._ptr->value = value;
        return it;
    }

    iterator insert(const_iterator pos, size_type count, const T &value) {
        if (count) {
            iterator it = insert(pos, value);
            --count;
            while (count) {
                insert(pos, value);
                --count;
            }
            return it;
        }

        return iterator(pos._ptr);
    }

    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        if (first != last) {
            iterator it = insert(pos, *first);
            ++first;
            for (; first != last; ++first) {
                insert(pos, *first);
            }
            return it;
        }
        return iterator(pos._ptr);

    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return insert(pos, ilist.begin(), ilist.end());
    }

    void push_front(const T &value) {
        if (empty()) {
            insert(cend(), value);
        } else {
            insert(cbegin(), value);
        }
    }

    void push_front(T &&value) {
        if (empty()) {
            insert(cend(), value);
        } else {
            insert(cbegin(), value);
        }
    }

    void push_back(const T &value) {
        insert(cend(), value);
    }

    void push_back(T &&value) {
        insert(cend(), value);
    }

public:
    iterator erase(const_iterator pos) {
        pos._ptr->next->prev = pos._ptr->prev;
        pos._ptr->prev->next = pos._ptr->next;
        iterator it(pos._ptr->next);

        (pos._ptr->value).~value_type();
        delete pos._ptr;

        --_size;
        if (empty()) {
            mate->next = nullptr;
            mate->next = nullptr;
        }
        return it;

    }


    iterator erase(const_iterator first, const_iterator last) {
        while (first != last) {
            std::cout << *last << std::endl;
            erase(first++);
        }
        return iterator(last._ptr);
    }

    void pop_back() {
        erase(--cend());
    }

    void pop_front() {
        erase(cbegin());
    }

public:
    void sort() {
        auto p = [](const T &x, const T &y) { return x < y; };
        sort(p);
    }

    template<typename Compare>
    void merge(size_type l, size_type m, size_type r, LinkedList<T> &temp, Compare comp) {

        iterator left = begin();
        iterator mid = begin();
        iterator right = begin();

        std::advance(left, l);
        std::advance(mid, m);
        std::advance(right, std::min(r, _size));

        iterator temp_mid = mid;
        iterator it = temp.begin();
        std::advance(it, l);

        while (left != temp_mid and mid != right) {
            if (comp(*left, *mid)) {
                it._ptr->value = left._ptr->value;
                ++left;
            } else {
                it._ptr->value = mid._ptr->value;
                ++mid;
            }
            ++it;
        }


        while (left != temp_mid) {
            it._ptr->value = left._ptr->value;
            ++left;
            ++it;
        }

        while (mid != right) {
            it._ptr->value = mid._ptr->value;
            ++mid;
            ++it;
        }

    }

    void print() {
        for (const_reference x: *this) std::cout << x << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    };


    template<typename Compare>
    void sort(Compare comp) {
        LinkedList<T> temp(_size);
        for (size_type i = 1; i <= _size; i *= 2) {
            for (size_type j = 0; j <= _size - i; j += 2 * i) {

                merge(j, j + i, j + 2 * i, temp, comp);
            }
            swap(temp);
        }
    }

    size_type unique() {
        auto p = [](const T &x, const T &y) { return x == y; };
        return unique(p);
    }

    template<typename BinaryPredicate>
    size_type unique(BinaryPredicate p) {
        size_type count = 0;
        for (const_iterator it = cbegin(); it != cend(); ++it) {
            const_iterator temp = it;
            while (p(*it, *(++temp)) && temp != cend()) {
                ++count;
                erase(temp);
                temp = it;
            }
        }
        return count;
    }

    void reverse() noexcept {
        iterator temp;
        for (iterator &it = begin();; --it) {
            temp = it;
            it._ptr->next = it._ptr->prev;
            it._ptr->prev = temp._ptr->next;
            if (it == end()) break;
        }
    }

    size_type remove(const T &value) {
        auto p = [&value](const T &other) { return value == other; };
        return remove_if(p);
    }

    template<typename UnaryPredicate>
    size_type remove_if(UnaryPredicate p) {
        size_type count = 0;
        for (const_iterator it = cbegin(); it != cend();) {
            const_iterator temp = it;
            ++it;
            if (p(*temp)) {
                ++count;
                erase(temp);
            }
        }
        return count;
    }

private:
    void remove_after(size_type count) {
        const_iterator first = cbegin();
        while (count) {
            ++first;
            --count;
        }
        erase(first, cend());
    }

public:
    void clear() noexcept {
        std::cout << "clear" << std::endl;
        erase(cbegin(), cend());
    }

    void resize(size_type count, const value_type &value) {
        if (count < _size) {
            remove_after(count);
        } else {
            insert(cend(), count - _size, value);
        }
    }

    void resize(size_type count) {
        if (count < _size) {
            remove_after(count);
        } else {
            size_type count_new_elements = count - _size;
            while (count_new_elements) {
                insert_without_value(cend());
                --count_new_elements;
            }
        }

    }

    void swap(LinkedList &other) noexcept {
        size_type temp_sz = _size;
        Node *temp = mate;
        mate = other.mate;
        other.mate = temp;

        _size = other._size;
        other._size = temp_sz;
    }

};