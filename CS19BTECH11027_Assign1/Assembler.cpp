#include<bits/stdc++.h>
using namespace std;


unordered_map <string, char> format;            //to knkow the format
unordered_map <string, long long int> symbol_table; // to know the address of the label
unordered_map <string, string> register_number;     //to know the code for a register
unordered_map <string, string> opcode;              //to know the opcode of a instruction
unordered_map <string, string> bin_to_hex;          //to make the common case faster

string get_substr(string str, int low, int high)    // to get a substring
{
    string ans;
    for(int i=low;i<high;i++)
    {
        ans.push_back(str[i]);
    }
    int space = high-1;
    while(str[space] == ' ')            //remove the last spaces
    {
        ans.pop_back();
        space--;
    }
    return ans;
}



void initialise();      //to initialise the maps
string decToBinary(int n, int bit); //to conver from decimal to binary
string binary_to_hex(string instruct);  //to convert from binary to hex


int main()
{
    initialise();
    ifstream fin;
    ofstream fout;
    string line;

    string sub_folder = "sample_data/";
    string filename;
    cout<<"Enter the .asm file name (present in the sample_data): ";
    cin>>filename;
    sub_folder = sub_folder + filename;
    fin.open(sub_folder);

    int pos = filename.find(".");
    string outputfile = "sample_data/" + filename.substr(0,pos) + "bin.txt";
    cout<<"the output is in"<<outputfile<<"\n";
    fout.open(outputfile);

    while (fin) {

        getline(fin, line);

        if(line.find(":") == string::npos && line[0] != '#')            //it should not be a comment or label
        {
            if(line.length()>1)
            {
                string line_without_comment;
                if(line.find("#") != string::npos){         //to remove comments
                    int comment_pos = line.find("#");
                    line_without_comment = get_substr(line, 4, comment_pos);
                }
                else
                    line_without_comment = get_substr(line, 4, line.length());

                    // cout<<line_without_comment<<"\n";

                string oper;
                string instruction, hex_instruction;
                int j=4;
                while(line[j]!= ' ')
                {
                    oper.push_back(line[j]);
                    j++;
                }
                j++;
                if(format[oper] == 'R')     //if the format is R
                {
                    string op = "000000";
                    string rs = "00000";
                    string rt = "00000";
                    string rd = "00000";
                    string func;
                    string shamt = "00000";

                    if(oper == "mfhi" || oper == "mflo" || oper == "jr")        // they take only single register
                    {
                        string reg1;
                        while(line[j]!=' ')
                        {
                            reg1.push_back(line[j]);
                            j++;
                        }
                        // cout<<"!"<<reg1<<"!";
                        if(oper == "jr")
                            rs = register_number[reg1];
                        else
                            rd = register_number[reg1];
                    }
                    else if(oper == "div" || oper == "mult")            //they take two register
                    {
                        string reg1;
                        while(line[j]!=',')
                        {
                            reg1.push_back(line[j]);
                            j++;
                        }
                        rs = register_number[reg1];

                        j = j+2;
                        string reg2;
                        while(line[j]!=' ')
                        {
                            reg2.push_back(line[j]);
                            j++;
                        }
                        rt = register_number[reg2];

                    }
                    else                // for 3 register
                    {
                        string reg1;
                        while(line[j]!=',')
                        {
                            reg1.push_back(line[j]);
                            j++;
                        }
                        rd = register_number[reg1];

                        j = j+2;
                        string reg2;
                        while(line[j]!=',')
                        {
                            reg2.push_back(line[j]);
                            j++;
                        }
                        rs = register_number[reg2];
                        j+=2;
                        string reg3;
                        while(line[j]!=' ')
                        {
                            reg3.push_back(line[j]);
                            j++;
                        }
                        rt = register_number[reg3];

                        if(oper == "sll" || oper == "srl")      // last arguement is a number
                        {
                            int int_reg3 = stoi(reg3);
                            shamt = decToBinary(int_reg3, 4);
                            rt = register_number[reg2];
                            rs = "00000";
                        }
                    }
                    func = opcode[oper];

                    instruction = op + rs + rt + rd + shamt + func;         //forming the instruction
                    hex_instruction = binary_to_hex(instruction);           //converting to hex code
                    fout<<instruction<<"("<<hex_instruction<<","<<line_without_comment<<")"<<"\n";
                }
                else if(format[oper] == 'I')        //if format is I
                {
                    string op = opcode[oper];
                    string rs = "00000";
                    string rt = "00000";
                    string address;
                    if(oper == "lw" || oper == "sw")    //they have different formating of arguement like $s0, 32($s1)
                    {
                        string reg1;
                        while(line[j]!=',')
                        {
                            reg1.push_back(line[j]);
                            j++;
                        }
                        rt = register_number[reg1];
                        j+=2;

                        string reg2;
                        while(line[j]!='(')
                        {
                            reg2.push_back(line[j]);
                            j++;
                        }
                        // cout<<reg2<<"!";
                        int int_reg2 = stoi(reg2);
                        address = decToBinary(int_reg2, 15);
                        j++;

                        string reg3;
                        while(line[j]!=')')
                        {
                            reg3.push_back(line[j]);
                            j++;
                        }
                        rs = register_number[reg3];
                    }
                    else            //else case
                    {
                        string reg1;
                        while(line[j]!=',')
                        {
                            reg1.push_back(line[j]);
                            j++;
                        }

                        j = j+2;
                        string reg2;
                        while(line[j]!=',')
                        {
                            reg2.push_back(line[j]);
                            j++;
                        }

                        j+=2;
                        string offset;
                        while(line[j]!=' ')
                        {
                            offset.push_back(line[j]);
                            j++;
                        }

                        if(oper == "beq" || oper == "bne" || oper == "ble" || oper == "bgt" || oper == "bge")   //there last arguement is label
                        {
                            rs = register_number[reg1];
                            rt = register_number[reg2];
                            int label_address = symbol_table[offset];
                            address = decToBinary(label_address, 15);
                            // cout<<"@"<<address<<"@";
                        }
                        else
                        {
                            int int_offset = stoi(offset);
                            address = decToBinary(int_offset, 15);
                            rt = register_number[reg1];
                            rs = register_number[reg2];
                        }
                    }
                    instruction = op + rs + rt + address;   //forming the instruction
                    hex_instruction = binary_to_hex(instruction);   //converting to hex_code
                    fout<<instruction<<"("<<hex_instruction<<","<<line_without_comment<<")"<<"\n";
                }
                else if(format[oper] == 'J')        //if format is J
                {
                    string label;
                    while(line[j]!=' ')
                    {
                        label.push_back(line[j]);
                        j++;
                    }
                    string op = opcode[oper];
                    int label_address = symbol_table[label];
                    string address = decToBinary(label_address, 25);
                    instruction = op + address;
                    hex_instruction = binary_to_hex(instruction);
                    fout<<instruction<<"("<<hex_instruction<<","<<line_without_comment<<")"<<"\n";
                }

            }
        }
    }
    fin.close();
    fout.close();
    return 0;
}


