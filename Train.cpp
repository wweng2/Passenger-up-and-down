
/*
File: Train.cpp
Project: CMSC 202 Project 3, Fall 2020
0;136;0cAuthorL Wei zhang Weng
Date: 10/25/2020
Section: 10
Email: wweng@umbc.edu

This file inculdes the fucntion implentation of all the functions in the train class which allows for adding train cars and allow for loading passenger file and allwing for the boarding and disembarking of passenger, and going to the next stop and turing the trains around.
*/

#include "Train.h"

Train::Train(Route* route){
  m_route = route;// Set m_route to route that have all stops loaded
  m_totalCars = 0;
  m_head = nullptr;
  AddCar();// Add a car and add one to the total of cars
}

Train::~Train(){
  Car *curr = m_head;
  while (curr != nullptr){
    m_head = curr;
    curr = curr->m_next;
    m_head->m_passengers.clear();// Get rid of the vectors
    delete m_head;// And then get rid of the node
  }
  m_head = nullptr;
  m_totalCars = 0;
  
}

void Train::AddCar(){
  
   if (m_head == nullptr){
     m_head = new Car(CAR_CAPACITY,m_totalCars + 1);// This is m_totalcars plus one to make the start at Car 1 and not 0
  }
   else{       
      Car *currCar = m_head;

      while(currCar->m_next !=nullptr){// until currcar become null pointer the while loop will keep running
	currCar = currCar->m_next;// Goes to the next car
	  }
      
      currCar->m_next = new Car(CAR_CAPACITY,m_totalCars + 1);// Sets m_next to a new car node, use m_totalCars as a car number
      
    }
  
   m_totalCars ++;
  
      
}
 
void Train::RemoveCar(Car*){
  return ;// Not used so just return nothing to not let it bother anything
}


void Train::TrainStatus(){
  if(m_head == nullptr){
    cout<<"No cars are on the train"<<endl;// This shows nothing if there is no cars on the train
    
  }
  else{
    Car *curr = m_head;
    
    cout<<"Number of cars: "<<m_totalCars<<endl;// output the number of cars

    while(curr != nullptr){// Loops through all the car display how many passengers are in each car

      cout<<"Car "<<curr->m_carNumber<<": Number of passengers: "<<curr->m_passengers.size()<<endl;
      curr = curr->m_next;
           

      }
    Stop* currentStop = m_route->GetCurrentStop();
    Stop* next = currentStop->GetNextStop();// Set next to the next Stop load after the current
    if(currentStop ->GetNextStop() != nullptr){
      cout<<"Current stop: "<<currentStop->GetName()<<"  ("<<currentStop->GetNumber()<<")"<<endl;
      cout<<"Next stop is: "<<next->GetName()<<"   ("<<next->GetNumber()<<")"<<endl;
    }
    else{// When it reach the last stop, it will just say this is the last stop and
      cout<<"Current stop: "<<currentStop->GetName()<<"  ("<<currentStop->GetNumber()<<")"<<endl;
      cout<<"This is the last stop"<<endl;
    }
    }      
  
}
 
void Train::LoadPassengers(string passName){

  string firstname;
  string lastname;
  string age;
  string startLocation;
  string finalDestination;
  ifstream myfile(passName);
  string name;
  int Loadedpeoples = 0;
  Stop* currentStop = m_route->GetCurrentStop();
 
  if(myfile.is_open()){

    while(getline(myfile,firstname,',')){// Will keep run until till there is no string left in the file
      getline(myfile,lastname,',');
      getline(myfile,age,',');
      getline(myfile,startLocation,',');
      getline(myfile,finalDestination);

      name = firstname + ' ' + lastname;// Combine the first and last name togther so the passenger has a a full name

        
      if(startLocation == currentStop->GetName()){// If the start location of the passenger is the same as the curr location than the passenger is added
	
	Passenger *passenger = new Passenger(name,stoi(age),startLocation,finalDestination);
	BoardPassenger(passenger);// The noardpassenger function will load the passenger struct into the linked list
	cout<<passenger->GetName()<<" Board the Train (Destination: "<<passenger->GetFinalDestination()<<" )\
"<<endl;
	Loadedpeoples ++;
      }
      
    }
  }
  else{
    cout<<"unable to open file , please try again "<<endl;
  }
  myfile.close();
  cout<<"Boarded "<<Loadedpeoples<<" passengers "<<endl;
 
}

void Train::BoardPassenger(Passenger* passenger){
  
  if(IsTrainFull() == true){
    AddCar();// If the entire train is full then add a new car
  }
  Car *curr = m_head;
  
  while(curr != nullptr){
    if(curr->IsFull() == false){// If the car is full goes to the next one
      curr->AddPassenger(passenger);
      return;
    }
      curr = curr->m_next;
      
  
}
}


void Train::DisembarkPassengers(){
  unsigned int i = 0;
  int Disembarked = 0;
  Car* curr = m_head;
  Stop* currentStop = m_route->GetCurrentStop();
    while(curr != nullptr){
      for( i = 0; i< curr->m_passengers.size();i++){// Loops through the vectors and checks to see of any passenger has rech it's destanation
	if(curr->m_passengers[i]->GetFinalDestination() == currentStop->GetName()){//If it does then then remove the passnger by first delteling it then erase the passenger

	  cout<<curr->m_passengers[i]->GetName()<<" Disembark the Trains (Destination: "<<curr->m_passengers[i]->GetFinalDestination()<<" )"<<endl;
	  delete curr->m_passengers[i];
	  curr->m_passengers.erase(curr->m_passengers.begin() + i);// Get rid of the passenger by erasing it
	  Disembarked ++;
	}
       
      }
      curr = curr->m_next;
 
  }
    cout<<Disembarked<<" passenger disemabrked"<<endl;

}

void Train::TravelToNextStop(){
  Stop* currentStop = m_route->GetCurrentStop();
  Stop* nextStop = currentStop->GetNextStop();
  if(nextStop->GetNextStop() == nullptr){// stop the current stop is moving to ,  when it's next stop is nullptr and such is arrving at the last stop tell the user that
    
    m_route->SetCurrentStop(nextStop);
    
    Stop* ArriviedStop = m_route->GetCurrentStop();
    cout<<"Arriving at "<<ArriviedStop->GetName()<<endl;
    cout<<"You have reach the end of the route, would you like to reverse the route "<<endl;
  }
  else{
    m_route->SetCurrentStop(nextStop);// Moves the stop up one to the netStop
    Stop* ArriviedStop = m_route->GetCurrentStop();
    cout<<"Arriving at "<<ArriviedStop->GetName()<<endl;

  }
}


void Train::TurnTrainAround(){
  Stop* currentStop = m_route->GetCurrentStop();
  if(currentStop->GetNextStop() == nullptr){//If the the route is at the end reverse it
    m_route->ReverseRoute();
  }
  else if (currentStop->GetNextStop() != nullptr){//Valid validation, if the the reoute is not at the end stop it will not reverse
    cout<<"You have not reach the end of the route please try it at the end of the route"<<endl;
  }
}


bool Train::IsTrainFull(){
  
  
  Car *curr = m_head;
  
  while(curr != nullptr){

    if(curr->IsFull() == true){// If the car is full goes to the next car to check to see
      curr = curr->m_next;
    }
    
    else if (curr->IsFull() == false){// If the car is not full then return false
      return false;
      }
  }
  return true;
  
  
}
