#include<iostream>

using namespace std;

void compare(string A, string B){
  // If B > A then 1 otherwise 0
  int i = 0 ;
  for (;i<6;i++){
    if (((int) A.at(i)) > ((int)B.at(i)) ){
      cout << 0 << "\n" ;
      break;
    }
    else if (((int) A.at(i)) < ((int)B.at(i)) ){
        cout << 1 << "\n" ;
        break;
    }
  }
  if (i == 6){
    cout << 1 << "\n" ;
  }
    
}
int main(){
  string numberPlate[2];
  bool act=0;
  while (cin >> numberPlate[act]){
    act=1-act;
    if(act==0){
      // Call your string compare function here on numberPlate[0] and numberPlate[1].
      compare(numberPlate[0],numberPlate[1]) ;
    }
  }
  return(0);
}