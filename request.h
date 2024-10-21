/**
 * @file request.h
 * @brief Defines the Request struct to hold web request data.
 * 
 * This header contains the declaration of the Request struct, which holds
 * the necessary data for processing a request in the load balancer.
 */


#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;
//Request class


/**
 * @struct request
 * @brief A structure to hold a web request.
 * 
 * This struct stores the IP addresses, job type, and time required to process a request.
 */


struct request {
    string ip_in;
    string ip_out;
    int time;
    char job;

    /**
     * @brief Constructor for request.
     * 
     * Initializes a request with the given IP addresses, time, and job type.
     * 
     * @param in Incoming IP address.
     * @param out Outgoing IP address.
     * @param t Time required to process.
     * @param j Job type.
     */


    request(string in, string out, int t, char j) {
        this->ip_in = in;
        this->ip_out = out;
        this->time = t;
        this->job = j;
    }

};

#endif // REQUEST_H