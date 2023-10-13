//Ammar Munir 
//20L-1150
//final project

//Included Libraries
#ifdef _CRT_SECURE_NO_WARNINGS
#undef _CRT_SECURE_NO_WARNINGS
#endif
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <chrono> //for time//


using namespace std;

char unique_terms1[10300][200] = { '\0' };
char unique_terms[10300][200] = { '\0' };
char doc_list[50][30] = { '\0' };
char term_document_frequency[100] = { 0 };
char term_frequency_in_all_documents[11][100] = { 0 };
char stop_words[500][20] = { '\0' };
char read1[11000][20] = { '\0' };
int counter1 = 0;
int lol1 = 0;
int p4 = 0;
char store[1000][50];
int inc = 1;
char term[15];
int local_counter = 0;
int z1 = 0;



void time_function(char term[]);//prototypes//
void find_term_in_document(int term_ID, int documentID);


int mystrlen(char str[])
{
    int len = 0;
    int i;
    
    for (i = 0; str[i] != '\0'; i++)
    {
        
    }
    return i;
}
void mystrcpy(char a[], char b[])
{
    int l = mystrlen(a);
    int i = 0;
    while (i <= l)
    {
        b[i] = a[i];
        i++;
    }
}

int mystrcmp(char term[], char input[])
{
    int length = mystrlen(term);
    if (length > mystrlen(input))
    {
        return 1;
    }
    else if (length < mystrlen(input))
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            if (term[i] != input[i])
                return 1;
        }
        return 0;
    }
}

void sort(int n, char a2[10000][200])
{
    char low[200];
    int a;
    
    for (int i = 0; i < n - 1; i++)
    {
        a = i;
        strcpy_s(low, a2[i]);
        for (int j = i + 1; j < n; j++)
        {
            if ((strcmp(a2[j], low)) < 0)
            {
                strcpy_s(low, a2[j]);
                a = j;
            }
        }
        strcpy_s(a2[a], a2[i]);
        strcpy_s(a2[i], low);
    }
}

void read_stop_words() {
    ifstream file_terms("stoplist.txt");
    int j = 0;
    int local_counter = 0;
    if (file_terms.is_open()) {
        while (!file_terms.eof()) {
            file_terms >> stop_words[j];
            j++;
            local_counter++;
        }
        
    }
    
    else
    {
        cout << "failure" << endl;
    }
    file_terms.close();
}

void read_docs_list()
{
    ifstream docid;
    docid.open("doclist.txt");
    if (docid.is_open() == true)
    {
        int w = 0;
        while (!docid.eof())
        {
            docid >> doc_list[w];
            w++;
        }
    }
    else
    {
        cout << "ERROR! Your file docids.txt was not succesfully opened!";
    }
    docid.close();
}

void write_docs_with_IDs() {
    
    ofstream doc;
    doc.open("docids.txt");
    
    for (int i = 0; i < 11; i++) {
        doc << i;
        doc << "\t";
        doc << doc_list[i] << endl;
    }
    doc.close();
}

void remove_sc(char arr[]) {
    for (int i = 0; i < 30 && arr[i] != '\0'; i++) {
        if ((int(arr[i]) >= 65 && int(arr[i]) <= 90) || (int(arr[i]) >= 97 && int(arr[i]) <= 122));
        else {
            arr[i] = '\0';
        }
    }
    
}

void my_tolower(char arr[]) {
    
    for (int i = 0; i < 20 && arr[i] != '\0'; i++) {
        if (int(arr[i]) >= 65 && int(arr[i]) <= 90) {
            
            arr[i] = arr[i] + 32;
        }
    }
}

void convert_to_token(char docname[]) {
    
    ifstream temp;
    
    temp.open(docname);
    if (!temp)
    {
        cout << "I could not open the file. Fooey.\n";
    }
    else
    {
        while (!temp.eof()) {
            
            temp >> read1[lol1];
            remove_sc(read1[lol1]);
            my_tolower(read1[lol1]);
            
            lol1++;
            counter1++;
        }
    }
    temp.close();
}

void write_term_IDs() {
    
    ofstream write;
    write.open("termid.txt");
    {
        for (int i = 0; i < p4; i++) {
            write << i << "\t" << unique_terms[i] << endl;
        }
    }
    write.close();
}

