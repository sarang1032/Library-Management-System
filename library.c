// Library Management System
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
typedef struct issue{
    char issuedate[15];         //book issue date
    char issuetime[15];         //book issue time
}issue;
typedef struct library{
    char name[50];
    char date[50];   //date of purchased
    char time[50];   //time of purchased
    double price;
    issue info;
}lib;
FILE *bookfile;
FILE *issuefile;
// To add a book to the library
void addbook(){
    system("cls");
    printf("---------------------------------\n");
    printf("--Add a new Book to the Library--\n");
    printf("---------------------------------\n\n");
    lib l;
    // bookfile=fopen("Books.dat","a+");
    // fclose(bookfile);
    printf("Enter the name: ");
    fgets(l.name,50,stdin);
    l.name[strlen(l.name)-1]=0;
    printf("Enter the price: ");
    scanf("%lf",&l.price);
    fgetc(stdin);
    strcpy(l.date,__DATE__);
    strcpy(l.time,__TIME__);
    strcpy(l.info.issuedate,"0");
    strcpy(l.info.issuetime,"0");
    printf("%s\n%s\n",l.date,l.time);
    fwrite(&l,sizeof(lib),1,bookfile);
    lib lread;
    int c=0;
    FILE *fptr;
    fptr=fopen("temp.dat","a+");
    bookfile=fopen("books.dat","r");
    if (NULL != bookfile) {
        fseek (bookfile, 0, SEEK_END);
        int size = ftell(bookfile);
        if (0 == size) {
            fwrite(&l,sizeof(lib),1,fptr);
            c=1;
            }
        }
    fclose(bookfile);
    if(c==0){
    bookfile=fopen("books.dat","r");
    while (fread(&lread,sizeof(lib),1,bookfile)){
            if (!(strcmp(lread.name,l.name)<=0) && c==0){ 
                fwrite(&l,sizeof(lib),1,fptr);
                c++;
                // printf("new\t");
                fwrite(&lread,sizeof(lib),1,fptr);
            }
            else{
                fwrite(&lread,sizeof(lib),1,fptr);
                // printf("old\t");
            }
        }
        fclose(bookfile);
    }
        if(c==0)
            fwrite(&l,sizeof(lib),1,fptr);
        fclose(fptr);
        remove("books.dat");  		// remove the original file 
        rename("temp.dat","books.dat");
    if(!fwrite==0){
        printf("\n<<<<<<<<<<<<<<>>>>>>>>>>>>>>>\n");
        printf("<---Insertion successfull--->\n");
        printf("<<<<<<<<<<<<<<>>>>>>>>>>>>>>>\n\n");
    }
    else{
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf("!=-=-=-=Error occured-=-=-=-!\n");
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
    }
}
//To delete a book from the library
void deletebook(){
    system("cls");
    printf("----------------------------------\n");
    printf("--Delete a Book from the Library--\n");
    printf("----------------------------------\n\n");
        FILE *fptr2;
        lib lread;
        int c=0;
		char fname[50];
		printf("Enter the name of the book: ");
		fgets(fname,50,stdin);
        fname[strlen(fname)-1]=0;
        bookfile = fopen("books.dat", "r");
        fptr2=fopen("temp.dat","w");
        //Searching
        while (fread(&lread,sizeof(lib),1,bookfile)){
            if (!strcmp(fname,lread.name)==0||c!=0) 
                fwrite(&lread,sizeof(lib),1,fptr2);
            else
                c++;
        }
        fclose(bookfile);
        fclose(fptr2);
        remove("books.dat");  		// remove the original file 
        rename("temp.dat","books.dat"); 	// rename the temporary file to original name
    if(c!=0){
        printf("\n******************************************\n");
        printf("*---------Deleted Successfully-----------*\n");
        printf("******************************************\n\n");
    }
    else{
        printf("\n.............................\n");
        printf(":       Book not found      :\n");
        printf(".............................\n\n");
    }
}
// To search the books of same name into the issue book file
int searchbook(char fname[50]){
    int count=0;
    lib lread;
    issuefile=fopen("Book_Issue.dat","r");
    while (fread(&lread,sizeof(lib),1,issuefile))
            if (strcmp(fname,lread.name)==0) 
                count++;
    fclose(issuefile);
    return count;
}
//To issue a book
void issuebook(){
    system("cls");
    printf("---------------------------------\n");
    printf("----------Issue a Book-----------\n");
    printf("---------------------------------\n\n");
    char fname[50];
    lib lread;
    int c=0,p=0;
    printf("Enter the name of the book to be issued: ");
    fgets(fname,50,stdin);
    fname[strlen(fname)-1]=0;
    bookfile=fopen("Books.dat","r");
    if (NULL != bookfile) {
        fseek (bookfile, 0, SEEK_END);
        int size = ftell(bookfile);
            if (0 == size) {
                printf("----------Out of Stock----------\n");
                return;
            }
        }
    fclose(bookfile);
    int count=searchbook(fname);
    bookfile=fopen("Books.dat","r");
    issuefile=fopen("Book_Issue.dat","a+");
    while(fread(&lread,sizeof(lib),1,bookfile)){
        // printf("Name of the book: %s\nPrice of the book: Rs.%.2lf\nDate of purchase: %s\n\n",lread.name,lread.price,lread.date);
        if(strcmp(lread.name,fname)==0 ){
            if(p<count){
                p++;
                continue;
            }
            strcpy(lread.info.issuedate,__DATE__);
            strcpy(lread.info.issuetime,__TIME__);
            fwrite(&lread,sizeof(lib),1,issuefile);
            c=1;
            break;
        }
    }
    // printf("%d\n%d\n%d\n",p,count,c);
    if(!fwrite==0 && c==1){
        printf("\n**************************************************************\n");
        printf("*------------------Issued successfully-----------------------*\n");
        printf("**************************************************************\n\n");
    }
    else if(p==count){
        printf("\n**************************************************************\n");
        printf("*-=-=-=-=-=-=Book Already Issued or not available-=-=-=-=-=-=*\n");
        printf("**************************************************************\n\n");
    }
    else
        printf("\n-=-=-=-=-=-=Error-=-=-=-=-=-=\n\n");
    fclose(issuefile);
    fclose(bookfile);
}
//To return or delete the issue book
void returnbook(){
    system("cls");
    printf("---------------------------------\n");
    printf("----------Return a Book----------\n");
    printf("---------------------------------\n\n");
    FILE *fptr2;
    lib lread;
    int c=0;
	char fname[50];
	printf("Enter the name of the book: ");
	fgets(fname,50,stdin);
    fname[strlen(fname)-1]=0;
    bookfile = fopen("Book_Issue.dat", "r");
    if (!bookfile) 
	{
        printf(" File not found or unable to open the input file!!\n");
        fclose(bookfile);
        return;
    }
    fptr2 = fopen("temp.dat","w"); 
    if (!fptr2) 
	{
        printf("Unable to open a temporary file to write!!\n");
        fclose(bookfile);
        return;
    }
    while (fread(&lread,sizeof(lib),1,bookfile)){
        if (!strcmp(fname,lread.name)==0 || c!=0)
                fwrite(&lread,sizeof(lib),1,fptr2);
        else
            c++;
    }
    fclose(bookfile);
    fclose(fptr2);
    remove("Book_Issue.dat"); 
    rename("temp.dat","Book_Issue.dat");
    if(c!=0){
        printf("\n***********************************\n");
        printf("*----------Book Recieved----------*\n");
        printf("***********************************\n\n");
    }
    else{
        printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        printf("!     Book not issued     !\n");
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
        fclose(bookfile);
        fclose(fptr2);
}
//To view the books
void viewbooks(){
    int n;
    lib lread;
    bookfile=fopen("books.dat","r");
    issuefile=fopen("Book_Issue.dat","r");
    system("cls");
    printf("Choose from the following:\n1. Issued Books\n2. All Books\n");
    // 2. Recieved Books\n
    scanf("%d",&n);
    fgetc(stdin);
    switch(n){
        case 1:
            system("cls");
            if (NULL != issuefile) {
                fseek (issuefile, 0, SEEK_END);
                int size = ftell(issuefile);
                if (0 == size) {
                    printf("\n||||||||||||||||||||||||||||||||||\n");
                    printf("|---------No book issued---------|\n");
                    printf("||||||||||||||||||||||||||||||||||\n\n");
                    break;
                    }
                }
            fclose(issuefile);
            issuefile=fopen("Book_Issue.dat","r");
            printf("\n                Issued Books              \n");
            printf("------------------------------------------\n");
            while(fread(&lread,sizeof(lib),1,issuefile)){
            printf("\n------------------------------------------\n");
            printf("Name of the book: %s\nPrice of the book: Rs.%.2lf\nIssued Date: %s\nIssued Time: %s\n",lread.name,lread.price,lread.info.issuedate,lread.info.issuetime);
            printf("------------------------------------------\n\n");
            }
            break;
        case 2:
            system("cls");
            if (NULL != bookfile) {
                fseek (bookfile, 0, SEEK_END);
                int size = ftell(bookfile);
                if (0 == size) {
                    printf("\n||||||||||||||||||||||||||||||||||\n");
                    printf("|---------No book found---------|\n");
                    printf("||||||||||||||||||||||||||||||||||\n\n");
                    break;
                    }
                }
            fclose(bookfile);
            bookfile=fopen("books.dat","r");
            printf("\n                 All Books                \n");
            printf("------------------------------------------\n");
            while(fread(&lread,sizeof(lib),1,bookfile)){
            printf("\n------------------------------------------\n");
            printf("Name of the book: %s\nPrice of the book: Rs.%.2lf\nDate of purchase: %s\n",lread.name,lread.price,lread.date);
            printf("------------------------------------------\n\n");
            }
            break;
        default:
           printf("Invalid Option\n");
           break;
    }
    fclose(bookfile);
    fclose(issuefile);
}
void main(){
    char cons='y';
    while(cons=='y'){
    system("cls");
    printf("********************Welcome to the Library********************\n");
    printf("Choose your option\n1. Add Book\n2. Remove Book\n3. Issue Book\n4. Return Book\n5. View Issued Book Record\n6. Exit\n");
    int n;
    scanf("%d",&n);
    fgetc(stdin);
    printf("\n");
    switch(n){
        case 1:
        addbook();
        break;
        case 2:
        deletebook();
        break;
        case 3:
        issuebook();
        break;
        case 4:
        returnbook();
        break;
        case 5:
        viewbooks();
        break;
        case 6:
        printf("** * * * * * * * * * * * * * *\n");
        printf("* =   =   =   =   =   =   =  *\n");
        printf("*********Bye Bye :)***********\n");
        printf("* =   =   =   =   =   =   =  *\n");
        printf("** * * * * * * * * * * * * * *\n\n");
        
        exit(0);
        default:
        printf("Invalid choice\n");
        break;
    }
    printf("\nWant to continue(y/n): ");
    scanf("%c",&cons);
    fgetc(stdin);
    }
    printf("*********Bye Bye :)***********\n\n");
}

