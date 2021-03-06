function [x_n] = gradient_descent(A, gamma)
    
    n_iter=1000;

    % Initialisation x(0)
    n = size(A);
    n = n(1);
    x_0 = ones(n,1)/n;
   
    % Donn�es du TP
    alpha = 0.15;
    e = transpose(ones(1, n));
    
    % Voir r�solution
    B = 4 + gamma * n;
    S = ones(n)/n;
    M = (1 - alpha)*A + alpha*S;
    
    % Donn�es du TP
    mu = 1.99/B;
    
    x_n = x_0;
        
    % valeurs propres
    [V,D] = eig(M);
    
    % Matrice des valeurs propre, on voit la valeur propre 1 dans la
    % premiere colonne, donc on prend la premiere colonne de V pour
    % avoir le vecteur propre associ� (x*)
    x_etoile=V(:,1)
    x_etoile=x_etoile/sum(x_etoile)
    
    vals_norme = [];
    vals_th = [];
    
    for i=1:n_iter
        % Gradient : (voir pr�paration exo 1) (optimisation O(n*n) vers n
        % avec calcul de ((M - eye(n)) * x_n) mise en priorit� pour avoir
        % un vecteur multipli� par une matrice, et non une matrice par une
        % matrice
        %gradient = transpose(M - eye(n)) * ((M - eye(n)) * x_n) + gamma*(transpose(e) * x_n - 1) * e; % transpose(A) <=> A.'
        v = ((1-alpha)*sparse(A)*x_n  + alpha/n * sum(x_n) * ones(n,1)- x_n);
        gradient =((1-alpha) * transpose(sparse(A))* v + alpha/n * sum(v) * ones(n,1)) - v + gamma*(transpose(e) * x_n - 1) * e
        x_n = x_n - (mu * gradient); 
        
        % 2) 
        vals_norme(i) = norm(x_n-x_etoile);
        vals_th(i) = 1/2 * norm(M*x_n - x_n)^2 + (gamma/2)*(transpose(e)*x_n - 1)^2;
    end
    
    figure(1)
    plot(log(vals_norme))
    figure(2)
    plot(log(vals_th))
    
    
    