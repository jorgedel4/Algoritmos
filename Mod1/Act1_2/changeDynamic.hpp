vector<int> aux(vector<int> denominaciones, vector<int> coins) {
  vector<int> respuesta(denominaciones.size());

  for(int i = 0, j = denominaciones.size() - 1; i < denominaciones.size(); ++i, --j)
    respuesta[i] = count(coins.begin(), coins.end(), denominaciones[j]);

  return respuesta;
}

vector<int> changeDynamic(int change, vector<int> denominaciones) {
  vector<int> DP[change + 1];
  DP[0] = {}; 

  for(int i = 0; i <= change; ++i) {
    vector<vector<int>> posibles;

    for(int denominacion : denominaciones){
      if(denominacion > i) continue;
      vector<int> _DPAct = DP[i - denominacion];
      _DPAct.push_back(denominacion);
      posibles.push_back(_DPAct);
    }

    vector<int> mejor;

    for(int k = 0; k < posibles.size(); ++k) {
      if(!k) mejor = posibles[k];
      else {
        mejor = mejor.size() < posibles[k].size() ? mejor : posibles[k];
      }
    }
    DP[i] = mejor;
  }
  return aux(denominaciones, DP[change]);
}