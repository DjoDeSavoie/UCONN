//
//  ECElevatorSim.cpp
//  
//
//  Created by Yufeng Wu on 6/27/23.
//  Elevator simulation


#include "ECElevatorSim.h"

using namespace std;

#include "ECElevatorSim.h"
#include <iostream>
#include <vector>

using namespace std;

// Constructor for initializing the elevator simulation
ECElevatorSim::ECElevatorSim(int numFloors, vector<ECElevatorSimRequest> &listRequests)
    : numFloors(numFloors), requests(listRequests), currFloor(1), currDir(EC_ELEVATOR_STOPPED), currentTime(0)
{
}

// Destructor for cleaning up resources
ECElevatorSim::~ECElevatorSim()
{
    // Clean up if necessary
}

// Simulate method: Processes requests up to a given time period (lenSim)
void ECElevatorSim::Simulate(int lenSim)
{
    // Iterate over time from 0 to lenSim-1
    for (currentTime = 0; currentTime < lenSim; ++currentTime) {
        // Process requests made at the current time
        for (auto &req : requests) {
            if (req.GetTime() == currentTime) {
                // Handle the request based on its type
                if (req.IsMaintenanceStart()) {
                    // Maintenance start: Stop the elevator
                    SetCurrDir(EC_ELEVATOR_STOPPED);
                }
                else if (req.IsMaintenanceEnd()) {
                    // Maintenance end: Continue normal operations
                    SetCurrDir(EC_ELEVATOR_STOPPED);
                }
                else {
                    // Normal request: Either floor request or inside request
                    if (!req.IsFloorRequestDone()) {
                        // Stage 1: Waiting for the elevator at the floor
                        if (req.IsGoingUp() && currFloor < req.GetFloorSrc()) {
                            SetCurrDir(EC_ELEVATOR_UP);
                        }
                        else if (!req.IsGoingUp() && currFloor > req.GetFloorSrc()) {
                            SetCurrDir(EC_ELEVATOR_DOWN);
                        }
                    }
                    else if (!req.IsServiced()) {
                        // Stage 2: Passenger is inside the elevator, go to destination floor
                        if (currFloor < req.GetFloorDest()) {
                            SetCurrDir(EC_ELEVATOR_UP);
                        }
                        else if (currFloor > req.GetFloorDest()) {
                            SetCurrDir(EC_ELEVATOR_DOWN);
                        }
                    }
                }
            }
        }

        // Move the elevator based on its current direction
        if (currDir == EC_ELEVATOR_UP && currFloor < numFloors) {
            SetCurrFloor(currFloor + 1);
        }
        else if (currDir == EC_ELEVATOR_DOWN && currFloor > 1) {
            SetCurrFloor(currFloor - 1);
        }

        // After processing, check if any requests have been serviced
        for (auto &req : requests) {
            if (req.GetRequestedFloor() == currFloor) {
                if (!req.IsFloorRequestDone()) {
                    req.SetFloorRequestDone(true);  // Passenger has entered the elevator
                    req.SetArriveTime(currentTime);
                }
                else if (!req.IsServiced() && req.GetFloorDest() == currFloor) {
                    req.SetServiced(true);  // Passenger reached the destination
                }
            }
        }
    }
}

// Getter for current floor
int ECElevatorSim::GetCurrFloor() const
{
    return currFloor;
}

// Setter for current floor
void ECElevatorSim::SetCurrFloor(int f)
{
    if (f >= 1 && f <= numFloors) {
        currFloor = f;
    }
}

// Getter for current direction
EC_ELEVATOR_DIR ECElevatorSim::GetCurrDir() const
{
    return currDir;
}

// Setter for current direction
void ECElevatorSim::SetCurrDir(EC_ELEVATOR_DIR dir)
{
    currDir = dir;
}





