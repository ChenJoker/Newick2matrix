#include<iostream>
#include<algorithm> 
#include<fstream> 
#include<string>
using namespace std;

/*
程式目的: 分析樹狀結構字串，將物種及其演化長度(edge length)存至各自的陣列
          並利用sort(由小到大) 以方便做累加並產生distance matrix 
          newick format example:
          	
*/

void analyze(string str);

int level_count=0;//計算物種層數 

class str_array{
      /*
        存取物種名稱、邊長，並記錄每個物種分別位於第幾層(由 '(' & ')' 做判斷) 
        遇到 '(' 則level做加一 
      */ 
      private:
            double edge_length; 
            double internal_length;
            char species[20];
            int level; 
      public:                      
	  
	  		 str_array()
			 {
			 	internal_length=0.0;
	  		 }  		 
      		 //取得物種名稱 
             void setspecies(char name[])
             {
                  for(int i=0;i<20;i++)
                  	species[i]=name[i];
             }
             
             //取得物種長度 
             void setlength(char *length)
             {
             	edge_length=atof(length);
             }
             
             //取得物種層數 
             void setlevel(int number)
             {
             	level=number;
             }
             
             //取得inernal length
			 void setinternal(char *length)
			 {
			 	internal_length=atof(length);
			 }
			 
             double getlength()
             {
             	return edge_length;
             }
             
             double getinternal()
             {
             	return internal_length;
             }
             
             int getlevel()
             {
             	return level;
             }
             void print()
             {
             	cout<<species<<"	"<<edge_length<<"	"<<level<<"	"<<internal_length<<endl;
             }
}; 

/*
配置class 陣列 可存最多500物種(可再增加) 
*/
str_array node[500];


 
int main()
{
    ifstream input("output.txt_result.txt");
    ofstream output("tree_output.txt");
    string str;
    
    //讀進樹狀結構字串 
    if(input==NULL)
    {
 	    cout<<"Fail to open file."<<endl;
    	return 0;
    }
    else
    {   //讀進一字串方便分析 
     	input>>str;
    }
    
    input.close();
        
    cout<<str<<endl;
    
    
    analyze(str);
    
    output.close();

    return 0;
}

/*
分析newick format 並存至陣列 
*/ 
void analyze(string str)
{
	char species[20];
    char edge_length[20];
	int species_number=0;//array index;
	bool flag=true;//判斷要存物種或是邊長 
	int str_index=0;//物種&邊長陣列之index 
	int i; 
    /*
    分析字串 
    */
    for(i=0;i<str.length();i++)
    {
    	//遇到'('則層數加一 
    	if(str[i]=='(')
    	{ 
    		level_count++;
    		str_index=0;
    		flag=true;
    	} 
    	//','表是前面為長度 
    	else if(str[i]==',')
    	{
    		edge_length[str_index]='\0';
    		//如果已有存值則不再存以免錯誤 
    		if(node[species_number-1].getlength()==0.0)
    			node[species_number-1].setlength(edge_length);
    		else 
    		{	
			//	edge_length[str_index]='\0';
    			for(int j=species_number;j>=0;j--)
				{				
					if(node[j].getlevel()==level_count+2 && node[j].getinternal()==0.0)
						node[j].setinternal(edge_length);
				}
    		}
    		str_index=0;
    		flag=true;
    	}
    	//')'則層數減一 並儲存邊長 
    	else if(str[i]==')')
    	{
    		edge_length[str_index]='\0';
    		//如果已有存值則不再存以免錯誤 
    		if(node[species_number-1].getlength()==0.0)
    			node[species_number-1].setlength(edge_length);
    		str_index=0;
    		flag=true;
    		level_count--;
    	}
    	// ':'且前面非')'表示為物種 
    	else if(str[i]==':' && str[i-1]!=')')
    	{
    		species[str_index]='\0';
    		node[species_number].setspecies(species);
    		node[species_number].setlevel(level_count);
    		species_number++;
    		str_index=0;
    		flag=false;	
    	}
    	//取的internal length
		else if((str[i]==':' || str[i]==';') && str[i-1]==')')
		{			
			//species[str_index]='\0';
			for(int j=species_number;j>=0;j--)
			{
				if(node[j].getlevel()==level_count+2 && node[j].getinternal()==0.0)
					node[j].setinternal(species);
			}
		} 
    	//存取物種或是長度字串 
    	else
    	{
    		if(flag)
    		{    			
    			species[str_index]=str[i];
    			str_index++;
    		}
    		else
			{			
    			edge_length[str_index]=str[i];
				str_index++;	
    		}
    	}   		
    }
    
    for(i=0;i<species_number;i++)
    	node[i].print();
}







