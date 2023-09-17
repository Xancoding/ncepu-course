I1 = imread('G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第一次上机实验\第一次上机实验\2.jpg');
I2 = imread('G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第一次上机实验\第一次上机实验\3.jpg');
I3 = imread('G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第一次上机实验\第一次上机实验\4.jpg');
I4 = imread('G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第一次上机实验\第一次上机实验\5.jpg');

% 定义高斯滤波器
sigma = 2; % 高斯滤波器的标准差
h = fspecial('gaussian', [3 3], sigma);

figure(1);
subplot(1, 3, 1);  imshow(I1);  title('原图2.jpg');
subplot(1, 3, 2);  imshow(imfilter(I1, h));  title('去噪2.jpg');
subplot(1, 3, 3);  imshow(I3);  title('参考图像4.jpg');


figure(2);
subplot(1, 3, 1);  imshow(I2);  title('原图3.jpg');
subplot(1, 3, 2);  imshow(imfilter(I2, h));  title('去噪3.jpg');
subplot(1, 3, 3);  imshow(I4);  title('参考图像5.jpg');
