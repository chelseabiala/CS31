#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);
void swap(string a[], int first, int second);

int main()
{
    string a[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
    string a2[6] = { "martha", "mark", "joe", "susan", "", "kamala" };
    string a3[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
    string a4[5] = { "joe", "susan", "", "kamala", "lindsey" };
    string a5[2] = { "martha", "joe" };
    assert(lookupAny(a, 7, a4, 5) == 2);
    assert(subsequence(a, 7, a5, 2) == -1);
    assert(subsequence(a, 7, a4, 5) == 2);
    assert(differ(a, 7, a2, 6) == 6);
    assert(differ(a, 7, a3, 7) == 7);
    assert(lookup(a, 7, "mark") == 1);
    assert(lookup(a, 7, "chelsea") == -1);
    assert(lookup(a, 7, "Mark") == -1);
    assert(positionOfMax(a, 7) == 3);
    assert(countRuns(a, 7) == 7);
    assert(rotateLeft(a, 7, 6) == 6 && a[0] == "martha" && a[6] == "lindsey");
    assert(rotateLeft(a, 7, 0) == 0 && a[0] == "mark" && a[6] == "martha");
    
    string a6[5] = { "joe", "hi", "", "kamala", "lindsey" };
    assert(divide(a6, 5, "hi") == 1 && a6[0] == "" && a6[2] > "hi");
    
    string b[3] = {"chel", "izzy", "yui"};
    assert(subsequence(a, 7, b, 3) == -1);
    assert(rotateLeft(b, 3, 1) == 1 && b[0] == "chel" && b[1] == "yui" && b[2] == "izzy");
    assert(appendToAll(b, 3, "!") == 3 && b[0] == "chel!" && b[1] == "yui!" && b[2] == "izzy!");
    assert(flip(b, 3) == 3 && b[0] == "izzy!" && b[1] == "yui!" && b[2] == "chel!");
    assert(lookupAny(a, 7, b, 3) == -1);
    
    string c[4] = {"hi", "bye", "hi", "bye"};
    string c2[2] = {"hi", "bye"};
    assert(subsequence(c, 4, c2, 2) == 0);
    assert(lookupAny(c, 4, c2, 2) == 0);
    assert(lookup(c, 4, "bye") == 1);
    assert(positionOfMax(c, 4) == 0);
    assert(flip(c, 4) == 4 && c[0] == "bye" && c[1] == "hi" && c[2] == "bye" && c[3] == "hi");
    
    string d[1] = {"chelsea"};
    assert(rotateLeft(d, 1, 0) == 0);
    assert(countRuns(d, 1) == 1);
    assert(divide(d, 1, "a") == 0);
    assert(divide(d, 1, "zoo") == 1);
    
    string e[5] = {"", "", "hi", "", ""};
    assert(countRuns(e, 5) == 3);
    
    string f[0];
    assert(appendToAll(f, 0, "!") == 0);
    assert(lookup(f, 0, "") == -1);
    assert(positionOfMax(f, 0) == -1);
    assert(rotateLeft(f, 0, -2) == -1);
    assert(countRuns(f, 0) == 0);
    assert(flip(f, 0) == 0);
    assert(differ(e, 5, f, 0) == 0);
    assert(subsequence(e, 5, f, 0) == 0);
    assert(subsequence(f, 0, e, 5) == -1);
    assert(lookupAny(e, 5, f, 0) == -1);
    assert(lookupAny(f, 0, e, 5) == -1);
    assert(divide(f, 0, "!") == 0);
    
    string g[0];
    assert(differ(f, 0, g, 0) == 0);
    assert(subsequence(f, 0, g, 0) == 0);
    
    assert(appendToAll(b, -1, "!!!") == -1);
    assert(lookup(b, -1, "mark") == -1);
    assert(positionOfMax(b, -1) == -1);
    assert(rotateLeft(b, -1, -1) == -1);
    assert(countRuns(b, -1) == -1);
    assert(flip(b, -1) == -1);
    assert(differ(b, -1, a, 0) == -1);
    assert(subsequence(b, -1, a, 0) == -1);
    assert(lookupAny(b, -1, a, 0) == -1);
    assert(divide(b, -1, "!") == -1);
        
    cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value)
{
    if(n < 0)
        return -1;
    for(int i = 0; i < n; i++)
        a[i] += value;      // Adds value on to each element
    return n;
}

int lookup(const string a[], int n, string target)
{
    if(n < 0)
        return -1;
    for(int i = 0; i < n; i++)
    {
        if(a[i] == target)      // Checks if element is equal to target
            return i;
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if(n <= 0)      // If there are no interesting elements, return -1
        return -1;
    string max = a[0];      // Sets max to first element
    int maxPos = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] > max)      // Checks each element to see if it's greater than max
        {
            max = a[i];     // Resets max as appropriate
            maxPos = i;
        }
    }
    return maxPos;
}

int rotateLeft(string a[], int n, int pos)
{
    if(n < 0 || pos >= n || pos < 0)
        return -1;
    string shifted = a[pos];        // Stores value of element at pos
    for(int i = pos; i < n - 1; i++)
    {
        a[i] = a[i+1];      // Deletes element and shifts everything after over
    }
    a[n-1] = shifted;       // Assigns element to last position of array
    return pos;
}

int countRuns(const string a[], int n)
{
    if(n < 0)
        return -1;
    int runs = 0;
    if(n != 0)
        runs++;
    for(int i = 0; i < n - 1; i++)
    {
        if(a[i] != a[i+1])      // Checks if there's a new run at a[i+1]
        {
            runs++;     // If there is, increments run count
        }
    }
    return runs;
}

int flip(string a[], int n)
{
    if(n < 0)
        return -1;
    for(int i = 0; i < n / 2; i++)      // Iterates until the middle of the array
    {
        swap(a, i, n-1-i);      // Swaps elements in first half w/ elements in second half
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
        return -1;
    int j = n1;
    if(n2 < n1)
        j = n2;     // Sets to size of smaller array
    for(int i = 0; i < j; i++)
    {
        if(a1[i] != a2[i])      // Finds where the two arrays begin to differ
            return i;
    }
    return j;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
        return -1;
    int pos;
    if((n1 == 0 && n2 == 0) || (n2 == 0))
        pos = 0;        // In case empty array is passed in
    else
        pos = -1;
    for(int i = 0; i < n2; i++)
    {
        if(a1[i] == a2[0])      // Checks for beginning of subsequence
        {
            for(int j = 0; j < n2; j++)     // Makes sure entire subsequence is present
            {
                if(a1[j+i] != a2[j])
                    pos = -1;
                else
                    pos = i;
            }
        }
    }
    return pos;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
        return -1;
    for(int i = 0; i < n1; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            if(a1[i] == a2[j])      // Checks if element of a1 is equal to any in a2
                return i;
        }
    }
    return -1;
}

int divide(string a[], int n, string divider)
{
    if(n < 0)
        return -1;
    int pos = n;
    int temp = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[temp] > divider)
        {
            rotateLeft(a, n, temp);     // Puts all elements greater than temp at the end
        }
        else
            temp++;
    }
    for(int j = 0; j < n - 1; j++)
    {
        if(a[j] == divider && a[j+1] < divider)
        {
            swap(a, j, j+1);        // If the divider is in array, move it to correct position
        }
            
    }
    for(int k = 0; k < n; k++)
    {
        if(a[k] >= divider)
        {
            pos = k;        // Finds position of first elements >= to divider to return
            break;
        }
    }
    return pos;
}

void swap(string a[], int first, int second)
{
    string temp = a[first];
    a[first] = a[second];
    a[second] = temp;
}
