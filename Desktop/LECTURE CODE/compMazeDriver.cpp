//Student: Ariel Farias
//UFID: 93739830
//Due date: 03/17/14

#include "maze.h"
#include <vector>

//Input maze.txt file here:
#define MAZE_FILE "/Users/admin/Desktop/mazeWithCycle.txt"

//NOTE: I compiled with g++ UNIX terminal

//In order for the main to recognize the method calls
//the methods are declared here:
bool solve(Maze* M, char move);
bool path(int x, int y);
//To be able to use the tracking vectors in either method:
vector<int> xpath;
vector<int> ypath;


//Simply initialize and establish the maze that is linked
//After the maze knows the starting position, call the solver;
int main(){
	Maze M;
	M.ReadMaze(MAZE_FILE);
	cout<<"This is the maze."<<endl;
	cout << M;
  Maze* maze = &M;
	maze->getStart();
  cout << *maze;
	
	solve(maze, '@');
}

//The vectors are checked to see if the given coordinate
//has already been visited (stored): returns true or false
bool path(int x, int y){
  for(int i = 0; i<xpath.size(); i++){
    if(x==xpath[i] && y==ypath[i]){
      return false;
    }
  }
  return true;
}

//The solver has essentially five cases:
//(1)if it is finished
//(2)if we move south
//(3)if we move east
//...and so forth for each direction
bool solve(Maze* M, char move){
  //Printing to the screen to notify current position:
  cout<<*M;
  int x = 0;
  int y = 0;
  M->getCurrentLocation(x,y);
  cout<<"You are at ( " << x << ", " << y << ")!" <<endl;
  
  //Base Case(1)
  if(M->isFinish()){
    cout<<"Congratulations! Maze is complete"<<endl;
    return true;
  }

  // Recursive Cases(2-5)

  // The primary if statement will verify that
  // it doesn't move back and will verify that
  // south is an option.
  if(move !='N'&&M->south()){

    //Then, the x,y positions are updated and
    //The visited(previous) coordinates are
    //added to the vectors 
    M->getCurrentLocation(x,y);
    xpath.push_back(x);
    ypath.push_back(y-1);
    //Once previous location is stored, check
    //and see if the current location has already
    //been visited.
    //The recursion is then called within the same
    //condition.
    if(path(x,y)&&solve(M,'S')){
      return true;
    }
    //If no solution is plausible from that position,
    //Go back the opposite direction:
    else{
      M->north();
    }
  }

  //Repeat the same logic to each directional case
  if(move!='W'&&M->east()){
    M->getCurrentLocation(x,y);
    xpath.push_back(x-1);
    ypath.push_back(y);
    if(path(x,y)&&solve(M,'E')){
      return true;
    }
    else{
      M->west();
    }
  }
  if(move!='S'&&M->north()){
    M->getCurrentLocation(x,y);
    xpath.push_back(x);
    ypath.push_back(y+1);
    if(path(x,y)&&solve(M, 'N')){
      return true;
    }
    else{
      M->south();
    }
  }
  if(move!='E'&&M->west()){
    M->getCurrentLocation(x,y);
    xpath.push_back(x+1);
    ypath.push_back(y);
    if(path(x,y)&&solve(M,'W')){
      return true;
    }
    else{
      M->east();
    }
  }
}