#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include<algorithm>
using namespace std;


struct TreeNode {
  TreeNode* left;
    TreeNode* right;
    float value;
}; 


bool isnum (string datapart){
     if( datapart.size() == 0 ){
      return false ; 
     }
     for (int i = 0 ; i < datapart.size() ; i++ ){
     char st = datapart[i] ; 
     if ( isdigit(st) ==  0 && st != '-' && st != '.') {
        return false ; 
     }
     }
     return true  ; 
}


 vector<vector<float>> data() {
   unordered_map<string,float>hash   ; 
   string line  ;
   vector<vector<float>>data ; 
   float code  = 0.0 ; 
   ifstream file("data.csv");
    while (getline(file, line)) {
     stringstream ss(line);
     string datapart;
      vector<float> row ;
      bool skip = false;  
     while (getline(ss, datapart, ',')) {
        if (datapart.size() == 0 ){
            skip = true ; 
            break ; 
        }
        if (isnum(datapart) == true){
            row.push_back(stof(datapart)) ;
        }
        else {
            if (hash.count(datapart)  == 0 ){
                code = code + 1.0 ; 
                hash[datapart] = code  ; 
                row.push_back(code) ; 
            }
            else {
                row.push_back(hash[datapart])  ; 
            }

        }
    }
    if (skip == false ){
        data.push_back(row) ; 
    }
} 
return data ; 
}


float gini_impurity_subtree(vector<float>&counts ){
    int n = counts.size() ; 
    float sum = 0.0 ; 
    float gini = 0.0  ; 
    for(int i  = 0 ; i< n ; i++){
     sum = sum + counts[i] ; 
    }
    for(int i = 0 ; i < n ; i++){
     gini = gini + pow(counts[i]/sum , 2) ; 
    }
    gini = 1 - gini ; 
    return gini ;
}


vector<float> gini_impurity_tree(vector<float> &right_subtree , vector<float>& left_subtree){
    int n = right_subtree.size() ; 
    vector<float>ans ; 
    float r ; 
    for (int i = 0 ; i< n ; i++  ){
    r = r + right_subtree[i] ; 
    }
    float l ; 
    int m = left_subtree.size() ;
    for (int i = 0 ; i< m ; i++ ){
        l = l + left_subtree[i] ; 
    }
    float right = gini_impurity_subtree(right_subtree) ; 
    float left = gini_impurity_subtree(left_subtree) ; 
    float tot = r+l ; 
    float gini_final = (r/tot)*(right) + (l/tot)*(left ) ; 
    ans.push_back(gini_final) ; 
    ans.push_back(left) ;
    ans.push_back(right) ;  

    return ans ; 
}


vector<float>get_perfect(vector<pair<float , float>> pr , vector<pair<float , int>>pos , vector<float>target_things ){
    vector<float>smallest_gini_imp ; 
    unordered_map<float , float > hash_left ;
    unordered_map<float , float > hash_right ; 
    vector<float>left ; 
    vector<float>right ; 
    float num ; 
    float gini = 100 ; 
    vector<float> gini_imp ; 
    int position  = 0  ; 
    float gini_end ; 
    float gini_cmp ; 

    int m = pr.size() ; 
    for (int i = 0 ; i< pos.size() ; i++ ){
     hash_left.clear();
     hash_right.clear();
     left.clear();
     right.clear();
     int g = pos[i].second ; 
     for (int j =  0 ; j < g ;j++){
     hash_left[pr[j].second] = hash_left[pr[j].second] + 1.0 ; 
     }
     for (int j =  g ; j < m ;j++){
     hash_right[pr[j].second] = hash_right[pr[j].second] + 1.0 ; 
     }
     int n = target_things.size() ; 
     for (int i = 0 ; i< n ;i++){
        left.push_back(hash_left[target_things[i]]) ; 
        right.push_back(hash_right[target_things[i]]) ; 
     }
     gini_imp = gini_impurity_tree(right  , left) ; 
     gini_cmp = gini_imp[0] ; 
     gini = min(gini ,gini_cmp ) ; 
     if (gini == gini_cmp) {
      num = pos[i].first  ; 
      position = pos[i].second ; 
      gini_end = gini_cmp ; 
      gini_left = gini_imp[1] ; 
      gini_right = gini_imp[2] ; 
     }
    }
        smallest_gini_imp.push_back(num)  ; 
        smallest_gini_imp.push_back(position)  ; 
        smallest_gini_imp.push_back(gini_end)  ; 
        smallest_gini_imp.push_back(gini_left) ; 
        smallest_gini_imp.push_back(gini_right) ; 
  return smallest_gini_imp ; 

}


