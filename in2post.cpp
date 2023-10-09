#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "stack.h"

using namespace std;

bool isOperator(string val){
    if(val == "*" || val == "/" || val == "+" || val == "-"){
        return true;
    }
    return false;
}

//check if all values in expressions are numbers or operators
bool hasVariables(vector<string> post){ 
    for(int i = 0; i < post.size(); i++){
        if((post[i] < "0" || post[i] > "9") && !isOperator(post[i]) && post[i] != "(" && post[i] != ")"){
            //cout << "hola\n";
            return true;    //variables
        }
        //cout << post[i] << endl;
    }
    //cout << "bye\n";
    return false;    //no variables
}

//should there be if * before / kind of thing
bool precedence(string val, string top){
    if(val == "/" || val == "*"){
        if(top == "/" || top == "*"){
            return true;
        }
    }
    else if(val == "+" || val == "-"){
        if(isOperator(top)){
            return true;
        }
    }
    return false;
    
    /*
    if(val == "/" || val == "*")
    {
        return 2;
    }
    */
}

/*
bool isOperand(string val){
    if((val >= "a1" && val <= "zz") || (val >= "0" && val <= "9")
    || (val >= "a" && val <= "z")){
        return true;
    }
    return false;
}
*/

void print(vector<string> post){
    for(int i = 0; i < post.size(); i++){
        cout << post[i] << " ";
    }
    cout << endl;
}

bool errorInfix(vector<string> exp){
    //cout << "everywhere\n";
    bool check = false;
    for(int i = 0; i < exp.size() - 1; i++){ //not sure why size - 1...
        //cout << exp[i] << endl;
        //cout << "everything \n";
        if((!isOperator(exp[i]) && exp[i] != "(" && exp[i] != ")") || isOperator(exp[i])){
            if(isOperator(exp[i])){ //check 2 operators in a row or at beginning/end
                if(i != exp.size()-1 && isOperator(exp[i+1])){
                    cout << "\nConsecutive Opcodes: " << exp[i] << " " << exp[i+1] << endl; //is this correct to say? Take out beginning and end condition?
                    check = true;
                }
            }
            //cout << "all at once \n";
            if(!isOperator(exp[i]) && exp[i] != "(" && exp[i] != ")"){  //check 2 operands in a row or near ()
                if((!isOperator(exp[i+1]) && exp[i+1] != ")"  && exp[i+1] != "(")){
                    cout << "\nConsecutive Numbers: " << exp[i] << " " << exp[i+1] << endl;
                    /*if(exp[i] < "0" || exp[i] > "9"){
                        cout << "\nConsecutive Numbers: " << exp[i] << " " << exp[i+1] << endl;
                    }*/
                    check = true;
                }
            }
        }
        if(!isOperator(exp[i]) && (i+1) != 0 && exp[i+1] == "(" && exp[i] != ")" && exp[i] != "("){
            cout << "\nNumber (: " << exp[i] << " (\n";
            return true;
        }
        if((exp[i] == "(" || isOperator(exp[i])) && exp[i+1] == ")"){
            cout << "\nError: cannot have an opcode or ( before )\n";
            return true;
        }
    }
    //cout << "here\n";
    if(exp.size() > 2 && check != true && isOperator(exp[exp.size()-1]) || exp[exp.size()-1] == "("){ //check ( or if last input is operator
        cout << "\nError: Operator [" << exp[exp.size() - 1] << "] has only one operand:\n";
        return true;
    }
    if(exp.size() > 2 && check != true && isOperator(exp[0]) || exp[0] == ")"){ //check ) or if first input is operator
        cout << "\nError: Operator [" << exp[0] << "] has only one operand:\n";
        return true;
    }
    //cout << "there\n";
    //cout << "hmm...\n";
    //cout << check << endl;
    return check;
}

/*
bool errorPost(vector<string> exp){
    for(int i = 0; i < exp.size(); i++){
        if(i == exp.size() - 1 && (isOperator(exp[i]) || exp[i] == "(")){  //check if ( is last input
            return true;
        }
        /*else if(exp.size() < 2 && isOperator(exp[i])){ //check operator can operate on enough operands in stack
            return true;
        }
    }
}*/

vector<string> convertPost(vector<string> exp){
    cop4530::Stack<string> stack;
    vector<string> post;
    //bool errorCheck = false;
    
    //cout << "vanilla\n";

    //Error check - moved to main
    /*if(error(exp)){
        cout << "red velvet\n";
        //cout << "error" << endl;
        return exp;
    }*/

    for(int i = 0; i < exp.size(); i++){
        //cout << "chocolate \n";
        if(isOperator(exp[i]) || exp[i] == "("){    //operator/prec
            //cout << "carrot\n";
            //cout << "hi\n";
            while(!stack.empty() && (precedence(exp[i], stack.top()))){
                //cout << "strawberry\n";
                post.push_back(stack.top());
                stack.pop();
            }
            stack.push(exp[i]);
            //cout << "cheesecake \n";
        }
        else if(exp[i] == ")"){     //end prec
            //cout << "tres leches\n";
            while(!stack.empty() && stack.top() != "("){
                //cout << "raspberry \n";
                post.push_back(stack.top());
                //cout << "lemon \n";
                stack.pop();
                //cout << "banana \n";
            }
            //cout << "turtle \n";
            if(stack.empty()){  //parenthese error )
                //cout << "caramel\n";
                //errorCheck = true;
                post.clear();
                post.push_back("\nError: cannot find a matching (\n");
                post.push_back("Found in input:\n");
                print(post);
                print(exp);
                cout << endl;
                return post;
            }
            stack.pop();    //pop (
            //cout << "white chocolate\n";
        }
        else{   //operand
            //cout << "brownie\n";
            post.push_back(exp[i]);
        }
    }

    //cout << "blueberry\n";

    while(!stack.empty()){
        if(stack.top() == "("){ //parenthese error (
            //errorCheck = true;
            post.clear();
            post.push_back("Error: failed conversion. Deck top=(\n");
            post.push_back("Found in input:\n");
            print(post);
            print(exp);
            cout << endl;
            return post;
        }
        post.push_back(stack.top());
        stack.pop();
    }
    //cout << "birthday\n";
    return post;
}

