
解决方法#
删除NetworkManager缓存文件#
sudo service NetworkManager stop 

sudo rm /var/lib/NetworkManager/NetworkManager.state 

sudo service NetworkManager start

---
```# cd 改变目录  （change directory）
cd images   #进入images文件夹
cd ..      #进入上一层目录
cd ~       #进入用户根目录

# tab  自动补全，当我们输命令或者目录很长时，可以使用tab键进行自动补全。
# 按两次tab，会把所有符合要求的内容都列出来。

# pwd 打印当前目录的路径 （print work directory）
pwd


# ls 展示当前目录列表（list）
ls         # 展示当前目录
ls -a      # 展示全部内容，包括隐藏文件
ls -l      # 以列表的形式展示内容
ls -al     # 以列表的形式展示所有的内容，包括隐藏文件。
ls --help  # 查看ls所有的参数。
ls -l images   # 展示images目录下的文件，如果没有写目录，默认展示当前目录。


# clear reset清屏
clear  # 清除屏幕内容，滚动条，保留了历史
reset  # 重置，历史记录没了。


# mkdir  创建一个文件夹 （make directory）
mkdir css          # 创建一个css的文件夹
mkdir css img js   # 创建了三个文件夹

# rmdir  删除一个空的文件夹（没啥用）
rmdir img   # 删除文件夹

# touch  创建文件
touch index.html   #创建了一个index.html文件
touch css/index.css # 在css目录下创建idnex.css文件

# rm 删除一个文件获取文件夹
rm index.html # 删除index.html文件
rm js         # 删除空的js文件夹
rm -r css     # 递归删除一个文件夹

# mv 移动文件（move）
mv index.html js            # 将html文件移动到js文件夹中
mv index.html index2.html   # 将index.html重命名为index2.html

# cp 复制文件（cp）
cp index.html index2.html   # 复制index.html文件，命名为index2.html
cp -r css css02             # 如果复制的是文件夹，需要使用-r参数。

# cat 查看文件全部内容
cat index.html
# less 查看文件部分内容
less index.html
# q退出查看```

---

在/var/log/journal/垃圾日志文件，可以看到他的内存占用是比较大的，那么我们可以通过如下命令来清除这些日志文件

journalctl --disk-usage        # 检查日志大小
sudo journalctl --vacuum-time=1w    # 只保留一周的日志

sudo journalctl --vacuum-size=500M    # 只保留500MB的日志

rm -rf /var/log/journal/askd342fh35aewfhagf67iuro1（垃圾文件）    # 直接删除/var/log/journal/目录下的日志文件

du -sh ~/.cache/thumbnails       # 检查缩略图缓存的大小
rm -rf ~/.cache/thumbnails/*     # 清除缩略图缓存

---

下三个命令主要清理升级缓存以及无用包

sudo apt-get autoclean                # 删除旧版本软件缓存
sudo apt-get clean                    # 删除系统内所有软件缓存
sudo apt-get autoremove             # 删除系统不再使用的孤立软件

---

如果电脑装有VScode可以删除VScode中ipch文件（可以在磁盘分析器baobab中查看下面路径内容）

/home/用户名/.cache/vscode-cpptools/ipch

---

如果装有anaconda软件，当使用一段时间之后会占用相当一部分磁盘空间到pkgs文件夹下，在conda的设计中，目录’pkgs’是下载、存放缓存，当通过pip下载一些软件时，先去缓存区查找有无目标，若无目标会下载包至缓存区当中，再解压安装到指定环境当中的lib/pythonx.x/site-packages中。
同时，anaconda一起携带的包也会放在pkgs中。我们在构建一些envs的时候，对一些包的依赖会通过硬盘链接链接到pkgs目录，这样虚拟环境生成的速度大大加快，占用空间就大大减小了。

conda clean -p  # 这个命令会检查哪些包没有在包缓存中被硬依赖到其他地方，并删除它们
conda clean --packages  # 删除从不使用的包
conda clean --tarballs  # 删除tar包
conda clean -a  # 更强力些，删除索引缓存、锁定文件、未使用过的包和tar包

---

删除不用的pip缓存

sudo rm -r ~/.cache/pip

---

