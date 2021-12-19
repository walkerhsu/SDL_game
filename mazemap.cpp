#include "mazemap.hpp"
MazeMap::MazeMap(){
    
}

// destructor
MazeMap::~MazeMap(){
    matrix.clear();
}

void MazeMap::loadMap(char path[]){
    matrix.clear();
    
    //readfile
    fstream file;
    file.open(path);
    string line;
    int row=0;
    while (getline(file, line, '\n')) { //read till rew line char
        if (line.length() > 0) {
            vector<int> element = vector<int>();
            matrix.push_back(element);
        }
        istringstream templine(line); //string to stream
        string data;
        while (getline(templine, data, ',')) { //read till comma
            matrix[row].push_back(atoi(data.c_str() ) ); //string to int
        }
        row++;
    }
    file.close();
    dumpMap();
}

void MazeMap::dumpMap(){
    if (matrix.size() >0) {
        for (int row=0; row< matrix.size(); row++){
            for (int col=0; col<matrix[row].size(); col++ ) {
                cout << matrix[row][col];
            }
            cout << endl;
        }
    }
}
