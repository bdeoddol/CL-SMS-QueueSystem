#include <iostream>
using namespace std;

// bool sanitizeNumber(string phoneNumber);

int main(){


    




    
return 0;
}



/* testing blocks, copy and paste main code into main(), uncomment the corresponding func implementation*/
/* ------------------- test sanitizeNum -------------------------*/
    //test cases:
    /*
    (214)-931-4749
    2149314749
    sjoijefioj!214!-931-47-4b9
    +12948493928
    */

// string input = "+1214-931---4749";
// if(sanitizeNumber(input) == true){
//     cout << "valid" << endl;
// }
// else{
//     cout << "invalid" << endl;
//}


// bool sanitizeNumber(string phoneNumber){
//     string sanitizedDigits;
//     for(int i = 0; i < phoneNumber.length(); i++){
//         if(isdigit(phoneNumber[i]) == true){
//             sanitizedDigits.push_back(phoneNumber[i]);
//         }
//     }
//     if((sanitizedDigits.length() == 11) && (sanitizedDigits[0] == '1')){
//         return false;
//     }
//     else if((sanitizedDigits.length() < 10) || (sanitizedDigits.length() > 10) ){
//         return false;
//     }
//     else{
//         phoneNumber = sanitizedDigits;
//         cout << phoneNumber << endl;
//         return true;
//     }
// }