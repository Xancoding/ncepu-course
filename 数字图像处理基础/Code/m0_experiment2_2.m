% 在频率域对2.jpg图像进行sobel滤波，并显示滤波效果
I = imread("G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第二次上机实验\2.jpg");
I = im2gray(I);
I = im2double(I);

I2 = imfilter(I, fspecial('sobel'));

figure(1);
subplot(1, 2, 1); imshow(I); title("原图像");
subplot(1, 2, 2); imshow(I2); title("sobel滤波结果");