double evalPost(vector<string> post){
    //set precision, cop 3014 style
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);

    cop4530::Stack<double> stack;
    double result = 0;

    //cout << "hi\n";

    bool variableCheck = hasVariables(post);
    //cout << "There are variables: " << variableCheck << endl;;

    for(int i = 0; i < post.size(); i++){
        //cout << "hello\n";
        if(isOperator(post[i])){
            /*if(stack.size() < 2){ //check operator can operate on enough operands in stack
                cout << "Error: cannot have an opcode";
                return -1;
            }*/

            if(!variableCheck){
                //cout << "salud\n";
                double a = stack.top();
                stack.pop();

                double b = stack.top();
                stack.pop();
                
                //check which operator, no switch
                if(post[i] == "+"){
                    stack.push(a+b);
                }
                else if(post[i] == "-"){
                    stack.push(b-a);
                }
                else if(post[i] == "*"){
                    stack.push(a*b);
                }
                else if(post[i] == "/"){
                    stack.push(b/a);
                }
            }
            /* If you can see this, I will say that I figured
               out how to put it back to infix if there are variables
               when this is not part of the assignment. I spent too
               long on this :(
            else{
                //cout << "pistachio\n";
                string c = stack.top();
                stack.pop();

                string d = stack.top();
                stack.pop();

                //check which operator, no switch
                if(post[i] == "+"){
                    string temp = d + "+" + c;
                    stack.push(temp);
                    cout << stack.top();
                }
                else if(post[i] == "-"){
                    string temp = d + "-" + c;
                    stack.push(temp);
                }
                else if(post[i] == "*"){
                    string temp = d + "-" + c;
                    stack.push(temp);
                }
                else if(post[i] == "/"){
                    string temp = d + "/" + c;
                    stack.push(temp);
                }
            }
            */
        }
        else{
            double operand = stod(post[i]);
            stack.push(operand);
        }
    }

    if(!variableCheck){
        //cout << "almond\n";
        result = stack.top();
        stack.pop();
        if(!stack.empty()){
            cout << "ERROR";
            return -1;
        }
        //cout << "walnut\n";
        return result;
    }
    /*
    else{
        cout << "peanut\n";
        result = stack.top();
        stack.pop();
        //print(post);
    }*/
    return -1; 
}

int main(int argc, char **argv){
    //set precision, cop 3014 style
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);

    vector<string> infix;
    vector<string> post;
    string input;
    string result;
    ifstream myFile;
    bool errorCheck = false;

    // check if there is more than one argument and use the second
    if(argc > 1){
        string arg1(argv[1]);
        //cout << arg1;
        myFile.open(arg1);
        //cout << "hi\n";
    }
    else if(argc == 1){
        cout << "Enter infix or exit: ";
        getline(cin, input);
        cout << endl;
        while(input != "no"){}\
            string word;
            stringstream ss(input);
            while(getline(ss, word, ' '))
            {
                if(word != "")
                infix.push_back(word);
            }
        //bool error = false;
        //cout << "fix\n";
        if(errorInfix(infix)){
            errorCheck = true;
            cout << "Found in input:\n" << input << endl;
        }
        else{
            //cout << "no\n";
            post = convertPost(infix);
            //cout << "Postfix expression: ";
            print(post);
        }

        if(!errorCheck){
            //cout << "\nEvaluate expression: ";
            //print(post);
            if(!hasVariables(post)){
                cout << evalPost(post) << endl;
            }
            else{
                //cout << "peek\n";
                print(post);
            }
        }
        infix.clear();
        post.clear();
        cout << "\nEnter infix or exit: ";
        getline(cin, input);
        cout << endl;
    }

    /*if(argc == 2){
      int cnt = atoi(argv[1]);
      //cout << cnt << endl;
    }*/

    //cout << "received";
    
    //parses through each line given by myFile and stores in input
    for(string input; getline(myFile, input);)
    {
        //cout << input << endl;;
        string word;
        stringstream ss(input);
        //each word is an operator/operand sep by spaces
        while(getline(ss, word, ' '))
        {
            if(word != "")
            infix.push_back(word);
        }
        //bool error = false;
        //cout << "fix\n";
        if(errorInfix(infix)){
            errorCheck = true;
            cout << "Found in input:\n" << input << endl;
        }
        else{
            //cout << "no\n";
            post = convertPost(infix);
            //cout << "Postfix expression: ";
            //print(post);
        }

        if(!errorCheck){
            //cout << "\nEvaluate expression: ";
            //print(post);
            if(!hasVariables(post)){
                cout << evalPost(post) << endl;
            }
            else{
                //cout << "peek\n";
                print(post);
            }
        }
        infix.clear();
        post.clear();
    }

    myFile.close();

}