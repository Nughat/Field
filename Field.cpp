/*
Title: Field.cpp
Description: Implements a class Field
Date: 11/22/20
*/
#include <iostream>
#include <vector>
#include <string>
#include "Field.h"

/*@param vec The 2d array
@post If the construction is successful, two 2d arrays called sums and path have been created 
@return If vec is empty */
Field::Field(const std::vector<std::vector<int>> & vec)
{
    if(vec.empty()) //return if vec is empty
        return; //return
    path = vec; //set path equal to vec
    sums = vec; //set sums equal to vec
    std::vector<int> dp(vec[0].size()); //vector with size of the rows of vec, used to calculate sums of each row
    for (int i=0;i<vec.size();i++) 
    {
        dp = vec[i]; //set dp equal to each row of vec so that the row sum values can be calculated
        for (int j = 0; j < vec[i].size(); j++)
        {
            if (j != 0) //if it is not the first value in the row of the vector then the sum should be calculated, eg. 1,2,3 becomes 1,3,6
            {
                dp[j] = dp[j-1] + vec[i][j]; //calculate the row sums
            }             
            if (i==0) //if it is the first row
            {
                sums[i] = dp; //simply store the row sums bc they do not need to be modified further
                if (j!=0) //if it is not the first value in the first row of path then compute row sums
                {
                    path[i][j]=path[i][j-1] + path[i][j]; //calculate the row sums of the first row, eg. 1,2,3 becomes 1,3,6
                }
            }        
            else if (i != 0) //if it is not the first row 
            {
                sums[i][j] = dp[j] + sums[i-1][j]; //after computing the row sums of the row add the values to the sums of the previous row and insert into sums, eg. 1,3,6+1,3,6 = 2,6,12
                if (j == 0) //if it is the first col then the col sums in path need to be computed
                {
                    path[i][j]=path[i-1][j] + path[i][j]; //calculate the col sums of the first col, eg. 1,1,1 becomes 1,2,3
                }
                if (j != 0) //if it is not the first col then the cheapest path needs to be computed
                {
                    path[i][j] = path[i][j] + std::min(path[i-1][j], path[i][j-1]); //for every coordinate that is not in the first row or col check if its top or left value is smaller and add it to the coordinate
                }
            }
        }
    } //path will have the value of the cheapest path in the rightmost bottomost coordinate while sum will hold the sum of all elements
} //end parametrized constructor

/*@param vec The 2d array
@post If the construction is successful, two 2d arrays called sums and path have been created 
@return If vec is empty */
Field::Field( std::vector<std::vector<int>> && vec)
{
    if(vec.empty()) //return if vec is empty
        return; //return
    path = std::move(vec); //path takes vec's values, vec may no longer hold its values
    sums = path; //sums also needs vec's values, so it copies it from path
    std::vector<int> dp(path[0].size()); //vector with size of the rows of "vec", used to calculate sums of each row
    for (int i=0;i<path.size();i++)
    {
        dp = sums[i]; //set dp equal to each row of "vec" so that the row sum values can be calculated
        for (int j = 0; j < path[i].size(); j++)
         {
            if (j != 0) //if it is not the first value in the row of the vector then the sum should be calculated
            {
                dp[j] = dp[j-1] + sums[i][j]; //calculate the row sums
            }             
            if (i==0) //if it is the first row
            {
                sums[i] = dp; //simply store the row sums bc they do not need to be modified further
                if (j!=0) //if it is not the first value in the first row of path then compute row sums
                {
                    path[i][j]=path[i][j-1] + path[i][j]; //calculate the row sums of the first row
                }
            }        
            else if (i != 0) //if it is not the first row 
            {
                sums[i][j] = dp[j] + sums[i-1][j]; //after computing the row sums of the row add the values to the sums of the previous row and insert into sums
                if (j == 0) //if it is not the first col then the cheapest path needs to be computed
                {
                    path[i][j]=path[i-1][j] + path[i][j]; //calculate the col sums of the first col
                }
                if (j != 0) //if it is not the first col then the cheapest path needs to be computed
                {
                    path[i][j] = path[i][j] + std::min(path[i-1][j], path[i][j-1]); //for every coordinate that is not in the first row or col check if its top or left value is smaller and add it to the coordinate
                }
            }
        }
    } //path will have the value of the cheapest path in the rightmost bottomost coordinate while sum will hold the sum of all elements
} //end parameterized "move" constructor

/*@param x1, y1 and x2, y2 The coordinates of two corners of the rectangle, but in reality the x and y coordinates are switched
@post If the computation is successful, the the sum of all elements in the rectangle defined by the points (x1,y1) and (x2,y2) is obtained
@return The sum of elements between the two points */
int Field::Weight( int x1, int y1, int x2, int y2 )
{
    if ((x1 > sums[0].size()) || (x2 > sums[0].size()) || (y1 > sums.size())  || (y2 > sums.size())) //if any of the coordinates go past the array boundaries
    {
        throw std::out_of_range ("STOP!!! Invalid number"); //then the computations cannot be completed
    }
    if (sums.empty()) //if the origninal vec was empty then sums is also empty 
    {
        return 0; //the area of any rectangle in an empty sums array will be 0
    }
    int big_x = std::max(x1,x2); //find the maximum x value bw the two coordinates
    int small_x = std::min(x1,x2); //find the minimum x value bw the two coordinates
    int big_y = std::max(y1,y2); //find the maximum y value bw the two coordinates
    int small_y = std::min(y1,y2); //find the minimum y value bw the two coordinates
    int area_to_sub = sums[big_y][big_x]; //finds the rightmost bottomost corner of the defined rectangle, this is the sum to be subtracted from if necessary
    if (small_x == 0 && small_y == 0) //if either coordinate is 0,0
    {
        return area_to_sub; //there is no need to subtract anything and the rightmost bottomost corner should be returned as is       
    }
    if (small_y == 0 && small_x != 0) //if either coordinate is on topmost edge of the array but is not at 0,0
    {
        int left = sums[big_y][small_x - 1]; //then only need to remove the sum of any cols before the smallest x, eg. for (1,1) and (2,0) remove sum the sum of the 0th col
        return area_to_sub - left; //return the original total sum minus the left portion
    }
    if (small_x == 0 && small_y != 0) //if either coordinate is on leftmost edge of the array but is not at 0,0
    {
        int top = sums[small_y-1][big_x]; //then only need to remove the sum of any rows above the smallest y, eg. for (0,4) and (1,2) remove sum the sum of the 1st row  
        return area_to_sub - top; //return the original total sum minus the top portion
    }
    int left = sums[big_y][small_x - 1]; //none of the digits are 0, so left portion needs to be subtracted
    int top = sums[small_y-1][big_x]; //top portion also needs to be subtracted
    area_to_sub = area_to_sub - (left + top); //subtract them from the original total area
    area_to_sub = area_to_sub + sums[small_y-1][small_x-1]; //add back the overlapping area that was subtracted twice 
    return area_to_sub; //return the sum
} //end Weight

/*@post If the access is successful, the the cheapeast path from the first coordinate to the last coordinate will be obtained
@return The value of the cheapest value*/
int Field::PathCost()
{
    if (path.empty()) //if the orignial vec was empty then path is also empty
    {
        return 0; //the area of any path in an empty path array will be 0
    }
    return path[path.size() - 1][path[0].size() - 1]; //the cheapeast path value is at the rightmost bottomost coordinate of the array
} //end Path