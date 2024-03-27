#include <fcntl.h>
#include <unistd.h>

#include "textbuffer.h"

void edit(char* filename) {
	FILE *fp;	
	char c;
    char data[40];
	
    fp = fopen(filename, "r+");

    if (fp!=NULL) {
		int k=1;
	  	int i=0;
        
      	while ((fgets(data,41,fp))!=NULL)
      	{
			if (free_head==-1) {
				struct node new_node;
				strcpy(new_node.statement,data);
			    new_node.next = -1;
				textbuffer[0]=new_node;	
			}
			else {
			    if (free_head==1) {
			        //1 oneki node icin
			        struct node tmp_node;
			        tmp_node=textbuffer[0];
			        tmp_node.next=k;
			         
			        textbuffer[0]=tmp_node;
			        //yeni node icin
			        struct node new_node;
				    strcpy(new_node.statement, data);;
				    new_node.next=-1;
                    textbuffer[free_head]=new_node;
                    k++;              
			    }
			    else {
			        int index=free_head;
			        struct node new_node;
				    strcpy(new_node.statement, data);
				    new_node.next=-1;
                    textbuffer[free_head]=new_node;
                    
                    
                    struct node tmp_node;
                    tmp_node=textbuffer[--index];
                    tmp_node.next=k;
                    textbuffer[index--]=tmp_node;
			        k++;
			    }
			}
			i++;
			cursor_position=i;
			free_head=cursor_position;
			
			inuse_head=0;
        }
        fclose(fp);
        
		int ln = inuse_head;
		//int y=0;

		while (ln != -1 && ln < 25) {
			char str[40];
			strcpy(str, textbuffer[ln].statement);
			//str[strlen(str)-1] = '\0';
			printw("%s", str);
			//move(++y,x);
			refresh();
			ln = textbuffer[ln].next;
		}
    }
	else {
		endwin();
    	printf("File could not be opened!\n"); //if file is not opened
		exit(1);
	}
}

void insert(char* stat) {
	char ch = '\n';
	strncat(stat, &ch, 1);

	// if textbuffer is empty,
    if (free_head == -1) {
        int index=free_head;
        struct node new_node;
        strcpy(new_node.statement,stat);
		new_node.next =-1;
		textbuffer[++index]=new_node;
		free_head+=2;
    }
    
    else if ((free_head==1)&&(free_head==cursor_position)) {
        struct node tmp_node;
		tmp_node=textbuffer[0];
		tmp_node.next=free_head;
		textbuffer[0]=tmp_node;

		//yeni node icin
		struct node new_node;
		strcpy(new_node.statement, stat);;
		new_node.next=-1;
        textbuffer[free_head]=new_node;
        free_head++;
    }
    
    else if (free_head==0) {
        struct node new_node;
		strcpy(new_node.statement, stat);
		new_node.next=-1;
        textbuffer[free_head]=new_node;
		
		int index=cursor_position;
		struct node tmp_node;
		tmp_node=textbuffer[index-1];
		tmp_node.next=free_head;
	    textbuffer[index-1]=tmp_node;
	    
		free_head=cursor_position;
    }
    
    // if textbuffer is not empty,
    else {
        if (free_head==cursor_position) {//bosluk yoksa
            int index=free_head;
            struct node tmp_node;
		    tmp_node=textbuffer[index-1];
		    tmp_node.next=free_head;
	    	textbuffer[index-1]=tmp_node;
	    	
            struct node new_node;
			strcpy(new_node.statement, stat);
		    new_node.next=-1;
            textbuffer[free_head]=new_node;
			free_head++;
        }
        else {
			if (cursor_position == free_head-1) {
				int index=cursor_position;
                int next=cursor_position;
                struct node new_node;
		        strcpy(new_node.statement,stat);
		        new_node.next=-1;
                textbuffer[free_head]=new_node;
                
                struct node tmp_node;
			    tmp_node=textbuffer[index];
			    tmp_node.next=free_head;
			    textbuffer[index]=tmp_node;
			    free_head++;

				cursor_position++;
			}
            else if (cursor_position<free_head) {
                int index=cursor_position;
                int next=cursor_position;
                struct node new_node;
		        strcpy(new_node.statement,stat);
		        new_node.next=++next;
                textbuffer[free_head]=new_node;
                
                struct node tmp_node;
			    tmp_node=textbuffer[index];
			    tmp_node.next=free_head;
			    textbuffer[index]=tmp_node;
			    free_head++;

				count++;
            }
            else {
               int next=cursor_position;
               int index=cursor_position;
               struct node new_node;
		       strcpy(new_node.statement,stat);
		       new_node.next=-1;
               textbuffer[free_head]=new_node;
			   //en sondaki
			   struct node tmp_node;
			   tmp_node=textbuffer[index-1];
			   tmp_node.next=free_head;
			   textbuffer[index-1]=tmp_node;
			   free_head=next++;      
            }
        }
    }
    cursor_position++;
    inuse_head=0;

	//int y=0;
	clear();

	int ln = inuse_head;

	while (ln != -1 && ln < 25) {
		char str[40];
		strcpy(str, textbuffer[ln].statement);
		//str[strlen(str)-1] = '\0';
		printw("%s", str);
		//move(++y,x);
		refresh();
		ln = textbuffer[ln].next;
	}

	move(cursor_position,x);
}

