% 实现拉普拉斯增强
I = imread('D:\Static\img\lena.png');
I1 = rgb2gray(I);
I1 = im2double(I1);
F = [0 1 0; 1 -4 1; 0 1 0];   % 滤波器

I2 = imfilter(I1, F);

figure(1);
subplot(1, 2, 1);  imshow(I1); title('原始图像');
subplot(1, 2, 2);  imshow(I1-I2); title('拉普拉斯增强');

