#include <iostream>
#include <string>
using namespace std;

// Book structure to hold book details
struct Book
{
    string title;
    string author;
    string genre;

    Book(string t, string a, string g) : title(t), author(a), genre(g) {}
};

// Node for the binary search tree (BST) for books within a genre
struct SearchNode
{
    Book book;         // Book information
    SearchNode *left;  // Left child
    SearchNode *right; // Right child

    SearchNode(Book b) : book(b), left(nullptr), right(nullptr) {}
};

struct enqNode
{
    string data;   // String data
    enqNode *next; // Pointer to the next node
};
enqNode *start = NULL;

struct stackPtr
{
    string data;
    stackPtr *next;
   
};
stackPtr *topPtr = NULL;

const int MAX_GENRES = 3;

struct BookNode {
    string bookTitle;
    BookNode* next;

    BookNode(const string& title) : bookTitle(title), next(nullptr) {}
};

struct GenreNode {
    string genreName;
    BookNode* bookList;

    GenreNode(const string& name) : genreName(name), bookList(nullptr) {}
};

struct BookGraph {
    GenreNode* genres[MAX_GENRES];
    int genreCount;

    BookGraph() : genreCount(0) {
        for (int i = 0; i < MAX_GENRES; ++i) {
            genres[i] = nullptr;
        }
    }

    void addGenre(const string& genre) {
        if (genreCount >= MAX_GENRES) {
            cout << "Maximum genres reached. Cannot add more genres.\n";
            return;
        }
        genres[genreCount++] = new GenreNode(genre);
    }

    void addBook(const string& genre, const string& bookTitle) {
        for (int i = 0; i < genreCount; ++i) {
            if (genres[i]->genreName == genre) {
                BookNode* newBook = new BookNode(bookTitle);
                if (!genres[i]->bookList) {
                    genres[i]->bookList = newBook;
                } else {
                    BookNode* temp = genres[i]->bookList;
                    while (temp->next) {
                        temp = temp->next;
                    }
                    temp->next = newBook;
                }
                cout << "Book \"" << bookTitle << "\" added to genre \"" << genre << "\".\n";
                return;
            }
        }
        cout << "Genre \"" << genre << "\" not found.\n";
    }

    void displayBooks(const string& genre) {
        for (int i = 0; i < genreCount; ++i) {
            if (genres[i]->genreName == genre) {
                cout << "Books in " << genre << ":\n";
                BookNode* temp = genres[i]->bookList;
                if (!temp) {
                    cout << "No books available.\n";
                    return;
                }
                cout << "RECOMENDATION FOR " << genre << ": "<< endl;
                while (temp) {
                    cout << "- " << temp->bookTitle << "\n";
                    temp = temp->next;
                }
                return;
            }
        }
        cout << "Genre \"" << genre << "\" not found.\n";
    }
};

BookGraph bookGraph; // Global book graph

// Function to add books to the graph in the admin section
void enterBooksForGraph(const string& genre) {
    string title;
    cout << "Enter The Books You Have Entered Above And Type \"Done\" When You Finish For Genre: " << genre << " again(mandatory):\n";
    while (true) {
        cout << "Enter book title: ";
        getline(cin, title);
        if (title == "done") {
            break;
        }
        bookGraph.addBook(genre, title);
    }
}

// Function to display books in a genre
void displayBooksInGenre(const string& genre) {
    bookGraph.displayBooks(genre);
}

// Function to add a book to the binary search tree (BST)
SearchNode *addBookToBST(SearchNode *node, const Book &book)
{
    if (!node)
        return new SearchNode(book);

    if (book.title < node->book.title)
    {
        node->left = addBookToBST(node->left, book);
    }
    else
    {
        node->right = addBookToBST(node->right, book);
    }
    return node;
}

// Helper function to search books in the binary search tree (BST) by title
SearchNode *searchBooks(SearchNode *node, const string &title)
{
    if (!node)
        return nullptr;

    if (title == node->book.title)
    {
        return node;
    }
    else if (title < node->book.title)
    {
        return searchBooks(node->left, title);
    }
    else
    {
        return searchBooks(node->right, title);
    }
}

// Function to display a book's details
string displayBook(const Book &book)
{
    cout << "Found book: " << book.title << " by " << book.author << " [" << book.genre << "]" << endl;
    return book.title;
}

