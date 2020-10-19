// Now in this code if we are aaccessing the function then we wont have name but instead we will print the 
// address in binx.asm file
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>
using namespace std ;


string Find_opcode_reverse(string instruction) {

     if(instruction == "100000")
        return "add" ;

     else if(instruction == "100001")
        return "addu";

     else if(instruction == "001000")
        return "addi" ;

     else if(instruction == "100100")
        return "and" ;

     else if(instruction == "001100")
        return "andi" ;

     else if(instruction == "011010")
        return "div";

     else if(instruction == "011011")
        return "divu"  ;

     else if(instruction == "011000")
        return "mult" ;

     else if(instruction == "100011")
        return "subu" ;

     else if(instruction == "100010")
        return "sub" ;

     else if(instruction == "100111")
        return "nor" ;

     else if(instruction == "100101")
        return "or" ;

     else if(instruction == "001101")
        return "ori";

     else if(instruction == "000000")
        return "sll" ;

     else if(instruction == "000010")
        return "srl";

     else if(instruction == "101010")
        return "slt" ;

     else if(instruction == "001010")
        return "slti" ;

     else if(instruction == "000100")
        return "beq" ;

     else if(instruction == "000101")
        return  "bne";

     else if(instruction == "000010")
        return  "j";

     else if(instruction == "000011")
        return "jal" ;

     else if(instruction == "001000")
        return "jr" ;

     else if(instruction == "010000")
        return "mfhi" ;

     else if(instruction == "010010")
        return "mflo" ;

     else if(instruction == "101011")
        return "sw" ;

     else if(instruction == "100011")
        return "lw" ;

    return "NULL" ;
}
// above gives correct funct 

string register_name(string register_code){
    if(register_code ==  "00000")
        return "$zero";

    else if(register_code == "00010" )
        return "$v0" ;

    else if(register_code == "00011" )
        return "$v1" ;

    else if(register_code ==  "00100" )
        return "$a0";

    else if(register_code == "00101")
        return "$a1" ;

    else if(register_code == "00110")
        return "$a2" ;

    else if(register_code ==  "00111")
        return "$a2" ;

    else if(register_code == "01000" )
        return "$t0" ;

    else if(register_code == "01001" )
        return  "$t1";

    else if(register_code == "01010" )
        return "$t2" ;

    else if(register_code == "01011")
        return  "$t3" ;

    else if(register_code == "01100" )
        return  "$t4";

    else if(register_code == "01101" )
        return "$t5" ;

    else if(register_code == "01110" )
        return  "$t6";

    else if(register_code ==  "01111")
        return "$t7" ;

    else if(register_code == "10000" )
        return "$s0" ;

    else if(register_code ==  "10001")
        return "$s1" ;

    else if(register_code ==  "10010")
        return  "$s2";

    else if(register_code == "10011" )
        return "$s3" ;

    else if(register_code ==  "10100")
        return "$s4" ;

    else if(register_code == "10101")
        return  "$s5";

    else if(register_code == "10110")
        return  "$s6";

    else if(register_code == "10111")
        return "$s7" ;

    else if(register_code == "11000")
        return "$t8" ;

    else if(register_code == "11001" )
        return  "$t9";

    else if(register_code == "11100" )
        return  "$gp";

    else if(register_code =="11101")
        return "$sp" ;

    else if(register_code == "11110")
        return "$fp" ;

    else if(register_code == "11111")
        return "$ra" ;

    return "NULL" ;
}
// above returns register name based on register code


