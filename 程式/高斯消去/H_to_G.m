function [G] = H_to_G(H)


[m,n] = size(H);    %H = m*n

k = n-m;
start = n-m+1;  %要化成 I 支開始行數


P_T = H(:,1:k);             % P 轉
H_I = H(:,start:end);       % H 中之 單位矩陣 (n-k)*(n-k)

H_p = [H(:,start:end) H(:,1:k)];    %轉換為位置

H_Gauss = mod(rref(H_p),2);         %高斯消去

P = H_Gauss(:,m+1:end).';           %找到G中之P

G = [eye(k) P];                     %construct G


