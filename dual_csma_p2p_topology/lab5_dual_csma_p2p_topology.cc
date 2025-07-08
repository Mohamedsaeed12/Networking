/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-module.h"

// Default Network Topology
//
// 10.1.1.0
// n7 n6 n5 n0 -------------- n1 n2 n3 n4
// | | | | point-to-point | | | |
// ================ ================
// LAN 10.1.2.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SecondScriptExample");

int main(int argc, char* argv[])
{
    bool verbose = true;
    uint32_t nCsma0 = 3;
    uint32_t nCsma1 = 3;

    CommandLine cmd(__FILE__);
    cmd.AddValue("nCsma0", "Number of \"extra\" CSMA nodes/devices", nCsma0);
    cmd.AddValue("nCsma1", "Number of \"extra\" CSMA nodes/devices", nCsma1);
    cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);
    cmd.Parse(argc, argv);

    if (verbose) {
        LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
        LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

    nCsma0 = nCsma0 == 0 ? 1 : nCsma0;
    nCsma1 = nCsma1 == 0 ? 1 : nCsma1;

    // Create point-to-point nodes
    NodeContainer p2pNodes;
    p2pNodes.Create(2);

    // Create CSMA nodes
    NodeContainer csmaNodes0, csmaNodes1;
    csmaNodes0.Add(p2pNodes.Get(0));
    csmaNodes0.Create(nCsma0);
    csmaNodes1.Add(p2pNodes.Get(1));
    csmaNodes1.Create(nCsma1);

    // Configure point-to-point link
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("1.5ms"));

    NetDeviceContainer p2pDevices;
    p2pDevices = pointToPoint.Install(p2pNodes);

    // Configure CSMA channels
    CsmaHelper csma0, csma1;
    csma0.SetChannelAttribute("DataRate", StringValue("10Mbps"));
    csma0.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6.5)));
    csma1.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma1.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6)));

    NetDeviceContainer csmaDevices0, csmaDevices1;
    csmaDevices0 = csma0.Install(csmaNodes0);
    csmaDevices1 = csma1.Install(csmaNodes1);

    // Install internet stack
    InternetStackHelper stack;
    stack.Install(csmaNodes1);
    stack.Install(csmaNodes0);

    // Assign IP addresses
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer p2pInterfaces = address.Assign(p2pDevices);

    address.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer csmaInterfaces0 = address.Assign(csmaDevices0);

    address.SetBase("10.1.9.0", "255.255.255.0");
    Ipv4InterfaceContainer csmaInterfaces1 = address.Assign(csmaDevices1);

    // Set up UDP echo server on last csma1 node
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(csmaNodes1.Get(nCsma1));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(12.0));

    // Set up UDP echo client on last csma0 node
    UdpEchoClientHelper echoClient(csmaInterfaces1.GetAddress(nCsma1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(10));
    echoClient.SetAttribute("Interval", TimeValue(MilliSeconds(20.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));
    ApplicationContainer clientApps = echoClient.Install(csmaNodes0.Get(3));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(11.0));

    // Enable routing
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Enable PCAP tracing
    pointToPoint.EnablePcapAll("second");
    csma0.EnablePcap("secondcsma0", csmaDevices0.Get(0), true);
    csma1.EnablePcap("secondcsma1", csmaDevices1.Get(0), true);

    // Set up mobility and animation
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
        "MinX", DoubleValue(0.0),
        "MinY", DoubleValue(0.0),
        "DeltaX", DoubleValue(5.0),
        "DeltaY", DoubleValue(10.0),
        "GridWidth", UintegerValue(3),
        "LayoutType", StringValue("RowFirst"));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(csmaNodes0);
    mobility.Install(csmaNodes1);

    AnimationInterface anim("mysecond_anim.xml");
    anim.SetConstantPosition(csmaNodes0.Get(0), 15, 10);
    anim.SetConstantPosition(csmaNodes0.Get(1), 10, 20);
    anim.SetConstantPosition(csmaNodes0.Get(2), 5, 20);
    anim.SetConstantPosition(csmaNodes0.Get(3), 1, 20);

    anim.SetConstantPosition(csmaNodes1.Get(0), 25, 10);
    anim.SetConstantPosition(csmaNodes1.Get(1), 30, 20);
    anim.SetConstantPosition(csmaNodes1.Get(2), 35, 20);
    anim.SetConstantPosition(csmaNodes1.Get(3), 40, 20);

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}