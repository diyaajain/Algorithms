/*
################################################################################
#
# Diya Jain, U81673988
# Project 3, Algorithms Spring '24
#
################################################################################
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm> // Include algorithm header for std::reverse

struct Cell {
    int r; // Row of the cell
    int c; // Column of the cell
    int value; // Value of the cell
};

struct Maze {
    int dimension; // Dimension of the maze (square maze assumed)
    std::vector<std::vector<int> > maze; // 2D vector representing the maze layout
};

// Function to build the graph based on the maze and cells
void buildGraph(std::vector<std::vector<int> >& graph, const Maze& maze, const std::vector<Cell>& cells) {
    int dimension = maze.dimension;
    for (size_t i = 0; i < cells.size(); ++i) {
        const Cell& cell = cells[i];
        int index = cell.r * dimension + cell.c + 1; // Calculate index of the cell in the graph

        // Look North
        if (cell.r - cell.value >= 0) {
            int destIndex = (cell.r - cell.value) * dimension + cell.c + 1; // Calculate destination index
            graph[index].push_back(destIndex); // Add edge to the graph
        }

        // Look South
        if (cell.r + cell.value < dimension) {
            int destIndex = (cell.r + cell.value) * dimension + cell.c + 1; 
            graph[index].push_back(destIndex); 
        }

        // Look East
        if (cell.c + cell.value < dimension) {
            int destIndex = cell.r * dimension + cell.c + cell.value + 1; 
            graph[index].push_back(destIndex); 
        }

        // Look West
        if (cell.c - cell.value >= 0) {
            int destIndex = cell.r * dimension + cell.c - cell.value + 1; 
            graph[index].push_back(destIndex); 
        }
    }
}

// Function to find the path using BFS in the graph
bool findPath(const std::vector<std::vector<int> >& graph, const int start, const int end, std::vector<int>& path) {
    std::vector<bool> visited(graph.size(), false); // Mark vertices as not visited initially
    std::vector<int> queue; // Queue for BFS traversal
    std::vector<int> parent(graph.size(), -1); // Parent array to track the path

    queue.push_back(start); // Enqueue the start vertex
    visited[start] = true; // Mark start vertex as visited

    bool foundPath = false; // Flag to indicate if a path is found

    // Perform BFS traversal
    while (!queue.empty()) {
        int current = queue.front(); // Get the front of the queue
        queue.erase(queue.begin()); // Remove the front vertex

        // Check if current vertex is the goal
        if (current == end) {
            foundPath = true; // Set path found flag
            break; // Exit the loop
        }

        // Traverse neighbors of the current vertex
        for (size_t i = 0; i < graph[current].size(); ++i) {
            int next = graph[current][i]; // Get next vertex from adjacency list
            if (!visited[next]) { // Check if neighbor is not visited
                queue.push_back(next); // Enqueue the neighbor
                visited[next] = true; // Mark neighbor as visited
                parent[next] = current; // Update parent array
            }
        }
    }

    // Backtrack to get the path if a path is found
    if (foundPath) {
        int current = end;
        while (current != start) {
            path.push_back(current); // Add current vertex to the path
            current = parent[current]; // Move to parent vertex
        }
        path.push_back(start); // Add start vertex to the path
        std::reverse(path.begin(), path.end()); // Reverse the path to get correct order
    }

    return foundPath; // Return if a path is found or not
}

int main() {
    std::ifstream fileIn("input.txt"); // Open input file
    std::ofstream fileOut("output.txt"); // Open output file

    // Check if files are opened successfully
    if (!fileIn.is_open() || !fileOut.is_open()) {
        std::cerr << "Could not open file." << std::endl; // Print error message
        return 1; // Return with error code
    }

    int num_mazes;
    fileIn >> num_mazes; // Read number of mazes

    // Iterate through each maze
    for (int m = 0; m < num_mazes; ++m) {
        int dimension;
        fileIn >> dimension; // Read dimension of the maze

        Maze maze;
        maze.dimension = dimension; // Set maze dimension
        maze.maze.resize(dimension, std::vector<int>(dimension)); // Resize maze layout vector

        std::vector<Cell> cells;
        // Read maze layout from input file
        for (int r = 0; r < dimension; ++r) {
            for (int c = 0; c < dimension; ++c) {
                fileIn >> maze.maze[r][c]; // Read cell value
                Cell cell;
                cell.r = r; // Set cell row
                cell.c = c; // Set cell column
                cell.value = maze.maze[r][c]; // Set cell value
                cells.push_back(cell); // Add cell to vector
            }
        }

        std::vector<std::vector<int> > graph((dimension * dimension) + 1); // Create graph with appropriate size
        buildGraph(graph, maze, cells); // Build the graph based on maze layout and cells

        int start = 1; // Set start vertex (1-indexed)
        int end = dimension * dimension; // Set end vertex

        std::vector<int> path; // Vector to store the path
        bool foundPath = findPath(graph, start, end, path); // Find the path using BFS

        // Write the path to the output file
        for (size_t i = 1; i < path.size(); ++i) {
            int prevIndex = path[i - 1] - 1; // Get previous vertex index
            int curIndex = path[i] - 1; // Get current vertex index

            int prev_r = prevIndex / dimension; // Calculate previous vertex row
            int prev_c = prevIndex % dimension; // Calculate previous vertex column
            int cur_r = curIndex / dimension; // Calculate current vertex row
            int cur_c = curIndex % dimension; // Calculate current vertex column

            // Determine the direction of movement and write it to the output file
            if (cur_r > prev_r) {
                fileOut << "S "; // South
            } else if (cur_r < prev_r) {
                fileOut << "N "; // North
            } else if (cur_c > prev_c) {
                fileOut << "E "; // East
            } else if (cur_c < prev_c) {
                fileOut << "W "; // West
            }
        }
        //fileOut << std::endl; // Add newline in the file after writing the sequence
    }

    fileIn.close(); // Close input file
    fileOut.close(); // Close output file
    return 0; 
}
