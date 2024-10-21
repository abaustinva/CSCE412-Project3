/**
 * @file load_balancer.h
 * @brief Defines the LoadBalancer class for managing web servers and requests.
 * 
 * This header contains the declaration of the LoadBalancer class, which manages
 * a queue of requests and distributes them among multiple web servers. It also
 * dynamically scales the number of web servers based on the load.
 */


#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include "webservers.h"
#include <vector>
#include <queue>
#include <random>
#include <fstream>

/**
 * @class loadBalancer
 * @brief A class to manage load balancing between web servers.
 * 
 * This class is responsible for maintaining a queue of requests, distributing them
 * among the available web servers, and dynamically scaling the number of servers
 * to avoid overload.
 */


class loadBalancer {
    public:
        queue<request> requests;
        vector<WebServer> servers;
        int serverThreshold;
        int currentCycle;  // Track current cycle number

    /**
     * @brief Constructor for loadBalancer.
     * 
     * Initializes the load balancer with the specified number of web servers.
     * 
     * @param numServers Number of web servers to initialize.
     */

        loadBalancer(int numServers) {
            currentCycle = 0;
            for (int i = 0; i < numServers; i++) {
                servers.push_back(WebServer(i+1));
            }
        }

    /**
     * @brief Distribute requests to web servers.
     * 
     * This function distributes requests from the queue to the available web servers.
     * It ensures that the simulation does not exceed the specified time limit.
     * 
     * @param outFile Output file stream for logging.
     * @param simulationTime The total time for the simulation in cycles.
     * @return bool Returns true if simulation should continue, false if time limit is reached.
     */

        // Returns true if simulation should continue, false if time limit reached
        bool distributeRequest(ofstream &outFile, int simulationTime) {
            for (auto &server : servers) {
                if (!requests.empty()) {
                    request req = requests.front();
                    
                    // Check if processing this request would exceed simulation time
                    if (currentCycle + req.time > simulationTime) {
                        return false;  // Stop if we would exceed time limit
                    }
                    
                    requests.pop();
                    server.processRequest(req, outFile);
                    currentCycle += req.time;  // Advance time by request processing time
                    
                    outFile << "Current cycle: " << currentCycle << " / " << simulationTime << "\n";
                    outFile << requests.size() << " requests in the queue.\n";
                }
            }
            scaleServers(outFile);
            return currentCycle < simulationTime;
        }

        // Rest of the class implementation remains the same
        void scaleServers(ofstream &outFile) {
            int queueSize = requests.size();
            int numServers = servers.size();
            int targetServers = (queueSize + 2) / 3;
            //adding servers to maintain 3:1 ratio
            while (numServers < targetServers) {
                int newServerId = servers.size() + 1;
                servers.push_back(WebServer(newServerId));
                cout << "Added WebServer " << newServerId << " to maintain 3:1 ratio.\n";
                outFile << "Added WebServer " << newServerId << " to maintain 3:1 ratio.\n";
                numServers++;
            }
            //removing servers to maintain 3:1 ratio
            while (numServers > targetServers && numServers > 1) {
                cout << "Removed WebServer " << servers.back().id << " to maintain 3:1 ratio.\n";
                outFile << "Removed WebServer " << servers.back().id << " to maintain 3:1 ratio.\n";
                servers.pop_back();
                numServers--;
            }
        }

        bool hasPendingRequests() {
            return !requests.empty();
        }

        int getCurrentCycle() {
            return currentCycle;
        }
};

#endif // LOADBALANCER_H