void find_term_in_document(int term_ID, int documentID)
{
    int term_id = 0;
    int doc_id = 0;
    char arr[1000] = { '\0' };
    
    ifstream doc_index;
    
    doc_index.open("doc_index.txt");
    if (doc_index.is_open() == true)
    {
        int pl = 0;
        int k = 0;
        int sos = 0;
        int a = 0;
        while (!doc_index.eof() && doc_id <= documentID)
        {
            doc_index >> doc_id;
            doc_index >> term_id;
            doc_index.getline(arr, 1000);
            
            if (doc_id == documentID && term_id == term_ID)
                break;
        }
        if (doc_id != documentID || term_id != term_ID)
        {
            term_document_frequency[1] = -1;
            term_frequency_in_all_documents[documentID][1] = -1;
        }
        else
        {
            
            while (arr[sos] != 10 && arr[sos] != '\0' && arr[sos] != '\n')
            {
                
                term_document_frequency[k] = arr[sos];
                term_frequency_in_all_documents[documentID][k] = arr[sos];
                k++;
                sos++;
            }
            
            
            
        }
        pl = -1;
        term_document_frequency[k] = pl;
        term_frequency_in_all_documents[documentID][k] = pl;
    }
    
    else
    {
        cout << "Oops! Your file was not successfully opened!";
    }
    doc_index.close();
}

void print1DArray(char data[], int length)
{
    for (int i = 1; i < length && data[i] != -1; i++)
    {
        cout << data[i] ;
    }
    if (data[1] != -1)
    {
        
        cout << endl;
    }
    else
    {
        cout << " " << endl;
    }
    
}

void print2DArray(char array[][100], int rows, int cols)
{
    cout << "The position of term :" << endl;
    for (int i = 0; i <= 10; i++)
    {
        cout << "In document " << i << " = ";
        print1DArray(array[i], 100);
    }
}

int hammingDist(char str1[], char str2[])
{
    int i = 0, count = 0;
    while (str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            count++;
        i++;
    }
    return count;
}

int get_term_ID(char term[])
{
    for (int i = 0; term[i] != '\0'; i++)
    {
        term[i] = tolower(term[i]);
    }
    for (int i = 0;unique_terms[i][0]!='\0'; i++)
    {
        if (mystrcmp(unique_terms[i], term) == 0) {
            
            return i;
        }
    }
    return -1;
}

int get_Wrong_Word_ID(char wrong_word[]) {
    int  count = 0;
    int len;
    int flen;
    for (int i = 0;i<925; i++) {
        len = mystrlen(unique_terms[i]);
        flen = mystrlen(wrong_word);
        if (len == flen) {
            
            if (hammingDist(unique_terms[i], wrong_word) < 3) {
                
                cout << unique_terms[i];
                cout << "----Term Id: ";
                cout << i;
                cout << endl;
            }
        }
    }
    
    cout << endl << endl;
    
    
    return 0;
}

int get_Sub_Term_ID(char incomplete_word[]) {
    cout << "The followings are the suggested complete words:";
    cout << endl << endl;
    for (int i = 0; unique_terms[i][0]!='\0'; i++) {
        int count = 0;
        int k1 = 0;
        bool found = false;
        int pp = mystrlen(incomplete_word);
        
        
        for (int j = 0; unique_terms[i][j] != '\0' && found == false; j++) {
            if (unique_terms[i][j] == incomplete_word[k1]) {
                found = false;
                k1++;
                count++;
                if (count == pp) {
                    cout << unique_terms[i];
                    cout << "----Term Id: ";
                    cout << i;
                    cout << endl;
                }
                
            }
            else {
                found = true;
            }
        }
    }
    
    
    return 0;
}

void time_function(char term[]) {
    ofstream history;
    history.open("history.txt", history.app);
    auto timenow =
    chrono::system_clock::to_time_t(chrono::system_clock::now());
    
    
    history << "Current Day, Date and Time is = "
    << ctime(&timenow);
    history << "The searched term is :" << term << endl;
}

void doc_helper(char docname[], int idf[925][11][50]) {
    
    char read2[5000][10] = { '\0' };//creating 3d array to write doc index//
    ofstream write1;
    
    write1.open("doc_index.txt", write1.app);
    int lol2 = 0;
    ifstream iso;
    
    iso.open(docname);
    
    if (!iso)
    {}
    else
    {
        while (!iso.eof()) {
            
            iso >> read2[lol2];
            remove_sc(read2[lol2]);
            my_tolower(read2[lol2]);
            lol2++;
        }
        for (int i = 0; i < 925; i++)
        {
            int temp = 0;
            for (int j = 0; j < lol2; j++)
            {
                if (mystrcmp(unique_terms[i], read2[j]) == 0)
                {
                    idf[i][inc][temp] = j;
                    temp++;
                }
            }
            if (temp != 0) {
                write1 << inc - 1 << "\t" << i << "\t";
                for (int l = 0; l < temp; l++)
                {
                    write1 << idf[i][inc][l] << "	";
                    
                }
                write1 << endl;
            }
        }
    }
    iso.close();
    inc++;
}

void write_doc_index() {
    
    int idf[925][11][50] = { 0 };
    for (int i = 0; i < 11; i++) {
        doc_helper(doc_list[i], idf);
    }
}

