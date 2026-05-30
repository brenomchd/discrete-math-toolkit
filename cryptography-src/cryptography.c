#include "cryptography.h"

void menu () {
    printf("CRIPTOGRAFIA\n");
    printf("1 -> Descobrir chave publica (RSA)\n");
    printf("2 -> Descobrir chave privada (RSA)\n");
    printf("3 -> Encriptar mensagem (RSA)\n");
    printf("4 -> Desencriptar mensagem (RSA)\n");
    printf("0 -> SAIR\n");
}

lli t_euclides_estendido(lli a, lli b) {
    lli old_r = a, r = b;
    lli old_s = 1, s = 0;
    lli old_t = 0, t = 1;

    while (r != 0) {
        lli q = old_r / r;
        lli tmp = r; r = old_r - q * r; old_r = tmp;
        tmp = s; s = old_s - q * s; old_s = tmp;
        tmp = t; t = old_t - q * t; old_t = tmp;
    }
    return old_t;
}

lli num_primo(lli n) {
    if (n <= 1) return FALSE;
    if (n <= 3) return TRUE;
    if (n % 2 == 0) return FALSE;
    for (lli i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return FALSE;
    }
    return TRUE;
}

lli num_inverso(lli n, lli t) {
    return (t % n + n) % n;
}

lli inverter(lli phi, lli num) {
    printf("\n\tPrecisamos calcular o t de %lld em Zphi(n)=%lld\n\n", num, phi);
    lli t = t_euclides_estendido(phi, num);
    printf("\n\tO t é %lld\n", t);
    printf("\tInverso = t mod phi(n)\n");
    return num_inverso(phi, t);
}

public_key chave_publica(private_key Apvt) {
    public_key T;
    printf("\tTendo p e q, podemos calcular o phi(n): ");
    lli phi = (Apvt.p - 1) * (Apvt.q - 1);
    printf("%lld\n", phi);
    printf("\tCom o phi(n), descobrimos o 'e', já que 'e' é o inverso de 'd' em Zphi(n)\n");
    T.e = inverter(phi, Apvt.d);
    T.n = Apvt.p * Apvt.q;
    printf("\tE(M) = M^%lld mod %lld\n", T.e, T.n);
    return T;
}

private_key chave_privada(public_key B) {
    private_key T;
    printf("\n\tPrecisamos achar os numeros p e q que resultam em %lld\n", B.n);
    for (T.p = 2; T.p * T.p <= B.n; T.p++) {
        if (B.n % T.p == 0) break;
    }
    T.q = B.n / T.p;
    printf("\t(p,q) de 'B': (%lld,%lld)\n", T.p, T.q);
    printf("\tTendo p e q, podemos calcular o phi(n): ");
    lli phi = (T.p - 1) * (T.q - 1);
    printf("%lld\n", phi);
    printf("\tCom o phi(n), descobrimos o 'd', já que 'd' é o inverso de 'e' em Zphi(n)\n");
    T.d = inverter(phi, B.e);
    return T;
}

