#include <stdio.h>

void swap(int* a, int* b){ //aqui ocorre a troca dos elementos do vetor
    int temp = *a;
    *a = *b;
    *b = temp;
}

int selecao(int S[], int n, int k) {

    int i,j;

    if (n < 7) { //se o tamanho do vetor for < 7, iremos ordená-lo e depois retornar o k-esimo elemento
        for (int i = 0; i < n - 1; i++) { //Utilizando insertion sort para ordenar o vetor S
            int min = i;
            for (int j = i + 1; j < n; j++) {
                if (S[j] < S[min])
                    min = j;
            }
            swap(&S[i], &S[min]);
        }
        return S[k - 1];
    } else { //dividindo S em n/5 subsequências
        int numMedianas = (n+4) / 5;  //estou somando 4 p/arredondar o numero de medianas p/cima, ai eu nao perco elemento do vetor.
        int medianas[numMedianas];
        int index = 0;
        for (i = 0; i < n / 5; i++){ //determinando os indices iniciais e finais de cada subseq de tamanho 5
            int subEsq = i * 5; //como a subsq é de tam 5, então multiplicamos o i por 5 para pegar o indice inicial 
            int subDir = subEsq + 4; //indice final da subseq, já que são 4 elementos após o inicial.

            //Utilizando insertion sort para ordenar cada subsequencia
            for (j = subEsq; j < subDir; j++){ //subEsq = menor elemento à esquerda, subDir  = maior elemento à direita
                int min = j;
                for (int k = j + 1; k <= subDir; k++){
                    if (S[k] < S[min]){
                        min = k;
                    }
                }
                swap(&S[j], &S[min]);
            }
            medianas[index] = S[subEsq + 2]; //Determinando a mediana da subsequência
            index++;
        }

        // Determinando a mediana das medianas
        int medianOfmedianas = selecao(medianas, numMedianas, numMedianas / 2);

        // Dividindo o vetor S em três partes com base na mediana das medianas
        // Esses vetores são para armazenar os elementos menores, iguais e maiores que a mediana das medianas
        int S1[n], S2[n], S3[n];

        int sizeS1 = 0, sizeS2 = 0, sizeS3 = 0;

        for (int i = 0; i < n; i++){
            if (S[i] < medianOfmedianas){ //elementos menores que a mediana são colocados em S1
                S1[sizeS1] = S[i];
                sizeS1++;
            } else if (S[i] == medianOfmedianas){ //elementos iguais a mediana são colocados em S2
                S2[sizeS2] = S[i];
                sizeS2++; 
            } else { //elementos maiores que a mediana são colocados em S3
                S3[sizeS3] = S[i];
                sizeS3++;
            }
        }

        if (sizeS1 >= k){
            return selecao(S1, sizeS1, k);
        }
        else {
            if (sizeS1 + sizeS2 >= k){
                return medianOfmedianas;
            }
            else{
                return selecao(S3, sizeS3, k - sizeS1 - sizeS2);
            }
        }
    }
}

int main() {
    int S[] = {32,11,22,33,34,55,88,66,77,99};
    int n = sizeof(S) / sizeof(S[0]); //calculando o numero de elementos do vetor S
    int k = 10; //Definindo k entre [1,n]

    int result = selecao(S, n , k);
    printf("O elemento de ordem %d é: %d\n", k, result);

    return 0;
}