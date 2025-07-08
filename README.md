# Networking Projects Repository

This repository contains a collection of networking projects and labs, including:
- Python socket programming examples (HTTP server, TCP echo server)
- NS-3 network simulation scenarios (UDP echo, dual CSMA + point-to-point topologies)

## Repository Structure

```
networking/
├── NetworkPA1/                  # Python networking examples
│   ├── simple_http_server.py    # HTTP file server (was networkPA1.py)
│   ├── tcp_echo_server.py       # TCP echo server (was Problem12.py)
│   ├── helloworld.html          # Example HTML file
│   ├── notfound.html            # 404 error page
│   ├── Screenshot ...png        # Output screenshots
│   └── README.md                # Details for Python projects
│
├── NS-3 UDP Echo with FlowMonitor/
│   ├── lab4_udp_echo_flowmonitor.cc # NS-3 UDP echo simulation
│   └── README.md                    # Details for this simulation
│
├── dual_csma_p2p_topology/
│   ├── lab5_dual_csma_p2p_topology.cc # NS-3 dual CSMA + P2P simulation
│   └── README.md                      # Details for this simulation
│
└── README.md                      # (This file)
```

## Quick Start

### Python Projects
- Go to `NetworkPA1/` and see its README for details.
- Requirements: Python 3.x (no extra packages)
- Example:
  ```bash
  cd NetworkPA1
  python simple_http_server.py
  # or
  python tcp_echo_server.py
  ```

### NS-3 Simulations
- Each simulation is in its own folder with a README and instructions.
- Requirements: [NS-3 network simulator](https://www.nsnam.org/)
- Example (after installing NS-3):
  ```bash
  cd NS-3\ UDP\ Echo\ with\ FlowMonitor
  cp lab4_udp_echo_flowmonitor.cc /path/to/ns-3-dev/scratch/
  cd /path/to/ns-3-dev
  ./waf --run scratch/lab4_udp_echo_flowmonitor
  ```

## Requirements
- Python 3.x (for Python projects)
- NS-3 (for C++ simulation projects)
- C++ compiler (g++/clang++) for NS-3

## How to Use This Repository
1. Browse each subfolder for a specific project or lab.
2. Each subfolder contains its own README with detailed instructions.
3. Follow the setup and run instructions for each project type.

## Additional Resources
- [NS-3 Documentation](https://www.nsnam.org/documentation/)
- [Python socket documentation](https://docs.python.org/3/library/socket.html)

---

**This repository is for educational and demonstration purposes.**

For more details, see the README in each project folder.
