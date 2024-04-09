/*
File: Passenger.cpp
Project: CMSC 202 Project 3, Fall 2020
Author: Wei zhang Weng
Date: 10/25/20
Section: 10
Email: wweng2@umbc.edu

This file contains the function implmentation of all the functions in the Passenger class. Which allows for a passenger object to be created with an overloaded function, with it's name , start destination and end destination
*/

#include "Passenger.h"

Passenger::Passenger(string name, int age , string startLocation, string finalDestination){
  m_fullName = name;// This assign the full name a passenger has
  m_age = age;
  m_startLocation = startLocation;// Just assign the start location doesn't include the stop number;
  m_finalDestination = finalDestination;// This assign the Final destination , doesn't include the stop number
}
 
string Passenger::GetName(){
  return m_fullName;
}

string Passenger::GetStartLocation(){
  return m_startLocation;
}

string Passenger::GetFinalDestination(){
  return m_finalDestination;
}

