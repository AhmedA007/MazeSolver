#ifndef project.h
#define project .h // these prevent multiple inclusions of the same header file

#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;    // brings the 'std' namespace into global namespace
using namespace chrono; // brings 'chrono' namespace into global namespace

int SIZE = 20; // Default size of maze

struct Point // struct is defined with two integer members, represent the row and column coordinates in the maze
{

    int row, col;
};

class MazeSolver // class will contain member functions and variables related to solving and manipulating mazes
{

public:
    vector<vector<char>> globalMaze; // Global variable used to pass values into a method

    vector<Point> globalPath;

    vector<double> scoreboard;

    vector<Point> getNeighbors(Point p, const vector<vector<char>> &maze) // member function that takes a Point object and a constant reference to a 2D vector of characters representing the maze
    // The function's purpose is to find and return a vector of neighboring points of p that are not obstacles
    {

        vector<Point> neighbors; // initializes an empty vector of Point objects to store the neighboring points

        int rows[] = {0, 0, 1, -1}; // defines an array rows with four elements: [0, 0, 1, -1]. These values represent the changes in row coordinates needed to move in different directions: right, left, down, up

        int cols[] = {1, -1, 0, 0}; // defines an array cols with four elements: [1, -1, 0, 0]. These values represent the changes in column coordinates needed to move in different directions: right, left, down, up

        for (int i = 0; i < 4; i++) // starts a loop that iterates four times, corresponding to the four possible directions (right, left, down, up)

        {

            int r = p.row + rows[i]; // calculates the new row coordinate (r) by adding the current row coordinate of p with the value from the rows array corresponding to the current iteration of the loop

            int c = p.col + cols[i]; // calculates the new column coordinate (c) by adding the current column coordinate of p with the value from the cols array corresponding to the current iteration of the loop.

            if (r >= 0 && r < SIZE && c >= 0 && c < SIZE && // checks if the new coordinates (r and c) are within the boundaries of the maze (SIZE represents the size of the maze
                // checks if the character at that position in the maze is not an obstacle ('X'). If these conditions are satisfied, the neighboring point is valid and can be added to the neighbors vector
                maze[r][c] != 'X')

            {

                neighbors.push_back(Point{r, c}); // adds the valid neighboring point (represented by a Point object with coordinates r and c) to the neighbors vector.
            }
            else if (r >= 0 && r < SIZE && c >= 0 && c < SIZE && // This line is an additional condition that checks for a specific scenario
                                                                 // If the previous condition was not satisfied, it checks if the current point p is a special type ('0') and if the current direction is horizontal (right or left)
                                                                 // If these conditions are met and the neighboring point is valid (not an obstacle), it is added to the neighbors vector.
                     maze[p.row][p.col] == '0' && rows[i] == 0 &&

                     maze[r][c] != 'X')
            {

                neighbors.push_back(Point{r, c});
            }
        }

        return neighbors; // returns a vector of neighboring points that are not obstacles
    }

    vector<Point> getPath(const vector<vector<int>> &distances, // calculates the shortest path in a maze represented by a 2D vector of characters. It uses a 2D vector of integers called distances to store the distances from each cell to the start cell

                          const vector<vector<char>> &maze)

    {

        vector<Point> path; // creates an empty vector of Point objects to store the path

        Point curr = Point{SIZE - 1, SIZE - 1}; // initializes a Point object called curr with the coordinates of the bottom-right cell of the maze (assuming SIZE is a predefined constant). This represents the starting point

        path.push_back(curr); // adds the starting point to the path vector.

        while (curr.row != 0 || curr.col != 0) // loop iterates until the current cell is the top-left cell of the maze (0, 0).

        {

            int minDist = distances[curr.row][curr.col]; // initializes minDist with the distance of the current cell

            Point next = curr; // initializes next with the current cell.

            for (Point neighbor : getNeighbors(curr, maze)) // loop iterates over each neighbor of the current cell obtained from the getNeighbors function

            // Inside loop, the code checks if the distance of the neighbor cell is less than minDist. If true, it updates minDist and sets next to the neighbor cell.
            {

                if (distances[neighbor.row][neighbor.col] < minDist)

                {

                    minDist = distances[neighbor.row][neighbor.col];

                    next = neighbor;
                }
            }

            path.push_back(next); // dds next to the path vector.

            curr = next; // updates curr to be the next cell.
        }

        reverse(path.begin(), path.end()); // reverses the order of elements in the path vector to obtain the correct order.

        return path; // returns a vector of Point objects representing the shortest path in the maze
    }

    vector<Point> findShortestPath(const vector<vector<char>> &maze) // member function that takes a constant reference to a 2D vector of characters representing the maze

