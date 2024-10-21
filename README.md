# Load Balancer Simulation

## Overview
This project implements a dynamic load balancer simulation that distributes web requests across multiple servers while maintaining efficient resource utilization. The simulation includes automatic scaling of server instances based on request queue size and handles request processing within a specified time limit.

## Files Structure
- `load_balancer.h`: Main load balancer implementation
- `webservers.h`: Web server class implementation
- `request.h`: Request structure definition
- `main.cpp`: Main program and simulation controller

## Features
- Dynamic server scaling based on request queue size (3:1 ratio)
- Random request generation with varied processing times
- Time-based simulation with cycle tracking
- Automatic load distribution across available servers
- Server addition/removal based on workload
- Detailed logging to output file

## Usage

### Compilation
g++ main.cpp -o load_balancer_sim

### Running the Simulation
./load_balancer_sim

### Input Parameters

- Number of initial web servers
- Total simulation time (in cycles)

### Output

- Console output for real-time monitoring
- Detailed logs in output.txt including:

- Request processing details
- Server scaling events
- Current cycle count
- Queue status
- Final statistics


### Main Loop 

- Distributes requests to available servers
- Checks time constraints before processing
- Scales servers based on queue size
- Randomly adds new requests (10% chance per cycle)
- Updates and logs statistics