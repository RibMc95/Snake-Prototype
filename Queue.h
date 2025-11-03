#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue
{
private:
    std::vector<T> data;
    size_t front_index;
    size_t rear_index;
    size_t count;

public:
    // Constructor
    Queue() : front_index(0), rear_index(0), count(0)
    {
        data.reserve(10); // Reserve initial capacity
    }

    // Constructor with initial capacity
    Queue(size_t initial_capacity) : front_index(0), rear_index(0), count(0)
    {
        data.reserve(initial_capacity);
    }

    // Destructor
    ~Queue() = default;

    // Add element to the rear of the queue
    void enqueue(const T &item)
    {
        if (count == data.capacity())
        {
            // Resize and reorganize the vector
            std::vector<T> new_data;
            new_data.reserve(data.capacity() * 2);

            // Copy elements in correct order
            for (size_t i = 0; i < count; ++i)
            {
                new_data.push_back(data[(front_index + i) % data.capacity()]);
            }

            data = std::move(new_data);
            front_index = 0;
            rear_index = count;
        }

        if (rear_index == data.capacity())
        {
            data.resize(data.capacity());
        }

        if (count < data.capacity())
        {
            if (rear_index == data.size())
            {
                data.push_back(item);
            }
            else
            {
                data[rear_index] = item;
            }
        }

        rear_index = (rear_index + 1) % data.capacity();
        ++count;
    }

    // Remove element from the front of the queue
    T dequeue()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty - cannot dequeue");
        }

        T item = data[front_index];
        front_index = (front_index + 1) % data.capacity();
        --count;

        return item;
    }

    // Get the front element without removing it
    T &front()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty - no front element");
        }
        return data[front_index];
    }

    const T &front() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty - no front element");
        }
        return data[front_index];
    }

    // Get the rear element without removing it
    T &rear()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty - no rear element");
        }
        size_t rear_pos = (rear_index - 1 + data.capacity()) % data.capacity();
        return data[rear_pos];
    }

    const T &rear() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue is empty - no rear element");
        }
        size_t rear_pos = (rear_index - 1 + data.capacity()) % data.capacity();
        return data[rear_pos];
    }

    // Check if queue is empty
    bool isEmpty() const
    {
        return count == 0;
    }

    // Get the size of the queue
    size_t size() const
    {
        return count;
    }

    // Get the capacity of the queue
    size_t capacity() const
    {
        return data.capacity();
    }

    // Clear the queue
    void clear()
    {
        count = 0;
        front_index = 0;
        rear_index = 0;
    }

    // Display queue contents (for debugging)
    void display() const
    {
        if (isEmpty())
        {
            std::cout << "Queue is empty" << std::endl;
            return;
        }

        std::cout << "Queue contents (front to rear): ";
        for (size_t i = 0; i < count; ++i)
        {
            std::cout << data[(front_index + i) % data.capacity()];
            if (i < count - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
};

#endif // QUEUE_H