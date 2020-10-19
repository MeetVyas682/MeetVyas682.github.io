// To comment in asm file, it has to be of type "# comment "
// Follow the commenting syntax.
// For negative number binary representation, we using singned magnitude method
// i.e left most bit is 1 if negative and 0 if positve.

// We first scan the .asm file to find the functions in the file then we push the function in vector
// Now if the function is at xth position then we change x to binary code of desired bits and that will be the function address



#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std ;

int Type_func(string str){
    // If I then 0, J then 1, R then 2
    if (str == "addi")
        return 0;

    else if (str == "subi")
        return 0;

    else if (str == "multi")
        return 0;

    else if (str == "andi")
        return 0;

    else if (str == "slti")
        return 0;

    else if (str == "ori")
        return 0;

    else if (str == "nori")
        return 0;

    else if (str == "lw")
        return 0;

    else if (str == "sw")
        return 0;

    else if (str == "beq")
        return 0;

    else if (str == "bne")
        return 0;

    else if (str == "ble")
        return 0;

    else if (str == "bgt")
        return 0;

    else if (str == "bge")
        return 0;

    else if (str == "j")
        return 1;

    else if (str == "jal")
        return 1;

    else if (str == "add")
        return 2;

    else if (str == "addu")
        return 2;

    else if (str == "sub")
        return 2;

    else if (str == "subu")
        return 2;

    else if (str == "mult")
        return 2;

    else if (str == "multu")
        return 2;

    else if (str == "and")
        return 2;

    else if (str == "or")
        return 2;

    else if (str == "nor")
        return 2;

    else if (str == "sll")
        return 2;

    else if (str == "srl")
        return 2;

    else if (str == "slt")
        return 2;

    else if (str == "jr")
        return 2;

    else if (str == "div")
        return 2;

    else if (str == "mfhi")
        return 2;

    else if (str == "mflo")
        return 2;

    else                                                    // if str == jr
        return 2;
}
// Type function works ;

string Find_opcode(string instruction) {

     if(instruction == "add")
        return "100000" ;

     else if(instruction == "addu")
        return "100001" ;

     else if(instruction == "addi")
        return "001000" ;

     else if(instruction == "and")
        return "100100" ;

     else if(instruction == "andi")
        return "001100" ;

     else if(instruction == "div")
        return "011010" ;

     else if(instruction == "divu")
        return "011011" ;

     else if(instruction == "mult")
        return "011000" ;

     else if(instruction == "subu")
        return "100011" ;

     else if(instruction == "sub")
        return "100010" ;

     else if(instruction == "nor")
        return "100111" ;

     else if(instruction == "or")
        return "100101" ;

     else if(instruction == "ori")
        return "001101" ;

     else if(instruction == "sll")
        return "000000" ;

     else if(instruction == "srl")
        return "000010" ;

     else if(instruction == "slt")
        return "101010" ;

     else if(instruction == "slti")
        return "001010" ;

     else if(instruction == "beq")
        return "000100" ;

     else if(instruction == "bne")
        return "000101" ;

     else if(instruction == "j")
        return "000010" ;

     else if(instruction == "jal")
        return "000011" ;

     else if(instruction == "jr")
        return "001000" ;

     else if(instruction == "mfhi")
        return "010000" ;

     else if(instruction == "mflo")
        return "010010" ;

     else if(instruction == "sw")
        return "101011" ;

     else if(instruction == "lw")
        return "100011" ;

    return "NULL" ;
}
// Find_opcode works


string register_code(string register_name){
    if(register_name == "$zero" || register_name == "$zero,")
        return "00000";

    else if(register_name == "$v0" || register_name == "$v0,")
        return "00010" ;

    else if(register_name == "$v1" || register_name == "$v1,")
        return "00011" ;

    else if(register_name == "$a0" || register_name == "$a0,")
        return "00100" ;

    else if(register_name == "$a1" || register_name == "$a1,")
        return "00101" ;

    else if(register_name == "$a2" || register_name == "$a2,")
        return "00110" ;

    else if(register_name == "$a2" || register_name == "$a2,")
        return "00111" ;

    else if(register_name == "$t0" || register_name == "$t0,")
        return "01000" ;

    else if(register_name == "$t1" || register_name == "$t1,")
        return "01001" ;

    else if(register_name == "$t2" || register_name == "$t2,")
        return "01010" ;

    else if(register_name == "$t3" || register_name == "$t3," )
        return "01011" ;

    else if(register_name == "$t4" || register_name == "$t4,")
        return "01100" ;

    else if(register_name == "$t5" || register_name == "$t5,")
        return "01101" ;

    else if(register_name == "$t6" || register_name == "$t6," )
        return "01110" ;

    else if(register_name == "$t7" || register_name == "$t7,")
        return "01111" ;

    else if(register_name == "$s0" || register_name == "$s0,")
        return "10000" ;

    else if(register_name == "$s1" || register_name == "$s1,")
        return "10001" ;

    else if(register_name == "$s2" || register_name == "$s2,")
        return "10010" ;

    else if(register_name == "$s3" || register_name == "$s3,")
        return "10011" ;

    else if(register_name == "$s4" || register_name == "$s4,")
        return "10100" ;

    else if(register_name == "$s5" || register_name == "$s5,")
        return "10101" ;

    else if(register_name == "$s6" || register_name == "$s6,")
        return "10110" ;

    else if(register_name == "$s7" || register_name == "$s7,")
        return "10111" ;

    else if(register_name == "$t8" || register_name == "$t8,")
        return "11000" ;

    else if(register_name == "$t9" || register_name == "$t9,")
        return "11001" ;

    else if(register_name == "$gp" || register_name == "$gp,")
        return "11100" ;

    else if(register_name == "$sp" || register_name == "$sp," )
        return "11101" ;

    else if(register_name == "$fp" || register_name == "$fp,")
        return "11110" ;

    else if(register_name == "$ra" || register_name == "$ra,")
        return "11111" ;

    return "NULL" ;
}
// register_code works properly

