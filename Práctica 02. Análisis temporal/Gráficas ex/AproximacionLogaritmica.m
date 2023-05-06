%%VALORES DE X
x=[1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000];

%%VALORES DE Y = F(x) en Milisegundos

    %Búsqueda Binaria
    %y=[1 2 3 4 5 6 7 8 9 10];
    
    %Búsqueda en ABB
    %y=[1 2 3 4 5 6 7 8 9 10];

    %Búsqueda Exponencial
    %y=[1 2 3 4 5 6 7 8 9 10];

    %Búsqueda de Fibonacci
    %y=[1 2 3 4 5 6 7 8 9 10];

%%OBTENER UN POLINOMIO QUE SE AJUSTE A LOS PUNTOS X Y Y
p = polyfit(log(x),y,1);
a=p(1);
c=p(2);
fprintf('f(x)=%f*ln(x)+%f\n',a,c);

%%SE CREA UN ESPACIO PARA REALIZAR UNA GRAFICA EN 
%%DONDE SE COMPARA LA CURVA AJUSTADA CONTRA LOS 
%%VALORES EXPERIMENTALES
xi=linspace(0,10000000,2000);      %%ESPACIO DE PUNTOS PARA Xi
z = polyval(p,log(xi));        %%EVALUACION DE LA CURVA LOGARITMICA P EN EL ESPACIO Xi

%%SE REALIZA LA FIGURA CORRESPONDIENTE
figure(1);
plot(x,y,'o',xi,z,'-',LineWidth=1),grid;
ylabel('F(x)');
xlabel('x');
title('Ajuste logarítmico y=a·ln(x)+c');