void help() {//compaing with stop words//
    bool temp = 0;
    bool flag = false;
    int l5 = 0;
    for (int i = 0; i < lol1; i++)
    {
        flag = false;
        for (int j = 0; stop_words[j][0] != '\0'; j++)
        {
            if (mystrcmp(stop_words[j], read1[i]) == 0)
            {
                flag = true;
            }
        }
        if (flag == false)
        {
            strcpy_s(unique_terms[l5], read1[i]);
            l5++;
        }
    }
}

void copy() {
    
    for (int i = 0; i < lol1; i++) {//copy data//
        if (unique_terms[i][0] != '\0') {
            strcpy_s(unique_terms1[z1], unique_terms[i]);
            z1++;
        }
    }
}

void remove_freq() {
    
    for (int i = 0; i < z1; i++) {
        if (mystrcmp(unique_terms1[i], unique_terms1[i - 1]) != 0)
        {
            strcpy_s(unique_terms[p4], unique_terms1[i]);
            p4++;
        }
    }
}

void read_unique_terms() {
    
    ifstream tf;
    tf.open("termid.txt");
    for (int i = 0; i < 10300; i++) {
        for (int j = 0; j < 200; j++) {
            unique_terms[i][j] = '\0';
        }
    }
    char term4[200];
    if (tf.is_open())
    {
        int counter = 0;
        while (!tf.eof() )
        {
            term[0] = '\0';
            tf >> counter >> term4;
            strcpy(unique_terms[counter], term4);
            
        }
        
    }
}

int main() {
    
    cout << "----------------------H E L L O------------------------" << endl << endl;
    cout << "------W E L C O M E    T O    S E A R C H    E N G I N E--------" << endl;
    cout << endl;
    cout << endl;
    int loop = 0;
    while (loop == 0) {
        int choice;
        cout << "Do you want to skip PART-1?" << endl;
        cout << "Press 1 for YES and  press 0 for NO." << endl;
        cin >> choice;
        
        cout << endl << endl << endl;
        if (choice == 1) {
            read_unique_terms();
            char term[15] = { '\0' };
        lol:	cout << "Enter the term you want to search: " << endl;
            cin >> term;
            
            int term_ID = get_term_ID(term);
            if (term_ID == -1)
            {
                cout << endl << "The term doesnot exists " << endl<<endl;
                get_Sub_Term_ID(term);
                get_Wrong_Word_ID(term);
                goto lol;
                return 1;
            }
            cout << endl;
            cout << "The ID of your term : " << term_ID << endl;
            cout << endl;
            
            for (int i = 0; i <= 10; i++)
            {
                find_term_in_document(term_ID, i);
            }
            cout << endl;
            print2DArray(term_frequency_in_all_documents, 100, 10);
            time_function(term);
            
        }
        
        else {
            read_docs_list();
            cout << "---------Doc list has been read successfully!!!------" << endl;
            cout << endl;
            read_stop_words();
            cout << "-------Stop words has been read successfully!!!!----" << endl;
            cout << endl;
            write_docs_with_IDs();
            cout << "----Docs have been written with ids successfully!!!!----" << endl;
            cout << endl;
            
            for (int i = 0; i < 11; i++) {
                convert_to_token(doc_list[i]);
            }
            
            help();
            sort(lol1, unique_terms);
            copy();
            remove_freq();
            write_term_IDs();
            cout << "----termid.txt has been written successfully!!!----" << endl << endl;
            write_doc_index();
            
            cout << "----doc_index.txt has been written successfully!!!----" << endl << endl;
            char term[15] = { '\0' };
            cout << endl << endl << endl;
        lol1:	cout << "Enter the term you want to search: " << endl;
            cin >> term;
            
            int term_ID = get_term_ID(term);
            if (term_ID == -1)
            {
                cout << endl << "The term doesnot exists " << endl;
                get_Sub_Term_ID(term);
                get_Wrong_Word_ID(term);
                goto lol1;
                return 1;
            }
            cout << endl;
            cout << "The ID of your term : " << term_ID << endl;
            cout << endl;
            
            for (int i = 0; i <= 10; i++)
            {
                find_term_in_document(term_ID, i);
            }
            cout << endl;
            print2DArray(term_frequency_in_all_documents, 100, 10);
            time_function(term);
        }
        cout << endl<<endl;
        cout << "Press 0:To continue" << endl;
        cout<< "Press 1 to end and see history." << endl;
        cin >> loop;
    }
    cout << endl << endl;
    cout << "-------T H I S   I S  Y O U R  H I S T O R Y--------" << endl << endl;
    ifstream old;
    old.open("history.txt");
    char plus[100];
    while (!old.eof()) {
        old.getline(plus, 100);
        cout << plus << endl;
    }
    cout << endl<<endl;
    cout << "----------T H A N K  Y O U ----------" << endl << endl;
    cout << "----------------B Y E ----------------------" << endl << endl;
    
    
    return 0;
    
}
