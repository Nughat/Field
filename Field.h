/*
Title: Field.h
Description: Specifies a class Field
Date: 11/22/20
*/
#include <iostream>
#include <vector>

class Field
{
    private:
    std::vector<std::vector<int>> sums; //2d array holds the sum of all elements in a 2d array
    std::vector<std::vector<int>> path; //2d array holds the cheapest path from the first element to the last element in a 2d array
    public:
    Field(const std::vector<std::vector<int>> & rs); //parameterized constructor
    Field(std::vector<std::vector<int>> && rs); //parameterized "move" constructor
    //f(x)
    int Weight( int x1, int y1, int x2, int y2 );
    int PathCost();
};