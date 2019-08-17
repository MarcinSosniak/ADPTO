#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>


#define TYPE_START '.'
#define TYPE_WALL '#'
#define TYPE_GEM '+'
#define TYPE_MINE '*'
#define TYPE_HOLE 'O'
#define TYPE_EMPTY ' '
#define TYPE_UNDEFINED '\0'



using namespace std;


int width = 0;
int height = 0;
int max_res_size = 0;



template <typename T>
class fast_que{
private:
    vector<T> v_out;
    vector<T> v_in;
    void move_elems()
    {
        while(v_in.size()>0)
        {
            v_out.push_back(v_in[v_in.size()-1]);
            v_in.pop_back();
        }
    }

public:

    fast_que(int max_items)
    {
        v_in.reserve(max_items);
        v_out.reserve(max_items);
    }

    void push(T elem)
    {
        v_in.push_back(elem);
    }

    T pop()
    {
        if(v_out.size()>0)
        {
            auto elem=(v_out[v_out.size()-1]);
            v_out.pop_back();
            return elem;
        }
        else
        {
            move_elems();
            auto elem=(v_out[v_out.size()-1]);
            v_out.pop_back();
            return elem;
        }
        throw string("fast_que, pop immposible location");
    }

    void clear_q()
    {
        v_out.clear();
        v_in.clear();
    }
    int size_q()
    {
        return v_out.size()+v_in.size();
    }
};





class Node;
class TwoDimArray;

class Step
{
public:
    Node* node;
    bool fEnd;
    Step() : node(nullptr),fEnd(false) {;}
};



class Node
{
public:
    bool fVisited;
	char type;
	Step moves[8];

	Node(char type_in) : fVisited(false) ,type(type_in) { ; }
	Node() : fVisited(false), type(TYPE_UNDEFINED) { ; }
};

int make_move(int h,int w, int move_nr,TwoDimArray&  tda)
{
    return 0;
}












class TwoDimArray // (wysokosc/szerokosc)
{
private:
	Node* node_array;
public:
	int _h;
	int _w;
	Node* first;
	int gem_counter;

	TwoDimArray(int h, int w) : _h(h), _w(w), first(nullptr),gem_counter(0)
	{
		node_array = new Node[w * h];
	}
	Node* operator[](int i)
	{
		return node_array + (i * _w);
	}
	void print_self()
	{
		for (int i = 0; i < _h; i++)
		{
			char line[_w];
			line[_w] = '\0';
			for (int k = 0; k < _w; k++)
				line[k] = (*(node_array + i * _w + k)).type;
			printf("%s\n", line);
		}
	}

	void find_el(Node& elem,int& x, int& y)
	{
        for(int i=0;i<_h;i++)
            for(int k=0;k<_w;k++)
                if (&((*this)[i][k])==&elem)
                {
                    x=i;
                    y=k;
                    return;
                }
        x=-1;
        y=-1;
	}