void delete() {
	if (free_head == -1) {
    	printf("\nfree_head: %d\n", free_head);
    	printf("\n\nTEXTBUFFER BOŞ\n");
  	}
	else if (cursor_position <= free_head && count != 0) {
		int index = cursor_position-1;
		struct node tmp_node;
	    	tmp_node=textbuffer[index-count];
	    	tmp_node.next=-1;
	    	textbuffer[index-count]=tmp_node;
	    
	    	inuse_head=0;
	    	free_head=cursor_position;

			char* stat = "\0";
	 		strcpy(textbuffer[cursor_position].statement,stat);
	}
  	else {
	
		if (cursor_position==0) {
	    	struct node tmp_node;
	    	tmp_node=textbuffer[cursor_position];
	    	tmp_node.next=-1;
	    	textbuffer[cursor_position]=tmp_node;
	    
	    	inuse_head=1;
	    	free_head=0;
		}
		else if (cursor_position < free_head && cursor_position != 1) {
			int next;
    		struct node tmp_node;
    		int index=cursor_position;
			tmp_node=textbuffer[index];
			next=tmp_node.next;
	
			struct node tmp_node2;
			tmp_node2=textbuffer[index-1];
			tmp_node2.next=next++;
			textbuffer[index-1]=tmp_node2;
			free_head=cursor_position;

			struct node tmp_node3;
	    	tmp_node3=textbuffer[cursor_position];
	    	tmp_node3.next=-1;
	    	textbuffer[cursor_position]=tmp_node3;
		}
		// else if (cursor_position == 1) {
		// 	int next;
    	// 	struct node tmp_node;
    	// 	int index=cursor_position;
		// 	tmp_node=textbuffer[index];
		// 	next=tmp_node.next;
	
		// 	struct node tmp_node2;
		// 	tmp_node2=textbuffer[index-1];
		// 	tmp_node2.next=cursor_position+1;
		// 	textbuffer[index-1]=tmp_node2;
		// 	free_head=cursor_position;

		// 	// struct node tmp_node3;
	    // 	// tmp_node3=textbuffer[cursor_position];
	    // 	// tmp_node3.next=-1;
	    // 	// textbuffer[cursor_position]=tmp_node3;
		// }

		//if (cursor_position == 1) {
			char* stat = "\0";		
			strcpy(textbuffer[cursor_position].statement,stat);
		//}
  	}
	
	//int y=0;
	clear();

	int ln = inuse_head;

	while (ln != -1 && ln < 25) {
		char str[40];
		strcpy(str, textbuffer[ln].statement);
		//str[strlen(str)-1] = '\0';
		printw("%s", str);
		//move(++y,x);
		refresh();
		ln = textbuffer[ln].next;
	}

	move(cursor_position,x);
}

void save(char* filename) {
	FILE *fp;
	fp = fopen(filename, "w");

	int ln = inuse_head;

	while (ln != -1 && ln < 25) {
		fprintf(fp, "%s", textbuffer[ln].statement);
		ln = textbuffer[ln].next;
	}
	
	fclose(fp);
}