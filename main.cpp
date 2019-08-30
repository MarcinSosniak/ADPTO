#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdexcept>
#include <sstream>


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


string get_str_from_int_0_to_7(int in)
{
    switch(in)
    {
        case 0: return "0";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
    }
    throw string("logic error");
}



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
	bool _f_init=false;

	TwoDimArray(int h, int w) : _h(h), _w(w), first(nullptr),gem_counter(0)
	{
		node_array = new Node[w * h];
	}

    TwoDimArray(TwoDimArray& other) = delete;

    TwoDimArray(TwoDimArray&& other) :node_array(other.node_array), _h(other._h), _w(other._w),
                    first(other.first), gem_counter(other.gem_counter), _f_init(other._f_init) {}

    TwoDimArray& operator=(TwoDimArray& other) = delete;

    TwoDimArray& operator=(TwoDimArray&& other)
    {
        node_array=other.node_array;
        _h=other._h;
        _w=other._w;
        first=other.first;
        gem_counter=other.gem_counter;
        _f_init=false;
        return *this;
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
	    gem_counter=0;
	    _f_init=true;
        for(int i=1;i<_h-1;i++)
        {
            for(int k=1;k<_w-1;k++)
            {
                int m=1;
                Node* cN=&((*this)[i][k]);
                if (cN->type==TYPE_WALL || cN->type==TYPE_MINE)
                    continue;

                if (cN->type==TYPE_GEM)
                    gem_counter++;
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
        if(!_f_init) throw logic_error("usage of uninitalised matrix");
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
        if(!_f_init) throw logic_error("usage of uninitalised matrix");
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
        if(!_f_init) throw logic_error("usage of uninitalised matrix");
        for(int i=1;i<_h-1;i++)
        {
            for(int k=1;k<_w-1;k++)
            {
                Node* node=&((*this)[i][k]);
                printf("(%d,%d) [%d]: \'%c\' [(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d),(%d,fEnd=%d)]\n",i,k,node,node->type
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

    TwoDimArray clone_with_wrong_connections()
    {
        TwoDimArray outArr(_h,_w);
        for(int i=0;i<_h*_w;i++)
        {
            if(this->node_array[i].type==TYPE_START)
                outArr.first=&(outArr.node_array[i]);
            outArr.node_array[i].type=this->node_array[i].type;
        }
        outArr.gem_counter= -1;
        return outArr;
    }

    TwoDimArray* create_clone_with_wrong_connections()
    {
        TwoDimArray* outArr= new TwoDimArray(_h,_w);
        for(int i=0;i<_h*_w;i++)
        {
            if(this->node_array[i].type==TYPE_START)
                outArr->first=&(outArr->node_array[i]);
            outArr->node_array[i].type=this->node_array[i].type;
        }
        outArr->gem_counter= -1;
        return outArr;
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
    //m.print_self();
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
            //tn->fVisited=true;
            tn=tn->moves[move_nr].node;
        }
        if(TYPE_GEM==tn->type)
        {
            tda.gem_counter--;
            tn->type=TYPE_EMPTY;
            out++;
        }
        //tn->fVisited=true;

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
        if(curr.second->fVisited) continue;
        curr.second->fVisited=true;
        for(int i=0;i<8;i++)
        {
            if(curr.second->moves[i].node != nullptr)
            {
                auto res= make_move_counting_gems(curr.second,tda,i);
                if(res.first>0)
                    return make_pair(curr.first + get_str_from_int_0_to_7(i),res.second);
                else if(res.second !=nullptr)
                    q.push(make_pair(curr.first + get_str_from_int_0_to_7(i),res.second));
            }
        }
    }
    throw  cn;
    throw BFS_no_solution_exception();
}



void strategy_dummy_bfs_fill_with_tmp_mines(TwoDimArray& arr,std::vector<std::pair<std::pair<int,int>,char>> temporary_mines)
{
    for(auto& tmp_mine : temporary_mines)
    {
        arr[tmp_mine.first.first][tmp_mine.first.second].type=TYPE_MINE;
    }
}

void strategy_dummy_bfs_remove_tmp_mines(TwoDimArray& arr,std::vector<std::pair<std::pair<int,int>,char>> temporary_mines)
{
    for(auto& tmp_mine : temporary_mines)
    {
        arr[tmp_mine.first.first][tmp_mine.first.second].type=tmp_mine.second;
    }
}

void strategy_dummy_bfs(TwoDimArray& tda)
{
    Node * cn=tda.first;
    fast_que<pair<string,Node*>> q(0);
    stringstream out;
    TwoDimArray tdaCpy=TwoDimArray(0,0);
    std::vector<std::pair<std::pair<int,int>,char>> temporary_mines;
    while(true)
    {
        try
        {
            tdaCpy= tda.clone_with_wrong_connections();
            strategy_dummy_bfs_fill_with_tmp_mines(tdaCpy,temporary_mines);
            tdaCpy.calcualte_connections();

            cn=tdaCpy.first;
            q.clear_q();
            while(tdaCpy.gem_counter>0) // if there is a simple solution there will be no throw
            {
                auto res=bfs_step(tdaCpy,q,cn);
                out<<res.first;
                cn=res.second;
            }
            if(temporary_mines.size()==0)
            {
                cout<<out.str()<<"\n";
                return;
                // FOR  SOME FUUUCKING REASON return and cout caused crash
            }
            strategy_dummy_bfs_remove_tmp_mines(tdaCpy,temporary_mines);
            tdaCpy.calcualte_connections();
            try{
                while(tdaCpy.gem_counter>0) // if there is a simple solution there will be no throw
                {
                    auto res=bfs_step(tdaCpy,q,cn);
                    out<<res.first;
                    cn=res.second;
                }
            }
            catch (Node *)
            {
                cout<<"BRAK\n";
                return;
            }
            cout<<out.str()<<"\n";
            return;


        }
        catch (BFS_no_solution_exception ex)
        {
            cout<<"BRAK\n";
            return;
        }
        catch(Node * thrown_last_start_node)
        {
            int x,y;
            tdaCpy.find_el(*thrown_last_start_node,x,y);
            temporary_mines.push_back(make_pair(make_pair(x,y),thrown_last_start_node->type));
        }
    }
    cout<<"BRAK\n";
    return;
}




int actual_main()
{
    string sLineBuff;
	//char* sLineBuff;
	char* sWidth;
	getline(cin, sLineBuff);
	const char* sHeight = sLineBuff.c_str();
	//sLineBuff=line.to_c_str
	//scanf("%[^\n]", sLineBuff);

	for (int i = 0; true; i++)
	{
		if (sLineBuff[i] == '\0')
		{

			throw string("Invalid input on line 1");
			return 0;
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
    //m.print_connections(1);
    //m.print_all();
    /*
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
    */
    //cout<<strategy_dummy_dfs(m);
    //cout<<strategy_dummy_bfs(m).str()<<"\n";
    //printf("%s\n",strategy_dummy_bfs(m).c_str());
    strategy_dummy_bfs(m);
    /*while(true)
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
	*/return 0;
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