string to_hexa_dec (string str){
    string ans = "" ;
    for (int i = 0 ; i<32 ; i = i+4){
        string temp = "" ;
        temp.push_back(str[i+0]);
        temp.push_back(str[i+1]);
        temp.push_back(str[i+2]);
        temp.push_back(str[i+3]);
        // cout << temp << endl;
        if(temp == "0000")
            ans.push_back('0') ;
        if(temp == "0001")
            ans.push_back('1') ;
        if(temp == "0010")
            ans.push_back('2') ;
        if(temp == "0011")
            ans.push_back('3') ;
        if(temp == "0100")
            ans.push_back('4') ;
        if(temp == "0101")
            ans.push_back('5') ;
        if(temp == "0110")
            ans.push_back('6') ;
        if(temp == "0111")
            ans.push_back('7') ;
        if(temp == "1000")
            ans.push_back('8') ;
        if(temp == "1001")
            ans.push_back('9') ;
        if(temp == "1010")
            ans.push_back('a') ;
        if(temp == "1011")
            ans.push_back('b') ;
        if(temp == "1100")
            ans.push_back('c') ;
        if(temp == "1101")
            ans.push_back('d') ;
        if(temp == "1110")
            ans.push_back('e') ;
        if(temp == "1111")
            ans.push_back('f') ;

    }

    return ans ;
}
// conversion to hexadecimal works

string bit_generate (int Number, int num_bits){

    string tem_p ;
    while (Number >0){
        int n = Number%2 ;
        Number = Number/2 ;
        tem_p = to_string(n) + tem_p ;
    }
    int len = tem_p.length() ;
  
    while (len < num_bits) {
        tem_p = "0" + tem_p ;
        len++ ;
    }
    
    return tem_p ;
}
// The above function works , input number and number of desired bits

int FInd_in_vc (string reg_name,vector <string> procedures){
    int i = 0 ;
    for (;i<procedures.size();i++){
        if (reg_name == procedures[i])
            break ;
    }

    return i ;
}

