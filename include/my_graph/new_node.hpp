#ifndef New_Node_hpp
#define New_Node_hpp

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "knowledge_graph/knowledge_graph.hpp"
#include "knowledge_graph/graph_utils.hpp"
#include "knowledge_graph_msgs/msg/content.hpp"
#include "knowledge_graph_msgs/msg/edge.hpp"
#include "knowledge_graph_msgs/msg/graph.hpp"
#include "knowledge_graph_msgs/msg/graph_update.hpp"
#include "knowledge_graph_msgs/msg/node.hpp"
#include "knowledge_graph_msgs/msg/property.hpp"
#include "my_graph/srv/create_node.hpp"
#include "my_graph/srv/create_edge.hpp"



using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class NewNode : public rclcpp::Node {
public:
  NewNode() : rclcpp::Node("my_knowledge_graph"){
    service_create_node_=this->create_service<my_graph::srv::CreateNode>("create_node", std::bind(&NewNode::createNode, this, _1,_2));
    service_create_edge_=this->create_service<my_graph::srv::CreateEdge>("create_edge", std::bind(&NewNode::createEdge, this, _1,_2));

    service_remove_node_=this->create_service<my_graph::srv::CreateNode>("remove_node", std::bind(&NewNode::removeNode, this, _1,_2));
    service_remove_edge_=this->create_service<my_graph::srv::CreateEdge>("remove_edge", std::bind(&NewNode::removeEdge, this, _1,_2));

    add_property_node_=this->create_service<my_graph::srv::CreateNode>("add_property_node", std::bind(&NewNode::addPropertyNode, this, _1,_2));
    add_property_edge_=this->create_service<my_graph::srv::CreateEdge>("add_property_edge", std::bind(&NewNode::addPropertyEdge, this, _1, _2));

    timer_ = this->create_wall_timer(20ms, std::bind(&NewNode::timerCallback, this));
  } 

private:
    std::shared_ptr<knowledge_graph::KnowledgeGraph> graph_;
    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Service<my_graph::srv::CreateNode>::SharedPtr service_create_node_;
    rclcpp::Service<my_graph::srv::CreateEdge>::SharedPtr service_create_edge_;
    rclcpp::Service<my_graph::srv::CreateNode>::SharedPtr service_remove_node_;
    rclcpp::Service<my_graph::srv::CreateEdge>::SharedPtr service_remove_edge_;
    rclcpp::Service<my_graph::srv::CreateNode>::SharedPtr add_property_node_;
    rclcpp::Service<my_graph::srv::CreateEdge>::SharedPtr add_property_edge_;

    
    bool request_name_received;   
    bool request_edge_received; 
    bool request_remove_node_received;   
    bool request_remove_edge_received; 
    size_t count_;  
  
    void createNode(const std::shared_ptr<my_graph::srv::CreateNode::Request> request ,const std::shared_ptr<my_graph::srv::CreateNode::Response> response );
    void createEdge(const std::shared_ptr<my_graph::srv::CreateEdge::Request> request,const std::shared_ptr<my_graph::srv::CreateEdge::Response> response );
    void removeNode(const std::shared_ptr<my_graph::srv::CreateNode::Request> request ,const std::shared_ptr<my_graph::srv::CreateNode::Response> response );
    void removeEdge(const std::shared_ptr<my_graph::srv::CreateEdge::Request> request,const std::shared_ptr<my_graph::srv::CreateEdge::Response> response );
    void addPropertyNode(const std::shared_ptr<my_graph::srv::CreateNode::Request> request ,const std::shared_ptr<my_graph::srv::CreateNode::Response> response );
    void addPropertyEdge(const std::shared_ptr<my_graph::srv::CreateEdge::Request> request,const std::shared_ptr<my_graph::srv::CreateEdge::Response> response );
    void timerCallback();
};


  
#endif