static lli mod_pow(lli base, lli exp, lli mod) {
    lli result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

lli encriptar_RSA(public_key A, lli m) {
    printf("\tPrecisamos calcular E(M) = M^e mod n\n");
    printf("\tIsto eh %lld^%lld mod %lld\n", m, A.e, A.n);
    return mod_pow(m, A.e, A.n);
}

lli desencriptar_RSA (private_key Apvt, lli N) {
    lli n = Apvt.p * Apvt.q;
    printf("\n\tD(N) = N^d mod n, ou seja -> D(%lld) = %lld^%lld mod %lld\n", N, N, Apvt.d, n);
    lli msg = mod_pow(N, Apvt.d, n);
    printf("\tResultado: %lld\n", msg);
    return msg;
}

lli tcr(lli a1, lli a2, lli p, lli q) {
    int s = 2; // s = número de sistemas
    int i, j; // i,j são variáveis auxiliares
    
    /*
    uma matriz que armazena os números de cada sistema 
    1. tabela_tcr[0][i] = ai;
    2. tabela_tcr[1][i] = mi;
    3. tabela_tcr[2][i] = Mi;
    4. tabela_tcr[3][i] = xi;
    5. tabela_tcr[4][i] = yi = inverso de xi;
    6. tabela_tcr[5][i] = ai*Mi*yi;
    7. tabela_tcr[6][i] = (ai*Mi*yi) mod m;
    8. tabela_tcr[7][i] = + modular;
    */
   
    lli tabela_tcr[7][2];
    lli m = p*q; // número que armazena o m (m1*m2*m3*...*mi)
    
    /* 
     * 1. Mi = (m/mi);
     * 2. xi = Mi mod mi;
     * 3. yi = o inverso de xi em Zmi;
     * 4. solução de x = somatório de i = 1 indo até um número t calculando (ai * Mi * yi) mod m.
    */

    tabela_tcr[0][0] = a1; // armazenando a1 
    tabela_tcr[0][1] = a2; // armazenando a2

    tabela_tcr[1][0] = p; // armazenando m1
    tabela_tcr[1][1] = q; // armazenando m2
    
    // Para saber se tem solução, precisamos saber se o mdc entre
    // todos p e q é 1, ou seja, se são primos entre si.
    
    if (mdc_dois_numeros(tabela_tcr[1][0],tabela_tcr[1][1]) != 1) {
        printf("Os mi's não são primos entre si, o sistema não possui soluções\n");
        return FALSE;
    }

    // printf("m: %ld\n", m);
    for (i = 0; i < 2; i++) { // calculando Mi (Mi = m/mi)
        tabela_tcr[2][i] = m/(double)tabela_tcr[1][i]; 
        // printf("M%i = %ld/%ld\n", i, m, tabela_tcr[2][i]); 
    }
    for (i = 0; i < 2; i++) { // calculando xi
        tabela_tcr[3][i] = tabela_tcr[2][i] % tabela_tcr[1][i];
        // printf("x%d = %ld\n", i, tabela_tcr[3][i]);
    }

    lli t; // variável que armazena o t de euclides estendido (mi,xi)
    
    for (i = 0; i < 2; i++) { // calculando yi, o inverso de xi em Zmi
        printf("\n\tEncontrando y%i:\n", i+1);
        t = t_euclides_estendido(tabela_tcr[1][i],tabela_tcr[3][i]); // t de euclides estendido
        // printf("t de m%d,x%d: %ld\n", i, i, t);
        tabela_tcr[4][i] = num_inverso(tabela_tcr[1][i],t); // número inverso de xi em Zmi
        // printf("y%d: %ld\n",i,tabela_tcr[4][i]);
    }
    printf("\n");
    for (i = 0; i < 2; i++) { // calculando ai*Mi*yi
        tabela_tcr[5][i] = tabela_tcr[0][i]*tabela_tcr[2][i]*tabela_tcr[4][i];
    }
    for (i = 0; i < 2; i++) { // calculando (ai*Mi*yi) mod m
        tabela_tcr[6][i] = tabela_tcr[5][i] % m;
        if (tabela_tcr[6][i] < 0) tabela_tcr[6][i] += m;
    }

    lli x = 0; // a solução do sistema
    
    for (i = 0; i < 2; i++) x = (x + tabela_tcr[6][i]) % m;
    
    print_TCR(tabela_tcr,x);
    return x;    
}

void print_TCR(lli tabela_tcr[7][2], lli x) {
    int i;
    printf("\tTCR:\n");
    printf("\t|i              |");
    for (i = 0; i < 2; i++) printf("%10d|", i+1);
    printf("\n");
    printf("\t|ai             |");
    for (i = 0; i < 2; i++) printf("%10lld|", tabela_tcr[0][i]);
    printf("\n");
    printf("\t|mi             |");
    for (i = 0; i < 2; i++) printf("%10lld|", tabela_tcr[1][i]);
    printf("\n");
    printf("\t|Mi = m/mi      |");
    for (i = 0; i < 2; i++) printf("%10lld|", tabela_tcr[2][i]);
    printf("\n");
    printf("\t|xi = Mi mod mi |");
    for (i = 0; i < 2; i++) printf("%10lld|", tabela_tcr[3][i]);
    printf("\n");
    printf("\t|yi = (xi)-¹    |");
    for (i = 0; i < 2; i++) printf("%10lld|", tabela_tcr[4][i]);
    printf("\n");
    printf("\t|ai*Mi*yi       |");
    for (i = 0; i < 2; i++) printf("%10lld|", tabela_tcr[5][i]);
    printf("\n");
    printf("\t|ai*Mi*yi mod m |");
    for (i = 0; i < 2; i++) printf("%10lld|", tabela_tcr[6][i]);
    printf("\n");
    printf("\t|x0             |%10lld|",x);
    printf("\n\n");
}

lli maior_numero (lli n1, lli n2) { // maior número entre dois números
    lli maior = (n1 > n2) ? n1 : n2;
    return maior;
}

lli mdc_dois_numeros(lli n1, lli n2) {
    if (n2 > n1) {
        lli temp = n1;
        n1 = n2;
        n2 = temp;
    }
    if (n2 == 0) return n1;
    else return mdc_dois_numeros(n2, n1 % n2);
}
