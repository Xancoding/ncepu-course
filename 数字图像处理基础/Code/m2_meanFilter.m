I = imread('D:\Static\img\lena.png');
I1 = rgb2gray(I);
I1 = im2double(I1);
I1 = imnoise(I1, 'gaussian'); % 高斯噪声
x = 9;  % 滤波器参数
F = fspecial("average",x);   % 滤波器

[R, C] = size(I1);  % 图像的行&列
I2 = zeros(R,C);

for i=1:R
    for j=1:C
        v = 0;
        for r=1:x
            for c=1:x
                a = i-(floor(x/2)+1)+r;
                b = j-(floor(x/2)+1)+c;
                if a<1 || a>R || b<1 || b>C
                    v = v + 0;
                else 
                    v = v + F(r, c)*I1(a, b);
                end
            end
        end
        I2(i, j)=v;
    end
end

figure(1);
subplot(1, 2, 1);  imshow(I1); title('原始图像');
subplot(1, 2, 2);  imshow(I2); title([num2str(x) '*' num2str(x) '滤波']);

