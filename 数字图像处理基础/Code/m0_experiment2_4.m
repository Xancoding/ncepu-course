% 实现梯形滤波器，并应用
l1 = imread('G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第二次上机实验\1.jpg');
l1 = rgb2gray(l1);
l1 = im2double(l1);


% 计算图像的尺寸和中心点
[W1,H1] = size(l1);
u1 = -W1/2:(W1/2-1);
v1 = -H1/2:(H1/2-1);
[V1,U1] = meshgrid(v1,u1);

% 计算梯形低通滤波器并滤波
D0 = 5;
D1 = 10;

K = zeros(W1, H1); % 梯形低通滤波器
for i = 1:W1
    for j = 1:H1
        D = sqrt(u1(i)^2 + v1(j)^2);
        v = 0;
        if D < D0
           v = 1;
        elseif D > D1
           v = 0;
        else
           v = (D1-D)/(D1-D0);
        end
        K(i, j) = v;
    end
end


J1 = fftshift(fft2(l1));
L1 = J1.*K;
I1 = ifft2(fftshift(L1));


% 绘制第一个图像的滤波结果
figure(1);
subplot(1,2,1);
imshow(l1);
title('原图像');
subplot(1,2,2);
imshow(I1);
title('梯形低通滤波器处理图像');

