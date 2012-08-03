#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int index;
    int weight;
};

vector<Node> deleteFromVector(vector<Node>values,int a)
{
    int valueSize=values.size();
    for(int i=0;i<valueSize;i++)
    {
        if(values[i].index==a)
            values.erase(values.begin()+i);
    }
    return values;
}

vector<Node> merge(vector<Node>a,vector<Node>b)
{
    vector<Node>merged;
    int limit=a.size()<=b.size()?b.size():a.size();
    int k=0;
    int j=0;
    while(k<a.size() && j<b.size()){
        if(a[k].weight<b[j].weight)
        {
            merged.push_back(a[k]);
            k++;
        }
        else
        {
            merged.push_back(b[j]);
            j++;
        }
    }
    if(k>=a.size()) for(int i=j;i<b.size();i++) merged.push_back(b[i]);
    else for(int i=k;i<a.size();i++) merged.push_back(a[i]);
    return merged;
}
vector<Node>partition(vector<Node>&a,int start,int finish)
{
    vector<Node>parted;
    int size=finish-start+1;
    for(int i=0;i<size;i++) parted.push_back(a[i+start]);
    return parted;
}
void printVector(vector<int>&a)
{
    for(int i=0;i<a.size();i++)
        cout<<a[i]+1<<" ";
}

vector<Node>mergeSort(vector<Node>a)
{
    if(a.size()<=1)
        return a;
    else
    {
        vector<Node>partition1=partition(a,0,a.size()/2-1);
        vector<Node>partition2=partition(a,a.size()/2,a.size()-1);
        return merge(mergeSort(partition1),mergeSort(partition2));
    }
}


vector<int>aClique(int **graph,int numberOfNodes)
{


    srand(time(0));
    vector<int>basicSolutionSet;
    vector<Node>RCL;
    int currentNode;

    int initialNode=rand()%numberOfNodes;
    cout<<"Lucky node is Node #"<<initialNode+1<<endl;
    basicSolutionSet.push_back(initialNode);
    //Find first base neighbors of selected node
    for(int i=0;i<numberOfNodes;i++)
    {
        if(graph[initialNode][i]!=0)
        {
            Node a;
            a.index=i;
            a.weight=graph[initialNode][i];
            RCL.push_back(a);
        }
    }

    //List neighbors using a greedily: In this case by their weights.
    cout<<"neighbors of Node #"<<initialNode+1<<":"<<endl;
    //Using merge sort for efficienty
    RCL=mergeSort(RCL);
    for(int i=0;i<RCL.size();i++) {
        cout<<"Node #:"<<RCL[i].index+1<<" Weight:"<<RCL[i].weight<<endl;
    }

    int randomSelection=rand()%RCL.size();
    basicSolutionSet.push_back(RCL[randomSelection].index);

    currentNode=RCL[randomSelection].index;
    bool found=false;

    //Selected first neightbour

    //find the neighbors of the second node

    while(1)
    {
        cout<<"-------------------------------"<<endl;
        cout<<"Basic solution set: ";
        printVector(basicSolutionSet);
        cout<<endl;
        cout<<"-------------------------------"<<endl;
        if(RCL.size()<1)
            break;
        else
        {
            RCL.erase(RCL.begin(),RCL.end());
            for(int i=0;i<numberOfNodes;i++)
            {
                if(graph[currentNode][i]!=0 && std::find(basicSolutionSet.begin(),basicSolutionSet.end(), i) == basicSolutionSet.end())
                {
                    cout<<"Current Node: "<<currentNode+1<<" neighbor: "<<i+1<<endl;
                    Node a;
                    a.index=i;
                    a.weight=graph[currentNode][i];
                    RCL.push_back(a);
                }
            }
            if(RCL.size()<1)
                break;
            cout<<"--------------------------------------------"<<endl;
            cout<<"Node# "<<currentNode+1<<" neighbor size:"<<RCL.size()<<endl;
            cout<<"neighbors of Node #"<<currentNode+1<<":"<<endl;

            RCL=mergeSort(RCL);
            for(int i=0;i<RCL.size();i++)
            {
                cout<<"Node #:"<<RCL[i].index+1<<" Weight:"<<RCL[i].weight<<endl;
            }

            randomSelection=rand()%RCL.size();
            currentNode=RCL[randomSelection].index;
            int foundCounter=0;
            cout<<"Entering test with Node# "<<currentNode+1<<endl;

            while(RCL.size()>0 && foundCounter<basicSolutionSet.size()){
                for(int i=0;i<basicSolutionSet.size();i++)
                {
                    cout<<"Comparing node #"<<currentNode+1<<" with Node# "<<basicSolutionSet[i]+1<<endl;
                    if(graph[currentNode][basicSolutionSet[i]]==0)
                    {
                        cout<<"Deleting"<<endl;
                        RCL=deleteFromVector(RCL,currentNode);
                        if(RCL.size()>0)
                        {
                            currentNode=RCL[rand()%RCL.size()].index;
                            cout<<"Now node is Node# "<<currentNode+1<<endl;
                            i=0;
                            foundCounter=0;
                            //found=false;
                        }
                        else
                            break;
                    }
                    else
                    {
                        cout<<"Node #"<<currentNode+1<<" and Node #"<<basicSolutionSet[i]+1<<" with weight:"<<graph[currentNode][basicSolutionSet[i]]<<endl;
                        //found=true;
                        for(int t=0;t<basicSolutionSet.size();t++) cout<<basicSolutionSet[t]+1<<" ";
                        cout<<endl;
                        foundCounter++;
                        cout<<"Found Counter:"<<foundCounter<<endl;
                    }
                }

            }

            if(RCL.size()<1)
                break;
            else
                cout<<"RCL size is: "<<RCL.size()<<endl;


            //Select random node,if fails test delete it from the list, select another one
            cout<<"The node passed the connection test is Node# "<<currentNode+1<<endl;

            basicSolutionSet.push_back(currentNode);
            found=false;
            }
    }
    return basicSolutionSet;
}



int main()
{
    ifstream file("graphFromBook.txt");
    string word="",data="";
    getline(file,word);
    int node1,node2,weight,arrTemp[3];
    int numberOfNodes=atoi(word.c_str());
    int **graph=new int*[numberOfNodes];

    for(int i=0;i<numberOfNodes;i++)
        graph[i]=new int[numberOfNodes];

    for(int i=0;i<numberOfNodes;i++)
        for(int j=0;j<numberOfNodes;j++)
            graph[i][j]=0;

    while(file.good() && getline(file,word))
    {
           if(word.size()>0)
           {
               for(int i=0;i<3;i++)
               {
                   int cutFrom=word.find_first_of(' ');
                   arrTemp[i]=atoi(word.substr(0,cutFrom).c_str());
                   word=word.substr(cutFrom+1,word.length());
               }
               graph[arrTemp[0]-1][arrTemp[1]-1]=arrTemp[2];
               graph[arrTemp[1]-1][arrTemp[0]-1]=arrTemp[2];
           }
           else
                break;
    }

    vector<int>aCliqueFromGraph=aClique(graph,numberOfNodes);
    while(aCliqueFromGraph.size()<3){
        aCliqueFromGraph=aClique(graph,numberOfNodes);
    }
    cout<<endl;
    cout<<"###############################"<<endl;
    cout<<"Final solution set is:";
    printVector(aCliqueFromGraph);
    cout<<endl;
    cout<<"###############################"<<endl;

    delete []graph;
    return 0;
}
