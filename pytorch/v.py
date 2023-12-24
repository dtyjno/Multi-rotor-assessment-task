import torch

# 定义设备
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# 创建一个张量
x = torch.randn(10, 10)

# 将张量移动到指定的设备
x = x.to(device)