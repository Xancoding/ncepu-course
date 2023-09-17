% 实现Roberts梯度滤波
I = imread('D:\Static\img\lena.png');
I1 = rgb2gray(I);
I1 = im2double(I1);

[R, C] = size(I1);  % 图像的行&列
I2 = zeros(R,C);

for i=1:R
    for j=1:C
        v = 0;
        if i >= R || j >= C
            v = 0;
        else
            v = abs(I1(i+1,j+1)-I1(i,j))+abs(I1(i+1,j)-I1(i,j+1));
        end
        I2(i, j)=v;
    end
end

figure(1);
subplot(1, 2, 1);  imshow(I1); title('原始图像');
subplot(1, 2, 2);  imshow(I2); title('Roberts梯度滤波');

