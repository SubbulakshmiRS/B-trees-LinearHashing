#include<bits/stdc++.h> 

using namespace std;  

long int n,m,cur,capacity,size,divm,divl;
map<long int ,vector<long int > > data;
map<long int ,vector<long int > > overflowData;

void printData()
{
    cout<<endl;
    for(int i=0;i<data.size();i++)
    {
        cout<<i<<endl;
        for(int j=0;j<data[i].size();j++)
            cout<<data[i][j]<<" ";

        cout<<" | ";
        if(overflowData.find(i) != overflowData.end())
        {
            for(int j=0;j<overflowData[i].size();j++)
                cout<<overflowData[i][j]<<" ";
        }
        cout<<"\n============================="<<endl;
    }

}

long int calcIndex(long int value)
{
    long int  index = value%divm;
    index += divm;
    index = index%divm;
    if(cur > index)
    {
        index = value%divl;
        index += divl;
        index = index%divl;
    }
    return index;
}

bool search(long int  value)
{
    long int index1 = calcIndex(value);

    //cout<<divm<<" "<<divl<<" "<<index1<<" "<<value<<"     ";
    if(find(data[index1].begin(),data[index1].end(),value) != data[index1].end())
        return true;

    if(overflowData.find(index1) != overflowData.end() &&  find(overflowData[index1].begin(),overflowData[index1].end(),value) != overflowData[index1].end())
        return true;

    return false;
}

void processCommand(long int value)
{

    //////cout<<"ENTER    "<<value<<endl;
    if(cur>=n)
    {
        n = m;
        divm = divm*2;
        if(m != divm)
        {
            cout<<"ERROR not matching m and divm";
        }
        divl = divm*2;
        cur = 0;
    }

    if(search(value))
        return ;

    long int index = calcIndex(value);
    
    if(data[index].size() >= capacity)
    {
        if(overflowData.find(index) == overflowData.end())
        {
            vector<long int > temp;
            overflowData[index] = temp;
        }
        overflowData[index].push_back(value);
    }
    else 
        data[index].push_back(value);

    size++;
    float error =  ((float)size/((float)(m*capacity)));
    //////cout<<"SIZE "<<size<<" M "<<m<<" CAPACITY "<<capacity<<" ERROR "<<error<<endl;
    if(error > 0.75)
    {
        //cout<<"\nEXPAND1   "<<m<<endl;
        vector<long int> temp1;
        data[m] = temp1;
        cur++;
        long int  x = m-divm;

        if(x != (cur-1))
        {
            cout<<"not matching x and current block to break\n";
            cout<<value<<endl;
            cout<<x<<endl;
            cout<<cur<<endl;
            exit(1);
        }
        vector<long int > waste;
        for(long int  i=0;i<data[x].size();i++)
        {
            if(calcIndex(data[x][i]) == m)
            {
                data[m].push_back(data[x][i]);
                //cout<<data[x][i]<<" ";
                waste.push_back(i);
                //data[x].erase(data[x].begin()+i);
            }
        }
        //////cout<<"X "<<x<<" "<<data[x].size()<<endl;
        for(long int  i=0;i<waste.size();i++)
        {
            //////cout<<waste[i]<<endl;
            data[x].erase(data[x].begin()+(waste[i]-i));
        }

        //////cout<<"f es ";
        waste.clear();
        //////cout<<"EXPAND2   "<<value<<endl;
        if(overflowData.find(x) != overflowData.end())
        {
            //cout << "\nChecking for overflow " << endl;
            for(long int i=0;i<overflowData[x].size();i++)
            {                //cout << overflowData[x][i] << " " << calcIndex(overflowData[x][i]) << endl;

                if(calcIndex(overflowData[x][i]) == m)
                {
                    if(data[m].size() < capacity)
                        data[m].push_back(overflowData[x][i]);
                    else
                   {
                        if(overflowData.find(m) == overflowData.end())
                        {
                            vector<long int > temp;
                            overflowData[m] = temp;
                        }
                        overflowData[m].push_back(overflowData[x][i]);
                    }
                    
                    //cout<<overflowData[x][i]<<" ";
                    waste.push_back(i);
                    //overflowData[x].erase(overflowData[x].begin()+i);
                }
            }
            //////cout<<"dfnd ";
            for(long int  i=0;i<waste.size();i++)
                overflowData[x].erase(overflowData[x].begin()+(waste[i]-i));
          
        }

        ////cout<<"EXPAND3   "<<value<<endl;
        waste.clear();
        m++;
    }

    //////cout<<"======================="<<endl;
    cout<<value<<endl;
}

int  main(int  argc, char** argv)
{
    n = 2;
    m = 2;
    divm = 2;divl = 4;
    size = 0;
    cur = 0;
    capacity = 3;

    vector<long int > temp;
    data[0] = temp;
    vector<long int > temp1(temp);
    data[1] = temp1;

    if(argc < 2)
    {
        cout<<"Not enough arguments"<<endl;
        return 0;
    }

    char* filename=argv[1];

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        long int  n=0,num;
        while (getline(file, line)) {
            num = atoi(line.c_str());
            n++;
            processCommand(num);
        }
        file.close();
        //printData();
    }
    return 0;
}
