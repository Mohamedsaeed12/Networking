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
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-module.h"
#include "ns3/flow-monitor-helper.h"

// Default Network Topology
//
// 10.1.1.0
// n0 -------------- n1
// point-to-point
//

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FirstScriptExample");

int
main(int argc, char* argv[])
{
    CommandLine cmd(__FILE__);
    cmd.Parse(argc, argv);
    
    Time::SetResolution(Time::NS);
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    // Create nodes
    NodeContainer nodes;
    nodes.Create(2);
    
    // Configure point-to-point link
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
    
    NetDeviceContainer devices;
    devices = pointToPoint.Install(nodes);
    
    // Install internet stack
    InternetStackHelper stack;
    stack.Install(nodes);
    
    // Assign IP addresses
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);
    
    // Create UDP echo servers
    UdpEchoServerHelper echoServer1(9);
    UdpEchoServerHelper echoServer2(10);
    
    ApplicationContainer serverApps0 = echoServer1.Install(nodes.Get(1));
    serverApps0.Start(Seconds(1.0));
    serverApps0.Stop(Seconds(12.0));
    
    ApplicationContainer serverApps1 = echoServer2.Install(nodes.Get(1));
    serverApps1.Start(Seconds(1.0));
    serverApps1.Stop(Seconds(12.0));
    
    // Create UDP echo clients
    UdpEchoClientHelper echoClient1(interfaces.GetAddress(1), 9);
    UdpEchoClientHelper echoClient2(interfaces.GetAddress(1), 10);
    
    echoClient1.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient1.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient1.SetAttribute("PacketSize", UintegerValue(1024));
    
    echoClient2.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient2.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient2.SetAttribute("PacketSize", UintegerValue(1024));
    
    // Install client applications
    ApplicationContainer clientApps0 = echoClient1.Install(nodes.Get(0));
    // Measure throughput
    clientApps0.Start(Seconds(2.0));
    clientApps0.Stop(Seconds(10.0));
    
    ApplicationContainer clientApps1 = echoClient2.Install(nodes.Get(0));
    // Measure throughput
    clientApps1.Start(Seconds(2.0));
    clientApps1.Stop(Seconds(10.0));
    
    // Set simulation stop time
    Simulator::Stop(Seconds(11.0));
    
    // Log messages
    NS_LOG_ERROR("This is my Error message");
    NS_LOG_WARN("This is my Warning message");
    NS_LOG_INFO("This is my Information message");
    NS_LOG_DEBUG("This is for Debug");
    
    // Enable ASCII tracing
    AsciiTraceHelper ascii;
    pointToPoint.EnableAsciiAll(ascii.CreateFileStream("myfirst.tr"));
    
    // Configure mobility
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                "MinX", DoubleValue(0.0),
                                "MinY", DoubleValue(0.0),
                                "DeltaX", DoubleValue(5.0),
                                "DeltaY", DoubleValue(10.0),
                                "GridWidth", UintegerValue(3),
                                "LayoutType", StringValue("RowFirst"));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(nodes);
    
    // Configure animation
    AnimationInterface anim("lab4.xml");
    anim.SetConstantPosition(nodes.Get(0), 1, 30);
    anim.SetConstantPosition(nodes.Get(1), 50, 30);
    
    // Install flow monitor
    Ptr<FlowMonitor> flowMonitor;
    FlowMonitorHelper flowHelper;
    flowMonitor = flowHelper.InstallAll();
    
    // Enable PCAP tracing
    pointToPoint.EnablePcapAll("lab4Pcap");
    
    // Run simulation
    Simulator::Run();
    
    // Serialize flow monitor results
    flowMonitor->SerializeToXmlFile("lab4assignment.xml", true, true);
    
    // Clean up
    Simulator::Destroy();

    return 0;
}