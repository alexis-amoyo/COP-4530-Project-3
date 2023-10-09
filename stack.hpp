//protect later

//explicit constructor
template<typename T, class Container>
Stack<T, Container>::Stack(int initSize){
    //nothing
}

//Destructor
template<typename T, class Container>
Stack<T, Container>::~Stack(){
    clear();
}

//Copy Constructor
template<typename T, class Container>
Stack<T, Container>::Stack(const Stack<T>& rhs){
    v = rhs.v;
}

//Move Constructor
template<typename T, class Container>
Stack<T, Container>::Stack(Stack<T>&& rhs){
    v = rhs.v;
    rhs.clear();
}

//Copy Assignment Operator
template<typename T, class Container>
Stack<T>& Stack<T, Container>::operator=(const Stack<T>& rhs){
    Stack<T, Container> copy = rhs;
    std::swap(*this, copy);
    return *this;
}

//Move Assignment Operator
template<typename T, class Container>
Stack<T>& Stack<T, Container>::operator=(Stack<T>&& rhs){
    std::swap(v, rhs.v);    //only works with v not *this
    return *this;
}

//Empty, vector empty from C++ info page
template<typename T, class Container>
bool Stack<T, Container>::empty() const{
    if(v.empty())
        return true;
    else
        return false;
}

//Clear, vector pop_back from C++ info page
template<typename T, class Container>
void Stack<T, Container>::clear(){
    while(!v.empty())
        v.pop_back();
}

//Size, vector size from C++ info page
template<typename T, class Container>
int Stack<T, Container>::size() const{
    return v.size();
}

//Push Back Function - Copy, vector push_back from C++ info page
template<typename T, class Container>     
void Stack<T, Container>::push(const T& x){
    v.push_back(x);
}

//Push Back Function - Move, vector push_back from C++ info page
template<typename T, class Container>
void Stack<T, Container>::push(T&& x){
    v.push_back(x); //auto accommodates move
}

//Pop Back Function, vector pop_back from C++ info page
template<typename T, class Container>
void Stack<T, Container>::pop(){
    v.pop_back();
}

//Top - check Last Input non-const, vector back() from C++ info page
template<typename T, class Container>
T& Stack<T, Container>::top(){
    return v.back();
}

//Top - check Last Input const, vector back() from C++ info page
template<typename T, class Container>
const T& Stack<T, Container>::top() const{
    return v.back();
}

//Print
template<typename T, class Container>
void Stack<T, Container>::print(std::ostream& os, char ofc) const{
    for(int i = 0; i < v.size(); ++i){
        os << v[i] << ofc;
    }
}

//Invoke Print to specified ostream
template<typename T, class Container>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a){
    //os << a.print();
    a.print(os);
    return os;
}

//== - check X
template<typename T, class Container>
bool operator==(const Stack<T>& a, const Stack <T>& b){
    if(a.size() != b.size()){  //finish
        //std::cout << "\npasta\n";
        return false;
    }

    Stack<T> lhs = a;
    Stack<T> rhs = b;

    for(int i = 0; i < a.size(); i++){
        if(lhs.top() != rhs.top()){
            //std::cout << "\ncheese\n";
            return false;
        }
        lhs.pop();
        rhs.pop();
    }
    //std::cout << "\nhashbrown\n";
    return true;
}

//!= - check X
template<typename T, class Container>
bool operator!=(const Stack<T>& a, const Stack<T>& b){
    return !(a == b);
}

//<= for each element - check
template<typename T, class Container>
bool operator<=(const Stack<T>& a, const Stack<T>& b){
    if(a.size() > b.size()){  //works this way instead of =
        //std::cout << "\npasta\n";
        return false;
    }

    Stack<T> lhs = a;
    Stack<T> rhs = b;

    for(int i = 0; i < a.size(); i++){
        if(lhs.top() > rhs.top()){
            //std::cout << "\ncheese\n";
            return false;
        }
        lhs.pop();
        rhs.pop();
    }
    //std::cout << "\nhashbrown\n";
    return true;
}