#include <iostream>

#include <vector>

#include <queue>

#include <cstdlib>

#include <ctime>

#include <algorithm>

#include <chrono>
#include "project.h"
 
#include <fstream>//for scoreboard

using namespace std;

using namespace chrono;

int main()

{
 MazeSolver solver; //Create an instance of MazeSolver class

    Point starting = Point{0, 0}; // Initialized the starting point to pass into functions

    char ready;

    cout << "Hello! Welcome to the maze solver game!" << endl;

    cout << "Please Enter R or r when you are ready, there will be a timer, so pay attention!" << endl;

    cin >> ready;

    while (ready == 'R' || ready == 'r')

    {

      solver.generatePath(); //Generates a maze path
      break; //Exits the loop after generating the maze path

    }

    auto start = high_resolution_clock::now(); //Starts the timer that shows the time elapsed when you finish the game

    char done;

    solver.move(starting, solver.globalMaze); //moves through the maze based on user input

    cout << "Please enter D or d when you are done!";

    cin >> done;

   solver.solveMaze(solver.globalMaze); //solves the maze and shows the shortest path

    auto stop = high_resolution_clock::now(); //stops the timer

    auto duration = duration_cast<milliseconds>(stop - start); //calculates the elapsed time

     int timetaken=duration.count() / 1000; //in seconds

    cout << "Elapsed time: " << timetaken << " seconds" << endl;
 


//took help with the following code from https://cplusplus.com/doc/tutorial/files/

        // Open the file in append mode
    ofstream file("scoreboard.txt", ios::app); //opens file in append mode(ios::app). With this mode we can add times to the end of the file without overwriting the existing content.
     

       
        file << timetaken << endl; //writes time elapsed to file

 
        file.close(); //closes file

      ifstream readfile("scoreboard.txt");

          double min_value = numeric_limits<double>::max(); //This ensures that any valid value from the file will be smaller than the initial value of min_value
        double value;

        while (readfile >> value) { //if the current value is smaller than min_value, it updates min_value accordingly
            if (value < min_value) {
                min_value = value;
            }
        }

        file.close();

         
         
         if (min_value != numeric_limits<double>::max()) // Checks if min_value has been updated. If it has, it outputs the smallest value found in the file. Otherwise, it means that the file is empty
    {
        cout << "Your fastest score was: " << min_value << " seconds" << endl; //outputs fastest times
        if (timetaken < min_value)  //if user's score is faster than the fastest score in file
        {
            cout << "Congratulations! You beat the fastest score!" << endl;
        }
        else if (timetaken == min_value) //if user'score is as fast as the fastest one in the file
        {
            cout << "You tied with the fastest score!" << endl;
        }
        else //this means that the user's score was less than the fastest one
        {
            cout << "Keep trying to beat the fastest score!" << endl;
        }
    }
    else //this means the file is empty
    {
        cout << "Congratulations! You are the first player of our game" << endl;
    }

    return 0;
}