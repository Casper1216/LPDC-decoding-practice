function [H_ge, index] = gaussain_elimination2(H)
    m = size(H,1);
    index = (1:m).';
    first = 1;
    for i = 1:m-1
        notfound = 1;
        while(notfound&&first<=size(H,2))
            for j = i:m
                if(H(j,first)==1)
                    H([j,i],:) = H([i,j],:);
                    index([j,i],1) = index([i,j],1);
                    notfound = 0;
                    break;
                end
            end
            first = first + 1;
        end
        if(first<=size(H,2))
            for j = (i+1):m
                if(H(j,first-1)==1)
                    H(j,:) = mod(H(j,:) + H(i,:), 2);
                end
            end
        end
    end
    H_ge = H;
end