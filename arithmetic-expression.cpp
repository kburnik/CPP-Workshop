/*
    Task: Arithmetic Expression
    
          Calculate value of an nonnegative integer arithmetic expression given
          as a string and supporting + * / % (- excluded for simplicity)
          Ignore all charachters which ar not a digit or an operation (+ * / %)
          also detect division by zero and invalid or empty expression!
             
    Solution: Kristijan Burnik, Udruga informatičara Božo Težak
              GMail: kristijanburnik
              
    Complexity: Three passes
        Step 2: o(N) - Linear : where N denotes length of string
        Step 3: o(N~) - Linear : where N~ denotes number of tokens
        Step 4: o(N~) - Linear : where N~ denotes number of tokens
                        (rotating of tokens back/forth is o(1) )
    
    Strucutres: String, Vector & Double ended Queue
    
    Date: 31.01.2012.
    
    ----
    
    Test input  : 13 + 22 * 5 / 11 + 92 + 3%2
    Test output : 116 
                 (exit code 0)

    Test input  : 
    Test output : Empty expression! 
                 (exit code -1)
    
    Test input  :  7 + + 5
    Test output : Invalid expression! 
                 (exit code -2)
        
    Test input  : 7 / 0 + 5 
    Test output : Division by zero! 
                 (exit code -3)
    
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

typedef long long int llint;
typedef pair <int,string> token;
#define Type first
#define Value second
#define mp make_pair

const int NUMBER = 0, OPERATION = 1, OTHER = 2;

int get_type(char c) {
    if  (c >= '0' && c <= '9') return NUMBER;
    if (c == '*' || c == '+' || c == '/' || c == '%' ) return OPERATION;
    if (c == '~') return OPERATION; // sentinel
    return OTHER;    
}

// when operator a has greater priority than b
bool greater_priority(token a, token b) {
    return (( a.Value=="*" || a.Value=="/" || a.Value=="%" ) && b.Value == "+");
}

// integer to string conversion
string to_string(llint x) {
    string s;
    while (x > 0) {
        s = (char)((x%10)+'0') + s;
        x/=10;
    }
    return s;
}

// string to integer conversion
llint to_int(string s) {
    llint x = 0;
    for (int i = 0; i < s.size() ; i++ ) {
         x = x*10 + ((llint)(s[i]-'0'));
    }
    return x;
}

int main(void) {

////////////////////////////////////////////////////////////////////////////////
// STEP 1: input arithmetic expression: NON-NEG integers and + * / % operations
////////////////////////////////////////////////////////////////////////////////

    string s;
    getline(cin,s);

////////////////////////////////////////////////////////////////////////////////
// STEP 2: tokenize the expression
////////////////////////////////////////////////////////////////////////////////

    // add sentinel operation ~
    s += "~";    
    
    bool found_numbers = false;
    vector < token > tokens;
    string buffer;
    for (int i = 0; i  < s.size(); i++) {
        char c = s[i];
        int type = get_type(c);
        switch(type) {
            case NUMBER:
                buffer += c;
                found_numbers = true;
            break;
            case OPERATION:
                if (!found_numbers) {
                    cout << "Empty expression!" << endl;
                    exit(-1);    
                }
                if (buffer.size() > 0) {
                    tokens.push_back(mp(NUMBER,buffer));
                    buffer = "";
                }
                tokens.push_back(mp(OPERATION,s.substr(i,1)));
                    
            break;   
        }
        int ts = tokens.size();
        if (ts > 1 && tokens[ts-1].Type == tokens[ts-2].Type) {
            cout << "Invalid expression!" << endl;
            exit(-2);    
        }
    }
     
     // remove the sentinel operation ~
     tokens.pop_back();
  
////////////////////////////////////////////////////////////////////////////////
// STEP 3: Derive infix to sufix notation with priority handling!
////////////////////////////////////////////////////////////////////////////////

    deque <token> calc,ops;
    string last_op;
    for (int i = 0; i < tokens.size(); i++) {
            calc.push_back(tokens[i]);
            int cs = calc.size();
            
            switch (tokens[i].Type) {
                case NUMBER:
                    if (last_op != "") {
                        swap(calc[cs-1],calc[cs-2]);
                        last_op = "";
                    }
                break;
                case OPERATION:
                    last_op = tokens[i].Value;
                    ops.push_back(tokens[i]);
                break;    
            }
            
            int os = ops.size();
            
            // handle priority if needed
            if ( os > 1 && tokens[i].Type == NUMBER ) {
                if (greater_priority( ops[os-1], ops[os-2] ) ) {
                    swap( calc[cs-3] , calc[cs-2]);                        
                    swap( calc[cs-2] , calc[cs-1]);
                    swap( ops[os-1], ops[os-2] );
                }    
            }
    }


////////////////////////////////////////////////////////////////////////////////
// STEP 4: Calculate the expression from the sufix denoted tokens
////////////////////////////////////////////////////////////////////////////////

    token a, b, op, result = mp(NUMBER,"0");
    int atback = 0;
    while (calc.size() > 1) {
         
        // obtain first three tokens ( hope for A B OP respectivley )
        a = calc[0]; // first operand
        b = calc[1]; // second operand
        op = calc[2]; // operation
        
        // Check if A, B and OP correspond to their expected token type:
        // Priority handling: keep waiting operands at end of dequeue if needed
        if (op.Type != OPERATION) {
            // move the waiting operand to end of dequeue, and skip this round 
            calc.push_back(a);
            calc.pop_front();
            
            // keep track of the waiting operands: will restore them after calc
            atback++;
            
        } else {
           // ready for calculating result, remove the front A, B and OP
            calc.pop_front(); calc.pop_front(); calc.pop_front();

            // the essence of the calculation is done here
            if (op.Value == "*") {
                result.Value = to_string( to_int(a.Value) * to_int(b.Value) );
            } else if (op.Value == "+") {
                result.Value = to_string( to_int(a.Value) + to_int(b.Value) );
            } else {
                // check for division by zero
                if (to_int(b.Value) == 0) {
                    cout << "Division by zero!" << endl;
                    exit(-3); 
                }
                if (op.Value == "/") {
                    result.Value = to_string( to_int(a.Value) / to_int(b.Value) );
                } else if (op.Value == "%") {
                    result.Value = to_string( to_int(a.Value) % to_int(b.Value) );                
                }
        }
            
            // insert the result to its place for rest of the calculation
            calc.push_front(result);
            
            // restore the waiting operands from back to front
            while (atback-- > 0) {
                    calc.push_front(calc.back()); 
                    calc.pop_back();
            }
            atback = 0;
        
        }
        
    }
    
////////////////////////////////////////////////////////////////////////////////
// STEP 5: output result   
////////////////////////////////////////////////////////////////////////////////

    cout << calc.front().Value << endl;

    return 0;
}