#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <new>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;
vector<vector<int> > cofactor(vector<vector<int> > cubes1, int x, int sign) {
  vector<vector<int> > temp;
  int num_variable;
  int num_cubes;
  num_cubes=cubes1.size();
  if (cubes1.size() == 0)
    num_variable == 0;
  else
    num_variable == cubes1[0].size();
  vector<int> eraserow;
  vector<int> insertrow;
  int count = 0;
  for (int i = 0; i < cubes1.size(); i++) {
    if (cubes1[i][x] == (!sign))  // if the sign is the same as the sign, then
                               // delete this row
        {
      cubes1[i][x]=2;  // make them dash
    } else if (cubes1[i][x] == 2)
      continue;
  }
    for(int i=0;i<num_cubes;i++)
    {
        if(cubes1[i][x]==2)
            temp.push_back(cubes1[i]);
    }
  return temp;
}

int binate_select(vector<vector<int> > cubes1) {
  int t = 0;  // the column of binate selection
  int num_variable;
  if (cubes1.size() == 0)
    num_variable = 0;
  else
    num_variable = cubes1[0].size();
  int num_cubes = cubes1.size();
  int count = 0;
  int max = 0;
  for (int i = 0; i < num_variable; i++) {
    count = 0;  // reinitiate the value of count
    for (int j = 0; j < num_cubes; j++) {
      if (cubes1[j][i] != 2) {
        count += 1;
      }
    }
    if (count >= max) {
      t = i;  // make this one column t at this time
      max = count;
    }
  }
  return t;
}

vector<vector<int> > unate_reduction(vector<vector<int> > cubes1) {
  int num_variable;
  int num_cubes;
  vector<vector<int> > unate;
  if (cubes1.size() != 0)
    num_variable = cubes1[0].size();
  else
    num_variable = 0;
  num_cubes = cubes1.size();  // the unate reduction cube
  int unate_check[num_variable];
  int flag;
  int check;
  int temp;
  int unate_count = 0;  // how many uante columns are in there in the cover
  int unate_sum = 0;
  vector<int> min_dash;  // the column with the smallest dash num
  int count = 0;
  vector<vector<int> > reduction;  // used to store the columns which are unate
  int sign = 0;                    // if
  vector<int> unate_column;
  for (int i = 0; i < num_variable; i++)  // check for unate
      {
    check = 0;
    for (int j = 0; j < num_cubes; j++) {
      if (cubes1[j][i] == 2)
        continue;
      else if (check == 0) {
        flag = cubes1[j][i];
        check = 1;
      } else {
        if (flag != cubes1[j][i]) {
          flag = 3;  // not uante
          break;
        }
      }
    }
    if (flag == 3)
      unate_check[i] = 0;  // not unate
    else {
      unate_check[i] = 1;  // is unate
      unate_count += 1;
      unate_column.push_back(i);  // mark this column as unate
    }
  }

  check = 0;
  for (int i = 0; i < num_cubes; i++) {
    check = 0;
    for (int j = 0; j < unate_column.size(); j++) {
      if (cubes1[i][unate_column[j]] != 2) {
        check = 1;
        goto here4;
      }
    }
  here4:
    ;
    if (check == 0)  // means this row has all dashes
        {
      min_dash.push_back(i);
    }
  }
  count = 0;
  for (int i = 0; i < min_dash.size(); i++) {
    vector<int> row;
    unate.push_back(row);
    for (int j = unate_count; j < num_variable; j++) {
      unate[count].push_back(cubes1[min_dash[i]][j]);
    }
    count += 1;
  }
  return unate;  // the unate reduction cover
}
int tautology(int num_variable, int num_cubes, vector<vector<int> > cubes1) {
  int t;
  int dash = 0;
  int check = 0;
  int flag = 1;
  vector<vector<int> > cubesN;  // negative
  vector<vector<int> > cubesP;  // positive
  int variable;
  int cubes;
  int cases = pow(2, num_variable);  // the decimal number of the cover case
  int totalminterm = 0;  // the total minterm covered by each row apply for the
                         // first sepcial case
  for (int i = 0; i < cubes1.size(); i++) {
    int count = 0;
    int tempcase = 1;  // the case for each row
    for (int j = 0; j < cubes1[i].size(); j++) {
      if (cubes1[i][j] == 2) {
        count += 1;
        flag ==
            0;  // the whole cover contains dash doesn't apply for the second
                // special case
        tempcase *=
            2;  // each time there is a dahs then the tempcase has 2 time case
      }
      if (check == 0 and count == num_variable)  // if there is a row with all
                                                 // dash
          {
        check = 1;
      }
    }
    totalminterm += tempcase;  // give the case of each row to the total case
  }
  if (totalminterm < cases)  // special case 1
      {
    // then it's not a toutology has to return the complement of the cover, for
    // now I just return -1, means it's not a toutology
    return 0;
  }
  if (flag == 1)  // means there is no dash in the whole cover, check special
                  // case 2
      {
    if (totalminterm == cases)  // means it's a totalology
        {
      return 1;
    }
  }
  if (cubes1.size() == 0)  // if the cube  is empty
    return 0;              // return false
  for (int i = 0; i < cubes1.size(); i++) {
    dash = 0;
    for (int j = 0; j < cubes1[i].size(); j++) {
      if (cubes1[i][j] != 2) {
        dash = 1;
        goto here3;
      }
    }
  here3:
    ;
    if (dash == 0) {
      return 1;
      break;
    }
  }
  for (int i = 0; i < cubes1[0].size(); i++) {
    flag = 0;
    check = 0;
    for (int j = 0; j < cubes1.size(); j++) {
      if (flag == 0 and cubes1[j][i] != 2) {
        flag = 1;
        check = cubes1[j][i];
      } else if (cubes1[j][i] == 2)  // contains dash
          {
        check = 2;
        break;
      } else if (flag == 1 and cubes1[j][i] != 2 and cubes1[j][i] !=
                 check)  // binate
          {
        check = 2;
        break;
      }
    }
    if (check != 2) {
      return 0;
    }
  }
  cubes1 = unate_reduction(cubes1);  // unate reduction
  t = binate_select(cubes1);
  cubesN = cofactor(cubes1, t, 0);  // cofactor column x with negative
  if (cubesN.size() != 0) {
    variable = cubesN[0].size();
    cubes = cubesN.size();
  } else {
    variable = 0;
    cubes = 0;
  }
  if (tautology(variable, cubes, cubesN) == 0) {
    return 0;  // return false
  }
  cubesP = cofactor(cubes1, t, 1);  // cofactor column x with positive
  if (cubesP.size() != 0) {
    variable = cubesP[0].size();
    cubes = cubesP.size();
  } else {
    variable = 0;
    cubes = 0;
  }
  if (tautology(variable, cubes, cubesP) == 0) {
    return 0;  // return false
  }

  return 1;  // return true
}

