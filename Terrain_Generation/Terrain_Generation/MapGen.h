#pragma once
#define UPDOWN 0
#define LEFTRIGHT 1
#include<iostream>
#include<vector>


//2D map generation function
std::vector<std::vector<double>> gen_map(int n);

//Display function
void display(std::vector < std::vector<double>>a);


//One D terrain gen function
std::vector<double> genoned(int n);


//Merge Function
std::vector<std::vector<double>> mergemap(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b,int overlap,int orientation_code);


//Normalization function
std::vector<std::vector<double>> normalize(std::vector <std::vector<double>> a);


//A map generation function for the game(Creates a square-like map by merging 4 maps)

std::vector<std::vector<double>> genMergeFourMap(int size);

//Map genertion to add a linear vertical clamping based on a given size (First and last n rows remain unchanged, middle rows become 0)
std::vector<std::vector<double>> verticalClamp(std::vector<std::vector<double>> a,int defsnow);