string decToBinary(int n, int bit)
{
    string ans;
    int n_positive = abs(n);
    for (int i = bit; i >= 0; i--) {
        int k = n_positive >> i;
        if (k & 1)
            ans = ans + "1";
        else
            ans = ans + "0";
    }
    if(n<0)
    {
        int first_zero = -1;
        for(int i=bit;i>=0;i--)
        {
            if(ans[i] == '1')
            {
                if(first_zero == -1)
                    first_zero = i;
                ans[i] = '0';
            }
            else
                ans[i] = '1';
        }
        ans[first_zero] = '1';
        for(int i=first_zero+1; i<=bit;i++)
            ans[i] = '0';
    }
    return ans;
}


string binary_to_hex(string instruct)
{
    string ans;
    for(int i=0;i<32;i=i+4)
    {
        string temp;
        for(int j=0;j<4;j++)
        {
            temp.push_back(instruct[i+j]);
        }
        string hex_code = bin_to_hex[temp];
        ans = ans + hex_code;
    }
    return ans;
}

void initialise()
{
    format["add"] = 'R';
    format["addu"] = 'R';
    format["sub"] = 'R';
    format["subu"] = 'R';
    format["mult"] = 'R';
    format["multu"] = 'R';
    format["and"] = 'R';
    format["or"] = 'R';
    format["nor"] = 'R';
    format["sll"] = 'R';
    format["srl"] = 'R';
    format["slt"] = 'R';
    format["jr"] = 'R';
    format["div"] = 'R';
    format["mfhi"] = 'R';
    format["mflo"] = 'R';
    format["jr"] = 'R';
    format["addi"] = 'I';
    format["subi"] = 'I';
    format["multi"] = 'I';
    format["andi"] = 'I';
    format["slti"] = 'I';
    format["ori"] = 'I';
    format["nori"] = 'I';
    format["lw"] = 'I';
    format["sw"] = 'I';
    format["beq"] = 'I';
    format["bne"] = 'I';
    format["ble"] = 'I';
    format["bgt"] = 'I';
    format["bge"] = 'I';
    format["j"] = 'J';
    format["jal"] = 'J';

    symbol_table["loop"] = 2000;
    symbol_table["check"] = 2200;
    symbol_table["end"] = 2400;
    symbol_table["return"] = 2600;
    symbol_table["final"] = 2800;
    symbol_table["gcd"] = 3000;
    symbol_table["L1"] = 3200;
    symbol_table["L2"] = 3400;
    symbol_table["fact"] = 3600;
    symbol_table["else"] = 3800;
    symbol_table["elseend"] = 4000;
    symbol_table["loopend"] = 4200;



    register_number["$zero"] = "00000";
    register_number["$v0"] = "00010";
    register_number["$v1"] = "00011";
    register_number["$a0"] = "00100";
    register_number["$a1"] = "00101";
    register_number["$a2"] = "00110";
    register_number["$a3"] = "00111";
    register_number["$t0"] = "01000";
    register_number["$t1"] = "01001";
    register_number["$t2"] = "01010";
    register_number["$t3"] = "01011";
    register_number["$t4"] = "01100";
    register_number["$t5"] = "01101";
    register_number["$t6"] = "01110";
    register_number["$t7"] = "01111";
    register_number["$s0"] = "10000";
    register_number["$s1"] = "10001";
    register_number["$s2"] = "10010";
    register_number["$s3"] = "10011";
    register_number["$s4"] = "10100";
    register_number["$s5"] = "10101";
    register_number["$s6"] = "10110";
    register_number["$s7"] = "10111";
    register_number["$t8"] = "11000";
    register_number["$t9"] = "11001";
    register_number["$gp"] = "11100";
    register_number["$sp"] = "11101";
    register_number["$fp"] = "11110";
    register_number["$ra"] = "11111";

    opcode["add"] = "100000";
    opcode["addu"] = "100001";
    opcode["addi"] = "001000";
    opcode["and"] = "100100";
    opcode["andi"] = "001100";
    opcode["div"] = "011010";
    opcode["divu"] = "011011";
    opcode["mult"] = "011000";
    opcode["subu"] = "100011";
    opcode["sub"] = "100010";
    opcode["nor"] = "100111";
    opcode["or"] = "100101";
    opcode["ori"] = "001101";
    opcode["sll"] = "000000";
    opcode["srl"] = "000010";
    opcode["slt"] = "101010";
    opcode["slti"] = "001010";
    opcode["beq"] = "000100";
    opcode["bne"] = "000101";
    opcode["j"] = "000010";
    opcode["jal"] = "000011";
    opcode["jr"] = "001000";
    opcode["mfhi"] = "010000";
    opcode["mflo"] = "010010";
    opcode["sw"] = "101011";
    opcode["lw"] = "100011";


    bin_to_hex["0000"] = "0";
    bin_to_hex["0001"] = "1";
    bin_to_hex["0010"] = "2";
    bin_to_hex["0011"] = "3";
    bin_to_hex["0100"] = "4";
    bin_to_hex["0101"] = "5";
    bin_to_hex["0110"] = "6";
    bin_to_hex["0111"] = "7";
    bin_to_hex["1000"] = "8";
    bin_to_hex["1001"] = "9";
    bin_to_hex["1010"] = "a";
    bin_to_hex["1011"] = "b";
    bin_to_hex["1100"] = "c";
    bin_to_hex["1101"] = "d";
    bin_to_hex["1110"] = "e";
    bin_to_hex["1111"] = "f";
}
