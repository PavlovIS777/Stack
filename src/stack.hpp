//#include <exception>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <stdexcept>


namespace PIlib
{
    uint64_t DEFAULT_STACK_CAPACITY = 25;
    template <typename T>
    class stack
    {
    public:
        stack(): data_(new T[DEFAULT_STACK_CAPACITY]){}
        ~stack();
        stack(const stack<T>&);
        stack(stack<T> && other) noexcept;
        T top() const;
        void push(const T& value);
        void push(T&& );
        void pop();
        void resize(int64_t newCapacity);
        int64_t size() const;
        bool empty() const;
        template<typename ... D> void emplace(D&& ... args);
        stack<T>& operator=(const stack<T>&);
        stack<T>& operator=(stack<T>&&) noexcept;
    private:
        T* data_ = nullptr;
        int64_t size_ = 0ll;
        int64_t capacity_ = DEFAULT_STACK_CAPACITY;
    };

    template<typename T> void stack<T>::resize(int64_t newCapacity) {
        auto newData_ = new T[newCapacity];
        std::copy(data_, data_ + capacity_, newData_);
        capacity_ = newCapacity;
        delete [] data_;
        data_ = newData_;
    }

    template<typename T> void stack<T>::push(const T& value) {
        if (size_ < capacity_) {
            data_[size_++] = value;
        } else {
            this->resize(capacity_ * 2);
            data_[size_++] = value;
        }
    }

    template<typename T> void stack<T>::push(T&& value) {
        if (size_ < capacity_) {
            data_[size_++] = std::move(value);
        } else {
            this->resize(capacity_*2);
            data_[size_++] = std::move(value);
        }
    }

    template<typename T> void stack<T>::pop() {
        if (size_ == 0) {
            throw std::out_of_range("Segmentation fault. Stack is empty");
        }
        size_--;
    }

    template<typename T> T stack<T>::top() const {
        if (size_ == 0) {
            throw std::out_of_range("Segmentation fault. Stack is empty.\n");
        }
        return data_[size_-1];
    }

    template<typename T> bool stack<T>::empty() const {
        return (size_ == 0);
    }

    template<typename T> stack<T>::~stack() {
        delete [] data_;
    }

    template <typename T> template<typename ... D> void stack<T>::emplace(D&& ... args) {
        push(T(args ...));
    }

    template<typename T> stack<T>::stack(stack<T>&& other) noexcept {
        delete [] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
    }

    template<typename T> int64_t stack<T>::size() const {
        return size_;
    } 

    template<typename T> stack<T>::stack(const stack<T>& other) {
        data_ = new T[other.capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
    }
    template<typename T> stack<T>& stack<T>::operator=(const stack<T>& other) {
        if (this == &other) {
            return *this;
        }
        delete [] data_;
        data_ = new T[other.capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;     
    }
    
    template<typename T> stack<T>& stack<T>::operator=(stack<T>&& other) noexcept {
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        other.data_ = nullptr;
        return *this;
    }

    const int64_t BIT_IN_BYTE = std::numeric_limits<char>::digits + 1;
    const int64_t DEFAULT_BOOL_STACK_CAPACITY = sizeof(int64_t) * BIT_IN_BYTE;
    template <>
    class stack<bool>
    {
    public:
        stack(): data_(new uint64_t[DEFAULT_BOOL_STACK_CAPACITY]{0}){}
        ~stack();
        stack(const stack<bool>&);
        stack(stack<bool> && other) noexcept;
        bool top() const;
        void push(const bool& value);
        void push(bool&& );
        void pop();
        bool empty() const;
        void resize(int64_t newCapacity);
        int64_t size() const;
        stack<bool>& operator=(const stack<bool>&);
        stack<bool>& operator=(stack<bool>&&) noexcept;
    private:
        uint64_t* data_ = nullptr;
        int64_t size_ = 0;
        int64_t capacity_ = DEFAULT_BOOL_STACK_CAPACITY;
    };

    void stack<bool>::resize(int64_t newCapacity) {
        auto* newData_ = new uint64_t[newCapacity];
        std::copy(data_, data_ + size_, newData_);
        capacity_ = newCapacity;
        delete [] data_;
        data_ = newData_;
    }

    void stack<bool>::push(const bool& value) {
        if (size_ == capacity_) {
            this->resize(capacity_ * 2);
        }
        ++size_;
        int64_t offset = (size_ - 1) / (sizeof(int64_t) * BIT_IN_BYTE);
        int64_t pos = (size_ - 1) % (sizeof(int64_t) * BIT_IN_BYTE);
        data_[offset] &= (std::numeric_limits<std::uint64_t>::max() - (1ull << pos));
        data_[offset] += (uint64_t(value) << pos);
    }

    void stack<bool>::push(bool&& value) {
        this->push(value);
    }

    void stack<bool>::pop() {
        if (size_ == 0) {
            throw std::out_of_range("Segmentation fault. Stack is empty");
        }
        size_--;
    }

    bool stack<bool>::top() const {
        if (size_ == 0) {
            throw std::out_of_range("Segmentation fault. Stack is empty.\n");
        }
        int64_t pos = (size_ - 1) % (sizeof(int64_t) * BIT_IN_BYTE);
        int64_t offset = (size_ - 1) / (sizeof(int64_t) * BIT_IN_BYTE);

        return (data_[offset] & (1ull << pos));
    }

    bool stack<bool>::empty() const {
        return (size_ == 0);
    }

    stack<bool>::~stack() {
        delete [] data_;
    }
    int64_t stack<bool>::size() const {
        return size_;
    } 
    stack<bool>::stack(stack<bool>&& other) noexcept {
        delete [] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
    }

    stack<bool>::stack(const stack<bool>& other) {
        if (this == &other) {
            return;
        }
        delete [] data_;
        data_ = new uint64_t[other.capacity_];
        size_ = other.size_;
        std::copy(other.data_, other.data_ + size_, data_);
    }
    stack<bool>& stack<bool>::operator=(const stack<bool>& other) {
        if (this == &other) {
            return *this;
        }
        delete [] data_;
        data_ = new uint64_t[other.capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;   
    }

    stack<bool>& stack<bool>::operator=(stack<bool>&& other) noexcept {
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        other.data_ = nullptr;
        return *this;
    }
} // namespace PIlib
