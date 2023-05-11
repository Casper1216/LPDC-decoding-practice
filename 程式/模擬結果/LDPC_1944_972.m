clear 
clc

%%


SPA = readmatrix("LDPC_1944_SPA_final.csv");
MSA = readmatrix("LDPC_1944_MSA_final.csv");
LBP = readmatrix("LDPC_1944_Layered_BP_final.csv");
LNMSA = readmatrix("LDPC_1944_Layered_NMSA_final.csv");


figure(1)
semilogy(SPA(1,:), SPA(2,:), 'b-pentagram');
hold on 

semilogy(MSA(1,:), MSA(2,:), 'b-diamond');
hold on 

semilogy(LBP (1,:), LBP (2,:), 'g--pentagram');
hold on 

semilogy(LNMSA (1,:), LNMSA (2,:), 'g--diamon');
hold on 




legend('BER-SPA','BER-MSA','BER-LBP','BER-LNMSA');
title('BER');
xlabel('Eb/N0');
ylabel('BER');


figure(2)
semilogy(SPA(1,:), SPA(3,:), 'r-pentagram');
hold on 
semilogy(MSA(1,:), MSA(3,:), 'r-diamond');
hold on 
semilogy(LBP (1,:), LBP (3,:), 'm--pentagram');
hold on 
semilogy(LNMSA (1,:), LNMSA (3,:), 'm--diamon');
hold on 

legend('FER-SPA','FER-MSA','FER-LBP','FER-LNMSA');
title('FER');
xlabel('Eb/N0');
ylabel('FER');