// Function to allow users to choose a genre and enter books
void enterBooksForGenre(SearchNode *&genreRoot, const string &genre)
{
    string title, author;

    cout << "\nEnter books for genre: " << genre << endl;
    while (true)
    {
        cout << "Enter book title (or 'done' to finish): ";
        getline(cin, title);
        if (title == "done")
        {
            break;
        }

        cout << "Enter author: ";
        getline(cin, author);

        // Add the book to the genre's BST
        Book newBook(title, author, genre);
        genreRoot = addBookToBST(genreRoot, newBook);

        cout << "Book added: " << title << " by " << author << " [" << genre << "]" << endl;
    }
}

// Function to search for a book by title in the BST of a genre
string searchBookInGenre(SearchNode *genreRoot)
{
    string title, book;
    cout << "Enter a book title to search: ";
    getline(cin, title);

    SearchNode *result = searchBooks(genreRoot, title);
    if (result)
    {
        book = displayBook(result->book);
        return book;
    }
    else
    {
        cout << "Book not found in the genre." << endl;
        return "";
    }
}

void enqueue(string book)
{
    enqNode *q = new enqNode;
    q->data = book;
    q->next = NULL;

    if (start == NULL)
    {
        start = q;
    }
    else
    {
        enqNode *temp = start;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = q;
    }
}

void dequeue(enqNode*& start,string book){
    if (!start) {
        cout << "Queue is empty!" << endl;
        return;
    }

    enqNode* q = start;
    enqNode* prev = nullptr;

    // Traverse the queue to find the target string
    while (q != nullptr && q->data != book) {
        prev = q;
        q = q->next;
    }

    // If target string is not found
    if (!q) {
        cout << "String not found in the queue." << endl;
        return;
    }

    // If target is the first element
    if (q == start) {
        start = q->next;
    } else {
        prev->next = q->next;
    }

    // Delete the node
    delete q;
    cout << " The book " << book << " has been returned successfully." << endl;
}

void pushL(string k){
   stackPtr *newNode = new stackPtr;
   newNode->data=k;
   newNode->next = topPtr;
   topPtr=newNode;
}

void displayL(stackPtr *q){
    if (q == NULL)
        return;
    displayL(q->next);
    cout << q->data<< ", ";
}

// Clear the stack
void clear() {
        while (topPtr != nullptr) {
            stackPtr* temp = topPtr;
            topPtr = topPtr->next;
            delete temp;  // Delete the current node
        }
        cout << "History cleared successfully.\n";
    }