int main (void){
    string sub_folder = "sample_data/";
    string filename;
    cout << "Enter the name of the asm file without extension (i.e prog1): " ;
    cin >> filename ;

    ofstream fout;
    ifstream fin;

    string input_file ;
    input_file = sub_folder + filename + ".asm";
    cout << input_file << endl ;
    fin.open(input_file.c_str());
    string output_file ;
    output_file = sub_folder + filename + "bin.txt" ;
    fout.open(output_file.c_str());
    if (fin.is_open())
        cout << "fin is open" << endl;

    else
        cout << "fin is not open" << endl;

    if (fout.is_open())
        cout << "fout is in " << output_file << endl ;

    else
        cout << "No fout" ;


     // The files are open
     // Input file is fin
     // Output file is fout

    string word ;                      // Word will work as an extracting variable. It will extract file word by word
    string func_finder ;
    vector <string> procedures ;        // vector to store the procedures

    while (fin >> func_finder){
       if (func_finder[func_finder.length()-1] == ':'){
            procedures.push_back(func_finder) ;
        }
    }
    fin.close() ;
    fin.open(input_file.c_str());
    while (fin >> word){
        // cout << word << endl ;
        if (word[word.length()-1] == ':'){
        }
        else if (word[0] == '#'){
            string str ;
            getline(fin,str) ;
        }
        else {
            if (Type_func(word) == 2) {             // R type
                string op = "000000" ;
                string rs = "00000" ;
                string rt = "00000" ;
                string rd = "00000" ;
                string shamt = "00000" ;
                string func_code ;
                string instruction = word + " ";

                func_code = Find_opcode(word) ;
                if (word == "jr") {
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    rs = register_code(reg_1) ;
                }
                else  if (word == "mfhi" || word == "mflo"){
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    rd = register_code(reg_1) ;
                }
                else if (word == "div" || word == "multu" || word == "mult"){
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    string reg_2 ;
                    fin >> reg_2 ;
                    instruction += (reg_2+ " " );
                    rs = register_code(reg_1) ;
                    rt = register_code(reg_2) ;
                }

                else if (word == "sll" || word == "srl"){
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    string reg_2 ;
                    fin >> reg_2 ;
                    instruction += (reg_2 + " " );
                    rd = register_code(reg_1) ;
                    rt = register_code(reg_2) ;
                    string reg_3 ;
                    fin >> reg_3 ;
                    instruction += (reg_3 + " " );
                    int num_shamt = stoi(reg_3) ;
                    shamt = bit_generate(num_shamt,5) ;
                }

                else {
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    string reg_2 ;
                    fin >> reg_2 ;
                    instruction += (reg_2 + " " );
                    rd = register_code(reg_1) ;
                    rs = register_code(reg_2) ;
                    string reg_3 ;
                    fin >> reg_3 ;
                    instruction += (reg_3 + " " );
                    rt = register_code(reg_3) ;                  
                }

                string hexa_code = to_hexa_dec(op + rs + rt + rd + shamt + func_code) ;
                fout << op << rs << rt << rd << shamt << func_code << " (" << hexa_code << ", " << instruction << ")\n" ;               

            }

            else if (Type_func(word) == 0){
                string op  ;
                string rs  ;
                string rt  ;
                string add_ress ;
                string instruction = word + " ";
                op = Find_opcode(word) ;
                if (word == "beq" || word == "bne"){
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    string reg_2 ;
                    fin >> reg_2 ;
                    instruction += (reg_2+ " " );
                    rs = register_code(reg_1) ;
                    rt = register_code(reg_2) ;
                    // add_ress for 
                    string reg_3 ;
                    fin >> reg_3 ;
                    instruction += (reg_3 + " " );
                    reg_3.push_back(':') ;
                    int function_in_vector = FInd_in_vc (reg_3,procedures) ;
                    add_ress = bit_generate(function_in_vector,16) ;
                }
                // cout << op << " " << rs << " " << rt << " " << add_ress ;

                else if (word == "lw" || word == "sw"){
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    rt = register_code(reg_1) ;
                    string reg_2 ;
                    fin >> reg_2 ;
                    instruction += (reg_2+ " " );

                    string reg_3 ;  // integer offset
                    int i = 0 ;
                    while (reg_2[i] != '('){
                        reg_3.push_back(reg_2[i]) ;
                        i++ ;                                     
                    }
                    string reg_4 ;  // regiser inside brackets
                    reg_4.push_back(reg_2[i+1]) ;
                    reg_4.push_back(reg_2[i+2]) ;
                    reg_4.push_back(reg_2[i+3]) ;
                    // cout << reg_4 << endl ;
                    int before_brac = stoi(reg_3) ;
                    add_ress = bit_generate(before_brac,16) ;
                    rs = register_code(reg_4) ;
                    // cout << op << " " << rs << " " << rt << " " << add_ress << " " << instruction;
                }

                else {
                    string reg_1 ;
                    fin >> reg_1 ;
                    instruction += (reg_1 + " " );
                    rt = register_code(reg_1) ;

                    string reg_2 ;
                    fin >> reg_2 ;
                    instruction += (reg_2 + " " );
                    rs = register_code(reg_2) ;

                    string reg_3 ;
                    fin >> reg_3 ;
                    instruction += (reg_3 + " " );
                    if (reg_3[0] == '-'){
                        string n_q = reg_3.substr(1,(reg_3.length()-1)) ;
                        int int_reg_3 = stoi(n_q) ;
                        // fout << int_reg_3 << endl;
                        add_ress = bit_generate(int_reg_3,15) ; 
                        add_ress = "1" + add_ress ;
                    }
                    else {
                        int int_reg_3 = stoi(reg_3) ;
                        add_ress = bit_generate(int_reg_3,16) ; }
                    // cout << op << " " << rs << " " << rt << " " << add_ress << " " << instruction;
                }

                string hexa_code = to_hexa_dec(op + rs + rt + add_ress) ;
                fout << op <<  rs << rt << add_ress << " (" << hexa_code << ", " << instruction << ")\n" ;
            }

            else if (Type_func(word) == 1){
                string op  ;
                string add_ress ;
                string instruction = word + " ";
                op = Find_opcode(word) ;

                string reg_3 ;
                fin >> reg_3 ;
                instruction += (reg_3 + " " );
                reg_3.push_back(':') ;
                int function_in_vector = FInd_in_vc (reg_3,procedures) ;
                add_ress = bit_generate(function_in_vector,26) ;
                // cout << op << " " << add_ress << " " ;
                // cout << instruction << endl ;
                string hexa_code = to_hexa_dec(op + add_ress) ;
                fout << op << add_ress << " (" << hexa_code << ", " << instruction << ")\n" ;
            }
        }

    }

    fin.close();
    fout.close();
    return 0;

    // cout << bit_generate(16, 9) ;

}