vector<float> perfect_variable(vector<vector<float>>data){
    int n = data.size() ; 
    vector<float>target = data[n-1]  ; 
    float variable_pos  ; 
    float thresh_data_loc ; 
    vector<float>final_ans ; 
    vector<float >target_things  ; 
    unordered_map<float , int > tt ; 
    float gini_left ; 
    float gini_right ; 
    for (int i = 0 ; i < target.size() ; i++){
        if (tt[target[i]] > 0 ){
            continue ; 
        }
        else {
          target_things.push_back(target[i]) ; 
          tt[target[i]]++ ; 
        }
    }
     float gini ; 
     float gini_impurity  = 100 ; 
     float num ; 
    for ( int i = 0 ; i< n-1 ; i++){
        vector<pair<float  , float>> pr ; 
        for (int j = 0  ; j < data[i].size() ; j++ ){
            pr.push_back({data[i][j] , target[j]}) ; 
        }
        sort(pr.begin() , pr.end()) ; 
        vector<pair<float  , int>>pos ; 
        for (int k = 0 ; k< pr.size()-1 ; k++){
         float   first = pr[k].first ; 
         float second  = pr[k+1].first ; 
         float mid  = ( first + second)/2 ; 
         pos.push_back({mid , k+1 }) ; 
        }
        vector<float>vec = get_perfect(pr,pos,target_things ) ; 
       gini = v2ec[] ;  
        if (gini < gini_impurity){
            gini_impurity = gini ; 
            num = vec[0] ; 
            variable_pos = (float)i ;
            thresh_data_loc = vec[1] ; 
            gini_left = vec[3] ; 
            gini_right = vec[4]
        }
    }
 final_ans.push_back(gini_impurity  ) ; 
 final_ans.push_back( num ) ; 
 final_ans.push_back( variable_pos ) ; 
 final_ans.push_back(thresh_data_loc ) ;
 final_ans.push_back( gini_left ) ; 
 final_ans.push_back(gini_right ) ;
 
}

vector<vector<vector<float>>> new_dataset( vector<float>prev_data  ,vector<vector<float>> data) {
    int on_basis = (int)prev_data[2];
    int thresh = (int)prev_data[3];
    vector<vector<vector<float>>> result;
    sort(data.begin(), data.end(),
        [on_basis](vector<float>& a, vector<float>& b) {
            return a[on_basis] < b[on_basis];
        });

    vector<vector<float>> left_data(data.begin(), data.begin() + thresh + 1);
    for (int i = 0; i < left_data.size(); i++) {
        left_data[i].erase(left_data[i].begin() + on_basis);
    }
    vector<vector<float>> right_data(data.begin() + thresh + 1, data.end());
    for (int i = 0; i < right_data.size(); i++) {
        right_data[i].erase(right_data[i].begin() + on_basis);
    }
    result.push_back(left_data);
    result.push_back(right_data);
    return result;
}

void rec(vector<vector<float>>dta , int i  , int n  , TreeNode*tree){
    if (i > 9 || n == 0 ){
        return  ; 
    }
    vector<float>thing = perfect_variable(dta) ; 
    tree->value = thing[1] ; 
    vector<vector<vector<float>>>dt  = new_dataset(thing  , dta);
    vector<vector<float>>left_part = dt[0] ; 
    vector<vector<float>>right_part = dt[1] ; 
    if (thing[4] > 0.01){
    tree->left = new TreeNode();
    rec(left_part , i+1 , n-1 ,  tree->left) ;
    }
    if (thing[5] > 0.01){ 
     tree->right = new TreeNode();
    rec(right_part , i+1 , n-1 , tree->right) ; 
    }
    return  ; 
}


int main(){
    TreeNode* tree = new TreeNode() ; 
    int i  = 0 ; 
    vector<vector<float>>data_set = data() ; 
    int size = data_set[0].size() ; 
    rec(data_set , i , size , tree ) ; 
    return 0 ; 
}




