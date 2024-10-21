
/**
 * @file webservers.h
 * @brief Defines the WebServer class to handle web requests.
 * 
 * This header contains the declaration of the WebServer class, which processes
 * requests assigned by the load balancer and logs the results.
 */


#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"

#include <iostream>
#include <fstream>
using namespace std;
// WebServer class


/**
 * @class WebServer
 * @brief A class to simulate a web server processing requests.
 * 
 * This class represents a web server that processes requests from the load balancer.
 * It logs the details of each processed request.
 */
class WebServer {
    
 public:
    int id;
    /**
     * @brief Constructor for WebServer.
     * 
     * Initializes the web server with a specific ID.
     * 
     * @param id ID of the web server.
     */
    WebServer(int id) {
        this->id = id;
    }
// Process request function
// This function takes a request object and an ofstream object as arguments.

    /**
     * @brief Processes a web request.
     * 
     * Takes a request object and processes it, logging the details to the output file.
     * 
     * @param request The web request to process.
     * @param outFile Output file stream for logging.
     */

    void processRequest(request request, ofstream &outFile) {
        cout << "WebServer " << id << " processing request from " 
                  << request.ip_in << " to " << request.ip_out 
                  << " for job type " << request.job 
                  << " taking " << request.time << " cycles." << endl;



        outFile << "WebServer " << id << " processing request from " 
                  << request.ip_in << " to " << request.ip_out 
                  << " for job type " << request.job 
                  << " taking " << request.time << " cycles." << endl;
    
    }


};





#endif