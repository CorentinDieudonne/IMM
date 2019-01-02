#define HEAD_INFO
#include "sfmt/SFMT.h"
using namespace std;
typedef double (*pf)(int,int); 
class Graph
{
    public:
        int numberOfNodes, numberOfEdges,sizeOfTheSeedSet;
        vector<int> inDeg;//number of dependencies
        vector<vector<int>> gT;//Transpose

        vector<vector<double>> probT;//propagation probability


        vector<bool> visit;
        vector<int> visit_mark;
        enum InfluModel {IC, LT};
        InfluModel influModel;
		string folder;
		string graph_file;
		vector<bool> hasnode;

        void setInfuModel(InfluModel p){
            influModel=p;
        }
        
        void readNM(){
            ifstream cin((folder+"attribute.txt").c_str());
            ASSERT(!cin == false);
            string s;
            while(cin >> s){
                if(s.substr(0,2)=="numberOfNodes="){
					numberOfNodes =atoi(s.substr(2).c_str());
                    continue;
                }
                if(s.substr(0,2)=="numberOfEdges="){
					numberOfEdges =atoi(s.substr(2).c_str());
                    continue;
                }
                ASSERT(false);
            }
            visit_mark=vector<int>(numberOfNodes);
            visit=vector<bool>(numberOfNodes);
            cin.close();
        }
        void add_edge(int numberOftheAddEdge, int numberOfTheOriginesEdges, double probabilite){
            probT[numberOfTheOriginesEdges].push_back(probabilite);// adding the propagation probability 
            gT[numberOfTheOriginesEdges].push_back(numberOftheAddEdge);// adding the number of the egdes
            inDeg[numberOfTheOriginesEdges]++;//increase the number of dependecies
        }
        
        void readGraph(){ //graph recovery
            FILE * fin= fopen((graph_file).c_str(), "r");
            ASSERT(fin != false);
            int readCnt=0;
            for(int i=0; i<m; i++){
                readCnt ++;
                int numberOftheAddEdge, numberOfTheOriginesEdges;
                double probabilite;
                int c=fscanf(fin, "%d%d%lf", &numberOftheAddEdge, &b, &probabilite);
                ASSERT(c==3);
                ASSERTT(c==3, numberOftheAddEdge, numberOfTheOriginesEdges, probabilite, c);
                
                ASSERT(numberOftheAddEdge<numberOfNodes);
                ASSERT(numberOfTheOriginesEdges<numberOfNodes);
                hasnode[numberOftheAddEdge]=true;
                hasnode[numberOfTheOriginesEdges]=true;
                add_edge(numberOftheAddEdge, numberOfTheOriginesEdges, probabilite);
            }
            if(readCnt != numberOfEdges)
                ExitMessage("numberOfEdges not equal to the number of edges in file "+graph_file);
            fclose(fin);
        }

        Graph(string folder, string graph_file):folder(folder), graph_file(graph_file){//constructor
																					   
            readNM();

            //init vector
            FOR(i, numberOfNodes){
                gT.push_back(vector<int>());
                hasnode.push_back(false);
                probT.push_back(vector<double>());
                //hyperGT.push_back(vector<int>());
                inDeg.push_back(0);
            }

            readGraph();
        }

};
double sqr(double t)
{
    return t*t;
}

#include "infgraph.h"
#include "timgraph.h"