vector<vector<int> > andop(int position, int x, vector<vector<int> > cubes1) {
  if (!cubes1.empty())  // if the matrix is not empty
      {
    for (int i = 0; i < cubes1.size(); i++) {
      cubes1[i][position] = x;
    }
  }
  return cubes1;
}

vector<vector<int> > row_complement(vector<vector<int> > cubes1) {
  vector<vector<int> > temp;
  vector<int> row;
  int count = 0;
  for (int i = 0; i < cubes1[0].size(); i++) {
    if (cubes1[0][i] != 2)  // get the complement of the row
        {
      temp.push_back(row);
      for (int j = 0; j < cubes1[0].size(); j++) {
        temp[count].push_back(2);
      }
      temp[count][i] = (!cubes1[0][i]);
      count += 1;
    }
  }
  return temp;
}
int unate_select_complement(vector<vector<int> > cubes1) {
  int num_variable;
  int num_cubes1;
  int t;
  int max = 0;
  int count = 0;
  for (int i = 0; i < cubes1[0].size(); i++) {
    count = 0;
    for (int j = 0; j < cubes1.size(); j++) {
      if (cubes1[j][i] != 2) count += 2;
    }
    if (count > max) {
      max = count;
      t = i;
    }
  }
  return t;
}

int binate_select_complement(vector<vector<int> > cubes1) {
  int num_variable;
  int num_cubes;
  int t;
  int max = 0;
  int count = 0;
  int check = 0;
  int flag = 0;
  int binate = 0;
  num_cubes = cubes1.size();
  if (cubes1.size() == 0) {
    num_variable = 0;
    return 0;
  } else
    num_variable = cubes1[0].size();
  for (int i = 0; i < num_variable; i++) {
    check = 0;
    binate = 0;
    count = 0;
    for (int j = 0; j < num_cubes; j++) {
      if (check == 0 and cubes1[j][i] != 2) {
        flag = cubes1[j][i];
        check = 1;
        count += 1;
      } else if (check == 1 and cubes1[j][i] != 2) {
        count += 1;
        if (cubes1[j][i] != flag) binate = 1;
      }
    }
    if (binate == 1) {
      if (count > max) {
        t = i;
        max = count;
      }
    }
  }
  if (max == 0) {
    t = -1;
  }
  return t;
}
vector<vector<int> > unate_complement(vector<vector<int> > cubes1) {
  vector<int> row;
  vector<vector<int> > temp;
  int count = 0;
  if (cubes1.size() == 0) return temp;
  int num_variable = cubes1[0].size();
  for (int i = 0; i < cubes1.size(); i++) {
    for (int j = 0; j < cubes1[0].size(); j++) {
      if (cubes1[i][j] != 2) {
        temp.push_back(row);
        for (int k = 0; k < num_variable; k++) {
          temp[count].push_back(2);
        }
        temp[count][j] = (!cubes1[i][j]);
        count += 1;
      }
    }
  }
  return temp;
}
vector<vector<int> > complement(vector<vector<int> > cubes1) {
  int num_variable;
  int num_cubes;
  int all_dash = 0;
  int sign = 0;
  int check;
  int flag;
  int all_column;
  int t;
  int binate_check = 0;
  vector<int> row;
  vector<vector<int> > temp;
  vector<vector<int> > temp_left;
  vector<vector<int> > temp_right;
  vector<vector<int> > R1;
  vector<vector<int> > R2;
  if (cubes1.size() == 0) {
    temp.push_back(row);
    temp[0].push_back(2);
    return temp;
  }
  num_variable = cubes1[0].size();
  num_cubes = cubes1.size();
  for (int i = 0; i < num_cubes; i++)  // check if it contains all dash
      {
    all_dash = 0;
    for (int j = 0; j < num_variable; j++) {
      if (cubes1[i][j] != 2) {
        all_dash = 1;  // this row is not all dash
        break;
      }
    }
    if (all_dash == 0) return temp;  // return a empty cubes
  }
  if (cubes1.size() == 1) return row_complement(cubes1);

  t = binate_select_complement(cubes1);
  if (t == -1) {
    t = binate_select(cubes1);
    binate_check = 1;
    for (int i = 0; i < num_cubes; i++) {
      if (cubes1[i][t] != 2) {
        sign = cubes1[i][t];
        break;
      }
    }
  }
  temp_right = cofactor(cubes1, t, 1);  // cofactror 0
  temp_left = cofactor(cubes1, t, 0);   // cofactor 1

  R1 = complement(temp_left);
  R2 = complement(temp_right);
  if (R1.size() == 1 and R1[0].size() == 1) {
    for (int i = 1; i < num_variable; i++) {
      R1[0].push_back(2);
    }
  }
  if (R2.size() == 1 and R2[0].size() == 1) {
    for (int i = 1; i < num_variable; i++) {
      R2[0].push_back(2);
    }
  }
  /**else
  {
      R1=unate_complement(temp_left);
      if(R1.size()==0)
          {
          R1.push_back(row);
          for(int i=0;i<num_variable;i++)
              {
              R1[0].push_back(2);
              }
          }
      R2=unate_complement(temp_right);
      if(R2.size()==0)
          {
          R2.push_back(row);
          for(int i=0;i<num_variable;i++)
              {
              R2[0].push_back(2);
              }
          }
  }**/
  if (binate_check != 1) {
    R1 = andop(t, 1, R1);
    R2 = andop(t, 0, R2);
  } else if (binate_check == 1) {
    if (sign == 1) {
      // R1=andop(t,2,R1);
      R2 = andop(t, 0, R2);
    } else if (sign == 0) {
      R1 = andop(t, 1, R1);
      // R2=andop(t,2,R2);
    }
  }
  if (R1.size() > R2.size()) {
    for (int i = 0; i < R1.size(); i++) {
      temp.push_back(R1[i]);  // push row by row
      if (i < R2.size()) {
        temp.push_back(R2[i]);
      }
    }
  } else {
    for (int i = 0; i < R2.size(); i++) {
      temp.push_back(R2[i]);
      if (i < R1.size()) {
        temp.push_back(R1[i]);
      }
    }
  }
  return temp;
}
int main() {
  int line = 0;
  int num_variable;
  int num_cubes;
  int content;
  int t;
  string filename;
  vector<vector<int> > cubes;
  vector<vector<int> > complement_cubes;
  vector<int> result;
  char ch;
  // cout<<"input file name: "<<endl;
  // cin>>filename;
  ifstream fin(filename.c_str());
  // if(fin.is_open())
  while (cin) {
    if (line == 0) {
      cin >> num_variable;
      line++;
    } else if (line == 1) {
      cin >> num_cubes;
      line++;
      for (int i = 0; i < num_cubes; i++) {
        vector<int> row;
        cubes.push_back(row);
      }
    } else {
      for (int i = 0; i < num_variable; i++) {
        cin >> ch;
        if (ch == '_' or ch == '-')
          cubes[line - 2]
              .push_back(2);  // in case the read in is a dash then make it 2
        else
          cubes[line - 2]
              .push_back((int)ch - 48);  // in case the read in is others then
                                         // firt format it into integer type
      }
      line++;
      if (line == num_cubes + 2) break;
    }
  }
  t = tautology(num_variable, num_cubes, cubes);
  // cout<<t<<endl;
  if (t == 1)  // it's a tautology
      {
    for (int i = 0; i < num_variable; i++) cout << "_";
    cout << "" << endl;
  } else if (t == 0)  // it's not a tautology
      {
    complement_cubes = complement(cubes);
    for (int i = 0; i < complement_cubes.size(); i++) {
      for (int j = 0; j < complement_cubes[0].size(); j++) {
        if (complement_cubes[i][j] == 2)
          cout << "_";
        else
          cout << complement_cubes[i][j];
      }
      cout << "" << endl;
    }
  }
  return 0;
}
