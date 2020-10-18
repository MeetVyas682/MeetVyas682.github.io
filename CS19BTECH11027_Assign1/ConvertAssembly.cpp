#include<bits/stdc++.h>
using namespace std;

void initialise();      // to initialise the maps
int binary_to_dec(string binary); //from binary to decimal
string get_substr(string str, int low, int high);   // to get the substring

unordered_map<string, string> register_number;  //to knwo the register name
unordered_map<string, string> opcode;       //to know the instruction name
unordered_map <int, string> symbol_table;   //to know the label



int main()
{
    initialise();
    ifstream fin;
    ofstream fout;
    string line;
    string sub_folder = "sample_data/";
    string filename;
    cout<<"Enter the .txt file name (present in the sample_data): ";
    cin>>filename;
    sub_folder = sub_folder + filename;
    fin.open(sub_folder);

    int pos = filename.find("bin");
    char ch = filename[pos-1];
    string num(1, ch);
    string outputfile = "sample_data/bin" + num + ".asm";
    cout<<"the output is in"<<outputfile<<"\n";
    fout.open(outputfile);

    while(fin)
    {
        getline(fin, line);
        if(line.length()!=0)
        {

            string binary_instruct = get_substr(line, 0, 32);
            string op = get_substr(binary_instruct, 0,6);
            if(op == "000000")          // if op == "000000"  then it's is R format
            {
                string rs = get_substr(binary_instruct, 6,11);
                string rt = get_substr(binary_instruct, 11,16);
                string rd = get_substr(binary_instruct, 16,21);
                string shamt = get_substr(binary_instruct, 21,26);
                string func = get_substr(binary_instruct, 26, 32);
                string oper = opcode[func];

                if(func == "100011")            //because opcode of jr is same as subu
                    oper = "subu";

                string reg1, reg2, reg3;
                if(oper == "mfhi" || oper == "mflo" || oper == "jr")    //they have only one arguement
                {
                    if(oper == "jr")
                        reg2 = register_number[rs];
                    else
                        reg2 = register_number[rd];
                    fout<<"\t"<<oper<<" "<<reg2<<"\n";
                }
                else if(oper == "div" || oper == "mult")        //they have two arguemnet
                {
                    reg1 = register_number[rs];
                    reg2 = register_number[rt];
                    fout<<"\t"<<oper<<" "<<reg1<<", "<<reg2<<"\n";
                }
                else if(oper == "sll" || oper == "srl")     //there last arguement is a nummber
                {
                    long long int sa = binary_to_dec(shamt);
                    reg1 = register_number[rd];
                    reg2 = register_number[rt];
                    fout<<"\t"<<oper<<" "<<reg1<<", "<<reg2<<", "<<sa<<"\n";

                }
                else
                {
                    reg1 = register_number[rd];
                    reg2 = register_number[rs];
                    reg3 = register_number[rt];
                    fout<<"\t"<<oper<<" "<<reg1<<", "<<reg2<<", "<<reg3<<"\n";
                }
            }
            else    //else it can be a J format or I format
            {
                string oper = opcode[op];
                if(oper == "jr")    //because opcode of jr and addi is same, but jr is a R format
                    oper = "addi";

                if(oper == "j" || oper == "jal")    //for J format
                {
                    string add = get_substr(binary_instruct, 6, 32);
                    long long int address = binary_to_dec(add);
                    string label = symbol_table[address];
                    fout<<"\t"<<oper<<" "<<label<<"\n";
                }
                else        //for I format
                {

                    string rs = get_substr(binary_instruct, 6,11);
                    string rt = get_substr(binary_instruct, 11,16);
                    string address = get_substr(binary_instruct, 16, 32);
                    long long int int_address = binary_to_dec(address);
                    string reg1, reg2, reg3;
                    reg1 = register_number[rs];
                    reg2 = register_number[rt];
                    if(oper == "lw" || oper == "sw")    //they have different format
                        fout<<"\t"<<oper<<" "<<reg2<<", "<<int_address<<"("<<reg1<<")"<<"\n";
                    else if(oper == "beq" || oper == "bne" || oper == "ble" || oper == "bgt" || oper == "bge")  //they have different format
                    {
                        string label = symbol_table[int_address];
                        fout<<"\t"<<oper<<" "<<reg1<<", "<<reg2<<", "<<label<<"\n";
                    }
                    else
                        fout<<"\t"<<oper<<" "<<reg2<<", "<<reg1<<", "<<int_address<<"\n";
                }

            }

        }
    }
}

string get_substr(string str, int low, int high)
{
    string ans;
    for(int i=low;i<high;i++)
    {
        ans.push_back(str[i]);
    }
    return ans;
}

int binary_to_dec(string binary)
{
    long long int ans = 0;
    long long int twopower = 1;
    for(int i=binary.length()-1;i>=0;i--)
    {
        if(i==0 && binary[0] == '1')
            ans-=twopower;
        else if(binary[i] == '1')
            ans+=twopower;
        twopower*=2;
    }
    return ans;
}

void initialise()
{
    register_number["00000"] = "$zero";
    register_number["00010"] = "$v0";
    register_number["00011"] = "$v1";
    register_number["00100"] = "$a0";
    register_number["00101"] = "$a1";
    register_number["00110"] = "$a2";
    register_number["00111"] = "$a3";
    register_number["01000"] = "$t0";
    register_number["01001"] = "$t1";
    register_number["01010"] = "$t2";
    register_number["01011"] = "$t3";
    register_number["01100"] = "$t4";
    register_number["01101"] = "$t5";
    register_number["01110"] = "$t6";
    register_number["01111"] = "$t7";
    register_number["10000"] = "$s0";
    register_number["10001"] = "$s1";
    register_number["10010"] = "$s2";
    register_number["10011"] = "$s3";
    register_number["10100"] = "$s4";
    register_number["10101"] = "$s5";
    register_number["10110"] = "$s6";
    register_number["10111"] = "$s7";
    register_number["11000"] = "$t8";
    register_number["11001"] = "$t9";
    register_number["11100"] = "$gp";
    register_number["11101"] = "$sp";
    register_number["11110"] = "$fp";
    register_number["11111"] = "$ra";



    opcode["100000"] = "add";
    opcode["100001"] = "addu";
    opcode["001000"] = "addi";
    opcode["100100"] = "and";
    opcode["001100"] = "andi";
    opcode["100011"] = "subu";
    opcode["100010"] = "sub";
    opcode["011010"] = "div";
    opcode["011011"] = "divu";
    opcode["011000"] = "mult";
    opcode["100111"] = "nor";
    opcode["100101"] = "or";
    opcode["001101"] = "ori";
    opcode["000000"] = "sll";
    opcode["000010"] = "srl";
    opcode["101010"] = "slt";
    opcode["001010"] = "slti";
    opcode["101011"] = "sw";
    opcode["100011"] = "lw";
    opcode["000100"] = "beq";
    opcode["000101"] = "bne";
    opcode["000010"] = "j";
    opcode["001000"] = "jr";
    opcode["000011"] = "jal";
    opcode["010000"] = "mfhi";
    opcode["010010"] = "mflo";

     symbol_table[2000] = "loop";
     symbol_table[2200] = "check";
     symbol_table[2400] = "end";
     symbol_table[2600] = "return";
     symbol_table[2800] = "final";
     symbol_table[3000] = "gcd";
     symbol_table[3200] = "L1";
     symbol_table[3400] = "L2";
     symbol_table[3600] = "fact";
     symbol_table[3800] = "else";
     symbol_table[4000] = "elseend";
     symbol_table[4200] = "loopend";


}
