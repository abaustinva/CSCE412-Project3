/**
 * @file main.cpp
 * @brief This is the main driver program for the load balancer simulation.
 * 
 * This file contains the main function which initializes the simulation, 
 * sets up the load balancer, and runs the simulation for the specified 
 * number of clock cycles.
 */

/**
 * @brief Main function that runs the load balancer simulation.
 * 
 * This function sets up the number of servers, the duration of the simulation,
 * and manages the distribution of requests.
 * 
 * @return int Returns 0 if the program executes successfully.
 */

#include <iostream>
#include "load_balancer.h"
#include <random>
#include <fstream>

using namespace std;

// Helper function to generate random IPs

/**
 * @brief Helper function to generate random IP addresses.
 * 
 * This function generates a random IPv4 address in the format xxx.xxx.xxx.xxx
 * using uniformly distributed random numbers.
 * 
 * @return string A randomly generated IP address.
 */




string generateRandomIP() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);
    return to_string(dis(gen)) + "." + to_string(dis(gen)) + "." + to_string(dis(gen)) + "." + to_string(dis(gen));
}

// Helper function to generate random processing times

/**
 * @brief Helper function to generate random processing times.
 * 
 * This function generates a random processing time between 1 and 10 clock cycles.
 * 
 * @return int A randomly generated time in clock cycles.
 */
int generateRandomTime() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10); // time between 1 and 10 cycles
    return dis(gen);
}




// Helper function to generate random job types
/**
 * @brief Helper function to generate random job types.
 * 
 * This function randomly assigns either 'P' for processing or 'S' for streaming
 * as the job type.
 * 
 * @return char The job type ('P' for processing, 'S' for streaming).
 */
char generateRandomJobType() {
    return (rand() % 2 == 0) ? 'P' : 'S';
}




// Function to randomly add new requests during the simulation
/**
 * @brief Function to randomly add new requests during the simulation.
 * 
 * This function provides a 10% chance of adding a new request during each cycle of the simulation.
 * 
 * @return bool Returns true if a new request is added, false otherwise.
 */
bool addNewRequestRandomly() {
    return (rand() % 10 < 1);  // 10% chance of adding a new request
}


int main() {
    int numServers;
    int simulationTime;

    cout << "Enter number of web servers: ";
    cin >> numServers;
    cout << "Enter simulation time (in clock cycles): ";
    cin >> simulationTime;

    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    loadBalancer lb(numServers);

    // Generate initial requests (100 * numServers)
    for (int i = 0; i < numServers * 100; ++i) {
        string ip_in = generateRandomIP();
        string ip_out = generateRandomIP();
        int time = generateRandomTime();
        char job_type = generateRandomJobType();
        lb.requests.push(request(ip_in, ip_out, time, job_type));
    }

    // Simulate until we reach the time limit
    bool continueSimulation = true;
    while (continueSimulation && (lb.getCurrentCycle() < simulationTime)) {
        continueSimulation = lb.distributeRequest(outFile, simulationTime);

        // Randomly add new requests during the simulation
        if (addNewRequestRandomly()) {
            string ip_in = generateRandomIP();
            string ip_out = generateRandomIP();
            int time = generateRandomTime();
            char job_type = generateRandomJobType();
            lb.requests.push(request(ip_in, ip_out, time, job_type));
            cout << "New request added to the queue.\n";
            outFile << "New request added to the queue.\n";
            outFile << lb.requests.size() << " requests in the queue.\n";
        }
    }

    // Output final statistics
    cout << "\nFinal Statistics:\n";
    cout << "Simulation ended at cycle: " << lb.getCurrentCycle() << " / " << simulationTime << endl;
    
    outFile << "\nFinal Statistics:\n";
    outFile << "Simulation ended at cycle: " << lb.getCurrentCycle() << " / " << simulationTime << endl;

    if (lb.hasPendingRequests()) {
        cout << "Simulation ended with " << lb.requests.size() << " pending requests." << endl;
        outFile << "Simulation ended with " << lb.requests.size() << " pending requests." << endl;
    } else {
        cout << "Simulation completed. All requests processed." << endl;
        outFile << "Simulation completed. All requests processed." << endl;
    }

    outFile.close();
    return 0;
}