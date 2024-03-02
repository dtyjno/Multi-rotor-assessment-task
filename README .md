# ros2学习日志
在ubuntu22.04环境下学习ros2
## ros2安装方法
[Ubuntu （Debian 软件包）]https://docs.ros.org/en/rolling/Installation/Ubuntu-Install-Debians.html  
[解决”Failed to connect to raw.githubusercontent.com“报错]https://www.guyuehome.com/37844  
1. 系统设置   
    1. 设置区域设置 

        确保你有一个支持的语言环境 UTF-8。 如果您处于最小环境（例如 docker 容器）中，则区域设置可能是最小 POSIX。 我们使用以下设置进行测试。但是，如果您使用其他 UTF-8 支持的区域设置，这应该没问题。

    2. 启用所需的存储库 
   
        您需要将 ROS 2 apt 存储库添加到您的系统中。
        首先确保 启用了 Ubuntu Universe 存储库 。

        现在使用 apt 添加 ROS 2 GPG 密钥。

        然后将存储库添加到源列表中。

    >安装开发工具（可选）   
    如果你打算构建 ROS 包或以其他方式进行开发，你也可以安装开发工具：  
    sudo apt update && sudo apt install ros-dev-tools

```sh
#1
locale  # check for UTF-8
sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
locale  # verify settings
#2
sudo apt install software-properties-common
sudo add-apt-repository universe
#curl: (7) Failed to connect to raw.githubusercontent.com port 443 after 15 ms: 拒绝连接

#sudo gedit /etc/hosts
#185.199.111.133 raw.githubusercontent.com

#sudo apt update && sudo apt install curl -y
#sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```
2. 安装 ROS 2 

    设置存储库后，更新 apt 存储库缓存。

    ROS 2 软件包建立在频繁更新的 Ubuntu 系统上。 始终建议您在安装新软件包之前确保系统是最新的。


    >警告
    >
    >由于 Ubuntu 22.04 的早期更新，重要的是 systemd 和 udev- 在安装 ROS 2 之前，会更新相关软件包。 在不升级的情况下将 ROS 2 的依赖项安装在新安装的系统上可能会触发 关键系统软件包的删除 。

    桌面安装（推荐）：ROS、RViz、演示、教程。  sudo apt install ros-rolling-desktop

    ROS-Base Install （Bare Bones）：通信库、消息包、命令行工具。 没有GUI工具。  sudo apt install ros-rolling-ros-base

    安装其他 RMW 实现（可选） 
    ROS 2 默认使用的中间件是 Fast DDS，但中间件 （RMW） 可以在运行时替换。 请参阅 的指南 有关如何使用多个 RMW
    设置环境 

    通过获取以下文件来设置环境。  
    (设置环境变量  
    $ source /opt/ros/rolling/setup.bash
    $ echo " source /opt/ros/rolling/setup.bash" >> ~/.bashrc 
    )
```sh
sudo apt update
sudo apt upgrade

sudo apt install ros-humble-desktop
#桌面安装（推荐）

# Replace ".bash" with your shell if you're not using bash
# Possible values are: setup.bash, setup.sh, setup.zsh
source /opt/ros/humble/setup.bash

##echo " source /opt/ros/humble/setup.bash" >> ~/.bashrc 
```

3. 尝试一些示例   
    如果安装了 ros-rolling-desktop 上面你可以尝试一些例子。

    在一个终端中，获取安装文件，然后运行 C++ talker：  
    ```bash
    #source /opt/ros/rolling/setup.bash
    ros2 run demo_nodes_cpp talker
    ```
    在另一个终端中，获取安装文件，然后运行 Python listener：  
    ```bash
    #source /opt/ros/rolling/setup.bash
    ros2 run demo_nodes_py listener
    ```
    您应该看到 talker 说它是 Publishing 消息和 listener 谚语 I heard 这些消息。 这将验证 C++ 和 Python API 是否正常工作。 


## 初学者：CLI 工具

### 配置环境
* ROS 2 依赖于使用 shell 环境组合工作区(workspace)概念。
    
* 1. 在每次打开新 shell 时获取安装文件  (每个新 shell 上运行```source /opt/ros/rolling/setup.bash```) 才能访问 ROS 2 命令，  
    2. 或者通过将 source 命令添加到 shell 启动脚本一次(```echo "source /opt/ros/rolling/setup.bash" >> ~/.bashrc```)来更轻松地实现针对不同版本的 ROS 2 或不同的软件包集进行开发。
* 使用以下命令确保您的环境已正确设置：```printenv | grep -i ROS```，检查变量是否像 ROS_DISTRO 和 ROS_VERSION 设置。```ROS_VERSION=2 ROS_PYTHON_VERSION=3 ROS_DISTRO=rolling```
 
https://docs.ros.org/en/rolling/Tutorials/Beginner-CLI-Tools/Configuring-ROS2-Environment.html

### 使用 turtlesim， ros2和 rqt（海龟仿真
* Turtlesim 是一款用于学习 ROS 2 的轻量级模拟器。 它说明了 ROS 2 在最基本的层面上做了什么，让您了解以后将如何处理真正的机器人或机器人模拟。
* ros2 工具是用户管理、反省和与 ROS 系统交互的方式。 它支持针对系统及其操作的不同方面的多个命令。 人们可能会用它来启动节点(node)、设置参数、收听主题(topic)等等。 ros2 工具是核心 ROS 2 安装的一部分。
* rqt 是 ROS 2 的图形用户界面 （GUI） 工具。 在 rqt 中完成的所有操作都可以在命令行上完成，但 rqt 提供了一种更用户友好的方式来操作 ROS 2 元素。

--==--
- turtlesim 
1. 安装 turtlesim （可跳过）
    为您的 ROS 2 发行版安装 turtlesim 软件包：

    检查是否已安装软件包：

    上面的命令应该返回 turtlesim 的可执行文件列表：
    ```turtlesim draw_square turtlesim mimic turtlesim turtle_teleop_key turtlesim turtlesim_node```
    ```bash
    sudo apt update
    sudo apt install ros-rolling-turtlesim
    
    ros2 pkg executables turtlesim
    ```
2. 启动turtlesim  
* 不要忘记在 您打开的每个新终端 中获取 ROS 2  
 
    想要运行ROS2中某个节点，我们可以使用ros2 run命令进行操作，启动turtlesim，终端中输入```ros2 run turtlesim turtlesim_node```出现模拟器窗口，中间有一只随机的龟龟。  
    您将看到来自节点(node)的消息：
    ```bash
    [INFO] [turtlesim]: Starting turtlesim with node name /turtlesim
    [INFO] [turtlesim]: Spawning turtle [turtle1] at x=[5.544445], y=[5.544445], theta=[0.000000]
    ```
    可以看到默认的名字和它生成的坐标。
1. 使用 turtlesim  
打开一个新终端，再次获取ROS 2。

    现在，您将运行一个新节点(node)来控制第一个节点(node)中的：```ros2 run turtlesim turtle_teleop_key```  
    - 此时，您应该打开三个窗口：一个正在运行的终端 turtlesim_node，终端运行 turtle_teleop_key 和 turtlesim 窗口。  
    排列这些窗口，以便您可以看到 turtlesim 窗口，但也让终端运行 turtle_teleop_key 活动，以便您可以在 Turtlesim 中控制。

    使用键盘上的箭头键来控制。 它将在屏幕上移动，使用其附加的“笔”绘制到目前为止所遵循的路径。

    >注意
    >
    >按下箭头键只会使移动一小段距离，然后停止。 这是因为，实际上，如果操作员失去了与机器人的连接，您不会希望机器人继续执行指令。

    您可以使用 list 相应命令的子命令：
    ```sh
    ros2 node list#查看节点信息
    #查看当前运行的ROS系统中都有哪些节点
    #ros2 node info /turtlesim 
    #加上一个info子命令，就可以知道某一个节点的详细信息

    ros2 topic list#查看话题信息
    #ros2 topic echo /turtle1/pose #还想看到某一个话题中的消息数据，加上echo子命令

    #ros2 topic pub --rate 1 /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}" 
    #控制海龟动起来，我们还可以直接通过命令行发布话题指令： 

    ros2 service list#发送服务请求
    #ros2 service call /spawn turtlesim/srv/Spawn "{x: 2, y: 2, theta: 0.2, name: ''}"
    #一只海龟太孤单，仿真器还提供改了一个服务——产生海龟，我们试一试服务调用，再来一只海龟：

    ros2 action list#发送动作目标
    #ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "theta: 3"
    #想要让海龟完成一个具体动作，比如转到指定角度，仿真器中提供的这个action可以帮上忙，通过命令行这样发送动作目标：

    #录制控制命令系统运行中的数据有很多，如果想要把某段数据录制下来，回到实验室再复现这段数据如何？ROS2中的rosbag功能还是很好用的，轻松实现数据的录制与播放$ ros2 bag record /turtle1/cmd_vel$ ros2 bag play rosbag2_2022_04_11-17_35_40/rosbag2_2022_04_11-17_35_40_0.db3
    ```
    使用 rqt 调用一些 turtlesim 服务并与turtlesim_node交互 
* rqt
1. 打开新终端进行安装 rqt 及其插件：
    ```sh
    sudo apt update
    sudo apt install ~nros-rolling-rqt*
    ```
2. 要运行 rqt：```rqt```  
选择 Plugins > Services > Service Caller  
使用服务下拉列表左侧的刷新按钮，确保 turtlesim 节点的所有服务都可用。
1.  尝试生成服务   
- 使用 rqt 来调用 ```/spawn``` 服务。 从它的名字可以猜到， /spawn 将在 turtlesim 窗口中创建另一个龟龟。

    1. 给新龟龟起一个独特的名字，比如 turtle2。在“表达式“行中的空单引号之间双击，您可以看到此表达式对应于 name 的值 name ，并且是 string 类型。  
    2. 接下来输入一些有效的坐标来生成新，例如 x = 1.0 和 y = 1.0。 
    3. 然后需要通过单击 rqt 窗口右上角的“呼叫“ 生成 turtle2
     
    在rqt 中刷新服务列表，你还会看到现在有与新 turtle 相关的服务 
  - 试用```/set_pen```服务
    1.   r 、 g 和 b 的值介于 0 和 255 之间，用于设置笔的颜色 turtle1 绘制， 宽度 设置线的粗细。

    要有 turtle1 用一条明显的红线绘制，将 r 的值更改为 255，将 width 的值更改为 width 5。 不要忘记在更新值后调用服务。 

    您可能还注意到，没有办法移动 turtle2。 那是因为没有 teleop 节点 turtle2。

4. 重新映射  
    您需要第二个远程操作节点才能控制 turtle2。 但是，如果您尝试运行与以前相同的命令，您会注意到这个命令还控制 turtle1。 更改此行为的方法是重新映射 cmd_vel 主题。

    在新终端中，获取 ROS 2，然后运行：

    ```sh
    ros2 run turtlesim turtle_teleop_key --ros-args --remap turtle1/cmd_vel:=turtle2/cmd_vel
    #更改cmd_vel主题并定位 turtle2
    ```

    现在，您可以移动 turtle2   
    当此终端处于活动状态时，并且 turtle1 当另一个终端运行时 turtle_teleop_key 处于活动状态。

