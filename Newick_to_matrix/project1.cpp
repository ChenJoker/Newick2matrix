#include<iostream>
#include<algorithm> 
#include<fstream> 
#include<string>
using namespace std;

/*
�{���ت�: ���R�𪬵��c�r��A�N���ؤΨ�t�ƪ���(edge length)�s�ܦU�۪��}�C
          �çQ��sort(�Ѥp��j) �H��K���֥[�ò���distance matrix 
          newick format example:
          	
*/

void analyze(string str);

int level_count=0;//�p�⪫�ؼh�� 

class str_array{
      /*
        �s�����ئW�١B����A�ðO���C�Ӫ��ؤ��O���ĴX�h(�� '(' & ')' ���P�_) 
        �J�� '(' �hlevel���[�@ 
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
      		 //���o���ئW�� 
             void setspecies(char name[])
             {
                  for(int i=0;i<20;i++)
                  	species[i]=name[i];
             }
             
             //���o���ت��� 
             void setlength(char *length)
             {
             	edge_length=atof(length);
             }
             
             //���o���ؼh�� 
             void setlevel(int number)
             {
             	level=number;
             }
             
             //���oinernal length
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
�t�mclass �}�C �i�s�̦h500����(�i�A�W�[) 
*/
str_array node[500];


 
int main()
{
    ifstream input("output.txt_result.txt");
    ofstream output("tree_output.txt");
    string str;
    
    //Ū�i�𪬵��c�r�� 
    if(input==NULL)
    {
 	    cout<<"Fail to open file."<<endl;
    	return 0;
    }
    else
    {   //Ū�i�@�r���K���R 
     	input>>str;
    }
    
    input.close();
        
    cout<<str<<endl;
    
    
    analyze(str);
    
    output.close();

    return 0;
}

/*
���Rnewick format �æs�ܰ}�C 
*/ 
void analyze(string str)
{
	char species[20];
    char edge_length[20];
	int species_number=0;//array index;
	bool flag=true;//�P�_�n�s���ةάO��� 
	int str_index=0;//����&����}�C��index 
	int i; 
    /*
    ���R�r�� 
    */
    for(i=0;i<str.length();i++)
    {
    	//�J��'('�h�h�ƥ[�@ 
    	if(str[i]=='(')
    	{ 
    		level_count++;
    		str_index=0;
    		flag=true;
    	} 
    	//','��O�e�������� 
    	else if(str[i]==',')
    	{
    		edge_length[str_index]='\0';
    		//�p�G�w���s�ȫh���A�s�H�K���~ 
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
    	//')'�h�h�ƴ�@ ���x�s��� 
    	else if(str[i]==')')
    	{
    		edge_length[str_index]='\0';
    		//�p�G�w���s�ȫh���A�s�H�K���~ 
    		if(node[species_number-1].getlength()==0.0)
    			node[species_number-1].setlength(edge_length);
    		str_index=0;
    		flag=true;
    		level_count--;
    	}
    	// ':'�B�e���D')'��ܬ����� 
    	else if(str[i]==':' && str[i-1]!=')')
    	{
    		species[str_index]='\0';
    		node[species_number].setspecies(species);
    		node[species_number].setlevel(level_count);
    		species_number++;
    		str_index=0;
    		flag=false;	
    	}
    	//����internal length
		else if((str[i]==':' || str[i]==';') && str[i-1]==')')
		{			
			//species[str_index]='\0';
			for(int j=species_number;j>=0;j--)
			{
				if(node[j].getlevel()==level_count+2 && node[j].getinternal()==0.0)
					node[j].setinternal(species);
			}
		} 
    	//�s�����ةάO���צr�� 
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







