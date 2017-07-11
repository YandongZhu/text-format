// A Dynamic programming solution for Word Wrap Problem
#include <limits.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#define INF INT_MAX
using namespace std;
 

int num = 0;
int limit = 0;
int weight = 0;
int length [1000000];
string word [1000000];
int print[1000000];
std::vector<std::vector<int> > extras;
std::vector<std::vector<int> > lineCost;
 

int printSolution (int n)
{  
    int check = 1; 
    int k;
    if (print[n] == 0)
        k = 1;
    else
        k = printSolution (print[n]-1) + 1;

    for (int i = print[n]; i <= n; ++i)
    {
        if (check)
        {
            cout << word[i];
            check = 0;
        }
        else
        {
        cout << " " << word[i];
        }
    }
    cout << endl;
    return k;
}

int count (int n)
{   
    int k;
    if (print[n] == 0)
        k = 1;
    else
        k = count (print[n]-1) + 1;
    weight += lineCost[print[n]][n];
    return k;
}


void solveWordWrap (void)
{
    
    int cost[num];


    for (int i = 0; i < num; i++)
    {
        extras.push_back(std::vector<int>());
        lineCost.push_back(std::vector<int>());
        for (int k = 0; k < i; ++k)
        {
            extras[i].push_back(0);
            lineCost[i].push_back(0);
        }
        for (int j = i; j < num; j++)
        {
            // finding extra space
            if (i == j)
            {
                extras[i].push_back(limit - length[i]);
            }
            else
            {
                extras[i].push_back(extras[i][j-1] - length[j] - 1);
            }

            //finding line cost for each possibliliy
            if (extras[i][j] < 0)
            {
                lineCost[i].push_back(INF);
            }
            else if (j == num-1 && extras[i][j] >= 0)
            {
                lineCost[i].push_back(0);
            }
            else
            {
                lineCost[i].push_back(extras[i][j]*extras[i][j]);
            }
        }
    }

    cost[0] = 0;
    for (int j = 0; j < num; j++)
    {
        cost[j] = INF;
        for (int i = 0; i <= j; i++)
        {
            if (cost[i-1] != INF && lineCost[i][j] != INF && (cost[i-1] + lineCost[i][j] < cost[j]))
            {
                cost[j] = cost[i-1] + lineCost[i][j];
                print[j] = i;
            }
        }
    }
    int lineNum = count(num - 1);
    cout << weight << " " << lineNum << endl;
    printSolution(num-1);
}
 
int main()
{
    cin >> num >> limit;
    for (int i = 0; i < num; ++i)
    {
        string temp;
        cin >> temp;
        word[i] = temp;
        length[i] = temp.length();
    }


    solveWordWrap();
    return 0;
}