### Understanding nodes
* ros2 graph
![ROS (2) graph](https://docs.ros.org/en/rolling/_images/Nodes-TopicandService.gif)
    *ROS 图*是一个由 ROS 2 元素组成的网络，它们同时处理数据。它包含所有*可执行文件*以及*它们之间的连接*如果您要将它们全部映射出来并可视化它们 
* 节点(node)  
    * **每个节点都应该负责一个单一的模块化目的**，例如控制车轮电机或从激光测距仪发布传感器数据。 
    * **每个节点都可以通过主题、服务、操作或参数从其他节点发送和接收数据**。 
1.  ROS2 运行   
    命令 ```ros2 run``` 从包启动可执行文件。  
    ```sh
    ros2 run <package_name> <executable_name>
    ```  
    此处，包名称为 turtlesim 可执行文件名称为 turtlesim_node，用ros2 node list查找节点名称 
2. ROS2 节点列表  
```ros2 node list``` 将显示所有正在运行的节点的名称。当您想要与节点交互时，或者当您的系统运行多个节点并需要跟踪它们时，这特别有用。  ```/turtlesim
/teleop_turtle```
1. 重新映射   
重新映射 允许您将默认节点属性（如节点名称、主题名称、服务名称等）重新分配给自定义值。 在上一教程中，您在 turtle_teleop_key 更改cmd_vel主题并定位 turtle2 。

    现在，让我们重新分配我们的 /turtlesim 节点。 在新终端中，运行以下命令：
    ```sh
    ros2 run turtlesim turtlesim_node --ros-args --remap __node:=my_turtle
    ```
    ```/my_turtle /turtlesim /teleop_turtle```  
    既然你再次在 Turtlesim 上打电话 ros2 run ，将打开另一个 TurtleSim 窗口。 但是，现在如果您返回您运行的终端 ros2 node list，然后再次运行它，您将看到三个节点名称
4. ROS2 节点信息  
 
    现在您已经知道了节点的名称，可以通过以下命令访问有关它们的更多信息：

    ros2 node info <node_name>

    要检查最新的节点， my_turtle，运行以下命令：

    ros2 node info /my_turtle

    ros2 node info 返回订阅者、发布者、服务和操作的列表。 即与该节点交互的 ROS 图连接。 

### Understanding topics
ROS 2 将复杂的系统分解为许多模块化节点。 
- 主题(topic)是 ROS 图的重要组成部分，它充当节点交换消息的总线。 
![topic](https://docs.ros.org/en/rolling/_images/Topic-SinglePublisherandSingleSubscriber.gif)
* 一个节点可以将数据发布到任意数量的主题，并同时订阅任意数量的主题。
* 主题是数据在节点之间移动的主要方式之一。
1. 打开一个新终端并运行：
ros2 run turtlesim turtlesim_node
打开另一个终端并运行：
ros2 run turtlesim turtle_teleop_key  
这些节点的名称是 /turtlesim 和 /teleop_turtle
2. rqt_graph 

    使用 rqt_graph 可视化不断变化的节点和主题，以及它们之间的联系。  

    要运行rqt_graph，请打开一个新终端并输入以下命令：```rqt_graph```  
    也可以通过打开 rqt 并选择 Plugins > Introspection > Node Graph 来打开rqt_graph  
    ![rqt_graph](https://docs.ros.org/en/rolling/_images/rqt_graph.png)
3. ROS2 主题列表  

    ```ros2 topic list``` 将返回系统中当前处于活动状态的所有主题的列表  
    ```ros2 topic list -t ```将返回相同的主题列表，这次主题类型附加在括号中
    - 这些属性，尤其是类型，是节点在主题上移动时知道它们正在谈论相同信息的方式。
4. ROS2 主题回声 
 
    ```ros2 topic echo <topic_name>```查看有关主题发布的数据  
    * /teleop_turtle 将数据发布到 /turtlesim 在 /turtle1/cmd_vel 主题，让我们使用 echo 要反省/turtle1/cmd_vel 主题，```ros2 topic echo /turtle1/cmd_vel```使用rqt_graph（去除勾选debug）查看到/_ros2cli_26646 是由我们刚刚运行的 echo 命令（数字可能不同）。 现在，您可以看到发布者/teleop_turtle正在通过 cmd_vel 主题，并且有两个订阅者/turtlesim和/_ros2cli_26646订阅了它。  
5. ROS2 主题信息

    ```ros2 topic info <topic_name>```  
    * 主题不必只是一对一的交流;它们可以是一对多、多对一或多对多。
    运行：

        ros2 topic info /turtle1/cmd_vel

        这将返回：

        Type: geometry_msgs/msg/Twist
    Publisher count: 1
    Subscription count: 2
6.  ROS2 接口展示

    * 节点使用消息通过主题发送数据。 发布者和订阅者必须发送和接收相同类型的消息才能进行通信。

    ros2 topic list -t 让我们知道每个主题使用的消息类型。cmd_vel 主题的类型geometry_msgs/msg/Twist意味着**在包装中 geometry_msgs 有一个 msg 叫 Twist**。 

    ```ros2 interface show <msg type>``` 在此类型上了解消息需要的数据结构。  

    ```ros2 interface show geometry_msgs/msg/Twist```  
    对于上面的消息类型，它会产生：
    ```sh
    This expresses velocity in free space broken into its linear and angular parts.

        Vector3  linear
                float64 x
                float64 y
                float64 z
        Vector3  angular
                float64 x
                float64 y
                float64 z
    ```
    这告诉您 /turtlesim node 期待一条包含两个向量的消息， linear 和 angular，每个元素有三个元素。  
    我们看到的数据 /teleop_turtle 传递给 /turtlesim 使用 echo 命令，它的结构相同： 
7. ROS2 主题发布

    ```ros2 topic pub <topic_name> <msg_type> '<args>'```有了消息结构，直接将数据发布到主题  
    '\<args\>' argument 是您将传递给主题的实际数据，位于您刚刚在上一节中发现的结构中。该参数需要以 YAML 语法输入。

    ```sh
    ros2 topic pub --once /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"
    ```
    --once是一个可选参数，意思是 "发布一条信息然后退出"。你将在终端看到以下输出：发布者：开始循环

    --rate 1 选项，它告诉 ros2 topic pub 以 1 Hz 的频率稳定地发布命令。  
    乌龟（通常也包括它要模拟的真实机器人）需要源源不断的指令才能持续运行。因此，要让乌龟持续移动，可以运行```ros2 topic pub --rate 1 /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y： 0.0, z: 0.0}, angular： {x: 0.0, y： 0.0, z: 1.8}}"```这里的区别在于去掉了--once 选项，增加了-- rate 选项
    echo on the pose ```ros2 topic echo /turtle1/pose```    
    可以看到 /turtlesim 节点也在向新 echo 节点订阅的 pose 主题发布信息。 
    
    在发布带有时间戳的信息时，pub 有两种方法来自动填写当前时间。对于带有 std_msgs/msg/Header 的信息，可将标题字段设置为auto，以填写stamp字段。
    ```bash
    # A Pose with reference coordinate frame and timestamp
    std_msgs/Header header
        builtin_interfaces/Time stamp
            int32 sec
            uint32 nanosec
        string frame_id
    Pose pose
        Point position
            float64 x
            float64 y
            float64 z
        Quaternion orientation
            float64 x 0
            float64 y 0
            float64 z 0
            float64 w 1
    ```
    ```sh
    ros2 topic pub /pose geometry_msgs/msg/PoseStamped '{header: "auto", pose: {position: {x: 1.0, y: 2.0, z: 3.0}}}'
    ```
    If the message does not use a full header, but just has a field with type builtin_interfaces/msg/Time, that can be set to the value now。
    ```sh
    # Measurement from an external time source not actively synchronized with the system clock.

    std_msgs/Header header      # stamp is system time for which measurement was valid
    builtin_interfaces/Time stamp
        int32 sec
        uint32 nanosec
        string frame_id
                                         # frame_id is not used

    builtin_interfaces/Time time_ref  # corresponding time from this external source
        int32 sec
        uint32 nanosec
    string source                     # (optional) name of time source
    ```
    ```sh
    ros2 topic pub /reference sensor_msgs/msg/TimeReference '{header: "auto", time_ref: "now", source: "dumy"}'
    ```
8. ```ros2 topic hz ``` 
    
    为了对该进程进行最后一次反省，您可以使用
    ```ros2 topic hz /turtle1/pose```
    它将返回 /turtlesim 节点向 pose 主题发布数据的速率数据。  
    平均速率 59.354
    最小： 0.005s 最大： 0.027s 0.027s std dev: 0.00284s window： 58  
    >请注意，您使用 ros2 topic pub --rate 1 将 turtle1/cmd_vel 的速率设置为稳定的 1 Hz。如果使用 turtle1/cmd_vel 而不是 turtle1/pose 运行上述命令，就会看到反映该速率的平均值。
9. 清理
此时，您将有很多节点正在运行。别忘了在每个终端输入 Ctrl+C 停止它们。
### Understanding services
* 服务(services)是 ROS 图中节点的另一种通信方式。 服务**基于主题的呼叫和响应模型**，而不是**发布者-订阅者模型**。 虽然主题允许节点订阅数据流并获得持续更新，但**服务仅在客户端专门调用它们时才提供数据**。 

    节点可以使用的服务在ROS2. 同一主题的一个方式的通信模式在一个节点发布的信息可通过一个或多个订户-服务是一个**请求/回应**的模式，其中一个客户的请求一个节点提供的服务和服务流程的请求而产生的响应。

    你一般不要使用服务的连续呼吁；主题或甚至行动会更适合。 
    ![alt text](https://docs.ros.org/en/rolling/_images/Service-SingleServiceClient.gif)
1. 服务列表

    ```ros2 service list ```新终端中的命令将返回系统中当前处于活动状态的所有服务的列表  
```ros2 service list -t```要同时查看所有活动服务的类型，可以将 --show-types 选项，缩写为 -t，到 list 命令：



    ROS 2 中几乎每个节点都有基础设施服务，参数就是基于这些服务构建的。专注于 turtlesim 特定的服务，您可能还记得在 使用 turtlesim、ros2 和 rqt 教程中使用 rqt 与其中一些服务进行交互。

1. 服务类型

    ```ros2 service type <service_name>```找出服务的类型。
ros2 service type /clear 返回：std_srvs/srv/Empty，Empty type 表示服务调用在发出请求时不发送任何数据，在收到响应时不接收任何数据。 
1. ROS2 服务信息

    ```ros2 service info <service_name>```返回服务类型以及服务客户端和服务器的计数。 
5. ROS2 服务查找 

    ```ros2 service find <type_name>```查找特定类型的所有服务。  
    例如，您可以找到所有 Empty 像这样键入服务：ros2 service find std_srvs/srv/Empty
这将返回：
/clear
/reset
6. ros2界面显示 

    你可以打电话服务从命令行，但首先你需要知道结构中的输入参数。

    ```ros2 interface show <type_name>```

    试试这个上 /clear 服务的类型 Empty:
    ros2 interface show std_srvs/srv/Empty
    这将返回：
    ```---```
    "---" 分隔开来的**要求的结构**(同上)从**反应的结构**(下文)。 
7. ros2服务电话  
现在，你知道什么一个服务类型，如何找到一个服务类型，以及如何寻找该结构的这种类型的论点，你可以打电话服务使用：
    ```sh
    ros2 service call <service_name> <service_type> <arguments>
    ```
    的 \<arguments\> 一部分是任选的。 例如，你知道， Empty 类型的服务没有任何论据：

    ```ros2 service call /clear std_srvs/srv/Empty```
    这一命令将明确turtlesim窗口的你的乌龟已经绘制。

    ```ros2 service call /spawn turtlesim/srv/Spawn "{x: 2, y: 2, theta: 0.2, name: ''}"```你turtlesim窗口将更新与新产生的乌龟的权利
### Understanding parameters
参数是节点的配置值。 您可以将参数视为节点设置。 节点可以将参数存储为整数、浮点数、布尔值、字符串和列表。 在 ROS 2 中，每个节点都维护自己的参数。
1. ```ros2 param list```查看属于节点的参数。   
您将看到节点命名空间， /teleop_turtle 和 /turtlesim，后跟每个节点的参数，每个节点都有参数 use_sim_time 。
3. ros2 参数获取 

    ```ros2 param get <node_name> <parameter_name>```显示参数的类型和当前值。

    让我们找出 /turtlesim的参数 background_g：  
    ```ros2 param get /turtlesim background_g```  
    这将返回值：  
    Integer value is: 86
4. ROS2 参数集 

    ```ros2 param set <node_name> <parameter_name> <value>```在运行时更改参数的值。

    让我们改变 /turtlesim的背景颜色：  
    ```ros2 param set /turtlesim background_r 150```  
    您的终端应返回以下消息： 
    Set parameter successful  
    你的turtlesim窗口的背景应该改变颜色： 

    使用 set 命令只会在当前会话中更改它们，而不是永久更改它们。 但是，您可以保存设置，并在下次启动节点时重新加载它们。
5. ROS2 参数转储 

    ```ros2 param dump <node_name>```查看节点的所有当前参数值：

    * 默认情况下，该命令打印到标准输出 （stdout），但您也可以将参数值重定向到文件中以保存它们以供以后使用。
     
    要保存当前配置 /turtlesim的参数添加到文件中 turtlesim.yaml，输入以下命令：  
    ```ros2 param dump /turtlesim > turtlesim.yaml```  
    您将在运行 shell 的当前工作目录中找到一个新文件。 如果打开此文件，您将看到以下内容：  
    ```sh
        background_g: 86
        background_r: 150
        qos_overrides:
        /parameter_events:
            publisher:
            depth: 1000
            durability: volatile
            history: keep_last
            reliability: reliable
        use_sim_time: false
    ```
    如果您想在将来使用相同的参数重新加载节点，转储参数会派上用场。    
6. ROS2 参数加载  

    ```ros2 param load <node_name> <parameter_file>```将参数从文件加载到当前正在运行的节点：

    要加载 turtlesim.yaml 生成的文件 ros2 param dump 到 /turtlesim 节点的参数，输入以下命令：  
    ```ros2 param load /turtlesim turtlesim.yaml```

    >注意
    >
    >只读参数只能在启动时修改，而不能在启动后修改，这就是为什么“qos_overrides”参数会出现一些警告的原因。

7. 在节点启动时加载参数文件 

    ```ros2 run <package_name> <executable_name> --ros-args --params-file <file_name>```开始相同的节点采用保存的参数值。

    这是同一命令你总是用来启动turtlesim，加入标志 --ros-args 和 --params-file，随后通过的文件你想要的负荷。

    停止你运行的turtlesim节点，并试图重新装载您保存的参数，使用：  
    ```ros2 run turtlesim turtlesim_node --ros-args --params-file turtlesim.yaml```  
    turtlesim 窗口应照常显示，但使用您之前设置的紫色背景。
    >注意  
    当节点启动时使用参数文件时，所有参数（包括只读参数）都将被更新。
* 摘要:节点具有用于定义其默认配置值的参数。 您可以 get 和 set 命令行中的参数值。 您还可以将参数设置保存到文件中，以便在将来的会话中重新加载它们。

### Understanding actions
背景  
* 操作是 ROS 2 中的通信类型之一，用于长时间运行的任务。 它们由三部分组成：目标、反馈和结果。  
* 操作建立在主题和服务之上。 它们的功能类似于服务，只是可以取消操作。 它们还提供稳定的反馈，而不是返回单个响应的服务。
* 操作使用客户端-服务器模型，类似于发布者-订阅者模型（在 主题教程 中介绍）。 “操作客户端”节点将目标发送到“操作服务器”节点，该节点确认目标并返回反馈流和结果。 
  ![alt text](https://docs.ros.org/en/rolling/_images/Action-SingleActionClient.gif)
2. 使用操作  
   
   当您启动 /teleop_turtle 节点，您将在终端中看到以下消息：

    Use arrow keys to move the turtle.  
    Use G|B|V|C|D|E|R|T keys to rotate to absolute orientations. 'F' to cancel a rotation.

    让我们关注第二行，它对应于**一个动作**。 （第一条指令对应于前面讨论的“cmd_vel”主题。

    注意终端在 /turtlesim 节点正在运行。 每次按下其中一个键时，都会将目标发送到作为 /turtlesim 节点。 目标是旋转以面向特定方向。 一旦完成旋转，就会显示一条传递目标结果的消息：
    ```sh
    [INFO] [turtlesim]: Rotation goal completed successfully
    ```
    --  
    不仅客户端（您在远程操作中的输入）可以阻止目标，而且服务器端（ /turtlesim node）也可以。

    1. 按 F key 将在执行过程中取消目标。

    尝试按 C 键，然后按 F 键，然后才能完成旋转。 在终端中 /turtlesim 节点正在运行，您将看到以下消息：
    ```sh
    [INFO] [turtlesim]: Rotation goal canceled
    ```

    2. 当服务器端选择停止处理目标时，称为“中止”目标。

    尝试点击 D 键，然后 G 键，然后才能完成第一次旋转。 在终端中 /turtlesim 节点正在运行，您将看到以下消息：  
    ```sh
    [WARN] [turtlesim]: Rotation goal received before a previous goal finished. Aborting previous goal
    ```  
    此操作服务器选择中止第一个目标，因为它获得了一个新目标。不要假设每个操作服务器在获得新目标时都会选择中止当前目标。 
3. ROS2 节点信息 

    要查看 /turtlesim 节点提供的操作列表，在这种情况下，请打开一个新终端并运行命令  
    ```ros2 node info /turtlesim```。
    
    ```sh
    Action Servers:
    /turtle1/rotate_absolute: turtlesim/action/RotateAbsolute
    Action Clients:
    ```
    /turtle1/rotate_absolute for /turtlesim is under Action Servers。 这意味着 /turtlesim **响应**并提供反馈 /turtle1/rotate_absolute 行动。 
    
    /teleop_turtle node has the name /turtle1/rotate_absolute under Action Clients  
    这意味着/teleop_turtle**发送**turtle1/rotate_absolute的目标。 要查看这一点，请运行： 
    ```ros2 node info /teleop_turtle```
    ```sh
    Action Servers:
    Action Clients:
    /turtle1/rotate_absolute: turtlesim/action/RotateAbsolute
    ```
4. ROS2 操作列表 

    ```ros2 action list```识别 ROS 图中的所有操作。

    这将返回：

    /turtle1/rotate_absolute

    这是目前 ROS 图中唯一的操作。 您还已经知道有一个操作客户端（part/teleop_turtle） 和一个操作服务器（part/turtlesim）。
    
    操作具有类型，类似于主题和服务。 找到 /turtle1/rotate_absolute，运行以下命令：

    ```ros2 action list -t```

    这将返回：

    /turtle1/rotate_absolute [turtlesim/action/RotateAbsolute]

    在每个操作名称右侧的括号中 是动作类型。 当您想要从命令行或代码执行操作时，您将需要它。
5. ROS2 操作信息 

    您可以进一步反省 /turtle1/rotate_absolute 使用命令执行以下操作：

    ```ros2 action info /turtle1/rotate_absolute```
6. ROS2 接口展示 

    ```ros2 interface show turtlesim/action/RotateAbsolute```在自己发送或执行操作目标之前，您需要的另一条信息是操作类型的结构。

    ```sh
    # The desired heading in radians
    float32 theta
    ---
    # The angular displacement in radians to the starting position
    float32 delta
    ---
    # The remaining rotation in radians
    float32 remaining
    ```
    该信息的第一部分------以上部分是目标请求的结构（数据类型和名称）。下一部分是结果结构。最后一部分是反馈结构。
7. ros2 action send_goal

    现在，让我们使用以下语法：  
    ```ros2 action send_goal <action_name> <action_type> <values>```从命令行发送操作目标。
    - \<values\> 需要采用 YAML 格式。

    关注 turtlesim 窗口，并在终端中输入以下命令： 
    ```ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{theta: 1.57}"```  
    您应该在终端中看到在旋转，以及以下消息：
    ```sh
    Waiting for an action server to become available...
    Sending goal:
    theta: 1.57

    Goal accepted with ID: f8db8f44410849eaa93d3feb747dd444

    Result:
    delta: -1.568000316619873

    Goal finished with status: SUCCEEDED
    ```
    - 所有目标都有一个唯一的 ID，显示在返回消息中。  
    - 您还可以看到结果，即名称为 delta，即到起始位置的位移。

    要查看此目标的反馈，请添加 --feedback 到 ros2 action send_goal 命令：

    ```ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{theta: -1.57}" --feedback```

    您的终端将返回以下消息：
    ```
    Sending goal:
    theta: -1.57

    Goal accepted with ID: e6092c831f994afda92f0086f220da27

    Feedback:
    remaining: -3.1268222332000732

    Feedback:
    remaining: -3.1108222007751465

    …

    Result:
    delta: 3.1200008392333984

    Goal finished with status: SUCCEEDED
    ```
    您将继续收到反馈，即剩余的弧度，直到目标完成。

摘要 

- 操作类似于**服务**，允许您执行长时间运行的任务，**提供定期反馈**，并且**可以取消**。

- 机器人系统可能会使用**动作**进行导航。 行动目标可以告诉机器人移动到一个位置。 当机器人导航到该位置时，它可以**沿途发送更新**（即**反馈**），然后在到达目的地后发送**最终结果消息**。

- Turtlesim 有一个动作服务器，动作客户端可以向其发送旋转海龟的目标。 在本教程中，你回顾了该操作， /turtle1/rotate_absolute，以更好地了解什么是操作以及它们是如何工作的。


### 概念总览

#### 工作空间(workspace)
-  “工作区(workspace)”是一个 ROS 术语，指的是您使用 ROS 2 进行开发的系统位置。 核心 ROS 2 工作区称为底层(underlay)。 后续的本地工作区称为叠加(overlays)。 使用 ROS 2 进行开发时，通常会同时激活多个工作区。 
1.  在ROS机器人开发中，我们针对机器人某些功能进行代码开始时，各种编写的代码、参数、脚本等文件，也需要放置在某一个文件夹里进行管理，这个文件夹在ROS系统中就叫做工作空间(workspace)。  
    所以工作空间是一个存放项目开发相关文件的文件夹，也是开发过程中存放所有资料的大本营。

ROS系统中一个典型的工作空间结构：
```
dev_ws 工作空间名称（内容数量不定）
|
|—src     代码空间
|—build   编译空间
|—install 安装空间
|—log     日志空间
```
这个dev_ws就是工作空间的根目录，里边会有四个子目录，或者叫做四个子空间。
* src，代码空间，未来编写的代码、脚本，都需要人为的放置到这里；
*  build，编译空间，保存编译过程中产生的中间文件；
*  install，安装空间，放置编译得到的可执行文件和脚本；
*  log，日志空间，编译和运行过程中，保存各种警告、错误、信息等日志。
#### 功能包 package
1. 软件包是 ROS 2 代码的组织单位。  
   如果你想安装你的代码或与他人分享，那么你就需要将其整理成一个软件包。有了软件包，你就可以发布你的 ROS 2 作品，并允许他人轻松地构建和使用它。  
   ROS 2 中的软件包创建使用 ament 作为构建系统，使用 colcon 作为构建工具。你可以使用官方支持的 CMake 或 Python 创建软件包，当然也存在其他构建类型。
1. 功能包：开发过程的大本营  
    在下载的教程代码中，大家可以看到有很多不同名称的文件夹，这些在ROS2并不是普通的文件夹，而是叫做功能包。

    每个机器人可能有很多功能，比如移动控制、视觉感知、自主导航等，如果我们把这些功能的源码都放到一起当然也是可以的，但是当我们想把其中某些功能分享给别人时，就会发现代码都混合到了一起，很难拆分出来。

    我们把不同功能的代码划分到不同的功能包中，尽量降低他们之间的耦合关系，当需要在ROS社区中分享给别人的时候，只需要说明这个功能包该如何使用，别人很快就可以用起来了。

    所以功能包的机制，是提高ROS中软件复用率的重要方法之一。
#### 节点 Nodes

节点（node）是 ROS 2 图的参与者，它使用 客户端库(Client libraries) 与其他节点进行通信。 节点可以与同一进程中、不同进程中或不同计算机上的其他节点进行通信。 节点通常是 ROS 图中的计算单位;每个节点都应该做一件合乎逻辑的事情。

节点可以 发布(publish) 到命名主题以将数据传递到其他节点，也可以 订阅(subscribe) 命名主题以从其他节点获取数据。 它们还可以充当 服务客户端(service cilent) ，让另一个节点代表它们执行计算，或者充当 服务服务器(service server) ，为其他节点提供功能。 对于长时间运行的计算，节点可以充当 操作客户端(action cilent) ，让另一个节点代表它们执行它，或者充当 操作服务器(action server) ，为其他节点提供功能。 节点可以提供可配置的 参数(parameters) ，以在运行时更改行为。

节点通常是发布者、订阅者、服务服务器、服务客户端、操作服务器和操作客户端的复杂组合，同时存在。

节点之间的连接是通过分布式 发现(discover) 过程建立的。
#### 发现 (discover)

节点的发现通过 ROS 2 的底层中间件自动发生。 可以归纳为以下几点：

*  当一个节点启动时，它会将其状态通告给网络上具有相同 ROS 域（使用 ROS_DOMAIN_ID 环境变量设置）的其他节点。 节点使用有关自身的信息来响应此通告，以便可以建立适当的连接并且节点可以通信。

-  节点会定期公布其存在，以便可以与新发现的实体建立连接，即使在初始发现期之后也是如此。

-  节点在脱机时向其他节点通告。

只有当节点具有兼容的服务质量设置时，节点才会与其他节点建立连接。
#### 接口 interfaces

### Using rqt_console to view logs
用 rqt_console 查看日志  
rqt_console 是一个 GUI 工具，用于内省 ROS 2 中的日志消息。 通常，日志消息会显示在终端中。 跟 rqt_console，您可以随着时间的推移收集这些消息，以更有条理的方式仔细查看它们，过滤它们，保存它们，甚至重新加载保存的文件以在不同的时间进行反省。

开始 rqt_console 在新终端中使用以下命令：

ros2 run rqt_console rqt_console

这 rqt_console 窗口将打开： 
* 控制台的第一部分是显示来自系统的日志消息的位置。

* 在中间，您可以选择通过排除严重性级别来筛选邮件。 您还可以使用右侧的加号按钮添加更多排除过滤器。

* 底部用于突出显示包含您输入的字符串的消息。 您也可以向此部分添加更多筛选器。 

ROS 2 的记录器级别按严重性排序：

    Fatal
    Error
    Warn
    Info
    Debug

每个级别所表示的内容没有确切的标准，但可以肯定的是：

  -  Fatal 消息指示系统将终止，以尝试保护自己免受损害。

   - Error 消息表示重大问题，这些问题不一定会损坏系统，但会阻止其正常运行。

   - Warn 消息指示意外活动或非理想结果，可能表示更深层次的问题，但不会直接损害功能。

   - Info 消息指示事件和状态更新，这些更新可直观地验证系统是否按预期运行。

   - Debug 消息详细说明了系统执行的整个分步过程。

默认级别为 Info。 您将只能看到默认严重性级别和更严重级别的消息。

通常，只有 Debug 消息是隐藏的，因为它们是唯一比 Info 严重级别低的消息。 例如，如果将默认级别设置为 Warn，则只会看到严重性很强的消息 Warn， Error和 Fatal。 

```ros2 run turtlesim turtlesim_node --ros-args --log-level WARN```设置默认记录器级别   
现在你不会看到上次启动时在控制台中出现的 Info 级别消息 。 那是因为 Info 消息的优先级低于新的默认严重性。 
### Launching nodes
运行了启动文件

打开一个新端运行：

ros2 launch turtlesim multisim.launch.py

这种命令将运行以下启动文件：
```py
# turtlesim/launch/multisim.launch.py

from launch import LaunchDescription
import launch_ros.actions

def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node(
            namespace= "turtlesim1", package='turtlesim', executable='turtlesim_node', output='screen'),
        launch_ros.actions.Node(
            namespace= "turtlesim2", package='turtlesim', executable='turtlesim_node', output='screen'),
    ])
```
这将同时运行两个turtlesim节点。

控制Turtlesim节点
在第二端：  
``
ros2 topic pub  /turtlesim1/turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"
``  
在第三终端：  
``
ros2 topic pub  /turtlesim2/turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: -1.8}}"
``  
### Recording and playing back data
<kbd>ros2 bag</kbd> 是一个命令行工具，用于记录系统中主题上发布的数据。  
它累积在任意数量的主题上传递的数据并将其保存在数据库中。 然后，您可以重播数据以重现测试和实验的结果。 录制主题也是分享您的作品并允许其他人重新创建它的好方法。 
1. 设置  
创建一个新目录来存储我们保存的录音，就像一个好的做法一样：
mkdir bag_files
cd bag_files
2. 选择一个主题  
ros2 bag 只能记录 Topics 中已发布消息的数据。 要查看系统主题列表，请打开一个新终端并运行以下命令：
```ros2 topic list```，  
3. 记录单个主题  

    ```ros2 bag record <topic_name>```记录发布到主题的数据。  
    ros2 bag record /turtle1/cmd_vel

    现在 ros2 bag 正在记录发布在 /turtle1/cmd_vel 主题。按 Ctrl+C 停止录制。

    数据将累积在一个新的袋子目录中，其名称的模式为 rosbag2_year_month_day-hour_minute_second。 此目录将包含一个 metadata.yaml 以及记录格式的袋子文件。 
3. 记录多个主题 
您还可以录制多个主题，以及更改文件的名称 ros2 bag 保存到。

运行以下命令：

```ros2 bag record -o subset /turtle1/cmd_vel /turtle1/pose```

 -o 选项允许您为行李文件选择唯一名称。

4. ROS2 包信息 

您可以通过运行以下命令查看有关录制文件的详细信息：

```ros2 bag info <bag_file_name>```

5. 重播 bag 文件

    输入以下命令：

    ```ros2 bag play subset```

    你的将遵循你在录制时输入的相同路径（尽管不是100%完全;turtlesim对系统时间的微小变化很敏感）。 

## 初学者：客户端库 
### 开发环境配置
https://book.guyuehome.com/ROS2/1.%E7%B3%BB%E7%BB%9F%E6%9E%B6%E6%9E%84/1.5_ROS2%E5%BC%80%E5%8F%91%E7%8E%AF%E5%A2%83%E9%85%8D%E7%BD%AE/
### 用 colcon 生成包
创建和构建 ROS 2 工作区  
- colcon 是 ROS 构建工具catkin_make， catkin_make_isolated， catkin_tools 和 ament_tools的迭代。 
- Prerequisites
    - Install colcon

        ```sudo apt install python3-colcon-common-extensions```

    - Install ROS 2
1. 基础知识

    ROS 工作区是一个具有特定结构的目录。通常会有一个 src 子目录。在该子目录中，存放着 ROS 软件包的源代码。通常情况下，该目录开始时是空的。  
    colcon 会进行源代码编译。默认情况下，它会创建以下目录作为 src 目录的同级目录：
    - build目录将存放中间文件。为每个软件包创建一个子文件夹，例如 CMake 将在其中调用。
    - install目录是每个软件包的安装目录。默认情况下，每个软件包都将安装到一个单独的子目录中。
    - log目录包含有关每次调用 colcon 的各种日志信息。
2. Create a workspace

    First, create a directory (ros2_ws) to contain our workspace:

    mkdir -p ~/ros2_ws/src
    cd ~/ros2_ws

    此时，工作区只包含一个空目录 src：
    ```sh
    .
    └── src

    1 directory, 0 files
    ```
3. Add some sources

    让我们将示例库克隆到工作区的 src 目录中：
    ```sh
    git clone https://github.com/ros2/examples src/examples -b rolling
    ```
4. 获取底层环境  
    重要的是，我们要为现有的 ROS 2 安装提供环境，以便为我们的工作区提供示例软件包所需的构建依赖项。这可以通过二进制安装或源安装（即另一个 colcon 工作区）提供的设置脚本来实现。我们称这种环境为 "底层"。

    我们的工作区 ros2_ws 将是现有 ROS 2 安装的覆盖层。一般来说，当你计划迭代少量软件包时，建议使用覆盖层，而不是把所有软件包都放到同一个工作区。
5. Build the workspace  
    运行```colcon build```
    #### colcon常用指令
    ```colcon build --parallel-workers 6 ```cpu/内存占用100%时卡死，使用6内核进行编译

    只编译一个包

    ```colcon test --packages-select YOUR_PKG_NAME```

    不编译测试单元

    ```colcon test --packages-select YOUR_PKG_NAME  --cmake-args -DBUILD_TESTING=0```

    运行编译的包的测试

    ```colcon test```

    允许通过更改src下的部分文件来改变install（重要）

   ```colcon build --symlink-install```在工作区的根目录下运行 colcon build。  
   由于 ament_cmake 等构建类型不支持开发空间（devel space）的概念，需要安装软件包，因此 colcon 支持 --symlink-install 选项。这允许通过更改源代码空间中的文件（如 Python 文件或其他非编译资源）来更改已安装的文件，从而加快迭代速度。  
   编译完成后，我们将看到编译、安装和日志目录：
    ```
    .
    ├── build
    ├── install
    ├── log
    └── src
    ```

6. 环境来源

    当 colcon 成功完成构建后，输出结果将出现在安装目录中。  
    **在使用任何已安装的可执行文件或库之前，您需要将它们添加到路径和库路径中**。colcon 会在安装目录中生成 bash/bat 文件，以帮助设置环境。这些文件会将所有必要元素添加到路径和库路径中，并提供软件包导出的任何 bash 或 shell 命令。  
    ```source install/setup.bash```
7. 尝试演示

   有了源的环境，我们就可以运行由 colcon 构建的可执行文件。  
    让我们从示例中运行一个订阅者节点，在另一个终端中，让我们运行一个发布者节点，您应该会看到来自发布者和订阅者的消息，其中数字递增。
    ```sh
    source install/setup.bash
    ros2 run examples_rclcpp_minimal_subscriber subscriber_member_function
    ```
    ```sh
    source ~/ros2_ws/install/setup.sh
    ros2 run examples_rclcpp_minimal_publisher publisher_member_function
    ```
8. 创建您自己的软件包

   - colcon 使用 package.xml 中定义的规范 REP 149 

   - Colcon 支持多种构建类型。 建议的构建类型包括 ament_cmake 和 ament_python。 还支持纯 cmake 包。

   - 您可以使用 ros2 pkg create 以基于模板创建新包。 
9. 设置 colcon_cd

    命令 colcon_cd 允许您快速将 shell 的当前工作目录更改为包的目录。 举个例子 colcon_cd some_ros_package 会很快把你带到目录 ~/ros2_ws/src/some_ros_package。
    ```sh
    echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> ~/.bashrc
    echo "export _colcon_cd_root=/opt/ros/rolling/" >> ~/.bashrc
    ```
10. 设置 colcon 选项卡补全 

    命令 colcon 支持 bash 和类似 bash 的 shell 的命令完成，如果 colcon-argcomplete 软件包已安装。
    ```sh
    echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc
    ```

### 创建工作区
创建一个工作空间，并学习如何设立了一个覆盖层进行开发和测试。
     
* 工作区是一个包含 ROS 2 软件包的目录。在使用 ROS 2 之前，有必要在你计划工作的终端中为 ROS 2 安装工作区提供源代码。这样，ROS 2 的软件包就可以在该终端中使用了。
* 你还可以选择 **"覆盖"（overlay）--一个辅助工作区**，在这里你可以添加新软件包，而不会影响你正在扩展的现有 ROS 2 工作区，
* 或者 "底层"（underlay）。**底层必须包含覆盖层中所有软件包的依赖关系**。覆盖层中的软件包将覆盖底层中的软件包。也可以有多层底层和覆盖层，每一层覆盖层都使用其父底层的软件包


1. 源 ROS 2 环境

    您的主 ROS 2 安装将是本教程的底层。(请记住，底层并不一定是 ROS 2 的主安装）。  
    根据您安装 ROS 2 的方式（源代码还是二进制文件）以及您所处的平台，您的源代码命令也会有所不同  
    ```sh
    source /opt/ros/rolling/setup.bash #humble
    ```
2. 创建新目录

    最佳做法是**为每个新工作区创建一个新目录**。名称并不重要，但最好能说明工作区的目的。让我们选择 ros2_ws 作为 "开发工作区 "的目录名：  
    ```
    mkdir -p ~/ros2_ws/src
    cd ~/ros2_ws/src
    ```
    另一个最佳做法是**将工作区中的所有软件包都放到 src 目录中**。上述代码在 ros2_ws 中创建了一个 src 目录，然后导航进入该目录。
3. 克隆一个示例 
 
    repo克隆之前，请确保你仍在 ros2_ws/src 目录中。现在你将练习使用现有软件包组建工作区。一个软件仓库可以有多个分支。你需要查看针对你已安装的 ROS 2 发行版的那个分支。克隆该 repo 时，在该分支后添加 -b 参数。在 ros2_ws/src 目录下运行以下命令：
    ```sh
    git clone https://github.com/ros/ros_tutorials.git -b rolling
    ```
    现在 ros_tutorials 在工作区中克隆。 这 ros_tutorials 存储库包含 turtlesim package。 此存储库中的其他软件包未构建，因为它们包含 COLCON_IGNORE 文件。
4. 解决依赖关系 

    在构建工作空间之前，需要解决包依赖关系。 您可能已经拥有所有依赖项，但最佳做法是**在每次克隆时检查依赖项**。 您不希望构建在长时间等待后才意识到缺少依赖项而失败。

    从工作区的根目录 （ros2_ws），运行以下命令：
    ```sh
    # cd if you're still in the ``src`` directory with the ``ros_tutorials`` clone
    cd ..
    rosdep install -i --from-path src --rosdistro rolling -y
    ```
    ```sh
    rosdep install --from-paths src --ignore-src -r -y
    ```
    Here are the from-source rosdep section
    ```
    sudo rosdep init
    rosdep update
    rosdep install --from-paths src --ignore-src -y --skip-keys "fastcdr rti-connext-dds-6.0.1 urdfdom_headers"
    ```
    如果您已经拥有所有依赖项，控制台将返回：

    All required rosdeps installed successfully

    * 包在 package.xml 文件中声明其依赖项（您将在下一教程中了解有关包的更多信息）。 此命令将遍历这些声明并安装缺少的声明。
5. 使用 colcon 构建工作空间 

    从工作区的根目录 （ ros2_ws），现在可以使用以下命令构建包：
    ```sh
    colcon build
    ```
    >WARNING:colcon.colcon_core.package_selection:Some selected packages are already built in one or more underlay workspaces:  
    >If you understand the risks and want to override a package anyways, add the following to the command line:  
    >
    >--allow-overriding turtlesim
    >
    >---
    >If a package in a merged underlay workspace is overridden and it installs headers, then all packages in the overlay must sort their include directories by workspace order. Failure to do so may result in build failures or undefined behavior at run time.
    If the overridden package is used by another package in any underlay, then the overriding package in the overlay must be API and ABI compatible or undefined behavior at run time may occur.
    >
    >If you understand the risks and want to override a package anyways, add the following to the command line:
	--allow-overriding turtlesim
    ```sh
    colcon build --allow-overriding turtlesim
    ```
               

    > colcon build 的其他有用参数
    > - ```--packages-up-to```构建你想要的软件包及其所有依赖包，但不构建整个工作区（节省时间）
    >- ```--symlink-install```（链接安装）省去了每次修改 python 脚本都要重建的麻烦
    >- ```--event-handlers console_direct+``` 在构建时显示控制台输出（也可以在日志目录中找到）。

6. 创建覆盖层

    **在获取覆盖层之前，打开一个新的终端**非常重要，要与构建工作区的终端分开。在构建工作区的同一终端或同样在构建工作区的终端中获取覆盖层可能会产生复杂的问题。  
    在新终端中，将 ROS 2 的主环境作为 "底层"，这样就可以在其 "顶层 "构建覆盖层：
    ```sh
    source /opt/ros/rolling/setup.bash
    #进入工作区的根目录：
    cd ~/ros2_ws
    #在根目录中，获取覆盖层：
    source install/local_setup.bash
    ```
    >注意  
    >setup会将覆盖层的本地设置（local_setup）添加到你的环境中。setup不仅会将覆盖层的设置添加到你的环境中，也会将它创建时所在的下层设置添加到你的环境中，这样你就可以同时使用两个工作空间了。  
    >因此，像你刚才这样，**先获取 ROS 2 主安装的设置，然后再获取 ros2_ws 覆盖层的 local_setup，与只获取 ros2_ws 的设置是一样的**，因为它包含了覆盖层的环境。

    现在您可以运行 turtlesim 来自叠加层的包：
    ```sh
    ros2 run turtlesim turtlesim_node
    ```
    这是正在运行的覆盖 turtlesim，而不是你主安装的 turtlesim

    * **您可以单独修改和重建叠加层中的包，而不是底层。**

    * **叠加层优先于参考底图**。
7. 修改覆盖层  
   1. 您可以通过编辑 turtlesim 窗口的标题栏来修改覆盖层中的 turtlesim。
      * 找到 ~/ros2_ws/src/ros_tutorials/turtlesim/src 中的 turtle_frame.cpp 文件。使用您喜欢的文本编辑器打开 turtle_frame.cpp。
      * 在第 52 行，您将看到函数 setWindowTitle("TurtleSim");。将 "TurtleSim "更改为 "MyTurtleSim"，然后保存文件。
   2. 返回之前运行 colcon build 的第一个终端，再次运行```colcon build```。
   3. 返回第二个终端（覆盖层的来源），再次运行 turtlesim：
   ```ros2 run turtlesim turtlesim_node```

   你会看到 turtlesim 窗口的标题栏现在显示 "MyTurtleSim"。

   - 尽管您的主 ROS 2 环境是在该终端中创建的，但您的 ros2_ws 环境的覆盖层优先于底层的内容。  
   要查看底层内容是否完好无损，请打开一个全新的终端，并只在 ROS 2 安装中获取源代码。再次运行 turtlesim：
   ros2 run turtlesim turtlesim_node

    覆盖层中的修改实际上并不影响底层中的任何内容。
- 您获取了主要的 ROS 2 发行版安装作为底层，并通过在新工作区中克隆和构建软件包来创建覆盖层。
-  叠加层被附加到路径之前，并优先于底层。
- 建议使用覆盖来处理少量包，这样您就不必将所有内容放在同一个工作区中，并在每次迭代时重新构建一个巨大的工作区。 
### 创建软件包
目标： 使用 CMake 或 Python 创建一个新软件包，并运行其可执行文件。
- 什么是 ROS 2 软件包？
   
    软件包是 ROS 2 代码的组织单位。如果你想安装你的代码或与他人分享，那么你就需要把它整理成一个软件包。有了软件包，你就可以发布你的 ROS 2 作品，并允许他人轻松构建和使用。
    ROS 2 中的软件包创建使用 ament 作为构建系统，使用 colcon 作为构建工具。你可以使用官方支持的 CMake 或 Python 创建软件包，当然也存在其他构建类型。
- ROS 2 软件包由哪些部分组成？
   
    ROS 2 Python 和 CMake 软件包都有各自的最低要求内容：

    * CMake
    - **CMakeLists.txt 文件**，说明如何在软件包内构建代码
    - **include/<package_name> 目录**，包含软件包的公共头文件
    - **package.xml 文件**，包含软件包的元信息
    - **src 目录**包含软件包的源代码

    其中必然存在两个文件：**package.xml**和**CMakerLists.txt**。

    最简单的软件包可能具有如下文件结构：
    ```
    my_package/
            CMakeLists.txt
            include/my_package/
            package.xml
            src/
    ```
    * Python
    

        - **package.xml 文件**包含了软件包的元信息

        - **resource/<package_name>** 是软件包的标记文件

        - **setup.cfg**当软件包有可执行文件时是必须的 ，以便 ros2 run 能够找到它们

        - **setup.py** 包含有关如何安装软件包的说明

        - **<package_name>** - 一个与你的软件包同名的目录，ROS 2 工具用它来查找你的软件包，包含 **\_\_init__.py**

    Python语言是解析型的，不需要编译，所以会有一些不同，但也会有这两个文件：**package.xml**和**setup.py**。

    最简单的软件包可能具有如下文件结构：
    ```sh
    my_package/
        package.xml
        resource/my_package
        setup.cfg
        setup.py
        my_package/
    ```
- 工作空间中的软件包
   - 单个工作区可以包含任意数量的包，每个包都位于自己的文件夹中。 
   - 可以在一个工作区（CMake、Python 等）中包含不同生成类型的包。
   - 不能有嵌套包。

    最佳做法是拥有 src 文件夹，并在其中创建包。 这样可以使工作区的顶层保持“干净”。 
    ```sh
    workspace_folder/
    src/
      cpp_package_1/
          CMakeLists.txt
          include/cpp_package_1/
          package.xml
          src/

      py_package_1/
          package.xml
          resource/py_package_1
          setup.cfg
          setup.py
          py_package_1/
      ...
      cpp_package_n/
          CMakeLists.txt
          include/cpp_package_n/
          package.xml
          src/
    ```
* 前提条件  
按照前面教程中的说明操作后，您应该拥有一个 ROS 2 工作区。您将在此工作区中创建软件包。
```sh
#创建名为ros2_ws的工作空间

#了解了工作空间的概念和结果，接下来我们可以使用如下命令创建一个工作空间，并且下载教程的代码：

mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
git clone https://github.com/ros/ros_tutorials.git -b rolling

#自动安装依赖

#我们从社区中下载的各种代码，多少都会有一些依赖，我们可以手动一个一个安装，也可以使用rosdep工具自动安装：

# sudo apt install -y python3-pip
# sudo pip3 install rosdepc
# sudo rosdepc init
# rosdepc update
# cd ..
# rosdepc install -i --from-path src --rosdistro humble -y

# ROS Noetic
sudo apt install -y python3-pip
sudo apt-get install python3-rosdep
sudo rosdep init
rosdep update
# sudo pip install -U rosdep  #On non ubuntu platforms
cd .. #cd ~/ros2_ws/
rosdep install -i --from-path src --rosdistro rolling -y

#编译工作空间

#依赖安装完成后，就可以使用如下命令编译工作空间啦，如果有缺少的依赖，或者代码有错误，编译过程中会有报错，否则编译过程应该不会出现任何错误：

sudo apt install python3-colcon-ros
cd ~/ros2_ws/
colcon build

#编译成功后，就可以在工作空间中看到自动生产的build、log、install文件夹了。


#设置环境变量

#编译成功后，为了让系统能够找到我们的功能包和可执行文件，还需要设置环境变量：

#在获取覆盖层之前，打开一个新的终端非常重要，要与构建工作区的终端分开。在构建工作区的同一终端或同样在构建工作区的终端中获取覆盖层可能会产生复杂的问题。
# source install/local_setup.sh # 仅在当前终端生效

# echo " source ~/dev_ws/install/local_setup.sh" >> ~/.bashrc # 所有终端均生效
```
1 创建软件包 

首先， 获取 ROS 2 安装 。

让我们使用在上一教程中创建的工作区 ros2_ws，用于您的新软件包。

确保您在 src 文件夹，然后再运行包创建命令。```cd ~/ros2_ws/src```

**在 ROS 2 中创建新包的命令语法**为：

CMake:```ros2 pkg create --build-type ament_cmake --license Apache-2.0 <package_name>```

Python:```ros2 pkg create --build-type ament_python --license Apache-2.0 <package_name>```

- pkg：表示功能包相关的功能；
- create：表示创建功能包；
- build-type：表示新创建的功能包是C++还是Python的，如果使用C++或者C，那这里就跟ament_cmake，如果使用Python，就跟ament_python；
- package_name：新建功能包的名字。

在本教程中，您将使用可选参数 --node-name 和 --license。  
- --node-name option 在包中创建一个简单的 Hello World 类型可执行文件，并且   
- --license 声明包的许可证信息。
 
CMake:```ros2 pkg create --build-type ament_cmake --license Apache-2.0 --node-name my_node my_package```

Python:```ros2 pkg create --build-type ament_python --license Apache-2.0 --node-name my_node my_package```

现在，你将在工作区的 src 目录中
新建一个名为 my_package 的文件夹，您可以看到为新软件包自动生成的文件。

2. 构建软件包

    将软件包放在工作区中尤为重要，因为通过在工作区根目录下运行 colcon build，可以一次性构建多个软件包。否则，你将不得不单独构建每个软件包。  
    返回工作区的根目录：```cd ~/ros2_ws```

    现在，您可以构建包：```colcon build```

    要想下次只编译 my_package 软件包，可以运行  
    ```colcon build --packages-select my_package```
3. Source the setup file
    要使用新软件包和可执行文件，首先要打开一个新终端，并将 ROS 2 主安装source。  
    然后，在 ros2_ws 目录下运行以下命令，获取工作区的源代码：   
    ```source install/local_setup.bash```
4. 使用软件包 

    要运行您创建的可执行文件 --node-name 参数，输入以下命令：  
    ```ros2 run my_package my_node```
5. 检查包装内容 

里面 ros2_ws/src/my_package，您将看到以下文件和文件夹 ros2 pkg create 自动生成。
6. 自定义package.xml 

您可能已经注意到，在创建包后的返回消息中，字段 description 和 license 包含 TODO 笔记。 这是因为包描述和许可证声明不是自动设置的，但如果你想发布包，则需要设置包说明和许可证声明。 这 maintainer 字段可能还需要填写。

从 ros2_ws/src/my_package打开 package.xml 使用您喜欢的文本编辑器：

<?xml version="1.0"?>
<?xml-model
   href="http://download.ros.org/schema/package_format3.xsd"
   schematypens="http://www.w3.org/2001/XMLSchema"?>
<package format="3">
 <name>my_package</name>
 <version>0.0.0</version>
 <description>TODO: Package description</description>
 <maintainer email="user@todo.todo">user</maintainer>
 <license>TODO: License declaration</license>

 <buildtool_depend>ament_cmake</buildtool_depend>

 <test_depend>ament_lint_auto</test_depend>
 <test_depend>ament_lint_common</test_depend>

 <export>
   <build_type>ament_cmake</build_type>
 </export>
</package>

输入您的姓名和电子邮件 maintainer 行（如果尚未自动填充）。 然后，编辑 description 行总结包：

```<description>Beginner client libraries tutorials practice package</description>```

然后，更新 license 线。 您可以在此处阅读有关开源许可证的更多信息 here。 由于此包仅用于练习，因此使用任何许可证都是安全的。 我们将使用 Apache License 2.0：

```<license>Apache License 2.0</license>```

完成编辑后不要忘记保存。

在许可证标签下方，您将看到一些以 _depend。package.xml 将列出它对其他软件包的依赖关系，供 colcon 搜索。   
my_package 很简单，没有任何依赖项，但你将在即将到来的教程中看到这个空间被使用。 

python:
```
setup.py 文件包含与 package.xml，所以你也需要设置这些。 它们需要在两个文件中完全匹配。 版本和名称 （ package_name） 也需要完全匹配，并且应自动填充到两个文件中。

打开 setup.py 使用您喜欢的文本编辑器。

from setuptools import find_packages, setup

package_name = 'my_py_pkg'

setup(
 name=package_name,
 version='0.0.0',
 packages=find_packages(exclude=['test']),
 data_files=[
     ('share/ament_index/resource_index/packages',
             ['resource/' + package_name]),
     ('share/' + package_name, ['package.xml']),
   ],
 install_requires=['setuptools'],
 zip_safe=True,
 maintainer='TODO',
 maintainer_email='TODO',
 description='TODO: Package description',
 license='TODO: License declaration',
 tests_require=['pytest'],
 entry_points={
     'console_scripts': [
             'my_node = my_py_pkg.my_node:main'
     ],
   },
)

编辑 maintainer， maintainer_email和 description 要匹配 package.xml。

不要忘记保存文件。
```

### 编写简单的发布者和订阅者 （C++）
* 节点 是通过 ROS 图进行通信的可执行进程。 在本教程中，节点将通过主题以字符串消息的形式相互传递信息 topic。 这里使用的示例是一个简单的“说话者”和“倾听者”系统;一个节点发布数据，另一个节点订阅主题，以便它可以接收该数据。 
1. 创建软件包 

    - 打开一个新终端并 获取您的 ROS 2 安装。

    回想一下，包应该在 src目录，而不是工作区的根目录。 因此：   
    - 导航到 ros2_ws/src，  
    - 然后运行包创建命令：

        ```ros2 pkg create --build-type ament_cmake --license Apache-2.0 cpp_pubsub```

        您的终端将返回一条消息，验证您的软件包的创建 cpp_pubsub 及其所有必要的文件和文件夹。

    - 导航到 ros2_ws/src/cpp_pubsub/src。  
    这是 CMake 软件包中包含可执行文件的源文件所在的目录。
  
2. 写入发布者节点 
   
    通过输入以下命令下载示例说话者代码：

    ```wget -O publisher_lambda_function.cpp https://raw.githubusercontent.com/ros2/examples/rolling/rclcpp/topics/minimal_publisher/lambda.cpp```

    [publisher_lambda_function.cpp](publisher_lambda_function.cpp)
- 2.1 检查代码  

```cpp

#include "rclcpp/rclcpp.hpp"

/*
    创建一个类节点，名字叫做Node03,继承自Node.
*/
class Node03 : public rclcpp::Node
{

public:
    // 构造函数,有一个参数为节点名称
    Node03(std::string name) : Node(name)
    {
        // 打印一句
        RCLCPP_INFO(this->get_logger(), "大家好，我是%s.",name.c_str());
    }

private:
   
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个node_03的节点*/
    auto node = std::make_shared<Node03>("node_03");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

```
```cpp

```
代码的顶部包括您将使用的标准 C++ 标头。  
在标准 C++ 标头之后是 ```rclcpp/rclcpp.hpp include``` 允许您使用 ROS 2 系统中最常见的部分。  
最后是 ```std_msgs/msg/string.hpp```，其中包括将用于发布数据的内置消息类型。

首先，我们包含了必要的头文件，包括`<chrono>`，`<memory>`，`<string>`，`"rclcpp/rclcpp.hpp"`和`"std_msgs/msg/string.hpp"`。  
其中，`<chrono>`用于处理时间，`<memory>`用于智能指针，`<string>`用于字符串操作，`"rclcpp/rclcpp.hpp"`是ROS2的主要库，`"std_msgs/msg/string.hpp"`是ROS2的标准消息类型之一。

然后，我们使用`std::chrono_literals`命名空间，这样我们就可以使用便捷的时间字面量，如`500ms`。


```cpp
#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
```
这些行表示节点的依赖关系。  
回想一下，必须将依赖项添加到 package.xml 和 CMakeLists.txt，您将在下一节中执行此操作。

---

接下来，我们定义了一个名为[`MinimalPublisher`](command:_github.copilot.openSymbolInFile?%5B%22publisher_lambda_function.cpp%22%2C%22MinimalPublisher%22%5D "publisher_lambda_function.cpp")的类，它是`rclcpp::Node`的子类。这个类代表一个ROS2节点，它可以发布消息到一个名为"topic"的主题。



下一行通过继承 rclcpp::Node 的派生类 MinimalPublisher 创建节点 。 每一个 ```this``` 在代码中代表着节点。

```cpp
class MinimalPublisher : public rclcpp::Node
```
公共 构造函数 命名节点 `minimal_publisher` 并初始化 `count_` 设置为 0。  
在构造函数中，发布者使用 `String` 消息类型，主题名称 `topic`，以及在发生备份时限制消息所需的队列大小。  
接下来，一个名为  `timer_callback` 的 lambda 表达式 已声明。 它执行当前对象的按引用捕获 this ，不接受任何输入参数并返回 void。 这 `timer_callback` 函数创建类型的新消息 `String`，使用所需的字符串设置其数据并发布它。 这 RCLCPP_INFO 宏可确保将每条已发布的消息打印到控制台。 最后 `timer_` 初始化，这会导致 `timer_callback` 函数每秒执行两次。

在[`MinimalPublisher`](command:_github.copilot.openSymbolInFile?%5B%22publisher_lambda_function.cpp%22%2C%22MinimalPublisher%22%5D "publisher_lambda_function.cpp")的构造函数中，我们创建了一个发布者和一个定时器。发布者用于发布`std_msgs::msg::String`类型的消息到"topic"主题。定时器每500毫秒触发一次，每次触发时，它会调用一个lambda函数。这个lambda函数创建一个新的`std_msgs::msg::String`消息，将其内容设置为"Hello, world!"加上一个递增的计数器，然后通过发布者发布这个消息。
```cpp
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    auto timer_callback =
      [this]() -> void {
       auto message = std_msgs::msg::String();
        message.data = "Hello, world! " + std::to_string(this->count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        this->publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(500ms, timer_callback);
  }
```
类的底部是计时器、发布者和计数器字段的声明。
```cpp
private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
```
遵循 MinimalPublisher class 是 main，节点实际执行的位置。 rclcpp::init 初始化 ROS 2，并 rclcpp::spin 开始处理来自节点的数据，包括来自计时器的回调。

在`main`函数中，我们初始化ROS2，创建一个[`MinimalPublisher`](command:_github.copilot.openSymbolInFile?%5B%22publisher_lambda_function.cpp%22%2C%22MinimalPublisher%22%5D "publisher_lambda_function.cpp")的实例，并让它开始运行。`rclcpp::spin`函数会阻塞当前线程，直到ROS2节点被关闭。最后，我们关闭ROS2并退出程序。
```cpp
int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
```
- 2.2 添加依赖  (package.xml)

导航返回一个级别到 ros2_ws/src/cpp_pubsub 目录，其中 CMakeLists.txt 和 package.xml 已为您创建文件。

打开 package.xml 使用您的文本编辑器。

如 上一教程 所述，请确保将 \<description>， \<maintainer> 和 \<license> 标签：
```xml
<description>Examples of minimal publisher/subscriber using rclcpp</description>
<maintainer email="you@email.com">Your Name</maintainer>
<license>Apache License 2.0</license>
```
在 `ament_cmake` buildtool 依赖关系后添加一行新内容，并粘贴以下与节点的 include 语句相对应的依赖关系：
```xml
<depend>rclcpp</depend>
<depend>std_msgs</depend>
```
这声明了包需求 rclcpp 和 std_msgs 当其代码被构建和执行时。

确保保存文件。

- 2.3 CMakeLists.txt 

现在打开 `CMakeLists.txt` 文件。 在现有依赖项 `find_package(ament_cmake REQUIRED)`之下，添加以下行：
```
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
```
之后，添加可执行文件并命名它为 talker 。因此，您可以使用以下命令运行节点 ros2 run：
```
add_executable(talker src/publisher_lambda_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
```
最后，添加 install(TARGETS...) 部分 ，所以 ros2 run 可以找到您的可执行文件：
```
install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})
```
你可以清理你的 CMakeLists.txt 通过删除一些不必要的部分和注释，它看起来像这样：
```cmake
cmake_minimum_required(VERSION 3.5)
project(cpp_pubsub)

Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker src/publisher_lambda_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME})

ament_package()
```
您现在可以构建您的软件包，获取本地安装文件并运行它，但让我们先创建订阅者节点，以便您可以看到整个系统的工作情况。 

1. 写入订阅节点 

返回 ros2_ws/src/cpp_pubsub/src 以创建下一个节点。 在终端中输入以下代码：
```
wget -O subscriber_lambda_function.cpp https://raw.githubusercontent.com/ros2/examples/rolling/rclcpp/topics/minimal_subscriber/lambda.cpp
```
检查以确保以下文件存在：
```
publisher_lambda_function.cpp  subscriber_lambda_function.cpp
```
打开 subscriber_lambda_function.cpp 使用您的文本编辑器。[subscriber_lambda_function.cpp](subscriber_lambda_function.cpp)

- 3.1 检查代码 

订阅者节点的代码与发布者的代码几乎相同。 现在节点被命名为 minimal_subscriber，并且构造函数使用节点的 create_subscription 函数来执行回调。

没有计时器，因为订阅者只是在数据发布到 topic 主题。

这 topic_callback 函数接收通过主题发布的字符串消息数据，并简单地使用 RCLCPP_INFO 宏观。

回想一下 主题教程 中，发布者和订阅者使用的主题名称和消息类型必须匹配才能允许它们进行通信。
```cpp
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    auto topic_callback =
      [this](std_msgs::msg::String::UniquePtr msg) -> void {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
      };
    subscription_ =
      this->create_subscription<std_msgs::msg::String>("topic", 10, topic_callback);
  }
```
此类中唯一的字段声明是订阅。
```cpp
private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
```
这 main 函数完全相同，只是现在它旋转了 MinimalSubscriber 节点。 对于发布者节点来说，旋转意味着启动计时器，但对于订阅者来说，它只是意味着准备在消息到来时接收消息。

由于此节点与发布者节点具有相同的依赖项，因此无需`package.xml`添加任何新内容 。

- 3.2 CMakeLists.txt 

重开 CMakeLists.txt 并在发布者的条目下方添加订阅者节点的可执行文件和目标。
```cmake
add_executable(listener src/subscriber_lambda_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})
```
确保保存文件，然后您的发布/订阅系统应该准备就绪。 

4. 构建和运行

您可能已经拥有 rclcpp 和 std_msgs 作为 ROS 2 系统的一部分安装的软件包。 在工作区的根目录 （ros2_ws）运行 rosdep 是很好的做法，在生成之前检查是否缺少依赖项：
```sh
rosdep install -i --from-path src --rosdistro rolling -y
```
仍然在工作区的根目录下， ros2_ws，构建新包：
```sh
colcon build --packages-select cpp_pubsub
```
打开一个新终端，导航到 ros2_ws，并获取安装文件：
```sh
. install/setup.bash
```
现在运行 talker 节点：
```sh
ros2 run cpp_pubsub talker
```
终端应每 0.5 秒开始发布一次信息消息，如下所示：
```sh
[INFO] [minimal_publisher]: Publishing: "Hello World: 0"
[INFO] [minimal_publisher]: Publishing: "Hello World: 1"
[INFO] [minimal_publisher]: Publishing: "Hello World: 2"
[INFO] [minimal_publisher]: Publishing: "Hello World: 3"
[INFO] [minimal_publisher]: Publishing: "Hello World: 4"
```
打开另一个终端，从内部获取设置文件 ros2_ws 再次，然后启动侦听器节点：
```sh
ros2 run cpp_pubsub listener
```
侦听器将开始将消息打印到控制台，从发布者当时处于的任何消息计数开始，如下所示：
```sh
[INFO] [minimal_subscriber]: I heard: "Hello World: 10"
[INFO] [minimal_subscriber]: I heard: "Hello World: 11"
[INFO] [minimal_subscriber]: I heard: "Hello World: 12"
[INFO] [minimal_subscriber]: I heard: "Hello World: 13"
[INFO] [minimal_subscriber]: I heard: "Hello World: 14"
```
进入 Ctrl+C 在每个终端中停止节点旋转。 
### 编写简单的发布者和订阅者 （Python）
1. 创建软件包 

   - 打开一个新终端并 获取您的 ROS 2 安装 ，以便 ros2 命令将起作用。

       导航到 ros2_ws中创建的目录 。

   - 导航到 ros2_ws/src，然后运行包创建命令：

   ```ros2 pkg create --build-type ament_python --license Apache-2.0 py_pubsub```

   您的终端将返回一条消息，验证您的软件包的创建 py_pubsub 及其所有必要的文件和文件夹。 

2. 写入发布者节点

导航到 ros2_ws/src/py_pubsub/py_pubsub。 这个目录是一个 Python 包，与它嵌套的 ROS 2 包同名。 

通过输入以下命令下载示例talker code：  
`wget https://raw.githubusercontent.com/ros2/examples/rolling/rclpy/topics/minimal_publisher/examples_rclpy_minimal_publisher/publisher_member_function.py`

现在将有一个名为 publisher_member_function.py 相邻 \_\_init__.py。

使用您喜欢的文本编辑器打开文件。 

- 2.1 检查代码 

注释导入后的第一行代码 rclpy 所以它的 Node 可以使用类。
```py
import rclpy
from rclpy.node import Node
```
next 语句导入内置的字符串消息类型，节点使用该类型来构建它在主题上传递的数据。
```py
from std_msgs.msg import String
```
这些行表示节点的依赖关系。 回想一下，必须将依赖项添加到 package.xml，您将在下一节中执行此操作。

接下来， MinimalPublisher 创建类，该类继承自（或是其子类） Node。
```py
class MinimalPublisher(Node):
```
以下是类构造函数的定义。 super().\_\_init__ 调用 Node class 的构造函数，并为其指定节点名称（在本例中） minimal_publisher。

create_publisher 声明节点发布以下类型的消息 String （从 std_msgs.msg module），在名为 topic，并且“队列大小”为 10。 队列大小是必需的 QoS（服务质量）设置，用于在订阅者接收消息的速度不够快时限制排队消息的数量。

接下来，创建一个计时器，其中包含每 0.5 秒执行一次回调。 self.i 是回调中使用的计数器。

timer_callback 创建附加了计数器值的消息，并使用 get_logger().info。
```py
def timer_callback(self):
    msg = String()
    msg.data = 'Hello World: %d' % self.i
    self.publisher_.publish(msg)
    self.get_logger().info('Publishing: "%s"' % msg.data)
    self.i += 1
```
最后，定义了主要功能。
```py
def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()
```
首先 rclpy 初始化库，然后创建节点，然后“旋转”节点，以便调用其回调。 
- 2.2 添加依赖

导航一个级别返回到 ros2_ws/src/py_pubsub 目录，其中已为您创建 `setup.py`， `setup.cfg`和 `package.xml` 文件。

使用您的文本编辑器打开 `package.xml` 。

如 上一教程 所述，请确保fill in \<description>， \<maintainer> 和 \<license> 标签：
```xml
<description>Examples of minimal publisher/subscriber using rclpy</description>
<maintainer email="you@email.com">Your Name</maintainer>
<license>Apache License 2.0</license>
```
在上面的行之后，添加与节点的 import 语句相对应的以下依赖项：
```xml
<exec_depend>rclpy</exec_depend>
<exec_depend>std_msgs</exec_depend>
```
这声明了包需求 rclpy 和 std_msgs 执行其代码时。

确保保存文件。

- 2.3 添加入口点

打开 setup.py 文件。 再次，匹配 maintainer， maintainer_email， description 和 license 字段添加到您的 package.xml：
```py
maintainer='YourName',
maintainer_email='you@email.com',
description='Examples of minimal publisher/subscriber using rclpy',
license='Apache License 2.0',
```
在 entry_points 内 console_scripts 的括号领域：
```py
entry_points={
        'console_scripts': [
                'talker = py_pubsub.publisher_member_function:main',
        ],
},
```
别忘了保存。

- 2.4 检查setup.cfg 

内容 setup.cfg 文件应自动正确填充，如下所示：
```cfg
[develop]
script_dir=$base/lib/py_pubsub
[install]
install_scripts=$base/lib/py_pubsub
```
这只是告诉 setuptools 将您的可执行文件放入 lib因为 ros2 run 会在那里寻找他们。

您现在可以构建您的软件包，获取本地安装文件并运行它，但让我们先创建订阅者节点，以便您可以看到整个系统的工作情况。 

3. 写入订阅节点 

返回 ros2_ws/src/py_pubsub/py_pubsub 以创建下一个节点。 在终端中输入以下代码：
```sh
wget https://raw.githubusercontent.com/ros2/examples/humble/rclpy/topics/minimal_subscriber/examples_rclpy_minimal_subscriber/subscriber_member_function.py
```
订阅者节点的代码与发布者的代码几乎相同。 构造函数使用与发布者相同的参数创建订阅服务器。 回想一下 主题教程 中，发布者和订阅者使用的主题名称和消息类型必须匹配才能允许它们进行通信。
```py
self.subscription = self.create_subscription(
    String,
    'topic',
    self.listener_callback,
    10)
```
订阅者的构造函数和回调不包含任何计时器定义，因为它不需要计时器定义。 一旦收到消息，就会调用它的回调。

回调定义只是将信息消息连同它接收的数据一起打印到控制台。 回想一下，发布者定义 msg.data = 'Hello World: %d' % self.i
```py
def listener_callback(self, msg):
    self.get_logger().info('I heard: "%s"' % msg.data)
```
这 main 定义几乎完全相同，用订阅者替换了发布者的创建和旋转。
```py
minimal_subscriber = MinimalSubscriber()

rclpy.spin(minimal_subscriber)
```
由于此节点与发布者具有相同的依赖项，因此无需添加任何新内容 package.xml。 这 setup.cfg 文件也可以保持不变。 

- 3.2 添加入口点

重开 setup.py 并将订阅服务器节点的入口点添加到发布者的入口点下方。 这 entry_points 字段现在应如下所示：
```py
entry_points={
        'console_scripts': [
                'talker = py_pubsub.publisher_member_function:main',
                'listener = py_pubsub.subscriber_member_function:main',
        ],
},
```

确保保存文件，然后您的发布/订阅系统应该准备就绪。 

4. 构建和运行 
   
```rosdep``` 在工作区的根目录 （ ros2_ws） 在生成之前检查是否缺少依赖项： 
```sh
rosdep install -i --from-path src --rosdistro humble -y
```
仍然在工作区的根目录下， ros2_ws，构建新包：
```sh
colcon build --packages-select py_pubsub
```
打开一个新终端，导航到 ros2_ws，并获取安装文件：
```sh
source install/setup.bash
```
现在运行 talker 节点：
```sh
ros2 run py_pubsub talker
```
打开另一个终端，从内部获取设置文件 ros2_ws 再次，然后启动侦听器节点：
```sh
ros2 run py_pubsub listener
```
### 编写简单的服务和客户端 （C++）
当节点使用服务进行通信时，发送数据请求的节点称为客户端节点，响应请求的节点称为服务节点。  
请求和响应的结构由 .srv 文件决定。  

1. 创建软件包

    打开一个新终端并 获取您的 ROS 2 安装 ，以便 ros2 命令将起作用。

    导航到在上一教程中创建的目录 ros2_ws 。

    导航到 ros2_ws/src 并创建一个新包：
    ```sh
    ros2 pkg create --build-type ament_cmake --license Apache-2.0 cpp_srvcli --dependencies rclcpp example_interfaces
    ```
    您的终端将返回一条消息，验证您的软件包的创建 `cpp_srvcli` 及其所有必要的文件和文件夹。

    - `--dependencies` 参数会自动将必要的依赖线添加到 `package.xml` 和 `CMakeLists.txt`。  
    - `example_interfaces` 包含  构建请求和响应所需的`.srv` 文件 。  
    ```srv
    int64 a
    int64 b
    ---
    int64 sum
    ```
    前两行是请求的参数，破折号下方是响应

    - 1.1 更新 package.xml

    因为你使用了 --dependencies 选项，您不必手动将依赖项添加到 package.xml 或 CMakeLists.txt。

    不过，与往常一样，请**确保将描述、维护者电子邮件和姓名以及许可证信息添加到 package.xml**。
    ```sh
    <description>C++ client server tutorial</description>
    <maintainer email="you@email.com">Your Name</maintainer>
    <license>Apache License 2.0</license>
    ```
2. 写入服务节点 

    在 ros2_ws/src/cpp_srvcli/src 目录下，创建一个名为 add_two_ints_server.cpp 的文件，并将以下代码粘贴到其中：
    ```cpp
    #include "rclcpp/rclcpp.hpp"
    #include "example_interfaces/srv/add_two_ints.hpp"

    #include <memory>

    void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
            std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>      response)
    {
    response->sum = request->a + request->b;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
                    request->a, request->b);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
    }

    int main(int argc, char **argv)
    {
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service =
        node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

    rclcpp::spin(node);
    rclcpp::shutdown();
    }
    ```
    2.1 检查代码 

    前两个 #include 语句是包依赖项。

    这 add 函数从请求中添加两个整数，并为响应提供总和，同时使用日志通知控制台其状态。
    ```cpp
    void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
            std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>      response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
            request->a, request->b);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
    }
    ```
    这 main 函数逐行完成以下操作：

    - 初始化 ROS 2 C++ 客户端库：

        rclcpp::init(argc, argv);

    - 创建一个名为 add_two_ints_server：

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

    - 创建名为 add_two_ints 并自动通过网络通告它 &add 方法：

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service =
    node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

    - 准备就绪时打印日志消息：

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

    - 旋转节点，使服务可用。

    rclcpp::spin(node);

    - 2.2 添加可执行文件 

    add_executable 宏生成可执行文件，让您可以使用 ros2 run。 将以下代码块添加到 CMakeLists.txt 以创建名为 server 的可执行文件：
    ```cmake
    add_executable(server src/add_two_ints_server.cpp)
    ament_target_dependencies(server rclcpp example_interfaces)
    ```
    此时 ros2 run 可以找到可执行文件，将以下行添加到文件末尾，right before ament_package()：
    ```cmake
    install(TARGETS
        server
    DESTINATION lib/${PROJECT_NAME})
    ```
    您现在可以构建您的软件包，获取本地安装文件并运行它，但让我们先创建客户端节点，以便您可以看到整个系统的工作情况。 

3. 写入客户端节点

    里面 ros2_ws/src/cpp_srvcli/src 目录下，创建一个名为 add_two_ints_client.cpp 并将以下代码粘贴到其中：
    ```cpp
    #include "rclcpp/rclcpp.hpp"
    #include "example_interfaces/srv/add_two_ints.hpp"

    #include <chrono>
    #include <cstdlib>
    #include <memory>

    using namespace std::chrono_literals;

    int main(int argc, char **argv)
    {
    rclcpp::init(argc, argv);

    if (argc != 3) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
        return 1;
    }

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client =
        node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = atoll(argv[1]);
    request->b = atoll(argv[2]);

    while (!client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
        return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = client->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
    }

    rclcpp::shutdown();
    return 0;
    }
    ```
    - 3.1 检查代码

    与服务节点类似，以下代码行创建节点，然后为该节点创建客户机：
    ```cpp
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client =
    node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    ```
    接下来，创建请求。 其结构由 .srv 前面提到的文件。
    ```cpp
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = atoll(argv[1]);
    request->b = atoll(argv[2]);
    ```
    这 while loop 给客户端 1 秒钟的时间来搜索网络中的服务节点。 如果找不到任何内容，它将继续等待。
    ```cpp
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    ```
    如果客户端被取消（例如，您输入 Ctrl+C 进入终端），它将返回一条错误日志消息，指出它已中断。
    ```cpp
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
    ```
    然后客户端发送其请求，节点旋转直到收到响应或失败。 

    - 3.2 添加可执行文件

    返回 CMakeLists.txt 为新节点添加可执行文件和目标。 从自动生成的文件中删除一些不必要的样板后，您的 CMakeLists.txt 应如下所示：
    ```cmake
    cmake_minimum_required(VERSION 3.5)
    project(cpp_srvcli)

    find_package(ament_cmake REQUIRED)
    find_package(rclcpp REQUIRED)
    find_package(example_interfaces REQUIRED)

    add_executable(server src/add_two_ints_server.cpp)
    ament_target_dependencies(server rclcpp example_interfaces)

    add_executable(client src/add_two_ints_client.cpp)
    ament_target_dependencies(client rclcpp example_interfaces)

    install(TARGETS
    server
    client
    DESTINATION lib/${PROJECT_NAME})

    ament_package()
    ```

4. 建立和运行
   
    这是很好的做法运行 rosdep 在工作区的根目录 （ ros2_ws） 以在生成之前检查是否缺少依赖项： 
    ```sh
    rosdep install -i --from-path src --rosdistro humble -y
    ```
    导航回到根本的工作空间， ros2_ws 和建立新的包装：
    ```sh
    colcon build --packages-select cpp_srvcli
    ```
    打开一个新终端的导航向 ros2_ws 和源的设置文件：
    ```
    source install/setup.bash
    ```
    现在运行的业务的节点：
    ```
    ros2 run cpp_srvcli server
    ```
    终端应该回到以下消息，然后等待：

    [INFO] [rclcpp]: Ready to add two ints.

    打开另一端，源安装的文件里面 ros2_ws再次。 启动的客户的节点，随后通过的任何两个整数分隔的空间：
    ```
    ros2 run cpp_srvcli client 2 3
    ```
您创建了两个节点来通过服务请求和响应数据。 您已将其依赖项和可执行文件添加到包配置文件中，以便可以构建和运行它们，并查看正在工作的服务/客户端系统。 
### 编写简单的服务和客户端 （Python）
### 创建自定义 msg 和 srv 文件
- 定义自定义接口文件 （ .msg 和 .srv），并将它们与 Python 和 C++ 节点一起使用。   
在前面的教程中，您利用消息和服务接口来了解 主题 、 服务 以及简单的发布者/订阅者 （ C++ / /Python Python） 和服务/客户端 （ C++ /Python） 节点。 在这些情况下，您使用的接口是预定义的。 

1. 创建一个新包

    在本教程中，您将创建自定义 `.msg` 和 `.srv` 文件，然后在单独的包中使用它们。 这两个包应位于同一工作区中。

    由于我们将使用在前面教程中创建的 pub/sub 和 service/client 包，因此请确保您与这些包位于同一工作区 （ ros2_ws/src），然后运行以下命令以创建新包：
    ```sh
    ros2 pkg create --build-type ament_cmake --license Apache-2.0 tutorial_interfaces
    ```
    tutorial_interfaces 是新包的名称。 请注意，它是且只能是 CMake 包，但这并不限制您可以在哪种类型的包中使用消息和服务。 您可以在 CMake 包中创建自己的自定义接口，然后在 C++ 或 Python 节点中使用它，这将在上一节中介绍。

    `.msg` 和 `.srv` 文件需要放在名为 msg 和 srv 的文件夹中以分别。 在 ros2_ws/src/tutorial_interfaces：
    ```
    mkdir msg srv
    ```
2. 创建自定义定义
   - 2.1 msg定义

   在 tutorial_interfaces/msg 目录，创建一个新文件，称为 Num.msg 用一行代码声明其数据结构：
   ```msg
   int64 num
   ```
   这是一条自定义消息，用于传输一个名为 num 的单64位整数。

   同样在 tutorial_interfaces/msg 目录，创建一个新文件，称为 Sphere.msg 包含以下内容：
   ```
   geometry_msgs/Point center
   float64 radius
   ```
   此自定义消息使用来自另一个消息包 （ geometry_msgs/Point 在这种情况下）。

   - 2.2 SRV 定义

   返回 tutorial_interfaces/srv 目录，创建一个新文件，称为 AddThreeInts.srv 具有以下请求和响应结构：
   ```
   int64 a
   int64 b
   int64 c
   ---
   int64 sum
   ```
   这是您的自定义服务，它请求三个名为 a， b和 c，并使用一个名为 sum。 
3. CMakeLists.txt

   若要将定义的接口转换为特定于语言的代码（如 C++ 和 Python），以便可以在这些语言中使用它们，请将以下行添加到 CMakeLists.txt：
   ```sh
   find_package(geometry_msgs REQUIRED)
   find_package(rosidl_default_generators REQUIRED)

   rosidl_generate_interfaces(${PROJECT_NAME}
     "msg/Num.msg"
     "msg/Sphere.msg"
     "srv/AddThreeInts.srv"
     DEPENDENCIES geometry_msgs # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
   )
   ```
   >注意
   >
   >rosidl_generate_interfaces中的第一个参数（库名称）必须与 ${PROJECT_NAME} 匹配

4. package.xml

    因为接口依赖于 `rosidl_default_generators` 若要生成特定于语言的代码，需要声明对其的生成工具依赖项。 `rosidl_default_runtime` 是运行时或执行阶段依赖项，需要以便以后能够使用接口。 这 rosidl_interface_packages 是包所在的依赖项组的名称， ，应与 tutorial_interfaces 关联，使用 \<member_of_group> tag。

    在 \<package> 元素 package.xml：
    ```
    <depend>geometry_msgs</depend>
    <buildtool_depend>rosidl_default_generators</buildtool_depend>
    <exec_depend>rosidl_default_runtime</exec_depend>
    <member_of_group>rosidl_interface_packages</member_of_group>
    ```
5. 构建 tutorial_interfaces 包装 

    现在，自定义接口包的所有部分都已就绪，您可以构建该包。 在工作区的根目录 （ ~/ros2_ws），运行以下命令：
    ```
    colcon build --packages-select tutorial_interfaces
    ```
    现在，这些接口将被其他 ROS 2 软件包发现。
 
6. 确认 msg 和 srv 创建 

    在新终端中，从工作区中运行以下命令 （ ros2_ws） 获取：
    ```
    source install/setup.bash
    ```
    现在，您可以使用 ros2 interface show 命令：
    ```
    ros2 interface show tutorial_interfaces/msg/Num
    ```
    应返回：
    ```
    int64 num
    ```
    ---
    ```
    ros2 interface show tutorial_interfaces/msg/Sphere
    ```
    应返回：
    ```
    geometry_msgs/Point center
            float64 x
            float64 y
            float64 z
    float64 radius
    ```
    ---
    ```
    ros2 interface show tutorial_interfaces/srv/AddThreeInts
    ```
    应返回：
    ```
    int64 a
    int64 b
    int64 c
    ---
    int64 sum
    ```
7. 测试新接口 

对于此步骤，可以使用在前面的教程中创建的包。 对节点进行一些简单的修改， CMakeLists.txt 和 package.xml 文件将允许您使用新界面。
- 7.1 测试 Num.msg 使用 pub/sub 

通过对上一教程（C++ 或 Python ）中创建的发布者/订阅者包进行一些修改 ，您可以看到 Num.msg 在行动中。 由于您将标准字符串 msg 更改为数字字符串，因此输出将略有不同。 
- c++

- **publisher**
  
```cpp
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"                                            // CHANGE

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("topic", 10);  // CHANGE
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = tutorial_interfaces::msg::Num();                                   // CHANGE
    message.num = this->count_++;                                                     // CHANGE
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.num << "'");    // CHANGE
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;             // CHANGE
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
```
- **Subscriber**

```cpp
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/num.hpp"                                       // CHANGE

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<tutorial_interfaces::msg::Num>(    // CHANGE
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const tutorial_interfaces::msg::Num & msg) const  // CHANGE
  {
    RCLCPP_INFO_STREAM(this->get_logger(), "I heard: '" << msg.num << "'");     // CHANGE
  }
  rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscription_;  // CHANGE
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
```

- Python

- **publisher**
  
```py
import rclpy
from rclpy.node import Node

from tutorial_interfaces.msg import Num                            # CHANGE


class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(Num, 'topic', 10)  # CHANGE
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = Num()                                                # CHANGE
        msg.num = self.i                                           # CHANGE
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%d"' % msg.num)       # CHANGE
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
```
- **Subscriber**

```py
import rclpy
from rclpy.node import Node

from tutorial_interfaces.msg import Num                        # CHANGE


class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            Num,                                               # CHANGE
            'topic',
            self.listener_callback,
            10)
        self.subscription

    def listener_callback(self, msg):
            self.get_logger().info('I heard: "%d"' % msg.num)  # CHANGE


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
```


- CMakeLists.txt

Add the following lines (C++ only):
```cmake


#...

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)                      # CHANGE

add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp tutorial_interfaces)    # CHANGE

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp tutorial_interfaces)  # CHANGE

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

ament_package()
```

- package.xml
  - c++

    Add the following line:
    ```
    <depend>tutorial_interfaces</depend>
    ```
  - py
    ```<exec_depend>tutorial_interfaces</exec_depend>```
After making the above edits and saving all the changes, build the package:

On Linux/macOS:

colcon build --packages-select cpp_pubsub

On Windows:

colcon build --merge-install --packages-select cpp_pubsub

Then open two new terminals, source ros2_ws in each, and run:

ros2 run cpp_pubsub talker

ros2 run cpp_pubsub listener

On

colcon build --packages-select py_pubsub

On Windows:

colcon build --merge-install --packages-select py_pubsub

Then open two new terminals, source ros2_ws in each, and run:

ros2 run py_pubsub talker

ros2 run py_pubsub listener

Since Num.msg relays only an integer, the talker should only be publishing integer values, as opposed to the string it published previously:

由于Num.msg只中继一个整数，因此讲话者应该只发布整数值，而不是之前发布的字符串：

[INFO] [minimal_publisher]: Publishing: '0'
[INFO] [minimal_publisher]: Publishing: '1'
[INFO] [minimal_publisher]: Publishing: '2'

  - 7.2 测试 AddThreeInts.srv 使用服务/客户端 

）中创建的服务/客户端包进行一些修改 通过对上一教程（C++ 或 Python ，您可以看到 AddThreeInts.srv 在行动中。 由于要将原来的两个整数请求 srv 更改为三个整数请求 srv，因此输出将略有不同。

- Service服务
  - c++
```cpp
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"                                        // CHANGE

#include <memory>

void add(const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,     // CHANGE
          std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response>       response)  // CHANGE
{
  response->sum = request->a + request->b + request->c;                                      // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld" " c: %ld",  // CHANGE
                request->a, request->b, request->c);                                         // CHANGE
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");   // CHANGE

  rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr service =               // CHANGE
    node->create_service<tutorial_interfaces::srv::AddThreeInts>("add_three_ints",  &add);   // CHANGE

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");                     // CHANGE

  rclcpp::spin(node);
  rclcpp::shutdown();
}
```
- Cilent客户
  - c++
``` c++
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"                                       // CHANGE

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 4) { // CHANGE
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_three_ints_client X Y Z");      // CHANGE
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_client");  // CHANGE
  rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client =                // CHANGE
    node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");          // CHANGE

  auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();       // CHANGE
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);
  request->c = atoll(argv[3]);                                                              // CHANGE

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_three_ints");    // CHANGE
  }

  rclcpp::shutdown();
  return 0;
}
```

- Service服务
  - py
```py
from tutorial_interfaces.srv import AddThreeInts                                                           # CHANGE

import rclpy
from rclpy.node import Node


class MinimalService(Node):

    def __init__(self):
        super().__init__('minimal_service')
        self.srv = self.create_service(AddThreeInts, 'add_three_ints', self.add_three_ints_callback)       # CHANGE

    def add_three_ints_callback(self, request, response):
        response.sum = request.a + request.b + request.c                                                   # CHANGE
        self.get_logger().info('Incoming request\na: %d b: %d c: %d' % (request.a, request.b, request.c))  # CHANGE

        return response

def main(args=None):
    rclpy.init(args=args)

    minimal_service = MinimalService()

    rclpy.spin(minimal_service)

    rclpy.shutdown()

if __name__ == '__main__':
    main()
```
- Cilent客户
  - py
```py 
from tutorial_interfaces.srv import AddThreeInts                            # CHANGE
import sys
import rclpy
from rclpy.node import Node


class MinimalClientAsync(Node):

    def __init__(self):
        super().__init__('minimal_client_async')
        self.cli = self.create_client(AddThreeInts, 'add_three_ints')       # CHANGE
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = AddThreeInts.Request()                                   # CHANGE

    def send_request(self):
        self.req.a = int(sys.argv[1])
        self.req.b = int(sys.argv[2])
        self.req.c = int(sys.argv[3])                                       # CHANGE
        self.future = self.cli.call_async(self.req)


def main(args=None):
    rclpy.init(args=args)

    minimal_client = MinimalClientAsync()
    minimal_client.send_request()

    while rclpy.ok():
        rclpy.spin_once(minimal_client)
        if minimal_client.future.done():
            try:
                response = minimal_client.future.result()
            except Exception as e:
                minimal_client.get_logger().info(
                    'Service call failed %r' % (e,))
            else:
                minimal_client.get_logger().info(
                    'Result of add_three_ints: for %d + %d + %d = %d' %                                # CHANGE
                    (minimal_client.req.a, minimal_client.req.b, minimal_client.req.c, response.sum))  # CHANGE
            break

    minimal_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
```
CMakeLists.txt

添加以下行（仅限 C++）：
```cmake
#...

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tutorial_interfaces REQUIRED)         # CHANGE

add_executable(server src/add_two_ints_server.cpp)
ament_target_dependencies(server
  rclcpp tutorial_interfaces)                      # CHANGE

add_executable(client src/add_two_ints_client.cpp)
ament_target_dependencies(client
  rclcpp tutorial_interfaces)                      # CHANGE

install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})

ament_package()


```
package.xml

添加以下行：
c++
```
<depend>tutorial_interfaces</depend>
```
py
```
<exec_depend>tutorial_interfaces</exec_depend>
```
进行上述编辑并保存所有更改后，生成包：

- c++

在 Linux/macOS 上：
```
colcon build --packages-select cpp_srvcli
```
在 Windows 上：
```
colcon build --merge-install --packages-select cpp_srvcli
```
然后打开两个新终端，源 ros2_ws 在每个中，并运行：
```
ros2 run cpp_srvcli server
```
```
ros2 run cpp_srvcli client 2 3 1
```
- python

在 Linux/macOS 上：
```
colcon build --packages-select py_srvcli
```
在 Windows 上：
```
colcon build --merge-install --packages-select py_srvcli
```
然后打开两个新终端，源 ros2_ws 在每个中，并运行：
```
ros2 run py_srvcli service
```
```
ros2 run py_srvcli client 2 3 1
```
在本教程中，您学习了如何在自定义接口自己的包中创建自定义接口，以及如何在其他包中使用这些接口。

本教程仅触及了有关定义自定义接口的表面。 您可以在 关于 ROS 2 接口 中了解更多信息。 
### 实现自定义接口
在前面的 教程 中，你学习了如何创建自定义 msg 和 srv 接口。

虽然最佳做法是在专用接口包中声明接口，但有时在一个包中声明、创建和使用接口会很方便。

回想一下，接口目前只能在 CMake 包中定义。 但是，可以在 CMake 包中包含 Python 库和节点（使用 ament_cmake_python ），因此您可以在一个包中一起定义接口和 Python 节点。 为了简单起见，我们将在这里使用 CMake 包和 C++ 节点。

本教程将重点介绍 msg 接口类型，但此处的步骤适用于所有接口类型。 

1. 创建软件包  

在工作区中 src 目录，创建包 more_interfaces 并在其中为 msg 文件创建一个目录：

ros2 pkg create --build-type ament_cmake --license Apache-2.0 more_interfaces
mkdir more_interfaces/msg

2. 创建消息文件 

里面 more_interfaces/msg，创建一个新文件 AddressBook.msg，然后粘贴以下代码以创建一条消息，用于携带有关个人的信息：
```
uint8 PHONE_TYPE_HOME=0
uint8 PHONE_TYPE_WORK=1
uint8 PHONE_TYPE_MOBILE=2

string first_name
string last_name
string phone_number
uint8 phone_type
```
此消息由以下字段组成：

   - first_name：字符串类型

   - last_name：字符串类型

   - phone_number：字符串类型

   - phone_type：类型为 uint8，定义了多个命名常量值

请注意，可以为消息定义中的字段设置默认值。 有关 ，请参阅接口 自定义接口的更多方法

接下来，我们需要确保 msg 文件转换为 C++、Python 和其他语言的源代码。 
  - 2.1 构建消息文件

打开 package.xml 并添加以下行：
```
<buildtool_depend>rosidl_default_generators</buildtool_depend>

<exec_depend>rosidl_default_runtime</exec_depend>

<member_of_group>rosidl_interface_packages</member_of_group>
```
请注意，在构建时，我们需要 rosidl_default_generators，而在运行时，我们只需要 rosidl_default_runtime。

打开 CMakeLists.txt 并添加以下行：

查找从 msg/srv 文件生成消息代码的包：
```
find_package(rosidl_default_generators REQUIRED)
```
声明要生成的消息列表：
```
set(msg_files
  "msg/AddressBook.msg"
)
```
通过手动添加.msg文件，我们可以确保 CMake 知道在添加其他.msg文件后何时必须重新配置项目。

生成消息：
```
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)
```
此外，请确保导出消息运行时依赖项：
```
ament_export_dependencies(rosidl_default_runtime)
```
现在，你已准备好从 msg 定义生成源文件。 我们暂时跳过编译步骤，因为我们将在下面的步骤 4 中一起完成所有操作。 
- 2.2 （额外） 设置多个接口 

    注意

    你可以使用 set 在 CMakeLists.txt 要整齐地列出所有接口，请执行以下操作：
    ```
    set(msg_files
    "msg/Message1.msg"
    "msg/Message2.msg"
    # etc
    )

    set(srv_files
    "srv/Service1.srv"
    "srv/Service2.srv"
    # etc
    )
    ```
    并像这样一次生成所有列表：

    rosidl_generate_interfaces(${PROJECT_NAME}
    ${msg_files}
    ${srv_files}
    )
3 使用同一软件包中的接口 

现在我们可以开始编写使用此消息的代码了。

在 more_interfaces/src 创建一个名为 publish_address_book.cpp 并粘贴以下代码：
```cpp
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
  AddressBookPublisher()
  : Node("address_book_publisher")
  {
    address_book_publisher_ =
      this->create_publisher<more_interfaces::msg::AddressBook>("address_book", 10);

    auto publish_msg = [this]() -> void {
        auto message = more_interfaces::msg::AddressBook();

        message.first_name = "John";
        message.last_name = "Doe";
        message.phone_number = "1234567890";
        message.phone_type = message.PHONE_TYPE_MOBILE;

        std::cout << "Publishing Contact\nFirst:" << message.first_name <<
          "  Last:" << message.last_name << std::endl;

        this->address_book_publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr address_book_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AddressBookPublisher>());
  rclcpp::shutdown();

  return 0;
}
```
3.1 代码解释 

包括我们新创建的标题 AddressBook.msg。
```cpp
#include "more_interfaces/msg/address_book.hpp"
```
创建一个节点和 AddressBook 发行人。
```cpp
using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
  AddressBookPublisher()
  : Node("address_book_publisher")
  {
    address_book_publisher_ =
      this->create_publisher<more_interfaces::msg::AddressBook>("address_book");
```
创建回调以定期发布消息。
```cpp
auto publish_msg = [this]() -> void {
```

创建一个我们稍后将发布的AddressBook消息实例。
```cpp
auto message = more_interfaces::msg::AddressBook();
```
填充通讯簿AddressBook字段。
```
message.first_name = "John";
message.last_name = "Doe";
message.phone_number = "1234567890";
message.phone_type = message.PHONE_TYPE_MOBILE;
```

最后定期发送消息。
```cpp
std::cout << "Publishing Contact\nFirst:" << message.first_name <<
  "  Last:" << message.last_name << std::endl;

this->address_book_publisher_->publish(message);
```

创建一个1秒计时器，每秒调用我们的publish_msg函数。
```cpp
timer_ = this->create_wall_timer(1s, publish_msg);
```
- 3.2 Build the publisher


我们需要在<kbd>CMakeLists.txt</kbd>中为此节点创建一个新目标：
```cmake
find_package(rclcpp REQUIRED)

add_executable(publish_address_book src/publish_address_book.cpp)
ament_target_dependencies(publish_address_book rclcpp)

install(TARGETS
    publish_address_book
  DESTINATION lib/${PROJECT_NAME})
```
- 3.3 与接口的链接 

为了使用同一包中生成的消息，我们需要使用以下 CMake 代码：
```cmake
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(publish_address_book "${cpp_typesupport_target}")
```
这将查找从 AddressBook.msg 生成的相关 C++ 代码并允许您的目标链接到它。

您可能已经注意到，当使用的接口来自独立构建的不同包时，此步骤不是必需的。 **仅当要使用与定义接口的接口相同的包中的接口时，才需要此 CMake 代码**。

4 试一试 

返回到工作区的根目录以生成包：
```sh
cd ~/ros2_ws
colcon build --packages-up-to more_interfaces
```
然后获取工作区并运行发布者：
```sh
source install/local_setup.bash
ros2 run more_interfaces publish_address_book
```
您应该会看到发布者转发您定义的消息，包括您在 publish_address_book.cpp。

要确认消息是否在 address_book 主题，打开另一个终端，获取工作区，然后调用 topic echo：
```sh
source install/setup.bash
ros2 topic echo /address_book
```
在本教程中，我们不会创建订阅者，但您可以尝试自己编写一个订阅者进行练习（使用编写 简单的发布者和订阅者 （C++） 来提供帮助）。

5.（额外） 使用现有接口定义 

注意

您可以在新的接口定义中使用现有接口定义。 例如，假设有一条名为 Contact.msg 属于名为 rosidl_tutorials_msgs。 假设它的定义与我们定制的 AddressBook.msg 定义前面的界面相同。

在这种情况下，您可以定义 AddressBook.msg （包中 带有 节点的接口）作为类型 Contact包中的接口 （单独 ）。 您甚至可以定义 AddressBook.msg 作为 数组 类型的 Contact这样：

rosidl_tutorials_msgs/Contact[] address_book

要生成此消息，您需要声明对 Contact.msg's 包 rosidl_tutorials_msgs在 package.xml：

<build_depend>rosidl_tutorials_msgs</build_depend>

<exec_depend>rosidl_tutorials_msgs</exec_depend>

而在 CMakeLists.txt：

find_package(rosidl_tutorials_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES rosidl_tutorials_msgs
)

您还需要包含 Contact.msg 在发布者节点中，以便能够添加 contacts 到你的 address_book。

#include "rosidl_tutorials_msgs/msg/contact.hpp"

您可以将回调更改为如下所示：
```cpp
auto publish_msg = [this]() -> void {
   auto msg = std::make_shared<more_interfaces::msg::AddressBook>();
   {
     rosidl_tutorials_msgs::msg::Contact contact;
     contact.first_name = "John";
     contact.last_name = "Doe";
     contact.phone_number = "1234567890";
     contact.phone_type = message.PHONE_TYPE_MOBILE;
     msg->address_book.push_back(contact);
   }
   {
     rosidl_tutorials_msgs::msg::Contact contact;
     contact.first_name = "Jane";
     contact.last_name = "Doe";
     contact.phone_number = "4254242424";
     contact.phone_type = message.PHONE_TYPE_HOME;
     msg->address_book.push_back(contact);
   }

   std::cout << "Publishing address book:" << std::endl;
   for (auto contact : msg->address_book) {
     std::cout << "First:" << contact.first_name << "  Last:" << contact.last_name <<
       std::endl;
   }

   address_book_publisher_->publish(*msg);
 };
```
生成并运行这些更改将显示按预期定义的 msg 以及上面定义的 msg 数组。
摘要 

在本教程中，您尝试了用于定义接口的不同字段类型，然后在使用它的同一包中构建了一个接口。

您还学习了如何使用另一个接口作为字段类型，以及 package.xml， CMakeLists.txt和 #include 使用该功能所需的语句。

### 在类中使用参数 （C++）


在创建自己的 节点 时，有时需要添加可以从启动文件设置的参数。

本教程将向您展示如何在 C++ 类中创建这些参数，以及如何在启动文件中设置它们。
先决条件 

在前面的教程中，你学习了如何 创建工作区 和 创建包 。 您还了解 的参数 了 ROS 2 系统中
任务 
1. 创建软件包 

打开一个新终端并 获取您的 ROS 2 安装 ，以便 ros2 命令将起作用。

按照 以下说明 创建名为 ros2_ws。

回想一下，包应该在 src目录，而不是工作区的根目录。 导航到 ros2_ws/src 并创建一个新包：

ros2 pkg create --build-type ament_cmake --license Apache-2.0 cpp_parameters --dependencies rclcpp

您的终端将返回一条消息，验证您的软件包的创建 cpp_parameters 及其所有必要的文件和文件夹。

这 --dependencies 参数会自动将必要的依赖线添加到 package.xml 和 CMakeLists.txt。
  - 1.1 更新 package.xml

因为你使用了 --dependencies 选项，您不必手动将依赖项添加到 package.xml 或 CMakeLists.txt。

不过，与往常一样，请确保将描述、维护者电子邮件和姓名以及许可证信息添加到 package.xml。
```
<description>C++ parameter tutorial</description>
<maintainer email="you@email.com">Your Name</maintainer>
<license>Apache License 2.0</license>
```
2. 写入 C++ 节点  

在 ros2_ws/src/cpp_parameters/src 目录下，创建一个名为 cpp_parameters_node.cpp 的文件并将以下代码粘贴到其中：
```cpp
#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    //auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
    //param_desc.description = "This parameter is mine!";
    this->declare_parameter("my_parameter", "world");

    timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalParam::timer_callback, this));
  }

  void timer_callback()
  {
    std::string my_param = this->get_parameter("my_parameter").as_string();

    RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());

    //std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", "world")};
    //this->set_parameters(all_new_parameters);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}
```
  - 2.1 检查代码 

这 #include 顶部的语句是包依赖项。

下一段代码创建类和构造函数。 此构造函数的第一行创建名称为 my_parameter ，默认值为 world。 参数类型是从默认值推断出来的，因此在本例中，它将设置为字符串类型。 接下来 timer_ 初始化周期为 1000ms，这会导致 timer_callback 函数每秒执行一次。
```
void timer_callback()
{
  std::string my_param = this->get_parameter("my_parameter").as_string();

  RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());

  std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", "world")};
  this->set_parameters(all_new_parameters);
}
```
最后是声明 timer_。
```
private:
  rclcpp::TimerBase::SharedPtr timer_;
```
 MinimalParam 之后是我们的 main 。 这里 ROS 2 被初始化了，一个 MinimalParam 类被构造，并且 rclcpp::spin 开始处理来自节点的数据。
```
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}
```
  - 2.1.1 (Optional) Add ParameterDescriptor


也可以为参数设置描述符。描述符允许您指定参数及其约束的文本描述，例如使其为只读、指定范围等。要实现这一点，必须将构造函数中的代码更改为：
```cpp
// ...

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
    param_desc.description = "This parameter is mine!";

    this->declare_parameter("my_parameter", "world", param_desc);

    timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalParam::timer_callback, this));
  }
```

代码的其余部分保持不变。一旦运行了节点，就可以运行`ros2 param describe/minimal_param_node my_parameter`来查看类型和描述。

  - 2.2 Add executable

Now open the `CMakeLists.txt file`. Below the dependency `find_package(rclcpp REQUIRED) `add the following lines of code.
```cmake
add_executable(minimal_param_node src/cpp_parameters_node.cpp)
ament_target_dependencies(minimal_param_node rclcpp)

install(TARGETS
    minimal_param_node
  DESTINATION lib/${PROJECT_NAME}
)
```
3. Build and run

在构建之前，最好在工作区的根目录（ros2_ws）中运行`rosdep`，以检查是否缺少依赖项：

    rosdep install -i --from-path src --rosdistro humble -y


导航回工作区的根目录ros2_ws，并构建新的包：

    colcon build --packages-select cpp_parameters


打开一个新终端，导航到ros2_ws，并获取安装文件：

    source install/setup.bash


现在运行节点：

    ros2 run cpp_parameters minimal_param_node


终端应每秒返回以下消息：

    [INFO] [minimal_param_node]: Hello world!


现在您可以看到参数的默认值，但您希望能够自己设置它。有两种方法可以做到这一点。

  - 3.1 通过控制台进行更改

本部分将使用您从教程中获得的有关参数的知识，并将其应用于刚刚创建的节点。

Make sure the node is running:

    ros2 run cpp_parameters minimal_param_node

Open another terminal, source the setup files from inside ros2_ws again, and enter the following line:

    ros2 param list


在那里您将看到自定义参数my_parameter。要更改它，只需在控制台中运行以下行：

    ros2 param set /minimal_param_node my_parameter earth

你知道，如果你成功地获得了`Set parameter successful`，它会进行得很好。如果您查看另一个终端，您应该会看到输出更改为 `[INFO] [minimal_param_node]: Hello earth!`

  - 3.2 通过启动文件进行更改

您也可以在启动文件中设置参数，但首先需要添加启动目录。在ros2_ws/src/cpp_parameters/目录中，创建一个名为launch的新目录。在那里，创建一个名为cpp_parameters_launch.py的新文件

```py
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="cpp_parameters",
            executable="minimal_param_node",
            name="custom_minimal_param_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"my_parameter": "earth"}
            ]
        )
    ])
```

在这里，您可以看到，当我们启动节点minimal_parameter_node时，我们将my_parameter设置为earth。通过添加下面的两行，我们可以确保我们的输出打印在控制台中。

    output="screen",
    emulate_tty=True,


现在打开CMakeLists.txt文件。在前面添加的行下面，添加以下代码行。

    install(
    DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
    )

打开控制台并导航到工作区的根目录ros2_ws，然后构建新的包：

    colcon build --packages-select cpp_parameters

Then source the setup files in a new terminal:

    source install/setup.bash

Now run the node using the launch file we have just created:

===
```sh
ros2 launch cpp_parameters cpp_parameters_launch.py
```
The terminal should return the following message every second:

    [INFO] [custom_minimal_param_node]: Hello earth!


总结

您创建了一个具有自定义参数的节点，该参数可以从启动文件或命令行进行设置。您将依赖项、可执行文件和启动文件添加到包配置文件中，以便构建和运行它们，并查看参数的作用。

### （略）在类中使用参数 （Python）
Goal: Create and run a class with ROS parameters using Python.

Tutorial level: Beginner

Time: 20 minutes

### 用 ros2doctor 识别问题

背景 

当您的 ROS 2 设置未按预期运行时，您可以使用 ros2doctor 工具。

ros2doctor 检查ROS 2的方方面面，包括***平台、版本、网络、环境、运行系统***等，并警告您可能出现的错误和问题的原因。

先决条件

ros2doctor 是 ros2cli 包。 只要你有 ros2cli 已安装（任何正常安装都应该有），您将能够使用 ros2doctor。 

任务 
1. 检查您的设置 

让我们用 ros2doctor 从整体上检查一下您的常规 ROS 2 设置。 首先，在新终端中获取 ROS 2，然后输入以下命令：
```
ros2 doctor
```
这将对所有设置模块进行检查，并返回警告和错误。

如果您的 ROS 2 设置处于完美状态，您将看到类似于以下内容的消息：
```
All <n> checks passed
```
但是，返回一些警告并不罕见。 一个 UserWarning 并不意味着您的设置不可用;这更有可能只是表明某些东西的配置方式不理想。

如果您确实收到警告，它将如下所示：
```
<path>: <line>: UserWarning: <message>
```
例如 ros2doctor 如果您使用的是不稳定的 ROS 2 发行版，则会发现此警告：
```
UserWarning: Distribution <distro> is not fully supported or tested. To get more consistent features, download a stable version at https://index.ros.org/doc/ros2/Installation/
```
如果 ros2doctor 仅在您的系统中找到警告，您仍将收到 `All \<n> checks passed` 消息。

大多数检查被归类为警告，而不是错误。 主要由你（用户）来确定 ros2doctor 返回反馈的重要性 。 如果它确实在您的设置中发现一个罕见的错误，将会用 `UserWarning: ERROR:`表示，此时检查被视为失败。

你将看到类似于以下问题反馈列表的消息：
```sh
1/3 checks failed

Failed modules:  network
```
错误表示系统缺少对 ROS 2 至关重要的重要设置或功能。 应解决错误以确保系统正常运行。

2. 检查系统 

您还可以检查正在运行的 ROS 2 系统，以确定问题的可能原因。 看 ros2doctor 在一个正在运行的系统上工作，让我们运行 turtlesim，它有节点主动相互通信。

通过打开一个新终端，获取source ROS 2 并输入命令来启动系统：
```
ros2 run turtlesim turtlesim_node
```
打开另一个终端并获取 ROS 2 以运行远程操作控件：
```
ros2 run turtlesim turtle_teleop_key
```
现在在 ros2doctor 自己的终端中再次运行它。 您将看到上次运行 ros2doctor 时在您的设置中遇到的警告和错误（如果有的话）。以下是与系统本身有关的几个新警告：
```sh
UserWarning: Publisher without subscriber detected on /turtle1/color_sensor.
UserWarning: Publisher without subscriber detected on /turtle1/pose.
```

/turtlesim节点似乎向两个未订阅的主题发布数据，ros2doctor认为这可能会导致问题。


如果运行命令以回显echo /color_sensor 和 /pose 主题，这些警告将消失，因为发布者将有订阅者。

你可以尝试在turtlesim仍在运行时打开两个新终端，在每个终端中获取ROS 2，并在它们自己的终端中运行以下每个命令：
```
ros2 topic echo /turtle1/color_sensor
```
```
ros2 topic echo /turtle1/pose
```
然后在运行过 ros2doctor 的终端中再次运行它。 这时 publisher without subscriber 警告将消失。（请确保在运行echo的终端中输入Ctrl+C）。

现在，请尝试退出turtlesim窗口，或者退出teleop并再次运行ros2doctor。由于系统中的一个节点不可用，您将看到更多警告，指示不同主题的发布者没有订阅者或订阅者没有发布者。

在具有许多节点的复杂系统中，ros2doctor对于识别通信问题的可能原因将是非常宝贵的。

3. 获取完整报告 

而 ros2doctor 会让你知道有关你的网络、系统等的警告，用 `--report` 参数将为您提供更多详细信息，以帮助您分析问题。

如果您收到有关网络设置的警告，您可能想要使用 `--report` 并希望确切了解您的配置的哪个部分导致了警告。

当你需要打开一张支持票来获得ROS 2的帮助时，这也很有帮助。您可以将报告的相关部分复制并粘贴到票证中，以便帮助您的人能够更好地了解您的环境并提供更好的帮助。
It’s also very helpful when you need to open a support ticket to get help with ROS 2. You can copy and paste the relevant parts of your report into the ticket so the people helping you can better understand your environment and provide better assistance.

要获取完整报告，请在终端中输入以下命令：

```
ros2 doctor --report
```
这将返回分为五组的信息列表：
```
NETWORK CONFIGURATION
...

PLATFORM INFORMATION
...

RMW MIDDLEWARE
...

ROS 2 INFORMATION
...

TOPIC LIST
...
```

您可以将此处的信息与运行 ros2 doctor 时收到的警告进行交叉检查。例如，如果 ros2 doctor 返回警告（前面提到），表示您的发行版“未得到完全支持或测试”“not fully supported or tested”，您可以查看报告的`ROS 2 INFORMATION`部分：

```sh
distribution name      : <distro>
distribution type      : ros2
distribution status    : prerelease
release platforms      : {'<platform>': ['<version>']}
```

在这里，您可以看到分发状态distribution status为预发布prerelease，这解释了为什么它不完全受支持。

总结

ros2 doctor 将通知您 ROS 2 设置和运行系统中的问题。 您可以使用 --report 论点。

请记住， ros2doctor 不是一个调试工具;它无助于解决代码中的错误或系统的实现端。

### 创建和使用插件 （C++）

背景

pluginlib 是一个C++库，用于从ROS包中加载和卸载插件。 插件是从运行时库（即共享对象、动态链接库）加载的动态可加载类。 使用 pluginlib，您不必将应用程序与包含类的库显式链接 - 相反 pluginlib 可以在任何时候打开包含导出类的库，而无需应用程序事先了解该库或包含类定义的头文件。 插件可用于扩展/修改应用程序行为，而无需应用程序源代码。 

