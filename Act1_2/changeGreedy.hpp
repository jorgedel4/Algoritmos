vector<int> changeGr(int change, vector<int> currencies){
    vector<int> resultado;
    int _change;
    for(int i = currencies.size() - 1; i >= 0; --i){
        _change = change;
        for(int j = i; j >= 0; --j) {
            resultado.push_back(_change / currencies[j]);
            if(_change >= currencies[j]) _change %= currencies[j];
            if(!j && !_change) goto rtn;
        }
        resultado.clear();
    }
    rtn:
    int diff = currencies.size() - resultado.size();
    if(diff)
    for(int _ = 0; _ < diff; ++_) resultado.insert(resultado.begin(), 0);
    resultado.begin(), resultado.end();
    return resultado;
}