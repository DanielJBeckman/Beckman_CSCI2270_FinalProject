#include <iostream>
#include <vector>
//#include "Functions.cpp"
#include "Functions.hpp"

using namespace std;



int main()
{
    int choice = 0;
   
    Route R;
    
    R.BuildG();
    R.BuildT();
    //R.PrntG();
    //R.PrntR(R.sim);

    
    while(choice != 4){
        
        cout << "==========Main Menu==========" << endl;
        cout << "1. Find route" << endl;
        cout << "2. Find airfare" << endl;
        cout << "3. Run simulation" << endl;
        cout << "4. Exit" << endl;
        cout << "5. Print graph" << endl;
        cout << "6. Print Tree" << endl;
        
        cin >> choice;
        cin.clear();
        cin.ignore();
        
        switch(choice){
            case 1: R.PrntR(R.sim);
                break;
            case 2: R.getFare();
                break;
            case 3: R.Scenario();
                break;
            case 4: cout << "Goodbye!" << endl;
                break;
            case 5: R.PrntG();
                break;
            case 6:
                break;
        }
        }
        
 
    
    
    
    return 0;
}
