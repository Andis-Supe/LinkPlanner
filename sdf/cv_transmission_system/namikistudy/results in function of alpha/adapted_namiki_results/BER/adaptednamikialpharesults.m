%% N�o esquecer de usar o sqrt de alpha, pois os valores nas vari�veis
% alpha s�o os n�meros de fot�es
clearvars
close all
clc

files=dir('*.txt');

F1= @(x,alpha) sqrt(2/pi)*exp(-2*(x-alpha*cos(pi/4)/sqrt(2)).^2);
F2= @(x,alpha) sqrt(2/pi)*exp(-2*(x-alpha*sin(pi/4)/sqrt(2)).^2);

normfactor=.6404;
%BER=zeros(1,length(files)/2);
%BERT=BER;

alpha=0:5;


for i=1:1%length(files)/2;
    
    dataphas=load(files(i).name);
%    dataquad=load(files(i+length(files)/2).name);
    
    
    bins=50;
    [h1,x1]=hist(dataphas,bins);
    
    %    if i~=1;
    %        normfactor=abs(mean(dataphas))/alpha;
    %    end
    
    
    x1=x1/normfactor;
    h1=h1/trapz(x1,h1);
    
%    [h2,x2]=hist(dataquad,bins);
%    x2=x2/normfactor;
%    h2=h2/trapz(x2,h2);
    
    xint1=min(x1):1e-3:max(x1);
%    xint2=min(x2):1e-3:max(x2);
    hint1=interp1(x1,h1,xint1);
%    hint2=interp1(x2,h2,xint2);
    
    plot(xint1,hint1)
    hold on
 %   plot(xint2,hint2)
    legend('X','Y')
    
    
end
%%
    Xint1_mais=xint1(xint1>=0);
    Xint1_mens=xint1(xint1<=0);
  %  Xint2_mais=xint2(xint2>=0);
   % Xint2_mens=xint2(xint2<=0);
    
    %Yint1=sqrt(2/pi)*exp(-2*(xint1-sqrt(alpha(i))).^2);
    
    if ~isempty(Xint1_mais)
        Px_mais=trapz(Xint1_mais,hint1(length(hint1)-length(Xint1_mais)+1:length(hint1)));
    else
        Px_mais=0;
    end
    if ~isempty(Xint1_mens)
        Px_mens=trapz(Xint1_mens,hint1(1:length(Xint1_mens)));
    else
        Px_mens=0;
    end
    if ~isempty(Xint2_mais)
        Py_mais=trapz(Xint2_mais,hint2(length(hint2)-length(Xint2_mais)+1:length(hint2)));
    else
        Py_mais=0;
    end
    if ~isempty(Xint2_mens)
        Py_mens=trapz(Xint2_mens,hint2(1:length(Xint2_mens)));
    else
        Py_mens=0;
    end
    
    BER(i)=Px_mais*Py_mens+Px_mens*Py_mais+Px_mens*Py_mens;
    
end

xlabel('quadrature x')
ylabel('probability density')


%legend('\alpha^2=0','\alpha^2=0.25','\alpha^2=0.5','\alpha^2=0.75','\alpha^2=1','\alpha^2=1.5','\alpha^2=2','\alpha^2=3','\alpha^2=4','\alpha^2=5')


Alpha=linspace(0,5,1e3);

BERt=(2*erfc(sqrt(2)*(sqrt(Alpha)/2)).*erfc(sqrt(2)*(sqrt(Alpha)/2))+erfc(sqrt(2)*(sqrt(Alpha)/2)).^2)/6;
%erfc(sqrt(2)*sqrt(Alpha))./2;
figure
plot(alpha,BER,'*',Alpha,BERt,alpha,BERT,'+k')
xlabel('pulse  intensity (photon/pulse)')
ylabel('BER')
legend('numerical results','theoretical results')