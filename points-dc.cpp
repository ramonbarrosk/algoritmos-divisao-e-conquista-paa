#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX 10000

using namespace std;

struct Ponto{
  int x, y;
};

vector<vector<Ponto>> dividir_pontos(vector<Ponto>& pontos){
  vector<vector<Ponto>> matriz(2);

  int indice_meio = pontos.size() / 2;

  for (int i = 0; i < pontos.size(); i++){
    if (i <= indice_meio){
      matriz[0].push_back(pontos[i]);
    } else {
      matriz[1].push_back(pontos[i]);
    }
  }

  return matriz;
}

double calcula_distancia(const Ponto& ponto1, const Ponto& ponto2){
  return sqrt(pow(ponto2.x - ponto1.x, 2) + pow(ponto2.y - ponto1.y, 2));
}

pair<pair<Ponto, Ponto>, double> forca_bruta(vector<Ponto>& pontos, int n){
  double min = MAX;
  pair<Ponto, Ponto> par_menor;

  for (int i = 0; i < n; i++){
    for (int j = i + 1; j < n; j++){
      if (calcula_distancia(pontos[i], pontos[j]) < min){
        min = calcula_distancia(pontos[i], pontos[j]);
        par_menor = {pontos[i], pontos[j]};
      }
    }
  }

  return {par_menor, min};
}

pair<pair<Ponto, Ponto>, double> points_dc(vector<Ponto>& pontos, int quantidade){
  if (quantidade <= 3){
    return forca_bruta(pontos, quantidade);
  }


  vector<Ponto> pontos_ordenados = pontos;
  sort(pontos_ordenados.begin(), pontos_ordenados.end(), [](const Ponto& ponto1, const Ponto& ponto2) {
        return ponto1.x < ponto2.x;
    });

  int meio = quantidade/2;
  Ponto ponto_medio = pontos[meio];

  vector<vector<Ponto>> matriz_dividida = dividir_pontos(pontos_ordenados);

  auto [par_menor_esq, dist_esq] = points_dc(matriz_dividida[0], matriz_dividida[0].size());
  auto [par_menor_dir, dist_dir] = points_dc(matriz_dividida[1], matriz_dividida[1].size());

  double menor_distancia = min(dist_esq, dist_dir);
  pair<Ponto, Ponto> pontos_proximos = (dist_esq < dist_dir) ? par_menor_esq : par_menor_dir;

  vector<Ponto> pontos_interior;

  for (int i = 0; i < quantidade; i++){
    if (abs(pontos[i].x - ponto_medio.x) < menor_distancia){
      pontos_interior.push_back(pontos[i]);
    }
  }

  sort(pontos_interior.begin(), pontos_interior.end(), [](const Ponto& ponto1, const Ponto& ponto2) {
      return ponto1.y < ponto2.y;
  });


  for (int i = 0; i < pontos_interior.size(); i++){
    for (int j = i + 1; j < pontos_interior.size(); j++){
      if (pontos_interior[j].y - pontos_interior[i].y >= menor_distancia){
        break;
      }
      double dist = calcula_distancia(pontos_interior[i], pontos_interior[j]);
      if (dist < menor_distancia){
        menor_distancia = dist;
        pontos_proximos = {pontos_interior[i], pontos_interior[j]};
      }
    }
  }

  return {pontos_proximos, menor_distancia};
}

int main(){
  int n;

  cin >> n;

  vector<Ponto> pontos;

  for (int i = 0; i < n; i++){
    Ponto ponto;
    cout << "Digite as coordenadas do ponto " << i + 1 << "\n";
    cout << "Coordenada x: ";
    cin >> ponto.x;
    cout << "Coordenada y: ";
    cin >> ponto.y;

    pontos.push_back(ponto); 
  }

  for (int i = 0; i < n; i++){
    cout << "Ponto " << i + 1 << ": ";
    cout << "Coordenada x: " << pontos[i].x << " ";
    cout << "Coordenada y: " << pontos[i].x << " ";
    cout << "\n";
  }

  pair<pair<Ponto, Ponto>, double> resultado;
  resultado = points_dc(pontos, n);

  double distancia = resultado.second;
  Ponto ponto1 = resultado.first.first;
  Ponto ponto2 = resultado.first.second;

  if (n == 1){
    cout << "Como existe apenas um ponto, a menor distância é 0!\n";
  } else {
    cout << "---------------\n";
    cout << "Saída\n";
    cout << "---------------\n";
    cout << "Ponto1:\n";
    cout << "x: " << ponto1.x << endl;
    cout << "y: " << ponto1.y << endl;

    cout << "Ponto2:\n";
    cout << "x: " << ponto2.x << endl;
    cout << "y: " << ponto2.y << endl;

    cout << "------\n";
    cout << "Menor distancia:" << distancia << endl;
  }

  return 0;
}
