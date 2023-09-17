% 将1.jpg图像进行二值化处理。
% 读取图像
img = imread('G:\SCHOOL\500 计算机科学与技术 专选课\200 数字图像处理基础\第一次上机实验\第一次上机实验\1.jpg');

% 将图像转换为灰度图像
img_gray = rgb2gray(img);

% 设置阈值
threshold = 128;

% 将灰度图像转换为二值图像
img_bw = img_gray > threshold;

% 显示结果
imshow(img_bw);