// Function to display the menu and process user input
void menu()
{
    SearchNode *scienceFictionRoot = nullptr;
    SearchNode *fantasyRoot = nullptr;
    SearchNode *mysteryRoot = nullptr;

    bookGraph.addGenre("Science Fiction");
    bookGraph.addGenre("Fantasy");
    bookGraph.addGenre("Mystery");

    int choice;
    string title;

    while (true)
    {
        cout << "***********WELLCOME TO OUR LIBRARY MANAGEMENT SYSTEM************" << endl;
        cout << "\nSelect a Genre to Manage Books:" << endl;
        cout << "1. Science Fiction" << endl;
        cout << "2. Fantasy" << endl;
        cout << "3. Mystery" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // to clear the newline character from the buffer

        switch (choice)
        {
        case 1:
        {
            int actionChoice;
            string password;
            cout << "1. Add Books to Science Fiction(admin only)" << endl;
            cout << "2. Search And Borrow Books in Science Fiction" << endl;
            cout << "3. Return book." << endl;
            cout << "4. Transaction  History. " << endl;
            cout << "Enter your choice: ";
            cin >> actionChoice;
            cin.ignore(); // to clear the newline character from the buffer

            if (actionChoice == 1)
            {
                cout << "FOR ADMIN ONLY!! if you are an admin please enter your password: ";
                getline(cin, password);
                if (password == "ADMIN")
                {
                    enterBooksForGenre(scienceFictionRoot, "Science Fiction");
                    enterBooksForGraph("Science Fiction");
                }
                else
                    cout << "WRONG PASSWORD!! please use the search feature only." << endl;
            }
             else if (actionChoice == 2)
            {
                displayBooksInGenre("Science Fiction");
                string book = searchBookInGenre(scienceFictionRoot);
                char ch;
                if (book != "")
                {
                    
                    cout << "Do you want to boorow the book('Y' for yes and 'N' for no): ";
                    cin >> ch;
                    if (ch == 'Y' || ch == 'y')
                    {
                        enqueue(book);
                        pushL(book);
                        cout << "successfuly borrowed." << endl;
                        break;
                    }
                    else if (ch == 'N' || ch == 'n'){
                        cout << "search again..." << endl;
                    }
                    else{
                        cout << "invalid entry" << endl;
                    }
                }
                
                
            }
            else if(actionChoice==3){
                string bok; 
                cout << "enter the book you want to return: ";
                getline(cin, bok);
                dequeue(start,bok);
            }
            else if(actionChoice==4){
                int i;
                cout << "1.View Transaction History" << endl;
                cout << "2. Clear History" << endl;
                cout << "enter choise: ";
                cin >> i;
                if(i==1){
                    cout << "Your Transaction History is: ";
                    displayL(topPtr);
                    cout << endl;
                }
                else if(i==2){
                    clear();
                }
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 2:
        {
            int actionChoice;
            string password;
            cout << "1. Add Books to Fantasy(admin only)" << endl;
            cout << "2. Search And Borrow Books in Fantasy" << endl;
            cout << "3. Return book." << endl;
            cout << "4. Transaction  History. " << endl;
            cout << "Enter your choice: ";
            cin >> actionChoice;
            cin.ignore(); // to clear the newline character from the buffer

            if (actionChoice == 1)
            {
                cout << "FOR ADMIN ONLY!! if you are an admin please enter your password: ";
                getline(cin, password);
                if (password == "ADMIN")
                {
                    enterBooksForGenre(fantasyRoot, "Fantasy");
                    enterBooksForGraph("Fantasy");
                }
                else
                    cout << "WRONG PASSWORD!! please use the search feature only." << endl;
            }
            else if (actionChoice == 2)
            {
                displayBooksInGenre("Fantasy");
                string book = searchBookInGenre(fantasyRoot);
                char ch;
                if (book != "")
                {
                    
                    cout << "Do you want to boorow the book('Y' for yes and 'N' for no): ";
                    cin >> ch;
                    if (ch == 'Y' || ch == 'y')
                    {
                        enqueue(book);
                        pushL(book);
                        cout << "successfuly borrowed." << endl;
                        break;
                    }
                    else if (ch == 'N' || ch == 'n'){
                        cout << "search again..." << endl;
                    }
                    else{
                        cout << "invalid entry" << endl;
                    }
                }
                
                
            }
            else if(actionChoice==3){
                string bok; 
                cout << "enter the book you want to return: ";
                getline(cin, bok);
                dequeue(start,bok);
            }
            else if(actionChoice==4){
                int i;
                cout << "1.View Transaction History" << endl;
                cout << "2. Clear History" << endl;
                cout << "enter choise: ";
                cin >> i;
                if(i==1){
                    cout << "Your Transaction History is: ";
                    displayL(topPtr);
                    cout << endl;
                }
                else if(i==2){
                    clear();
                }
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 3:
        {
            int actionChoice;
            string password;
            cout << "1. Add Books to Mystery(admin only)" << endl;
            cout << "2. Search And Borrow Books in Mystery" << endl;
            cout << "3. Return book." << endl;
            cout << "4. Transaction  History. " << endl;
            cout << "Enter your choice: ";
            cin >> actionChoice;
            cin.ignore(); // to clear the newline character from the buffer

            if (actionChoice == 1)
            {
                cout << "FOR ADMIN ONLY!! if you are an admin please enter your password: ";
                getline(cin, password);
                if (password == "ADMIN")
                {
                    enterBooksForGenre(mysteryRoot, "Mystery");
                    enterBooksForGraph("Mystery");
                }
                else
                    cout << "WRONG PASSWORD!! please use the search feature only." << endl;
            }
            else if (actionChoice == 2)
            {
                displayBooksInGenre("Mystery");
                string book = searchBookInGenre(mysteryRoot);
                char ch;
                if (book != "")
                {
                    
                    cout << "Do you want to boorow the book('Y' for yes and 'N' for no): ";
                    cin >> ch;
                    if (ch == 'Y' || ch == 'y')
                    {
                        enqueue(book);
                        pushL(book);
                        cout << "successfuly borrowed." << endl;
                        break;
                    }
                    else if (ch == 'N' || ch == 'n'){
                        cout << "search again..." << endl;
                    }
                    else{
                        cout << "invalid entry" << endl;
                    }
                }
                
                
            }
            else if(actionChoice==3){
                string bok; 
                cout << "enter the book you want to return: ";
                getline(cin, bok);
                dequeue(start,bok); 
            }
            else if(actionChoice==4){
                int i;
                cout << "1.View Transaction History" << endl;
                cout << "2. Clear History" << endl;
                cout << "enter choise: ";
                cin >> i;
                if(i==1){
                    cout << "Your Transaction History is: ";
                    displayL(topPtr);
                    cout << endl;
                }
                else if(i==2){
                    clear();
                }
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 4:
            cout << "Exiting program." << endl;
            return;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

int main()
{
    menu(); // Start the menu-driven program
    return 0;
}
