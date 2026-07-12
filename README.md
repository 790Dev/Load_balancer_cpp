# Layer-7 HTTP Load Balancer

A production-style Layer-7 HTTP load balancer built from scratch in C++. It features a multithreaded architecture, active health checking, dynamic routing algorithms, and a real-time monitoring dashboard.

## Key Features

- **Multithreaded Request Handling**: Utilizes a custom Thread Pool with 20 worker threads for high-concurrency request processing.
- **Dynamic Routing Algorithms**: Supports `Round-Robin` and `Least-Connections`, switchable at runtime without restarting the server.
- **Active Health Checks**: Dedicated background thread polls backend health every 5 seconds. Unhealthy nodes are automatically skipped for zero-downtime failover.
- **HTTP Reverse Proxy**: Parses raw HTTP requests and seamlessly forwards them to backend servers, relaying the responses back to the client.
- **Real-Time Observability**: Built-in Admin API exposing metrics (total requests, active connections, fail rates).
- **Web Dashboard**: A Node.js-based UI to monitor metrics, view per-backend request distribution, and toggle algorithms in real-time.

## Architecture Layout

1. **Load Balancer (C++)**: Listens on Port `8080`. Distributes incoming HTTP traffic.
2. **Backend Services (Node.js/Docker)**: 3 containerized backend servers listening on ports `5001`, `5002`, and `5003`.
3. **Admin Dashboard (Node.js)**: Runs on Port `3000` to visualize the load balancer's state and metrics.

## Getting Started

### Prerequisites
- C++ Compiler (supporting C++11 or higher) & CMake
- Node.js (v22+)
- Docker & Docker Compose (for backend nodes)

### 1. Start the Backend Servers
The backends are containerized for easy deployment and load testing.
```bash
docker-compose up --build -d
```

### 2. Run the Load Balancer
Compile and run the C++ load balancer from the `load_balancer` directory:
```bash
cd load_balancer
# Compile using CMake or your C++ IDE (e.g. MSVC, MinGW)
# Run the executable:
./load_balancer.exe
```
*(The load balancer will start listening on port 8080).*

### 3. Start the Dashboard
To monitor the traffic, start the web dashboard:
```bash
cd dashboard
npm install
node server.js
```
*(Visit `http://localhost:3000` in your browser).*

## Admin API Endpoints

The load balancer intercepts specific routes on port `8080` for monitoring and control:

- `GET /metrics` - Returns JSON with total requests, active connections, and failed requests.
- `GET /backends` - Returns JSON array of all registered backends, their health status, and handled request counts.
- `GET /health` - Basic health check endpoint for the load balancer itself.
- `GET /algorithm/round-robin` - Switches routing algorithm to Round Robin dynamically.
- `GET /algorithm/least-connection` - Switches routing algorithm to Least Connections dynamically.

## Configuration

Check `.env.example` for the standard configuration variables you can use:
```ini
LB_PORT=8080
LB_ALGORITHM=round-robin
DASHBOARD_PORT=3000
BACKEND_1_PORT=5001
BACKEND_2_PORT=5002
BACKEND_3_PORT=5003
```
