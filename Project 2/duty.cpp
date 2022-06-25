#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Collects and verifies user input
   
    cout << "Cheese type: ";
    string type;
    getline(cin, type);
    if(type == "")
    {
        cout << "---" << endl << "You must enter a cheese type" << endl;
        return 1;
    }

    cout << "Value: ";
    double value;
    cin >> value;
    if(value <= 0)
    {
        cout << "---" << endl <<"The value must be positive" << endl;
        return 1;
    }
    
    cout << "Importer: ";
    cin.ignore(10000, '\n');
    string importer;
    getline(cin, importer);
    if(importer == "")
    {
        cout << "---" << endl << "You must enter an importer" << endl;
        return 1;
    }
    
    // Calculates import duty
    
    double duty;
    double tempValue = value;
    
    if(value <= 1000)   // For values less than 1000
    {
        duty = 0.011 * value;
    }
    else    // For values over 1000
    {
        duty = 0.011 * 1000;
        tempValue -= 1000;
    }
    
    if(value <= 13000 && value > 1000)  // For values less than 13000 but over 1000
    {
        if(type == "stilton" || type == "chesire")
        {
            duty += (0.014 * tempValue);
        }
        else
        {
            duty += (0.02 * tempValue);
        }
    }
    else if(value > 1000)   // For values over 13000
    {
        if(type == "stilton" || type == "chesire")
        {
            duty += (0.014 * 12000);
            tempValue -= 12000;
        }
        else
        {
            duty += (0.02 * 12000);
            tempValue -= 12000;
        }
    }
    
    if(value > 13000)   // For values over 13000
    {
        duty += (0.029 * tempValue);
    }
    
    // Outputs information
    
    cout.setf(ios::fixed);
    cout.precision(2);
    

    cout << "---" << endl
    << "The import duty for " << importer << " is $" << duty << endl;
    
    return 0;
    
}
