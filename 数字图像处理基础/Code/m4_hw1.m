% 1、为一副图像分布添加3种不同的噪声。
% 2、分布使用deconvreg、deconvwnr和deconvblind复原问题1中的三幅添加噪声之后的图像。
I = imread('D:\Static\img\lena.png');
I = rgb2gray(I);
I = im2double(I);

% 构造点扩散函数
H1 = fspecial('motion', 25, 45);     % 运动模糊  长度 25、角度 45
H2 = fspecial('gaussian', 25, 5);    % 高斯模糊  尺寸 25、均方差 5
H3 = fspecial('disk', 10);           % 圆盘模糊  模糊半径 10

% 退化图像
J1 = imfilter(I, H1, 'conv', 'circular');
J2 = imfilter(I, H2, 'conv', 'circular');
J3 = imfilter(I, H3, 'conv', 'circular');

% 初始化PSF
INITPSF1 = ones(size(H1)); 
INITPSF2 = ones(size(H2)); 
INITPSF3 = ones(size(H3)); 

% 复原图像
L1 = deconvreg(J1, H1, 0);  % 有约束的最小二乘法  点扩散函数 H1、噪声强度 0
L2 = deconvreg(J2, H2, 0);  % 有约束的最小二乘法  点扩散函数 H2、噪声强度 0
L3 = deconvreg(J3, H3, 0);  % 有约束的最小二乘法  点扩散函数 H3、噪声强度 0

L4 = deconvwnr(J1, H1, 0);  % 维纳滤波            点扩散函数、信噪比 0
L5 = deconvwnr(J2, H2, 0);  % 维纳滤波            点扩散函数、信噪比 0
L6 = deconvwnr(J3, H3, 0);  % 维纳滤波            点扩散函数、信噪比 0

L7 = deconvblind(J1, INITPSF1, 10);  % 盲解卷积图像复原 预设的初始PSF INITPSF1、迭代次数 10
L8 = deconvblind(J2, INITPSF2, 10);  % 盲解卷积图像复原 预设的初始PSF INITPSF2、迭代次数 10
L9 = deconvblind(J3, INITPSF3, 10);  % 盲解卷积图像复原 预设的初始PSF INITPSF3、迭代次数 10



figure(1);
subplot(4, 3, 1); imshow(J1); title('运动模糊退化图像');
subplot(4, 3, 2); imshow(J2); title('高斯模糊退化图像');
subplot(4, 3, 3); imshow(J3); title('圆盘模糊退化图像');

subplot(4, 3, 4); imshow(L1); title('运动模糊复原图像--有约束的最小二乘法');
subplot(4, 3, 5); imshow(L2); title('高斯模糊复原图像--有约束的最小二乘法');
subplot(4, 3, 6); imshow(L3); title('圆盘模糊复原图像--有约束的最小二乘法');

subplot(4, 3, 7); imshow(L4); title('运动模糊复原图像--维纳滤波法');
subplot(4, 3, 8); imshow(L5); title('高斯模糊复原图像--维纳滤波法');
subplot(4, 3, 9); imshow(L6); title('圆盘模糊复原图像--维纳滤波法');

subplot(4, 3, 10); imshow(L7); title('运动模糊复原图像--盲解卷积图像复原');
subplot(4, 3, 11); imshow(L8); title('高斯模糊复原图像--盲解卷积图像复原');
subplot(4, 3, 12); imshow(L9); title('圆盘模糊复原图像--盲解卷积图像复原');