string BTD_SA (string str,int leng){
    int i = leng - 1 ; 
    int mul = 1 ;
    int ans = 0 ;
    for (;i>0;i--){
        if (str[i] == '1')
            ans += mul ;
        mul *= 2 ;
    }
    if (str[0] == '1')
        ans = (-1)*ans ;
   return to_string(ans) ;
}
int main (void){
    string sub_folder = "sample_data/";
    string filename;
    cout << "Enter the name of the txt file without extension (i.e prog1bin): " ;
    cin >> filename ;

    ofstream fout;
    ifstream fin;

    string input_file ;
    input_file = sub_folder + filename + ".txt";
    cout << input_file << endl ;

    fin.open(input_file.c_str());
    string output_file ;
    output_file = sub_folder + "bin" + filename.substr(4,1) + ".asm" ;
    cout << output_file << endl ;
    fout.open(output_file.c_str());
    if (fin.is_open())
        cout << "fin is open" << endl;

    else
        cout << "fin is not open" << endl;

    if (fout.is_open())
        cout << "fout is in" << output_file << endl ;

    else
        cout << "No fout" ;

    string code_bina ;
    while (fin >> code_bina){
        if (code_bina.length() != 32)
            continue ;
        if (code_bina.substr(0,6) == "000000"){
            string instructio  = "" ;
            string funct_ = Find_opcode_reverse(code_bina.substr(26,6));
            if (funct_ == "addi")
                funct_ = "jr" ;
            instructio += (funct_ + " ") ;
            
            if (funct_ == "jr"){
                string reg_rs  = register_name(code_bina.substr(6,5)) ;
                instructio += reg_rs ;
            }

            else if (funct_ == "mfhi" || funct_ == "mflo"){
                string reg_rd = register_name(code_bina.substr(16,5)) ;
                instructio += reg_rd ;
            }
            else if (funct_ == "div" || funct_ == "mult"){
                string reg_rs  = register_name(code_bina.substr(6,5)) ;
                instructio += (reg_rs + ", ");
                string reg_rt  = register_name(code_bina.substr(11,5)) ;
                instructio += reg_rt;
            }

            else if (funct_ == "sll" || funct_ == "srl"){
                string reg_rd  = register_name(code_bina.substr(16,5)) ;
                instructio += (reg_rd + ", ");
                string reg_rt  = register_name(code_bina.substr(11,5)) ;
                instructio += (reg_rt + ", ");
                string shamt_dec = BTD_SA (code_bina.substr(21,5),5) ;
                instructio += shamt_dec ;
            }

            else {
                string reg_rd  = register_name(code_bina.substr(16,5)) ;
                instructio += (reg_rd + ", ");
                string reg_rs  = register_name(code_bina.substr(6,5)) ;
                instructio += (reg_rs + ", ");
                string reg_rt  = register_name(code_bina.substr(11,5)) ;
                instructio += reg_rt ;

            }
            fout << instructio << endl ;
        }
        
        else if (Find_opcode_reverse(code_bina.substr(0,6)) == "srl"  || Find_opcode_reverse(code_bina.substr(0,6)) == "jal" ){
            string funct_ = Find_opcode_reverse(code_bina.substr(0,6)) ;
            if (funct_ == "srl")
                funct_ = "j" ;
            string instructio  = "" ;
            instructio += (funct_ + " ") ;
            instructio += "Function at 26-bit address: ";
            instructio += code_bina.substr(6,26) ;

            fout << instructio << endl ;
        }

        else if (Find_opcode_reverse(code_bina.substr(0,6)) == "beq"  || Find_opcode_reverse(code_bina.substr(0,6)) == "bne" ){
            string instructio  = "" ;
            string funct_ = Find_opcode_reverse(code_bina.substr(0,6));
            instructio += (funct_ + " ") ;
            string reg_rs  = register_name(code_bina.substr(6,5)) ;
            instructio += (reg_rs + ", ");
            string reg_rt  = register_name(code_bina.substr(11,5)) ;
            instructio += (reg_rt + ", ") ;
            
            instructio += "Function at 16-bit address: ";
            instructio += code_bina.substr(16,16) ;

            fout << instructio << endl ;
        }

        else if (Find_opcode_reverse(code_bina.substr(0,6)) == "subu"  || Find_opcode_reverse(code_bina.substr(0,6)) == "sw" ){
            string funct_ = Find_opcode_reverse(code_bina.substr(0,6)) ;
            if (Find_opcode_reverse(code_bina.substr(0,6)) == "subu")
                funct_ = "lw" ;
            string instructio  = "" ;
            instructio += (funct_ + " ") ;
            string reg_rt  = register_name(code_bina.substr(11,5)) ;
            instructio += (reg_rt + ", ") ;

            string imm = BTD_SA(code_bina.substr(16,16),16) ;
            instructio += (imm + "(") ;
            string reg_rs  = register_name(code_bina.substr(6,5)) ;
            instructio += (reg_rs + ")");
            fout << instructio << endl ;


        }

        else {
            string funct_ = Find_opcode_reverse(code_bina.substr(0,6)) ;
            string instructio  = "" ;
            instructio += (funct_ + " ") ;
            string reg_rt  = register_name(code_bina.substr(11,5)) ;
            instructio += (reg_rt + ", ") ;
            string reg_rs  = register_name(code_bina.substr(6,5)) ;
            instructio += (reg_rs + ", ");
            string imm = BTD_SA(code_bina.substr(16,16),16) ;
            instructio += imm ;

            fout << instructio << endl ;      

        }


    }


    return 0 ;
}