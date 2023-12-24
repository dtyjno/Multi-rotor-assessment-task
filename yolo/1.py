#from ultralytics import YOLO

# 从头开始创建一个新的YOLO模型
#model = YOLO('yolov8n.yaml')

# 加载预训练的YOLO模型（推荐用于训练）
#model = YOLO('yolov8n.pt')

# 使用“coco128.yaml”数据集训练模型3个周期
#results = model.train(data='coco128.yaml', epochs=3)

# 评估模型在验证集上的性能
#results = model.val()

# 使用模型对图片进行目标检测
#results = model('https://ultralytics.com/images/bus.jpg')

# 将模型导出为ONNX格式
#success = model.export(format='onnx')

import torch

# Model
model = torch.hub.load("ultralytics/yolov5", "yolov5s")  # or yolov5n - yolov5x6, custom

# Images
img = "https://ultralytics.com/images/zidane.jpg"  # or file, Path, PIL, OpenCV, numpy, list

# Inference
results = model(img)

# Results
results.print()  # or .show(), .save(), .crop(), .pandas(), etc.