    {
        // uses a breadth-first search algorithm to find the shortest path from the starting point to the ending point in the maze
        vector<vector<int>> distances(SIZE, vector<int>(SIZE, -1)); // initializes a 2D vector distances with the same dimensions as the maze, filled with -1 values. This vector will store the distances from the starting point to each cell in the maze

        vector<vector<Point>> paths(SIZE, vector<Point>(SIZE)); // initializes a 2D vector paths with the same dimensions as the maze, filled with default-constructed Point objects. This vector will store the previous cell on the shortest path to each cell in the maze.

        queue<Point> q; // creates an empty queue to perform the BFS. The queue will store the cells to be explored.

        Point start = Point{0, 0}; // initializes a Point object called start with the coordinates of the top-left cell of the maze. This represents the starting point.

        q.push(start); // adds the starting point to the queue

        distances[start.row][start.col] = 0; // sets the distance of the starting point to 0 in the distances vector.

        while (!q.empty()) // loop continues until the queue is empty, meaning all reachable cells have been explored

        {

            Point curr = q.front(); // retrieves the front element (oldest element) from the queue.

            q.pop(); // removes the front element from the queue.

            if (curr.row == SIZE - 1 && curr.col == SIZE - 1) // If the current cell is the ending point (bottom-right cell of the maze), the function calls the getPath function and returns the shortest path as a vector of Point objects

            {

                return getPath(distances, maze);
            }

            for (Point neighbor : getNeighbors(curr, maze)) // loop iterates over each neighbor of the current cell obtained from the getNeighbors function
            // Inside the loop, the code checks if the distance of the neighbor cell is -1, indicating it has not been visited yet
            {

                if (distances[neighbor.row][neighbor.col] == -1)
                // If the neighbor cell has not been visited, the code updates its distance in the distances vector by incrementing the distance of the current cell by 1. It also sets the previous cell (curr) as the value in the paths vector for the neighbor cell

                {
                    // The neighbor cell is then added to the queue for further exploration

                    distances[neighbor.row][neighbor.col] =

                        distances[curr.row][curr.col] + 1;

                    paths[neighbor.row][neighbor.col] = curr;

                    q.push(neighbor);
                    // After the loop finishes, if the ending point has not been reached, an empty vector of Point objects is returned, indicating that there is no valid path from the starting point to the ending point.
                }
            }
        }

        return vector<Point>{}; // returns a vector of Point objects representing the shortest path
    }

