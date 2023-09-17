I = imread('D:\Static\img\lena.png');
I1 = 0.299*I(:, :, 1) + 0.587*I(:, :, 2) + 0.114*I(:, :, 3);

% 创建图形窗口
figure(1);

% 原图像
subplot(1, 2, 1);
imshow(I1);
title("原图像");

% 提高对比度
k = 1.5;
b = 0;
I2 = k.*I1 + b;
subplot(1, 2, 2);
imshow(I2);
title('k=1.5, b=0');
