"""Launch as2_knowledge_graph node."""
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, EnvironmentVariable
from launch import LaunchDescription


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('namespace',
                              default_value=EnvironmentVariable(
                                  'AEROSTACK2_SIMULATION_DRONE_ID'),
                              description='Drone namespace'),

        Node(
            package="as2_knowledge_graph",
            executable="as2_knowledge_graph_node_server_main",
            name="knowledge_graph_server",
            namespace=LaunchConfiguration('namespace'),
            output="screen",
            emulate_tty=True,
        )
    ])
