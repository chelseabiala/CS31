#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;

const int MAX_WORD_LENGTH = 20;
int cleanupRules(char wordin[][MAX_WORD_LENGTH+1],
                 char wordout[][MAX_WORD_LENGTH+1],
                 int nRules);
int determineScore(const char document[],
                   const char wordin[][MAX_WORD_LENGTH+1],
                   const char wordout[][MAX_WORD_LENGTH+1],
                   int nRules);
void rotate(char a[][MAX_WORD_LENGTH+1], int n, int pos);

int main()
{
    char in[14][MAX_WORD_LENGTH+1] = {"confusion", "FAMILY", "charm", "hearty", "house", "worn-out", "", "family", "charm", "ties", "", "charm", "FaMiLy"};
    char out[14][MAX_WORD_LENGTH+1] = {"", "TIES", "confusion", "hearty", "intrigue", "younger", "", "first", "", "family", "frightened", "", "tIeS"};
    assert(cleanupRules(in, out, 14) == 6);
    assert(cleanupRules(in, out, -1) == 0);
    
    char in1[1][MAX_WORD_LENGTH+1] = {"confusion"};
    char out1[1][MAX_WORD_LENGTH+1] = {"hello"};
    assert(cleanupRules(in1, out1, 1) == 1);
    
    char in2[1][MAX_WORD_LENGTH+1] = {"confusion1"};
    char out2[1][MAX_WORD_LENGTH+1] = {"he llo"};
    assert(cleanupRules(in2, out2, 1) == 0);


    const int TEST1_NRULES = 3;
               char test1win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
                   "family", "unhappy", "horse",
               };
               char test1wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
                   "",       "horse",   "",
               };
    assert(determineScore("Hi Horse man", test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("Hi Horse man", test1win, test1wout, -1) == 0);
    assert(determineScore("Nothing", test1win, test1wout, TEST1_NRULES) == 0);
    assert(determineScore("I’m unhappy rn", test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("Unhappy horse", test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("Unhappy family", test1win, test1wout, TEST1_NRULES) == 2);
    assert(determineScore("Family-horse", test1win, test1wout, TEST1_NRULES) == 0);
    assert(determineScore("Horse horse", test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("LLL horse jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", test1win, test1wout, TEST1_NRULES) == 1);

               cout << "All tests succeeded" << endl;
}

int cleanupRules(char wordin[][MAX_WORD_LENGTH+1],
                 char wordout[][MAX_WORD_LENGTH+1],
                 int nRules)
{
    if(nRules < 1)
        return 0;
    int n = nRules;
    for(int i = 0; i < n;)
    {
        bool checked = true;
        if(wordin[i][0] == '\0')        // Finds rules where win is ""
            checked = false;
        if(strcmp(wordin[i], wordout[i]) == 0)
            checked = false;
        if(checked)
        {
            for(int j = 0; j < MAX_WORD_LENGTH; j++)
            {
                if((!isalpha(wordin[i][j])  // Finds rules with non-alphabetical chars
                    && wordin[i][j] != '\0')
                   || ((!isalpha(wordout[i][j]))
                       && wordout[i][j] != '\0'))
                {
                    checked = false;
                }
                if(isupper(wordin[i][j]))       // Converts win to lowercase
                    wordin[i][j] = tolower(wordin[i][j]);
                if(isupper(wordout[i][j]))
                    wordout[i][j] = tolower(wordout[i][j]);     // Converts wout to lowercase
            }
        }
        if(!checked)
        {
            rotate(wordin, nRules, i);      // Gets rid of any illegal rules
            rotate(wordout, nRules, i);
            n--;
        }
        else
            i++;
    }
    for(int i = 0; i < n; i++)
    {
        if(strcmp(wordout[i], "") == 0)
        {
            for(int j = 0; j < n; j++)
            {
                if(strcmp(wordin[i], wordin[j]) == 0 && i != j)
                {
                    rotate(wordin, nRules, j);      // Gets rid of rules with win duplicates
                    rotate(wordout, nRules, j);
                    n--; j--;
                    if(i > j)
                        i--;
                }
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        if(strcmp(wordout[i], "") != 0)
        {
            for(int j = 0; j < n; j++)
            {
                if((strcmp(wordin[i], wordin[j]) == 0 && i != j)
                   && (strcmp(wordout[i],  wordout[j]) == 0 && i != j))
                {
                    rotate(wordin, nRules, j); // Gets rid of rules with win and wout duplicates
                    rotate(wordout, nRules, j);
                    n--; j--;
                    if(i > j)
                        i--;
                }
            }
        }
    }
    return n;
}

int determineScore(const char document[],
                   const char wordin[][MAX_WORD_LENGTH+1],
                   const char wordout[][MAX_WORD_LENGTH+1],
                   int nRules)
{
    int score = 0;
    char doc[253];
    doc[0] = ' ';
    int docSize = 1; int pos = 0;
    while(pos < 251 && document[pos] != '\0')
    {
        if(isalpha(document[pos]) || document[pos] == ' ')
        {
            doc[docSize] = tolower(document[pos]);      // Copies all relevant characters into separate array
            docSize++;
        }
        pos++;
    }
    doc[docSize] = ' ';     // Adds a space to beginning and end of document text
    docSize++;
    doc[docSize] = '\0';
    for(int i = 0; i < nRules; i++)
    {
        char word[MAX_WORD_LENGTH+3] = " ";
        strcat(word, wordin[i]);        // Adds a space to beginning and end of each rule
        strcat(word, " ");
        if(wordout[i][0] != '\0')
        {
            if(strstr(doc, word) != nullptr && strstr(doc, wordout[i]) == nullptr)
                score++;
        }
        else
        {
            if(strstr(doc, word) != nullptr)
                score++;
        }
    }
    return score;
}


void rotate(char a[][MAX_WORD_LENGTH+1], int n, int pos)
{
    for(int i = pos; i < n - 1; i++)
    {
        strcpy(a[i],a[i+1]);
    }
}
