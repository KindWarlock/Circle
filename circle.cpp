#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    const int size = 400;
    bool curr[size], prev[size];
    int y, vershx = 0, leftx = 0, vershy, r, x; //план: найти x0 через середину верхнего отрезка окружности, найти самый левый x, при х-х0 получить радиус и прибавить его к y вершины
    ifstream file("..\\inputs\\input.dat");
    if (!file.is_open()) {
        cout << "No file" << endl;
        return -1;
    }
    for (int x = 0; x < size; x++) {
        file >> prev[x];
    }
    for (int y = 1; y < size; y++) {
        for (x = 0; x < size; x++) {
            if (x > 2) prev[x-2] = curr[x-2]; //значения x и x-1 нам еще понадобятся
            file >> curr[x];
            if (curr[x] && prev[x] && !vershx) {
                for (int i = 0; prev[x + i]; i++) {
                    vershx++;
                }
                vershx = vershx/2 + x;
                vershy = y;
            }
            else if (x > 1 && x < vershx && curr[x] && !curr[x-1] && prev[x] && prev[x - 1]) {
                for (int i = x - 1; prev[i] == 1; --i) {    //возможна ситуация, при которой одна из лишних единиц снизу "приклеится" к окружности
                    if (curr[i] == 1) continue;
                }
                leftx = x - 1;
                break;
            }  
            
        }
        if (x > 0) prev[x - 1] = curr[x - 1];
        if (leftx) break;
    }
    ofstream out("..\\inputs\\output.dat");
    if (!out.is_open()) {
        cout << "Could not create a file" << endl;
        return -4;
    }
    r = vershx - leftx;
    out << vershx << " " << vershy + r - 1<< " " << r<< endl;
    file.close();
    out.close();
    return(0);
}

/*Honorable mention, я слишком поздно поняла, что улетаю по памяти
int main()
{
    const int size = 400;
    bool ones[size][size], temp, prev = 0;
    int vershx = 0, lefty = 0, leftx;
    ifstream file ("..\\inputs\\input1.dat");
    if (!file.is_open()) { 
        cout << "No file" << endl;
        return -1;
    }
    
    for (int x = 0; x <= 399; x++) {
        cin >> temp;
        if (temp) ones[x][0] = true;
    }
    for (int y = 1; y <= 399; y++) {
        for (int x = 1; x <= 399; x++) {
            cin >> temp;
            if (temp) ones[x][y] = true;
            if (!temp && prev) {
                if (ones[x][y - 1] && vershx == 0) vershx = x;
                else if (ones[x - 1][y - 1] && vershx == 0) vershx = x - 1;
                else if (vershx){
                    for (int i = 1; ; i++) {
                        if (ones[x - i][y - 1]) {
                            leftx = x - i;
                            lefty = y - 1;
                            break;
                        }
                    }
                    
                }
            }
            if (lefty) break;
            prev = temp;
        }
        if (lefty) break;
    }
    ofstream out("..\\inputs\\output11.dat");
    if (!out.is_open()) {
        cout << "Could not create a file" << endl;
        return -4;
    }
    cout << vershx << lefty << vershx - leftx << endl;
    file.close();
    out.close();
    return(0);
}*/
