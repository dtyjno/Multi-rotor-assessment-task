多旋翼考核任务，**上交时间为2023年12年31日23:59分**，请将git仓库的地址私发给群主。任务验收时间暂定2024年1月1日19：00，地点：西北田工作室。  
这是一个学习的过程，旨在锻炼大家自主学习和解决问题的能力 ！！！  
√—×  
# 多旋翼考核任务  
涉及知识:Linux/c++/cmake/git/python
* 注意:以下全部任务在Ubuntu系统上完成，量力而行，不要求全部完成，根据任务点给分
    
* 0． 长期任务:整个考核任务完成过程中，将使用到的知识点、遇到的报错、如何解决等整理为
学习笔记(markdown格式)
</a><div id="1"></div>
* [x] 1. <a href ="#a"> 选择虚拟机或者双系统安装Ubuntu系统【10’】，换源换输入法（使能打出中文）【5'】</a><div id="2"></div>

* [ ] 2. <a href ="#b"> 自己写一个打印"Hello Word”的函数定义在头文件(.h)里，然后在一个cpp文件中调用它(你或许需要学习g++命令或者学会编写CmakeLists.txt将它们链接到一起)【10】</a><div id="3"></div>

* [ ] 3. <a href ="#c1">编译安装或者使用包管理器安装OpenCV，自己编写代码成功调用摄像头并将窗口展示出来(c++)【15'】</a><div id="4"></div>
* [ ] 4. <a href ="#d">在github上建立自己的仓库,将完成的代码以及效果图全部传到你的仓库里,将0任务
的学习笔记作为README一起上传（使用git命令行,
学会使用.gitigignore和git lfs 用
法【10'】</a><div id="5"></div>
* [ ] 5. 安装anaconda，学习虚拟环境使用方法，配置好pytorch.环境(有独显的电脑必须安装GPU版本，没有独显的可以学习白嫖 CoLab等云服务器)【10'】
* [ ] 6. 完成SITL仿真环境搭建，成功启动Terminal、Console、Map三个窗口(可参考教程-微信公众号苍穹四轴DIY) 【15'】
* [ ] 7. 了解YOLO目标检测算法，选择一个版本，跑通源码训练和检测部分【25'】
---

多旋翼考核任务
涉及知识:Linux/c++/cmake/git/python
注意:以下全部任务在 Ubuntu系统上完成，量力而行，不要求全部完成，根据任务点给分0． 长期任务:整个考核任务完成过程中，将使用到的知识点、遇到的报错、如何解决等整理为
学习笔记(markdown格式)
1.选择虚拟机或者双系统安装Ubuntu系统【10'】，换源，换输入法(使能打出中文)【5'】
*安装 Ubuntu 系统时自定义分盘，将根目录和home目录的磁盘格式设为btrfs，并学习如何在 btrfs 文件系统下拍快照*
2． 自己写一个打印""Hello Word"的函数定义在头文件(.h)里，然后在一个cpp文件中调用它
(你或许需要学习g++命令或者学会编写CmakeLists.txt将它们链接到一起)【10'】3．编译安装或者使用包管理器安装OpenCV，自己编写代码成功调用摄像头并将窗口展示
出来 (c++)【15'】*安装能使用cuda 的 OpenCV版本（编译安装 OpenCV和OpenCV_contrib)*
4．在github上建立自己的仓库，将完成的代码以及效果图全部传到你的仓库里，将0任务
的学习笔记作为README一起上传(使用git命令行，学会.gitigignore和 git lfs用法)【10】
5．安装 anaconda，学习虚拟环境使用方法，配置好 pytorch环境(有独显的电脑必须安装
GPU版本，没有独显的可以学习白嫖CoLab等云服务器)【10'】学*习pytorch框架基本使用方法，自己写一个神经网络训练minist 数据集,使测试准确率达到95%*
6.完成SITL仿真环境搭建，成功启动Terminal、Console、Map三个窗口(可参考教程-微
信公众号苍穹四轴DIY)【15'】
7．了解YOLO目标检测算法,选择一个版本,跑通源码训练和检测部分【25'】*使用labelme
或者labellmg 制作自己的数据集并训练，将训练好的模型部署到c++上*


##  <div id="a"></div><a href ="#1"> 任务1</a>
### 1.ubuntu系统
1. 安装程序(vmware tools)  
    * ~~拷贝目录（cp）~~

    * 解压文件(tar -zxvf 文件名 (当前位置)解压到位置)
        > tar -xzvf VMwareTools-10.3.21-14772444.tar.gz

    * ~~切换目录  
        (cd 当前目录文件夹名/相对路径   
        cd /根目录+（完整路径）  
        cd \~ [\\\~\==\home])~~
        > ~~cd vmware-tools-distrib/~~

    * 以系统管理者的身份执行指令(sudo 文件名)
        >sudo ./ vmware-install.pl  

        当有网络链接时安装成功
    
    方法二
    ```
    sudo apt upgrade
    sudo apt install open-vm-tools-desktop -y
    sudo reboot
    ```

    <a href=https://blog.csdn.net/dengjin20104042056/article/details/130545759>链接</a>

2. ubuntu网卡丢失
    ```
    sudo service NetworkManager stop
    
    sudo rm  /var/lib/NetworkManager/NetworkManager.state
    
    sudo vi /etc/NetworkManager/NetworkManager.conf 
    //打开.conf文件后，找到里面的managed，将managed=false改为managed=true。
    
    sudo service NetworkManager start
    ```

3. ubuntu文件系统根目录磁盘空间不足
    在使用Ubuntu时，可能会出现下图中的提示：这需要我们对Ubuntu根目录磁盘空间进行扩展具体步骤：
    1. 打开终端，输入下面的命令行，安装gparted管理器sudo apt-get install gparted 
    2. 安装完成后，输入下面的命令行sudo gparted打开的界面如下图所示
    3. 右键点击分区，选择调整大小/移动
    4. 增大分区后，点击调整大小
    5. 点击应用全部操作通过以上步骤就完成了对Ubuntu根目录磁盘空间的扩展
