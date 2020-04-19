#pragma once

#include <memory>

constexpr size_t CONT_OVERFLOW_ERR = 1;
constexpr size_t CONT_EMPTY_ERR = 2;

template<typename T>
class container {
private:
    T* m_values;
    size_t m_size;
    size_t m_current;
    void copy_from(const container<T>& other) {
        m_size = other.m_size;
        m_current = other.m_current;
        m_values = new T[m_size];
        std::memcpy(m_values, other.m_values, sizeof(T) * m_size);
    }
    void move_from(container<T>& other) {
        m_size = other.m_size;
        m_current = other.m_current;
        m_values = other.m_values;

        other.m_values = nullptr;
    }
public:
    container(const size_t size): m_values{ new T[size] }, m_size{ size }, m_current{ 0 } {}
    container(const container<T>& other) {
        copy_from(other);
    }
    container(container<T>&& other) {
        move_from(other);
    }
    ~container() {
        delete[] m_values;
    }
    container<T>& operator=(const container<T>& other) {
        copy_from(other);
        return *this;
    }
    container<T>& operator=(container<T>&& other) {
        move_from(other);
    }
    void clear() {
        m_current = 0;
    }
    void add(const T value) {
        if (m_current == m_size) throw CONT_OVERFLOW_ERR;
        std::memcpy(&m_values[m_current], &value, sizeof(T));
        m_current++;
    }
    T get(const size_t index) const {
        if (m_current == 0) throw CONT_EMPTY_ERR;
        T value;
        std::memcpy(&value, &m_values[index], sizeof(T));
        return value;
    }
    size_t size() const {
        return m_current;
    }
};
