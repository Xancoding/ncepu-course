I1 = imread('D:\Static\img\lena.png');
I1 = im2double(I1);  % 转换为double
I2 = imread('D:\Static\img\Flower.jpg');
I2 = im2double(I2);  % 转换为double
I3 = I1*0.5 + I2*0.5;

figure(1);
subplot(1, 3, 1); imshow(I1); title('图像1');
subplot(1, 3, 2); imshow(I2); title('图像2');
subplot(1, 3, 3); imshow(I3); title('叠加图像');