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

struct BorrowQueNode
{
    string data;   // String data
    BorrowQueNode *next; // Pointer to the next node
};
BorrowQueNode *start = NULL;

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
void BorrowEnque(string book)
{
    BorrowQueNode *q = new BorrowQueNode;
    q->data = book;
    q->next = NULL;

    if (start == NULL)
    {
        start = q;
    }
    else
    {
        BorrowQueNode *temp = start;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = q;
    }
}
void ReturnDeque(BorrowQueNode*& start,string book){
    if (!start) {
        cout << "Queue is empty!" << endl;
        return;
    }

    BorrowQueNode* q = start;
    BorrowQueNode* prev = nullptr;

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

// Function to display the menu and process user input
void menu()
{
    SearchNode *scienceFictionRoot = nullptr;
    SearchNode *fantasyRoot = nullptr;
    SearchNode *mysteryRoot = nullptr;

    int choice;
    string title;

    while (true)
    {
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
                }
                else
                    cout << "WRONG PASSWORD!! please use the search feature only." << endl;
            }
             else if (actionChoice == 2)
            {

                string book = searchBookInGenre(scienceFictionRoot);
                char ch;
                if (book != "")
                {
                    
                    cout << "Do you want to boorow the book('Y' for yes and 'N' for no): ";
                    cin >> ch;
                    if (ch == 'Y' || ch == 'y')
                    {
                        BorrowEnque(book);
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
                ReturnDeque(start,bok);
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
                }
                else
                    cout << "WRONG PASSWORD!! please use the search feature only." << endl;
            }
            else if (actionChoice == 2)
            {

                string book = searchBookInGenre(fantasyRoot);
                char ch;
                if (book != "")
                {
                    
                    cout << "Do you want to boorow the book('Y' for yes and 'N' for no): ";
                    cin >> ch;
                    if (ch == 'Y' || ch == 'y')
                    {
                        BorrowEnque(book);
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
                ReturnDeque(start,bok);
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
                }
                else
                    cout << "WRONG PASSWORD!! please use the search feature only." << endl;
            }
            else if (actionChoice == 2)
            {

                string book = searchBookInGenre(mysteryRoot);
                char ch;
                if (book != "")
                {
                    
                    cout << "Do you want to boorow the book('Y' for yes and 'N' for no): ";
                    cin >> ch;
                    if (ch == 'Y' || ch == 'y')
                    {
                        BorrowEnque(book);
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
                ReturnDeque(start,bok);
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
