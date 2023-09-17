% 将1.jpg图像变换为频率域图像，并显示频谱图、相位图、旋转后的频谱图、反变换后的图像
% 频谱图是指将信号（例如音频或图像）转换为频域表示的图形
% 相位图是指将信号（例如音频或图像）转换为频域表示后，显示信号在频率域中的相位信息的图形
I1 = imread("G:\SCHOOL\100 计算机科学与技术 专选课\200 数字图像处理基础\第二次上机实验\1.jpg");
I1 = rgb2gray(I1);
I1 = im2double(I1);

I1 = fft2(I1);
I2 = angle(I1);
I3 = imrotate(I1, 30, 'crop');
I4 = ifft2(I1);


figure(1);
% subplot(1, 4, 1); imshow(I1); title("频谱图");
% subplot(1, 4, 2); imshow(I2); title("相位图");
% subplot(1, 4, 3); imshow(I3); title("旋转后的频谱图");
subplot(1, 4, 1); imshow(abs(I1)); title("频谱图");
subplot(1, 4, 2); imshow(abs(I2)); title("相位图");
subplot(1, 4, 3); imshow(abs(I3)); title("旋转后的频谱图");
subplot(1, 4, 4); imshow(I4); title("反变换后的图像");