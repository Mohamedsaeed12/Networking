# Dual CSMA + Point-to-Point Topology Simulation (NS-3)

This project simulates a network topology using NS-3 with two CSMA LANs connected by a point-to-point link. It demonstrates UDP echo communication between nodes across the topology, with animation and packet capture support.

## Topology Overview

```
10.1.1.0
n7 n6 n5 n0 -------------- n1 n2 n3 n4
 |  |  |  |   point-to-point   |  |  |  |
 ================             ================
      LAN 0                        LAN 1
```
- **LAN 0**: n0, n5, n6, n7 (CSMA, 10Mbps)
- **LAN 1**: n1, n2, n3, n4 (CSMA, 100Mbps)
- **n0 <-> n1**: Point-to-point link (10Mbps, 1.5ms delay)

## Features
- Two CSMA LANs with configurable node counts
- Point-to-point backbone
- UDP Echo server/client demonstration
- NetAnim XML animation output
- PCAP and ASCII tracing
- Mobility model for visualization

## Requirements
- **NS-3** (version 3.30+ recommended)
- C++ compiler (g++/clang++)

## Installation

### Install NS-3 (Linux/WSL/macOS)
```bash
sudo apt-get update
sudo apt-get install ns3-dev
```
Or build from source:
```bash
git clone https://gitlab.com/nsnam/ns-3-dev.git
cd ns-3-dev
./waf configure
./waf build
```

### Windows
- Use WSL and follow Linux instructions, or
- Use the official NS-3 Docker image:
```bash
docker pull nsnam/ns-3-dev
docker run -it nsnam/ns-3-dev
```

## Usage

1. **Copy the source file to your NS-3 scratch directory:**
   ```bash
   cp lab5_dual_csma_p2p_topology.cc /path/to/ns-3-dev/scratch/
   cd /path/to/ns-3-dev
   ```
2. **Build and run:**
   ```bash
   ./waf --run scratch/lab5_dual_csma_p2p_topology
   ```

## Output Files
- `mysecond_anim.xml` — NetAnim animation file
- `second-*.pcap`, `secondcsma0-*.pcap`, `secondcsma1-*.pcap` — Packet capture files

## Customization
- Change the number of CSMA nodes with `--nCsma0` and `--nCsma1` command-line arguments.
- Adjust data rates, delays, and simulation time in the source code as needed.

## Troubleshooting
- **Header errors:** Make sure NS-3 is installed and your include paths are set up in your IDE.
- **PCAP/animation not generated:** Ensure you have write permissions in the directory.
- **Visualization:** Use NetAnim to open `mysecond_anim.xml`:
  ```bash
  sudo apt-get install ns3-netanim
  netanim mysecond_anim.xml
  ```

## References
- [NS-3 Documentation](https://www.nsnam.org/documentation/)
- [NetAnim](https://www.nsnam.org/docs/netanim/)