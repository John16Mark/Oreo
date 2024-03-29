%%VALORES DE X 
x=[50000000 100000000 500000000 1000000000 5000000000];
 
%%POLINOMIOS DE CADA ALGORITMO, DE LA APROXIMACIÓN SELECCIONADA, AQUI SE
%%PEGA LO QUE SALGA EN P, O EN SU DEFECTO PXLOGK
%Grado 1 Lineal
y1=[2.108520231515151e-09,0.001131399466667];
%Grado 2 ABB
y2=[3.940600369387357e-07,-4.012795138447297e-06];
%Grado Binaria
y3=[2.333864132155350e-07,-2.421738923280408e-06];
%Grado Exponencial
y4=[3.222744045990978e-07,-3.205871996181187e-06];
%Grado Fibonacci
y5=[2.068505054941463e-07,-1.657420880167905e-06];

%%SE CREA UN ESPACIO PARA REALIZAR UNA GRAFICA EN 
%%DONDE SE COMPARA LA CURVA AJUSTADA CONTRA LOS 
%%VALORES EXPERIMENTALES
xi=linspace(0,20000000, 5);      %%ESPACIO DE PUNTOS PARA Xi
%Lineal
z1=polyval(y1,xi);				%%EVALUACION DEL POLINOMIO Y1 EN EL ESPACIO Xi
%Binaria
z2=polyval(y2,log(xi));	    	%%EVALUACION DEL POLINOMIO Y2 EN EL ESPACIO Xi
%Binaria
z3=polyval(y3,log(xi));	    	%%EVALUACION DEL POLINOMIO Y3 EN EL ESPACIO Xi
%Binaria
z4=polyval(y4,log(xi));	    	%%EVALUACION DEL POLINOMIO Y4 EN EL ESPACIO Xi
%Binaria
z5=polyval(y5,log(xi));	    	%%EVALUACION DEL POLINOMIO Y5 EN EL ESPACIO Xi


%%SI HAY UNA SELECCION QUE SEA LOGARITMICA CAMBIAR LA PARTE DE POLIVAL POR
%%LA FUNCION CORRESPONDIENTE DONDE "K" ES EL NUMERO DE ALGORITMO
%zk = polyval(yk,xi.*log(xi));        %%EVALUACION DE LA CURVA LOGARITMICA YK EN EL ESPACIO Xi

%%SE REALIZA LA FIGURA CORRESPONDIENTE
figure(1);
%plot(x,z1,'o'),grid;        %Lineal
%plot(x,z2,'o'),grid;        %ABB
%plot(x,z3,'o'),grid;        %Binaria
%plot(x,z4,'o'),grid;        %Exponencial
%plot(x,z5,'o'),grid;        %Fibonacci

ylabel('F_t(n)');
xlabel('n');
title('Ajuste polinomial');
%legend('Bur. Simple', 'Bur. Opt. 1', 'Bur. Opt. 2', 'Inserción', 'Selección', 'Shell', 'TreeSort', 'MergeSort', 'QuickSort', 'HeapSort');