    void generatePath() // member function that generates a random maze and finds the shortest path in it
                        // uses the findShortestPath function and updates the globalMaze and globalPath variables with the generated maze and shortest path, respectively
    {

        int difficulty;
        cout << "What difficulty maze do you want: EASY(1), HARD(2), EXPERT(3) "; // for different maze difficulties
        cin >> difficulty;

        if (difficulty == 2)
        {
            SIZE = 30;
        }
        else if (difficulty == 3)
        {
            SIZE = 40;
        }
        else
        {
            SIZE = 20;
        }

        srand(time(NULL));

        vector<vector<char>> maze(SIZE, vector<char>(SIZE, '0'));

        srand(time(NULL));

        for (int i = 0; i < SIZE; i++)

        {

            for (int j = 0; j < SIZE; j++)

            {

                if (i == 0 || j == 0 || i == SIZE - 1 || j == SIZE - 1)

                {

                    if (rand() % 3 == 0)

                    {

                        maze[i][j] = 'X';
                    }
                }

                else

                {

                    if (rand() % 3 == 0)

                    {

                        maze[i][j] = 'X';
                    }
                }
            }
        }

        Point starting1 = Point{0, 0};

        Point end = Point{SIZE - 1, SIZE - 1};

        maze[starting1.row][starting1.col] = 'S';

        maze[end.row][end.col] = 'E';

        for (int i = 0; i < SIZE; i++)

        {

            for (int j = 0; j < SIZE; j++)

            {

                if (maze[i][j] == 'X')

                {

                    bool replace = false;

                    if (i > 0 && (maze[i - 1][j] == 'S' || maze[i - 1][j] == 'E'))

                    {

                        replace = true;
                    }

                    else if (i < SIZE - 1 && (maze[i + 1][j] == 'S' || maze[i + 1][j] == 'E'))

                    {

                        replace = true;
                    }

                    else if (j > 0 && (maze[i][j - 1] == 'S' || maze[i][j - 1] == 'E'))

                    {

                        replace = true;
                    }

                    else if (j < SIZE - 1 && (maze[i][j + 1] == 'S' || maze[i][j + 1] == 'E'))

                    {

                        replace = true;
                    }

                    else if (i > 0 && j > 0 && (maze[i - 1][j - 1] == 'S' || maze[i - 1][j - 1] == 'E'))

                    {

                        replace = true; // Check for the top-left diagonal cell
                    }

                    else if (i > 0 && j < SIZE - 1 && (maze[i - 1][j + 1] == 'S' || maze[i - 1][j + 1] == 'E'))

                    {

                        replace = true; // Check for the top-right diagonal cell
                    }

                    else if (i < SIZE - 1 && j > 0 && (maze[i + 1][j - 1] == 'S' || maze[i + 1][j - 1] == 'E'))

                    {

                        replace = true; // Check for the bottom-left diagonal cell
                    }

                    else if (i < SIZE - 1 && j < SIZE - 1 && (maze[i + 1][j + 1] == 'S' || maze[i + 1][j + 1] == 'E'))

                    {

                        replace = true; // Check for the bottom-right diagonal cell
                    }

                    if (replace)

                    {

                        maze[i][j] = '0';
                    }
                }
            }
        }

        for (int i = 0; i < SIZE; i++)

        {

            for (int j = 0; j < SIZE; j++)

            {

                if (maze[i][j] == '0')

                {

                    cout << "\033[32m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'X')

                {

                    cout << "\033[37m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == '*')

                {

                    cout << "\033[31m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'S')

                {

                    cout << "\033[36m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'E')

                {

                    cout << "\033[36m" << maze[i][j] << " ";
                }

                else

                {

                    cout << maze[i][j] << " ";
                }
            }

            cout << "\033[0m" << endl;
        }

        vector<Point> path = findShortestPath(maze);

        globalPath = path; // makes the latest values of path and transfers it to globalPath variable

        if (path.size() == 0)

        {

            cout << "No path found." << endl;

            generatePath(); // recursion used so that a path is always found
        }

        else

        {

            globalMaze = maze; // makes the latest values of maze and transfers it to globalMaze variable
        }
    }

    void move(Point &p, const vector<vector<char>> &maze) // member function takes a Point object and a constant reference to a 2D vector of characters representing the maze
                                                          // Allows the user to move through the maze by inputting 'w' (up), 's' (down), 'a' (left), or 'd' (right)
                                                          // It checks for valid moves, obstacles, and reaching the end point, and updates the maze accordingly
    {

        string direction;

        cout << "What is your move?" << endl;

        cin >> direction;

        if (direction == "w")

        {

            p.col--;
        }

        else if (direction == "s")

        {

            p.col++;
        }

        else if (direction == "a")

        {

            p.row--;
        }

        else if (direction == "d")

        {

            p.row++;
        }

        else

        {

            cout << "Invalid move. Please enter 'w', 's', 'a', or 'd'." << endl;

            return;
        }

        // This checks if the move is within the maze boundaries

        if (p.row < 0 || p.row >= SIZE || p.col < 0 || p.col >= SIZE)

        {

            cout << "Invalid move. You hit a wall. GAME OVER" << endl;

            return;
        }

        // This checks if the move is allowed (not hitting a wall)

        if (maze[p.col][p.row] == 'X')

        {

            cout << "Invalid move. You hit a wall. GAME OVER" << endl;

            return;
        }

        if (maze[p.col][p.row] == 'E')

        {

            cout << "Yay! YOU FINISHED!" << endl;

            return;
        }

        // This prints the updated maze

        for (int i = 0; i < SIZE; i++)

        {

            for (int j = 0; j < SIZE; j++)

            {

                if (i == p.col && j == p.row)

                {

                    cout << "\033[33m" << 'P' << " ";
                }

                else if (maze[i][j] == '0')

                {

                    cout << "\033[32m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'X')

                {

                    cout << "\033[37m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == '*')

                {

                    cout << "\033[31m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'S')

                {

                    cout << "\033[36m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'E')

                {

                    cout << "\033[36m" << maze[i][j] << " ";
                }

                else

                {

                    cout << maze[i][j] << " ";
                }
            }

            cout << "\033[0m" << endl;
        }

        move(p, maze);
    }

    void solveMaze(vector<vector<char>> &maze) // member function takes a reference to a 2D vector of characters representing the maze
    // It uses the findShortestPath function to find the shortest path in the maze and updates the maze with markers '*' to represent the path.
    {

        vector<Point> path = findShortestPath(maze);

        path = globalPath;

        for (Point p : path)

        {

            maze[p.row][p.col] = '*';
        }

        cout << endl;

        for (int i = 0; i < SIZE; i++)

        {

            for (int j = 0; j < SIZE; j++)

            {

                if (maze[i][j] == '0')

                {

                    cout << "\033[32m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'X')

                {

                    cout << "\033[37m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == '*')

                {

                    cout << "\033[31m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'S')

                {

                    cout << "\033[36m" << maze[i][j] << " ";
                }

                else if (maze[i][j] == 'E')

                {

                    cout << "\033[36m" << maze[i][j] << " ";
                }

                else

                {

                    cout << maze[i][j] << " ";
                }
            }

            cout << "\033[0m" << endl;
        }
    }
};

#endif // closes the conditional inclusion statement
