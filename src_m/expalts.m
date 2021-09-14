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
    % - 0. limit-theorem: bit-shift and integer squares approx.
    % - 2. laplace approximation
    % - 1: in-built approximation
    %
    % - gradual natural exponentation: - useful for improved accuracy
    %   esp. in resource-constrained embedded systems.
    % y = expalts.byones(x, 0);
    % y = expalts.byones(x, 2);
    % - compare with the inbuilt exp.
    % y = expalts.byones(x, 1);
    %
    
    methods(Static)
        
        %EXPBONE: EXP BY ONES
        function y = bones(x,mode)
            %BONES
            % Gradual natural exponentiation
            % reducing power x to the closed range [-1 1]
            % for increased accuracy of fast exponential approximations
            % by bit shifting and integer squaring.
            
            %             arguments
            %                 x {mustBeNumeric}
            %                 mode {mustBeMember(mode,[0,1,2])}= 0
            %             end
            
            %
            expone = 2.7183; % 2.718281828459046;

            % Vectorized Implementation
            
            xrepts = sign(x).*floor(abs(x));
            xfrac = x - xrepts;
            y = (expone).^xrepts;
            if mode == 0
                % y = (expalts.ebits(sign(x).*1)).^xrepts;
                y = y.*expalts.ebits(xfrac);
            elseif mode == 1
                y = y.*exp(xfrac);
            elseif mode == 2
                y = y.*expalts.elap(xfrac);
            end
            
            if isrow(x)&&~isrow(y)
                y = y';
            end
            
            % LOOP implementation
            %             for id = 1:numel(x)
            %                 if mode == 0
            %                     % limit theorem:
            %                     % bit shift and integer squaring fcn implementation
            %                      if x(id) > 1
            %                         while x(id) > 1
            %                             y(id) = y(id).*...
            %                                 (expalts.ebits(1) + 0.0053); %n=8;
            %                             x(id) = x(id)-1;
            %                         end
            %                     elseif x(id) < -1
            %                         while x(id) < -1
            %                             y(id) = y(id).*...
            %                                 (expalts.ebits(-1) + 7.1969e-4); %n=8
            %                             x(id) = x(id)+1;
            %                         end
            %                     end
            %                     % x is now a number close to zero, differences from the
            %                     % truth becomes negligible
            %                     y(id) = y(id).*expalts.ebits(x(id));
            %                 elseif mode == 1
            %                     % in-built exponential fcn implementation
            %                     if x(id) > 1
            %                         while x(id) > 1
            %                             y(id) = y(id).*exp(1);
            %                             x(id) = x(id)-1;
            %                         end
            %                     elseif x(id) < -1
            %                         while x(id) < -1
            %                             y(id) = y(id).*exp(-1);
            %                             x(id) = x(id)+1;
            %                         end
            %                     end
            %                     y(id) = y(id).*exp(x(id));
            %                 elseif mode == 2
            %                     % laplace exponential fcn implementation
            %                     if x(id) > 1
            %                         while x(id) > 1
            %                             y(id) = y(id).*...
            %                                 (expalts.elap(1) - 9.5315e-04); %n=8
            %                             x(id) = x(id)-1;
            %                         end
            %                     elseif x(id) < -1
            %                         while x(id) < -1
            %                             y(id) = y(id).*...
            %                                 (expalts.elap(-1) + 0.0016); % n=8
            %                             x(id) = x(id)+1;
            %                         end
            %                     end
            %                     y(id) = y(id).*expalts.elap(x(id));
            %                 end
            %             end
            
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
            % n = 2^k =>
            % k = 2; n = 4;
            % k = 4; n = 16;
            k = 8; n = 256;
            % k = 10; n = 1024;
            % k = 16; n = 65536;
            % k = 24; n = 16777216; % - recommended
            % k = 28; n = 268435456;
            % k = 32; n = 4294967295;
            y = 1 + bitsra(x, k);
            % - integer squares
            % y = (xx).^n; choose n = 2^16 -> infty;
            y = expalts.isq(y, n);
            % - end
            
        end
        
        %EXPLAP: EXP BY LAPLACE APPROXIMATION
        function y = elap(x)
            %ELAP
            % Fast Laplace-based Exponential Algorithm
            % : just a loop and a first-order algebra
            
            % x : real-valued input value
            
            % k or nts : number of bits, sampling-time power in base 2,
            % max value is constrained for speed and
            % integer-precision max-min limit on current
            % gen. purpose digital computers.
            % k = 16, n = 65536
            % k = 24, n = 16777216,
            % k = 28, n = 268435456
            % k = 32, n = 4294967295
            
            %             arguments
            %                 x {mustBeNumeric}
            %             end
            
            if ~isrow(x)
                y = zeros(numel(x),1);
            else
                y = zeros(1,numel(x));
            end
            
            % final time is unity (1.0secs).
            
            % loop limit computation N = 2^nts
            %N = bitsll(1,nts); % zero-based indexing
            %N = bitsll(1,nts) + 1; % one-based indexing
            %
            %-k = 2,
            % N = 4; ts = 0.25;
            % -k = 4,
            % N = 16; ts = 0.0625;
            % - k = 8,
            N = 256; ts = 0.0039;
            % - k = 10,
            % N = 1024; ts = 9.7656e-4;
            % - k = 16, % ts = 1.52587890625e-05
            % N = 65536 - 1; ts = 1.5259e-5; % - recommended
            % - k = 21, % ts = 4.7684e-7
            % N = 2097152 - 1; ts = 4.7684e-7;
            % - k = 24  % ts = 5.960464477539063e-08
            % N = 16777216 - 1; ts = 5.9605e-8;
            % - k = 28,  ts = 3.725290298461914e-09
            % N = 268435456 - 1; ts = 3.7253e-9;
            % - k = 32, ts =2.328306436538696e-10
            % N = 4294967296 - 1; ts = 2.3283e-10;
            
            %nts = 16;
            % sampling-time computation using bitwise shift right
            %ts = bitsra(1,nts); % 2^-nts = 1/(2^nts)
            ts = x.*ts; % augmented sampling-time

            % vectorized form
            for id = 0:N
                y = y + ts.*(y + sign(x).*1);
            end
            y = 1 + sign(x).*y;
            y(isnan(y)) = 0;
            y(x==0) = 1;
            
%             % input is zero, then output is 1
%             if x == 0, y =1, end
%             % input is negative-real
%             if x < 0
%                 % using a first-order filter:
%                 % laplace transfer-function
%                 % impulse response: un = 1, always unity.
%                 for id = 0:N
%                     y = y + (ts.*(y-1));
%                     %y = y.*(1+ts) - ts;
%                 end
%                 y = 1 - y;
%                 % the natural exponential of
%                 % very large negative numbers tend to zero
%                 if isnan(y)
%                     y = 0;
%                 end
%             end
%             
%             % if input is positive real
%             if x > 0
%                 % using a first-order filter:
%                 % laplace transfer-function
%                 % impulse response: un = 1, always unity.
%                 for id = 0:N
%                     y = y + (ts.*(1+y));
%                     % y = y.*(1+ts) + ts;
%                 end
%                 y = 1 + y;
%             end
            
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
        function y = ieven(n)
            %IEVEN
            % tests if an input integer n is even or not
            % returns 1 for even n, 0 for  odd n.
            
            %             arguments
            %                 n
            %             end
            
            y = ~(bitand(n,1,'int32')); % ~(n & 1)
            
        end
        
    end
end

