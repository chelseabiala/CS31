#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function declarations

bool isSyntacticallyCorrect(string pollData);
int tallyVotes(string pollData, char party, int& voteTally);
bool isValidUppercaseStateCode(string stateCode);
int processCode(string code, char p);

// Main method for testing functions - to be discarded

int main()
    {
        for (;;)
        {
            cout << "Enter poll data string: ";
            string pds;
        getline(cin, pds);
        if (pds == "quit")
            break;
            
        cout << "isSyntacticallyCorrect returns ";
        if (isSyntacticallyCorrect(pds))
            cout << "true";
        else
            cout << "false";
        
        int votes = 999;
        tallyVotes(pds, 'd', votes);
        cout << endl;
            cout << votes << endl;

        }
    }

// Checks validity of 2-letter state codes

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

// Checks validity of poll data strings

bool isSyntacticallyCorrect(string pollData)
{
    if(pollData == "")
        return true;
    else
    {
        int i = 0;
        for(;;)
        {
            
            // Checks for vote counts
            
            if(i == pollData.size())
                break;
            if(!isdigit(pollData.at(i)))
                return false;
            i++;
            if(i == pollData.size())
                return false;
            if(isdigit(pollData.at(i)))
                i++;
            string stateCode = "";
            
            // Checks for a valid state code
            
            if(i != pollData.size() - 1 && i + 1 != pollData.size() - 1)
            {
                stateCode += toupper(pollData.at(i));
                stateCode += toupper(pollData.at(i+1));
            }
            else
                return false;
            if(!isValidUppercaseStateCode(stateCode))
                return false;
            i+=2;
            
            // Checks for party codef
            
            if(i >= pollData.size() || !isalpha(pollData.at(i)))
                return false;
            i++;
        }
        return true;
    }
}

// Processes each state forecast individually, returns number of votes for specified political party

int processCode(string code, char p, int length)
{
    
    // Checks for the empty string
    
    if(length == 4 && code.at(0) == '0')
        return -1;
    if(code.at(0) == '0' && code.at(1) == '0')
        return -1;
    int votes = 0;
    
    // Differentiates between forecasts with 1 and 2 digits
    
    if(code.at(length - 1) == p)
    {
        if(length == 5)
        {
            votes += 10 * (code.at(0) - '0');
            votes += (code.at(1) - '0');
        }
        else
        {
            votes += (code.at(0) - '0');
        }
    }
    return votes;
}

// Totals votes in a poll data string for a specified party

int tallyVotes(string pollData, char party, int& voteTally)
{
    
    // Catches exceptional cases, verifies arguments
    
    if(!isSyntacticallyCorrect(pollData))
        return 1;
    if(!isalpha(party) || isdigit(party))
        return 2;
    int k = 0;
    
    int temp = 0;
    
    // Separates and individually processes poll data strings
    
    while(k != pollData.size())
    {
        int processed;
        if(k != pollData.size() - 1 && isdigit(pollData.at(k+1)))
        {
            processed = processCode(pollData.substr(k, 5), party, 5);
            k += 5;
        }
        else
        {
            processed = processCode(pollData.substr(k, 4), party, 4);
            k += 4;
        }
        if(processed == -1)
            return 3;
        else
            temp += processed;
    }
    
    // Sets vote tally to total number of votes after processing all state codes
    
    voteTally = temp;
    return 0;
}
