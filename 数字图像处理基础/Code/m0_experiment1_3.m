% 对1.jpg图像进行三值化处理，例如灰度值为0，0.5和1，或者0，128，255，请考虑阈值如何设置。
% 读取图像
img = imread('G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第一次上机实验\第一次上机实验\1.jpg');
img = im2gray(img);
img = im2double(img);

% 绘制直方图
imhist(img);
% 计算阈值
thresh1 = 0.6;
thresh2 = 0.7;


% 进行三值化处理
img_bw = zeros(size(img));
img_bw(img < thresh1) = 0;
img_bw(img >= thresh1 & img < thresh2) = 0.5;
img_bw(img >= thresh2) = 1;

% 显示结果图像
% imshow(img_bw);
