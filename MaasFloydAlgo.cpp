/* Name: Jeremy Maas
   Date: 3/28/2022
   Class: CSC 2710
   Location: ~/csc2710/assignments/FloydAssignment/MaasFloydAlgo.cpp

   About: This program performs floyd's algorithm on data files following a specified
   format. It is also capable of finding the shortest path between two nodes in the array.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#define INFINITY 2000;

using namespace std;

void floyds(int vertices, int WArray[100][100], int DArray[100][100], int PArray[100][100]);// Function to perform Floyd's Algorithm using 2D Arrays//

void path(int q, int r, int Array[100][100]);//Function to find shortest path between nodes//

void printArray(int Array[100][100], int vertices);//Function to Print the 2D Arrays in matrix format//


//NOTE: Everytime a "-49" is seen, it is merely converting ascii integer to regular integer :)//
int main() {

    //Variable Declaration//

    int WArray[100][100], DArray[100][100], PArray[100][100];
    string file;
    ifstream DataFile;
    int vertices, edges;
    string node1, node2;
    int weight;
    int numPaths;

    //File Opening and Loading//

    cout << "Enter name of data file to be used: " << endl;
    cin >> file;
    DataFile.open(file);
    DataFile >> vertices >> edges;

    //Setting W Array Values to Default//
    for(int i = 0; i < vertices; i++)
    {
        for(int j = 0; j < vertices; j++)
        {
            if (i==j)
                WArray[i][j] = 0;
            else
                WArray[i][j] = INFINITY;
        }
    }
    //Reading in values to update W Array//
    for(int i = 0; i < edges; i++)
    {
        DataFile >> node1;
        DataFile >> node2;
        DataFile >> weight;

        WArray[(node1[1]-49)][(node2[1]-49)] = weight;
    }
    //Loading Complete//

    //Call Floyd's Algorithm//
    floyds(vertices, WArray, DArray, PArray);

    //Print WArray
    cout << "W Array:" << endl;
    printArray(WArray, vertices);

    //Print D Array
    cout << "D Array:" << endl;
    printArray(DArray, vertices);

    //Print P Array
    cout << "P Array:" << endl;
    printArray(PArray, vertices);

    //Input number of paths//
    DataFile >> numPaths;
    for (int i = 0; i < numPaths; i++)
    {
        DataFile >> node1 >> node2;
        if ( PArray[node1[1]-49][node2[1]-49] != 0)
        {
            cout << "Path from " << node1 << " to " << node2 << " ====> " << node1 << " ";
            path(node1[1]-49, node2[1]-49, PArray);
            cout << node2 << endl;
        }
        else
        {
            cout << "No path between " << node1 << " and " << node2 << endl;
        }
    }

    DataFile.close();
}

void printArray(int Array[100][100], int vertices)
{
    //Formatting//
    for(int i = 0; i < 7; i++)
    {
        cout << "______";
    }
    cout << endl <<"     ";

    //Labels for Columns
    for(int i = 0; i < vertices; i++)
    {
        cout << left << "v" << i+1 << "    ";
    }
    cout << endl;

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            //Labels for rows//
            if (j == 0)
                cout << "v" << i+1 << "   ";

            //If "Infinity, display "INF", else proceed as normal//
            if(Array[i][j] != 2000)
            {
                cout << setw(6) << left << Array[i][j];
            }
            else
                cout << setw(6) << left << "INF ";
        }
        cout << endl;

    }
    //Formatting//
    for(int i = 0; i < 7; i++)
    {
        cout << "______";
    }
    cout << endl;
}

void floyds(int vertices, int WArray[100][100], int DArray[100][100], int PArray[100][100])
{

    for (int j = 0; j < vertices; j++)
    {
        for (int i = 0; i < vertices; i++)
        {
            //Filling Initial DArray//
            DArray[i][j] = WArray[i][j];
        }
    }

    //Floyds Algorithm
    for (int k = 0; k < vertices; k++)
    {
        for (int j = 0; j < vertices; j++)
        {
            for (int i = 0; i < vertices; i++)
            {
                if(DArray[i][k] + DArray[k][j] < DArray[i][j])//
                {
                    PArray[i][j] = k;//Set P array equal to D(k)(Step in which it changes)
                    DArray[i][j] = DArray[i][k] + DArray[k][j];//If smaller path is found, replace old one
                }
            }
        }
    }
}

void path(int q, int r, int Array[100][100])
{
    if (Array[q][r] != 0)
    {
        path(q, Array[q][r], Array);
        cout << "v" << Array[q][r]+1 << " ";
        path(Array[q][r], r, Array);
    }
}