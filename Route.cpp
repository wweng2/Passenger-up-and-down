
/*
File: Route.cpp
Project: CMSC 202 Project 3, Fall 2020
Author: Wei zhang weng
Date: 10/25/2020
Section: 10
Email: wweng2@umbc.edu

This file contains all of the function implmentation for all the fucntion in the class route. This file
allows of adding of Stop into an linked List and being able to get information about the stop of it's name and stop number, being able to
reverse the route when it reaches an end point and getting and setting the current stop . And to avoid memory issue there is an function that delete all of the linked list.

*/

#include "Route.h"

Route::Route(){
  m_head = nullptr;
  m_tail = nullptr;
  m_currentStop = nullptr;// Setting the the currentStop to null becuase at this point there is no Stop
  m_totalStops = 0;
  
}

Route::~Route(){
  Stop *m_currentStop = m_head;

  while(m_currentStop != nullptr){// This will keep traversing the Stops until it reaches the end when the last Stop point to a null pointer
    
    m_head = m_currentStop;
    m_currentStop = m_currentStop->GetNextStop();// This set the currentstop to th next stop
    delete m_head;// Getting rid of the Stop node
  }
  m_head = nullptr;
  m_tail = nullptr;
  m_currentStop = nullptr;
  m_totalStops = 0;

}

void Route::LoadRoute(string routefile){
  string name;
  string number;

  ifstream myfile(routefile);

  if(myfile.is_open()){
    while(getline(myfile,name,',')){// As long as there is a string that can getthis will run 
      getline(myfile,number);// This getline doesn't inlcude the delimiter in order to get everything that is left
      AddStop(name,stoi(number));// Use stoi becuase getline requires string so cahnge the number back into an int
       m_totalStops ++;// Inecrease the amount of stop that exist in the route
    }
    
  }
  else{
    cout<<"Unable to open file "<<endl;
  }
  
  cout<<"Route loaded with "<<m_totalStops<<" stops. "<<endl;
  myfile.close();
  m_currentStop = m_head; // To let the route start at the begining
}

void Route::AddStop(string name, int number){
 
  if (m_head == nullptr){// If there is no Stop, this will just make make one and insert it into the linked list
    m_head = new Stop(name,number);
  }
  else{
    Stop* m_currentStop = m_head;// Set the currentStop to m_head the start of the node
     while(m_currentStop->GetNextStop()  != nullptr){ // This will only stop when the current stop's pointer to the next node is poiting at nullptr
      m_currentStop = m_currentStop->GetNextStop();// Goes to the next node
    }
    Stop *NextStop = new Stop(name,number);// Makes a new stop
    m_currentStop->SetNextStop(NextStop);// This make the currentSTop's next stop point to the new stop made
    
}
}


void Route::PrintRouteDetails(){
  Stop *nextStop = m_currentStop->GetNextStop();// Store the next stop after the current one.
  cout<<"Current Stop: "<< m_currentStop->GetName()<<" ("<<m_currentStop->GetNumber()<<" ) "<<endl;
  cout<<"Next Stop: "<<nextStop->GetName()<<" (" << nextStop->GetNumber()<<") "<<endl;
}

 
Stop* Route::GetCurrentStop(){
  return m_currentStop;
}


void Route::SetCurrentStop(Stop* nextStop){
  
  m_currentStop = nextStop;//Goes to the next stop in the route.

}

void Route::ReverseRoute(){
  Stop *current;
  Stop *previous;
  Stop *next;
  current = m_head;
  previous = nullptr;

  while(current != nullptr){

    next = current->GetNextStop();// Set the next stop to be current's next stop
    current->SetNextStop(previous);// Set the current stop to a previous one

    previous = current;
    current = next;
  }
  m_head  = previous;
  m_tail = m_head;
  m_currentStop = m_head;// Set the the current stop to be the complete reverse start.
}

