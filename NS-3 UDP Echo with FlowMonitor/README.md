# NS-3 UDP Echo with FlowMonitor

This project implements a UDP echo simulation using NS-3 with flow monitoring capabilities.

## Prerequisites

### NS-3 Installation

**Option 1: Package Manager (Recommended)**
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install ns3-dev

# CentOS/RHEL/Fedora
sudo yum install ns3-devel
# or
sudo dnf install ns3-devel

# macOS (using Homebrew)
brew install ns3
```

**Option 2: Build from Source**
```bash
# Clone NS-3 repository
git clone https://gitlab.com/nsnam/ns-3-dev.git
cd ns-3-dev

# Configure and build
./waf configure
./waf build

# Install (optional)
sudo ./waf install
```

**Option 3: Windows**
- Use WSL (Windows Subsystem for Linux) and follow Linux instructions
- Or use NS-3 Docker container:
```bash
docker pull nsnam/ns-3-dev
docker run -it nsnam/ns-3-dev
```

## Project Files

- `lab4_udp_echo_flowmonitor.cc` - Main NS-3 simulation file
- `README.md` - This documentation file

## Network Topology

```
10.1.1.0
n0 -------------- n1
point-to-point
```

The simulation creates:
- 2 nodes connected via point-to-point link
- 2 UDP echo servers on node 1 (ports 9 and 10)
- 2 UDP echo clients on node 0
- Flow monitoring for performance analysis

## Compilation and Execution

### Method 1: Using NS-3 Waf Build System
```bash
# Copy the source file to NS-3 scratch directory
cp lab4_udp_echo_flowmonitor.cc /path/to/ns-3-dev/scratch/

# Navigate to NS-3 directory
cd /path/to/ns-3-dev

# Build and run
./waf --run scratch/lab4_udp_echo_flowmonitor
```

### Method 2: Direct Compilation
```bash
# Compile with NS-3 libraries
g++ -o lab4_udp_echo_flowmonitor lab4_udp_echo_flowmonitor.cc -lns3-dev

# Run the simulation
./lab4_udp_echo_flowmonitor
```

## Output Files

The simulation generates several output files:
- `myfirst.tr` - ASCII trace file
- `lab4.xml` - Animation file for NetAnim
- `lab4Pcap-*.pcap` - PCAP files for packet analysis
- `lab4assignment.xml` - Flow monitor statistics

## Features

- **UDP Echo Servers**: Two servers on ports 9 and 10
- **UDP Echo Clients**: Two clients sending packets to servers
- **Flow Monitoring**: Performance analysis and statistics
- **Animation**: Visual representation using NetAnim
- **Tracing**: ASCII and PCAP trace files
- **Logging**: Multiple log levels (ERROR, WARN, INFO, DEBUG)

## Configuration

### Network Parameters
- Data Rate: 1 Mbps
- Delay: 2ms
- Network: 10.1.1.0/24

### Application Parameters
- Packet Size: 1024 bytes
- Interval: 1 second
- Max Packets: 1 per client
- Simulation Duration: 11 seconds

## Troubleshooting

### Header File Errors
If you see errors like `cannot open source file "ns3/..."`:
1. Ensure NS-3 is properly installed
2. Check your include paths in your IDE
3. For VS Code, add NS-3 include path to `c_cpp_properties.json`:
```json
{
    "configurations": [
        {
            "includePath": [
                "/usr/include/ns3",
                "/usr/local/include/ns3"
            ]
        }
    ]
}
```

### Compilation Errors
- Ensure all NS-3 modules are installed
- Check that you're using a compatible NS-3 version
- Verify C++ compiler is properly configured

## Analysis Tools

### View Trace Files
```bash
# View ASCII trace
cat myfirst.tr

# View PCAP files with Wireshark
wireshark lab4Pcap-*.pcap
```

### View Animation
```bash
# Install NetAnim if not already installed
sudo apt-get install ns3-netanim

# Run NetAnim
netanim lab4.xml
```

### Analyze Flow Statistics
The `lab4assignment.xml` file contains detailed flow statistics including:
- Throughput
- Delay
- Packet loss
- Jitter

## Dependencies

| Component | Purpose |
|-----------|---------|
| NS-3 Core | Basic simulation framework |
| NS-3 Applications | UDP echo applications |
| NS-3 Internet | Internet stack |
| NS-3 Network | Network devices |
| NS-3 Point-to-Point | Point-to-point links |
| NS-3 NetAnim | Animation support |
| NS-3 Mobility | Node positioning |
| NS-3 Flow Monitor | Performance monitoring |

## Additional Resources

- [NS-3 Documentation](https://www.nsnam.org/documentation/)
- [NS-3 Tutorial](https://www.nsnam.org/docs/tutorial/)
- [Flow Monitor Documentation](https://www.nsnam.org/docs/models/html/flow-monitor.html)
- [NetAnim Documentation](https://www.nsnam.org/docs/netanim/)







