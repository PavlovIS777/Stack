#include "stack.h"

template <>
class stack<bool> {
public:
    stack() : data_(new uint64_t[DEFAULT_BOOL_STACK_CAPACITY / sizeof(int64_t)] {0}) {}
    ~stack();
    stack(const stack<bool> &);
    stack(stack<bool> &&other) noexcept;
    bool top() const;
    void push(const bool &value);
    void push(bool &&);
    void pop();
    bool empty() const;
    void resize(int64_t newCapacity);
    int64_t size() const;
    stack<bool> &operator=(const stack<bool> &);
    stack<bool> &operator=(stack<bool> &&) noexcept;

private:
    uint64_t *data_ = nullptr;
    int64_t size_ = 0;
    int64_t capacity_ = DEFAULT_BOOL_STACK_CAPACITY;
};

void stack<bool>::resize(int64_t newCapacity)
{
    auto *newData_ = new uint64_t[newCapacity / sizeof(int64_t)];
    std::copy(data_, data_ + capacity_ / sizeof(int64_t), newData_);
    capacity_ = newCapacity;
    delete[] data_;
    data_ = newData_;
}

void stack<bool>::push(const bool &value)
{
    if (size_ == capacity_) {
        this->resize(capacity_ * 2);
    }
    ++size_;
    int64_t offset = (size_ - 1) / (sizeof(int64_t) * BIT_IN_BYTE);
    int64_t pos = (size_ - 1) % (sizeof(int64_t) * BIT_IN_BYTE);
    data_[offset] &= (std::numeric_limits<std::uint64_t>::max() - (1ull << pos));
    data_[offset] += (uint64_t(value) << pos);
}

void stack<bool>::push(bool &&value)
{
    this->push(value);
}

void stack<bool>::pop()
{
    if (size_ == 0) {
        throw std::out_of_range("Segmentation fault. Stack is empty");
    }
    size_--;
}

bool stack<bool>::top() const
{
    if (size_ == 0) {
        throw std::out_of_range("Segmentation fault. Stack is empty.\n");
    }
    int64_t pos = (size_ - 1) % (sizeof(int64_t) * BIT_IN_BYTE);
    int64_t offset = (size_ - 1) / (sizeof(int64_t) * BIT_IN_BYTE);

    return (data_[offset] & (1ull << pos));
}

bool stack<bool>::empty() const
{
    return (size_ == 0);
}

stack<bool>::~stack()
{
    delete[] data_;
}

int64_t stack<bool>::size() const
{
    return size_;
}

stack<bool>::stack(stack<bool> &&other) noexcept
{
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
}

stack<bool>::stack(const stack<bool> &other)
{
    if (this == &other) {
        return;
    }
    delete[] data_;
    data_ = new uint64_t[other.capacity_ / sizeof(int64_t)];
    size_ = other.size_;
    std::copy(other.data_, other.data_ + other.capacity_ / sizeof(int64_t), data_);
}

stack<bool> &stack<bool>::operator=(const stack<bool> &other)
{
    if (this == &other) {
        return *this;
    }
    delete[] data_;
    data_ = new uint64_t[other.capacity_ / sizeof(int64_t)];
    std::copy(other.data_, other.data_ + other.capacity_ / sizeof(int64_t), data_);
    capacity_ = other.capacity_;
    size_ = other.size_;
    return *this;
}

stack<bool> &stack<bool>::operator=(stack<bool> &&other) noexcept
{
    data_ = other.data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    other.data_ = nullptr;
    return *this;
}