	void calcualte_connections()
	{
        for(int i=1;i<_h-1;i++)
        {
            for(int k=1;k<_w-1;k++)
            {
                int m=1;
                Node* cN=&((*this)[i][k]);
                if (cN->type==TYPE_WALL || cN->type==TYPE_MINE)
                    continue;
                //MOVE 0 TOP
                 if(cN->moves[0].node==nullptr)
                {
                    if ( (*this)[i-1][k].type==TYPE_WALL || (*this)[i-1][k].type==TYPE_MINE  )
                        {cN->moves[0].node=nullptr; cN->moves[0].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i-m][k].type || TYPE_GEM==(*this)[i-m][k].type || (*this)[i-m][k].type==TYPE_START )
                        {m++;}
                        if (TYPE_MINE !=(*this)[i-m][k].type)
                        {
                            if(TYPE_HOLE!=(*this)[i-m][k].type )
                                m--;
                            --m;
                            (*this)[i-m][k].moves[0].node=&((*this)[i-m-1][k]);
                            (*this)[i-m][k].moves[0].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i-m][k].moves[0].node=&((*this)[i-m-1][k]);
                                (*this)[i-m][k].moves[0].fEnd=false;
                                m--;
                            }
                        }
                    }
                }
                if(i==5 )
                {
                    printf("");
                }
                m=1;
                // MOVE 1 TOP RIGHT
                if(cN->moves[1].node==nullptr)
                {
                    if ((*this)[i-1][k+1].type==TYPE_WALL || (*this)[i-1][k+1].type==TYPE_MINE  )
                        {cN->moves[1].node=nullptr; cN->moves[1].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i-m][k+m].type || TYPE_GEM==(*this)[i-m][k+m].type || (*this)[i-m][k+m].type==TYPE_START)
                        {m++;}
                        if (TYPE_MINE !=(*this)[i-m][k+m].type)
                        {
                            if(TYPE_HOLE!=(*this)[i-m][k+m].type )
                                m--;
                            --m;
                            (*this)[i-m][k+m].moves[1].node=&((*this)[i-m-1][k+m+1]);
                            (*this)[i-m][k+m].moves[1].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i-m][k+m].moves[1].node=&((*this)[i-m-1][k+m+1]);
                                (*this)[i-m][k+m].moves[1].fEnd=false;
                                m--;
                            }
                        }
                    }
                }
                m=1;
                // MOVE 2 RIGHT
                if(cN->moves[2].node==nullptr)
                {
                    if ((*this)[i][k+1].type==TYPE_WALL || (*this)[i][k+1].type==TYPE_MINE )
                        {cN->moves[2].node=nullptr; cN->moves[2].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i][k+m].type || TYPE_GEM==(*this)[i][k+m].type || (*this)[i][k+m].type==TYPE_START  )
                        {m++;}
                        if (TYPE_MINE !=(*this)[i][k+m].type)
                        {
                            if(TYPE_HOLE!=(*this)[i][k+m].type )
                                m--;
                            --m;
                            (*this)[i][k+m].moves[2].node=&((*this)[i][k+m+1]);
                            (*this)[i][k+m].moves[2].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i][k+m].moves[2].node=&((*this)[i][k+m+1]);
                                (*this)[i][k+m].moves[2].fEnd=false;
                                m--;
                            }
                        }
                    }
                }
                m=1;
                // MOVE 3 DOWN RIGHT
                if(cN->moves[3].node==nullptr)
                {
                    if ((*this)[i+1][k+1].type==TYPE_WALL || (*this)[i+1][k+1].type==TYPE_MINE )
                        {cN->moves[3].node=nullptr; cN->moves[3].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i+m][k+m].type || TYPE_GEM==(*this)[i+m][k+m].type || (*this)[i+m][k+m].type==TYPE_START )
                        {m++;}
                        if (TYPE_MINE !=(*this)[i+m][k+m].type)
                        {
                            if(TYPE_HOLE!=(*this)[i+m][k+m].type )
                                m--;
                            --m;
                            (*this)[i+m][k+m].moves[3].node=&((*this)[i+m+1][k+m+1]);
                            (*this)[i+m][k+m].moves[3].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i+m][k+m].moves[3].node=&((*this)[i+m+1][k+m+1]);
                                (*this)[i+m][k+m].moves[3].fEnd=false;
                                m--;
                            }
                        }
                    }
                }
                m=1;
                // MOVE 4 DOWN
                if(cN->moves[4].node==nullptr)
                {
                    if ((*this)[i+1][k].type==TYPE_WALL || (*this)[i+1][k].type==TYPE_MINE)
                        {cN->moves[4].node=nullptr; cN->moves[4].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i+m][k].type || TYPE_GEM==(*this)[i+m][k].type || (*this)[i+m][k].type==TYPE_START )
                        {m++;}
                        if (TYPE_MINE !=(*this)[i+m][k].type)
                        {
                            if(TYPE_HOLE!=(*this)[i+m][k].type )
                                m--;
                            --m;
                            (*this)[i+m][k].moves[4].node=&((*this)[i+m+1][k]);
                            (*this)[i+m][k].moves[4].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i+m][k].moves[4].node=&((*this)[i+m+1][k]);
                                (*this)[i+m][k].moves[4].fEnd=false;
                                m--;
                            }
                        }
                    }
                }
                m=1;
                // MOVE 5 DOWN LEFT
                if(cN->moves[5].node==nullptr)
                {
                    if ((*this)[i+1][k-1].type==TYPE_WALL || (*this)[i+1][k-1].type==TYPE_MINE  )
                        {cN->moves[5].node=nullptr; cN->moves[5].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i+m][k-m].type || TYPE_GEM==(*this)[i+m][k-m].type || (*this)[i+m][k-m].type==TYPE_START)
                        {m++;}
                        if (TYPE_MINE !=(*this)[i+m][k-m].type)
                        {
                            if(TYPE_HOLE!=(*this)[i+m][k-m].type )
                                m--;
                            --m;
                            (*this)[i+m][k-m].moves[5].node=&((*this)[i+m+1][k-m-1]);
                            (*this)[i+m][k-m].moves[5].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i+m][k-m].moves[5].node=&((*this)[i+m+1][k-m-1]);
                                (*this)[i+m][k-m].moves[5].fEnd=false;
                                m--;
                            }
                        }
                    }
                }
                m=1;
                // MOVE 6  LEFT
                if(cN->moves[6].node==nullptr)
                {
                    if ((*this)[i][k-1].type==TYPE_WALL || (*this)[i][k-1].type==TYPE_MINE  )
                        {cN->moves[6].node=nullptr; cN->moves[6].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i][k-m].type || TYPE_GEM==(*this)[i][k-m].type || (*this)[i][k-m].type==TYPE_START)
                        {m++;}
                        if (TYPE_MINE !=(*this)[i][k-m].type)
                        {
                            if(TYPE_HOLE!=(*this)[i][k-m].type )
                                m--;
                            --m;
                            (*this)[i][k-m].moves[6].node=&((*this)[i][k-m-1]);
                            (*this)[i][k-m].moves[6].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i][k-m].moves[6].node=&((*this)[i][k-m-1]);
                                (*this)[i][k-m].moves[6].fEnd=false;
                                m--;
                            }
                        }
                    }
                }

                m=1;
                // MOVE 7  LEFT Up
                if(cN->moves[7].node==nullptr)
                {
                    if ((*this)[i-1][k-1].type==TYPE_WALL || (*this)[i-1][k-1].type==TYPE_MINE  )
                        {cN->moves[7].node=nullptr; cN->moves[7].fEnd=true;}
                    else
                    {
                        while(TYPE_EMPTY==(*this)[i-m][k-m].type || TYPE_GEM==(*this)[i-m][k-m].type || (*this)[i-m][k-m].type==TYPE_START)
                        {m++;}
                        if (TYPE_MINE !=(*this)[i-m][k-m].type)
                        {
                            if(TYPE_HOLE!=(*this)[i-m][k-m].type )
                                m--;
                            --m;
                            (*this)[i-m][k-m].moves[7].node=&((*this)[i-m-1][k-m-1]);
                            (*this)[i-m][k-m].moves[7].fEnd=true;
                            --m;
                            while(m>=0)
                            {
                                (*this)[i-m][k-m].moves[7].node=&((*this)[i-m-1][k-m-1]);
                                (*this)[i-m][k-m].moves[7].fEnd=false;
                                m--;
                            }
                        }
                    }
                }
                //TODO rest

            }
        }
	}
	void print_connections()
    {
        for(int n=0;n<_w*_h;n++)
        {
            Node* cN=&node_array[n];
            for (int i=0;i<8;i++)
            {
                int my_x=-1;
                int my_y=-1;
                int t_x=-1;
                int t_y=-1;
                find_el(*cN,my_x,my_y);
                if (cN->moves[i].node!= nullptr)
                {
                    find_el(*(cN->moves[i].node),t_x,t_y);
                    printf("(%d,%d)-> (%d,%d) fEnd=%d\n",my_x,my_y,t_x,t_y,cN->moves[i].fEnd);
                }
            }
        }
    }
    void print_connections(int i)
    {
        for(int n=0;n<_w*_h;n++)
        {
            Node* cN=&node_array[n];
            int my_x=-1;
            int my_y=-1;
            int t_x=-1;
            int t_y=-1;
            find_el(*cN,my_x,my_y);
            if (cN->moves[i].node!= nullptr)
            {
                find_el(*(cN->moves[i].node),t_x,t_y);
                printf("(%d,%d)-> (%d,%d) fEnd=%d\n",my_x,my_y,t_x,t_y,cN->moves[i].fEnd);
            }
        }
    }
    void print_all()
    {
        for(int i=1;i<_h-1;i++)
        {
            for(int k=1;k<_w-1;k++)
            {
                Node* node=&((*this)[i][k]);
                printf("(%d,%d): \'%c\' [(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d)]\n",i,k,node->type
                       ,node->moves[0].node,node->moves[0].fEnd
                       ,node->moves[1].node,node->moves[1].fEnd
                       ,node->moves[2].node,node->moves[2].fEnd
                       ,node->moves[3].node,node->moves[3].fEnd
                       ,node->moves[4].node,node->moves[4].fEnd
                       ,node->moves[5].node,node->moves[5].fEnd
                       ,node->moves[6].node,node->moves[6].fEnd
                       ,node->moves[7].node,node->moves[7].fEnd);
            }
        }
    }
    void clear_visited()
    {
        for (int i=0;i<_w*_h;i++)
        {
            (*(node_array+i)).fVisited=false;
        }
    }
    ~TwoDimArray()
    {
        delete node_array;
    }
};