##  <div id="b"></div><a href ="#2"> 任务2</a>
### cpp
1. 编辑器，编译器（IDE）
#### vscode
1. 下载linux deb x64版（文件名code_1.78.2-1683731010_amd64.deb）到Download目录[下载链接](https://code.visualstudio.com/#alt-downloads)，安装   双击deb安装包安装[教程链接](https://blog.csdn.net/m0_56484847/article/details/130831817)
    1. 在终端下进入Dowload目录
       ~~```cd Downloads/```（查找download文件夹）~~（cd 下载）  
    2. 执行本地安装命令
       ```sudo dpkg -i code_1.85.0-1701902998_amd64.deb ``` 
          * deb文件是linux发行版debian系统的安装包格式，还有像基于debian系统的发型版ubuntu等系统就是使用的deb格式安装包，我们可以使用dpkg命令进行安装管理这些deb安装包文件。
          1. 使用dpkg命令进行安装。 
           ```sudo dpkg -i deb文件名 ``` 
           2. 根据经验，通常情况下会报依赖关系的错误，我们可以使用以下的命令修复安装。  
           ```sudo apt-get install -f```
           3. 卸载软件
           如果要卸载安装的应用我们通过```sudo dpkg -l```查看已经安装的软件，并找到自己的安装的软件名。 
           最后使用```sudo dpkg -r 软件名```进行卸载。
    3. 执行code命令即可打开vscode软件
       code
       
2. 安装vscode插件  
    我们需要按照的插件有下面几个：
    1. Chinese(Simplified)，即中文环境显示，非常方便。
    2. C/C++，这个是必须的，可对 C 和 C++ 代码进行调试支持、智能提示、代码重构、代码格式化等重要基础功能
    3. C/C++ Snippets，即 C/C++重用代码块;提供了许多常见的代码片段，例如if/else语句、循环语句、函数定义、数组操作等等，C/C++ Snippets插件绝对是一个值得安装和使用的插件。
    4. C/C++ Advanced Lint,即 C/C++静态检测 ；可以在编译前检查代码中的潜在错误，并提供错误提示和建议。它还支持多种编译器，包括 GCC、Clang 和 MSVC。
    5. Code Runner，即代码运行。
    6. Include AutoComplete，即自动头文件包含。
    7. Rainbow Brackets，彩虹花括号，有助于阅读代码。
    8. One Dark Pro， VSCode 的主题。
    9. GBKtoUTF8，将 GBK 转换为 UTF8。
    10. ARM，即支持 ARM 汇编语法高亮显示。
    11. vscode-icons， VSCode 图标插件，主要是资源管理器下各个文件夹的图标。
    12. compareit，比较插件，可以用于比较两个文件的差异。
    13. DeviceTree，设备树语法插件。
    14. TabNine，一款 AI 自动补全插件
    15. Code Autocomplete，也可自动补全
    16.  cmake,提供cmake语法编译

3. 通过VSCode对C++代码进行编译、调试[教程](https://blog.csdn.net/hypc9709/article/details/129413482)
    1. VSCode中的"C/C++插件"已安装（直接在VSCode扩展商店搜索"C++"即可）
    2. 确保g++编译器和gdb调试器已安装。可以在终端查看g++是否已安装
    查看版本```g++ -v``` 
    安装 ```sudo apt-get update
    sudo apt get install build-essential gdb```
    3. 配置tasks.json  
    调试c++文件，选择"C/C++: g++ 生成活动文件”，vscode会自动生成一个.vscode文件夹和 tasks.json文件。
    4. 执行编译  
    右上角三角运行/<kbd>ctrl</kbd>+<kbd>shift</kbd>+<kbd>B</kbd>/菜单中选择运行：Terminal -> Run Build Task
    5. 调试 
    .cpp中设断点，右上角三角调试 
    * 如果想要在其他的文件夹下复用这种配置，只需要把tasks.json和launch.json文件复制到新文件夹下的.vscode目录下，然后根据需要改变对应的源文件和可执行文件的名称即可。
#### c++
1. 程序结构[sbCSDN](https://blog.csdn.net/m0_62692838/article/details/130301872)
    * 命名空间
        * C++解决了C语言中命名冲突的问题，C++使用namespace-命名空间（关键字）来解决命名冲突的问题，使用namespace定义一个域，用域进行隔离。
        * 定义命名空间,需要使用到namespace关键字,后面跟命名空间的名字,然后接一对{}即可,{}中即为命名空间的成员。
        ```cpp
        #include<stdio.h>
        #include<stdlib.h>
        namespace A
        {
        int rand = 0;
        }
        int main ( ){
        printf ( "%d\n" , rand ) ;
        return 0;
        }
        ```
        1. 命名空间中可以定义变量/函数/类型。
        2. 命名空间可以嵌套。
        3. 同一个工程中允许存在多个相同名称的命名空间,编译器最后会合成同一个命名空间中。
        *  域作用限定符  
              ```::```, ::加在变量的前面，表示去::左边的域访问。注意：如果左边的域是空白，就代表是全局域。
             ```::a
             A::a```
        * ```using namespace A```;将命名空间域A展开，但是展开就相当于将A中的内容放在全局中
        * C++标准库  
            c++标准库中的函数或者对象都是在**命名空间std**中定义的,所以我们要使用标准库中的函数或者对象都要用std来限定。   
            把C++标准库中的函数或者对象都用std这个命名空间包起来了，为了和旧的库进行区分，就定义了新的标准，不再使用.h了。
        * 输入输出函数  
           cout相当于输出函  数，cin相当于输入函数，endl相当于换行，注意cout和cin都可以连续一行插入或输出多个变量，会自动识别类型。
            ```cpp
            #include<iostream>  
            cin >> x >> d;
            cout << "hello" << x<<" "<< d<<endl
            ``` 

        * 缺省参数  
            声明函数的时候可以让最右边的连续若干个参数有缺省值，在调用函数的时候，如果不写相应位置的参数，则调用的参数就为缺省值。

    * 编译 & 执行 C++ 程序
    ```c++
    include  // 包含iostream头文件
    using namespace std; // 使用命名空间std，可以避免使用std::cout等冗长的操作
    int main() { // C++程序的入口函数
        cout << "Hello, world!\n"; // 输出Hello, world!的提示信息
        return 0; // 返回0，表示程序执行正常结束
    }
    ```
2. 头文件
    * 头文件(.h)  
    * 在写头文件时需要注意，在开头和结尾处必须按照如下样式加上预编译语句（如下）：
    ```cpp
    #ifndef CIRCLE_H
    #define  CIRCLE_H

    // 你的代码写在这里
    class  Circle
    {
    private:
        double r;//半径
    public:
        Circle();//构造函数
        Circle(double R);//构造函数
        double Area();//求面积函数
    } ;

    #endif
    ```
    这样做是为了防止重复编译，不这样做就有可能出错。
    * 具体实现(.cpp)  
        在源文件夹里新建一个Circle.cpp的文件，它的内容如下：
        ```cpp
        #include  " Circle.h "

        Circle::Circle()
        {
            this->r=5.0;
        }

        Circle::Circle( double  R)
        {
            this->r=R;
        }

        double  Circle:: Area()
        {
            return 3.14*r*r;
        } 
        ```
    * 源文件(.cpp)  
    main.cpp来测试我们写的Circle类，它的内容如下：
    ```cpp
    #include  < iostream >  
    #include  " Circle.h "
    using   namespace  std;

     int  main()
    {
        Circle c(3);
        cout<<"Area="<<c.Area()<<endl;
        return 1;
    }
    ```


3. 把源代码保存在一个文件中，以及如何编译并运行它。下面是简单的步骤：

    * 打开一个文本编辑器，添加上述代码。
    * 保存文件为 hello.cpp。
    * 打开命令提示符，进入到保存文件所在的目录。
    * 键入 '```g++ hello.cpp ```'，输入回车，编译代码。如果代码中没有错误，命令提示符会跳到下一行，并生成 a.out 可执行文件。
    * 现在，键入 '```./a.out```' 来运行程序。
    * 您可以看到屏幕上显示 ' Hello World
     
dtyjno: @workspace /fix 

---

dtyjno: 写一个打印"Hello Word”的函数定义在头文件(.h)里，然后在一个cpp文件中调用它(你或许需要学习g++命令或者学会编写CmakeLists.txt将它们链接到一起)

GitHub Copilot: 首先，我们需要在头文件中声明一个函数，然后在cpp文件中定义这个函数。最后，我们在另一个cpp文件中调用这个函数。

以下是这个过程的详细步骤：

1. 创建一个头文件（例如，`hello.h`）并声明函数：

```c
// hello.h
#ifndef HELLO_H
#define HELLO_H

void print_hello();

#endif // HELLO_H
```

2. 在一个cpp文件（例如，`hello.cpp`）中包含头文件并定义函数：

```cpp
// hello.cpp
#include <iostream>
#include "hello.h"

void print_hello() {
    std::cout << "Hello World" << std::endl;
}
```

3. 在另一个cpp文件（例如，`main.cpp`）中包含头文件并调用函数：

```cpp
// main.cpp
#include "hello.h"

int main() {
    print_hello();
    return 0;
}
```

4. 使用g++命令编译并链接这两个cpp文件：

```bash
g++ -o main hello.cpp main.cpp
```

这个命令将生成一个名为`main`的可执行文件。运行这个文件将打印出"Hello World"。

注意：这些文件应该都在同一个目录下，否则你需要在包含头文件时指定正确的路径。

要使用CMake编译和链接这两个文件，你需要创建一个名为`CMakeLists.txt`的文件，该文件描述了构建过程。

以下是一个简单的`CMakeLists.txt`文件：

```cmake
cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 11)

add_executable(HelloWorld main.cpp hello.cpp)
```

这个`CMakeLists.txt`文件做了以下几件事：

1. 检查你的CMake版本是否至少为3.10。
2. 创建一个名为`HelloWorld`的项目。
3. 设置C++标准为C++11。
4. 添加一个可执行文件`HelloWorld`，它由`main.cpp`和`hello.cpp`构建。

然后，你可以在命令行中运行以下命令来构建项目：

```bash
mkdir build
cd build
cmake ..
make
```

这些命令做了以下几件事：

1. 创建一个名为`build`的目录，用于存放构建过程中生成的文件。
2. 进入`build`目录。
3. 运行CMake以生成Makefile。
4. 运行Make以构建项目。

最后，你可以运行生成的可执行文件：

```bash
./HelloWorld
```

这将打印出"Hello World"。

---
#### [cmake](https://www.coonote.com/linux-note/cmake-quick-start.html)
1. 终端输入  
    #创建并进入build目录
    mkdir build && cd build

    #构建当前目录
    cmake ..

    #使用cmake生成的makefile编译得到可执行文件
    make


    ```
    linhao@linhao-virtual-machine:~/code$ cd helloworld
    linhao@linhao-virtual-machine:~/code/helloworld$ mkdir build
    linhao@linhao-virtual-machine:~/code/helloworld$ cd build
    linhao@linhao-virtual-machine:~/code/helloworld/build$ cmake ..
    -- The C compiler identification is GNU 11.4.0
    -- The CXX compiler identification is GNU 11.4.0
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: /usr/bin/cc - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/linhao/code/helloworld/build
    linhao@linhao-virtual-machine:~/code/helloworld/build$ make
    [ 25%] Building CXX object CMakeFiles/printhello.dir/libHelloWorld.cpp.o
    [ 50%] Linking CXX static library libprinthello.a
    [ 50%] Built target printhello
    [ 75%] Building CXX object CMakeFiles/Demo.dir/useHello.cpp.o
    [100%] Linking CXX executable Demo
    [100%] Built target Demo
    linhao@linhao-virtual-machine:~/code/helloworld/build$ ./Demo
    Hello world!
    ```
2. cpp  
    问题：HelloWorld()--Hallowarld（）

##  <div id="c1"></div><a href ="#3">编译安装或者使用包管理器安装OpenCV，自己编写代码成功调用摄像头并将窗口展示出来(c++)【15'】</a>
### 下载安装
https://opencv.org/get-started/
https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html


Build core modules
```
# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
# Create build directory
mkdir -p build && cd build
# Configure
cmake  ../opencv-4.x
# Build
cmake --build .



sudo make install

pkg-config --modversion opencv  


```
https://blog.csdn.net/logani/article/details/128361925

1. ubuntu vscode无法打开源文件opencv2  

回答: 当编译时出现"fatal error: opencv2/opencv.hpp: No such file or directory"的错误时，这意味着编译器无法找到opencv2/opencv.hpp头文件。[1]解决这个问题的方法是将opencv2文件夹链接到include文件夹下，可以使用以下命令进行链接：sudo ln -s /usr/include/opencv4/opencv2 /usr/include/。[2]这样做可以让编译器能够找到所需的头文件。另外，还可以将opencv2文件夹拷贝到自己的include文件夹中，这也可以解决找不到头文件的问题。[2]这样做可以确保编译器能够正确地找到opencv2/opencv.hpp头文件。如果在编译过程中出现其他错误，比如"LNK2019 无法解析的外部符号"，这可能是由于链接错误导致的。[3]在这种情况下，您可能需要检查您的链接设置和库文件路径是否正确。


2. 引用[.reference_title]

* 查找opencv版本  
pkg-config --modversion opencv  

这个错误表明`pkg-config`在其搜索路径中找不到`opencv`包。`pkg-config`是一个帮助你在编译阶段找到库的工具。你需要将包含`opencv.pc`文件的目录添加到`PKG_CONFIG_PATH`环境变量中。

你可以使用以下命令来查找`opencv.pc`文件的位置：

```bash
sudo find / -name "opencv.pc"
```

假设你找到的`opencv.pc`文件路径为`/usr/local/lib/pkgconfig/opencv.pc`，你可以使用以下命令将其添加到`PKG_CONFIG_PATH`环境变量：

```bash
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
```

然后，你可以使用`pkg-config`来获取OpenCV的编译和链接标志：

```bash
g++ `pkg-config --cflags --libs opencv` -o cam cam.cpp
```

请注意，你可能需要根据你的OpenCV安装和系统环境来调整这些命令。

3. [ WARN:0@0.007] global cap_v4l.cpp:997 open VIDEOIO(V4L2:/dev/video0): can't open camera by index
[ERROR:0@0.012] global obsensor_uvc_stream_channel.cpp:156 getStreamChannelGroup Camera index out of range
terminate called after throwing an instance of 'cv::Exception'
  what():  OpenCV(4.8.0-dev) /home/linhao/opencv-4.x/modules/highgui/src/window.cpp:971: error: (-215:Assertion failed) size.width>0 && size.height>0 in function 'imshow'


这个错误表明OpenCV试图打开的摄像头设备（在这个例子中是设备0）无法打开。这可能是因为设备不存在，或者设备已经被其他进程占用。

你可以尝试以下方法来解决这个问题：

   1. 确保你的摄像头设备已经正确连接并且可以被你的系统识别。你可以使用`ls /dev/video*`命令来查看你的系统中的摄像头设备。

   2. 确保没有其他进程正在使用摄像头。你可以使用`lsof /dev/video0`命令来查看是否有其他进程正在使用设备0。

   3. 尝试使用其他设备索引来打开摄像头。如果你有多个摄像头设备，它们的设备索引可能是0、1、2等。

   此外，错误信息中的`size.width>0 && size.height>0 in function 'imshow'`表明你试图显示一个没有有效尺寸的图像。这可能是因为摄像头没有正确打开，所以没有读取到有效的图像帧。你需要在调用`imshow`之前检查图像帧是否有效。

g++ test2.cpp -o test2 `pkg-config --cflags --libs opencv4`  
./test2

 --cflags --libs opencv4`  
./test2
terminate called after throwing an instance of 'cv::Exception'
  what():  OpenCV(4.8.0-dev) /home/linhao/opencv-4.x/modules/highgui/src/window.cpp:1272: error: (-2:Unspecified error) The function is not implemented. Rebuild the library with Windows, GTK+ 2.x or Cocoa support. If you are on Ubuntu or Debian, install libgtk2.0-dev and pkg-config, then re-run cmake or configure script in function 'cvShowImage'

  这个错误表明你的OpenCV库没有正确地构建GUI支持。OpenCV的`imshow`函数需要一个GUI后端来显示图像，这通常是Windows、GTK+ 2.x或Cocoa。

在Ubuntu或Debian上，你需要安装`libgtk2.0-dev`和`pkg-config`，然后重新构建OpenCV。你可以按照以下步骤来操作：

   1. 安装必要的包：

   ```bash
   sudo apt-get install -y libgtk2.0-dev pkg-config
   ```

   2. 重新构建OpenCV。首先，你需要进入到你的OpenCV源代码目录，然后运行以下命令：

   ```bash
   mkdir build
   cd build
   cmake ..
   sudo make
   sudo make install
   ```

这些命令将在你的OpenCV源代码目录中创建一个新的`build`目录，然后在这个目录中构建OpenCV。`cmake ..`命令将生成Makefile，`make`命令将编译OpenCV，`sudo make install`命令将安装OpenCV。

请注意，你可能需要根据你的OpenCV安装和系统环境来调整这些命令。


Code Runner会为多种编程语言预先写好一下编译执行或者解释执行的代码，当然，由于我们这边花里胡哨需要一堆的额外编译参数，所以我们需要去修改Code Runner的默认参数，按下Ctrl + 逗号，或者点击左下角的齿轮按钮点击设置。然后搜索code runner，点击红框框框中的选项的“在setting.json中编辑”链接，如下图：


找到cpp选项，没错，我们要修改code runner对所有的后缀为.cpp的文件的默认执行动作：


可以看到，默认的编译指令就是裸的hhh，我们需要在其中加上必要的编译参数。直接将"cpp"这个键值参数改为如下就行：

"```cd $dir && g++ $fileName -o $fileNameWithoutExt -std=c++14 -I D:\\MinGW\\mingw64\\include -lopencv_core452 -lopencv_imgcodecs452 -lopencv_imgproc452 -lopencv_calib3d452 -lopencv_dnn452 -lopencv_features2d452 -lopencv_flann452 -lopencv_gapi452 -lopencv_highgui452 -lopencv_ml452 -lopencv_objdetect452 -lopencv_photo452 -lopencv_stitching452 -lopencv_video452 -lopencv_videoio452 && $dir$fileNameWithoutExt"```
改完之后一大长条：


4. 问题：/usr/bin/ld: cannot find -lhdf5
csdn
Linux编译opencv4.7报错“/usr/bin/ld: cannot find -lopencv_shape”
VScode编译中opencv的undefined reference 问题
一般来说，undefined reference to cv:: 等的问题是关于编译时依赖文件的问题，应该将包含库的路径弄好了就没问题（至少我是这样，而且网上对于具体问题应该有更具体的解决方法的文章，这个文章主要是针对Undefined Reference to cv::Mat::updateContinuityFlag()。

具体出错界面
CMakeFiles/test.dir/src/imageProcess.cpp.o: In function `cv::Mat::Mat(int, int, int, void*, unsigned long)':
/usr/local/include/opencv2/core/mat.inl.hpp:521: undefined reference to `cv::Mat::updateContinuityFlag()'

问题所在：在经过上网查找搜索以后，发现应该就是opencv版本的问题，updateContinuityFlag函数只在opencv 3.4.2及其最新版本中存在，而我使用的是Ubuntu 18.04中自带的opencv包，所以应该就是把opencv升级就好了。但是我在安装完opencv 3.4.2新版本之后，发现还是有问题，编译依然不行，经过一番挣扎后，就有了下面的解决过程，仅供参考，只是记录一下我的过程。

解决过程
1.下载安装opencv 3.4.2
（如果可以的话，试试先卸载老版本再安装新版本，不过注意删除库与其他库的依赖关系）
安装新版本，我选择的是opencv 3.4.2, 主要参考了以下文章完成了安装
链接：https://blog.csdn.net/qq_32408773/article/details/83346816
　　　https://blog.csdn.net/baidu_34971492/article/details/81665538
PS:检查自己的opencv版本可以在终端输入pkg-config opencv --modversion
　　查看linux下的opencv安装库pkg-config opencv --libs

2.修改CmakeLists.txt
参考：https://github.com/jhu-lcsr/handeye_calib_camodocal/issues/22
首先我只是修改了编译出错的cpp文件的依赖，将find_package(OpenCV REQUIRED)改为find_package(OpenCV 3.4.２ REQUIRED)，但是还是编译错误，后来发现应该要在文件最开始描述依赖文件时就要修改

3.再次编译
再次编译，没有错误了，但是有一个warning

/usr/bin/ld: warning: libopencv_imgproc.so.3.4, needed by /usr/local/lib/libopencv_highgui.so.3.4.2, may conflict with libopencv_imgproc.so.3.2
/usr/bin/ld: warning: libopencv_core.so.3.4, needed by /usr/local/lib/libopencv_highgui.so.3.4.2, may conflict with libopencv_core.so.3.2

经查找是因为opencv新版本和旧版本的冲突问题
（参考：https://blog.csdn.net/quantum7/article/details/88908071）
由于怕删除其余库所以我没敢直接卸载（看个人情况吧
于是我就去修改了一下include路径，使其只链接到opencv3.4.2, 编译成功！

---

5. 1

https://blog.csdn.net/qq_40199447/article/details/109309186
在这里插入图片描述
解决方法：

cd /usr/local/lib
sudo mkdir pkgconfig
cd pkgconfig
sudo gedit opencv.pc

输入

prefix=/usr/local
exec_prefix=${prefix}
includedir=${prefix}/include
libdir=${exec_prefix}/lib

Name: opencv
Description: The opencv library
Version:4.4.0
Cflags: -I${includedir}/opencv4
Libs: -L${libdir} -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann  -lopencv_core
~                                               


6. 1
c/c++ runner  
```
setting.json  
        "cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt -I g++ your_source_file.cpp -o output_file -I /path/to/opencv/include -L /path/to/opencv/libs -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_core452 -lopencv_imgcodecs452 -lopencv_imgproc452 -lopencv_calib3d452 -lopencv_dnn452 -lopencv_features2d452 -lopencv_flann452 -lopencv_gapi452 -lopencv_highgui452 -lopencv_ml452 -lopencv_objdetect452 -lopencv_photo452 -lopencv_stitching452 -lopencv_video452 -lopencv_videoio452 && $dir$fileNameWithoutExt",
```

7. cc1plus: fatal error: your_source_file.cpp: 没有那个文件或目录
compilation terminated.

https://blog.csdn.net/jiaken2660/article/details/117034123

task.json
"-g",
                "-std=c++11",
                "${workspaceRoot}/src/*.cpp",
                "-o",
                "test",
                "-I",
                "/usr/local/include",
                "-I",
                "${workspaceRoot}/include",
                "-I",
                "/usr/local/include/opencv4",
                "-I",
                "/usr/local/include/opencv4/opencv2",
                "-I",
                "/home/jiaken2660/Qt5.9.9/5.9.9/gcc_64/include",
                "-L",
                "/usr/local/lib",
                "-L",
                "/home/jiaken2660/Qt5.9.9/5.9.9/gcc_64/lib",
                "-l",
                "opencv_aruco",
                "-l",
                "opencv_bgsegm",
                "-l",
                "opencv_bioinspired",
                "-l",
                "opencv_calib3d",
                "-l",
                "opencv_ccalib",
                "-l",
                "opencv_core",
                "-l",
                "opencv_datasets",
                "-l",
                "opencv_dnn_objdetect",
                "-l",
                "opencv_dnn",
                "-l",
                "opencv_dpm",
                "-l",
                "opencv_face",
                "-l",
                "opencv_features2d",
                "-l",
                "opencv_flann",
                "-l",
                "opencv_freetype",
                "-l",
                "opencv_fuzzy",
                "-l",
                "opencv_hfs",
                "-l",
                "opencv_highgui",
                "-l",
                "opencv_imgcodecs",
                "-l",
                "opencv_img_hash",
                "-l",
                "opencv_imgproc",
                "-l",
                "opencv_line_descriptor",
                "-l",
                "opencv_ml",
                "-l",
                "opencv_objdetect",
                "-l",
                "opencv_optflow",
                "-l",
                "opencv_phase_unwrapping",
                "-l",
                "opencv_photo",
                "-l",
                "opencv_plot",
                "-l",
                "opencv_reg",
                "-l",
                "opencv_rgbd",
                "-l",
                "opencv_saliency",
                "-l",
                "opencv_shape",
                "-l",
                "opencv_stereo",
                "-l",
                "opencv_stitching",
                "-l",
                "opencv_structured_light",
                "-l",
                "opencv_superres",
                "-l",
                "opencv_surface_matching",
                "-l",
                "opencv_text",
                "-l",
                "opencv_tracking",
                "-l",
                "opencv_videoio",
                "-l",
                "opencv_video",
                "-l",
                "opencv_videostab",
                "-l",
                "opencv_xfeatures2d",
                "-l",
                "opencv_ximgproc",
                "-l",
                "opencv_xobjdetect",
                "-l",
                "opencv_xphoto",
                "-l",
                "icui18n",
                "-l",
                "icuuc",
                "-l",
                "icudata"

8. /usr/bin/ld: 找不到 -lopencv_xfeatures2d: 没有那个文件或目录  
删除tasks.json中“-l”,“opencv_xfeatures2d",

9. Failed to open camera.
找不到摄像机   
Vmware右下角单击摄像头图标，连接失败。  
windows中任务管理器摄像头禁用再打开，Vmware中打开选择连接到虚拟机。

10. 版本切换
第一个表示自动寻找系统库里版本4以上的，第二个表示找系统库里的最低版本。

find_package(OpenCV 4 REQUIRED)
或者
find_package(OpenCV REQUIRED)


环境变量管理

添加到系统环境变量
修改~/.bashrc：

sudo gedit ~/.bashrc

像下面这样加入新的内容：

##OpenCV_4.4.0
#export PKG_CONFIG_PATH= /usr/local/opencv/opencv4.4.0/lib/pkgconfig
#export LD_LIBRARY_PATH= /usr/local/opencv/opencv4.4.0/lib

##OpenCV_3.4.2
#export PKG_CONFIG_PATH= /usr/local/opencv/opencv3.4.2/lib/pkgconfig
#export LD_LIBRARY_PATH= /usr/local/opencv/opencv3.4.2/lib

新加入OpenCV版本或者暂时不使用的OpenCV版本的建议注释掉。
对需要使用OpenCV_4.4.0，就可以把上面的#去掉。

每次切换后，都需要更新~/.bashrc

source ~/.bashrc 


查询OpenCV版本

pkg-config --modversion opencv
pkg-config --modversion opencv4

### OpenCV基础入门【C++语言】
运行：  
 g++ test2.cpp -o test2 `pkg-config --cflags --libs opencv4`  
./test2














## <div id="d"></div><a href ="#4">任务四</a>

https://git-scm.com/download/linux

Debian/Ubuntu

For the latest stable version for your release of Debian/Ubuntu
```# apt-get install git```

For Ubuntu, this PPA provides the latest stable upstream Git version
```# add-apt-repository ppa:git-core/ppa # apt update; apt install git```

* 问题：E: 无法打开锁文件 /var/lib/dpkg/lock-frontend - open (13: 权限不够)
E: 无法获取 dpkg 前端锁 (/var/lib/dpkg/lock-frontend)，请查看您是否正以 root 用户运行？

* 解决方法：要解决这个问题，需要以root用户身份或具有sudo权限的用户身份运行命令。可以尝试在命令前添加"sudo"：
```sudo dpkg <command>```
系统将要求输入管理员密码。输入正确密码后，理论上能够执行dpkg命令并顺利完成操作。

* q:dpkg: ```错误: 需要一个指示操作的选项
输入 dpkg --help 可获得安装和卸载软件包的有关帮助 [*]；
使用 apt 或是 aptitude 就能在友好的界面下管理软件包；
输入 dpkg -Dhelp 可看到 dpkg 除错标志的值的列表；
输入 dpkg --force-help 可获得所有强制操作选项的列表；
输入 dpkg-deb --help 可获得有关操作 *.deb 文件的帮助；
带有 [*] 的选项将会输出较大篇幅的文字 - 可使用管道将其输出连接到 less 或 more ！```
* a: ```“dpkg” 命令来自 Debian 软件包 dpkg (1.21.1ubuntu2.2)
尝试 sudo apt install <deb name>```
dpkg --help
用法：dpkg [<选项>...] <命令>
``

* 1.```sudo apt install git```
 >1、备份 /etc/apt/sources.list 文件 执行命令  
>sudo cp /etc/apt/sources.list /etc/apt/sources.list.old  
>2、打开文件 sudo vim /etc/apt/sources.list 
>3.2.sudo apt update更新
>apt-get update
>apt-get upgrade
sudo mv /home/xxxx/下载/name/* /opt/zotero/

>sudo nvdiv build
>sudo cd build
>sudo cmake -DCMAKE_BUILD_TYPE=Release -DOPENCV_GENERATE_PKGCONFIG=ON -DCMAKE_INSTALL_PREFIX=/usr/local .. 
>sudo make -j2
>sudo make install

问题现象#
尝试了网上很多教程，都是在Windows上修改网络属性，然而都没能解决，后来找到了解决方法。发现虚拟机里Ubuntu20.04系统桌面右上角并没有有线网络图标，尝试删除网络缓存文件后，重启网络后问题就解决了。

解决方法#
删除NetworkManager缓存文件#
sudo service NetworkManager stop 

sudo rm /var/lib/NetworkManager/NetworkManager.state 

sudo service NetworkManager start

### git 使用

初始化git仓库git init  
查看当前git仓库的状态git status  
将文件添加到git的暂存区git add   
* git add 文件名

        例如： git add index.html
        git add --all 或者 git add -A 或者git add .（简写） 添加所有文件
        git add a.txt b.txt 同时添加两个文件
        git add *.js 添加当前目录下的所有js文件
文件名将文件由暂存区提交到仓库区git commit -m '提交说明'  
查看提交日志git log  

配置邮箱和用户名
*  如果第一次使用git，会要求设置用户名和邮箱  
    >git config  user.name 你的目标用户名  
    git config  user.email 你的目标邮箱名  
    这种配置方式只有在当前仓库生效  
    git config user.name shuaige   
    git config user.email   669104343@qq.com  

    可以使用--global参数，配置全局的用户名和邮箱，这样别的git仓库就不需要重新配置了。  
    如果同时配置了局部的和全局的，那么局部的用户名和邮箱将会生效。  
    >git config  --global user.name shuaige
    git config  --global user.email 669104343@qq.com  

    查看配置信息
    >git config --list


## * [ ] 5. 安装anaconda，学习虚拟环境使用方法，配置好pytorch.环境(有独显的电脑必须安装GPU版本，没有独显的可以学习白嫖 CoLab等云服务器)【10'】
 
https://blog.csdn.net/JACKZHOU8/article/details/127338038

### 1. 安装anaconda3
终端输入  
bash Anaconda3-5.3.1-Linux-x86_64.sh

安装失败，找不到conda命令  
echo 'export PATH="/home/anaconda3/bin:$PATH"' >> ~/.bashrc  
source ~/.bashrc
配置环境变量  
刷新，挂载到base

### 2. 配置虚拟环境
 创建虚拟环境

创建名为pytorch的虚拟环境来安装Pytorch,python版本为3.7

conda create -n pytorch python=3.7 #创建名为pytorch的anaconda虚拟环境

（建议安装3.7版本的，之前安装了3.6版本的之后下载pytorch默认下载的是cpu版本的，用torch.cuda.is_available()测试总是返回False找了很多方法都没用，后来重装了虚拟环境把python设置为3.7后就成功了）

https://blog.csdn.net/qq_40600379/article/details/131950614

4.1创建虚拟环境

（1）如下表示创建一个名为“pytouch ”、python版本为3.10的虚拟环境，看到输入“yes/no”时，需输入“yes”

conda create -n pytouch python=3.10

（2）看到如下内容，则表示环境创建成功

Downloading and Extracting Packages                                
Preparing transaction: done                                    
Verifying transaction: done                                    
Executing transaction: done                                      

4.2查询当前系统conda虚拟环境

使用“conda info --envs”命令，可看到多了一个名为“pytouch”的虚拟环境

(base) root@gt-ubuntu22-04-cmd-v1-0-32gb-100m:/home/ubuntu# conda info --envs
 conda environments:

base                  *  /root/anaconda3
pytouch              /root/anaconda3/envs/pytouch


4.3挂载虚拟环境

使用conda activate pytouch命令，挂载名为pytouch的虚拟环境，如下，可看到由“base”->“pytouch”

conda activate pytouch

(pytouch) root@gt-ubuntu22-04-cmd-v1-0-32gb-100m:/home/ubuntu# 
(pytouch) root@gt-ubuntu22-04-cmd-v1-0-32gb-100m:/home/ubuntu# 

4.4退出虚拟环境

使用conda deactivate命令，退出名为pytouch的虚拟环境，如下，可看到由“pytouch”->“base”

conda deactivate

(base) root@gt-ubuntu22-04-cmd-v1-0-32gb-100m:/home/ubuntu# 

4.5查看已安装的工具包

使用conda list命令，查看当前虚拟环境，已安装的包，基本时当前虚拟环境默认安装的

conda list


4.6删除虚拟环境

（1）使用conda remove -n pytouch --all命令，删除名为pytouch 的虚拟环境及该环境安装的工具包。注：看到输入“yes/no”时，需输入“yes”

conda remove -n pytouch --all

Remove all packages in environment /root/anaconda3/envs/pytouch:



（2）执行conda info --envs命令，可看到只剩下base环境

2. cuDNN
* 安装(cuda11.8+cuDNN8.9.7.29)  
```
1.3.2.Debian Local lnstallation
Download the Debian local repository installation package. Before issuing the following commands, you must replace1.8 and 8.9.7.29 with your specific CUDA and cuDNN versions.
1.Navigate to your <cudnnpath> directory containing the cuDNN Debian local installer file.
2.Enable the local repository. or
sudo dpkg -i cudnn-local-repo-ubuntu2204-8.9.7.29_1.0-1_amd64.deb
sudo dpkg -i cudnn-local-repo-ubuntu2204-8.9.7.29_1.0-1_amd64.deb
3. lmport the CUDA GPG key.
sudo cp /var/cudnn-local-repo-ubuntu2204-8.9.7.29/cudnn-local-8AE81B24-keyring.gpg /usr/share/keyrings/
4.Refresh the repository metadata.
sudo apt-get update
5.Install the runtime library.
sudo apt-get install libcudnn8=8.9.7.29-1+cuda11.8
6.lnstall the developer library.
sudo apt-get install libcudnn8-dev=8.9.7.29-1+cuda11.8
7.Install the code samples and the cuDNN library documentation.
sudo apt-get install libcudnn8-samples=8.9.7.29-1+cuda11.8
```
 sudo dpkg -i cudnn-local-repo-ubuntu2204-8.9.7.29_1.0-1_amd64.deb

 The public cudnn-local-repo-ubuntu2204-8.9.7.29 GPG key does not appear to be installed.
To install the key, run this command:
sudo cp /var/cudnn-local-repo-ubuntu2204-8.9.7.29/cudnn-local-8AE81B24-keyring.gpg /usr/share/keyrings/

sudo adp update

* 测试cudnn

```
1.4.Verifying the lInstall on Linux
To verify that cuDNN is installed and is running properly, compile the mnistcUDNN sample located in the/usr/src/cudnn_samples_v8 directory in the Debian file.
1.Copy the cuDNN samples to a writable path.
cp -r /usrlsrc/cudnn_samples_v8/ $HOME
2.Go to the writable path.
cd $HOME/cudnn_samples_v8/mnistCUDNN
3.Compile the mnistcUDNN sample.
make clean && make
4.Run the mnistCUDNN sample.
./mnistCUDNN
lf cuDNN is properly installed and running on your Linux system, you will see a message similar to the following;
Test passed!
```

查看版本  
cuda  
~~ls -l /usr/local | grep cuda  
或
cat /usr/local/cuda/version.json~~  

cuda版本
nvcc -V   
自动检查
cd /usr/local/cuda/extras/demo_suite/
./bandwidthTest

cuDNN  
cat /usr/include/cudnn.h | grep CUDNN_MAJOR -A 2   

①删除之前创建的软链接
rm -rf /usr/local/cuda  
②建立新的软链接， 将 cuda10.1 连接到 默认cuda上
sudo ln -s /usr/local/cuda-10.1 /usr/local/cuda  
②再次核查 cuda版本：
cat /usr/local/cuda/version.txt

3. 安装pytorch步骤

创建虚拟环境

conda create --name env_torch_cuda113 python=3.8

进入虚拟环境

conda activate env_torch_cuda113

安装pytorch

    官网链接：https://pytorch.org/ 
    
pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118

(env_torch_cuda113) linhao@linhao-virtual-machine:~/下载$ python
Python 3.8.18 (default, Sep 11 2023, 13:40:15) 
[GCC 11.2.0] :: Anaconda, Inc. on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> torch.cuda.is_available()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
NameError: name 'torch' is not defined
>>> 

python
```python
# 验证torch安装
import torch
print(torch.__version__)

#验证cuda安装
print(torch.cuda.is_available())
```

2.0.1  
false

```python
import torch
print(torch.__version__)
print(torch.cuda.is_available())
print(torch.cuda.device_count())
print(torch.cuda.current_device())
```




https://blog.csdn.net/qq_35768355/article/details/131261838

第一步：我们先查看操作系统的版本

cat /etc/issue  
>Ubuntu 22.04.3 LTS \n \l

第二步：查看显卡驱动版本

nvidia-smi  
>NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver. Make sure that the latest NVIDIA driver is installed and running.

第三步：更新显卡驱动（不需要可跳过）

驱动安装包传送门：[NVIDIA驱动](https://www.nvidia.cn/Download/index.aspx?lang=cn)

https://zhuanlan.zhihu.com/p/621079424


4. 问题

这个错误表明CUDA无法在你的系统上找到任何CUDA-capable的设备，也就是说，你的系统可能没有安装NVIDIA的GPU，或者你的GPU不支持CUDA，或者你的驱动没有正确安装。

以下是一些可能的解决方案：

1. 检查你的系统是否有NVIDIA的GPU，并且这个GPU是否支持CUDA。你可以在NVIDIA的网站上查看你的GPU是否支持CUDA。

2. 如果你的GPU支持CUDA，那么请确保你已经安装了正确的驱动。你可以从NVIDIA的网站上下载并安装驱动。

3. 如果你已经安装了驱动，那么请确保你的CUDA toolkit已经正确安装。你可以通过运行`nvcc -V`来检查CUDA的版本。

4. 如果以上都没有问题，那么可能是你的系统没有正确识别你的GPU。你可以尝试重启你的系统，或者在BIOS设置中检查你的GPU设置。

如果以上的方法都不能解决你的问题，那么我建议你查看NVIDIA的官方文档，或者在相关的论坛和社区中寻求帮助。

cd /data/software(下载目录)
sudo chmod +x NVIDIA-Linux-x86_64-525.105.17.run 
sudo ./NVIDIA-Linux-x86_64-525.105.17.run -no-x-check -no-nouveau-check -no-opengl-files