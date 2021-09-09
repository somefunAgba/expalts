classdef expalts
    %EXPALTS: ALTERNATIVE NATURAL EXPONENTIAL COMPUTATIONS
    % Oluwasegun Somefun.
    % OAS.<oasomefun@futa.edu.ng, somefuno@oregonstate.edu>
    % Original: 2020,
    % Revised: 2021
    %
    % UseCase: Test
    %
    % x = -10:0.01:10
    %
    % - 1. bit-shift and integer squares approx. of the limit-theorem
    % y = expalts.ebits(x);
    %
    % - 2. gradual exponentation: - useful for improved accuracy
    %   esp. in resource-constrained embedded systems.
    % y = expalts.byones(x, 0);
    % - compare with the inbuilt exp.
    % y = expalts.byones(x, 1);
    %
    
    methods(Static)
        
        %EXPBONE: EXP BY ONES
        function y = byones(x,mode)
            %BYONES
            % Gradual natural exponentiation
            % reducing power x to the closed range [-1 1]
            % for increased accuracy of fast exponential approximations
            % by bit shifting and integer squaring.
            
            arguments
                x {mustBeNumeric}
                mode {mustBeMember(mode,[0,1])}= 0
            end
            
            if ~isrow(x)
                y = ones(numel(x),1);
            else
                y = ones(1,numel(x));
            end
            %
            if mode == 0
                % limit theorem:
                % bit shift and integer squaring fcn implementation
                if x > 1
                    while x > 1
                        y = y.*expalts.ebits(1);
                        x = x-1;
                    end
                elseif x < -1
                    while x < -1
                        y = y.*expalts.ebits(-1);
                        x = x+1;
                    end
                end
                y = y.*expalts.ebits(x);
            elseif mode == 1
                % in-built exponential fcn implementation
                if x > 1
                    while x > 1
                        y = y.*exp(1);
                        x = x-1;
                    end
                elseif x < -1
                    while x < -1
                        y = y.*exp(-1);
                        x = x+1;
                    end
                end
                y = y.*exp(x);
            end
            
        end
        
        %EXP COMPUTATION BY LIMIT THEOREM AND BIT-SHIFTS
        function y = ebits(x)
            % EBITS
            % Exponentiatiobn by the Limit Theoremm.
            % implements natural exponentiation function
            % using the limit theorem as n -> infinity
            % y =  ( (1 + (x)*(1/n)) )^n
            
            %             arguments
            %                 x {mustBeNumeric}
            %             end
            
            % - bit-shift
            % bitwise realization of
            % xx = (1 + (x).*(1/n)) = 1 + (x .* bitsra(1,16));
            % n = 2^k =>  k = 16, n = 65536
            % k = 24, n = 16777216
            y = 1 + bitsra(x, 24);
            % - integer squares
            % y = (xx).^n; choose n = 2^16 -> infty;
            y = expalts.isq(y, 16777216);
            % - end
            
        end
        
        %INTEGER EXPONENTIATION BY SQUARING
        function y = isq(x,n)
            % ISQ
            % integer exponentiation by squaring
            % iexpbsq: iteration
            
            %             arguments
            %                 x {mustBeNumeric}
            %                 n
            %             end
            
            if ~isrow(x)
                y = ones(numel(x),1);
            else
                y = ones(1,numel(x));
            end
            %
            % n < 0
            if n < 0
                x = 1./x;
                n = -n;
            elseif n == 0
                % y = 1;
            elseif n == 1
                y = x;
            end
            %
            while (n > 1)
                if (expalts.ieven(n))
                    x = x.*x;
                    n = n/2;
                else
                    y = x.*y;
                    x = x.*x;
                    n = (n-1)/2;
                end
            end
            y = x.*y;
        end
        
        %IS INTEGER EVEN?
        function y = ieven(x)
            %IEVEN
            % tests if an input integer x is even or not
            % returns 1 for even x, 0 for  odd x.
            
            %             arguments
            %                 x
            %             end
            
            y = ~(bitand(x,1)); % ~(x & 1)
            
        end
        
    end
end