void build_matrix_from_stdin(TwoDimArray& m)
{
    int h=m._h;
    int w=m._w;
    string line;
    for(int i=0;i<h;i++)
    {
        getline(cin,line);
        //cout<<string("//")<<line;
        for(int k=0;k<w;k++)
        {
            m[i][k].type=line[k];
            if (line[k]==TYPE_START)
                m.first=&m[i][k];
            else if (line[k]==TYPE_GEM)
            {
                m.gem_counter++;
            }
        }
    }
    m.print_self();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////STRATEGIES//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//   _____ _             _
//   / ____| |           | |
//  | (___ | |_ _ __ __ _| |_ ___  __ _ _   _
//   \___ \| __| '__/ _` | __/ _ \/ _` | | | |
//   ____) | |_| | | (_| | ||  __/ (_| | |_| |
//  |_____/ \__|_|  \__,_|\__\___|\__, |\__, |
//                                 __/ | __/ |
//                                |___/ |___/



pair<string,Node*> dummy_dfs_move(TwoDimArray& tda,Node* cn, string old);
pair<int, Node*> make_move_counting_gems(Node* cn,TwoDimArray &tda,int move_nr);
pair<string,Node*> dummy_dfs_move_single(TwoDimArray& tda,Node* cn, string old, int nr);



pair<int, Node*> make_move_counting_gems(Node* cn,TwoDimArray& tda,int move_nr)
{
    int out=0;
    if(cn->moves[move_nr].node != nullptr)
    {
        Node* tn=cn;
        while(!tn->moves[move_nr].fEnd)
        {
            if (TYPE_GEM==tn->type)
            {
                tda.gem_counter--;
                tn->type=TYPE_EMPTY;
                out++;
            }
            tn->fVisited=true;
            tn=tn->moves[move_nr].node;
        }
        if(TYPE_GEM==tn->type)
        {
            tda.gem_counter--;
            tn->type=TYPE_EMPTY;
            out++;
        }
        tn->fVisited=true;

        tn=tn->moves[move_nr].node;

        if(TYPE_GEM==tn->type)
        {
            tda.gem_counter--;
            tn->type=TYPE_EMPTY;
            out++;
        }
        //tn->fVisited=true;


        pair<int,Node*> outp(out,tn);
        return outp;
    }
    pair<int,Node*> outp(-1,nullptr);
    return outp;
}



// --------------------------------------------DUMMY DFS------------------------------------------------------------------------------------------------------

pair<string,Node*> dummy_dfs_move_single(TwoDimArray& tda,Node* cn, string old, int nr)
{
    auto ret= make_move_counting_gems(cn,tda,nr);
    if (ret.first>0)
    {
        string out=old + to_string(nr);
        pair<string,Node*> out_p= make_pair(out,ret.second);
        return out_p;
    }
    else if(ret.second !=nullptr)
    {
        auto ret0_2= dummy_dfs_move(tda,ret.second,old + to_string(nr));
        if (ret0_2.first != string(""))
            return ret0_2;
    }
    return make_pair(string(""),nullptr);
}


pair<string,Node*> dummy_dfs_move(TwoDimArray& tda,Node* cn, string old)
{
    if(cn==nullptr || cn==0)
        throw string("cn is nullptr where it shouldn;t");
    if(true==cn->fVisited)
    {
        return make_pair(string(""),nullptr);
    }



    pair <string,Node*> p;
    for(int i=0;i< 8;i++)
    {
        p=dummy_dfs_move_single(tda,cn,old,i);
        if(p.first!=string(""))
        {
            return p;
        }
    }
    return make_pair(string(""),nullptr);
}



string strategy_dummy_dfs(TwoDimArray& tda)
{
    string out=string("");
    Node* cn=tda.first;
    while(tda.gem_counter>0)
    {
        if(cn==nullptr || cn==0)
            throw string(" hue1");
        auto single_move=dummy_dfs_move(tda,cn,string(""));
        cn=single_move.second;
        out+=single_move.first;
        tda.clear_visited();
        int x,y;
        tda.find_el(*cn,x,y);
        printf("%s(%d,%d)\n",single_move.first.c_str(),x,y);
    }
    return out;
}

class BFS_no_solution_exception
{

};


pair<string,Node*> bfs_step(TwoDimArray& tda,fast_que<pair<string,Node*>>& q,Node * cn)
{
    tda.clear_visited();
    q.clear_q();
    q.push(make_pair(string(""),cn)); // push first elem
    while(q.size_q()>0)
    {
        auto curr=q.pop();
        for(int i=0;i<8;i++)
        {
            if(curr.second->moves[i].node != nullptr)
            {
                auto res= make_move_counting_gems(curr.second,tda,i);
                if(res.first>0)
                    return make_pair(curr.first + to_string(i),res.second);
                else if(res.second !=nullptr)
                    q.push(make_pair(curr.first + to_string(i),res.second));
            }
        }
    }
    throw  BFS_no_solution_exception();
}



string strategy_dummy_bfs(TwoDimArray& tda)
{
    Node * cn=tda.first;
    fast_que<pair<string,Node*>> q(tda._h*tda._w*8);
    string out=string("");
    try
    {
        while(tda.gem_counter>0)
        {
            auto res=bfs_step(tda,q,cn);
            out+=res.first;
            cn=res.second;
        }
    }
    catch (BFS_no_solution_exception ex)
    {
        return string("BRAK");
    }
    return out;
}










int actual_main()
{
        string sLineBuff;
	//char* sLineBuff;
    const char* sHeight = sLineBuff.c_str();
	char* sWidth;
	getline(cin, sLineBuff);
	//sLineBuff=line.to_c_str
	//scanf("%[^\n]", sLineBuff);

	for (int i = 0; true; i++)
	{
		if (sLineBuff[i] == '\0')
		{

			throw string("Invalid input on line 1");
			exit(-1);
		}
		if (sLineBuff[i] == ' ')
		{
			sLineBuff[i] = '\0';
			sWidth = &sLineBuff[i+1];
			break;
		}
	}
	height = atoi(sHeight);
	width = atoi(sWidth);
	getline(cin, sLineBuff);
	//scanf("%s", sLineBuff);
	max_res_size = atoi(sLineBuff.c_str());
	//printf("height=%d, width=%d, max_res_size=%d", height, width,max_res_size);
	TwoDimArray m(height,width);
    build_matrix_from_stdin(m);
    m.calcualte_connections();
    m.print_connections(1);

    for(int i=0;i<height;i++)
    {
        for(int k=0;k<width;k++)
        {
            printf("(%d,%d)%c",i,k,m[i][k].type);
        }
        printf("\n");
    }
    printf("\n\n   ");
    //m.print_all();
    printf("\n 0123456789\n");
    for(int i=0;i<height;i++)
    {
        printf("%d",i);
        for(int k=0;k<width;k++)
        {
            printf("%c",m[i][k].type);
        }
        printf("\n");
    }
    //cout<<strategy_dummy_dfs(m);
    cout<<strategy_dummy_bfs(m);
    while(true)
    {
        int x;
        int y;
        printf("give x:\n");
        cin>>x;
        printf("give y:\n");
        cin>>y;
        printf("%c\n",m[x][y].type);
    }

    string hue;
    cin>>hue;
	return 0;
}







int main()
{
    try
    {
        actual_main();
    }
    catch (int i)
    {
        ;
    }
    catch (string x)
    {
        cout<<"!!!!!!! EXCEPTION\n\n";
        cout<<x;
    }

}
