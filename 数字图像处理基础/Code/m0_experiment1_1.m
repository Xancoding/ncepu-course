% 将1.jpg图像向右平移50个像素，向上平移30个像素，然后顺时针旋转60度。
I1 = imread('G:\SCHOOL\500 计算机科学与技术 专选课\200 数字图像处理基础\第一次上机实验\第一次上机实验\1.jpg');
I1 = im2double(I1);

figure(1);
imshow(I1); title("原始图像");

% 水平向右平移50个像素，竖直向上平移30个像素
offset = [50, -30];
I2 = imtranslate(I1, offset);

% 顺时针旋转60度
I3 = imrotate(I2, -60);

figure(2)
imshow(I3); title("处理后的图像");