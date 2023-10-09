#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <initializer_list>
#include <utility>
#include <vector>

namespace cop4530 {
    template <typename T, class Container = std::vector<T>>
    class Stack{
        public:
            //Big Five
            explicit Stack(int initSize = 0);
            ~Stack();
            Stack(const Stack<T>&);
            Stack(Stack<T>&&);
            Stack<T>& operator=(const Stack<T>&);
            Stack<T>& operator=(Stack<T>&&);

            //no touchy functions
            bool empty() const;
            void clear();
            int size() const;
            
            //mutator functions
            void push(const T& x);
            void push(T&& x);
            void pop();

            //peeking functions
            T& top();
            const T& top() const;

            //le print
            void print(std::ostream& os, char ofc=' ') const;

        private:
            int initSize;
            //int capacity;
            //T * elements;
        
        protected:
            Container v;
    };
    template <typename T, class Container = std::vector<T>>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& a);

    template <typename T, class Container = std::vector<T>>
    bool operator==(const Stack<T>&, const Stack <T>&);

    template <typename T, class Container = std::vector<T>>
    bool operator!=(const Stack<T>&, const Stack<T>&);

    template <typename T, class Container = std::vector<T>>
    bool operator<=(const Stack<T>& a, const Stack<T>& b);

    #include "stack.hpp"  // do not change this line    
} 

#endif