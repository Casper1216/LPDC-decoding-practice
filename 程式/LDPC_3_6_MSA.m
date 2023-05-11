clear 
clc
%%

%time start
tic;

n=6;
k=3;
m=n-k;
R=k/n;  %coderate


Eb=1;

H = [1 0 0 1 0 1;
     1 1 0 0 1 0;
     0 1 1 0 0 1];

dv = 2;
dc = 3;

u = zeros(1,n);         %codeword
x = ones(1,n);          %BPSK

%SNR_dB  = [0 0.4 0.8 1.2 1.6 2];
SNR_dB  = [0];

BER = zeros(1,length(SNR_dB));
FER = zeros(1,length(SNR_dB));

%channel information
Fn_1 = ones(1,n);

%VN update

%CN update
tau = H;  
CN = H;  

%total LLR;
VN_total = zeros(1,n);

%decoded
syd = zeros(1,m);
u_hat = zeros(1,n);

%%
numtime = 100000;
iteration = 50;

for q = 1:length(SNR_dB)

    biterror=0;
    frameerror=0;

    SNR = 10^(-SNR_dB(q)/10);
    sigma = sqrt(SNR/(2*R));
    
    for num = 1: numtime
        
        noise = sigma*randn(1,n);
        y = x + noise;
        


        %%
        %initialization
        Fn = Fn_1.*(2*y/(sigma^2));
        
        VN = H.*Fn;   %直接初始化
        VN_2 = VN;  
        for iter = 1:iteration
            
          
            CN =H;
            %CN update
            
            for j = 1:m
                for i=1:n


                    if(H(j,i)==0)
                        continue;
                    end
                    
                    min_beta = 10^6;
                    for k=1:n
                         if(H(j,k)==1&&k~=i)
                             
                             if(abs(VN(j,k))<min_beta)
                                min_beta = abs(VN(j,k));
                             end
                             CN(j,i)  = CN(j,i)*sign(VN(j,k));
                            
                        end
                    end
                    CN(j,i) = CN(j,i)*min_beta;
                    
                    
                end
            end
            %VN update
            
            for i=1:n
                for j=1:m
                    
                    if(H(j,i)==0)
                        continue;
                    end
 
                    VN(j,i) = Fn(i)+sum(CN(:,i)) - CN(j,i); 

                end
            end
           
            %total LLR
            %decoded seq

            VN_total = Fn + sum(CN,1);  %sum(CN , 1) 全部列相加 
            u_hat = (1-sign(VN_total))/2;
            
%             for i=1:n
%                 u_hat(i) = 0;
%                 if(VN_total(i)<0)
%                     u_hat(i) = 1;
%                 end
%                 
%             end
            
            if(syd == mod(u_hat*H',2))
                break;
            end
         
        end
        disp(iter);
        
%%
        biterror = biterror+sum(abs(u-u_hat));
        
        if(sum(abs(u-u_hat))>0)
            frameerror = frameerror+1;
        end

    end


    BER(q) = biterror/(n*numtime);
    FER(q) = frameerror/(numtime);

end

%%
figure(1)
semilogy(SNR_dB, BER, 'b');
hold on 
semilogy(SNR_dB, FER, 'r');
hold on 
legend('BER','FER');
title('SPA');
xlabel('SNR(dB)');
ylabel('error rate');

%time end
toc
