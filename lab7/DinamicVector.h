#pragma once
#include <string>
#include <stdexcept>

template <typename T>
class IteratorVector;

template<typename T>
class MyVector {
    friend class IteratorVector<T>;

private:
    size_t cap;
    size_t lg;
    T* elems;
    void resize();

public:
    MyVector() : cap{ 1 }, lg{ 0 }, elems{ new T[cap] } {};
    MyVector(const size_t initialCapacity) : cap{ initialCapacity }, lg{ 0 }, elems{ new T[initialCapacity] } {};
    MyVector(const MyVector& v);
    MyVector& operator=(const MyVector& v);
    void push_back(T elem);
    void erase(size_t index);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t size() const { return this->lg; };
    IteratorVector<T> begin() { return IteratorVector<T>(*this); };
    IteratorVector<T> end() { return IteratorVector<T>(*this, this->lg); };
    //const IteratorVector<T> begin() const { return IteratorVector<T>(*this); };
     const IteratorVector<T> begin() const { return IteratorVector<T>(const_cast<MyVector<T>&>(*this)); };

    //const IteratorVector<T> end() const { return IteratorVector<T>(*this, this->lg); };
    const IteratorVector<T> end() const { return IteratorVector<T>(const_cast<MyVector<T>&>(*this), this->lg); };
    ~MyVector();
    bool empty() const {
        return this->lg == 0;
    }
};

template<typename T>
class IteratorVector {
private:
    MyVector<T>& v;   // Remove const from here
    size_t current_index;

public:
    IteratorVector(MyVector<T>& vecToIterate) : v{ vecToIterate }, current_index{ 0 } {}
    IteratorVector(MyVector<T>& vecToIterate, size_t poz) : v{ vecToIterate }, current_index{ poz } {};
    T& element(); // Change to non-const
    void next();
    bool valid() const noexcept;
    T& operator*(); // Change to non-const
    IteratorVector& operator++();
    IteratorVector& operator++(int);
    bool operator==(const IteratorVector& ot) noexcept;
    bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename T>
inline void MyVector<T>::resize() {
    size_t newCapacity = this->cap * 2;
    T* newElems = new T[newCapacity];
    for (size_t i = 0; i < this->lg; i++)
        newElems[i] = this->elems[i];
    delete[] elems;
    this->elems = newElems;
    this->cap = newCapacity;
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector& v) {
    this->cap = v.cap;
    this->lg = v.lg;
    this->elems = new T[this->cap];
    for (size_t i = 0; i < this->lg; i++)
        this->elems[i] = v.elems[i];
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector& v) {
    if (this == &v)
        return *this;
    this->cap = v.cap;
    this->lg = v.lg;
    delete[] this->elems;
    this->elems = new T[this->cap];
    for (size_t i = 0; i < this->lg; i++)
        this->elems[i] = v.elems[i];
    return *this;
}

template<typename T>
inline void MyVector<T>::push_back(T elem) {
    if (this->lg >= this->cap) {
        resize();
    }
    this->elems[this->lg++] = elem;
}

template<typename T>
inline void MyVector<T>::erase(size_t index) {
    if (index >= this->lg)
        throw std::out_of_range("Index out of bounds: " + std::to_string(index));
    for (size_t i = index; i < this->lg - 1; ++i) {
        this->elems[i] = this->elems[i + 1];
    }
    --this->lg;
}

template<typename T>
inline T& MyVector<T>::operator[](size_t index) {
    if (index >= this->lg)
        throw std::out_of_range("Index out of bounds: " + std::to_string(index));
    return this->elems[index];
}

template<typename T>
inline const T& MyVector<T>::operator[](size_t index) const {
    if (index >= this->lg)
        throw std::out_of_range("Index out of bounds: " + std::to_string(index));
    return this->elems[index];
}

template<typename T>
inline MyVector<T>::~MyVector() {
    delete[] this->elems;
}

template<typename T>
inline T& IteratorVector<T>::element() {
    return this->v.elems[current_index];  // Change to non-const
}

template<typename T>
inline void IteratorVector<T>::next() {
    if (this->current_index >= this->v.lg)
        throw std::out_of_range("Invalid iterator.");
    this->current_index++;
}

template<typename T>
inline bool IteratorVector<T>::valid() const noexcept {
    return (this->current_index < this->v.lg);
}

template<typename T>
inline T& IteratorVector<T>::operator*() {
    return this->element(); // Change to non-const
}

template<typename T>
inline IteratorVector<T>& IteratorVector<T>::operator++() {
    this->next();
    return *this;
}

template<typename T>
inline IteratorVector<T>& IteratorVector<T>::operator++(int) {
    this->next();
    return *this;
}

template<typename T>
inline bool IteratorVector<T>::operator==(const IteratorVector& ot) noexcept {
    return this->current_index == ot.current_index;
}

template<typename T>
inline bool IteratorVector<T>::operator!=(const IteratorVector& ot) noexcept {
    return !(*this == ot);
}
